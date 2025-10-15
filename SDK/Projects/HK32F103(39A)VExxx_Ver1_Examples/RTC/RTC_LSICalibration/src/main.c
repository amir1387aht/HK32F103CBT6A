/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*                     1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_ICInitTypeDef  TIM_ICInitStructure;
RCC_ClocksTypeDef RCC_Clocks;
__IO uint32_t PeriodValue = 0,  LsiFreq = 0;
__IO uint32_t OperationComplete = 0;

/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
static void RTC_Configuration(void);
static void NVIC_Configuration(void);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configure Usart */
    USART_Config();
    
    printf("Start of execution\n");
  
    /* Configure Button */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    /* Configures LED */
    HK_EVAL_LEDInit(LED2);

    /* Turns selected LED Off */
    HK_EVAL_LEDOff(LED2);

    /* Configure RTC */
    RTC_Configuration();

    /* Wait until Key Push button is pressed */
    while (HK_EVAL_PBGetState(BUTTON_KEY1) != 0)
    {
    }

    /* Get the Frequency value */
    RCC_GetClocksFreq(&RCC_Clocks);

    /* Enable TIM5 APB1 clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    /* Connect internally the TM5_CH4 Input Capture to the LSI clock output */
    GPIO_ExtendPinRemapConfig(GPIO_E_Remap_TIM5CH4_LSI, ENABLE);

    /* TIM5 Time base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

    /* TIM5 Channel4 Input capture Mode configuration */
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);

    /* Reinitialize the index for the interrupt */
    OperationComplete = 0;

    /* Enable the TIM5 Input Capture counter */
    TIM_Cmd(TIM5, ENABLE);

    /* Reset all TIM5 flags */
    TIM5->SR = 0;

    /* Enable the TIM5 channel 4 */
    TIM_ITConfig(TIM5, TIM_IT_CC4, ENABLE);

    /* NVIC configuration */
    NVIC_Configuration();

    /* Wait the TIM5 measuring operation to be completed */
    while (OperationComplete != 2)
    {
    }

    /* Compute the actual frequency of the LSI. (TIM5_CLK = 2 * PCLK1)  */
    if (PeriodValue != 0)
    {
        LsiFreq = (uint32_t)((uint32_t)(RCC_Clocks.PCLK1_Frequency * 2) / (uint32_t)PeriodValue);
    }

    /* Adjust the RTC prescaler value */
    RTC_SetPrescaler(LsiFreq - 1);
    
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    printf("End of execution\n");
    
    while (1)
    {
    }
}

/**
  * @brief  Configure Usart
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
    - Receive enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
}

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* Enable the RTC Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the TIM5 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Configures the RTC.
  * @param  None
  * @retval None
  */
static void RTC_Configuration(void)
{
    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);

    /* Reset Backup Domain */
    BKP_DeInit();

    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);

    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

    /* Enable RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Set RTC prescaler: set RTC period to 1sec */
    RTC_SetPrescaler(40000);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* To output second signal on Tamper pin, the tamper functionality
         must be disabled (by default this functionality is disabled) */
    BKP_TamperPinCmd(DISABLE);

    /* Enable the RTC Second Output on Tamper Pin */
    BKP_RTCOutputConfig(BKP_RTCOutputSource_Second);
}

/**
  * @brief  Increments OperationComplete variable and return its value
  *         before increment operation.
  * @param  None
  * @retval OperationComplete value before increment
  */
uint32_t IncrementVar_OperationComplete(void)
{
    OperationComplete++;
    return (uint32_t)(OperationComplete - 1);
}

/**
  * @brief  Returns OperationComplete value.
  * @param  None
  * @retval OperationComplete value
  */
uint32_t GetVar_OperationComplete(void)
{
    return (uint32_t)OperationComplete;
}

/**
  * @brief  Sets the PeriodValue variable with input parameter.
  * @param  Value: Value of PeriodValue to be set.
  * @retval None
  */
void SetVar_PeriodValue(uint32_t Value)
{
    PeriodValue = (uint32_t)(Value);
}

/**
  * @brief  printf function
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /*  Printf   */
    USART_SendData(USART1, (unsigned char) ch);

    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
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
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */


