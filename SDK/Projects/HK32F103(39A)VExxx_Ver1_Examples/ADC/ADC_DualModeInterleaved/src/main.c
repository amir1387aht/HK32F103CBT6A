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

/** @addtogroup ADC_DualModeInterleaved
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADC1_DR_Address         ((uint32_t)0x4001244C)
#define ConvertedValueTabSize   ((uint32_t)16)
#define PrintCount              ((uint32_t)(ConvertedValueTabSize/2))
/* Init Structure definition */
static ADC_InitTypeDef           ADC_InitStructure;
static DMA_InitTypeDef           DMA_InitStructure;
__IO uint32_t ADC_DualConvertedValueTab[ConvertedValueTabSize];
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void RCC_Configuration(void);
static void GPIO_Configuration(void);
static void USART_Config(void);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint16_t *pcvt;
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_hk32f103xxxxa.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_hk32f103xxxxa.c file
       */

    /* Debug Usart initialization */
    USART_Config();

    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* DMA1 channel1 configuration ----------------------------------------------*/
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_DualConvertedValueTab;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = ConvertedValueTabSize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    /* Enable DMA1 Channel1 */
    DMA_Cmd(DMA1_Channel1, ENABLE);

    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.ADC_Mode = ADC_Mode_FastInterl;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 2;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADC1 regular channels configuration */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_17, 2, ADC_SampleTime_1Cycles5);

    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);

    /* ADC2 configuration ------------------------------------------------------*/
    ADC_InitStructure.ADC_Mode = ADC_Mode_FastInterl;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 2;
    ADC_Init(ADC2, &ADC_InitStructure);

    /* ADC2 regular channels configuration */
    ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 1, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC2, ADC_Channel_12, 2, ADC_SampleTime_1Cycles5);

    /* Enable ADC2 external trigger conversion */
    ADC_ExternalTrigConvCmd(ADC2, ENABLE);

    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);

    /* Enable Vrefint channel17 */
    ADC_TempSensorVrefintCmd(ENABLE);

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

    /* Start ADC1 Software Conversion */
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    /* Test on DMA1 channel1 transfer complete flag */
    while (!DMA_GetFlagStatus(DMA1_FLAG_TC1))
	{
	}

    /* Clear DMA1 channel1 transfer complete flag */
    DMA_ClearFlag(DMA1_FLAG_TC1);
    /* Output sampling result to Debug Usart */
    printf("/******* ADC DualMode Regular Simultaneous************/\r\n");
    printf("\r\nCH10(PC0)\tCH17(Vref)\tCH11(PC1)\tCH12(PC2)\r\n");
    pcvt = (uint16_t*)ADC_DualConvertedValueTab;

    for (int i = 0; i < PrintCount; i++)
    {
        printf("%03X,\t\t%03X,\t\t%03X,\t\t%03X\r\n", *pcvt, *(pcvt + 2), \
               *(pcvt + 1), *(pcvt + 3));
        pcvt = pcvt + 4;
    }

    printf("\r\n/*****************************************************/\r\n");

    while (1)
    {
    }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
    /* ADCCLK = PCLK2/4 */
    RCC_ADC1CLKConfig(RCC_PCLK2_Div4);
    RCC_ADC2CLKConfig(RCC_PCLK2_Div4);

    /* Enable peripheral clocks ------------------------------------------------*/

    /* Enable DMA1 clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    /* Enable ADC1, ADC2 and GPIOC clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 |
                           RCC_APB2Periph_GPIOC, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure PC.01, PC.02 and PC.00 (ADC Channel11, Channel12 and Channel10)
      as analog input ----------------------------------------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
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

