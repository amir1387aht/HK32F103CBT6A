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
#define RTCClockOutput_Enable  /* RTC Clock/64 is output on tamper pin(PC.13) */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t TimeDisplay = 0;

/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
static void NVIC_Configuration(void);
static void RTC_Configuration(void);
static void Time_Adjust(void);
static void Time_Show(void);

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

    /* Configures USART */
    USART_Config();

    /* Configures NVIC */
    NVIC_Configuration();
  
    /* Enable BKP clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
  
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
        /* Backup data register value is not correct or not yet programmed (when
           the first time the program is executed) */
        printf("RTC not yet configured....\r\n");

        /* RTC Configuration */
        RTC_Configuration();
        printf("RTC configured....\r\n");

        /* Adjust time by values entered by the user on the hyperterminal */
        Time_Adjust();
        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    }
    else
    {
        /* Check if the Power On Reset flag is set */
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
        {
            printf("Power On Reset occurred....\r\n");
        }

        /* Check if the Pin Reset flag is set */
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
        {
            printf("External Reset occurred....\r\n");
        }

        printf("No need to configure RTC....\r\n");

        /* Wait for RTC registers synchronization */
        RTC_WaitForSynchro();

        /* Enable the RTC Second */
        RTC_ITConfig(RTC_IT_SEC, ENABLE);

        /* Wait until last write operation on RTC registers has finished */
        RTC_WaitForLastTask();
    }

#ifdef RTCClockOutput_Enable
    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);
    /* Disable the Tamper Pin */
    BKP_TamperPinCmd(DISABLE); /* To output RTCCLK/64 on Tamper pin, the tamper
                                 functionality must be disabled */
    /* Enable RTC Clock Output on Tamper Pin */
    BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
#endif
    /* Clear reset flags */
    RCC_ClearFlag();
    /* Display time in infinite loop */
    Time_Show();

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
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
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
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
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
}

/**
  * @brief  Gets numeric values from the hyperterminal.
  * @param  None
  * @retval None
  */
static uint8_t USART_Scanf(uint32_t value)
{
    uint32_t index = 0;
    uint32_t tmp[2] = {0, 0};

    while (index < 2)
    {
        /* Loop until RXNE = 1 */
        while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_RXNE) == RESET)
        {
        }

        tmp[index++] = (USART_ReceiveData(EVAL_COM1));

        if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
        {
            printf("Please enter valid number between 0 and 9\r\n");
            index--;
        }
    }

    /* Calculate the Corresponding value */
    index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10);

    /* Checks */
    if (index > value)
    {
        printf("Please enter valid number between 0 and %d\r\n", value);
        return 0xFF;
    }

    return index;
}

/**
  * @brief  Returns the time entered by user, using Hyperterminal.
  * @param  None
  * @retval Current time RTC counter value
  */
static uint32_t Time_Regulate(void)
{
    uint32_t Tmp_HH = 0xFF, Tmp_MM = 0xFF, Tmp_SS = 0xFF;
    printf("==============Time Settings=====================================\r\n");
    printf("Please Set Hours\r\n");

    while (Tmp_HH == 0xFF)
    {
        Tmp_HH = USART_Scanf(23);
    }

    printf(":  %d\r\n", Tmp_HH);
    printf("Please Set Minutes\r\n");

    while (Tmp_MM == 0xFF)
    {
        Tmp_MM = USART_Scanf(59);
    }

    printf(":  %d\r\n", Tmp_MM);
    printf("Please Set Seconds\r\n");

    while (Tmp_SS == 0xFF)
    {
        Tmp_SS = USART_Scanf(59);
    }

    printf(":  %d\r\n", Tmp_SS);

    /* Return the value to store in RTC counter register */
    return ((Tmp_HH * 3600 + Tmp_MM * 60 + Tmp_SS));
}

/**
  * @brief  Adjusts time.
  * @param  None
  * @retval None
  */
static void Time_Adjust(void)
{
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Change the current time */
    RTC_SetCounter(Time_Regulate());

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}

/**
  * @brief  Displays the current time.
  * @param  TimeVar: RTC counter value.
  * @retval None
  */
static void Time_Display(uint32_t TimeVar)
{
    uint32_t THH = 0, TMM = 0, TSS = 0;

    /* Reset RTC Counter when Time is 23:59:59 */
    if (RTC_GetCounter() == 0x0001517F)
    {
        RTC_SetCounter(0x0);

        /* Wait until last write operation on RTC registers has finished */
        RTC_WaitForLastTask();
    }

    /* Compute  hours */
    THH = TimeVar / 3600;

    /* Compute minutes */
    TMM = (TimeVar % 3600) / 60;

    /* Compute seconds */
    TSS = (TimeVar % 3600) % 60;
    printf("Time: %0.2d:%0.2d:%0.2d\r\n", THH, TMM, TSS);
}

/**
  * @brief  Shows the current time (HH:MM:SS) on the Hyperterminal.
  * @param  None
  * @retval None
  */
static void Time_Show(void)
{
    printf("\n\r");

    /* Infinite loop */
    while (1)
    {
        /* If 1s has been elapsed */
        if (TimeDisplay == 1)
        {
            /* Display current time */
            Time_Display(RTC_GetCounter());
            TimeDisplay = 0;
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


