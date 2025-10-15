/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     This file provides the DMA_FLASHRAMTransfer example.
* @author:    AE Team
* @version:   V1.0.0/2023-10-18
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f103xxxxa_conf.h"
#include "hk32f103xxxxa_eval.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BUFFER_SIZE         0x1000
#define NAND_MakerID        0xAD
#define NAND_DeviceID       0xF1

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BufferSize     32
#define DELAY_COUNT    0x1FFFFF

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
DMA_InitTypeDef  DMA_InitStructure;
__IO uint32_t CurrDataCounterBegin = 0;
__IO uint32_t CurrDataCounterEnd = 0x01; /* This variable should not be initialized to 0 */

TestStatus TransferStatus = FAILED;
const uint32_t SRC_Const_Buffer[BufferSize] =
{
    0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
    0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
    0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
    0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
    0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
    0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
    0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
    0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80
};
uint32_t DST_Buffer[BufferSize];

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
TestStatus Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);
static void Delay(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_hk32f103xxxxa.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_hk32f103xxxxa.c file
       */

    /* System Clocks Configuration */
    RCC_Configuration();

    /* NVIC configuration */
    NVIC_Configuration();

    /* Initialize Leds mounted on HK32F103xxxxA-EVAL board */
    HK_EVAL_LEDInit(LED1);

    /* DMA1 channel6 configuration */
    DMA_DeInit(DMA1_Channel6);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SRC_Const_Buffer;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)DST_Buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = BufferSize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
    DMA_Init(DMA1_Channel6, &DMA_InitStructure);

    /* Enable DMA1 Channel6 Transfer Complete interrupt */
    DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);

    /* Get Current Data Counter value before transfer begins */
    CurrDataCounterBegin = DMA_GetCurrDataCounter(DMA1_Channel6);

    /* Enable DMA1 Channel6 transfer */
    DMA_Cmd(DMA1_Channel6, ENABLE);

    /* Wait the end of transmission */
    while (CurrDataCounterEnd != 0)
    {
    }

    /* Check if the transmitted and received data are equal */
    TransferStatus = Buffercmp(SRC_Const_Buffer, DST_Buffer, BufferSize);

    /* TransferStatus = PASSED, if the transmitted and received data
       are the same */

    /* TransferStatus = FAILED, if the transmitted and received data
       are different */
    if (TransferStatus == PASSED)
    {
        /* OK */

        /* Toggle LED1 */

        /* Infinite loop */
        while (1)
        {
            HK_EVAL_LEDToggle(LED1);
            Delay(DELAY_COUNT);
        }
    }
    else
    {
        /* Fail */

        /* On LED1 */
        HK_EVAL_LEDOn(LED1);
    }

    while (1)
    {
    }
}


/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--)
    {
    }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/

    /* Enable DMA1 clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable DMA1 channel6 IRQ Channel */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer, pBuffer1: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer identical to pBuffer1
  *         FAILED: pBuffer differs from pBuffer1
  */
TestStatus Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer != *pBuffer1)
        {
            return FAILED;
        }

        pBuffer++;
        pBuffer1++;
    }

    return PASSED;
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
