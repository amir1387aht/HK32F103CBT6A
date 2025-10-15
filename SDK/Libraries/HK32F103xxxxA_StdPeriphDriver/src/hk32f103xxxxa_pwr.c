/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_pwr.c
* @brief:     PWR initialization and configuration           
* @author:    AE Team
* @version:   V1.0.0/2022-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"
#include "hk32f103xxxxa_pwr.h"
#include "hk32f103xxxxa_rcc.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @brief PWR driver modules
  * @{
  */

/** @defgroup PWR_Private_Defines PWR_Private_Defines
  * @{
  */
/* Private typedef ---------------------------------------------------------

  --*/
/* Private define ------------------------------------------------------------*/

/* ------------------ PWR registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_DS_MASK               ((uint32_t)0xFFFFFFFC)
#define CR_PLS_MASK              ((uint32_t)0xFFFFFF1F)

/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWR_Private_Functions PWR_Private_Functions
  * @{
  */

/** @defgroup PWR_Group1 Backup Domain Access function
 *  @brief   Backup Domain Access function
 *
@verbatim
  ==============================================================================
                   ##### Backup Domain Access function #####
  ==============================================================================

    [..] After reset, the Backup Domain Registers (RCC BDCR Register, RTC registers
         and RTC backup registers) are protected against possible stray write accesses.
    [..] To enable access to Backup domain use the PWR_BackupAccessCmd(ENABLE) function.

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the PWR peripheral registers to their default reset values.
  * @retval None
  */
void PWR_DeInit(void)
{
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}


/**
  * @brief  Enables or disables access to the Backup domain registers.
  * @note   If the HSE divided by 32 is used as the RTC clock, the
  *         Backup Domain Access should be kept enabled.
  * @param  NewState: new state of the access to the Backup domain registers.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_BackupAccessCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Backup Domain Access */
        PWR->CR |= PWR_CR_DBP;
    }
    else
    {
        /* Disable the Backup Domain Access */
        PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_DBP);
    }
}

/**
  * @}
  */

/** @defgroup PWR_Group2 PVD configuration functions
 *  @brief   PVD configuration functions
 *
@verbatim
  ==============================================================================
                    ##### PVD configuration functions #####
  ==============================================================================
  [..]
  (+) The PVD is used to monitor the VDD power supply by comparing it to a threshold
      selected by the PVD Level (PLS[2:0] bits in the PWR_CR).
  (+) A PVDO flag is available to indicate if VDD/VDDA is higher or lower than the
      PVD threshold. This event is internally connected to the EXTI line16
      and can generate an interrupt if enabled through the EXTI registers.
  (+) The PVD is stopped in Standby mode.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
  * @param  PWR_PVDLevel: specifies the PVD detection level
  *         This parameter can be one of the following values:
  *            @arg PWR_PVDLevel_0
  *            @arg PWR_PVDLevel_1
  *            @arg PWR_PVDLevel_2
  *            @arg PWR_PVDLevel_3
  *            @arg PWR_PVDLevel_4
  *            @arg PWR_PVDLevel_5
  *            @arg PWR_PVDLevel_6
  *            @arg PWR_PVDLevel_7
  * @param  PWR_PVDMode: specifies the PVD mode
  *         This parameter can be one of the following values:
  *            @arg PVD_MODE_IT
  *            @arg PVD_MODE_EVT
  * @param  PWR_PVDEdge: specifies the edge
  *            @arg PVD_RISING_EDGE
  *            @arg PVD_FALLING_EDGE
  *            @arg PVD_RISING_FALLING
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection level.
  * @retval None
  */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel, uint32_t PWR_PVDMode, uint32_t PWR_PVDEdge)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
    EXTI->EMR &= (uint32_t)~((uint32_t)EXTI_EMR_MR16);
    EXTI->IMR &= (uint32_t)~((uint32_t)EXTI_IMR_MR16);
    EXTI->FTSR &= (uint32_t)~((uint32_t)EXTI_FTSR_TR16);
    EXTI->RTSR &= (uint32_t)~((uint32_t)EXTI_RTSR_TR16);
    tmpreg = PWR->CR;
    /* Clear PLS[7:5] bits */
    tmpreg &= CR_PLS_MASK;
    /* Set PLS[7:5] bits according to PWR_PVDLevel value */
    tmpreg |= (uint32_t)((uint32_t)PWR_PVDLevel << PWR_CR_PLS_Pos);
    /* Store the new value */
    PWR->CR = tmpreg;

    /* Configure interrupt mode */
    if ((PWR_PVDMode & PVD_MODE_IT) == PVD_MODE_IT)
    {
        EXTI->IMR |= EXTI_IMR_MR16;
    }

    /* Configure event mode */
    if ((PWR_PVDMode & PVD_MODE_EVT) == PVD_MODE_EVT)
    {
        EXTI->EMR |= EXTI_EMR_MR16;
    }

    /* Configure the edge */
    if ((PWR_PVDEdge & PVD_RISING_EDGE) == PVD_RISING_EDGE)
    {
        EXTI->RTSR |= EXTI_RTSR_TR16;
    }

    if ((PWR_PVDEdge & PVD_FALLING_EDGE) == PVD_FALLING_EDGE)
    {
        EXTI->FTSR |= EXTI_FTSR_TR16;
    }
}


/**
  * @brief  Enables or disables the Power Voltage Detector(PVD).
  * @param  NewState: new state of the PVD.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_PVDCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the PVD */
        PWR->CR |= PWR_CR_PVDE;
    }
    else
    {
        /* Disable the PVD */
        PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_PVDE);
    }
}
/**
  * @}
  */

/** @defgroup PWR_Group3 WakeUp pins configuration functions
 *  @brief   WakeUp pins configuration functions
 *
@verbatim
  ==============================================================================
               ##### WakeUp pin configuration functions #####
  ==============================================================================

  (+) WakeUp pins are used to wakeup the system from Standby mode. These pins are
      forced in input pull down configuration and are active on rising edges.
  (+) There are eight WakeUp pins: WakeUp Pin 1 on PA.00 and WakeUp Pin 2 on PC.13.
            WakeUp Pin 3 on PA.8

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the WakeUp Pin functionality.
  * @param  PWR_WakeUpPin: specifies the WakeUpPin or RTC .
  *         This parameter can be one of the following values
  *            @arg PWR_WakeUpPin_1 :Enable WKUP1 pin
  *            @arg PWR_WakeUpPin_2 :Enable WKUP2 pin
  *            @arg PWR_WakeUpPin_3 :Enable WKUP3 pin
  * @param  NewState: new state of the WakeUp Pin functionality.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_PWR_WAKEUP_PIN(PWR_WakeUpPin));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the EWUPx pin */
        PWR->CSR |= PWR_WakeUpPin;
    }
    else
    {
        /* Disable the EWUPx pin */
        PWR->CSR &= ~PWR_WakeUpPin;
    }
}

/**
  * @}
  */


/** @defgroup PWR_Group4 Low Power modes configuration functions
 *  @brief   Low Power modes configuration functions
 *
@verbatim

@endverbatim
  * @{
  */

/**
  * @brief  Enters Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param  PWR_SLEEPEntry: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *            @arg PWR_SLEEPEntry_WFI: enter SLEEP mode with WFI instruction
  *            @arg PWR_SLEEPEntry_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void PWR_EnterSleepMode(uint8_t PWR_SLEEPEntry)
{
    /* Check the parameters */
    assert_param(IS_PWR_SLEEP_ENTRY(PWR_SLEEPEntry));
    /* Clear SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

    /* Select SLEEP mode entry -------------------------------------------------*/
    if (PWR_SLEEPEntry == PWR_SLEEPEntry_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
}


/**
  * @brief  Enters STOP mode.
  * @note   In Stop mode, all I/O pins keep the same state as in Run mode.
  * @note   When exiting Stop mode by issuing an interrupt or a wakeup event,
  *         the HSI RC oscillator is selected as system clock.
  * @note   When the voltage regulator operates in low power mode, an additional
  *         startup delay is incurred when waking up from Stop mode.
  *         By keeping the internal regulator ON during Stop mode, the consumption
  *         is higher although the startup time is reduced.
  * @param  PWR_Regulator: specifies the regulator state in STOP mode.
  *         This parameter can be one of the following values:
  *            @arg PWR_Regulator_ON: STOP mode with regulator ON
  *            @arg PWR_Regulator_LowPower: STOP mode with regulator in low power mode
  * @param  PWR_STOPEntry: specifies if STOP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *            @arg PWR_STOPEntry_WFI: enter STOP mode with WFI instruction
  *            @arg PWR_STOPEntry_WFE: enter STOP mode with WFE instruction
  *            @arg PWR_STOPEntry_SLEEPONEXIT: enter STOP mode with SLEEPONEXIT instruction
  * @retval None
  */
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_PWR_REGULATOR(PWR_Regulator));
    assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));
    /* Select the regulator state in STOP mode ---------------------------------*/
    tmpreg = PWR->CR;
    /* Clear PDDS and LPDS bits */
    tmpreg &= CR_DS_MASK;
    /* Set LPDS bit according to PWR_Regulator value */
    tmpreg |= PWR_Regulator;
    /* Store the new value */
    PWR->CR = tmpreg;
    /* Set SLEEPDEEP bit of Cortex-M3 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Select STOP mode entry --------------------------------------------------*/
    if (PWR_STOPEntry == PWR_STOPEntry_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
        /* Reset SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
    }
    else if (PWR_STOPEntry == PWR_STOPEntry_WFE)
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
        /* Reset SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
    }
    else
    {
        /* Set SLEEP on exit bit of Cortex-M3 System Control Register */
        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    }
}



/**
  * @brief  Enters STANDBY mode.
  * @param  PWR_STANDBYEntry
  * @retval None
  */
void PWR_EnterSTANDBYMode(uint8_t PWR_STANDBYEntry)
{
    assert_param(IS_PWR_STANDBY_ENTRY(PWR_STANDBYEntry));
    /* Select STANDBY mode */
    PWR->CR |= PWR_CR_PDDS;
    /* Set SLEEPDEEP bit of Cortex-M3 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Select STANDBY mode entry --------------------------------------------------*/
    if (PWR_STANDBYEntry == PWR_STOPEntry_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
        /* Reset SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
    }
    else if (PWR_STANDBYEntry == PWR_STOPEntry_WFE)
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
        /* Reset SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
    }
    else
    {
        /* Set SLEEP on exit bit of Cortex-M3 System Control Register */
        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    }
}
/**
  * @}
  */


/** @defgroup PWR_Group5 Flags management functions
 *  @brief   Flags management functions
 *
@verbatim
  ==============================================================================
                       ##### Flags management functions #####
  ==============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified PWR flag is set or not.
  * @param  PWR_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg PWR_FLAG_WU: Wake Up flag. This flag indicates that a wakeup
  *                 event was received from the WKUP pin or from the RTC alarm
  *                 (Alarm A or Alarm B), RTC Tamper event or RTC TimeStamp event.
  *            @arg PWR_FLAG_SB: StandBy flag. This flag indicates that the
  *                 system was resumed from StandBy mode.
  *            @arg PWR_FLAG_PVDO: PVD Output. This flag is valid only if PVD
  *                 is enabled by the PWR_PVDCmd() function.
  *            @arg PWR_FLAG_LDORDY: Internal Voltage Reference Ready flag.
  * @retval The new state of PWR_FLAG (SET or RESET).
  */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_PWR_GET_FLAG(PWR_FLAG));

    if ((PWR->CSR & PWR_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the flag status */
    return bitstatus;
}


/**
  * @brief  Clears the PWR's pending flags.
  * @param  PWR_FLAG: specifies the flag to clear.
  *         This parameter can be one of the following values:
  *            @arg PWR_FLAG_WU: Wake Up flag
  *            @arg PWR_FLAG_SB: StandBy flag
  * @retval None
  */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
    /* Check the parameters */
    assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));
    PWR->CR |=  PWR_FLAG << 2;
}

/**
  * @brief  wakeup pin polarity config.
  * @note   the wakeup pin can set rising edge  wakeup or falling edge
  * @param  WakeUpPin: specifies the wake up pin
  *            @arg WAKE_UP_PIN1
  *            @arg WAKE_UP_PIN2
  *            @arg WAKE_UP_PIN3
  * @param  Edge: specifies the wake up pin polarity
  *            @arg FALLING_EDGE
  *            @arg RISING_EDGE
  * @retval None
  */
void PWR_WakeupPinPolarityConfig(uint32_t WakeUpPin, uint32_t Edge)
{
    /* Check the parameters */
    assert_param(IS_WAKEUPPIN_STATE(Edge));
    assert_param(IS_WAKEUP_PIN(WakeUpPin));

    if (WakeUpPin == WAKE_UP_PIN1)
    {
        /* clear WUPOL1 */
        PWR->WUP_POL &= (uint32_t)~((uint32_t)PWR_WUP_POL_WUPOL1);
        /* set WUPOL1*/
        PWR->WUP_POL |= (Edge << PWR_WUP_POL_WUPOL1_Pos);
    }
    else if (WakeUpPin == WAKE_UP_PIN2)
    {
        /* clear WUPOL2 */
        PWR->WUP_POL &= (uint32_t)~((uint32_t)PWR_WUP_POL_WUPOL2);
        /* set WUPOL2*/
        PWR->WUP_POL |= (Edge << PWR_WUP_POL_WUPOL2_Pos);
    }
    else
    {
        /* clear WUPOL3 */
        PWR->WUP_POL &= (uint32_t)~((uint32_t)PWR_WUP_POL_WUPOL3);
        /* set WUPOL3*/
        PWR->WUP_POL |= (Edge << PWR_WUP_POL_WUPOL3_Pos);
    }
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
