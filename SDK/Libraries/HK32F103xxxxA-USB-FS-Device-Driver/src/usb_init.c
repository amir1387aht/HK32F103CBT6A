/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_init.c
* @brief:     Initialization routines & global variables.
* @author:    AE Team
* @version:   V1.0.0/2023-10-16
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"

/** @addtogroup USB
  * @brief  USB driver modules
  * @{
  */

/** @defgroup usb_init usb_init
  * @{
    @verbatim
 ===============================================================================
                        ##### usb_init.c explain #####
 ===============================================================================
....[..]
   (#) This module sets initialization routines and global variables that will be used in the library.
    @endverbatim
  *
  ******************************************************************************
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup usb_init_Private_Variables usb_init_Private_Variables
  * @{
  */

/*  The number of current endpoint, it will be used to specify an endpoint */
uint8_t    EPindex;
/*  The number of current device, it is an index to the Device_Table */
/* uint8_t  Device_no; */
/*  Points to the DEVICE_INFO structure of current device */
/*  The purpose of this register is to speed up the execution */
DEVICE_INFO *pInformation;
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */
DEVICE_PROP *pProperty;
/*  Temporary save the state of Rx & Tx status. */
/*  Whenever the Rx or Tx state is changed, its value is saved */
/*  in this variable first and will be set to the EPRB or EPRA */
/*  at the end of interrupt process */
uint16_t    SaveState ;
uint16_t  wInterrupt_Mask;
DEVICE_INFO Device_Info;
USER_STANDARD_REQUESTS  *pUser_Standard_Requests;

/**
  * @}
  */

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup usb_init_Private_Functions usb_init_Private_Functions
  * @{
  */

/**
  * @brief  USB system initialization
  * @retval None.
  **/
void USB_Init(void)
{
    pInformation = &Device_Info;
    pInformation->ControlState = 2;
    pProperty = &Device_Property;
    pUser_Standard_Requests = &User_Standard_Requests;
    /* Initialize devices one by one */
    pProperty->Init();
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

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
