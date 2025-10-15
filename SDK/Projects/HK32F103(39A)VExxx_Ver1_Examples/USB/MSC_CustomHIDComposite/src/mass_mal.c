/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  mass_mal.c
* @brief:     Medium Access Layer interface.
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "mass_mal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Mass_Memory_Size[2];
uint32_t Mass_Block_Size[2];
uint32_t Mass_Block_Count[2];
__IO uint32_t Status = 0;

SD_CardInfo mSDCardInfo;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the Media on the HK32
  * @retval None
  */
uint16_t MAL_Init(uint8_t lun)
{
    uint16_t status = MAL_OK;

    switch (lun)
    {
        case 0:
            Status = SD_Init();
            break;

        default:
            return MAL_FAIL;
    }

    return status;
}
/**
  * @brief  Write sectors
  * @retval None
  */
uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length)
{

    switch (lun)
    {
        case 0:
            //Status = SD_WriteMultiBlocks((uint8_t*)Writebuff, Memory_Offset, Transfer_Length,1);
            Status =    SD_WriteBlock((uint8_t*)Writebuff, Memory_Offset, Transfer_Length);
            Status = SD_WaitWriteOperation();

            while (SD_GetStatus() != SD_TRANSFER_OK)
            {

            }

            if ( Status != SD_OK )
            {
                return MAL_FAIL;
            }

            break;

        default:
            return MAL_FAIL;
    }

    return MAL_OK;
}

/**
  * @brief  Read sectors
  * @retval Buffer pointer
  */
uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
{

    switch (lun)
    {
        case 0:

            //SD_ReadMultiBlocks((uint8_t*)Readbuff, Memory_Offset, Transfer_Length, 1);
            SD_ReadBlock((uint8_t*)Readbuff, Memory_Offset, Transfer_Length);
            Status = SD_WaitReadOperation();

            while (SD_GetStatus() != SD_TRANSFER_OK)
            {
            }

            if ( Status != SD_OK )
            {
                return MAL_FAIL;
            }

            break;

        default:
            return MAL_FAIL;
    }

    return MAL_OK;
}

/**
  * @brief  Get status
  * @retval None
  */
uint16_t MAL_GetStatus(uint8_t lun)
{
    uint32_t DeviceSizeMul = 0, NumberOfBlocks = 0;

    if (lun == 0)
    {
        //if (SD_Init() == SD_OK)
        {
            SD_GetCardInfo(&mSDCardInfo);
            SD_SelectDeselect((uint32_t) (mSDCardInfo.RCA << 16));
            DeviceSizeMul = (mSDCardInfo.SD_csd.DeviceSizeMul + 2);

            if (mSDCardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)
            {
                Mass_Block_Count[0] = (mSDCardInfo.SD_csd.DeviceSize + 1) * 1024;
            }
            else
            {
                NumberOfBlocks  = ((1 << (mSDCardInfo.SD_csd.RdBlockLen)) / 512);
                Mass_Block_Count[0] = ((mSDCardInfo.SD_csd.DeviceSize + 1) * (1 << DeviceSizeMul) << (NumberOfBlocks / 2));
            }

            Mass_Block_Size[0]  = 512;

            Status = SD_SelectDeselect((uint32_t) (mSDCardInfo.RCA << 16));
            //Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);

            if ( Status != SD_OK )
            {
                return MAL_FAIL;
            }

            Mass_Memory_Size[0] = Mass_Block_Count[0] * Mass_Block_Size[0];
            return MAL_OK;
        }
    }

    return MAL_FAIL;
}

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/


