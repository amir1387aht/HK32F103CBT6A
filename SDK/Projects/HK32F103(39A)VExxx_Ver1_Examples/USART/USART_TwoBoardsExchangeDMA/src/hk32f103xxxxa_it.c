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
/** @addtogroup HK32F103xxxxA_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
uint8_t DataStart= 0;
uint16_t Delay_ms;

/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern void SendData(uint8_t data);
extern uint8_t ReceiveData(void);
extern uint8_t RxCounter;
extern uint8_t RxBuffer2[];
extern uint8_t RxBuffer1[];
extern uint8_t NbrOfDataToRead;
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

    #if (DEVICE == MASTER) 
    
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        /* Read one byte from the receive data register */
        RxBuffer1[RxCounter++] = USART_ReceiveData(USART2);

        if(RxCounter == NbrOfDataToRead)
        {
            /* Disable the USART2 Receive interrupt */
            USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
        }
    }
    #elif (DEVICE == SLAVE) 

        if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
        {
            /* Read one byte from the receive data register */
            RxBuffer2[RxCounter++] = USART_ReceiveData(USART2);

            if(RxCounter == NbrOfDataToRead)
            {
                /* Disable the USART2 Receive interrupt */
                USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
            }
        }
  
    #endif
	
}
/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
