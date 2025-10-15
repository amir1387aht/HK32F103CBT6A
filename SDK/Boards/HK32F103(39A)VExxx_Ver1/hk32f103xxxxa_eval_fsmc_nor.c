/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval_fsmc_nor.c
* @brief:     This file provides a set of functions needed to drive the S29GL128P,
*             S29GL128P NOR memories mounted on HK32F103xxxxA-EVAL board.
* @author:    AE Team
* @version:   V1.0.0/2023-11-14
*             1.Initial version
* @log:
*******************************************************************************/ 

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_eval_fsmc_nor.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup HK32_EVAL
  * @{
  */

/** @addtogroup HK32F103xxxxA_EVAL
  * @{
  */

/** @addtogroup HK32F103xxxxA_EVAL_FSMC_NOR
  * @brief      This file provides a set of functions needed to drive the M29W128FL,
  *             M29W128GL and S29GL128P NOR memories mounted on HK32F103xxxxA-EVAL board.
  * @{
  */

/** @defgroup HK32F103xxxxA_EVAL_FSMC_NOR_Private_Types
  * @{
  */
/**
  * @}
  */

/** @defgroup HK32F103xxxxA_EVAL_FSMC_NOR_Private_Defines
  * @{
  */
/**
  * @brief  FSMC Bank 1 NOR/SRAM2
  */
#define Bank1_NOR2_ADDR       ((uint32_t)0x64000000)

/* Delay definition */
#define BlockErase_Timeout    ((uint32_t)0x00A00000)
#define ChipErase_Timeout     ((uint32_t)0x30000000)
#define Program_Timeout       ((uint32_t)0x00001400)
/**
  * @}
  */


/** @defgroup HK32F103xxxxA_EVAL_FSMC_NOR_Private_Macros
  * @{
  */
#define ADDR_SHIFT(A) (Bank1_NOR2_ADDR + (2 * (A)))
#define NOR_WRITE(Address, Data)  (*(__IO uint16_t *)(Address) = (Data))
/**
  * @}
  */


/** @defgroup HK32F103xxxxA_EVAL_FSMC_NOR_Private_Variables
  * @{
  */
/**
  * @}
  */


/** @defgroupHK32AUTO39A3X_EVAL_FSMC_NOR_Private_Function_Prototypes
  * @{
  */
/**
  * @}
  */


/** @defgroup HK32F103xxxxA_EVAL_FSMC_NOR_Private_Functions
  * @{
  */

/**
  * @brief  Configures the FSMC and GPIOs to interface with the NOR memory.
  *         This function must be called before any write/read operation
  *         on the NOR.
  * @param  None
  * @retval None
  */
void NOR_Init(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  p;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    SET_BIT(AFIO->MAPR2, AFIO_MAPR2_FSMC_100PIN_REMAP);
    /* 使能FSMC对应相应管脚时钟*/
    RCC_APB2PeriphClockCmd (NOR_CS_CLK | NOR_WR_CLK | NOR_RD_CLK | NOR_NWAIT_CLK |
                            NOR_D0_CLK | NOR_D1_CLK |  NOR_D2_CLK |
                            NOR_D3_CLK | NOR_D4_CLK | NOR_D5_CLK |
                            NOR_D6_CLK | NOR_D7_CLK | NOR_D8_CLK |
                            NOR_D9_CLK | NOR_D10_CLK | NOR_D11_CLK |
                            NOR_D12_CLK | NOR_D13_CLK | NOR_D14_CLK | NOR_D15_CLK |
                            NOR_A0_CLK | NOR_A1_CLK | NOR_A2_CLK | NOR_A3_CLK |
                            NOR_A4_CLK | NOR_A5_CLK | NOR_A6_CLK | NOR_A7_CLK |
                            NOR_A8_CLK | NOR_A9_CLK | NOR_A10_CLK | NOR_A11_CLK |
                            NOR_A12_CLK | NOR_A13_CLK | NOR_A14_CLK | NOR_A15_CLK |
                            NOR_A16_CLK | NOR_A17_CLK | NOR_A18_CLK | NOR_A19_CLK |
                            NOR_A20_CLK | NOR_A21_CLK | NOR_A22_CLK, ENABLE );
    /* 配置FSMC相对应的数据线,FSMC-D0~D15 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = NOR_D0_PIN;
    GPIO_Init ( NOR_D0_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D1_PIN;
    GPIO_Init ( NOR_D1_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D2_PIN;
    GPIO_Init ( NOR_D2_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D3_PIN;
    GPIO_Init ( NOR_D3_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D4_PIN;
    GPIO_Init ( NOR_D4_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D5_PIN;
    GPIO_Init ( NOR_D5_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D6_PIN;
    GPIO_Init ( NOR_D6_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D7_PIN;
    GPIO_Init ( NOR_D7_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D8_PIN;
    GPIO_Init ( NOR_D8_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D9_PIN;
    GPIO_Init ( NOR_D9_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D10_PIN;
    GPIO_Init ( NOR_D10_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D11_PIN;
    GPIO_Init ( NOR_D11_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D12_PIN;
    GPIO_Init ( NOR_D12_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D13_PIN;
    GPIO_Init ( NOR_D13_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D14_PIN;
    GPIO_Init ( NOR_D14_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_D15_PIN;
    GPIO_Init ( NOR_D15_PORT, & GPIO_InitStructure );
    /* A0~A19 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = NOR_A0_PIN;
    GPIO_Init ( NOR_A0_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A1_PIN;
    GPIO_Init ( NOR_A1_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A2_PIN;
    GPIO_Init ( NOR_A2_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A3_PIN;
    GPIO_Init ( NOR_A3_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A4_PIN;
    GPIO_Init ( NOR_A4_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A5_PIN;
    GPIO_Init ( NOR_A5_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A6_PIN;
    GPIO_Init ( NOR_A6_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A7_PIN;
    GPIO_Init ( NOR_A7_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A8_PIN;
    GPIO_Init ( NOR_A8_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A9_PIN;
    GPIO_Init ( NOR_A9_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A10_PIN;
    GPIO_Init ( NOR_A10_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A11_PIN;
    GPIO_Init ( NOR_A11_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A12_PIN;
    GPIO_Init ( NOR_A12_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A13_PIN;
    GPIO_Init ( NOR_A13_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A14_PIN;
    GPIO_Init ( NOR_A14_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A15_PIN;
    GPIO_Init ( NOR_A15_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A16_PIN;
    GPIO_Init ( NOR_A16_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A17_PIN;
    GPIO_Init ( NOR_A17_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A18_PIN;
    GPIO_Init ( NOR_A18_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A19_PIN;
    GPIO_Init ( NOR_A19_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A20_PIN;
    GPIO_Init ( NOR_A20_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A21_PIN;
    GPIO_Init ( NOR_A21_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_A22_PIN;
    GPIO_Init ( NOR_A22_PORT, & GPIO_InitStructure );
    /* 配置FSMC相对应的控制线
     * FSMC_NOE  :LCD-RD
     * FSMC_NWE  :LCD-WR
     * FSMC_NE2  :LCD-CS
     * FSMC_NWAIT
     */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = NOR_RD_PIN;
    GPIO_Init (NOR_RD_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_WR_PIN;
    GPIO_Init (NOR_WR_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = NOR_CS_PIN;
    GPIO_Init ( NOR_CS_PORT, & GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = NOR_NWAIT_PIN;
    GPIO_Init ( NOR_NWAIT_PORT, & GPIO_InitStructure );
    /*-- FSMC Configuration ----------------------------------------------------*/
    p.FSMC_AddressSetupTime = 0x07;
    p.FSMC_AddressHoldTime = 0x00;
    p.FSMC_DataSetupTime = 0x07;
    p.FSMC_BusTurnAroundDuration = 0x00;
    p.FSMC_CLKDivision = 0x01;
    p.FSMC_DataLatency = 0x02;
    p.FSMC_AccessMode = FSMC_AccessMode_B;
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM2;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_High;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
    /*!< Enable FSMC Bank1_NOR Bank */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM2, ENABLE);
}

/**
  * @brief  Reads NOR memory's Manufacturer and Device Code.
  * @param  NOR_ID: pointer to a NOR_IDTypeDef structure which will hold the
  *         Manufacturer and Device Code.
  * @retval None
  */
void NOR_ReadID(NOR_IDTypeDef* NOR_ID)
{
    NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
    NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
    NOR_WRITE(ADDR_SHIFT(0x0555), 0x0090);
    NOR_ID->Manufacturer_Code = *(__IO uint16_t *) ADDR_SHIFT(0x0000);
    NOR_ID->Device_Code1 = *(__IO uint16_t *) ADDR_SHIFT(0x0001);
    NOR_ID->Device_Code2 = *(__IO uint16_t *) ADDR_SHIFT(0x000E);
    NOR_ID->Device_Code3 = *(__IO uint16_t *) ADDR_SHIFT(0x000F);
}

/**
  * @brief  Erases the specified Nor memory block.
  * @param  BlockAddr: address of the block to erase.
  * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
  *         or NOR_TIMEOUT
  */
NOR_Status NOR_EraseBlock(uint32_t BlockAddr)
{
    NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
    NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
    NOR_WRITE(ADDR_SHIFT(0x0555), 0x0080);
    NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
    NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
    NOR_WRITE((Bank1_NOR2_ADDR + BlockAddr), 0x30);
    return (NOR_GetStatus(BlockErase_Timeout));
}

/**
  * @brief  Erases the entire chip.
  * @param  None
  * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
  *         or NOR_TIMEOUT
  */
NOR_Status NOR_EraseChip(void)
{
    NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
    NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
    NOR_WRITE(ADDR_SHIFT(0x0555), 0x0080);
    NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
    NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
    NOR_WRITE(ADDR_SHIFT(0x0555), 0x0010);
    return (NOR_GetStatus(ChipErase_Timeout));
}

/**
  * @brief  Writes a half-word to the NOR memory.
  * @param  WriteAddr: NOR memory internal address to write to.
  * @param  Data: Data to write.
  * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
  *         or NOR_TIMEOUT
  */
NOR_Status NOR_WriteHalfWord(uint32_t WriteAddr, uint16_t Data)
{
    NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
    NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
    NOR_WRITE(ADDR_SHIFT(0x0555), 0x00A0);
    NOR_WRITE((Bank1_NOR2_ADDR + WriteAddr), Data);
    return (NOR_GetStatus(Program_Timeout));
}

/**
  * @brief  Writes a half-word buffer to the FSMC NOR memory.
  * @param  pBuffer: pointer to buffer.
  * @param  WriteAddr: NOR memory internal address from which the data will be
  *         written.
  * @param  NumHalfwordToWrite: number of Half words to write.
  * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
  *         or NOR_TIMEOUT
  */
NOR_Status NOR_WriteBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite)
{
    NOR_Status status = NOR_ONGOING;

    do
    {
        /*!< Transfer data to the memory */
        status = NOR_WriteHalfWord(WriteAddr, *pBuffer++);
        WriteAddr = WriteAddr + 2;
        NumHalfwordToWrite--;
    } while ((status == NOR_SUCCESS) && (NumHalfwordToWrite != 0));

    return (status);
}

/**
  * @brief  Writes a half-word buffer to the FSMC NOR memory. This function
  *         must be used only with S29GL128P NOR memory.
  * @param  pBuffer: pointer to buffer.
  * @param  WriteAddr: NOR memory internal address from which the data will be
  *         written.
  * @param  NumHalfwordToWrite: number of Half words to write.
  *         The maximum allowed value is 32 Half words (64 bytes).
  * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
  *         or NOR_TIMEOUT
  */
NOR_Status NOR_ProgramBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite)
{
    uint32_t lastloadedaddress = 0x00;
    uint32_t currentaddress = 0x00;
    uint32_t endaddress = 0x00;
    /*!< Initialize variables */
    currentaddress = WriteAddr;
    endaddress = WriteAddr + NumHalfwordToWrite - 1;
    lastloadedaddress = WriteAddr;
    /*!< Issue unlock command sequence */
    NOR_WRITE(ADDR_SHIFT(0x00555), 0x00AA);
    NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
    /*!< Write Write Buffer Load Command */
    NOR_WRITE(ADDR_SHIFT(WriteAddr), 0x0025);
    NOR_WRITE(ADDR_SHIFT(WriteAddr), (NumHalfwordToWrite - 1));

    /*!< Load Data into NOR Buffer */
    while (currentaddress <= endaddress)
    {
        /*!< Store last loaded address & data value (for polling) */
        lastloadedaddress = currentaddress;
        NOR_WRITE(ADDR_SHIFT(currentaddress), *pBuffer++);
        currentaddress += 1;
    }

    NOR_WRITE(ADDR_SHIFT(lastloadedaddress), 0x29);
    return (NOR_GetStatus(Program_Timeout));
}

/**
  * @brief  Reads a half-word from the NOR memory.
  * @param  ReadAddr: NOR memory internal address to read from.
  * @retval Half-word read from the NOR memory
  */
uint16_t NOR_ReadHalfWord(uint32_t ReadAddr)
{
    NOR_WRITE(ADDR_SHIFT(0x00555), 0x00AA);
    NOR_WRITE(ADDR_SHIFT(0x002AA), 0x0055);
    NOR_WRITE((Bank1_NOR2_ADDR + ReadAddr), 0x00F0 );
    return (*(__IO uint16_t *)((Bank1_NOR2_ADDR + ReadAddr)));
}

/**
  * @brief  Reads a block of data from the FSMC NOR memory.
  * @param  pBuffer: pointer to the buffer that receives the data read from the
  *         NOR memory.
  * @param  ReadAddr: NOR memory internal address to read from.
  * @param  NumHalfwordToRead : number of Half word to read.
  * @retval None
  */
void NOR_ReadBuffer(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead)
{
    NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
    NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
    NOR_WRITE((Bank1_NOR2_ADDR + ReadAddr), 0x00F0);

    /*!< while there is data to read */
	for (; NumHalfwordToRead != 0x00; NumHalfwordToRead--) 
    {
        /*!< Read a Halfword from the NOR */
        *pBuffer++ = *(__IO uint16_t *)((Bank1_NOR2_ADDR + ReadAddr));
        ReadAddr = ReadAddr + 2;
    }
}

/**
  * @brief  Returns the NOR memory to Read mode.
  * @param  None
  * @retval NOR_SUCCESS
  */
NOR_Status NOR_ReturnToReadMode(void)
{
    NOR_WRITE(Bank1_NOR2_ADDR, 0x00F0);
    return (NOR_SUCCESS);
}

/**
  * @brief  Returns the NOR memory to Read mode and resets the errors in the NOR
  *         memory Status Register.
  * @param  None
  * @retval NOR_SUCCESS
  */
NOR_Status NOR_Reset(void)
{
    NOR_WRITE(ADDR_SHIFT(0x00555), 0x00AA);
    NOR_WRITE(ADDR_SHIFT(0x002AA), 0x0055);
    NOR_WRITE(Bank1_NOR2_ADDR, 0x00F0);
    return (NOR_SUCCESS);
}

/**
  * @brief  Returns the NOR operation status.
  * @param  Timeout: NOR progamming Timeout
  * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
  *         or NOR_TIMEOUT
  */
NOR_Status NOR_GetStatus(uint32_t Timeout)
{
    uint16_t val1 = 0x00, val2 = 0x00;
    NOR_Status status = NOR_ONGOING;
    uint32_t timeout = Timeout;

    /*!< Poll on NOR memory Ready/Busy signal ----------------------------------*/
    while ((GPIO_ReadInputDataBit(NOR_NWAIT_PORT, NOR_NWAIT_PIN) != RESET) && (timeout > 0))
    {
        timeout--;
    }

    timeout = Timeout;

    while ((GPIO_ReadInputDataBit(NOR_NWAIT_PORT, NOR_NWAIT_PIN) == RESET) && (timeout > 0))
    {
        timeout--;
    }

    /*!< Get the NOR memory operation status -----------------------------------*/
    while ((Timeout != 0x00) && (status != NOR_SUCCESS))
    {
        Timeout--;
        /*!< Read DQ6 and DQ5 */
        val1 = *(__IO uint16_t *)(Bank1_NOR2_ADDR);
        val2 = *(__IO uint16_t *)(Bank1_NOR2_ADDR);

        /*!< If DQ6 did not toggle between the two reads then return NOR_Success */
        if ((val1 & 0x0040) == (val2 & 0x0040))
        {
            return NOR_SUCCESS;
        }

        if ((val1 & 0x0020) != 0x0020)
        {
            status = NOR_ONGOING;
        }

        val1 = *(__IO uint16_t *)(Bank1_NOR2_ADDR);
        val2 = *(__IO uint16_t *)(Bank1_NOR2_ADDR);

        if ((val1 & 0x0040) == (val2 & 0x0040))
        {
            return NOR_SUCCESS;
        }
        else if ((val1 & 0x0020) == 0x0020)
        {
            return NOR_ERROR;
        }
    }

    if (Timeout == 0x00)
    {
        status = NOR_TIMEOUT;
    }

    /*!< Return the operation status */
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

