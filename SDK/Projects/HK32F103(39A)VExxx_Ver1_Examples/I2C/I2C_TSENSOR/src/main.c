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
#define TEMPERATURE_TOS     28
#define TEMPERATURE_THYS    27

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint8_t SMbusAlertOccurred = 0;
static int32_t TempValue = 0;

/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
static void NVIC_Configuration(void);
static void Delay(uint32_t Cnt);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configures USART */
    USART_Config();

    /* Configures NVIC */
    NVIC_Configuration();

    /* Initialize the Temperature Sensor */
    LM75_Init();

    if (LM75_GetStatus() == SUCCESS)
    {
        printf("LM75 correctly.\n");

        /* Configure the Temperature sensor device STLM75:
        - Thermostat mode Interrupt
        - Fault tolerance: 00
        */
        LM75_WriteConfReg(0x02);

        /* Configure the THYS and TOS in order to use the SMbus alert interrupt */
        LM75_WriteReg(LM75_REG_THYS, TEMPERATURE_THYS << 8);
        LM75_WriteReg(LM75_REG_TOS, TEMPERATURE_TOS << 8);
        I2C_ClearITPendingBit(LM75_I2C, I2C_IT_SMBALERT);
        SMbusAlertOccurred = 0;

        /* Infinite Loop */
        while (1)
        {
            /* Get double of Temperature value */
            TempValue = LM75_ReadTemp();

            if ((TempValue & 0x01) == 0x01)
            {
                printf(" = %d.5¡æ\n", (TempValue >> 1));
            }
            else
            {
                printf(" = %d¡æ\n", (TempValue >> 1));
            }

            Delay(0xfff);

            if (SMbusAlertOccurred == 1)
            {
                printf("Warning: Temp exceed\n");
            }

            if (SMbusAlertOccurred == 2)
            {
                SMbusAlertOccurred = 0;
            }
        }
    }
    else
    {
        printf("LM75 not correctly.\n");
    }

    while (1)
    {
    }
}


/**
  * @brief  Configures NVIC.
  * @param  None
  * @retval None
  */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = I2C2_ER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
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

static void Delay(uint32_t Cnt)
{
    for (uint32_t i = 0; i < 0xfff; i++)
    {
        for (uint32_t j = Cnt; j > 0; j--)
        {
        }
    }
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


