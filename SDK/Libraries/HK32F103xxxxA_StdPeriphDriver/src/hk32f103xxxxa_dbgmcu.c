/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_dbgmcu.c
* @brief:     This file provides firmware functions to manage the following
* @author:    AE Team
* @version:   V1.0.0/2023-10-18
* @log:       V1.0.0/2023-10-18// Initial release
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_dbgmcu.h"


/** @addtogroup HK32F103xxxxA_StdPeriph_Driver
  * @{
  */

/** @defgroup DBGMCU DBGMCU
  * @{
  */


#define IDCODE_DEVID_MASK    ((uint32_t)0x00000FFF)

/**
  * @brief  Returns the device revision identifier.
  * @retval Device revision identifier
  */
uint32_t DBGMCU_GetREVID(void)
{
    return(DBGMCU->IDCODE >> 16);
}

/**
  * @brief  Returns the device identifier.
  * @retval Device identifier
  */
uint32_t DBGMCU_GetDEVID(void)
{
    return(DBGMCU->IDCODE & IDCODE_DEVID_MASK);
}

/**
  * @brief  Configures the specified peripheral and low power mode behavior when the MCU under Debug mode.
  * @param  DBGMCU_Periph: specifies the peripheral and low power mode. 
  *         This parameter can be any combination of the following values:
  *            @arg DBGMCU_SLEEP: Keep debugger connection during SLEEP mode
  *            @arg DBGMCU_STOP: Keep debugger connection during STOP mode
  *            @arg DBGMCU_STANDBY: Keep debugger connection during STANDBY mode
  *            @arg DBGMCU_IWDG_STOP: Debug IWDG stopped when Core is halted
  *            @arg DBGMCU_WWDG_STOP: Debug WWDG stopped when Core is halted
  *            @arg DBGMCU_TIM1_STOP: TIM1 counter stopped when Core is halted
  *            @arg DBGMCU_TIM2_STOP: TIM2 counter stopped when Core is halted
  *            @arg DBGMCU_TIM3_STOP: TIM3 counter stopped when Core is halted
  *            @arg DBGMCU_TIM4_STOP: TIM4 counter stopped when Core is halted
  *            @arg DBGMCU_CAN1_STOP: Debug CAN2 stopped when Core is halted
  *            @arg DBGMCU_I2C1_SMBUS_TIMEOUT: I2C1 SMBUS timeout mode stopped when Core is halted
  *            @arg DBGMCU_I2C2_SMBUS_TIMEOUT: I2C2 SMBUS timeout mode stopped when Core is halted
  *            @arg DBGMCU_TIM5_STOP: TIM5 counter stopped when Core is halted
  *            @arg DBGMCU_TIM6_STOP: TIM6 counter stopped when Core is halted
  *            @arg DBGMCU_TIM7_STOP: TIM7 counter stopped when Core is halted
  *            @arg DBGMCU_TIM8_STOP: TIM8 counter stopped when Core is halted           
  * @param  NewState: new state of the specified peripheral in Debug mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DBGMCU_PERIPH(DBGMCU_Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        DBGMCU->CR |= DBGMCU_Periph;
    }
    else
    {
        DBGMCU->CR &= ~DBGMCU_Periph;
    }
}


/**
  * @brief  Enable/disable the trace io.
  * @param  Trace_Mode: the trace mode.This parameter can be choose from the following arg.
  *            @arg TRACE_MODE_0
  *            @arg TRACE_MODE_1
  *            @arg TRACE_MODE_2
  *            @arg TRACE_MODE_3
  * @retval None
  */
void DBGMCU_TraceModeConfig(uint32_t Trace_Mode)
{
    /* Check the parameters */
    assert_param(IS_TRACE_MODE(Trace_Mode));
    DBGMCU->CR |= Trace_Mode;
}

/**
  * @brief  Enable/disable the trace io.
  * @param  NewState: new state of the specified peripheral in Debug mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_TraceCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        DBGMCU->CR |= DBGMCU_CR_TRACE_IOEN;
    }
    else
    {
        DBGMCU->CR &= ~DBGMCU_CR_TRACE_IOEN;
    }
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
