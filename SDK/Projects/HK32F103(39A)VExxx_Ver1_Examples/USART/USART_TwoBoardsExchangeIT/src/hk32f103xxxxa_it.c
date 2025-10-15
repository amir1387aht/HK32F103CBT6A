/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_it.c
* @brief:     Interrupt Service Routines
* @author:    AE Team
* @version:   V1.0.0/2023-10-31
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_it.h"
#include "main.h"
#include "hk32f103xxxxa_eval.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
uint8_t DataRe = 0;
uint16_t Delay_ms;

/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern void SendData(uint8_t data);
extern uint8_t ReceiveData(void);

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
   if(Delay_ms < 500)
   {
        Delay_ms++;
   }
}

/**
  * @brief  This function handles USARTx global interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
   
    if(Delay_ms >= 500)
    {
        #if (DEVICE == MASTER)   
        if(DataRe == 0x01)
        {
            printf("Slave receive interrupt complete\r\n");
        }else if(DataRe == 0x02){
            printf("Slave flag of send complete set\r\n");
        }
        #elif (DEVICE == SLAVE)
        if(DataRe == 0x01)
        {
            printf("Master flag of send leisure interrupt set\r\n");;
        }else if(DataRe == 0x02){
            printf("Master receive interrupt complete\r\n");
        }                    
        #endif
        Delay_ms = 0; 
    }
    #if (DEVICE == MASTER) 
        
        if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
        {
            if(Delay_ms == 200)
            {
                DataRe =  ReceiveData();
                SendData(0x02);
                printf("Master receive interrupt complete\r\n");
            }
        }

       
        if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
        {  
            if(Delay_ms == 200)
            {
                SendData(0x01);
                printf("Master flag of send leisure interrupt set\r\n");
            }

        }
    #elif (DEVICE == SLAVE) 
        if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
        {
            DataRe =  ReceiveData();
            SendData(0x01); 
            printf("Slave receive interrupt complete\r\n");        
        }
 
    #endif
	
}
/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
