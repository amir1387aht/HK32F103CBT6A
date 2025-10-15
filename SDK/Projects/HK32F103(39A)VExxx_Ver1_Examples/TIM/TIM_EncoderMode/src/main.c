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
#define Timer2   50000
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
/* Private function prototypes -----------------------------------------------*/
static void RCC_Configuration(void);
static void GPIO_Configuration(void);
static void TIM1_Config(void);
static void Delay_Timer(uint32_t Timer1);
static void USART_Config(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();
    TIM1_Config();
    USART_Config();
    while (1)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_3);
        Delay_Timer(Timer2);
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        Delay_Timer(Timer2);
        GPIO_ResetBits(GPIOA, GPIO_Pin_3);
        Delay_Timer(Timer2);
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
        Delay_Timer(Timer2);
        printf("TIM1_CNT=%d\r\n",TIM1->CNT);
    }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
static void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/

    /* Enable GPIOs and ADC1 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE | RCC_APB2Periph_TIM1 | RCC_APB2Periph_AFIO, ENABLE);
}
/**
  * @brief  Configures delay.
  * @param  None
  * @retval None
  */
static void Delay_Timer(uint32_t Timer1)
{
    for (; Timer1 > 0; Timer1--)
    {
        
    }
}
/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 

    /* Configure PE.09 (TIM1_CH1),PE.11 (TIM1_CH2) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);
    /*Simulate Encoder*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/**
  * @brief  Configure the TIM1.
  * @param  None
  * @retval None
  */
static void TIM1_Config(void)
{
    /* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 4095;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
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


