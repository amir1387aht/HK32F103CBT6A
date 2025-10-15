/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_it.c
* @brief:     Main Interrupt Service Routines.
* @author:    AE Team
* @version:   V1.0.0/2023-10-30
*                     1.Initial version
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
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CanRxMsg RxMessage, RxMessage1;
extern uint8_t KeyNumber;
extern CanTxMsg TxMessage, TxMessage1;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern void LED_Display(uint8_t Ledstatus);
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
  * @brief  This function handles CAN RX0 Handler.
  * @param  None
  * @retval None
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{  
  if (CAN_MessagePending(CAN, CAN_FIFO0) != 0) 
  {
    
    CAN_Receive(CAN, CAN_FIFO0, &RxMessage);
    LED_Display(RxMessage.Data[0]);
    KeyNumber = RxMessage.Data[0];
  }
}

/**
  * @brief  This function handles CAN RX0 Handler.
  * @param  None
  * @retval None
  */
void CAN1_RX1_IRQHandler(void)
{
  if (CAN_MessagePending(CAN, CAN_FIFO1) != 0) 
  {
    CAN_Receive(CAN, CAN_FIFO1, &RxMessage1);
    LED_Display(RxMessage1.Data[0]);
    KeyNumber = RxMessage1.Data[0];
  }
}

/**
  * @brief  This function handles EXTI 0 request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
 if(KeyNumber < 0x2) 

  {
    KeyNumber = 0x05;
  }
  LED_Display(--KeyNumber);

  TxMessage.Data[0] = KeyNumber;

  CAN_Transmit(CAN, &TxMessage);
  /* Clear the EXTI line 0 pending bit */
  EXTI_ClearITPendingBit(EXTI_Line0);
}    

/**
  * @brief  This function handles EXTI 1 request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
  if(KeyNumber == 0x4) 
  {
    KeyNumber = 0x00;
  }
  LED_Display(++KeyNumber);
  TxMessage1.Data[0] = KeyNumber;
  CAN_Transmit(CAN, &TxMessage1);

  /* Clear the EXTI line 0 pending bit */
  EXTI_ClearITPendingBit(EXTI_Line1);
}
