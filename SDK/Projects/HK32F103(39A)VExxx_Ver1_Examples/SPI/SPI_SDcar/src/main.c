/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f103xxxxa_eval_spi_sd.h"
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/

#define  BUFFERSIZE     512 

/* Private macro -------------------------------------------------------------*/  
/* Private variables ---------------------------------------------------------*/
uint8_t Buffer_Block_Tx[BUFFERSIZE], Buffer_Block_Rx[BUFFERSIZE];
TestStatus TransferStatus = FAILED;
uint16_t Status = 0;
/* Private function prototypes -----------------------------------------------*/
static void Fill_Buffer(uint8_t *pBuffer, uint16_t BufferLenght, uint8_t Offset);
static TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */  
int main(void)
{

    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDOff(LED2);

    /* Initializes the SD/SPI communication */
    Status = SD_Init();
	
    /* If SD is responding */
    if (Status == SD_RESPONSE_NO_ERROR)
    {
        /* Fill the buffer to send */
        Fill_Buffer(Buffer_Block_Tx, BUFFERSIZE, 0x0);

        /* Write block of 512 bytes on address 0 */
        Status = SD_WriteBlock(Buffer_Block_Tx, 0, BUFFERSIZE);

        /* Read block of 512 bytes from address 0 */
        Status = SD_ReadBlock(Buffer_Block_Rx, 0, BUFFERSIZE);

        /* Check the corectness of written dada */
        TransferStatus = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, BUFFERSIZE);

        if (TransferStatus == PASSED)
        {
            /* OK: Turn on LD1 */
            HK_EVAL_LEDOn(LED1);
        }
        else
        {
            /* Error: Turn on LD2 */
            HK_EVAL_LEDOn(LED2);
        }
    }
    else
    {
        /* Error: Turn on LD2 */
        HK_EVAL_LEDOn(LED2);
    }

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
static TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
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
  * @brief  Fill the gloal buffer.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  BufferLenght: length of the buffer to fill
  * @param  Offset: first value to fill on the Buffer
  * @retval None.
  */
static void Fill_Buffer(uint8_t *pBuffer, uint16_t BufferLenght, uint8_t Offset)
{
    uint16_t IndexTmp;

    /* Put in global buffer same values */
    for ( IndexTmp = 0; IndexTmp < BufferLenght; IndexTmp++ )
    {
        pBuffer[IndexTmp] = IndexTmp + Offset;
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


