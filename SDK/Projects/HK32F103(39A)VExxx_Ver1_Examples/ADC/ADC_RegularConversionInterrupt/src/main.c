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

/** @addtogroup ADC_RegularConversionInterrupt
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Init Structure definition */
static ADC_InitTypeDef           ADC_InitStructure;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void RCC_Configuration(void);
static void GPIO_Configuration(void);
static void USART_Config(void);
static void NVIC_Configuration(void);
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

    /* Debug Usart initialization */
    USART_Config();

    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* NVIC configuration ------------------------------------------------------*/
    NVIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADC1 regular channels configuration */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);

    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);

    /* Enable ADC1 EOC interrupt */
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

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

    /* Start ADC1 Software Conversion */
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    while (1)
    {
    }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
static void RCC_Configuration(void)
{
    /* ADCCLK = PCLK2/20 */
    RCC_ADC1CLKConfig(RCC_PCLK2_Div20);

    /* Enable peripheral clocks ------------------------------------------------*/

    /* Enable ADC1 and GPIOC clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure PC.00 (ADC Channel10) as analog inputs */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
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

