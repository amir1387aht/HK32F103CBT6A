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

/** @addtogroup HK32F103xxxxA_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern const uint16_t I2S_Buffer_Tx[32];
extern __IO uint16_t TxIdx, RxIdx;
extern uint16_t I2S_Buffer_Rx[32];
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
  * @brief  This function handles I2s1 request.
  * @param  None
  * @retval None
  */
void SPI1_IRQHandler(void)
{

     /* Check the interrupt source */
  if (SPI_I2SGetITStatus(SPI1, SPI_I2S_IT_TXE) == SET)
  {
    /* Send a data from I2S3 */
    SPI_I2SSendData(SPI1,I2S_Buffer_Tx[TxIdx++]);
  }

  /* Check the end of buffer transfer */
  if (RxIdx == 32)
  {
    /* Disable the I2S1 TXE interrupt to end the communication */
    SPI_I2SITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);
  }   
}
/**
  * @brief  This function handles I2s2 request.
  * @param  None
  * @retval None
  */
void SPI2_IRQHandler(void)
{

     /* Check the interrupt source */
  if (SPI_I2SGetITStatus(SPI2, SPI_I2S_IT_RXNE) == SET)
  {
    /* Store the I2S2 received data in the relative data table */
    I2S_Buffer_Rx[RxIdx++]  = SPI_I2SReceiveData(SPI2);
  }   

}
/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
