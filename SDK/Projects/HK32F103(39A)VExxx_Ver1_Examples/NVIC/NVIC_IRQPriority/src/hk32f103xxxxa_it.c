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
extern uint8_t PreemptionOccured;
extern uint8_t PreemptionPriorityValue;

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
    /* If the EXTI0 IRQ Handler was preempted by SysTick Handler */
    if (NVIC_GetActive(EXTI0_IRQn) != 0)
    {
        PreemptionOccured = 1;
    }
}


/**
  * @brief  This function handles External interrupt Line 0 request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
    /* Generate SysTick exception */
    SCB->ICSR |= 0x04000000;

    /* Clear EXTI pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
}

/**
  * @brief  This function handles External lines 1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    if (EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
        PreemptionPriorityValue = !PreemptionPriorityValue;
        PreemptionOccured = 0;

        /* Modify the WAKEUP_BUTTON_EXTI_IRQn Interrupt Preemption Priority */
        NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriorityValue;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        /* Configure the SysTick Handler Priority: Preemption priority and subpriority */
        NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), !PreemptionPriorityValue, 0));

        /* Clear EXTI pending bit */
        EXTI_ClearITPendingBit(EXTI_Line1);
      
        NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&NVIC_InitStructure);
    }
}



