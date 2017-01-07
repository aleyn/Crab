/******************** Copyright wisearm.com *********************************
* File Name         : usbd_desc.h
* Author            : Îâ´´Ã÷(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-16
* Description       : USB
********************************************************************************/

#ifndef __USB_DESC_H
#define __USB_DESC_H

/* Includes ------------------------------------------------------------------*/
#include "usb_conf.h"
#include "usbd_req.h"
#include "usb_types.h"

#define USB_GAP_VID                             0x2282
#define USB_GAP_PID                             0x902C
#define USB_SIZ_DEVICE_DESC                     18
#define USB_GAP_IN_EP                           0x81
#define USB_GAP_OUT_EP                          0x01
#define USB_CMD_IN_EP                           0x82
#define USB_CMD_OUT_EP                          0x02
#define USB_LOG_IN_EP                           0x83
#define USB_GAP_PACKED_SIZE                     64
#define USB_CMD_PACKED_SIZE                     8
#define USB_LOG_PACKED_SIZE                     64
#define USB_MAX_STR_DESC_SIZ                    64
#define USB_MAX_EP0_SIZE                        64

    
typedef __packed struct
{
  TStandardConfigurationDescriptor   ConfigurationDescriptor;
  TStandardInterfaceDescriptor       InterfaceDescriptor;
  TStandardEndpointDescriptor        Endpoint1InDescriptor;
  TStandardEndpointDescriptor        Endpoint1OutDescriptor;
  TStandardEndpointDescriptor        Endpoint2InDescriptor;
  TStandardEndpointDescriptor        Endpoint2OutDescriptor;
  TStandardEndpointDescriptor        Endpoint3InDescriptor;
} TDeviceConfigurationDescriptor;
    
extern const TStandardDeviceDescriptor      USBD_DeviceDesc;
extern const TDeviceQualifierDescriptor     USBD_DeviceQualifierDesc;
extern const TStandardLangDescriptor        USBD_LangIDDesc;
extern const TDeviceConfigurationDescriptor USBD_GapDesc;

extern  uint8_t USBD_StrDesc[USB_MAX_STR_DESC_SIZ];
extern  USBD_DEVICE USR_desc; 

uint8_t *     USBD_USR_DeviceDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_ConfigDescriptor (uint8_t speed, uint16_t *length);
uint8_t *     USBD_USR_LangIDStrDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_ManufacturerStrDescriptor ( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_ProductStrDescriptor ( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_SerialStrDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_ConfigStrDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_InterfaceStrDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_QualifierDescriptor( uint8_t speed , uint16_t *length);

#ifdef USB_SUPPORT_USER_STRING_DESC
uint8_t *     USBD_USR_USRStringDesc (uint8_t speed, uint8_t idx , uint16_t *length);  
#endif /* USB_SUPPORT_USER_STRING_DESC */  

#endif /* __USBD_DESC_H */

