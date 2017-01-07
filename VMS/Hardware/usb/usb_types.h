/******************** Copyright wisearm.com *********************************
* File Name         : usb_type.h
* Author            : Îâ´´Ã÷(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2008-09-08
* Last Update       : 2016-10-17
* Description       : USB Device firmware library.
********************************************************************************/
#ifndef __USB_TYPES_H
#define __USB_TYPES_H

#define  USB_CONTROLSTATE_MASK      0xF0
#define  USB_CONTROLSTATE_SUBMASK   0x0F
#define  USB_DEVICE_VERSION_20      0x0200
#define  USB_DEVICE_VERSION_11      0x0110
#define  USB_LANGID_EN              0x0409

#define  USB_CS_INTERFACE           0x24
#define  USB_CS_ENDPOINT            0x25

#define  USB_IDX_LANGID_STR         0x00 
#define  USB_IDX_MFC_STR            0x01 
#define  USB_IDX_PRODUCT_STR        0x02
#define  USB_IDX_SERIAL_STR         0x03 
#define  USB_IDX_CONFIG_STR         0x04 
#define  USB_IDX_INTERFACE_STR      0x05 


typedef enum USB_RECIPIENT_ENUM
{
  USB_RECIPIENT_DEVICE    = 0,
  USB_RECIPIENT_INTERFACE = 1,
  USB_RECIPIENT_ENDPOINT  = 2,
  USB_RECIPIENT_OTHER     = 3
} USB_RECIPIENT_T;

typedef enum USB_REQUESTTYPE_ENUM
{
  USB_REQUEST_STANDARD    = 0,
  USB_REQUEST_CLASS       = 1,
  USB_REQUEST_VENDOR      = 2
} USB_REQUEST_T;

typedef enum USB_REQUESTDIR_ENUM
{
  USB_HOSTTODEVICE        = 0,
  USB_DEVICETOHOST        = 1
} USB_REQUESTDIR_T;

#define USB_STANDARD_REQUESTS_MAX 13

typedef enum USB_STANDARD_REQUESTS_ENUM
{
  USB_GET_STATUS             = 0,
  USB_CLEAR_FEATURE          = 1,
  USB_STD_RESERVED1          = 2,  //Res
  USB_SET_FEATURE            = 3, 
  USB_STD_RESERVED2          = 4,  //Res
  USB_SET_ADDRESS            = 5,
  USB_GET_DESCRIPTOR         = 6,
  USB_SET_DESCRIPTOR         = 7,
  USB_GET_CONFIGURATION      = 8,
  USB_SET_CONFIGURATION      = 9,
  USB_GET_INTERFACE          = 10,
  USB_SET_INTERFACE          = 11,
  USB_SYNCH_FRAME            = 12
} USB_STANDARD_REQUESTS_T;

typedef enum USB_DESCRIPTOR_ENUM
{
  USB_DEVICE_DESCRIPTOR       = 1,
  USB_CONFIG_DESCRIPTOR       = 2,
  USB_STRING_DESCRIPTOR       = 3,
  USB_INTERFACE_DESCRIPTOR    = 4,
  USB_ENDPOINT_DESCRIPTOR     = 5,
  USB_DEVICE_QUALIFIER        = 6,
  USB_OTHER_DESCRIPTOR        = 7,
  USB_INTERFACE_POWER         = 8,
  USB_HID_DESCRIPTOR          = 33,
  USB_REPORT_DESCRIPTOR       = 34
} USB_USB_DESCRIPTOR_T;

#ifdef USB_OTG_LIB
typedef enum USB_FEATURE_SELECTOR_ENUM
{
  ENDPOINT_STALL          = 0,
  DEVICE_REMOTE_WAKEUP    = 1
  //TEST_MODE               = 2
} USB_FEATURE_SELECTOR_T;
#endif

typedef enum USB_CONTROLSTATE_ENUM
{
  USB_CS_WAITFORSETUP     = 0x00,
  USB_CS_PAUSE            = 0x01,
  USB_CS_SUSPEND          = 0x02,
  USB_CS_RESUME           = 0x03,
  USB_CS_STALLED          = 0x04,
  USB_CS_SETUPIN          = 0x05,
  USB_CS_SETUPOUT         = 0x06,
  USB_CS_SETUPLAST        = 0x07,
  USB_CS_DATALAST         = 0x08,
  USB_CS_SETADDRESS       = 0x09,
  USB_CS_DATAIN           = 0x10,
  USB_CS_DATAOUT          = 0x20,
  USB_CS_OTHER            = 0x40,
  USB_CS_SETUP            = 0x80,
} USB_CONTROLSTATE_T;

typedef enum USB_ENDPOINT_ENUM
{
  USB_ENDP_CONTROL        = 0,
  USB_ENDP_ISO            = 1,
  USB_ENDP_BULK           = 2,
  USB_ENDP_INTERRUPT      = 3
} USB_ENDPOINT_T;

#ifdef USB_OTG_LIB
typedef enum USB_RESULT_ENUM
{
  USB_SUCCESS = 0,    /* Process sucessfully */
  USB_ERROR,
  USB_UNSUPPORT,
  USB_NOT_READY       /* The process has not been finished, endpoint will be
                         NAK to further rquest */
} USB_RESULT_T;
#endif

typedef enum USB_RESUME_ENUM
{
  USB_RESUME_EXTERNAL,
  USB_RESUME_INTERNAL,
  USB_RESUME_LATER,
  USB_RESUME_WAIT,
  USB_RESUME_START,
  USB_RESUME_ON,
  USB_RESUME_OFF,
  USB_RESUME_ESOF
} USB_RESUMESTATE_T;

#define USB_DEVICE_DESCRIPTOR_LENGTH  sizeof(TStandardDeviceDescriptor)
typedef __packed struct
{
  uint8_t      bLength;
  uint8_t      bDescriptorType;
  uint16_t     bcdUSB;
  uint8_t      bDeviceClass;
  uint8_t      bDeviceSubClass;
  uint8_t      bDeviceProtocol;
  uint8_t      bMaxPacketSize;
  uint16_t     idVendor;
  uint16_t     idProduct;
  uint16_t     bcdDevice;
  uint8_t      iManufacturer;
  uint8_t      iProduct;
  uint8_t      iSerialNumber;
  uint8_t      bNumConfigurations;
} TStandardDeviceDescriptor;  // size = 18


#define USB_QUAL_DESCRIPTOR_LENGTH sizeof(TDeviceQualifierDescriptor)
typedef __packed struct
{
  uint8_t      bLength;
  uint8_t      bDescriptorType;
  uint16_t     bcdUSB;
  uint8_t      bDeviceClass;
  uint8_t      bDeviceSubClass;
  uint8_t      bDeviceProtocol;
  uint8_t      bMaxPacketSize;
  uint8_t      bNumConfigurations;
  uint8_t      bReserved;
} TDeviceQualifierDescriptor;  // size = 10


#define USB_STD_CFG_DESCRIPTOR_LENGTH  sizeof(TStandardConfigurationDescriptor)
typedef __packed struct
{
  uint8_t      bLength;
  uint8_t      bDescriptorType;
  uint16_t     wTotalLength;
  uint8_t      bNumInterfaces;
  uint8_t      bConfigurationValue;
  uint8_t      iConfiguration;
  uint8_t      bmAttributes;
  uint8_t      bMaxPower;
} TStandardConfigurationDescriptor;  // size = 9


#define USB_STD_IF_DESCRIPTOR_LENGTH sizeof(TStandardInterfaceDescriptor)
typedef __packed struct
{
  uint8_t      bLength;
  uint8_t      bDescriptorType;
  uint8_t      bInterfaceNumber;
  uint8_t      bAlternateSetting;
  uint8_t      bNumEndpoints;
  uint8_t      bInterfaceClass;
  uint8_t      bInterfaceSubClass;
  uint8_t      bInterfaceProtocol;
  uint8_t      iInterface;
} TStandardInterfaceDescriptor;  // size  = 9


#define USB_STD_EP_DESCRIPTOR_LENGTH sizeof(TStandardEndpointDescriptor)
typedef __packed struct
{
  uint8_t      bLength;
  uint8_t      bDescriptorType;
  uint8_t      bEndpointAddress;
  uint8_t      bmAttribuates;
  uint16_t     wMaxPacketSize;
  uint8_t      bInterval;
} TStandardEndpointDescriptor;   // size = 7


#define USB_STD_HID_DESCRIPTOR_LENGTH sizeof(TStandardHidDescriptor)
typedef __packed struct
{
  uint8_t      bLength;
  uint8_t      bDescriptorType;
  uint16_t     bcdHID; 
  uint8_t      bCountryCode;
  uint8_t      bNumDescriptors;
  uint8_t      bHidDescriptorType;
  uint16_t     wHidDescriptorLength;
} TStandardHidDescriptor;   // size = 9


typedef union
{
  struct 
  {
    uint8_t      bRequestRecipient  :5;
    uint8_t      bRequestType       :2;
    uint8_t      bRequestDirection  :1;
  };
  uint8_t        bmRequestType;
} TStandardRequestType;

typedef union
{
  struct 
  {
    uint8_t      bValue0;
    uint8_t      bValue1;
  };
  struct
  {
    uint8_t      bDescriptorIndex;
    uint8_t      bDescriptorType;
  };
  uint16_t       wValue;
} TStandardRequestValue;

typedef union
{
  struct 
  {
    uint8_t      bIndex0;
    uint8_t      bIndex1;
  };
  struct
  {
    uint16_t     bEndpointID     :4;
    uint16_t     bSRI_Reserved1  :3;
    uint16_t     bEndpointDir    :1;
    uint16_t     bSRI_Reserved2  :8;
  };
  struct
  {
    uint8_t      bInterfaceID;
    uint8_t      bSRI_Reserved3;
  };
  uint16_t       wIndex;
  uint16_t       wLanguageID;
} TStandardRequestIndex;

typedef __packed struct
{
  TStandardRequestType                 ;
  uint8_t                      bRequest;
  TStandardRequestValue                ;
  TStandardRequestIndex                ;
  uint16_t                     wLength ;
} TStandardRequests;

typedef __packed struct
{
  uint8_t*     pAddress;
  union
  {
    uint8_t    bType;
    uint8_t    bIndex;
  };
  uint8_t      bLength;
} TStandardDescriptorRequest;

typedef __packed struct
{
  uint8_t      Feature;
  uint8_t      Configuration;
  uint8_t      Interface;
  uint8_t      AlternateSetting;
} TStandardDeviceConfig;

#define USB_STD_LNG_DESCRIPTOR_LENGTH sizeof(TStandardLangDescriptor)
typedef __packed struct
{
  uint8_t      bLength;
  uint8_t      bDescriptorType;
  uint16_t     wLangID;
} TStandardLangDescriptor;

typedef __packed struct   /*Functional Descriptor*/
{
  uint8_t      bLength;
  uint8_t      bDescriptorType;
  uint8_t      bDescriptorSubtype;
  uint8_t      bParam1;
} TCdcFunctionDescriptor1;

typedef __packed struct   /*Functional Descriptor*/
{
  uint8_t      bLength;
  uint8_t      bDescriptorType;
  uint8_t      bDescriptorSubtype;
  uint8_t      bParam1;
  uint8_t      bParam2;
} TCdcFunctionDescriptor2;

typedef __packed union
{
  struct
  {
  uint8_t     *Manufacturer;
  uint8_t     *Product;
  uint8_t     *Serial;
  uint8_t     *Configuration;
  uint8_t     *Interface;
  };
  uint8_t     *List[5];
} TStandardStringRequest;

#endif
/*******************************************************************************
**                                END OF FILE                                 **
*******************************************************************************/
