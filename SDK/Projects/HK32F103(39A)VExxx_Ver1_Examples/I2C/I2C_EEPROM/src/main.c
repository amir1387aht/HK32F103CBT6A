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
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define sEE_WRITE_ADDRESS1        0x00
#define sEE_READ_ADDRESS1         0x00
#define BUFFER_SIZE1             (countof(Tx1_Buffer)-1)
#define BUFFER_SIZE2             (countof(Tx2_Buffer)-1)
#define sEE_WRITE_ADDRESS2       (sEE_WRITE_ADDRESS1 + BUFFER_SIZE1)
#define sEE_READ_ADDRESS2        (sEE_READ_ADDRESS1 + BUFFER_SIZE1)

/* Private macro -------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
uint8_t Tx1_Buffer[] = "/* I2C Firmware Library EEPROM driver example, Tx1_Buffer.(HK24C02)*/";
uint8_t Tx2_Buffer[] = "/* I2C Firmware Library EEPROM driver example, Tx2_Buffer.(HK24C02)*/";
uint8_t Rx1_Buffer[BUFFER_SIZE1], Rx2_Buffer[BUFFER_SIZE2];

volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
volatile uint16_t NumDataRead = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
static void USART_Config(void);

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configures USART */
    USART_Config();

    /* Initialize the I2C EEPROM driver ----------------------------------------*/
    sEE_Init();

    /* First write in the memory followed by a read of the written data --------*/

    /* Write on I2C EEPROM from sEE_WRITE_ADDRESS1 */
    sEE_WriteBuffer(Tx1_Buffer, sEE_WRITE_ADDRESS1, BUFFER_SIZE1);

    /* Set the Number of data to be read */
    NumDataRead = BUFFER_SIZE1;

    /* Read from I2C EEPROM from sEE_READ_ADDRESS1 */
    sEE_ReadBuffer(Rx1_Buffer, sEE_READ_ADDRESS1, (uint16_t *)(&NumDataRead));

    /* Wait till DMA transfer is complete (Transfer complete interrupt handler
      resets the variable holding the number of data to be read) */
    while (NumDataRead > 0)
    {
        /* Starting from this point, if the requested number of data is higher than 1,
           then only the DMA is managing the data transfer. Meanwhile, CPU is free to
           perform other tasks:

          // Add your code here:
          //...
          //...

           For simplicity reasons, this example is just waiting till the end of the
           transfer. */
    }

    /* Check if the data written to the memory is read correctly */
    TransferStatus1 = Buffercmp(Tx1_Buffer, Rx1_Buffer, BUFFER_SIZE1);
    /* TransferStatus1 = PASSED, if the transmitted and received data
       to/from the EEPROM are the same */
    /* TransferStatus1 = FAILED, if the transmitted and received data
       to/from the EEPROM are different */
    
    if(TransferStatus1 == PASSED)
    {
        printf("Tx1_Buffer Write/Read Success \n");
    }
    else
    {
        printf("Tx1_Buffer Write/Read Failure \n");
        while(1)
        {
        }
    }
    
    /* Second write in the memory followed by a read of the written data -------*/
    /* Write on I2C EEPROM from sEE_WRITE_ADDRESS2 */
    sEE_WriteBuffer(Tx2_Buffer, sEE_WRITE_ADDRESS2, BUFFER_SIZE2);
    /* Set the Number of data to be read */
    NumDataRead = BUFFER_SIZE2;
    /* Read from I2C EEPROM from sEE_READ_ADDRESS2 */
    sEE_ReadBuffer(Rx2_Buffer, sEE_READ_ADDRESS2, (uint16_t *)(&NumDataRead));

    /* Wait till DMA transfer is complete (Transfer complete interrupt handler
      resets the variable holding the number of data to be read) */
    while (NumDataRead > 0)
    {
        /* Starting from this point, if the requested number of data is higher than 1,
           then only the DMA is managing the data transfer. Meanwhile, CPU is free to
           perform other tasks:

          // Add your code here:
          //...
          //...

           For simplicity reasons, this example is just waiting till the end of the
           transfer. */
    }

    /* Check if the data written to the memory is read correctly */
    TransferStatus2 = Buffercmp(Tx2_Buffer, Rx2_Buffer, BUFFER_SIZE2);
    /* TransferStatus2 = PASSED, if the transmitted and received data
       to/from the EEPROM are the same */
    /* TransferStatus2 = FAILED, if the transmitted and received data
       to/from the EEPROM are different */
    
    if(TransferStatus2 == PASSED)
    {
        printf("Tx2_Buffer Write/Read Success \n");
    }
    else
    {
        printf("Tx2_Buffer Write/Read Failure \n");
        while(1)
        {
        }
    }
    
    /* Free all used resources */
    sEE_DeInit();

    while (1)
    {
    }
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
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



