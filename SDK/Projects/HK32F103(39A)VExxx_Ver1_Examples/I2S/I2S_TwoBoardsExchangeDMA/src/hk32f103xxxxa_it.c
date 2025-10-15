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

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

extern __IO uint16_t TxStatus, RxStatus;


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
  * @brief  This function handles DMA1 Channel3 request.
  * @param  None
  * @retval None
  */
void DMA1_Channel3_IRQHandler(void)
{


    if (DMA_GetITStatus(DMA1_IT_TC3) == SET)
    {
        RxStatus = 1;
        DMA_ClearITPendingBit(DMA1_IT_TC3);
    }


}
/**
  * @brief  This function handles DMA1 Channel4 request.
  * @param  None
  * @retval None
  */
void DMA1_Channel4_IRQHandler(void)
{


    if (DMA_GetITStatus(DMA1_IT_TC4) == SET)
    {
        TxStatus = 1;
        DMA_ClearITPendingBit(DMA1_IT_TC4);
    }


}
/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
