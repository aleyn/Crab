/******************** Copyright wisearm.com *********************************
* File Name         : usbd_desc.c
* Author            : Îâ´´Ã÷(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-16
* Description       : USB
********************************************************************************/

#include "usbd_desc.h"

USBD_DEVICE USR_desc =
{
  USBD_USR_DeviceDescriptor,
  USBD_USR_LangIDStrDescriptor, 
  USBD_USR_ManufacturerStrDescriptor,
  USBD_USR_ProductStrDescriptor,
  USBD_USR_SerialStrDescriptor,
  USBD_USR_ConfigStrDescriptor,
  USBD_USR_InterfaceStrDescriptor,
  USBD_USR_QualifierDescriptor,
};

const TStandardDeviceDescriptor  USBD_DeviceDesc =
{
  USB_DEVICE_DESCRIPTOR_LENGTH,                     //u8      bLength;
  USB_DEVICE_DESCRIPTOR,                            //u8      bDescriptorType;
  USB_DEVICE_VERSION_20,                            //u16     bcdUSB;
  0x00,                                             //u8      bDeviceClass;
  0x00,                                             //u8      bDeviceSubClass;
  0x00,                                             //u8      bDeviceProtocol;
  USB_OTG_MAX_EP0_SIZE,                             //u8      bMaxPacketSize;
  USB_GAP_VID,                                      //u16     idVendor;
  USB_GAP_PID,                                      //u16     idProduct;
  0x0101,                                           //u16     bcdDevice;
  USBD_IDX_MFC_STR,                                 //u8      iManufacturer;
  USBD_IDX_PRODUCT_STR,                             //u8      iProduct;
  USBD_IDX_SERIAL_STR,                              //u8      iSerialNumber;
  USBD_CFG_MAX_NUM                                  //u8      bNumConfigurations;
};

const TStandardLangDescriptor USBD_LangIDDesc = 
{
  USB_STD_LNG_DESCRIPTOR_LENGTH,                    //u8      bLength;
  USB_STRING_DESCRIPTOR,                            //u8      bDescriptorType;
  USB_LANGID_EN                                     //u16     wLangID;
};

/* USB Standard Device Descriptor */
const TDeviceQualifierDescriptor  USBD_DeviceQualifierDesc =
{
  USB_QUAL_DESCRIPTOR_LENGTH,                       //u8      bLength;
  USB_DEVICE_QUALIFIER,                             //u8      bDescriptorType;
  USB_DEVICE_VERSION_20,                            //u16     bcdUSB;
  0x00,                                             //u8      bDeviceClass;
  0x00,                                             //u8      bDeviceSubClass;
  0x00,                                             //u8      bDeviceProtocol;
  USB_OTG_MAX_EP0_SIZE,                             //u8      bMaxPacketSize;
  USBD_CFG_MAX_NUM,                                 //u8      bNumConfigurations;
  0x00                                              //u8      bReserved;
};

const TDeviceConfigurationDescriptor USBD_GapDesc =
{
  { //ConfigurationDescriptor
    USB_STD_CFG_DESCRIPTOR_LENGTH,                  //u8      bLength;
    USB_CONFIG_DESCRIPTOR,                          //u8      bDescriptorType;
    sizeof(TDeviceConfigurationDescriptor),         //u16     wTotalLength;
    1,                                              //u8      bNumInterfaces;
    1,                                              //u8      bConfigurationValue;
    0,                                              //u8      iConfiguration;
    0x80,                                           //u8      bmAttributes;
    0xFA //500mA                                    //u8      bMaxPower;
  }, 
  { //InterfaceDescriptor
    USB_STD_IF_DESCRIPTOR_LENGTH,                   //u8      bLength;
    USB_INTERFACE_DESCRIPTOR,                       //u8      bDescriptorType;
    0,                                              //u8      bInterfaceNumber;
    0,                                              //u8      bAlternateSetting;
    5,                                              //u8      bNumEndpoints
    0xFF,                                           //u8      bInterfaceClass;
    0xFF,                                           //u8      bInterfaceSubClass;
    0xFF,                                           //u8      bInterfaceProtocol;
    0                                               //u8      iInterface;
  },
  { //Endpoint 1 In Descriptor
    USB_STD_EP_DESCRIPTOR_LENGTH,                   //u8      bLength;
    USB_ENDPOINT_DESCRIPTOR,                        //u8      bDescriptorType;
    USB_GAP_IN_EP,                                  //u8      bEndpointAddress;
    USB_ENDP_BULK,                                  //u8      bmAttribuates;
    USB_GAP_PACKED_SIZE,                            //u16     wMaxPacketSize;
    0                                               //u8      bInterval;
  }, 
  { //Endpoint 1 Out Descriptor
    USB_STD_EP_DESCRIPTOR_LENGTH,                   //u8      bLength;
    USB_ENDPOINT_DESCRIPTOR,                        //u8      bDescriptorType;
    USB_GAP_OUT_EP,                                 //u8      bEndpointAddress;
    USB_ENDP_BULK,                                  //u8      bmAttribuates;
    USB_GAP_PACKED_SIZE,                            //u16     wMaxPacketSize;
    0                                               //u8      bInterval;
  },
  { //Endpoint 2 In Descriptor
    USB_STD_EP_DESCRIPTOR_LENGTH,                   //u8      bLength;
    USB_ENDPOINT_DESCRIPTOR,                        //u8      bDescriptorType;
    USB_CMD_IN_EP,                                  //u8      bEndpointAddress;
    USB_ENDP_BULK,                                  //u8      bmAttribuates;
    USB_CMD_PACKED_SIZE,                            //u16     wMaxPacketSize;
    0                                               //u8      bInterval;
  },
  { //Endpoint 2 Out Descriptor
    USB_STD_EP_DESCRIPTOR_LENGTH,                   //u8      bLength;
    USB_ENDPOINT_DESCRIPTOR,                        //u8      bDescriptorType;
    USB_CMD_OUT_EP,                                 //u8      bEndpointAddress;
    USB_ENDP_BULK,                                  //u8      bmAttribuates;
    USB_CMD_PACKED_SIZE,                            //u16     wMaxPacketSize;
    0                                               //u8      bInterval;
  },
  { //Endpoint 3 In Descriptor
    USB_STD_EP_DESCRIPTOR_LENGTH,                   //u8      bLength;
    USB_ENDPOINT_DESCRIPTOR,                        //u8      bDescriptorType;
    USB_LOG_IN_EP,                                  //u8      bEndpointAddress;
    USB_ENDP_BULK,                                  //u8      bmAttribuates;
    USB_LOG_PACKED_SIZE,                            //u16     wMaxPacketSize;
    0                                               //u8      bInterval;
  }
};

const TStandardStringRequest USBD_StringDesc = 
{
    "WiseArm Lab.",                                 // Manufacturer
    "WiseArm UsbGap Device",                        // Product
    "CB20161103",                                   // Serial
    "UsbGap Config",                                // Configuration
    "UsbGap Interface",                             // Interface
};

__ALIGN_BEGIN uint8_t USBD_StrDesc[USB_MAX_STR_DESC_SIZ] __ALIGN_END ;

/*******************************************************************************
* Function    : USBD_USR_DeviceDescriptor
* Caption     : .
*  @Param     : 1.speed - 
*  @Param     : 2.length - 
* Return      : uint8_t*
* Description : .
*******************************************************************************/
uint8_t *  USBD_USR_DeviceDescriptor( uint8_t speed , uint16_t *length)
{
  *length = sizeof(USBD_DeviceDesc);
  return (uint8_t*)&USBD_DeviceDesc;
}

/*******************************************************************************
* Function    : USBD_USR_ConfigDescriptor
* Caption     : .
*  @Param     : 1.speed - 
*  @Param     : 2.length - 
* Return      : uint8_t*
* Description : .
*******************************************************************************/
uint8_t *     USBD_USR_ConfigDescriptor (uint8_t speed, uint16_t *length)
{
  *length = sizeof (USBD_GapDesc);
  return (uint8_t  *)&USBD_GapDesc;
}

/*******************************************************************************
* Function    : USBD_USR_QualifierDescriptor
* Caption     : .
*  @Param     : 1.speed - 
*  @Param     : 2.length - 
* Return      : uint8_t*
* Description : .
*******************************************************************************/
uint8_t *  USBD_USR_QualifierDescriptor( uint8_t speed , uint16_t *length)
{
  *length = sizeof(USBD_DeviceQualifierDesc);
  return (uint8_t*)&USBD_DeviceQualifierDesc;
}

/*******************************************************************************
* Function    : USBD_USR_LangIDStrDescriptor
* Caption     : .
*  @Param     : 1.speed - 
*  @Param     : 2.length - 
* Return      : uint8_t*
* Description : .
*******************************************************************************/
uint8_t *  USBD_USR_LangIDStrDescriptor( uint8_t speed , uint16_t *length)
{
  *length =  sizeof(USBD_LangIDDesc);  
  return (uint8_t*)&USBD_LangIDDesc;
}

/*******************************************************************************
* Function    : USB_GetString
* Caption     : .
*  @Param     : 1.desc - 
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t USB_GetString(uint8_t *desc)
{
  uint8_t idx;
  
  if (desc != NULL) 
  { 
    idx = 2;
    
    while (*desc != 0) 
    {
      USBD_StrDesc[idx++] = *desc++;
      USBD_StrDesc[idx++] =  0x00;
    }
    
    USBD_StrDesc[0] = idx;
    USBD_StrDesc[1] = USB_STRING_DESCRIPTOR;
    
    return idx;
  }
  else
  {
    return 0;
  }
}

/*******************************************************************************
* Function    : USBD_USR_ProductStrDescriptor
* Caption     : .
*  @Param     : 1.speed - 
*  @Param     : 2.length - 
* Return      : uint8_t*
* Description : .
*******************************************************************************/
uint8_t *  USBD_USR_ProductStrDescriptor( uint8_t speed , uint16_t *length)
{
  *length = USB_GetString(USBD_StringDesc.Product);
  return USBD_StrDesc;
}

/*******************************************************************************
* Function    : USBD_USR_ManufacturerStrDescriptor
* Caption     : .
*  @Param     : 1.speed - 
*  @Param     : 2.length - 
* Return      : uint8_t*
* Description : .
*******************************************************************************/
uint8_t *  USBD_USR_ManufacturerStrDescriptor( uint8_t speed , uint16_t *length)
{
  *length = USB_GetString(USBD_StringDesc.Manufacturer);
  return USBD_StrDesc;
}

/*******************************************************************************
* Function    : USBD_USR_SerialStrDescriptor
* Caption     : .
*  @Param     : 1.speed - 
*  @Param     : 2.length - 
* Return      : uint8_t*
* Description : .
*******************************************************************************/
uint8_t *  USBD_USR_SerialStrDescriptor( uint8_t speed , uint16_t *length)
{
  *length = USB_GetString(USBD_StringDesc.Serial);
  return USBD_StrDesc;  
}

/*******************************************************************************
* Function    : USBD_USR_ConfigStrDescriptor
* Caption     : .
*  @Param     : 1.speed - 
*  @Param     : 2.length - 
* Return      : uint8_t*
* Description : .
*******************************************************************************/
uint8_t *  USBD_USR_ConfigStrDescriptor( uint8_t speed , uint16_t *length)
{
  *length = USB_GetString(USBD_StringDesc.Configuration);
  return USBD_StrDesc;  
}

/*******************************************************************************
* Function    : USBD_USR_InterfaceStrDescriptor
* Caption     : .
*  @Param     : 1.speed - 
*  @Param     : 2.length - 
* Return      : uint8_t*
* Description : .
*******************************************************************************/
uint8_t *  USBD_USR_InterfaceStrDescriptor( uint8_t speed , uint16_t *length)
{
  *length = USB_GetString(USBD_StringDesc.Interface);
  return USBD_StrDesc;  
}
