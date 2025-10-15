/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-26
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/*KEY1 GPIO*/
#define KEY1_INT_GPIO_PORT         GPIOA
#define KEY1_INT_GPIO_CLK          (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define KEY1_INT_GPIO_PIN          GPIO_Pin_0
#define KEY1_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOA
#define KEY1_INT_EXTI_PINSOURCE    GPIO_PinSource0
#define KEY1_INT_EXTI_LINE         EXTI_Line0
#define KEY1_INT_EXTI_IRQ          EXTI0_IRQn
#define KEY1_IRQHandler            EXTI0_IRQHandler

/* Private variables ---------------------------------------------------------*/
__IO uint32_t TimingDelay = 0;
__IO uint32_t LsiFreq = 40000;
extern __IO uint16_t CaptureNumber;

/* Private function prototypes -----------------------------------------------*/
static void Delay(__IO uint32_t nTime);
static void USART_Config(void);
static void EXTI_Key_Config(void);
static void TIM5_ConfigForLSI(void);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    USART_Config();
    EXTI_Key_Config();

    /* Check if the system has resumed from IWDG reset */
    if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
    {
        printf("Reset\r\n");

        /* Clear reset flags */
        RCC_ClearFlag();
    }

    /* Setup SysTick Timer for 1 msec interrupts */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while (1)
        {
        }
    }

    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);

    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {
    }
    /* TIM Configuration*/
    TIM5_ConfigForLSI();

    /* Wait until the TIM5 get 2 LSI edges */
    while (CaptureNumber != 2)
    {
    }

    /* Disable TIM5 CC4 Interrupt Request */
    TIM_ITConfig(TIM5, TIM_IT_CC4, DISABLE);
    /* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
       dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    /* IWDG counter clock: LSI/32 */
    IWDG_SetPrescaler(IWDG_Prescaler_32);
    /* Set counter reload value to obtain 250ms IWDG TimeOut.
       Counter Reload Value = 250ms/IWDG counter clock period
                            = 250ms / (LSI/32)
                            = 0.25s / (LsiFreq/32)
                            = LsiFreq/(32 * 4)
                            = LsiFreq/128
     */
    IWDG_SetReload(LsiFreq / 128);
    /* Reload IWDG counter */
    IWDG_ReloadCounter();
    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();

    while (1)
    {
        printf("Code run normal\r\n");

        /* Insert 240 ms delay */
        Delay(240);

        /* Reload IWDG counter */
        IWDG_ReloadCounter();
    }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
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
  * @brief  Configure the USART.
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
}
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */

    /* write a character to the USART */
    USART_SendData(EVAL_COM1,(uint8_t)ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET)
    {
    }
    return ch;
}
/**
  * @brief  Configuration GPIO EXTI,and configuration priority.
  * @param  None
  * @retval None
  */
static void EXTI_Key_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK, ENABLE);
    /*KEY1 configuration*/
    GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);

    /* Select EXTI sign source */
    GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE);
    EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Configuration NVIC priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/**
  * @brief  Configures TIM5 to measure the LSI oscillator frequency.
  * @param  None
  * @retval None
  */
static void TIM5_ConfigForLSI(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;

    /* Enable TIM5 clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    /* Enable the TIM5 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure TIM5 prescaler */
    TIM_PrescalerConfig(TIM5, 0, TIM_PSCReloadMode_Immediate);

    /* Connect internally the TM5_CH4 Input Capture to the LSI clock output */
    GPIO_ExtendPinRemapConfig(GPIO_E_Remap_TIM5CH4_LSI, ENABLE);

    /* TIM5 configuration: Input Capture mode
       The LSI oscillator is connected to TIM5 CH4
       The Rising edge is used as active edge,
       The TIM5 CCR4 is used to compute the frequency value  */
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV8;
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);

    /* TIM10 Counter Enable */
    TIM_Cmd(TIM5, ENABLE);

    /* Reset the flags */
    TIM5->SR = 0;

    /* Enable the CC4 Interrupt Request */
    TIM_ITConfig(TIM5, TIM_IT_CC4, ENABLE);
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


