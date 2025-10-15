/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_desc.c
* @brief:     Descriptors for Custom HID Demo.
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
const uint8_t CustomHID_DeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC] =
{
    0x12,                       /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
    0x00,                       /*bcdUSB */
    0x02,
    0x00,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize40*/
    0x70,                       /* idVendor */
    0x34,
    0x06,                       /* idProduct */
    0x00,
    0x00,                       /*bcdDevice rel. 2.00*/
    0x02,
    1,                          /*Index of string descriptor describing
                                              manufacturer */
    2,                          /*Index of string descriptor describing
                                             product*/
    3,                          /*Index of string descriptor describing the
                                             device serial number */
    0x01                        /*bNumConfigurations*/
}
; /* CustomHID_DeviceDescriptor */


/* USB Configuration Descriptor */

/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t CustomHID_ConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC] =
{
    0x09, /* bLength: Configuration Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    CUSTOMHID_SIZ_CONFIG_DESC,
    
    /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /* bNumInterfaces: 1 interface */
    0x01,         /* bConfigurationValue: Configuration value */
    0x00,         /* iConfiguration: Index of string descriptor describing
                                 the configuration*/
    0xC0,         /* bmAttributes: Self powered */
    0x32,         /* MaxPower 100 mA: this current is used for detecting Vbus */

    /************** Descriptor of Custom HID interface ****************/
    
    /* 09 */
    0x09,         /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,/* bDescriptorType: Interface descriptor type */
    0x00,         /* bInterfaceNumber: Number of Interface */
    0x00,         /* bAlternateSetting: Alternate setting */
    0x02,         /* bNumEndpoints */
    0x03,         /* bInterfaceClass: HID */
    0x00,         /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x00,         /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,            /* iInterface: Index of string descriptor */
    
    /******************** Descriptor of Custom HID HID ********************/
    
    /* 18 */
    0x09,         /* bLength: HID Descriptor size */
    HID_DESCRIPTOR_TYPE, /* bDescriptorType: HID */
    0x10,         /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,         /* bCountryCode: Hardware target country */
    0x01,         /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,         /* bDescriptorType */
    CUSTOMHID_SIZ_REPORT_DESC,/* wItemLength: Total length of Report descriptor */
    0x00,
    
    /******************** Descriptor of Custom HID endpoints ******************/
    
    /* 27 */
    0x07,          /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: */

    0x81,          /* bEndpointAddress: Endpoint Address (IN) */
    0x03,          /* bmAttributes: Interrupt endpoint */
    REPORT_COUNT,          /* wMaxPacketSize: 2 Bytes max */
    0x00,
    0x20,          /* bInterval: Polling Interval (32 ms) */
    
    /* 34 */

    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: */
    
    /*  Endpoint descriptor type */
    0x01,   /* bEndpointAddress: */
    
    /*  Endpoint Address (OUT) */
    0x03,   /* bmAttributes: Interrupt endpoint */
    REPORT_COUNT,   /* wMaxPacketSize: 2 Bytes max  */
    0x00,
    0x20,   /* bInterval: Polling Interval (20 ms) */
    
    /* 41 */
}; /* CustomHID_ConfigDescriptor */

const uint8_t CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC] =
{
    //0x05, 0x8c,                                           // USAGE_PAGE (ST Page),Global project, specify user functions, where 0x8c represents Bar Code Scanner Page. It is recommended to change it to 0xFF (user-defined)
    
    0x05, 0xff,
    0x09, 0x00,                                             // USAGE (Demo Kit), Usage index value, indicating the recommended usage for an item or collectio
    0xa1, 0x01,                                             // COLLECTION (Application), This is a main project, set. 0x01 indicates that this is an application set, and the properties are defined by the previous purpose page as user-defined

    /*The Input report*/
    0x09, 0x01,                                             // USAGE ID - Vendor defined
    0x15, 0x00,                                             // LOGICAL_MINIMUM (0) ,Global project, with a minimum logical value of 0

    0x26, 0x00, 0xFF,                                       // LOGICAL_MAXIMUM (255) ,Global project, with a maximum logical value of 255
    0x75, 0x08,                                             // REPORT_SIZE (8bit) ,Global project, each data field has a length of 8 bits, which is one byte
    0x95, REPORT_COUNT,                                     // REPORT_COUNT (64Byte), Global project, with a data field length of 64 bytes
    0x81, 0x02,                                             // INPUT (Data,Var,Abs), Main project, define input list, the host uses this information to parse 
                                                            // the data provided by the device (define an input report that receives two bytes from the device)

    /*The Output report*/
    0x09, 0x02,                                             // USAGE ID - Vendor defined
    0x15, 0x00,                                             // LOGICAL_MINIMUM (0) ,Global project, with a minimum logical value of 0
    0x26, 0x00, 0xFF,                                       // LOGICAL_MAXIMUM (255),Global project, with a maximum logical value of 255
    0x75, 0x08,                                             // REPORT_SIZE (8bit),Global project, each data field has a length of 8 bits, which is one byte
    0x95, REPORT_COUNT,                                     // REPORT_COUNT (64Byte), Global project, with a data field length of 64 bytes
    0x91, 0x02,                                             // OUTPUT (Data,Var,Abs) ,Main project, create output report (define an output report that sends 2 bytes to the device)

    0xc0                                                    //END_COLLECTION ,This main project is used to close the previous collection
}; /* CustomHID_ReportDescriptor */

/* USB String Descriptors (optional) */
const uint8_t CustomHID_StringLangID[CUSTOMHID_SIZ_STRING_LANGID] =
{
    CUSTOMHID_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
}
; /* LangID = 0x0409: U.S. English */

const uint8_t CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR] =
{
    CUSTOMHID_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    
    /* Manufacturer: "HKMicroelectronics" */
    'H', 0, 'K', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
    'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
    'c', 0, 's', 0
};

const uint8_t CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT] =
{
    CUSTOMHID_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'H', 0, 'K', 0, '3', 0, '2', 0, ' ', 0, 'C', 0,
    'u', 0, 's', 0, 't', 0, 'm', 0, ' ', 0, 'H', 0, 'I', 0,
    'D', 0
};
uint8_t CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL] =
{
    CUSTOMHID_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'H', 0, 'K', 0, '3', 0, '2', 0
};

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/

