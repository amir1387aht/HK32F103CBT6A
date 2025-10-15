/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_exti.c
* @brief:     This file provides all the EXTI firmware functions:      
*             + Initialization and Configuration Functions
*             + SIRQ_Generate_Functions
*             + Flag Managemen Functions
* @author:    AE Team
* @version:   V1.0.0/2023-10-19
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_exti.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Driver
  * @{
  */

/** @defgroup EXTI EXTI
  * @brief EXTI driver modules
  * @{
  @verbatim
  ==============================================================================
                       ##### How to use this driver #####
  ==============================================================================
    [..] In order to use an I/O pin as an external interrupt source, follow
         steps below:
    (#) Configure the I/O in input mode using GPIO_Init()
    (#) Select the input source pin for the EXTI line using
        SYSCFG_EXTILineConfig().
    (#) Select the mode(interrupt, event) and configure the trigger selection
        (Rising, falling or both) using EXTI_Init(). For the internal interrupt,
        the trigger selection is not needed( the active edge is always the rising one).
    (#) Configure NVIC IRQ channel mapped to the EXTI line using NVIC_Init().
    (#) Optionally, you can generate a software interrupt using the function EXTI_GenerateSWInterrupt().
  @endverbatim
  */

/** @defgroup EXTI_PERIPH_Constants EXTI_PERIPH_Constants 
  * @{
  */
#define EXTI_LINENONE    ((uint32_t)0x00000)  /* No interrupt selected */
/**
  * @}
  */

/** @defgroup EXTI_Private_Functions EXTI_Private_Functions
  * @{
  */
/* Private functions ---------------------------------------------------------*/

/** @defgroup EXTI_Group1 Initialization and Configuration Functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
          ##### Initialization and Configuration functions #####
 ===============================================================================
    [..] This section provides functions allowing to:
        (+) Deinitializes the EXTI
        (+) Initializes the EXTI
        (+) Fills each EXTI_InitStruct member with its reset value

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
  * @retval None
  */
void EXTI_DeInit(void)
{
    EXTI->IMR   = 0x00000000;
    EXTI->EMR   = 0x00000000;
    EXTI->RTSR  = 0x00000000;
    EXTI->FTSR  = 0x00000000;
    EXTI->PR    = 0xFFFFFFFF;
}

/**
  * @brief  Initializes the EXTI peripheral according to the specified
  *         parameters in the EXTI_InitStruct.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure
  *         that contains the configuration information for the EXTI peripheral.
  * @retval None
  */
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
    uint32_t tmp = 0;
    /* Check the parameters */
    assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
    assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
    assert_param(IS_EXTI_LINE(EXTI_InitStruct->EXTI_Line));
    assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));
    tmp = (uint32_t)EXTI_BASE;

    if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
    {
        /* Clear EXTI line configuration */
        EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
        EXTI->EMR &= ~EXTI_InitStruct->EXTI_Line;
        tmp += EXTI_InitStruct->EXTI_Mode;
        *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
        /* Clear Rising Falling edge configuration */
        EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
        EXTI->FTSR &= ~EXTI_InitStruct->EXTI_Line;

        /* Select the trigger for the selected external interrupts */
        if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
        {
            /* Rising Falling edge */
            EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
            EXTI->FTSR |= EXTI_InitStruct->EXTI_Line;
        }
        else
        {
            tmp = (uint32_t)EXTI_BASE;
            tmp += EXTI_InitStruct->EXTI_Trigger;
            *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
        }
    }
    else
    {
        tmp += EXTI_InitStruct->EXTI_Mode;
        /* Disable the selected external lines */
        *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
    }
}

/**
  * @brief  Fills each EXTI_InitStruct member with its reset value.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
{
    EXTI_InitStruct->EXTI_Line = EXTI_LINENONE;
    EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/**
  * @}
  */

/** @defgroup EXTI_Group2 SIRQ_Generate_Functions
 *  @brief   SIRQ_generate_Functions
 *
@verbatim
 ===============================================================================
          ##### SIRQ_generate_Functions #####
 ===============================================================================
    [..] This section provides functions allowing to:
        (+) Generates a Software interrupt on selected EXTI line.
        
@endverbatim
  * @{
  */

/**
  * @brief  Generates a Software interrupt on selected EXTI line.
  * @param  EXTI_Line: specifies the EXTI line on which the software interrupt
  *         will be generated.
  *         This parameter can be any combination of EXTI_Linex
  *         where x can be (0..23).
  * @retval None
  */
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line)
{
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(EXTI_Line));
    EXTI->SWIER |= EXTI_Line;
}

/**
  * @}
  */

/** @defgroup EXTI_Group3 Flag Managemen Functions
 *  @brief   Flag Managemen Functions
 *
@verbatim
 ===============================================================================
          ##### Flag Managemen Functions #####
 ===============================================================================
    [..] This section provides functions allowing to:
        (+) Checks whether the specified EXTI line flag is set or not
        (+) Clears the EXTI's line pending flags
        (+) Checks whether the specified EXTI line is asserted or not
        (+) Clears the EXTI's line pending bits
        
@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  EXTI_Line: specifies the EXTI line flag to check.
  *         This parameter can be any combination of EXTI_Linex where x can be (0..23).
  * @retval The new state of EXTI_Line (SET or RESET).
  */
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_GET_EXTI_LINE(EXTI_Line));

    if ((EXTI->PR & EXTI_Line) != (uint32_t)RESET)
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
  * @brief  Clears the EXTI's line pending flags.
  * @param  EXTI_Line: specifies the EXTI lines flags to clear.
  *         This parameter can be any combination of EXTI_Linex where x can be (0..23).
  * @retval None
  */
void EXTI_ClearFlag(uint32_t EXTI_Line)
{
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(EXTI_Line));
    EXTI->PR = EXTI_Line;
}

/**
  * @brief  Checks whether the specified EXTI line is asserted or not.
  * @param  EXTI_Line: specifies the EXTI line to check.
  *         This parameter can be any combination of EXTI_Linex where x can be (0..23).
  * @retval The new state of EXTI_Line (SET or RESET).
  */
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;
    /* Check the parameters */
    assert_param(IS_GET_EXTI_LINE(EXTI_Line));
    enablestatus =  EXTI->IMR & EXTI_Line;

    if (((EXTI->PR & EXTI_Line) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
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
  * @brief  Clears the EXTI's line pending bits.
  * @param  EXTI_Line: specifies the EXTI lines to clear.
  *         This parameter can be any combination of EXTI_Linex where x can be (0..23).
  * @retval None
  */
void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
{
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(EXTI_Line));
    EXTI->PR = EXTI_Line;
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

