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

/** @addtogroup HK32F103xxxxA_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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
  * @brief  This function handles TIM2 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
    {
        /* Clear TIM2 Capture Compare1 interrupt pending bit*/
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);

        /* PC.06 turnoff after 1000 ms */
        GPIO_ResetBits(GPIOC, GPIO_Pin_6);
    }
    else if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
    {
        /* Clear TIM2 Capture Compare2 interrupt pending bit*/
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);

        /* PC.07 turnoff after 500 ms */
        GPIO_ResetBits(GPIOC, GPIO_Pin_7);
    }
    else if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
    {
        /* Clear TIM2 Capture Compare3 interrupt pending bit*/
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);

        /* PC.08 turnoff after 250 ms */
        GPIO_ResetBits(GPIOC, GPIO_Pin_8);
    }
    else
    {
        /* Clear TIM2 Capture Compare4 interrupt pending bit*/
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);

        /* PC.09 turnoff after 125 ms */
        GPIO_ResetBits(GPIOC, GPIO_Pin_9);
    }
}
