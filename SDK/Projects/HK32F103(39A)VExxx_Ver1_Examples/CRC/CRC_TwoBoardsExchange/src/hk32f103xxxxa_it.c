/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_it.c
* @brief:     Main Interrupt Service Routines.
* @author:    AE Team
* @version:   V1.0.0/2023-10-31
*                     1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_it.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t TxBuffer[];
extern uint8_t RxBuffer[];
extern __IO uint8_t RxIndex;
extern __IO uint8_t TxIndex;
extern __IO ButtonMode_TypeDef buttonmode;

__IO uint8_t Counter = 0x00;
__IO uint32_t TimeOut = 0x00;
uint8_t  ComputedCRC = 0;
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
    if (Counter < 10)
    {
        Counter++;
    }
    else
    {
        Counter = 0x00;
        HK_EVAL_LEDToggle(LED1);
    }
}

/**
  * @brief  This function handles USRAT interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
#ifdef MODE_TRANSMITTER

    /* ------------------ USART in mode Tramitter ------------------------------*/
    if (USART_GetITStatus(USART1, USART_IT_TXE) == SET)
    {
        if (TxIndex < 0x48)
        {
            /* Send TxBuffer data */
            USART_SendData(USART1, TxBuffer[TxIndex]);

            while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
            {                
            }

            /* Compute 8-bit CRC */
            CRC_CalcCRC(TxBuffer[TxIndex++]);
        }
        else if (TxIndex == 0x48)
        {
            /* Get computed computed value */
            TxBuffer[TxIndex] = (uint8_t)CRC_GetCRC();

            /* Reset CRC calculation unit */
            CRC_ResetDR();

            /* Send CRC computed value */
            USART_SendData(USART1, TxBuffer[TxIndex]);

            while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
            {
            }
            /* Disable the USARTx transmit data register empty interrupt */
            USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
            /*Discard CRC sent value*/
            TxBuffer[TxIndex] = 0;
            /*reset TxBuffer index*/
            TxIndex = 0;
        }
    }

#else

    /* ------------------ USART in mode Receiver -------------------------------*/
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        if (RxIndex < 0x48)
        {
            /* Receive the USART data */
            RxBuffer[RxIndex] = USART_ReceiveData(USART1);

            /* compute 8-bit CRC */
            CRC_CalcCRC(RxBuffer[RxIndex++]);
        }
        else if (RxIndex == 0x48)
        {
            /* Get computed computed value */
            ComputedCRC = (uint8_t)CRC_GetCRC();

            /* Reset CRC calculation unit */
            CRC_ResetDR();

            /* Recive expected CRC value */
            RxBuffer[RxIndex] = USART_ReceiveData(USART1);

            /* Compare computed CRC and recived CRC values*/
            if (ComputedCRC == RxBuffer[RxIndex])
            {
                /* LED3 Off */ 
                HK_EVAL_LEDOff(LED3);

                /* LED2 On */
                HK_EVAL_LEDOn(LED2);
            }
            else
            {
                /* LED3 On */ 
                HK_EVAL_LEDOn(LED3);

                /* LED2 Off */
                HK_EVAL_LEDOff(LED2);
            }

            /* Reset RxBuffer index */
            RxIndex = 0;
        }
    }

#endif /* MODE_TRANSMITTER */
}

/**
  * @brief  This function handles External lines 0 to 1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
    /* To detect user action on JOY_SEL button */
    if (EXTI_GetITStatus(KEY3_BUTTON_EXTI_LINE) != RESET)
    {
        buttonmode = BUTTON_MODE_EXTI;

        /* Clear the SEL Button EXTI line pending bit */
        EXTI_ClearITPendingBit(KEY3_BUTTON_EXTI_LINE);
    }
}
