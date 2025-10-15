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
#define BKP_DR_NUMBER              (11)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t BKPDataReg[BKP_DR_NUMBER] =
{
    BKP_DR0, BKP_DR1, BKP_DR2, BKP_DR3, BKP_DR4, BKP_DR5, BKP_DR6, BKP_DR7, BKP_DR8,
    BKP_DR9, BKP_DR10
};

/*
0: Tamper detection event not occurred.
1; Tamper detection event occurred, Backup registers are reset as expected.
2: Tamper detection event occurred, Backup registers are not reset.
*/
uint8_t BkpFlag = 0;

/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
static void NVIC_Configuration(void);
static void WriteToBackupReg(uint16_t FirstBackupData);
static uint8_t CheckBackupReg(uint16_t FirstBackupData);

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

    /* Enable PWR and BKP clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    /* Enable write access to Backup domain */
    PWR_BackupAccessCmd(ENABLE);

    /* Disable Tamper pin */
    BKP_TamperPinCmd(DISABLE);

    /* Disable Tamper interrupt */
    BKP_ITConfig(DISABLE);

    /* Tamper pin active on low level */
    BKP_TamperPinLevelConfig(BKP_TamperPinLevel_Low);

    /* Clear Tamper pin Event(TE) pending flag */
    BKP_ClearFlag();

    /* Enable Tamper interrupt */
    BKP_ITConfig(ENABLE);

    /* Enable Tamper pin */
    BKP_TamperPinCmd(ENABLE);

    /* Write data to Backup DRx registers */
    WriteToBackupReg(0xA53C);

    /* Check if the written data are correct */
    if (CheckBackupReg(0xA53C) == 0x00)
    {
        printf("the values in the BKP dataregisters are correct.\n");
    }
    else
    {
        printf("the values in the BKP data registers are not correct.\n");
    }

    while (1)
    {
        if(0 != BkpFlag)
        {
            if(1 == BkpFlag)
            {
                printf("Tamper detection event occurred, Backup registers are reset as expected.\n");
            }
            else
            {
                printf("Tamper detection event occurred, Backup registers are not reset.\n");
            }
            BkpFlag = 0;
        }
    }
}

/**
  * @brief  Configures NVIC and Vector Table base location.
  * @param  None
  * @retval None
  */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable TAMPER IRQChannel */
    NVIC_InitStructure.NVIC_IRQChannel = TAMPER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Writes data Backup DRx registers.
  * @param  FirstBackupData: data to be written to Backup data registers.
  * @retval None
  */
static void WriteToBackupReg(uint16_t FirstBackupData)
{
    uint32_t index = 0;

    for (index = 0; index < BKP_DR_NUMBER; index++)
    {
        BKP_WriteBackupRegister(BKPDataReg[index], FirstBackupData + (index * 0x5A));
    }
}

/**
  * @brief  Checks if the Backup DRx registers values are correct or not.
  * @param  FirstBackupData: data to be compared with Backup data registers.
  * @retval 0: All Backup DRx registers values are correct
  *         Value different from 0: Number of the first Backup register
  *         which value is not correct
  */
static uint8_t CheckBackupReg(uint16_t FirstBackupData)
{
    uint32_t index = 0;

    for (index = 0; index < BKP_DR_NUMBER; index++)
    {
        if (BKP_ReadBackupRegister(BKPDataReg[index]) != (FirstBackupData + (index * 0x5A)))
        {
            return (index + 1);
        }
    }

    return 0;
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
  * @brief  Checks if the Backup DRx registers are reset or not.
  * @param  None
  * @retval 0: All Backup DRx registers are reset
  *         Value different from 0: Number of the first Backup register
  *         not reset
  */
uint32_t IsBackupRegReset(void)
{
  uint32_t index = 0;

  for (index = 0; index < BKP_DR_NUMBER; index++)
  {
    if (BKP_ReadBackupRegister(BKPDataReg[index]) != 0x0000)
    {
      return (index + 1);
    }
  }

  return 0;  
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


