/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_rtc.c
* @brief:     This file provides firmware functions to manage the following
*             functionalities of the Real Time Clock(RTC) peripheral:
*             + Initialization and Configuration
*             + Interrupts and flags management
* @author:    AE Team
* @version:   V1.0.0/2023-10-19
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_rtc.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Driver
  * @{
  */

/** @defgroup RTC RTC
  * @brief RTC driver modules
@verbatim
================================================================================
                      ##### How to use this driver #####
================================================================================
    [..]
    (#) Enable the power and backup interface clocks using
        RCC_APB1PeriphClockCmd();
    (#) Enable access to the Backup registers and RTC using
        PWR_BackupAccessCmd();
    (#) Configure the RTC interrupt enable using
        NVIC_Init();
        RTC_ITConfig();
    (#) Configure the period counting value of the RTC prescaler using
        RTC_SetPrescaler();
@endverbatim
 * @{
 */

/** @defgroup RTC_PERIPH_Constants RTC_PERIPH_Constants
 * @{
 */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* RTC LSB Mask */
#define RTC_LSB_MASK                ((uint32_t)0x0000FFFF)

/* RTC Prescaler MSB Mask */
#define PRLH_MSB_MASK               ((uint32_t)0x000F0000)

/* RTC registers bit address in the alias region */
#define RTC_OFFSET                  (RTC_BASE - PERIPH_BASE)

/* --- CRH Register ----*/
/* Alias word address of RSM_MD bit */
#define CRH_OFFSET                  (RTC_OFFSET + 0x00)
#define RSM_MD_BitNumber            (0x0F)
#define CRH_RSM_MD_BB               (PERIPH_BB_BASE + (CRH_OFFSET * 32) + (RSM_MD_BitNumber * 4))

/**
  * @}
  */

/** @defgroup RTC_Private_Functions RTC_Private_Functions
  * @{
  */
/* Private functions ---------------------------------------------------------*/

/** @defgroup RTC_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
          ##### Initialization and Configuration functions #####
 ===============================================================================
    [..] This section provides functions allowing to:
    (+) Enters/Exits the RTC configuration mode
        (+) Gets/Sets the RTC counter value
        (+) Sets the RTC prescaler value
        (+) Gets the RTC divider value
        (+) Sets the RTC alarm value
        (+) Sets the RTC wakeup timer reload value
        (+) Waits until last write operation on RTC registers has finished
        (+) Waits until the RTC registers are synchronized with RTC APB clock
        (+) Enables or disables the RSM reload strategy
@endverbatim
  * @{
  */

/**
  * @brief  Enters the RTC configuration mode.
  * @retval None
  */
void RTC_EnterConfigMode(void)
{
    /* Set the CNF flag to enter in the Configuration Mode */
    RTC->CRL |= RTC_CRL_CNF;
}

/**
  * @brief  Exits from the RTC configuration mode.
  * @retval None
  */
void RTC_ExitConfigMode(void)
{
    /* Reset the CNF flag to exit from the Configuration Mode */
    RTC->CRL &= (uint16_t)~((uint16_t)RTC_CRL_CNF);
}

/**
  * @brief  Sets the RTC counter value.
  * @param  CounterValue: RTC counter new value.
  * @retval None
  */
void RTC_SetCounter(uint32_t CounterValue)
{
    RTC_EnterConfigMode();
    /* Set RTC COUNTER MSB word */
    RTC->CNTH = CounterValue >> 16;
    /* Set RTC COUNTER LSB word */
    RTC->CNTL = (CounterValue & RTC_LSB_MASK);
    RTC_ExitConfigMode();
}

/**
  * @brief  Gets the RTC counter value.
  * @retval RTC counter value.
  */
uint32_t RTC_GetCounter(void)
{
    uint16_t tmp = 0;
    tmp = RTC->CNTL;
    return (((uint32_t)RTC->CNTH << 16 ) | tmp) ;
}

/**
  * @brief  Sets the RTC prescaler value.
  * @param  PrescalerValue: RTC prescaler new value.
  * @retval None
  */
void RTC_SetPrescaler(uint32_t PrescalerValue)
{
    /* Check the parameters */
    assert_param(IS_RTC_PRESCALER(PrescalerValue));
    RTC_EnterConfigMode();
    /* Set RTC PRESCALER MSB word */
    RTC->PRLH = (PrescalerValue & PRLH_MSB_MASK) >> 16;
    /* Set RTC PRESCALER LSB word */
    RTC->PRLL = (PrescalerValue & RTC_LSB_MASK);
    RTC_ExitConfigMode();
}

/**
  * @brief  Gets the RTC divider value.
  * @retval RTC Divider value.
  */
uint32_t RTC_GetDivider(void)
{
    uint32_t tmp = 0x00;
    tmp = ((uint32_t)RTC->DIVH & (uint32_t)0x000F) << 16;
    tmp |= RTC->DIVL;
    return tmp;
}

/**
  * @brief  Sets the RTC alarm value.
  * @param  AlarmValue: RTC alarm new value.
  * @retval None
  */
void RTC_SetAlarm(uint32_t AlarmValue)
{
    RTC_EnterConfigMode();
    /* Set the ALARM MSB word */
    RTC->ALRH = AlarmValue >> 16;
    /* Set the ALARM LSB word */
    RTC->ALRL = (AlarmValue & RTC_LSB_MASK);
    RTC_ExitConfigMode();
}

/**
  * @brief  Sets the RTC wakeup timer reload value.
  * @param  ReloadValue: RTC wakeup timer substract 1 each clock.
  *         ReloadValue is been reloaded into counter when counter is zero.
  *         The value range is 0x0...0xFFFF
  * @retval None
  */
void RTC_SetWakeupTimer(uint16_t ReloadValue)
{
    RTC_EnterConfigMode();
    /* Set RTC wakeup timer reload value */
    RTC->WUT = ReloadValue;
    RTC_ExitConfigMode();
}

/**
  * @brief  Waits until last write operation on RTC registers has finished.
  * @note   This function must be called before any write to RTC registers.
  * @retval None
  */
void RTC_WaitForLastTask(void)
{
    /* Loop until RTOFF flag is set */
    while ((RTC->CRL & RTC_FLAG_RTOFF) == (uint16_t)RESET)
    {
    }
}

/**
  * @brief  Waits until the RTC registers (RTC_CNT, RTC_ALR and RTC_PRL)
  *         are synchronized with RTC APB clock.
  * @note   This function must be called before any read operation after an APB reset
  *         or an APB clock stop.
  * @retval None
  */
void RTC_WaitForSynchro(void)
{
    /* Clear RSF flag */
    RTC->CRL &= (uint16_t)~RTC_FLAG_RSF;

    /* Loop until RSF flag is set */
    while ((RTC->CRL & RTC_FLAG_RSF) == (uint16_t)RESET)
    {
    }
}

/**
  * @brief  Enables or disables the RSM reload strategy.
  * @param  NewState: Specified div counter reload strategy.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_RSMReloadStrategy(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CRH_RSM_MD_BB = (uint32_t)NewState;
}

/**
  * @}
  */

/** @defgroup RTC_Group2 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim
 ===============================================================================
          ##### Interrupts and flags management functions #####
 ===============================================================================
    [..] This section provides functions allowing to:
        (+) Enables or disables the specified RTC interrupts
        (+) Checks whether the specified RTC interrupt has occurred or not
        (+) Clears the RTC's interrupt pending bits
        (+) Checks whether the specified RTC flag is set or not
        (+) Clears the RTC's pending flags

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified RTC interrupts.
  * @param  RTC_IT: specifies the RTC interrupts sources to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *            @arg RTC_IT_WUT: Wakeup Timer interrupt
  *            @arg RTC_IT_OW: Overflow interrupt
  *            @arg RTC_IT_ALR: Alarm interrupt
  *            @arg RTC_IT_SEC: Second interrupt
  * @param  NewState: new state of the specified RTC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_ITConfig(uint16_t RTC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RTC_IT(RTC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RTC->CRH |= RTC_IT;
    }
    else
    {
        RTC->CRH &= (uint16_t)~RTC_IT;
    }
}

/**
  * @brief  Checks whether the specified RTC interrupt has occurred or not.
  * @param  RTC_IT: specifies the RTC interrupts sources to check.
  *         This parameter can be one of the following values:
  *            @arg RTC_IT_WUT: Wakeup Timer interrupt
  *            @arg RTC_IT_OW: Overflow interrupt
  *            @arg RTC_IT_ALR: Alarm interrupt
  *            @arg RTC_IT_SEC: Second interrupt
  * @retval The new state of the RTC_IT (SET or RESET).
  */
ITStatus RTC_GetITStatus(uint16_t RTC_IT)
{
    ITStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_RTC_GET_IT(RTC_IT));

    if (RTC_IT_WUT == RTC_IT)
    {
        bitstatus = (ITStatus)((RTC->CRL & RTC_IT) >> 8);
    }
    else
    {
        bitstatus = (ITStatus)(RTC->CRL & RTC_IT);
    }

    if (((RTC->CRH & RTC_IT) != (uint16_t)RESET) && (bitstatus != (uint16_t)RESET))
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * @brief  Clears the RTC's interrupt pending bits.
  * @param  RTC_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg RTC_IT_WUT: Wakeup Timer interrupt
  *            @arg RTC_IT_OW: Overflow interrupt
  *            @arg RTC_IT_ALR: Alarm interrupt
  *            @arg RTC_IT_SEC: Second interrupt
  * @retval None
  */
void RTC_ClearITPendingBit(uint16_t RTC_IT)
{
    /* Check the parameters */
    assert_param(IS_RTC_IT(RTC_IT));
    /* Clear the corresponding RTC pending bit */
    RTC->CRL &= (uint16_t)~RTC_IT;
}

/**
  * @brief  Checks whether the specified RTC flag is set or not.
  * @param  RTC_FLAG: specifies the flag to check.
  *         This parameter can be one the following values:
  *            @arg RTC_FLAG_WUTF: RTC wakeup timer over-reload flag
  *            @arg RTC_FLAG_RTOFF: RTC Operation OFF flag
  *            @arg RTC_FLAG_RSF: Registers Synchronized flag
  *            @arg RTC_FLAG_OW: Overflow flag
  *            @arg RTC_FLAG_ALR: Alarm flag
  *            @arg RTC_FLAG_SEC: Second flag
  * @retval The new state of RTC_FLAG (SET or RESET).
  */
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_RTC_GET_FLAG(RTC_FLAG));

    if ((RTC->CRL & RTC_FLAG) != (uint16_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * @brief  Clears the RTC's pending flags.
  * @param  RTC_FLAG: specifies the flag to clear.
  *         This parameter can be any combination of the following values:
  *            @arg RTC_FLAG_WUTF: wakeup timer over flag
  *            @arg RTC_FLAG_RSF: Registers Synchronized flag. This flag is cleared only after
  *                 an APB reset or an APB Clock stop.
  *            @arg RTC_FLAG_OW: Overflow flag
  *            @arg RTC_FLAG_ALR: Alarm flag
  *            @arg RTC_FLAG_SEC: Second flag
  * @retval None
  */
void RTC_ClearFlag(uint16_t RTC_FLAG)
{
    /* Check the parameters */
    assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG));
    /* Clear the corresponding RTC flag */
    RTC->CRL &= (uint16_t)~RTC_FLAG;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

