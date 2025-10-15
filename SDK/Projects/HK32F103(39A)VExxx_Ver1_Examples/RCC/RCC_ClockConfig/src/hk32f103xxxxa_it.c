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
#include "main.h"

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
    /* This interrupt is generated when HSE clock fails */
    if (RCC_GetITStatus(RCC_IT_CSS) != RESET)
    {
        /* At this stage: HSE, PLL are disabled (but no change on PLL config) and HSI
            is selected as system clock source */

        /* Enable HSE */
        RCC_HSEConfig(RCC_HSE_ON);

        /* Enable HSE Ready interrupt */
        RCC_ITConfig(RCC_IT_HSERDY, ENABLE);
#ifndef SYSCLK_HSE

        /* Enable PLL Ready interrupt */
        RCC_ITConfig(RCC_IT_PLLRDY, ENABLE);
#endif /* SYSCLK_HSE */

        /* Clear Clock Security System interrupt pending bit */
        RCC_ClearITPendingBit(RCC_IT_CSS);

        /* Once HSE clock recover, the HSERDY interrupt is generated and in the RCC ISR
           routine the system clock will be reconfigured to its previous state (before
           HSE clock failure) */
    }
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
  * @brief  This function handles RCC interrupt request.
  * @param  None
  * @retval None
  */
void RCC_IRQHandler(void)
{
    if (RCC_GetITStatus(RCC_IT_HSERDY) != RESET)
    {
        /* Clear HSERDY interrupt pending bit */
        RCC_ClearITPendingBit(RCC_IT_HSERDY);

        /* Check if the HSE clock is still available */
        if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
        {
#ifdef SYSCLK_HSE

            /* Select HSE as system clock source */
            RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
#else

            /* Enable PLL: once the PLL is ready the PLLRDY interrupt is generated */
            RCC_PLLCmd(ENABLE);
#endif /* SYSCLK_HSE */
        }
    }

    if (RCC_GetITStatus(RCC_IT_PLLRDY) != RESET)
    {
        /* Clear PLLRDY interrupt pending bit */
        RCC_ClearITPendingBit(RCC_IT_PLLRDY);

        /* Check if the PLL is still locked */
        if (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != RESET)
        {
            /* Select PLL as system clock source */
            RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        }
    }
}
