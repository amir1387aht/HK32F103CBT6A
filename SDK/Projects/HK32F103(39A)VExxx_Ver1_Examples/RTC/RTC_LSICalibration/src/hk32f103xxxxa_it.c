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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t tmpCC4[2] = {0, 0};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @addtogroup HK32F103xxxxA_StdPeriph_Template
  * @{
  */
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
  * @brief  This function handles RTC global interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
    if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
    {
        /* Toggle LED2 */
        HK_EVAL_LEDToggle(LED2);

        /* Clear Interrupt pending bit */
        RTC_ClearITPendingBit(RTC_FLAG_SEC);
    }
}

/**
  * @brief  This function handles TIM5 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM5_IRQHandler(void)
{
    uint32_t tmp = 0;

    if (TIM_GetITStatus(TIM5, TIM_IT_CC4) == SET)
    {
        tmpCC4[IncrementVar_OperationComplete()] = (uint16_t)(TIM5->CCR4);
        TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);

        if (GetVar_OperationComplete() >= 2)
        {
            /* Compute the period length */
            tmp = (uint16_t)(tmpCC4[1] - tmpCC4[0] + 1);
            SetVar_PeriodValue(tmp);

            /* Disable the interrupt */
            TIM_ITConfig(TIM5, TIM_IT_CC4, DISABLE);
            TIM_Cmd(TIM5, DISABLE);
        }
    }
}
