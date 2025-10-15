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
#define BKP_DR_NUMBER              (43)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t BKPDataReg[BKP_DR_NUMBER] =
{
    BKP_DR0, BKP_DR1, BKP_DR2, BKP_DR3, BKP_DR4, BKP_DR5, BKP_DR6, BKP_DR7, BKP_DR8,
    BKP_DR9, BKP_DR10, BKP_DR11, BKP_DR12, BKP_DR13, BKP_DR14, BKP_DR15, BKP_DR16,
    BKP_DR17, BKP_DR18, BKP_DR19, BKP_DR20, BKP_DR21, BKP_DR22, BKP_DR23, BKP_DR24,
    BKP_DR25, BKP_DR26, BKP_DR27, BKP_DR28, BKP_DR29, BKP_DR30, BKP_DR31, BKP_DR32,
    BKP_DR33, BKP_DR34, BKP_DR35, BKP_DR36, BKP_DR37, BKP_DR38, BKP_DR39, BKP_DR40,
    BKP_DR41, BKP_DR42
};

/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
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

    /* Enable PWR and BKP clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    /* Enable write access to Backup domain */
    PWR_BackupAccessCmd(ENABLE);

    /* Clear Tamper pin Event(TE) pending flag */
    BKP_ClearFlag();

    /* Wait until the power-on is stable */
    for (uint32_t i = 0; i < 0xffffff; i++)
    {
        __NOP();
    }

    printf("Start of execution\n");

    /* Check if the Power On Reset flag is set */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
        /* Clear reset flags */
        RCC_ClearFlag();
        printf("Power On Reset occurred.\n");

        /* Check if Backup data registers are programmed */
        if (CheckBackupReg(0x3210) == 0x00)
        {
            /* Backup data registers values are correct */
            printf("the values in the BKP data registers are correct.\n");
        }
        else
        {
            /* Backup data registers values are not correct or they are not yet
               programmed (when the first time the program is executed) */    
            printf("the values in the BKP data registers are not correct.\n");

             /* Write data to Backup data registers */
            WriteToBackupReg(0x3210);
        }
    }

    printf("End of execution\n");

    while (1)
    {
    }
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


