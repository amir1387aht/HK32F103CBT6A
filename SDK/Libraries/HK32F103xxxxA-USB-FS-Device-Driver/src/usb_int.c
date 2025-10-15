/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_int.c
* @brief:     Endpoint CTR (Low and High) interrupt's service routines.
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

/** @defgroup usb_int usb_int
  * @{
    @verbatim
 ===============================================================================
                        ##### usb_int.c explain #####
 ===============================================================================
....[..]
   (#) The usb_int module handles the correct transfer interrupt service routines; it offers the link
       between the USB device protocol events and the library.
    @endverbatim
  *
  ******************************************************************************
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup usb_int_Private_Variables usb_int_Private_Variables
  * @{
  */

__IO uint16_t SaveRState;
__IO uint16_t SaveTState;

/**
  * @}
  */

/* Extern variables ----------------------------------------------------------*/

/** @defgroup usb_int_Extern_Variables usb_int_Extern_Variables
  * @{
  */

extern void (*pEpInt_IN[7])(void);    /*  Handles IN  interrupts   */
extern void (*pEpInt_OUT[7])(void);   /*  Handles OUT interrupts   */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup usb_int_Private_Functions usb_int_Private_Functions
  * @{
  */

/**
* @brief  Low priority Endpoint Correct Transfer interrupt's service
*         routine.
* @retval None.
**/
void CTR_LP(void)
{
    __IO uint16_t wEPVal = 0;

    /* stay in loop while pending interrupts */
    while (((wIstr = _GetISTR()) & ISTR_CTR) != 0)
    {
        /* extract highest priority endpoint number */
        EPindex = (uint8_t)(wIstr & ISTR_EP_ID);

        if (EPindex == 0)
        {
            /* Decode and service control endpoint interrupt */
            /* calling related service routine */
            /* (Setup0_Process, In0_Process, Out0_Process) */

            /* save RX & TX status */
            /* and set both to NAK */

            SaveRState = _GetENDPOINT(ENDP0);
            SaveTState = SaveRState & EPTX_STAT;
            SaveRState &=  EPRX_STAT;

            _SetEPRxTxStatus(ENDP0, EP_RX_NAK, EP_TX_NAK);

            /* DIR bit = origin of the interrupt */

            if ((wIstr & ISTR_DIR) == 0)
            {
                /* DIR = 0 */

                /* DIR = 0      => IN  int */
                /* DIR = 0 implies that (EP_CTR_TX = 1) always  */

                _ClearEP_CTR_TX(ENDP0);
                In0_Process();

                /* before terminate set Tx & Rx status */
                _SetEPRxTxStatus(ENDP0, SaveRState, SaveTState);
                return;
            }
            else
            {
                /* DIR = 1 */
                /* DIR = 1 & CTR_RX       => SETUP or OUT int */
                /* DIR = 1 & (CTR_TX | CTR_RX) => 2 int pending */

                wEPVal = _GetENDPOINT(ENDP0);

                if ((wEPVal & EP_SETUP) != 0)
                {
                    _ClearEP_CTR_RX(ENDP0); /* SETUP bit kept frozen while CTR_RX = 1 */
                    Setup0_Process();
                    /* before terminate set Tx & Rx status */

                    _SetEPRxTxStatus(ENDP0, SaveRState, SaveTState);
                    return;
                }

                else if ((wEPVal & EP_CTR_RX) != 0)
                {
                    _ClearEP_CTR_RX(ENDP0);
                    Out0_Process();
                    /* before terminate set Tx & Rx status */

                    _SetEPRxTxStatus(ENDP0, SaveRState, SaveTState);
                    return;
                }
            }
        }/* if(EPindex == 0) */
        else
        {
            /* Decode and service non control endpoints interrupt  */

            /* process related endpoint register */
            wEPVal = _GetENDPOINT(EPindex);

            if ((wEPVal & EP_CTR_RX) != 0)
            {
                /* clear int flag */
                _ClearEP_CTR_RX(EPindex);
                /* call OUT service function */
                (*pEpInt_OUT[EPindex - 1])();
            } /* if((wEPVal & EP_CTR_RX) */

            if ((wEPVal & EP_CTR_TX) != 0)
            {
                /* clear int flag */
                _ClearEP_CTR_TX(EPindex);

                /* call IN service function */
                (*pEpInt_IN[EPindex - 1])();
            } /* if((wEPVal & EP_CTR_TX) != 0) */

        }/* if(EPindex == 0) else */

    }/* while(...) */
}

/**
  * @brief  High Priority Endpoint Correct Transfer interrupt's service
  *         routine.
  * @retval None.
  **/
void CTR_HP(void)
{
    uint32_t wEPVal = 0;

    while (((wIstr = _GetISTR()) & ISTR_CTR) != 0)
    {
        _SetISTR((uint16_t)CLR_CTR); /* clear CTR flag */
        /* extract highest priority endpoint number */
        EPindex = (uint8_t)(wIstr & ISTR_EP_ID);
        /* process related endpoint register */
        wEPVal = _GetENDPOINT(EPindex);

        if ((wEPVal & EP_CTR_RX) != 0)
        {
            /* clear int flag */
            _ClearEP_CTR_RX(EPindex);

            /* call OUT service function */
            (*pEpInt_OUT[EPindex - 1])();
        } /* if((wEPVal & EP_CTR_RX) */
        else if ((wEPVal & EP_CTR_TX) != 0)
        {
            /* clear int flag */
            _ClearEP_CTR_TX(EPindex);

            /* call IN service function */
            (*pEpInt_IN[EPindex - 1])();
        } /* if((wEPVal & EP_CTR_TX) != 0) */
    }/* while(...) */
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
