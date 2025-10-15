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
#include "hk32f103xxxxa_eval.h"
/** @addtogroup HK32F103xxxxA_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USARTx_IRQHandler   USART1_IRQHandler
#define TxBufferSize   (countof(TxBuffer) - 1)
#define RxBufferSize   0x20

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer[] = "\n\rUSART Hyperterminal Interrupts Example: USART-Hyperterminal\
 communication using Interrupt\n\r";
uint8_t RxBuffer[RxBufferSize];
uint8_t NbrOfDataToTransfer = TxBufferSize;
uint8_t NbrOfDataToRead = RxBufferSize;
uint8_t TxCounter = 0; 
uint16_t RxCounter = 0; 

/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern void SendData(uint8_t data);
extern uint8_t ReceiveData(void);
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
  * @brief  This function handles USARTx global interrupt request.
  * @param  None
  * @retval None
  */
void USARTx_IRQHandler(void)
{
  if(USART_GetITStatus(EVAL_COM1, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
    RxBuffer[RxCounter++] = (USART_ReceiveData(EVAL_COM1) & 0x7F);

    if(RxCounter == NbrOfDataToRead)
    {
      /* Disable the EVAL_COM1 Receive interrupt */
      USART_ITConfig(EVAL_COM1, USART_IT_RXNE, DISABLE);
    }
  }

  if(USART_GetITStatus(EVAL_COM1, USART_IT_TXE) != RESET)
  {   
    /* Write one byte to the transmit data register */
    USART_SendData(EVAL_COM1, TxBuffer[TxCounter++]);

    if(TxCounter == NbrOfDataToTransfer)
    {
      /* Disable the EVAL_COM1 Transmit interrupt */
      USART_ITConfig(EVAL_COM1, USART_IT_TXE, DISABLE);
    }
  }
}
/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
