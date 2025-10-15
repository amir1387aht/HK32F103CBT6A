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
static void USART_Config(void);
static void RTC_Configuration(void);
static void Delay(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configures LED GPIO */
    HK_EVAL_LEDInit(LED2);

    /* Turns selected LED Off */
    HK_EVAL_LEDOff(LED2);

    /* Configures Button GPIO */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    /* Configures USART */
    USART_Config();

    /* Configures the RTC */
    RTC_Configuration();

    if (PWR_GetFlagStatus(PWR_FLAG_SB) == SET)
    {
        PWR_ClearFlag(PWR_FLAG_SB);
        printf("Standby Reset Wakeup \r\n");

        while (1)
        {
            Delay(0xfff);
            HK_EVAL_LEDToggle(LED2);
        }
    }
    else
    {
        printf("Non-standby reset wake-up \r\n");
        while (1)
        {
            Delay(0xff);
            HK_EVAL_LEDToggle(LED2);

            if (HK_EVAL_PBGetState(BUTTON_KEY1) == RESET)
            {
                printf("Enter standby mode\n");
                BKP_WakeupTimerConfig(ENABLE);
                HK_EVAL_LEDOff(LED2);
                PWR_ClearFlag(PWR_FLAG_WU);
                PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFI);
            }
        }
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
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
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

    /* Enable LSE */
    RCC_LSEConfig(RCC_LSE_ON);

    /* Wait till LSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {
    }

    /* Select LSE as RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

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
    RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* auto wakeup timer config */
    BKP_SetRTCWakeupTimerClock(BKP_WUCKSEL_TRCLK);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Sets the RTC wakeup timer reload value */
    RTC_SetWakeupTimer(5);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* wakeup timer output in standby mode */
    BKP_WakeupTimerOutSel(DISABLE, ENABLE, DISABLE, DISABLE);

    /* Disable wakeup timer */
    BKP_WakeupTimerConfig(DISABLE);
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void Delay(__IO uint32_t nCount)
{
    for(uint32_t i = 0; i < 0xfff; i++)
    {
        for (uint32_t j = nCount; j != 0; j--)
        {
            __NOP();
        }
    }
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


