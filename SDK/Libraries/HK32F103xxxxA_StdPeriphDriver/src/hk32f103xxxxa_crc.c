/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_crc.c
* @brief:     CRC initialization and configuration
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_crc.h"

/** @addtogroup  HK32F103xxxxA_StdPeriph_Driver
  * @{
  */

/** @defgroup CRC CRC
  * @brief CRC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CRC_Private_Functions CRC_Private_Functions
  * @{
  */

/** @defgroup CRC_Group1 Configuration of the CRC computation unit functions
 *  @brief   Configuration of the CRC computation unit functions
 *
@verbatim
 ===============================================================================
                     ##### CRC configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes CRC peripheral registers to their default reset values.
  * @retval None
  */
void CRC_DeInit(void)
{
    /* Set DR register to reset value */
    CRC->DR = 0xFFFFFFFF;
    /* Reset IDR register */
    CRC->IDR = 0x00;
    /* Reset the CRC calculation unit */
    CRC->CR = CRC_CR_RESET;
}

/**
  * @brief  Resets the CRC calculation unit and sets INIT register content in DR register.
  * @retval None
  */
void CRC_ResetDR(void)
{
    /* Reset CRC generator */
    CRC->CR |= CRC_CR_RESET;
}


/**
  * @}
  */

/** @defgroup CRC_Group2 CRC computation of one/many 32-bit data functions
 *  @brief   CRC computation of one/many 32-bit data functions
 *
@verbatim
 ===============================================================================
                     ##### CRC computation functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  CRC_Data: data word(32-bit) to compute its CRC
  * @retval 32-bit CRC
  */
uint32_t CRC_CalcCRC(uint32_t CRC_Data)
{
    CRC->DR = CRC_Data;
    return (CRC->DR);
}

/**
  * @brief  Computes the 32-bit CRC of a given buffer of data word(32-bit).
  * @param  pBuffer: pointer to the buffer containing the data to be computed
  * @param  BufferLength: length of the buffer to be computed
  * @retval 32-bit CRC
  */
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength)
{
    uint32_t index = 0;

    for (index = 0; index < BufferLength; index++)
    {
        CRC->DR = pBuffer[index];
    }

    return (CRC->DR);
}

/**
  * @brief  Returns the current CRC value.
  * @retval 32-bit CRC
  */
uint32_t CRC_GetCRC(void)
{
    return (CRC->DR);
}

/**
  * @}
  */

/** @defgroup CRC_Group3 CRC Independent Register (IDR) access functions
 *  @brief   CRC Independent Register (IDR) access (write/read) functions
 *
@verbatim
 ===============================================================================
           ##### CRC Independent Register (IDR) access functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Stores an 8-bit data in the Independent Data(ID) register.
  * @param  CRC_IDValue: 8-bit value to be stored in the ID register
  * @retval None
  */
void CRC_SetIDRegister(uint8_t CRC_IDValue)
{
    CRC->IDR = CRC_IDValue;
}

/**
  * @brief  Returns the 8-bit data stored in the Independent Data(ID) register
  * @retval 8-bit value of the ID register
  */
uint8_t CRC_GetIDRegister(void)
{
    return (CRC->IDR);
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
