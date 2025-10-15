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

extern uint16_t ADC_RegularConvertedValueTab[2];
uint16_t ADC_InjectedConvertedValue1 = 0;
uint16_t ADC_InjectedConvertedValue2 = 0;
uint32_t Index = 0;
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

/******************************************************************************/
/* hk32f103xxxxa Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_hk32f103xxxxa.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */
/**
  * @brief  This function handles ADC1 and ADC2 global interrupts requests.
  * @param  None
  * @retval None
  */
void ADC1_2_IRQHandler(void)
{
    /* Clear ADC1 JEOC pending interrupt bit */
    ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);

    /* Get injected channel11 and channel12 converted value */
    ADC_InjectedConvertedValue1 = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
    ADC_InjectedConvertedValue2 = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2);
    printf("ADC Injected Channel Value: CH11:%03X\tCH12:%03X\t\r\n", ADC_InjectedConvertedValue1, ADC_InjectedConvertedValue2);
}

/**
  * @brief  This function handles DMA1_Channel1 global interrupts requests.
  * @param  None
  * @retval None
  */
void DMA1_Channel1_IRQHandler(void)
{
    /* Clear DMA1_Channel1 pending interrupt bit */
    DMA_ClearITPendingBit(DMA1_IT_TC1 | DMA1_IT_GL1);

    /* Print Regular channel converted value */
    printf("ADC Regular Channel Value: CH4:%03X\tCH10:%03X\t\r\n", ADC_RegularConvertedValueTab[0], ADC_RegularConvertedValueTab[1]);
}

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/


