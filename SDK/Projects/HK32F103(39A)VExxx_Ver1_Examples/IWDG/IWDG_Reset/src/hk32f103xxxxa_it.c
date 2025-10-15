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
extern __IO uint32_t TimingDelay;
uint16_t IC1ReadValue1 = 0, IC1ReadValue2 = 0;
__IO uint16_t CaptureNumber = 0;
__IO uint32_t Capture = 0;
extern uint32_t LsiFreq;
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
    TimingDelay--;
}

/**
  * @brief  This function handles EXTI0 Handler.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line0);

        /* As the following address is invalid (not mapped,reserved area in datasheet), a Hardfault exception
        will be generated with an infinite loop and when the WWDG counter falls to 63 the WWDG reset occurs */
        *(uint32_t*)0xA0002000 = 0x12345678;
    }
}

/**
  * @brief  This function handles TIM5 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM5_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)
    {
        if (CaptureNumber == 0)
        {
            /* Get the Input Capture value */
            IC1ReadValue1 = TIM_GetCapture4(TIM5);
        }
        else if (CaptureNumber == 1)
        {
            /* Get the Input Capture value */
            IC1ReadValue2 = TIM_GetCapture4(TIM5);

            /* Capture computation */
            if (IC1ReadValue2 > IC1ReadValue1)
            {
                Capture = (IC1ReadValue2 - IC1ReadValue1);
            }
            else
            {
                Capture = ((0xFFFF - IC1ReadValue1) + IC1ReadValue2);
            }

            /* Frequency computation */
            LsiFreq = (uint32_t) SystemCoreClock / Capture;
            LsiFreq *= 8;
        }

        CaptureNumber++;
        /* Clear TIM5 Capture compare interrupt pending bit */
        TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);
    }
}


