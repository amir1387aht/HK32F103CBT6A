/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-11-08
*                     1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup _template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer[] = "USART Interrupt Example: Communication between two USART using Interrupt";
uint8_t RxBuffer [RXBUFFERSIZE];

__IO ButtonMode_TypeDef buttonmode  = BUTTON_MODE_GPIO;
__IO uint8_t RxIndex = 0x00;
__IO uint8_t TxIndex = 0x00;

/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
static void SysTickConfig(void);
static void CRC_Config(void);
static void GPIO_Config(void);
void Delay(void);
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* LED configuration */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDInit(LED3); 

    /* turn off all leds */
    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDOff(LED2);
    HK_EVAL_LEDOff(LED3);

    /* USART configuration */
    USART_Config();

    /* SysTick configuration */
    SysTickConfig();

    /* GPIO configuration */
    GPIO_Config();

    /* Configure the CRC peripheral to use the polynomial x8 + x7 + x6 + x4 + x2 + 1 */
    CRC_Config();  
    
#ifdef MODE_TRANSMITTER

    /* ------------------ USART in mode Tramitter ------------------------------*/

    /* Configure the external interrupt button */
    HK_EVAL_PBInit(BUTTON_KEY3, BUTTON_MODE_EXTI);

    /* Forever loop */
    while (1)
    {
        /*Wait "JOY_SEL" to start data transfer */
        if ((buttonmode != BUTTON_MODE_GPIO))
        {
            /* Enable the USARTx transmit data register empty interrupt */
            USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

            /* Set PressedButton to default value */
            buttonmode = BUTTON_MODE_GPIO;
        }
    }

#else
    /* ------------------ USART in mode Receiver -------------------------------*/
    /* Enable the USARTx receive data register not empty interrupt */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /* Infinite loop */
    while (1)
    {
    }

#endif /* MODE_TRANSMITTER */
}

/**
  * @brief  CRC Configure
  * @param  None
  * @retval None
  */
static void CRC_Config(void)
{
    /* Enable CRC AHB clock interface */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

    /* DeInit CRC peripheral */
    CRC_DeInit();

    /* Set the initial value of the CRC_DR register to 0*/
    CRC_CalcCRC(0xFFFFFFFF);
}

/**
  * @brief  Configures the USART Peripheral.
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* USARTx configuration ----------------------------------------------------*/

    /* USARTx configured as follow:
    - BaudRate = 230400 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 230400;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);

    /* NVIC configuration: Enable the USARTx Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Configures GPIO.
  * @param  None
  * @retval None
  */
static void GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* GPIOA clocks enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    /* Configure PA4 pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PA5 pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/**
  * @brief  Configure a SysTick Base time to 10 ms.
  * @param  None
  * @retval None
  */
static void SysTickConfig(void)
{
    /* Setup SysTick Timer for 10ms interrupts  */
    if (SysTick_Config(SystemCoreClock / 100))
    {
        /* Capture error */
        while (1)
        {        
        }
    }

    /* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x0);
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

/**
  * @}
  */

/**
  * @}
  */
