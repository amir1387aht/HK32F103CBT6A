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
  * @brief  This function handles I2C2 Error interrupt request.
  * @param  None
  * @retval None
  */
void I2C2_ER_IRQHandler(void)
{
    /* Check on I2C2 SMBALERT flag and clear it */
    if (I2C_GetITStatus(LM75_I2C, I2C_IT_SMBALERT))
    {
        /* Reading the temperature makes the SMBALERT I/O lower */
        LM75_ReadTemp();
        I2C_ClearITPendingBit(LM75_I2C, I2C_IT_SMBALERT);
        SMbusAlertOccurred++;
    }

    /* Check on I2C2 Time out flag and clear it */
    if (I2C_GetITStatus(LM75_I2C, I2C_IT_TIMEOUT))
    {
        I2C_ClearITPendingBit(LM75_I2C, I2C_IT_TIMEOUT);
    }

    /* Check on I2C2 Arbitration Lost flag and clear it */
    if (I2C_GetITStatus(LM75_I2C, I2C_IT_ARLO))
    {
        I2C_ClearITPendingBit(LM75_I2C, I2C_IT_ARLO);
    }

    /* Check on I2C2 PEC error flag and clear it */
    if (I2C_GetITStatus(LM75_I2C, I2C_IT_PECERR))
    {
        I2C_ClearITPendingBit(LM75_I2C, I2C_IT_PECERR);
    }

    /* Check on I2C2 Overrun/Underrun error flag and clear it */
    if (I2C_GetITStatus(LM75_I2C, I2C_IT_OVR))
    {
        I2C_ClearITPendingBit(LM75_I2C, I2C_IT_OVR);
    }

    /* Check on I2C2 Acknowledge failure error flag and clear it */
    if (I2C_GetITStatus(LM75_I2C, I2C_IT_AF))
    {
        I2C_ClearITPendingBit(LM75_I2C, I2C_IT_AF);
    }

    /* Check on I2C2 Bus error flag and clear it */
    if (I2C_GetITStatus(LM75_I2C, I2C_IT_BERR))
    {
        I2C_ClearITPendingBit(LM75_I2C, I2C_IT_BERR);
    }
}
