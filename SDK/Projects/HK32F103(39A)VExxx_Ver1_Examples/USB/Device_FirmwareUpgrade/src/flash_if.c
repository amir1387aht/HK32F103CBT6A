/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  flash_if.c
* @brief:     specific media access Layer for internal flash.
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "flash_if.h"
#include "dfu_mal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the Media on the HK32
  * @retval None
  */
uint16_t FLASH_If_Init(void)
{
    return MAL_OK;
}

/**
  * @brief  Erase sector
  * @retval None
  */
uint16_t FLASH_If_Erase(uint32_t SectorAddress)
{
    FLASH_ErasePage(SectorAddress);
    return MAL_OK;
}

/**
  * @brief  Write sectors
  * @retval None
  */
uint16_t FLASH_If_Write(uint32_t SectorAddress, uint32_t DataLength)
{
    uint32_t idx = 0;

    if  (DataLength & 0x3) /* Not an aligned data */
    {
        for (idx = DataLength; idx < ((DataLength & 0xFFFC) + 4); idx++)
        {
            MAL_Buffer[idx] = 0xFF;
        }
    }

    /* Data received are Word multiple */
    for (idx = 0; idx <  DataLength; idx = idx + 4)
    {
        FLASH_ProgramWord(SectorAddress, *(uint32_t *)(MAL_Buffer + idx));
        SectorAddress += 4;
    }

    return MAL_OK;
}

/**
  * @brief  Read sectors
  * @retval buffer address pointer
  */
uint8_t *FLASH_If_Read(uint32_t SectorAddress, uint32_t DataLength)
{
    return  (uint8_t*)(SectorAddress);
}

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/

