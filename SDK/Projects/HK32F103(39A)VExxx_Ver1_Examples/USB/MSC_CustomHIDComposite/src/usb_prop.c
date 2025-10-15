/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_prop.c
* @brief:     All processing related to Custom HID Demo.
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "usb_bot.h"
#include "memory.h"
#include "mass_mal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t ProtocolValue;
__IO uint8_t EXTI_Enable;
__IO uint8_t Request = 0;
uint8_t Report_Buf[2];

/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

DEVICE Device_Table =
{
    EP_NUM,
    1
};

DEVICE_PROP Device_Property =
{
    CustomHID_init,
    CustomHID_Reset,
    CustomHID_Status_In,
    CustomHID_Status_Out,
    CustomHID_Data_Setup,
    CustomHID_NoData_Setup,
    CustomHID_Get_Interface_Setting,
    CustomHID_GetDeviceDescriptor,
    CustomHID_GetConfigDescriptor,
    CustomHID_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
};
USER_STANDARD_REQUESTS User_Standard_Requests =
{
    CustomHID_GetConfiguration,
    CustomHID_SetConfiguration,
    CustomHID_GetInterface,
    CustomHID_SetInterface,
    CustomHID_GetStatus,
    CustomHID_ClearFeature,
    CustomHID_SetEndPointFeature,
    CustomHID_SetDeviceFeature,
    CustomHID_SetDeviceAddress
};

ONE_DESCRIPTOR Device_Descriptor =
{
    (uint8_t*)Composite_DeviceDescriptor,
    Composite_SIZ_DEVICE_DESC
};

ONE_DESCRIPTOR Config_Descriptor =
{
    (uint8_t*)Composite_ConfigDescriptor,
    Composite_SIZ_CONFIG_DESC
};

ONE_DESCRIPTOR CustomHID_Report_Descriptor =
{
    (uint8_t *)CustomHID_ReportDescriptor,
    CUSTOMHID_SIZ_REPORT_DESC
};

ONE_DESCRIPTOR CustomHID_Hid_Descriptor =
{
    (uint8_t*)Composite_ConfigDescriptor + CUSTOMHID_OFF_HID_DESC,
    CUSTOMHID_SIZ_HID_DESC
};

ONE_DESCRIPTOR String_Descriptor[4] =
{
    {(uint8_t*)Composite_StringLangID, Composite_SIZ_STRING_LANGID},
    {(uint8_t*)Composite_StringVendor, Composite_SIZ_STRING_VENDOR},
    {(uint8_t*)Composite_StringProduct, Composite_SIZ_STRING_PRODUCT},
    {(uint8_t*)Composite_StringSerial, Composite_SIZ_STRING_SERIAL}
};

/* Extern variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Extern function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*CustomHID_SetReport_Feature function prototypes*/
uint8_t *CustomHID_SetReport_Feature(uint16_t Length);

extern unsigned char Bot_State;
extern Bulk_Only_CBW CBW;
uint32_t Max_Lun = 0;


/**
  * @brief  Handle the Get Max Lun request.
  * @param  uint16_t Length.
  * @retval None.
  */
uint8_t *Get_Max_Lun(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = LUN_DATA_LENGTH;
        return 0;
    }
    else
    {
        return ((uint8_t*)(&Max_Lun));
    }
}

/**
  * @brief  Custom HID init routine.
  * @retval None.
  */
void CustomHID_init(void)
{
    /* Update the serial number string descriptor with the data from the unique ID*/
    Get_SerialNum();

    pInformation->Current_Configuration = 0;
    
    /* Connect the device */
    PowerOn();

    /* Perform basic device initialization operations */
    USB_SIL_Init();

    bDeviceState = UNCONNECTED;
}

/**
  * @brief  Custom HID reset routine.
  * @retval None.
  */
void CustomHID_Reset(void)
{
    /* Set Composite_DEVICE as not configured */
    pInformation->Current_Configuration = 0;
    pInformation->Current_Interface = 0;/*the default Interface*/

    /* Current Feature initialization */
    pInformation->Current_Feature = Composite_ConfigDescriptor[7];

    SetBTABLE(BTABLE_ADDRESS);

    /* Initialize Endpoint 0 */
    SetEPType(ENDP0, EP_CONTROL);
    SetEPTxStatus(ENDP0, EP_TX_STALL);
    SetEPRxAddr(ENDP0, ENDP0_RXADDR);
    SetEPTxAddr(ENDP0, ENDP0_TXADDR);
    Clear_Status_Out(ENDP0);
    SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
    SetEPRxValid(ENDP0);

    /* Initialize Endpoint 1 */
    SetEPType(ENDP1, EP_INTERRUPT);
    SetEPTxAddr(ENDP1, ENDP1_TXADDR);
    SetEPRxAddr(ENDP1, ENDP1_RXADDR);
    SetEPTxCount(ENDP1, 64);
    SetEPRxCount(ENDP1, 64);
    SetEPRxStatus(ENDP1, EP_RX_VALID);
    SetEPTxStatus(ENDP1, EP_TX_NAK);

    /* Initialize Endpoint 2 IN */
    SetEPType(ENDP2, EP_BULK);
    SetEPTxCount(ENDP2, 64);
    SetEPTxAddr(ENDP2, ENDP2_TXADDR);
    SetEPTxStatus(ENDP2, EP_TX_NAK);

    /* Initialize Endpoint 2 OUT */
    SetEPType(ENDP2, EP_BULK);
    SetEPRxAddr(ENDP2, ENDP2_RXADDR);
    SetEPRxCount(ENDP2, 64);
    SetEPRxStatus(ENDP2, EP_RX_VALID);

    /* Set this device to response on default address */
    SetDeviceAddress(0);
    CBW.dSignature = BOT_CBW_SIGNATURE;
    Bot_State = BOT_IDLE;
    bDeviceState = ATTACHED;
}
/**
  * @brief  Update the device state to configured and command the ADC
  *         conversion.
  * @retval None.
  */
void CustomHID_SetConfiguration(void)
{
    if (pInformation->Current_Configuration != 0)
    {
        /* Device configured */
        bDeviceState = CONFIGURED;

        /* Start ADC Software Conversion */
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        ClearDTOG_TX(ENDP2);
        ClearDTOG_RX(ENDP2);
        Bot_State = BOT_IDLE; /* set the Bot state machine to the IDLE state */
    }
}

/**
  * @brief  Update the device state to addressed.
  * @retval None.
  */
void CustomHID_SetDeviceAddress(void)
{
    bDeviceState = ADDRESSED;
}
/**
  * @brief  CustomHID status IN routine.
  * @retval None.
  */
void CustomHID_Status_In(void)
{
}

/**
  * @brief  CustomHID status OUT routine.
  * @retval None.
  */
void CustomHID_Status_Out(void)
{
}

/**
  * @brief  Handle the data class specific requests.
  * @param  Request Nb.
  * @retval USB_UNSUPPORT or USB_SUCCESS.
  */
RESULT CustomHID_Data_Setup(uint8_t RequestNo)
{
    uint8_t *(*CopyRoutine)(uint16_t);

    if (pInformation->USBwIndex != 0)
    {
        return USB_UNSUPPORT;
    }

    CopyRoutine = NULL;

    if ((RequestNo == GET_DESCRIPTOR) && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT)))
    {

        if (pInformation->USBwValue1 == REPORT_DESCRIPTOR)
        {
            CopyRoutine = CustomHID_GetReportDescriptor;
        }
        else if (pInformation->USBwValue1 == HID_DESCRIPTOR_TYPE)
        {
            CopyRoutine = CustomHID_GetHIDDescriptor;
        }

    } /* End of GET_DESCRIPTOR */

    /*** GET_PROTOCOL, GET_REPORT, SET_REPORT ***/
    else if ( (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT)) )
    {
        switch ( RequestNo )
        {
            case GET_PROTOCOL:
                CopyRoutine = CustomHID_GetProtocolValue;
                break;

            case SET_REPORT:
                CopyRoutine = CustomHID_SetReport_Feature;
                Request = SET_REPORT;
                break;

            default:
                break;
        }
    }

    if (CopyRoutine == NULL)
    {
        return USB_UNSUPPORT;
    }

    pInformation->Ctrl_Info.CopyData = CopyRoutine;
    pInformation->Ctrl_Info.Usb_wOffset = 0;
    (*CopyRoutine)(0);
    return USB_SUCCESS;
}

/**
  * @brief  Set Feature request handling
  * @param  Length.
  * @retval Buffer
  */
uint8_t *CustomHID_SetReport_Feature(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = 2;
        return NULL;
    }
    else
    {
        return Report_Buf;
    }
}

/**
  * @brief  handle the no data class specific requests
  * @param  Request Nb.
  * @retval USB_UNSUPPORT or USB_SUCCESS.
  */
RESULT CustomHID_NoData_Setup(uint8_t RequestNo)
{
    if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT)) && (RequestNo == SET_PROTOCOL))
    {
        return CustomHID_SetProtocol();
    }

    else
    {
        return USB_UNSUPPORT;
    }
}

/**
  * @brief  Gets the device descriptor.
  * @param  Length
  * @retval The address of the device descriptor.
  */
uint8_t *CustomHID_GetDeviceDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/**
  * @brief  Gets the configuration descriptor.
  * @param  Length
  * @retval The address of the configuration descriptor.
  */
uint8_t *CustomHID_GetConfigDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/**
  * @brief  Gets the string descriptors according to the needed index
  * @param  Length
  * @retval The address of the string descriptors.
  */
uint8_t *CustomHID_GetStringDescriptor(uint16_t Length)
{
    uint8_t wValue0 = pInformation->USBwValue0;

    if (wValue0 >= 4)
    {
        return NULL;
    }
    else
    {
        return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
    }
}

/**
  * @brief  Gets the HID report descriptor.
  * @param  Length
  * @retval The address of the configuration descriptor.
  */
uint8_t *CustomHID_GetReportDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &CustomHID_Report_Descriptor);
}

/**
  * @brief  Gets the HID descriptor.
  * @param  Length
  * @retval The address of the configuration descriptor.
  */
uint8_t *CustomHID_GetHIDDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &CustomHID_Hid_Descriptor);
}

/**
  * @brief  tests the interface and the alternate setting according to the
  *         supported one.
  * @param  Interface : interface number.
  * @param  AlternateSetting : Alternate Setting number.
  * @retval USB_SUCCESS or USB_UNSUPPORT.
  */
RESULT CustomHID_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
    if (AlternateSetting > 0)
    {
        return USB_UNSUPPORT;
    }
    else if (Interface > 0)
    {
        return USB_UNSUPPORT;
    }

    return USB_SUCCESS;
}

/**
  * @brief  Joystick Set Protocol request routine.
  * @retval USB SUCCESS.
  */
RESULT CustomHID_SetProtocol(void)
{
    uint8_t wValue0 = pInformation->USBwValue0;
    ProtocolValue = wValue0;
    return USB_SUCCESS;
}

/**
  * @brief  get the protocol value
  * @param  Length.
  * @retval address of the protocol value.
  */
uint8_t *CustomHID_GetProtocolValue(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = 1;
        return NULL;
    }
    else
    {
        return (uint8_t *)(&ProtocolValue);
    }
}

/**
  * @brief  Clear feature
  * @retval None.
  */
void CustomHID_ClearFeature(void)
{
    if (CBW.dSignature != BOT_CBW_SIGNATURE)
    {
        Bot_Abort(BOTH_DIR);
    }
}

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/

