/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_it.c
* @brief:     Main Interrupt Service Routines.
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*                     1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_it.h"
#include "main.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

extern uint8_t BufferTx[];
extern uint8_t BufferRx[];
extern uint8_t TxFlagM;
extern uint8_t RxFlagM;

extern __IO  uint32_t NumbOfBytes;
extern __IO uint32_t I2CDirection ;
extern uint8_t Address;
__IO uint8_t TxIdx2 = 0, RxIdx2 = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}


/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/**
  * @brief  This function handles I2C Event interrupt request.
  * @param  None
  * @retval None
  */
void I2C1_EV_IRQHandler(void)
{
    /* I2C is slave */
    if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_MSL) == RESET)
    {
        if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_ADDR) == SET)
        {
            /* Initialize the transmit/receive counters for next transmission/reception using Interrupt  */
            TxIdx2 = 0;
            RxIdx2 = 0;
        }
     
        if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_TXE) == SET)
        {   
            I2C_SendData(s_I2C, BufferRx[TxIdx2++]);
        }
        
        if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_RXNE) == SET)
        {           
            BufferRx[RxIdx2++] = I2C_ReceiveData(s_I2C);
        }

        /* If STOPF =1: EV4 (Slave has detected a STOP condition on the bus */     
        if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_STOPF) == SET)
        {          
            RxFlagM = 1;
            I2C_Cmd(s_I2C, ENABLE);
        }
    }

    /* If SB = 1, I2C1 master sent a START on the bus: EV5) */    
    if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_SB) == SET)
    {
        /* Send the slave address for transmssion or for reception (according to the configured value
            in the write master write routine */
        if (I2CDirection == I2C_DIRECTION_TX)
        {
            I2C_Send7bitAddress(s_I2C, Address, I2C_Direction_Transmitter);
        }
        else
        {
            I2C_Send7bitAddress(s_I2C, Address, I2C_Direction_Receiver);
        } 
    }

    /* I2C is Master */
    if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_MSL) == SET)
    {      
        if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_ADDR) == SET)
        {
            if (I2CDirection == I2C_DIRECTION_TX)
            {
                /* Initialize the Transmit counter */
                TxIdx2 = 0;

                /* Write the first data in the data register */            
                I2C_SendData(s_I2C, BufferTx[TxIdx2++]);

                /* Decrement the number of bytes to be written */
                NumbOfBytes--;

                /* If no further data to be sent, disable the I2C BUF IT
                in order to not have a TxE interrupt */
                if (NumbOfBytes == 0)
                {                
                    I2C_ITConfig(s_I2C, I2C_IT_BUF, DISABLE);
                }
            }
            /* Master Receiver */
            else
            {
                /* Initialize Receive counter */
                RxIdx2 = 0;

                /* At this stage, ADDR is cleared because both SR1 and SR2 were read.*/

                /* EV6_1: used for single byte reception. The ACK disable and the STOP
                Programming should be done just after ADDR is cleared. */
                if (NumbOfBytes == 1)
                {
                    /* Clear ACK */                  
                    I2C_AcknowledgeConfig(s_I2C, DISABLE);

                    /* Program the STOP */                
                    I2C_GenerateSTOP(s_I2C, ENABLE);             
                }
            }
        }

        /* Master transmits the remaing data: from data2 until the last one.  */
        /* If TXE is set */      
        if ((I2C_GetFlagStatus(s_I2C, I2C_FLAG_TXE) == SET) && (I2C_GetFlagStatus(s_I2C, I2C_FLAG_BTF) == RESET))
        {
            /* If there is still data to write */
            if (NumbOfBytes != 0)
            {
                /* Write the data in DR register */          
                I2C_SendData(s_I2C, BufferTx[TxIdx2++]);

                /* Decrment the number of data to be written */
                NumbOfBytes--;

                /* If  no data remains to write, disable the BUF IT in order
                to not have again a TxE interrupt. */
                if (NumbOfBytes == 0)
                {
                    TxFlagM = 1;

                    /* Disable the BUF IT */                  
                    I2C_ITConfig(s_I2C, I2C_IT_BUF, DISABLE);
                }
            }
        }

        /* If BTF and TXE are set (EV8_2), program the STOP */      
        if ((I2C_GetFlagStatus(s_I2C, I2C_FLAG_TXE) == SET) && (I2C_GetFlagStatus(s_I2C, I2C_FLAG_BTF) == SET))
        {
            /* Program the STOP */      
            I2C_GenerateSTOP(s_I2C, ENABLE);

            /* Disable EVT IT In order to not have again a BTF IT */   
            I2C_ITConfig(s_I2C, I2C_IT_EVT, DISABLE);
        }

        /* If RXNE is set */      
        if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_RXNE) == SET)
        {
            /* Read the data register */         
            BufferRx[RxIdx2++] = I2C_ReceiveData(s_I2C);

            /* Decrement the number of bytes to be read */
            NumbOfBytes--;

            /* If it remains only one byte to read, disable ACK and program the STOP (EV7_1) */
            if (NumbOfBytes == 1)
            {
                RxFlagM = 1;

                /* Clear ACK */              
                I2C_AcknowledgeConfig(s_I2C, DISABLE);

                /* Program the STOP */          
                I2C_GenerateSTOP(s_I2C, ENABLE);
            }
        }
    }
}

/**
  * @brief  This function handles I2C Error interrupt request.
  * @param  None
  * @retval None
  */
void I2C1_ER_IRQHandler(void)
{
    if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_AF) == SET)
    {      
        I2C_ClearFlag(s_I2C, I2C_FLAG_AF);
    }
  
    if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_ARLO) == SET)
    {      
        I2C_ClearFlag(s_I2C, I2C_FLAG_ARLO);
    }
   
    if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_BERR) == SET)
    {
        I2C_ClearFlag(s_I2C, I2C_FLAG_BERR);
    }

    if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_OVR) == SET)
    {  
        I2C_ClearFlag(s_I2C, I2C_FLAG_OVR);
    }
}

/**
  * @}
  */



