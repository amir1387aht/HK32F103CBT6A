/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-11-14
*                     1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup FLASH_EraseProgram
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define FLASH_PAGE_SIZE    ((uint16_t)0x800)
#define BANK_WRITE_START_ADDR  ((uint32_t)0x08008000)
#define BANK_WRITE_END_ADDR    ((uint32_t)0x0800C000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t EraseCounter = 0x00, Address = 0x00;
uint32_t Data = 0x3210ABCD;
uint32_t NbrOfPage = 0x00;
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
volatile TestStatus MemoryProgramStatus = PASSED;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Porgram FLASH **********************************************************/

    /* Unlock the Flash Program Erase controller */
    FLASH_Unlock();

    /* Define the number of page to be erased */
    NbrOfPage = (BANK_WRITE_END_ADDR - BANK_WRITE_START_ADDR) / FLASH_PAGE_SIZE;

    /* Clear All pending flags */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

    /* Erase the FLASH pages */
    for (EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
    {
        FLASHStatus = FLASH_ErasePage(BANK_WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
    }

    /* Program Flash */
    Address = BANK_WRITE_START_ADDR;

    while ((Address < BANK_WRITE_END_ADDR) && (FLASHStatus == FLASH_COMPLETE))
    {
        FLASHStatus = FLASH_ProgramWord(Address, Data);
        Address = Address + 4;
    }

    FLASH_Lock();

    /* Check the correctness of written data */
    Address = BANK_WRITE_START_ADDR;

    while ((Address < BANK_WRITE_END_ADDR) && (MemoryProgramStatus != FAILED))
    {
        if ((*(__IO uint32_t*) Address) != Data)
        {
            MemoryProgramStatus = FAILED;
        }

        Address += 4;
    }

    while (1)
    {
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
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
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

