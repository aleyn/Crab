/******************** Copyright wisearm.com *********************************
* File Name         : usbd_gap.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-16
* Description       : USB
*******************************************************************************/
#ifndef __USB_GAP_H_
#define __USB_GAP_H_

#include "stm32ext.h"
#include "usbd_ioreq.h"
#include "usbd_desc.h"
#include "usbd_req.h"
#include "usb_dcd_int.h"
#include "gap.h"
#include "string.h"

#define USBGAP_FAILD           0x00    
#define USBGAP_SUCCESS         0x01
        
#define USBGAP_ID              0x01

#define USBGAP_LOG_DISABLE     0x00
#define USBGAP_LOG_ENABLE      0x01

#define USBGAP_LOG_LIST_COUNT   20
#define USBGAP_LOG_BUFFER_SIZE  2048
    
typedef struct
{
  uint8_t   ID;          //USBGAP-ID
  uint8_t   Status;      //状态
  uint16_t  Res;         //保留
  uint16_t  GapLiveLen;  //GAP剩余长度
  uint16_t  LogLiveLen;  //LOG剩余长度
} USB_GAP_Status_TypeDef;

typedef struct
{
  uint8_t   Query;     //主机查询
  uint8_t   Res;       //保留
  uint16_t  Param1;    //参数1
  uint16_t  Param2;    //参数2
  uint16_t  Param3;    //参数3
} USB_GAP_CMD_TypeDef;
  
extern GapByte  GapBuffer[];

void USB_HW_DeInit();
void USB_HW_Init();
void USB_InitDevice();
void USB_Enable();

extern void USB_OnDecodeGap();
extern void USB_OnRunScript(uint8_t State);

uint8_t USB_ReceiveSuccess();
void USB_ReceiveComplete(uint8_t State);
void USB_TransmitComplete(uint8_t State, uint16_t Size);

void Log(char* fmt, ...);
void Logc(char* fmt, ...);
void Log_Command(uint8_t Status);
uint8_t Log_Check(char **Buf, uint16_t MaxCount);
void Log_Add(uint16_t Offset, uint16_t Count);

#endif
/*****END OF FILE****/
