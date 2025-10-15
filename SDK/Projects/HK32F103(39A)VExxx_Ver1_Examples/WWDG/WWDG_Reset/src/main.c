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

/* Private function prototypes -----------------------------------------------*/
static void Delay(__IO uint32_t nTime);
static void USART_Config(void);
static void EXTI_Key_Config(void);

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

    /* Check if the system has resumed from WWDG reset */
    if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) != RESET)
    {
        /* WWDGRST flag set */
        printf(" Reset \r\n");

        /* Clear reset flags */
        RCC_ClearFlag();
    }

    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while (1)
        {
        }
    }

    /* WWDG configuration */
    /* Enable WWDG clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
    /* WWDG clock counter = (PCLK1(36MHz)/4096)/8 = 1099 Hz (~910 us)  */
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    /* Set Window value to 80; WWDG counter should be refreshed only when the counter
      is below 80 (and greater than 64) otherwise a reset will be generated */
    WWDG_SetWindowValue(80);
    /*
      Enable WWDG and set counter value to 127, WWDG timeout = ~910 us * 64 = 58.25 ms
      In this case the refresh window is: ~910 us * (127-80) = 42.77 ms < refresh window < ~910 us * 64 = 58.25ms
    */
    WWDG_Enable(127);

    while (1)
    {
        printf(" Code run normal\r\n");

        /* Insert 44 ms delay */
        Delay(44);

        /* Update WWDG counter */
        WWDG_SetCounter(127);
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

    /* e.g. write a character to the USART */
    USART_SendData(EVAL_COM1, (uint8_t) ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET)
    {
    }

    return ch;
}
/**
  * @brief  Configuration GPIO EXTI,and configuration priority
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


