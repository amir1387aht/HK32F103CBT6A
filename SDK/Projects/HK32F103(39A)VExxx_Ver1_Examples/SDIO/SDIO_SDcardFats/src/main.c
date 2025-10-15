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
#include "ff.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup SDIO_SDCardFats
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FATFS fs;
FIL fnew;
FRESULT res_sd;
/* Number of successful read/write files */
UINT fnum;
/* Read buffer */
BYTE ReadBuffer[1024] = {0};
/* Write buffer*/
BYTE WriteBuffer[] = "Hello Friend! Welcome to use HK32F103xxxxA EVAL Board V1.00!\r\n";
/* Private function prototypes -----------------------------------------------*/
static void SetSysClockTo48M_PLL(void);
static void USART_Config(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  : SDIO Fats Demo
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
    printf("\r\n****** HK32F103xxxxA EVAL SD-Card Fats Demo! ******\r\n");
    /*------------------------------ SD Init ---------------------------------- */
    res_sd = f_mount(&fs, "0:", 1);

    /* If no file system exists, format it. Create a file system */
    if (res_sd == FR_NO_FILESYSTEM)
    {
        printf(">>The SD card does not have a file system yet, "
               "and will be formatted soon ...\r\n");

        /* format */
        res_sd = f_mkfs("0:", 0, 0);

        if (res_sd == FR_OK)
        {
            printf(">>SD Card Format Success!\r\n");

            /* After formatting, cancel the mounting */
            res_sd = f_mount(NULL, "0:", 1);

            /* Remount */
            res_sd = f_mount(&fs, "0:", 1);
        }
        else
        {
            printf(">>SD Card Format Failed!\r\n");

            while (1)
            {
            }
        }
    }
    else if (res_sd != FR_OK)
    {
        printf(">>File system mount the SD card Failed (%d)!\r\n", res_sd);

        while (1)
        {
        }
    }
    else
    {
        printf("System File Test \r\n");
    }

    /*----------------------- File system tests: Write tests -----------------------------*/
    /* Open the file and create it if it does not exist */
    printf("\r\nFats Write Test\r\n");
    res_sd = f_open(&fnew, "0:test.txt", FA_CREATE_ALWAYS | FA_WRITE );

    if ( res_sd == FR_OK )
    {
        printf("Open And Write Data\r\n");

        /* Writes the specified storage contents to a file */
        res_sd = f_write(&fnew, WriteBuffer, sizeof(WriteBuffer), &fnum);

        if (res_sd == FR_OK)
        {
            printf("Data Num:%d\r\n", fnum);
            printf("Data:\r\n%s", WriteBuffer);
        }
        else
        {
            printf("Write Failed:%d\n", res_sd);
        }

        /* Stop reading and writing, and close the file */
        f_close(&fnew);
    }
    else
    {
        printf("Create Failed\r\n");
    }

    /*------------------- File system tests: Read tests ------------------------------------*/
    printf("\r\nFats Read Test\r\n");
    res_sd = f_open(&fnew, "0:test.txt", FA_OPEN_EXISTING | FA_READ);

    if (res_sd == FR_OK)
    {
        printf("Open And Read Data\r\n");
        res_sd = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum);

        if (res_sd == FR_OK)
        {
            printf("Read Num:%d\r\n", fnum);
            printf("Read Data:\r\n%s", ReadBuffer);
        }
        else
        {
            printf("Read Fail:(%d)\r\n", res_sd);
        }
    }
    else
    {
        printf("Open Fail\r\n");
    }

    /* The file system is no longer used , unmounted it */
    printf("\r\nExit File System\r\n");
    f_mount(NULL, "0:", 1);
    /* Operation complete, stop */

    /* Infinite loop */
    while (1)
    {
    }
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

