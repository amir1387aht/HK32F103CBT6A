/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_it.c
* @brief:     Interrupt Service Routines
* @author:    AE Team
* @version:   V1.0.0/2023-10-31
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_it.h"
#include "platform_config.h"
/** @addtogroup HK32F103xxxxA_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BufferSize  32
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t TxIdx, RxIdx;
extern uint8_t SPI_MASTER_Buffer_Tx[BufferSize], SPI_SLAVE_Buffer_Rx[BufferSize];
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
  * @brief  This function handles SPI2 Handler.
  * @param  None
  * @retval None
  */
void SPI2_IRQHandler(void)
{
    /* Store SPI_SLAVE received data */
    SPI_SLAVE_Buffer_Rx[RxIdx++] = SPI_I2SReceiveData(SPIz);
   
}

/**
  * @brief  This function handles SPI3 Handler.
  * @param  None
  * @retval None
  */
void SPI1_IRQHandler(void)
{
  
  if (SPI_I2SGetITStatus(SPIy, SPI_I2S_IT_TXE) != RESET)
  {
    /* Send SPI_MASTER data */
    SPI_I2SSendData(SPIy, SPI_MASTER_Buffer_Tx[TxIdx++]);

    /* Disable SPI_MASTER TXE interrupt */
    if (TxIdx == BufferSize)
    {
      SPI_I2SITConfig(SPIy, SPI_I2S_IT_TXE, DISABLE);
    }


  }

}
/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
