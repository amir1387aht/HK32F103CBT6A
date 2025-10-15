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
extern uint8_t BufferRx[BUFFER_SIZE];

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
  * @brief  This function handles I2C EV interrupt request.
  * @param  None
  * @retval None
  */
void I2C1_EV_IRQHandler(void)
{
    /* I2C is slave */
    if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_MSL) == RESET)
    {
        if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_ADDR) == SET)
        {
        }

        if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_TXE) == SET)
        {
            sDataNum = BUFFER_SIZE_R;
            s_LowLevel_DMAConfig((uint32_t)BufferRx, (uint8_t)(*&sDataNum), s_DIRECTION_TX);

            /* Enable the DMA Tx Channel */
            DMA_Cmd(s_I2C_DMA_CHANNEL_TX, ENABLE);
        }

        if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_RXNE) == SET)
        {
            sDataNum = BUFFER_SIZE_R;

            /* Configure the DMA Rx Channel with the buffer address and the buffer size */
            s_LowLevel_DMAConfig((uint32_t)BufferRx, (uint16_t)(*&sDataNum), s_DIRECTION_RX);
            DMA_Cmd(s_I2C_DMA_CHANNEL_RX, ENABLE);
        }

        /* If STOPF =1: EV4 (Slave has detected a STOP condition on the bus */
        if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_STOPF) == SET)
        {
            RxFlagM = 1;
            I2C_Cmd(s_I2C, ENABLE);
            /*!< Send STOP Condition */
            I2C_GenerateSTOP(s_I2C, ENABLE);

            /* Disable the DMA Rx Channel and Clear all its Flags */
            DMA_Cmd(s_I2C_DMA_CHANNEL_RX, DISABLE);
            DMA_ClearFlag(s_I2C_DMA_FLAG_RX_GL);
            DMA_Cmd(s_I2C_DMA_CHANNEL_TX, DISABLE);
            DMA_ClearFlag(s_I2C_DMA_FLAG_TX_GL);
        }
    }
}

/**
  * @brief  This function handles I2C Error interrupt request.
  * @param  None
  * @retval None
  */
void I2C1_ER_IRQHandler(void)
{
    if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_AF) == SET)
    {
        I2C_ClearFlag(s_I2C, I2C_FLAG_AF);
    }

    if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_ARLO) == SET)
    {
        I2C_ClearFlag(s_I2C, I2C_FLAG_ARLO);
    }

    if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_BERR) == SET)
    {
        I2C_ClearFlag(s_I2C, I2C_FLAG_BERR);
    }

    if (I2C_GetFlagStatus(s_I2C, I2C_FLAG_OVR) == SET)
    {
        I2C_ClearFlag(s_I2C, I2C_FLAG_OVR);
    }
}

