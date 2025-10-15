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
/* Private function prototypes -----------------------------------------------*/
static void TIM_Config(void);
static void USART_Config(void);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configures LED */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDInit(LED3);
  
    /* Configures Button GPIO */
    HK_EVAL_PBInit(BUTTON_KEY2, BUTTON_MODE_GPIO);

    /* Configures EXTI */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_EXTI);

    /* Configures TIM */
    TIM_Config();

    /* Configures USART */
    USART_Config();

    while (1)
    {
        /* Wait until KEY button is pressed. */
        while (HK_EVAL_PBGetState(BUTTON_KEY2) == RESET)
        {
        }
        while (HK_EVAL_PBGetState(BUTTON_KEY2) != RESET)
        {
        }

        /* This instruction raises the execution priority to 0. This prevents all
           exceptions with configurable priority from activating, other than through
           the HardFault fault escalation mechanism. */
        __disable_irq();
        printf("Disable all interrupts\n");

        /* Wait until KEY button is pressed. */
        while (HK_EVAL_PBGetState(BUTTON_KEY2) == RESET)
        {
        }
        while (HK_EVAL_PBGetState(BUTTON_KEY2) != RESET)
        {
        }

        /* This instruction will allow all exceptions with configurable priority to
           be activated. */
        __enable_irq();
        printf("Enable all interrupts\n");
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
  * @brief  Configures the used Timers.
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;

    /* Enable TIM2, TIM3 and TIM4 clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 |
                           RCC_APB1Periph_TIM4, ENABLE);

    /* TIM2 configuration */
    TIM_TimeBaseStructure.TIM_Period = 0x4AF;
    TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock / 1200) - 1);
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_OCStructInit(&TIM_OCInitStructure);

    /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStructure.TIM_Pulse = 0x0;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    /* TIM3 configuration */
    TIM_TimeBaseStructure.TIM_Period = 0x95F;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    /* TIM4 configuration */
    TIM_TimeBaseStructure.TIM_Period = 0xE0F;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);

    /* Immediate load of TIM2,TIM3 and TIM4 Precaler values */
    TIM_PrescalerConfig(TIM2, ((SystemCoreClock / 1200) - 1), TIM_PSCReloadMode_Immediate);
    TIM_PrescalerConfig(TIM3, ((SystemCoreClock / 1200) - 1), TIM_PSCReloadMode_Immediate);
    TIM_PrescalerConfig(TIM4, ((SystemCoreClock / 1200) - 1), TIM_PSCReloadMode_Immediate);

    /* Clear TIM2, TIM3 and TIM4 update pending flags */
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);

    /* Configure two bits for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Enable the TIM2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the TIM3 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the TIM4 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable TIM2, TIM3 and TIM4 Update interrupts */
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

    /* TIM2, TIM3 and TIM4 enable counters */
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
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


