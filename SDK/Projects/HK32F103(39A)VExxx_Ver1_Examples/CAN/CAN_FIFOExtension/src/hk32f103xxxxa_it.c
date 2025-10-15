/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_it.c
* @brief:     Main Interrupt Service Routines.
* @author:    AE Team
* @version:   V1.0.0/2023-10-30
*             1.Initial version
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
extern CAN_FilterInitTypeDef  CAN_FilterInitStructure;
__IO uint8_t MsgReceived = 0;
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
  * @brief  This function handles CAN RX0 Handler.
  * @param  None
  * @retval None
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{  
  if(CAN_GetFlagStatus(CAN,CAN_FLAG_FF0) != RESET)
  {
    /* Clears the CAN interrupt pending bit */
    CAN_ClearITPendingBit(CAN, CAN_IT_FF0);

    /* CAN filter init "FIFO1 " */
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 1;
    CAN_FilterInit(&CAN_FilterInitStructure,CAN);    
  }
}
/**
  * @brief  This function handles CAN RX1 Handler.
  * @param  None
  * @retval None
  */
void CAN1_RX1_IRQHandler(void)
{  
  if(CAN_GetFlagStatus(CAN,CAN_FLAG_FF1) != RESET)
  {
    /* Clears the CAN interrupt pending bit */
    CAN_ClearITPendingBit(CAN, CAN_IT_FF1);

    /* CAN filter init "FIFO0 " */
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
    CAN_FilterInit(&CAN_FilterInitStructure,CAN); 
    MsgReceived = 1;
  }
}
