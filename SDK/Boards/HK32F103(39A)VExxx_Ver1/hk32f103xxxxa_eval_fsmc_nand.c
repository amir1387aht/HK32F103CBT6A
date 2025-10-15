/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval_fsmc_nand.c
* @brief:     This file provides a set of functions needed to drive the
*             H27U1G8F2BTR-BC memory mounted on HK32F103xxxxA-EVAL board.
* @author:    AE Team
* @version:   V1.0.0/2023-11-14
*             1.Initial version
* @log:
*******************************************************************************/  

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_eval_fsmc_nand.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup HK32_EVAL
  * @{
  */

/** @addtogroup HK32F103xxxxA_EVAL
  * @{
  */

/** @addtogroup HK32F103xxxxA_EVAL_FSMC_NAND
  * @brief      This file provides a set of functions needed to drive the
  *             H27U1G8F2BTR-BC memory mounted on HK32F103xxxxA-EVAL board.
  * @{
  */

/** @defgroup HK32F103xxxxA_EVAL_FSMC_NAND_Private_Types
  * @{
  */
/**
  * @}
  */


/** @defgroup HK32F103xxxxA_EVAL_FSMC_NAND_Private_Defines
  * @{
  */
/**
  * @brief  FSMC Bank 2
  */
#define FSMC_Bank_NAND     FSMC_Bank2_NAND
#define Bank_NAND_ADDR     Bank2_NAND_ADDR
#define Bank2_NAND_ADDR    ((uint32_t)0x70000000)
/**
  * @}
  */

/** @defgroup HK32F103xxxxA_EVAL_FSMC_NAND_Private_Macros
  * @{
  */
#define ROW_ADDRESS (Address.Page + (Address.Block + (Address.Zone * NAND_ZONE_SIZE)) * NAND_BLOCK_SIZE)
/**
  * @}
  */


/** @defgroup HK32F103xxxxA_EVAL_FSMC_NAND_Private_Variables
  * @{
  */
/**
  * @}
  */


/** @defgroup HK32F103xxxxA_EVAL_FSMC_NAND_Private_Function_Prototypes
  * @{
  */
/**
  * @}
  */


/** @defgroup HK32F103xxxxA_EVAL_FSMC_NAND_Private_Functions
  * @{
  */

/**
  * @brief  Configures the FSMC and GPIOs to interface with the NAND memory.
  *         This function must be called before any write/read operation on the
  *         NAND.
  * @param  None
  * @retval None
  */
void NAND_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    FSMC_NANDInitTypeDef FSMC_NANDInitStructure;
    FSMC_NAND_PCCARDTimingInitTypeDef  p;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    /* 使能FSMC对应相应管脚时钟*/
    RCC_APB2PeriphClockCmd (NAND_CS_CLK | NAND_WR_CLK | NAND_RD_CLK | NAND_NWAIT_CLK | NAND_INT2_CLK |
                            NAND_D0_CLK | NAND_D1_CLK |  NAND_D2_CLK |
                            NAND_D3_CLK | NAND_D4_CLK | NAND_D5_CLK |
                            NAND_D6_CLK | NAND_D7_CLK |
                            NAND_A16_CLK | NAND_A17_CLK, ENABLE );
    /* 配置FSMC相对应的数据线,FSMC-D0~D15 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = NAND_D0_PIN;
    GPIO_Init ( NAND_D0_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NAND_D1_PIN;
    GPIO_Init ( NAND_D1_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NAND_D2_PIN;
    GPIO_Init ( NAND_D2_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NAND_D3_PIN;
    GPIO_Init ( NAND_D3_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NAND_D4_PIN;
    GPIO_Init ( NAND_D4_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NAND_D5_PIN;
    GPIO_Init ( NAND_D5_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NAND_D6_PIN;
    GPIO_Init ( NAND_D6_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NAND_D7_PIN;
    GPIO_Init ( NAND_D7_PORT, & GPIO_InitStructure );
    /* A */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = NAND_A16_PIN;
    GPIO_Init ( NAND_A16_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NAND_A17_PIN;
    GPIO_Init ( NAND_A17_PORT, & GPIO_InitStructure );
    /* 配置FSMC相对应的控制线
    * FSMC_NOE  :LCD-RD
    * FSMC_NWE  :LCD-WR
    * FSMC_NCE2 :LCD-CS
    * FSMC_NWAIT/INT2：需要接上拉电阻
    */
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = NAND_RD_PIN;
    GPIO_Init (NAND_RD_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NAND_WR_PIN;
    GPIO_Init (NAND_WR_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NAND_CS_PIN;
    GPIO_Init ( NAND_CS_PORT, & GPIO_InitStructure );
#if(NAND_USE_INT2_ENABLE==1)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = NAND_INT2_PIN;
    GPIO_Init (NAND_INT2_PORT, &GPIO_InitStructure );
#else
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = NAND_NWAIT_PIN;
    GPIO_Init (NAND_NWAIT_PORT, &GPIO_InitStructure );
#endif
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_Init ( GPIOE, & GPIO_InitStructure );
    /*-- FSMC Configuration ------------------------------------------------------*/
    p.FSMC_SetupTime = 0x1;
    p.FSMC_WaitSetupTime = 0x3;
    p.FSMC_HoldSetupTime = 0x2;
    p.FSMC_HiZSetupTime = 0x1;
    FSMC_NANDInitStructure.FSMC_Bank = FSMC_Bank2_NAND;
    FSMC_NANDInitStructure.FSMC_Waitfeature = FSMC_Waitfeature_Enable;
    FSMC_NANDInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
    FSMC_NANDInitStructure.FSMC_ECC = FSMC_ECC_Enable;
    FSMC_NANDInitStructure.FSMC_ECCPageSize = FSMC_ECCPageSize_2048Bytes;
    FSMC_NANDInitStructure.FSMC_TCLRSetupTime = 0x00;
    FSMC_NANDInitStructure.FSMC_TARSetupTime = 0x00;
    FSMC_NANDInitStructure.FSMC_CommonSpaceTimingStruct = &p;
    FSMC_NANDInitStructure.FSMC_AttributeSpaceTimingStruct = &p;
    FSMC_NANDInit(&FSMC_NANDInitStructure);
    /*!< FSMC NAND Bank Cmd Test */
    FSMC_NANDCmd(FSMC_Bank2_NAND, ENABLE);
}

/**
  * @brief  Reads NAND memory's ID.
  * @param  NAND_ID: pointer to a NAND_IDTypeDef structure which will hold
  *         the Manufacturer and Device ID.
  * @retval None
  */
void NAND_ReadID(NAND_IDTypeDef* NAND_ID)
{
    uint32_t data = 0;
    /*!< Send Command to the command area */
    *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = 0x90;
    *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = 0x00;
    /*!< Sequence to read ID from NAND flash */
    data = *(__IO uint32_t *)(Bank_NAND_ADDR | DATA_AREA);
    NAND_ID->Maker_ID   = ADDR_1st_CYCLE (data);
    NAND_ID->Device_ID  = ADDR_2nd_CYCLE (data);
    NAND_ID->Third_ID   = ADDR_3rd_CYCLE (data);
    NAND_ID->Fourth_ID  = ADDR_4th_CYCLE (data);
}

/**
  * @brief  This routine is for writing one or several 512 Bytes Page size.
  * @param  pBuffer: pointer on the Buffer containing data to be written
  * @param  Address: First page address
  * @param  NumPageToWrite: Number of page to write
  * @retval New status of the NAND operation. This parameter can be:
  *              - NAND_TIMEOUT_ERROR: when the previous operation generate
  *                a Timeout error
  *              - NAND_READY: when memory is ready for the next operation
  *                And the new status of the increment address operation. It can be:
  *              - NAND_VALID_ADDRESS: When the new address is valid address
  *              - NAND_INVALID_ADDRESS: When the new address is invalid address
  */
uint32_t NAND_WriteSmallPage(uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumPageToWrite)
{
    uint32_t index = 0x00, numpagewritten = 0x00, addressstatus = NAND_VALID_ADDRESS;
    uint32_t status = NAND_READY, size = 0x00;

    while ((NumPageToWrite != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
    {
        /*!< Page write command and address */
        *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_A;
        *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_WRITE0;
        *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = 0x00;
        *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
        *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
        *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
        /*!< Calculate the size */
        size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpagewritten);

        /*!< Write data */
        for (; index < size; index++)
        {
            *(__IO uint8_t *)(Bank_NAND_ADDR | DATA_AREA) = pBuffer[index];
        }

        *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_WRITE_TRUE1;
        /*!< Check status for successful operation */
        status = NAND_GetStatus();

        if (status == NAND_READY)
        {
            numpagewritten++;
            NumPageToWrite--;
            /*!< Calculate Next small page Address */
            addressstatus = NAND_AddressIncrement(&Address);
        }
    }

    return (status | addressstatus);
}

/**
  * @brief  This routine is for sequential read from one or several 512 Bytes Page size.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  Address: First page address
  * @param  NumPageToRead: Number of page to read
  * @retval New status of the NAND operation. This parameter can be:
  *              - NAND_TIMEOUT_ERROR: when the previous operation generate
  *                a Timeout error
  *              - NAND_READY: when memory is ready for the next operation
  *                And the new status of the increment address operation. It can be:
  *              - NAND_VALID_ADDRESS: When the new address is valid address
  *              - NAND_INVALID_ADDRESS: When the new address is invalid address
  */
uint32_t NAND_ReadSmallPage(uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumPageToRead)
{
    uint32_t index = 0x00, numpageread = 0x00, addressstatus = NAND_VALID_ADDRESS;
    uint32_t status = NAND_READY, size = 0x00;

    while ((NumPageToRead != 0x0) && (addressstatus == NAND_VALID_ADDRESS))
    {
        /*!< Page Read command and page address */
        *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_A;
		
		if (NAND_PAGE_SIZE <= 512U)
		{
			if ((NAND_BLOCK_SIZE * NAND_ZONE_SIZE) <= 65535U)
			{
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = 0x00;
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
			}
			else
			{
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = 0x00;
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
			}
		}
		else
		{
			if ((NAND_BLOCK_SIZE * NAND_ZONE_SIZE) <= 65535U)
			{
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = 0x00;
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = 0x00;
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
			}
			else
			{
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = 0x00;
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = 0x00;
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
				*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
			}	
		}
        /*!< Calculate the size */
        size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpageread);
		
		*(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA)  = NAND_CMD_AREA_TRUE1;

        /*!< Get Data into Buffer */
        for (; index < size; index++)
        {
            pBuffer[index] = *(__IO uint8_t *)(Bank_NAND_ADDR | DATA_AREA);
        }

        numpageread++;
        NumPageToRead--;
        /*!< Calculate page address */
        addressstatus = NAND_AddressIncrement(&Address);
    }

    status = NAND_GetStatus();
    return (status | addressstatus);
}

/**
  * @brief  This routine write the spare area information for the specified
  *         pages addresses.
  * @param  pBuffer: pointer on the Buffer containing data to be written
  * @param  Address: First page address
  * @param  NumSpareAreaTowrite: Number of Spare Area to write
  * @retval New status of the NAND operation. This parameter can be:
  *              - NAND_TIMEOUT_ERROR: when the previous operation generate
  *                a Timeout error
  *              - NAND_READY: when memory is ready for the next operation
  *                And the new status of the increment address operation. It can be:
  *              - NAND_VALID_ADDRESS: When the new address is valid address
  *              - NAND_INVALID_ADDRESS: When the new address is invalid address
  */
uint32_t NAND_WriteSpareArea(uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaTowrite)
{
    uint32_t index = 0x00, numsparesreawritten = 0x00, addressstatus = NAND_VALID_ADDRESS;
    uint32_t status = NAND_READY, size = 0x00;

    while ((NumSpareAreaTowrite != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
    {
        /*!< Page write Spare area command and address */
        *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_C;
        *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_WRITE0;
        *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = 0x00;
        *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
        *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
        *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
        /*!< Calculate the size */
        size = NAND_SPARE_AREA_SIZE + (NAND_SPARE_AREA_SIZE * numsparesreawritten);

        /*!< Write the data */
        for (; index < size; index++)
        {
            *(__IO uint8_t *)(Bank_NAND_ADDR | DATA_AREA) = pBuffer[index];
        }

        *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_WRITE_TRUE1;
        /*!< Check status for successful operation */
        status = NAND_GetStatus();

        if (status == NAND_READY)
        {
            numsparesreawritten++;
            NumSpareAreaTowrite--;
            /*!< Calculate Next page Address */
            addressstatus = NAND_AddressIncrement(&Address);
        }
    }

    return (status | addressstatus);
}

/**
  * @brief  This routine read the spare area information from the specified
  *         pages addresses.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  Address: First page address
  * @param  NumSpareAreaToRead: Number of Spare Area to read
  * @retval New status of the NAND operation. This parameter can be:
  *              - NAND_TIMEOUT_ERROR: when the previous operation generate
  *                a Timeout error
  *              - NAND_READY: when memory is ready for the next operation
  *                And the new status of the increment address operation. It can be:
  *              - NAND_VALID_ADDRESS: When the new address is valid address
  *              - NAND_INVALID_ADDRESS: When the new address is invalid address
  */
uint32_t NAND_ReadSpareArea(uint8_t *pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaToRead)
{
    uint32_t numsparearearead = 0x00, index = 0x00, addressstatus = NAND_VALID_ADDRESS;
    uint32_t status = NAND_READY, size = 0x00;

    while ((NumSpareAreaToRead != 0x0) && (addressstatus == NAND_VALID_ADDRESS))
    {
        /*!< Page Read command and page address */
        *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_C;
        *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = 0x00;
        *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
        *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
        *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
        /*!< Data Read */
        size = NAND_SPARE_AREA_SIZE +  (NAND_SPARE_AREA_SIZE * numsparearearead);

        /*!< Get Data into Buffer */
        for ( ; index < size; index++)
        {
            pBuffer[index] = *(__IO uint8_t *)(Bank_NAND_ADDR | DATA_AREA);
        }

        numsparearearead++;
        NumSpareAreaToRead--;
        /*!< Calculate page address */
        addressstatus = NAND_AddressIncrement(&Address);
    }

    status = NAND_GetStatus();
    return (status | addressstatus);
}

/**
  * @brief  This routine erase complete block from NAND FLASH
  * @param  Address: Any address into block to be erased
  * @retval New status of the NAND operation. This parameter can be:
  *              - NAND_TIMEOUT_ERROR: when the previous operation generate
  *                a Timeout error
  *              - NAND_READY: when memory is ready for the next operation
  */
uint32_t NAND_EraseBlock(NAND_ADDRESS Address)
{
    *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_ERASE0;
    *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
    *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
    *(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
    *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_ERASE1;
    return (NAND_GetStatus());
}

/**
  * @brief  This routine reset the NAND FLASH.
  * @param  None
  * @retval NAND_READY
  */
uint32_t NAND_Reset(void)
{
    *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_RESET;
    return (NAND_READY);
}

/**
  * @brief  Get the NAND operation status.
  * @param  None
  * @retval New status of the NAND operation. This parameter can be:
  *              - NAND_TIMEOUT_ERROR: when the previous operation generate
  *                a Timeout error
  *              - NAND_READY: when memory is ready for the next operation
  */
uint32_t NAND_GetStatus(void)
{
    uint32_t timeout = 0x1000000, status = NAND_READY;
    status = NAND_ReadStatus();

    /*!< Wait for a NAND operation to complete or a TIMEOUT to occur */
    while ((status != NAND_READY) && ( timeout != 0x00))
    {
        status = NAND_ReadStatus();
        timeout --;
    }

    if (timeout == 0x00)
    {
        status =  NAND_TIMEOUT_ERROR;
    }

    /*!< Return the operation status */
    return (status);
}

/**
  * @brief  Reads the NAND memory status using the Read status command.
  * @param  None
  * @retval The status of the NAND memory. This parameter can be:
  *              - NAND_BUSY: when memory is busy
  *              - NAND_READY: when memory is ready for the next operation
  *              - NAND_ERROR: when the previous operation gererates error
  */
uint32_t NAND_ReadStatus(void)
{
    uint32_t data = 0x00, status = NAND_BUSY;
    /*!< Read status operation ------------------------------------ */
    *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_STATUS;
    data = *(__IO uint8_t *)(Bank_NAND_ADDR);

    if ((data & NAND_ERROR) == NAND_ERROR)
    {
        status = NAND_ERROR;
    }
    else if ((data & NAND_READY) == NAND_READY)
    {
        status = NAND_READY;
    }
    else
    {
        status = NAND_BUSY;
    }

    return (status);
}

/**
  * @brief  Increment the NAND memory address.
  * @param  Address: address to be incremented.
  * @retval The new status of the increment address operation. It can be:
  *              - NAND_VALID_ADDRESS: When the new address is valid address
  *              - NAND_INVALID_ADDRESS: When the new address is invalid address
  */
uint32_t NAND_AddressIncrement(NAND_ADDRESS* Address)
{
    uint32_t status = NAND_VALID_ADDRESS;
    Address->Page++;

    if (Address->Page == NAND_BLOCK_SIZE)
    {
        Address->Page = 0;
        Address->Block++;

        if (Address->Block == NAND_ZONE_SIZE)
        {
            Address->Block = 0;
            Address->Zone++;

            if (Address->Zone == NAND_MAX_ZONE)
            {
                status = NAND_INVALID_ADDRESS;
            }
        }
    }

    return (status);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

