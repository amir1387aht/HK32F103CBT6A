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
#define TIM1_DMAR_ADDRESS ((uint32_t)0x40012C4C)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef         GPIO_InitStructure;
DMA_InitTypeDef          DMA_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef        TIM_OCInitStructure;
uint16_t SRC_Buffer[6] = {0x0FFF, 0x0000, 0x0555};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void USART_Config(void);
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    USART_Config();

    /* TIM1 and GPIOA clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA, ENABLE);

    /* DMA clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    /* GPIOA Configuration: Channel 1 as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* TIM1 DeInit */
    TIM_DeInit(TIM1);

    /* DMA1 Channel5 Config */
    DMA_DeInit(DMA1_Channel5);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)TIM1_DMAR_ADDRESS;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SRC_Buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 3;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    /*not DMA_Mode_Circular*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);

    /* Time base configuration */

    /* -----------------------------------------------------------------------
      TIM1 Configuration: generate 1 PWM signal using the DMA burst mode:
      The TIM1CLK frequency is set to SystemCoreClock (Hz), to get TIM1 counter
      clock at 24 MHz the Prescaler is computed as following:
       - Prescaler = (TIM1CLK / TIM1 counter clock) - 1.
      The TIM1 period is 5.8 KHz: TIM1 Frequency = TIM1 counter clock/(ARR + 1)
                                                 = 24 MHz / 4096 = 5.8KHz KHz
      TIM1 Channel1 duty cycle = (TIM1_CCR1/ TIM1_ARR)* 100 = 33.33%
    ----------------------------------------------------------------------- */
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t) (SystemCoreClock / 24000000) - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    /* TIM Configuration in PWM Mode */
    TIM_OCInitStructure.TIM_OCMode =  TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0xFFF;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    /* TIM1 DMAR Base register and DMA Burst Length Config */
    TIM_DMAConfig(TIM1, TIM_DMABase_ARR, TIM_DMABurstLength_3Transfers);

    /* TIM1 DMA Update enable */
    TIM_DMACmd(TIM1, TIM_DMA_Update, ENABLE);

    /* TIM1 enable */
    TIM_Cmd(TIM1, ENABLE);

    /* TIM1 PWM Outputs Enable */
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    /* DMA1 Channel5 enable */
    DMA_Cmd(DMA1_Channel5, ENABLE);

    /* Wait until DMA1 Channel5 end of Transfer */
    while (!DMA_GetFlagStatus(DMA1_FLAG_TC5))
    {
    }
    
    printf("TIM1_ARR=0x%X\r\n",TIM1->ARR);
    printf("TIM1_RCR=0x%X\r\n",TIM1->RCR);
    printf("TIM1_CCR1=0x%X\r\n",TIM1->CCR1);
    /* Infinite loop */
    while (1)
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


