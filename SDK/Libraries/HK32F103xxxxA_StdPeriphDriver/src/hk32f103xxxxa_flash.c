/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_flash.c
* @brief:     This file provides all the FLASH firmware functions.
* @author:    AE Team
* @version:   V1.0.0/2023-10-12
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_flash.h"
#include "hk32f103xxxxa_cache.h"

#define FLASH_CACHE_BUG_FIX         1

/** @addtogroup HK32F103xxxxA_StdPeriph_Driver
  * @{
  */

/** @defgroup FLASH FLASH
  * @brief FLASH driver modules
  * @{
    @verbatim
=====================================================================
                 ##### How to use this driver #####
=====================================================================
    [..] This driver provides functions to configure and program the FLASH
             of all hk32f103xxxxa Serial devices These functions are split in 7 groups:
             (#) Flash Access Function: this group includes all needed functions
                     to configure the Flash Access:
                     (++) FLASH_SetLatency.
                     (++) FLASH_HalfCycleAccessCmd.
                     (++) FLASH_PrefetchBufferCmd .
                     (++) FLASH_Unlock .
                     (++) FLASH_Lock .

             (#) Main Flash and User Option Block program and Erase:
                     (++) FLASH_EraseHalfPage .
                     (++) FLASH_ProgramHalfWord .
                     (++) FLASH_ErasePage .
                     (++) FLASH_EraseAllPages .
                     (++) FLASH_EraseOptionBytes .
                     (++) FLASH_ProgramWord .
                     (++) FLASH_ProgramOptionByteData .
                     (++) FLASH_EnableWriteProtection .
                     (++) FLASH_ReadOutProtection .
                     (++) FLASH_UserOptionByteConfig .

             (#) Get Flash User Option Status:
                     (++) FLASH_GetUserOptionByte .
                     (++) FLASH_GetWriteProtectionOptionByte .
                     (++) FLASH_GetReadOutProtectionStatus.
                     (++) FLASH_GetPrefetchBufferStatus .

             (#) Flash Flag Process:
                    (++) FLASH_GetFlagStatus.
                    (++) FLASH_ClearFlag .
                    (++) FLASH_ClearFlag .
                    (++) FLASH_WaitForLastOperation .

             (#) Flash User Option program.
                     (++) FLASH_OptionIWDG_RLIV .
                     (++) FLASH_OptionIWDG_RLIV_CMD.
                     (++) FLASH_Option_LSI_CMD .
                     (++) FLASH_Option_Debug_CMD .
                     (++) FLASH_BOR_SET .
                     (++) FLASH_ENCRY_DECRY .

             (#) Other Flash Function,Interrupt and Parity Check.
                     (++) FLASH_ITConfig.
                     (++) FLASH_Parity_Check.
                     (++) Get_FLASH_Parity_Err_Address.

    @endverbatim
  *
  ******************************************************************************
  */

/** @defgroup group_c1 FLASH_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup group_c2 FLASH_Private_Defines
  * @{
  */

/* Flash Access Control Register bits */
#define ACR_LATENCY_Mask         ((uint32_t)0x00000038)
#define ACR_HLFCYA_Mask          ((uint32_t)0xFFFFFFF7)
#define ACR_PRFTBE_Mask          ((uint32_t)0xFFFFFFEF)

/* Flash Access Control Register bits */
#define ACR_PRFTBS_Mask          ((uint32_t)0x00000020)

/* Flash Control Register bits */
#define CR_PG_Set                ((uint32_t)0x00000001)
#define CR_PG_Reset              ((uint32_t)0x00001FFE)
#define CR_PER_Set               ((uint32_t)0x00000002)
#define CR_PER_Reset             ((uint32_t)0x00001FFD)
#define CR_MER_Set               ((uint32_t)0x00000004)
#define CR_MER_Reset             ((uint32_t)0x00001FFB)
#define CR_OPTPG_Set             ((uint32_t)0x00000010)
#define CR_OPTPG_Reset           ((uint32_t)0x00001FEF)
#define CR_OPTER_Set             ((uint32_t)0x00000020)
#define CR_OPTER_Reset           ((uint32_t)0x00001FDF)
#define CR_STRT_Set              ((uint32_t)0x00000040)
#define CR_LOCK_Set              ((uint32_t)0x00000080)

#define ECR_MPER_Set               ((uint32_t)0x00000001)
#define ECR_MPER_Reset             ((uint32_t)0x000001FE)
#define ECR_WPG_Set                ((uint32_t)0x00000002)
#define ECR_WPG_Reset              ((uint32_t)0x000001FD)
#define ECR_2WPG_Set               ((uint32_t)0x00000004)
#define ECR_2WPG_Reset             ((uint32_t)0x000001FB)
#define ECR_4WPG_Set               ((uint32_t)0x00000008)
#define ECR_4WPG_Reset             ((uint32_t)0x000001F7)
#define ECR_Inf_MPER_Set           ((uint32_t)0x00000010)
#define ECR_Inf_MPER_Reset         ((uint32_t)0x000001EF)
#define ECR_Inf_HWPG_Set           ((uint32_t)0x00000020)
#define ECR_Inf_HWPG_Reset         ((uint32_t)0x000001DF)
#define ECR_Inf_WPG_Set            ((uint32_t)0x00000040)
#define ECR_Inf_WPG_Reset          ((uint32_t)0x000001BF)
#define ECR_Inf_2WPG_Set           ((uint32_t)0x00000080)
#define ECR_Inf_2WPG_Reset         ((uint32_t)0x0000017F)
#define ECR_Inf_4WPG_Set           ((uint32_t)0x00000100)
#define ECR_Inf_4WPG_Reset         ((uint32_t)0x000000FF)

/* FLASH Mask */
#define RDPRT_Mask               ((uint32_t)0x00000002)
#define WRP0_Mask                ((uint32_t)0x000000FF)
#define WRP1_Mask                ((uint32_t)0x0000FF00)
#define WRP2_Mask                ((uint32_t)0x00FF0000)
#define WRP3_Mask                ((uint32_t)0xFF000000)

/* FLASH Keys */
#define RDP_Key                  ((uint16_t)0x00A5)
#define FLASH_KEY1               ((uint32_t)0x45670123)
#define FLASH_KEY2               ((uint32_t)0xCDEF89AB)
#define FLASH_Encry              ((uint32_t)0x1357eca8)
#define FLASH_Decry              ((uint32_t)0x2468db97)
#define FLASH_IWDGRLIVCMD        ((uint32_t)0xa5a55b1e)
#define FLASH_LSILPCTL           ((uint32_t)0x369CF0F0)
#define FLASH_DebugCMD           ((uint32_t)0x1234bcde)

/* Delay definition */
#define EraseTimeout          ((uint32_t)0x000B0000)
#define ProgramTimeout        ((uint32_t)0x00002000)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup group_c3 FLASH_Private_Functions
  * @{
  */


/** @defgroup FLASH_Group1 Flash Access management functions
 *  @brief   Flash Access management functions
 *
@verbatim
 ===============================================================================
                 ##### Flash Access management functions #####
 ===============================================================================

        *** Flash Driver: how to use it in Flash Access ***
 ===============================================================================
    [..] To use the functions in Flash Access mode, the following steps are
         mandatory:
         (#) Setting Flash latency depends on the system clock.
                            0wait, 0<SYSCLK<=30MHz;
                            1wait, 30MHz<SYSCLK<=60MHz
                            2wait, 60MHz<SYSCLK<=90MHz
                            4wait, 90MHz<SYSCLK<=120MHz
         (#) Setting HalfCycleAccess may increase flash read-out efficiency
                         when system clock <= 8MHz.
         (#) Setting Prefetch buffer enable may increase flash read-out efficiency.
         (#) Write the right Key to Unlock the Flash
                         Key1 = 0x45670123
                         Key2 = 0xCDEF89AB
         (#) Setting the Lock bit in Flash->CR register when flash program/erase
                         operation is finished.
    [..]
@endverbatim
  * @{
  */

/**
  * @brief  Sets the code latency value.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  FLASH_Latency: specifies the FLASH Latency value.
  *         This parameter can be one of the following values:
  *         FLASH_Latency_0: FLASH Zero Latency cycle
  *         FLASH_Latency_1: FLASH One Latency cycle
  *         FLASH_Latency_2: FLASH Two Latency cycles
  *         ......
  *         FLASH_Latency_31: FLASH Thirty-one Latency cycles
  * @retval None
  */
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
    uint32_t tmpreg = 0, tmpreg1 = 0;
    /* Check the parameters */
    assert_param(IS_FLASH_LATENCY(FLASH_Latency));
    /* Read the ACR register */
    tmpreg = FLASH->ACR;
    /* Sets the Latency value */
    tmpreg &= ACR_LATENCY_Mask;
    tmpreg |= FLASH_Latency & 0x07;
    /* Sets the Latency-ex value */
    tmpreg1 |= FLASH_Latency >> 3;
    /* Write the ACR register */
    FLASH->ACR = tmpreg;
    FLASH->LATENCY_EX = tmpreg1;
}

/**
  * @brief  Enables or disables the Half cycle flash access.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  FLASH_HalfCycleAccess: specifies the FLASH Half cycle Access mode.
  *         This parameter can be one of the following values:
  *         FLASH_HalfCycleAccess_Enable: FLASH Half Cycle Enable
  *         FLASH_HalfCycleAccess_Disable: FLASH Half Cycle Disable
  * @retval None
  */
void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess)
{
    /* Check the parameters */
    assert_param(IS_FLASH_HALFCYCLEACCESS_STATE(FLASH_HalfCycleAccess));
    /* Enable or disable the Half cycle access */
    FLASH->ACR &= ACR_HLFCYA_Mask;
    FLASH->ACR |= FLASH_HalfCycleAccess;
}

/**
  * @brief  Enables or disables the Prefetch Buffer.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  FLASH_PrefetchBuffer: specifies the Prefetch buffer status.
  *         This parameter can be one of the following values:
  *         FLASH_PrefetchBuffer_Enable: FLASH Prefetch Buffer Enable
  *         FLASH_PrefetchBuffer_Disable: FLASH Prefetch Buffer Disable
  * @retval None
  */
void FLASH_PrefetchBufferCmd(uint32_t FLASH_PrefetchBuffer)
{
    /* Check the parameters */
    assert_param(IS_FLASH_PREFETCHBUFFER_STATE(FLASH_PrefetchBuffer));
    /* Enable or disable the Prefetch Buffer */
    FLASH->ACR &= ACR_PRFTBE_Mask;
    FLASH->ACR |= FLASH_PrefetchBuffer;
}

/**
  * @brief  Unlocks the FLASH Program Erase Controller.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @retval None
  */
void FLASH_Unlock(void)
{
    /* Authorize the FPEC of Bank1 Access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
}

/**
  * @brief  Locks the FLASH Program Erase Controller.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @retval None
  */
void FLASH_Lock(void)
{
    /* Set the Lock Bit to lock the FPEC  */
    FLASH->CR |= CR_LOCK_Set;
}

/**
  * @}
  */


/** @defgroup FLASH_Group2 Main_Flash/User_Option Block program/Erase management functions
 *  @brief    Main_Flash/User_Option Block program/Erase management functions
 *
@verbatim
 ===============================================================================
        ##### Main_Flash/User_Option Block program/Erase management functions #####
 ===============================================================================

        *** Flash Driver: how to use it in Main_Flash/User_Option Block program/Erase ***
 ===============================================================================
    [..] To use the functions in Flash program/Erase mode, the following steps are
         mandatory:
         (#) FLASH_ErasePage can be used in ALL_hk32f103xxxxa_SERIAL with 2KB/page.
                         Erase a full page data to 0xff.
                         this function satisfy all hk32f103xxxxa serials.

         (#) FLASH_EraseAllPage can be used in ALL_hk32f103xxxxa_SERIAL , Erase full
                         Chip data to 0xff.
                         this function satisfy all hk32f103xxxxa serials.

         (#) FLASH_EraseOptionBytes can be used in ALL_hk32f103xxxxa_SERIAL , Erase User
                         Option data to 0xff.
                         this function satisfy all hk32f103xxxxa serials.

         (#) FLASH_Program2Word can be used in ALL_hk32f103xxxxa_SERIAL , Program User desired
                         2*32bits data to Main flash .
                         this function satisfy all hk32f103xxxxa serials.

         (#) FLASH_ProgramWord can be used in ALL_hk32f103xxxxa_SERIAL , Program User desired
                         32bits data to Main flash .
                         this function satisfy all hk32f103xxxxa serials.

         (#) FLASH_ProgramHalfWord can be used in ALL_hk32f103xxxxa_SERIAL,Program User desired
                         16bits data to Main flash .
                         this function satisfy all hk32f103xxxxa serials.

         (#) FLASH_ProgramOptionByteData can be used in ALL_hk32f103xxxxa_SERIAL , Program User desired
                         data to Option byte .
                         this function satisfy all hk32f103xxxxa serials.

         (#) FLASH_EnableWriteProtection can be used in ALL_hk32f103xxxxa_SERIAL , set Main flash page to
                         write-protect status.
                         this function satisfy all hk32f103xxxxa serials.

         (#) FLASH_ReadOutProtection can be used in ALL_hk32f103xxxxa_SERIAL , set Main flash page to
                         write-protect status.
                         this function satisfy all hk32f103xxxxa serials.

         (#) FLASH_UserOptionByteConfig can be used in ALL_hk32f103xxxxa_SERIAL , Set IWDG,nStop,nStandby
                         chip function to Option byte .
                         this function satisfy all hk32f103xxxxa serials.
    [..]
@endverbatim
  * @{
  */

/**
  * @brief  Erases a specified FLASH page.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  Page_Address: The page address to be erased.
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Page_Address));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->CR |= CR_PER_Set;
        FLASH->AR = Page_Address;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        FLASH->CR |= CR_STRT_Set;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);
        /* Disable the PER Bit */
        FLASH->CR &= CR_PER_Reset;
    }

    /* Return the Erase Status */
    return status;
}

/**
  * @brief  Erases a micro FLASH page(512K).
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  Page_Address: The page address to be erased.
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseMicroPage(uint32_t Page_Address)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Page_Address));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->ECR |= ECR_MPER_Set;
        FLASH->AR = Page_Address;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        FLASH->CR |= CR_STRT_Set;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);
        /* Disable the PER Bit */
        FLASH->ECR &= ECR_MPER_Reset;
    }

    /* Return the Erase Status */
    return status;
}


/**
  * @brief  Erases all FLASH pages.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseAllPages(void)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to erase all pages */
        FLASH->CR |= CR_MER_Set;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        FLASH->CR |= CR_STRT_Set;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);
        /* Disable the MER Bit */
        FLASH->CR &= CR_MER_Reset;
    }

    /* Return the Erase Status */
    return status;
}


/**
  * @brief  Erases the FLASH option bytes.
  * @note   This functions erases all option bytes except the Read protection (RDP).
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseOptionBytes(void)
{
    uint16_t rdptmp = RDP_Key;
    FLASH_Status status = FLASH_COMPLETE;

    /* Get the actual read protection Option Byte value */
    if (FLASH_GetReadOutProtectionStatus() != RESET)
    {
        rdptmp = 0x00;
    }

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* Authorize the small information block programming */
        FLASH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CR |= CR_OPTER_Set;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        FLASH->CR |= CR_STRT_Set;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);

        if (status == FLASH_COMPLETE)
        {
            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CR &= CR_OPTER_Reset;
            /* Enable the Option Bytes Programming operation */
            FLASH->CR |= CR_OPTPG_Set;
            /* Restore the last read protection Option Byte value */
            OB->RDP = (uint16_t)rdptmp;
            /* Wait for last operation to be completed */
#if  FLASH_CACHE_BUG_FIX
            CACHE->CTL |= 0x0800;
#endif
            status = FLASH_WaitForLastOperation(ProgramTimeout);

            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CR &= CR_OPTPG_Reset;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTPG Bit */
                FLASH->CR &= CR_OPTPG_Reset;
            }
        }
    }

    /* Return the erase status */
    return status;
}

/**
  * @brief  Erases the info flash.
  * @note   This functions erases info flash.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseInfo(uint32_t Halfpage_Address)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* Authorize the small information block programming */
        FLASH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
        /* if the previous operation is completed, proceed to erase the info flash */
        FLASH->ECR |= ECR_Inf_MPER_Set;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        FLASH->CR |= ECR_Inf_MPER_Reset;
    }

    /* Return the erase status */
    return status;
}


/**
  * @brief  Programs a 4 words at a specified address.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_Program4Words(uint32_t Address, uint32_t *Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Address));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to program the new first
        half word */
        FLASH->ECR |= ECR_4WPG_Set;
        FLASH->PW0 = Data[0];
        FLASH->PW1 = Data[1];
        FLASH->PW2 = Data[2];
        FLASH->PW3 = Data[3];
        FLASH->AR = Address;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        FLASH->CR |= CR_STRT_Set;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        /* Disable the PG Bit */
        FLASH->ECR &= ECR_4WPG_Reset;
    }

    /* Return the Program Status */
    return status;
}

/**
  * @brief  Programs a 2 words at a specified address.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  Address: specifies the address to be programmed.
  * @param  DataL: specifies the data to be programmed in Low Address.
  * @param  DataH: specifies the data to be programmed in High Address.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_Program2Words(uint32_t Address, uint32_t DataL, uint32_t DataH)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Address));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to program the new first
        half word */
        FLASH->ECR |= ECR_2WPG_Set;
        FLASH->PW0 = DataL;
        FLASH->PW1 = DataH;
        FLASH->AR = Address;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        FLASH->CR |= CR_STRT_Set;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        /* Disable the PG Bit */
        FLASH->ECR &= ECR_2WPG_Reset;
    }

    /* Return the Program Status */
    return status;
}


/**
  * @brief  Programs a word at a specified address.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    __IO uint32_t tmp = 0;
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Address));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to program the new first
        half word */
        FLASH->ECR |= ECR_WPG_Set;
        *(__IO uint32_t*)Address = (uint32_t)Data;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        /* Disable the PG Bit */
        FLASH->ECR &= ECR_WPG_Reset;
    }

    /* Return the Program Status */
    return status;
}

/**
  * @brief  Programs a half word at a specified address.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Address));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to program the new data */
        FLASH->CR |= CR_PG_Set;
        *(__IO uint16_t*)Address = Data;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        /* Disable the PG Bit */
        FLASH->CR &= CR_PG_Reset;
    }

    /* Return the Program Status */
    return status;
}

/**
  * @brief  Programs a half word at a specified User Option Byte address.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  Address: specifies the address to be programmed.
  *         This parameter can be 0x1FFFF800 or 0x1FFFF840.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint16_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_USER_OPT_ADDRESS(Address));
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* Authorize the small information block programming */
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
        FLASH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
        /* Enables the Option Bytes Programming operation */
        FLASH->CR |= CR_OPTPG_Set;
        *(__IO uint16_t*)Address = Data;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);

        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= CR_OPTPG_Reset;
        }
    }

    /* Return the Option Byte Data Program Status */
    return status;
}

/**
  * @brief  Programs a word at a specified info word address.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramInfoWordData(uint32_t Address, uint32_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_USER_OPT_ADDRESS(Address));
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* Authorize the small information block programming */
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
        FLASH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
        /* Enables the Option word Programming operation */
        FLASH->ECR |= ECR_Inf_WPG_Set;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        *(__IO uint32_t*)Address = Data;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);

        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->ECR &= ECR_Inf_WPG_Reset;
        }
    }

    /* Return the info Data Program Status */
    return status;
}

/**
  * @brief  Programs a Half word at a specified info Half word address.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramInfoHalfWordData(uint32_t Address, uint16_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_USER_OPT_ADDRESS(Address));
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* Authorize the small information block programming */
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
        FLASH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
        /* Enables the Option half word Programming operation */
        FLASH->ECR |= ECR_Inf_HWPG_Set;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        *(__IO uint16_t*)Address = Data;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);

        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->ECR &= ECR_Inf_HWPG_Reset;
        }
    }

    /* Return the Option Byte Data Program Status */
    return status;
}


/**
  * @brief  Write protects the desired pages
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  FLASH_Pages: specifies the address of the pages to be write protected.
  *         This parameter can be:
  *         two pages from 0~61 and 62~255 protect together
  *         FLASH_WRProt_AllPages
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages)
{
    uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_FLASH_WRPROT_PAGE(FLASH_Pages));
    FLASH_Pages = (uint32_t)(~FLASH_Pages);
    WRP0_Data = (uint16_t)(FLASH_Pages & WRP0_Mask);
    WRP1_Data = (uint16_t)((FLASH_Pages & WRP1_Mask) >> 8);
    WRP2_Data = (uint16_t)((FLASH_Pages & WRP2_Mask) >> 16);
    WRP3_Data = (uint16_t)((FLASH_Pages & WRP3_Mask) >> 24);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* Authorizes the small information block programming */
        FLASH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
        FLASH->CR |= CR_OPTPG_Set;

        if (WRP0_Data != 0xFF)
        {
#if  FLASH_CACHE_BUG_FIX
            CACHE->CTL |= 0x0800;
#endif
            OB->WRP0 = WRP0_Data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
        }

        if ((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
        {
#if  FLASH_CACHE_BUG_FIX
            CACHE->CTL |= 0x0800;
#endif
            OB->WRP1 = WRP1_Data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
        }

        if ((status == FLASH_COMPLETE) && (WRP2_Data != 0xFF))
        {
#if  FLASH_CACHE_BUG_FIX
            CACHE->CTL |= 0x0800;
#endif
            OB->WRP2 = WRP2_Data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
        }

        if ((status == FLASH_COMPLETE) && (WRP3_Data != 0xFF))
        {
#if  FLASH_CACHE_BUG_FIX
            CACHE->CTL |= 0x0800;
#endif
            OB->WRP3 = WRP3_Data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
        }

        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= CR_OPTPG_Reset;
        }
    }

    /* Return the write protection operation Status */
    return status;
}

/**
  * @brief  Set the read out protection Level.
  * @note   If the user has already programmed the other option bytes before calling
  *         this function, he must re-program them since this function erases all option bytes.
  * @note   This function can be used for all HK32F103xxxxA devices.
  *         Once the RDP2 is set,the debug port is disabled ,and Option word erasing is disabled.
  * @param  NewState: new state of the ReadOut Protection.
  *         This parameter can be:
  *         DISABLE
  *         ENABLE
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* Authorizes the small information block programming */
        FLASH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
        FLASH->CR |= CR_OPTER_Set;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        FLASH->CR |= CR_STRT_Set;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);

        if (status == FLASH_COMPLETE)
        {
            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CR &= CR_OPTER_Reset;
            /* Enable the Option Bytes Programming operation */
            FLASH->CR |= CR_OPTPG_Set;

            if (NewState != DISABLE)
            {
                OB->RDP = 0x00;
            }
            else
            {
                OB->RDP = RDP_Key;
            }

#if  FLASH_CACHE_BUG_FIX
            CACHE->CTL |= 0x0800;
#endif
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(EraseTimeout);

            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CR &= CR_OPTPG_Reset;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CR &= CR_OPTER_Reset;
            }
        }
    }

    /* Return the protection operation Status */
    return status;
}

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  OB_IWDG: Selects the IWDG mode
  *         This parameter can be one of the following values:
  *         OB_IWDG_SW: Software IWDG selected
  *         OB_IWDG_HW: Hardware IWDG selected
  * @param  OB_STOP: Reset event when entering STOP mode.
  *         This parameter can be one of the following values:
  *         OB_STOP_NoRST: No reset generated when entering in STOP
  *         OB_STOP_RST: Reset generated when entering in STOP
  * @param  OB_STDBY: Reset event when entering Standby mode.
  *         This parameter can be one of the following values:
  *         OB_STDBY_NoRST: No reset generated when entering in STANDBY
  *         OB_STDBY_RST: Reset generated when entering in STANDBY
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
    assert_param(IS_OB_STOP_SOURCE(OB_STOP));
    assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CR |= CR_OPTPG_Set;
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        OB->USER = OB_IWDG | (uint16_t)(OB_STOP | (uint16_t)(OB_STDBY | ((uint16_t)0xF8)));
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);

        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= CR_OPTPG_Reset;
        }
    }

    /* Return the Option Byte program Status */
    return status;
}

/**
  * @}
  */


/** @defgroup FLASH_Group3 Get Flash User Option Status management functions
 *  @brief   Get Flash User Option Status management functions
 *
@verbatim
 ===============================================================================
           ##### Flash User Option Status management functions #####
 ===============================================================================

        *** Flash Driver: how to use it in User Option Status ***
 ===============================================================================
    [..] To use the functions in User Option Status mode, the following steps are
         mandatory:
         (#) FLASH_GetUserOptionByte: return user option status.
         (#) FLASH_GetWriteProtectionOptionByte: return user Wtite-Protect option status.
         (#) FLASH_GetReadOutProtectionStatus: return user Read-Protect option status.
         (#) FLASH_GetPrefetchBufferStatus: retrun Flash prefetch Buffer ON/OFF status.
    [..]
@endverbatim
  * @{
  */
/**
  * @brief  Returns the FLASH User Option Bytes values.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @retval The FLASH User Option Bytes values:IWDG_SW(Bit0), RST_STOP(Bit1)
  *         and RST_STDBY(Bit2).
  */
uint32_t FLASH_GetUserOptionByte(void)
{
    /* Return the User Option Byte */
    return (uint32_t)(FLASH->OBR >> 2);
}

/**
  * @brief  Returns the FLASH Write Protection Option Bytes Register value.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @retval The FLASH Write Protection  Option Bytes Register value
  */
uint32_t FLASH_GetWriteProtectionOptionByte(void)
{
    /* Return the Flash write protection Register value */
    return (uint32_t)(FLASH->WRPR);
}

/**
  * @brief  Get the FLASH Read Out Protection Status Level.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @retval FLASH ReadOut Protection Status (SET or RESET)
  */
FlagStatus FLASH_GetReadOutProtectionStatus(void)
{
    FlagStatus readoutstatus = RESET;

    if ((FLASH->OBR & RDPRT_Mask) != (uint32_t)RESET)
    {
        readoutstatus = SET;
    }
    else
    {
        readoutstatus = RESET;
    }

    return readoutstatus;
}

/**
  * @brief  Checks whether the FLASH Prefetch Buffer status is set or not.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @retval FLASH Prefetch Buffer Status (SET or RESET).
  */
FlagStatus FLASH_GetPrefetchBufferStatus(void)
{
    FlagStatus bitstatus = RESET;

    if ((FLASH->ACR & ACR_PRFTBS_Mask) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the new state of FLASH Prefetch Buffer Status (SET or RESET) */
    return bitstatus;
}

/**
  * @}
  */


/** @defgroup FLASH_Group4 Flash Flag Process management functions
 *  @brief   Flash Flag Process management functions
 *
@verbatim
 ===============================================================================
           ##### Flash Flag Process management functions #####
 ===============================================================================

        *** Flash Driver: how to use it in Flash Flag Process ***
 ===============================================================================
    [..] To use the functions in Flash Flag Process mode, the following steps are
         mandatory:
         (#) Flash Flag Process: Checks whether the specified FLASH flag is set or not,
                         return The new state of FLASH_FLAG (SET or RESET).

         (#) FLASH_ClearFlag: Clears the FLASH's pending flags by writting 1.

         (#) FLASH_GetStatus: Returns the FLASH Status
                         FLASH_BUSY, FLASH_ERROR_PG,FLASH_ERROR_WRP or FLASH_COMPLETE

         (#) FLASH_WaitForLastOperation: Ensure the last Flash Operation is finished.
    [..]
@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  FLASH_FLAG: specifies the FLASH flag to check.
  *         This parameter can be one of the following values:
  *         FLASH_FLAG_BSY: FLASH Busy flag
  *         FLASH_FLAG_PGERR: FLASH Program error flag
  *         FLASH_FLAG_WRPRTERR: FLASH Write protected error flag
  *         FLASH_FLAG_EOP: FLASH End of Operation flag
  *         FLASH_FLAG_OPTERR:  FLASH Option Byte error flag
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG)) ;

    if (FLASH_FLAG == FLASH_FLAG_OPTERR)
    {
        if ((FLASH->OBR & FLASH_FLAG_OPTERR) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else
    {
        if ((FLASH->SR & FLASH_FLAG) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }

    /* Return the new state of FLASH_FLAG (SET or RESET) */
    return bitstatus;
}

/**
  * @brief  Clears the FLASH's pending flags.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  FLASH_FLAG: specifies the FLASH flags to clear.
  *         This parameter can be any combination of the following values:
  *         FLASH_FLAG_PGERR: FLASH Program error flag
  *         FLASH_FLAG_WRPRTERR: FLASH Write protected error flag
  *         FLASH_FLAG_EOP: FLASH End of Operation flag
  * @retval None
  */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
    /* Check the parameters */
    assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG)) ;
    /* Clear the flags */
    FLASH->SR = FLASH_FLAG;
}

/**
  * @brief  Returns the FLASH Status.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP or FLASH_COMPLETE
  */
FLASH_Status FLASH_GetStatus(void)
{
    FLASH_Status flashstatus = FLASH_COMPLETE;

    if ((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY)
    {
        flashstatus = FLASH_BUSY;
    }
    else
    {
        if ((FLASH->SR & FLASH_FLAG_PGERR) != 0)
        {
            flashstatus = FLASH_ERROR_PG;
        }
        else
        {
            if ((FLASH->SR & FLASH_FLAG_WRPRTERR) != 0 )
            {
                flashstatus = FLASH_ERROR_WRP;
            }
            else
            {
                flashstatus = FLASH_COMPLETE;
            }
        }
    }

    /* Return the Flash Status */
    return flashstatus;
}

/**
  * @brief  Waits for a Flash operation to complete or a TIMEOUT to occur.
  * @note   This function can be used for all HK32F103xxxxA devices,
  *         it is equivalent to FLASH_WaitForLastBank1Operation.
  *         -  it waits for a Flash operation to complete
  *         or a TIMEOUT to occur.
  * @param  Timeout: FLASH programming Timeout
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check for the Flash Status */
    status = FLASH_GetStatus();

    /* Wait for a Flash operation to complete or a TIMEOUT to occur */
    while ((status == FLASH_BUSY) && (Timeout != 0x00))
    {
        status = FLASH_GetStatus();
        Timeout--;
    }

    if (Timeout == 0x00 )
    {
        status = FLASH_TIMEOUT;
    }

    /* Return the operation status */
    return status;
}

/**
  * @}
  */

/** @defgroup FLASH_Group5 Flash User Option program management functions
 *  @brief   Flash User Option program management functions
 *
@verbatim
 ===============================================================================
           ##### Flash User Option program management functions #####
 ===============================================================================

        *** Flash Driver: how to use it in Flash User Option program ***
 ===============================================================================
    [..] To use the functions in Flash User Option program mode, the following steps are
         mandatory:
         (#) FLASH_OptionIWDG_RLIV: Programs the FLASH Option Byte RLR interval time,
                         Hardware IWDG init with this reload value.

         (#) FLASH_OptionIWDG_RLIV_CMD: Programs the FLASH Option Byte to enable or
                         disable RLR interval time, if disabled ,the reload value is 0xfff.

         (#) FLASH_Option_LSI_CMD: Programs the FLASH can be WAKE up by IWDG or not
                         when in STOP and STANDBY mode

         (#) FLASH_Option_Debug_CMD: enable or disable Debug port.

         (#) FLASH_BOR_SET: Flash BOR level set.

         (#) FLASH_ENCRY_DECRY: Flash code encryption and decryption,ENCRY and DECRY
                         must be set together,otherwise CPU fecth wrong instruction.
    [..]
@endverbatim
  * @{
  */
/**
  * @brief  Programs the FLASH Option Byte RLR interval time.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  OB_IWDGRLIV: set the RLR interval value
  *         This parameter can be one of the following values0~0xffff:
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OptionIWDGRLIV(uint16_t OB_IWDGRLIV)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* Enable the Option Bytes Programming operation */
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        FLASH->CR |= CR_OPTPG_Set;
        OB->IWDG_RL_IV = OB_IWDGRLIV;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);

        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= CR_OPTPG_Reset;
        }
    }

    /* Return the Option Byte program Status */
    return status;
}

/**
  * @brief  Programs the FLASH Option Byte to enable or disable RLR interval time.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  NewState: new state of the IWDG init key.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OptionIWDGRLIVCMD(FunctionalState NewState)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* Enable the Option Bytes Programming operation */
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        FLASH->CR |= CR_OPTPG_Set;

        if (NewState != DISABLE)
        {
            OB->IWDG_INI_KEY = FLASH_IWDGRLIVCMD;
        }
        else
        {
            OB->IWDG_INI_KEY = 0;
        }

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);

        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= CR_OPTPG_Reset;
        }
    }

    /* Return the Option Byte program Status */
    return status;
}

/**
  * @brief  Programs the FLASH can be WAKE up by IWDG or not when in STOP and STANDBY mode.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  NewState: new state of the IWDG Clock support when in STOP and STANDBY mode.
  *         This parameter can be: ENABLE: cannot wake up by IWDG in stop and standby
  *         DISABLE: can be wake up by IWDG in stop and standby.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OptionLSICMD(FunctionalState NewState)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
        /* Enable the Option Bytes Programming operation */
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        FLASH->CR |= CR_OPTPG_Set;

        if (NewState != DISABLE)
        {
            OB->LSI_LP_CTL = FLASH_LSILPCTL;
        }
        else
        {
            OB->IWDG_INI_KEY = 0;
        }

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);

        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= CR_OPTPG_Reset;
        }
    }

    /* Return the Option Byte program Status */
    return status;
}

/**
  * @brief  enable or disable Debug port.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  NewState: new state of the ReadOut Protection.
  *         This parameter can be: ENABLE: close Debug port
  *         DISABLE: open Debug port.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OptionDebugCMD(FunctionalState NewState)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
#if  FLASH_CACHE_BUG_FIX
        CACHE->CTL |= 0x0800;
#endif
        /* Enable the Option Bytes Programming operation */
        FLASH->CR |= CR_OPTPG_Set;

        if (NewState != DISABLE)
        {
            OB->LSI_LP_CTL = FLASH_DebugCMD;
        }
        else
        {
            OB->IWDG_INI_KEY = 0;
        }

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);

        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= CR_OPTPG_Reset;
        }
    }

    /* Return the Option Byte program Status */
    return status;
}

/** @defgroup FLASH_Group6 Flash Other Flash Function management functions
 *  @brief   Other Flash Function management functions
 *
@verbatim
 ===============================================================================
           ##### Other Flash Function management functions #####
 ===============================================================================

        *** Flash Driver: how to use it in Other Flash Function ***
 ===============================================================================
    [..] To use the functions in FlashOther Flash mode, the following steps are
         mandatory:
         (#) FLASH_ITConfig: Enables or disables the specified FLASH interrupts.

    [..]
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified FLASH interrupts.
  * @note   This function can be used for all HK32F103xxxxA devices.
  * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *         FLASH_IT_ERROR: FLASH Error Interrupt
  *         FLASH_IT_EOP: FLASH end of operation Interrupt
  * @param  NewState: new state of the specified Flash interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FLASH_IT(FLASH_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the interrupt sources */
        FLASH->CR |= FLASH_IT;
    }
    else
    {
        /* Disable the interrupt sources */
        FLASH->CR &= ~(uint32_t)FLASH_IT;
    }
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
