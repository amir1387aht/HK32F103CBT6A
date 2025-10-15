/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-31
*             1.Initial Version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa.h"
#include "hk32f103xxxxa_eval_sdio_sd.h"
#include "hk32f103xxxxa_eval.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup SDIO_SDCardAccess
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Block Size in Bytes */
#define BLOCK_SIZE            512
/* For Multi Blocks operation (Read/Write) */
#define NUMBER_OF_BLOCKS      32
#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)

#define SD_OPERATION_ERASE          0
#define SD_OPERATION_BLOCK          1
#define SD_OPERATION_MULTI_BLOCK    2
#define SD_OPERATION_END            3

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Buffer_Block_Tx[BLOCK_SIZE];
uint8_t Buffer_Block_Rx[BLOCK_SIZE];
uint8_t Buffer_MultiBlock_Tx[MULTI_BUFFER_SIZE];
uint8_t Buffer_MultiBlock_Rx[MULTI_BUFFER_SIZE];
volatile TestStatus EraseStatus = FAILED;
volatile TestStatus TransferStatus1 = FAILED;
volatile TestStatus TransferStatus2 = FAILED;
SD_Error Status = SD_OK;
__IO uint32_t SDCardOperation = SD_OPERATION_ERASE;

/* Private function prototypes -----------------------------------------------*/
static void SD_EraseTest(void);
static void SD_SingleBlockTest(void);
static void SD_MultiBlockTest(void);
static void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset);
static TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);
static TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength);
static void SetSysClockTo48M_PLL(void);
static void USART_Config(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  : SDIO Access Demo
  * @param  : none
  * @retval : none
  */
int main(void)
{
    /* At this stage the microcontroller clock setting is already configured,
    this is done through SystemInit() function which is called from startup
    file (startup_hk32f103xxxxa.s) before to branch to application main. Call function
    SetSysClockTo48M_PLL() to reconfigure the default system clock */
    SetSysClockTo48M_PLL();

    /* Debug USART Config */
    USART_Config();
    printf("\r\n****** HK32F103xxxxA EVAL SD-Card Access Demo! ******\r\n");

    /* SD Init */
    if ((Status = SD_Init()) != SD_OK)
    {
        printf("\r\nSD Init Error!\r\n");
    }
    else
    {
        printf("\r\nSD Init OK!\r\n");
    }

    while ((Status == SD_OK) && (SDCardOperation != SD_OPERATION_END))
    {
        switch (SDCardOperation)
        {
            /* SD Erase Test */
            case (SD_OPERATION_ERASE):
            {
                SD_EraseTest();
                SDCardOperation = SD_OPERATION_BLOCK;
                break;
            }

            /* SD Single Block Test */
            case (SD_OPERATION_BLOCK):
            {
                SD_SingleBlockTest();
                SDCardOperation = SD_OPERATION_MULTI_BLOCK;
                break;
            }

            /* SD Multi Blocks Test */
            case (SD_OPERATION_MULTI_BLOCK):
            {
                SD_MultiBlockTest();
                SDCardOperation = SD_OPERATION_END;
                break;
            }
        }
    }

    /* Infinite loop */
    while (1)
    {
    }
}

/**
  * @brief  Tests the SD card erase operation.
  * @param  None
  * @retval None
  */
static void SD_EraseTest(void)
{
    /* Block Erase */
    if (Status == SD_OK)
    {
        /* Erase NumberOfBlocks Blocks of WRITE_BL_LEN(512 Bytes) */
        Status = SD_Erase(0x00, (BLOCK_SIZE * NUMBER_OF_BLOCKS));
    }

    if (Status == SD_OK)
    {
        Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

        /* Check if the Transfer is finished */
        Status = SD_WaitReadOperation();

        /* Wait until end of DMA transfer */
        while (SD_GetStatus() != SD_TRANSFER_OK)
        {
        }
    }

    /* Check the correctness of erased blocks */
    if (Status == SD_OK)
    {
        EraseStatus = eBuffercmp(Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE);
    }

    if (EraseStatus == PASSED)
    {
        printf("\r\nSD Erase Done!\r\n");
    }
    else
    {
        printf("\r\nSD Erase Failed!\r\n");
    }
}

/**
  * @brief  Tests the SD card Single Blocks operations.
  * @param  None
  * @retval None
  */
static void SD_SingleBlockTest(void)
{
    /* Block Read/Write */

    /* Fill the buffer to send */
    Fill_Buffer(Buffer_Block_Tx, BLOCK_SIZE, 0x320F);

    if (Status == SD_OK)
    {
        /* Write block of 512 bytes on address 0 */
        Status = SD_WriteBlock(Buffer_Block_Tx, 0x00, BLOCK_SIZE);

        /* Check if the Transfer is finished */
        Status = SD_WaitWriteOperation();

        while (SD_GetStatus() != SD_TRANSFER_OK)
        {
        }
    }

    if (Status == SD_OK)
    {
        /* Read block of 512 bytes from address 0 */
        Status = SD_ReadBlock(Buffer_Block_Rx, 0x00, BLOCK_SIZE);

        /* Check if the Transfer is finished */
        Status = SD_WaitReadOperation();

        while (SD_GetStatus() != SD_TRANSFER_OK)
        {
        }
    }

    /* Check the correctness of written data */
    if (Status == SD_OK)
    {
        TransferStatus1 = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, BLOCK_SIZE);
    }

    if (TransferStatus1 == PASSED)
    {
        printf("\r\nSD Single Block Test OK!\r\n");
    }
    else
    {
        printf("\r\nSD Single Block Test Failed!\r\n");
    }
}

/**
  * @brief  Tests the SD card Multiple Blocks operations.
  * @param  None
  * @retval None
  */
static void SD_MultiBlockTest(void)
{
    /* Multiple Block Read/Write */

    /* Fill the buffer to send */
    Fill_Buffer(Buffer_MultiBlock_Tx, MULTI_BUFFER_SIZE, 0x0);

    if (Status == SD_OK)
    {
        /* Write multiple block of many bytes on address 0 */
        Status = SD_WriteMultiBlocks(Buffer_MultiBlock_Tx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

        /* Check if the Transfer is finished */
        Status = SD_WaitWriteOperation();

        while (SD_GetStatus() != SD_TRANSFER_OK)
        {
        }
    }

    if (Status == SD_OK)
    {
        /* Read block of many bytes from address 0 */
        Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

        /* Check if the Transfer is finished */
        Status = SD_WaitReadOperation();

        while (SD_GetStatus() != SD_TRANSFER_OK)
        {
        }
    }

    /* Check the correctness of written data */
    if (Status == SD_OK)
    {
        TransferStatus2 = Buffercmp(Buffer_MultiBlock_Tx, Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE);
    }

    if (TransferStatus2 == PASSED)
    {
        printf("\r\nSD Muti Block Test OK!\r\n");
    }
    else
    {
        printf("\r\nSD Muti Block Test Failed!\r\n");
    }
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
static TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
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
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  BufferLength: size of the buffer to fill
  * @param  Offset: first value to fill on the Buffer
  * @retval None
  */
static void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset)
{
    uint16_t index = 0;

    /* Put in global buffer same values */
    for (index = 0; index < BufferLength; index++)
    {
        pBuffer[index] = index + Offset;
    }
}

/**
  * @brief  Checks if a buffer has all its values are equal to zero.
  * @param  pBuffer: buffer to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer values are zero
  *         FAILED: At least one value from pBuffer buffer is different from zero.
  */
static TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength)
{
    while (BufferLength--)
    {
        /* In some SD Cards the erased state is 0xFF, in others it's 0x00 */
        if ((*pBuffer != 0xFF) && (*pBuffer != 0x00))
        {
            return FAILED;
        }

        pBuffer++;
    }

    return PASSED;
}
/**
  * @brief  Sets System clock frequency to 48MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo48M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* Select HSI as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));

    /* Wait till HSI is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != 0x00000000)
    {
    }

    /* Disable PLL */
    RCC->CR &= (uint32_t)((uint32_t)~RCC_CR_PLLON);

    /* Wait till PLL not ready */
    while ((RCC->CR & RCC_CR_PLLRDY) != 0)
    {
    }

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */

    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 1 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_1;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x00000000;

        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)0x00000000;

        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)0x00000400;

        /*  PLL configuration: PLLCLK = HSE * 6 = 48 MHz */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(0x00010000 | 0x00100000);

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)0x00000002;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != 0x00000008)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up */
    }
}

/**
  * @brief  Configure the USART Device
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
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
}

/**
  * @brief  Redirect the c library function printf to the EVAL_COM1.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /* Send a byte of data to the EVAL_COM1 */
    USART_SendData(EVAL_COM1, (uint8_t) ch);

    /* Wait for transmit completed */
    while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TXE) == RESET);

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
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

