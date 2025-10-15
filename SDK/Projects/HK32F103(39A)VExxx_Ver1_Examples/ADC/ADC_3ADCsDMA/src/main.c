/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-11-09
*             1.Initial Version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f103xxxxa_eval.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_3ADCsDMA
  * @{
  */

extern uint16_t ADC2ConvertedValue;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
#define ADC3_DR_Address    ((uint32_t)0x40013C4C)
/* Init Structure definition */
static RCC_ClocksTypeDef RCC_Clocks;
static ADC_InitTypeDef           ADC_InitStructure;
static DMA_InitTypeDef           DMA_InitStructure;
static uint16_t ADC1ConvertedValue = 0;
static uint16_t ADC3ConvertedValue = 0;
static uint32_t TimingDelay = 0;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void RCC_Configuration(void);
static void GPIO_Configuration(void);
static void USART_Config(void);
static void NVIC_Configuration(void);
void TimingDelay_Decrement(void);
static void Delay(__IO uint32_t nTime);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_hk32f103xxxxa.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_hk32f103xxxxa.c file
       */

    /* SysTick end of count event each 10ms */
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);

    /* Debug Usart initialization */
    USART_Config();

    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* NVIC configuration ------------------------------------------------------*/
    NVIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* DMA1 channel1 configuration ----------------------------------------------*/
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC1ConvertedValue;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    /* Enable DMA1 channel1 */
    DMA_Cmd(DMA1_Channel1, ENABLE);

    /* DMA2 channel5 configuration ----------------------------------------------*/
    DMA_DeInit(DMA2_Channel5);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC3_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC3ConvertedValue;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA2_Channel5, &DMA_InitStructure);

    /* Enable DMA2 channel5 */
    DMA_Cmd(DMA2_Channel5, ENABLE);

    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADC1 regular channels configuration */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_28Cycles5);

    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);

    /* ADC2 configuration ------------------------------------------------------*/
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC2, &ADC_InitStructure);

    /* ADC2 regular channels configuration */
    ADC_RegularChannelConfig(ADC2, ADC_Channel_13, 1, ADC_SampleTime_28Cycles5);

    /* Enable ADC2 EOC interrupt */
    ADC_ITConfig(ADC2, ADC_IT_EOC, ENABLE);

    /* ADC3 configuration ------------------------------------------------------*/
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC3, &ADC_InitStructure);

    /* ADC3 regular channel12 configuration */
    ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 1, ADC_SampleTime_28Cycles5);

    /* Enable ADC3 DMA */
    ADC_DMACmd(ADC3, ENABLE);

    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);

    /* Enable ADC1 reset calibration register */
    ADC_ResetCalibration(ADC1);

    /* Check the end of ADC1 reset calibration register */
    while (ADC_GetResetCalibrationStatus(ADC1))
	{
	}

    /* Start ADC1 calibration */
    ADC_StartCalibration(ADC1);

    /* Check the end of ADC1 calibration */
    while (ADC_GetCalibrationStatus(ADC1))
	{
	}


    /* Enable ADC2 */
    ADC_Cmd(ADC2, ENABLE);
    /* Enable ADC2 reset calibration register */
    ADC_ResetCalibration(ADC2);

    /* Check the end of ADC2 reset calibration register */
    while (ADC_GetResetCalibrationStatus(ADC2))
	{
	}


    /* Start ADC2 calibration */
    ADC_StartCalibration(ADC2);

    /* Check the end of ADC2 calibration */
    while (ADC_GetCalibrationStatus(ADC2))
	{
	}


    /* Enable ADC3 */
    ADC_Cmd(ADC3, ENABLE);
    /* Enable ADC3 reset calibration register */
    ADC_ResetCalibration(ADC3);

    /* Check the end of ADC3 reset calibration register */
    while (ADC_GetResetCalibrationStatus(ADC3))
	{
	}


    /* Start ADC3 calibration */
    ADC_StartCalibration(ADC3);

    /* Check the end of ADC3 calibration */
    while (ADC_GetCalibrationStatus(ADC3))
	{
	}


    /* Start ADC1 Software Conversion */
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    /* Start ADC2 Software Conversion */
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);
    /* Start ADC3 Software Conversion */
    ADC_SoftwareStartConvCmd(ADC3, ENABLE);

    while (1)
    {
        Delay(50);
        printf("\r\nSample Values:\tADC1:%03X\tADC2:%03X\tADC3:%03X\t", ADC1ConvertedValue, ADC2ConvertedValue, ADC3ConvertedValue);
    }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
static void RCC_Configuration(void)
{
    /* ADCCLK = PCLK2/4 */
    RCC_ADC1CLKConfig(RCC_PCLK2_Div4);
    RCC_ADC2CLKConfig(RCC_PCLK2_Div4);
    RCC_ADC3CLKConfig(RCC_PCLK2_Div4);

    /* Enable peripheral clocks ------------------------------------------------*/

    /* Enable DMA1 and DMA2 clocks */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2, ENABLE);

    /* Enable ADC1, ADC2, ADC3 and GPIOC clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 |
                           RCC_APB2Periph_ADC3 | RCC_APB2Periph_GPIOC, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure PC.02, PC.03 and PC.00 (ADC Channel12, ADC Channel13 and
       ADC Channel10) as analog inputs */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
  * @brief  Configures Vector Table base location.
  * @param  None
  * @retval None
  */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure and enable ADC interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Configure the USART Device
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configured as follow:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1 Stop Bit
    - Parity = No Parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
}

/**
  * @brief  Redirect the c library function printf to the EVAL_COM1.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /* Send a byte of data to the EVAL_COM1 */
    USART_SendData(EVAL_COM1, (uint8_t) ch);

    /* Wait for transmit completed */
    while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TXE) == RESET)
	{
	}


    return (ch);
}

/**
  * @brief  Set a precise delay with systick timer.
  * @param  None
  * @retval None
  */
static void Delay(__IO uint32_t nTime)

{
    TimingDelay = nTime;

    while (TimingDelay != 0)
	{
	}

}

/**
  * @brief  Called by SysTick_Handler() periodically.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

