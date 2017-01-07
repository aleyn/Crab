/******************** Copyright wisearm.com *********************************
* File Name         : usbd_gap.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-16
* Description       : USB
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usbd_gap.h"
#include <stdio.h>
#include <stdarg.h>

__ALIGN_BEGIN uint32_t  usbd_gap_AltSet  __ALIGN_END = 0;
__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END ;

#define USBGAP_CMD_SCRIPT      0xA1
#define USBGAP_CMD_LOG         0xB2
#define USBGAP_CMD_RELOADGAP   0xC3
#define USBGAP_CMD_RELOADLOG   0xD4
    
#define USBGAP_DATA_NULL        0x00
#define USBGAP_DATA_STANDBY     0x01
#define USBGAP_DATA_READY       0x02
#define USBGAP_DATA_OVERRAM     0x03
#define USBGAP_DATA_ERROR       0x04
#define USBGAP_DATA_SUCCESS     0x05

GapByte   GapBuffer[GAP_ENCODE_SIZE];

uint8_t   LogBuffer[USBGAP_LOG_BUFFER_SIZE];
uint16_t  LogPos[USBGAP_LOG_LIST_COUNT];
uint16_t  LogLen[USBGAP_LOG_LIST_COUNT];
uint16_t  LogReadIndex;
uint16_t  LogWriteIndex;
uint16_t  LogWritePos;
uint8_t   LogEnable;

uint8_t   USB_Tx_Flag;
uint16_t  USB_Tx_Count;
uint8_t   USB_Rx_Flag;
uint16_t  USB_Rx_Count;

uint8_t*  USB_Tx_Buffer; 
uint8_t*  USB_Rx_Buffer;
uint8_t*  USB_Log_Buffer;

//uint16_t  USB_Log_Count;
uint8_t   USB_Log_Flag;

USB_GAP_Status_TypeDef   UsbGap_Status;
USB_GAP_CMD_TypeDef      UsbGap_Cmd;

//extern CrabByte          ScriptFlag;

/*********************************************
   GAP Device library callbacks
 *********************************************/
uint8_t  usbd_gap_Init        (void *pdev, uint8_t cfgidx);
uint8_t  usbd_gap_DeInit      (void *pdev, uint8_t cfgidx);
uint8_t  usbd_gap_Setup       (void *pdev, USB_SETUP_REQ *req);
uint8_t  usbd_gap_EP0_RxReady (void *pdev);
uint8_t  usbd_gap_DataIn      (void *pdev, uint8_t epnum);
uint8_t  usbd_gap_DataOut     (void *pdev, uint8_t epnum);
uint8_t  usbd_gap_SOF         (void *pdev);

void USB_UpdateStatus();
void USB_PrepareGap();
void USB_ReloadGap();
void USB_ReloadLog();

/*********************************************
   GAP specific management functions
 *********************************************/

void usbd_gap_Command(void);

/* GAP interface class callbacks structure */
USBD_Class_cb_TypeDef  USBD_GAP_cb = 
{
  usbd_gap_Init,
  usbd_gap_DeInit,
  usbd_gap_Setup,
  NULL,                 /* EP0_TxSent, */
  usbd_gap_EP0_RxReady,
  usbd_gap_DataIn,
  usbd_gap_DataOut,
  usbd_gap_SOF,
  NULL,
  NULL,     
  USBD_USR_ConfigDescriptor
};

USBD_Usr_cb_TypeDef USR_cb =
{
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,  
};

void GAP_IN_Callback(void);
void GAP_OUT_Callback(void);
void CMD_IN_Callback(void);
void CMD_OUT_Callback(void);
void LOG_IN_Callback(void);

/*******************************************************************************
* Function    : USB_InitBuffer
* Caption     : .
* Description : .
*******************************************************************************/
void USB_InitDevice()
{
  UsbGap_Status.ID = USBGAP_ID;
  UsbGap_Status.Res = 0;
  UsbGap_Status.Status = 0;
  UsbGap_Status.GapLiveLen = 0;

  USB_Tx_Buffer = (uint8_t*)&GapBuffer;
  USB_Tx_Count = 0;
  USB_Tx_Flag = USBGAP_DATA_NULL;

  USB_Rx_Buffer = (uint8_t*)&GapBuffer;
  USB_Rx_Count = 0;
  USB_Rx_Flag = USBGAP_DATA_NULL;
  
  USB_Log_Buffer = (uint8_t*)&LogBuffer;
  UsbGap_Status.LogLiveLen = 0; 
  
  Log_Command(DISABLE);  
  
  //DCD_DevDisconnect(&USB_OTG_dev);  

  USB_HW_Init();
  
  USBD_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USR_desc, 
            &USBD_GAP_cb, 
            &USR_cb);
  
  //DCD_DevDisconnect(&USB_OTG_dev);  
}

/*******************************************************************************
* Function    : usbd_gap_Init
* Caption     : .
*  @Param     : 1.pdev - 
*  @Param     : 2.cfgidx - 
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t  usbd_gap_Init (void  *pdev,
                               uint8_t cfgidx)
{
  //USB_InitBuffer();

  /* Open GAP IN */
  DCD_EP_Open(pdev,
              USB_GAP_IN_EP,
              USB_GAP_PACKED_SIZE,
              USB_OTG_EP_BULK);
  
  /* Open GAP OUT */
  DCD_EP_Open(pdev,
              USB_GAP_OUT_EP,
              USB_GAP_PACKED_SIZE,
              USB_OTG_EP_BULK);
        
  /* Open CMD IN */
  DCD_EP_Open(pdev,
              USB_CMD_IN_EP,
              USB_CMD_PACKED_SIZE,
              USB_OTG_EP_BULK);
  
  /* Open CMD OUT */
  DCD_EP_Open(pdev,
              USB_CMD_OUT_EP,
              USB_CMD_PACKED_SIZE,
              USB_OTG_EP_BULK);

  /* Open LOG IN */
  DCD_EP_Open(pdev,
              USB_LOG_IN_EP,
              USB_LOG_PACKED_SIZE,
              USB_OTG_EP_BULK);
  
  
  /* Prepare Out endpoint to receive next packet */
  DCD_EP_PrepareRx(pdev,
                   USB_CMD_OUT_EP,
                   (unsigned char*)&UsbGap_Cmd,
                   USB_CMD_PACKED_SIZE);
  
  DCD_EP_Tx (&USB_OTG_dev,
             USB_GAP_IN_EP,
             GapBuffer,
             0);

  DCD_EP_Tx (&USB_OTG_dev,
             USB_LOG_IN_EP,
             LogBuffer,
             0);
  
  USB_PrepareGap();
  USB_UpdateStatus();

  return USBD_OK;
}


/*******************************************************************************
* Function    : usbd_gap_DeInit
* Caption     : .
*  @Param     : 1.pdev - 
*  @Param     : 2.cfgidx - 
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t  usbd_gap_DeInit (void  *pdev,
                                 uint8_t cfgidx)
{
  /* Open GAP IN */
  DCD_EP_Close(pdev, USB_GAP_IN_EP);
  
  /* Open GAP OUT */
  DCD_EP_Close(pdev, USB_GAP_OUT_EP);  

  /* Open CMD IN */
  DCD_EP_Close(pdev, USB_CMD_IN_EP);
  
  /* Open EP OUT */
  DCD_EP_Close(pdev, USB_CMD_OUT_EP);
  
  /* Open EP IN */
  DCD_EP_Close(pdev,   USB_LOG_IN_EP);
  
  return USBD_OK;
}


/*******************************************************************************
* Function    : usbd_gap_Setup
* Caption     : .
*  @Param     : 1.pdev - 
*  @Param     : 2.req - 
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t  usbd_gap_Setup (void  *pdev,
                                USB_SETUP_REQ *req)
{
  uint8_t Request = req->bmRequest & USB_REQ_TYPE_MASK;
  
  if (Request == USB_REQ_TYPE_STANDARD)
  {
    switch (req->bRequest)
    {
    case USB_REQ_GET_DESCRIPTOR: 
      USBD_CtlError (pdev, req);
      return USBD_FAIL;
      
    case USB_REQ_GET_INTERFACE :
      USBD_CtlSendData (pdev,
                        (uint8_t *)&usbd_gap_AltSet,
                        1);
      break;
      
    case USB_REQ_SET_INTERFACE :
      if ((uint8_t)(req->wValue) < USBD_ITF_MAX_NUM)
      {
        usbd_gap_AltSet = (uint8_t)(req->wValue);
      }
      else
      {
        /* Call the error management function (command will be nacked */
        USBD_CtlError (pdev, req);
      }
      break;
    }
  }
  else if (Request == USB_REQ_TYPE_CLASS)
  {
      USBD_CtlError (pdev, req);
      return USBD_FAIL;
  }
  else
  {
      USBD_CtlError (pdev, req);
      return USBD_FAIL;
  }
  return USBD_OK;
}


/*******************************************************************************
* Function    : usbd_gap_EP0_RxReady
* Caption     : .
*  @Param     : 1.pdev - 
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t  usbd_gap_EP0_RxReady (void  *pdev)
{
  return USBD_OK;
}

/*******************************************************************************
* Function    : usbd_gap_DataIn
* Caption     : .
*  @Param     : 1.pdev - 
*  @Param     : 2.epnum - 
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t  usbd_gap_DataIn (void *pdev, uint8_t epnum)
{
  switch (epnum)
  {
    case 1:
    {
      GAP_IN_Callback();
      break;
    }
    case 2:
    {
      CMD_IN_Callback();
      break;
    }
    case 3:
    {
      LOG_IN_Callback();
      break;
    }    
    default:
    {
      USB_UpdateStatus();
    }
  }
  
  return USBD_OK;
}

/*******************************************************************************
* Function    : usbd_gap_DataOut
* Caption     : .
*  @Param     : 1.pdev - 
*  @Param     : 2.epnum - 
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t  usbd_gap_DataOut (void *pdev, uint8_t epnum)
{
  if (epnum == 1)
  {
    GAP_OUT_Callback();
  }
  else
  {
    if (UsbGap_Cmd.Query)
    {
      CMD_OUT_Callback();
    }
    else
    {
      USB_UpdateStatus();
    }
      
    DCD_EP_PrepareRx(pdev,
                     USB_CMD_OUT_EP,
                     (unsigned char*)&UsbGap_Cmd,
                     USB_CMD_PACKED_SIZE);
  }

  return USBD_OK;
}


/*******************************************************************************
* Function    : usbd_gap_SOF
* Caption     : .
*  @Param     : 1.pdev - 
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t  usbd_gap_SOF (void *pdev)
{
  static uint32_t FrameCount = 0;
  
  if (FrameCount++ == 100)
  {
    /* Reset the frame counter */
    FrameCount = 0;
    
    if ((USB_Tx_Flag == USBGAP_DATA_STANDBY) && (USB_Tx_Count > 0))
    {
      USB_ReloadGap();
      USB_UpdateStatus();
    }

    if ((USB_Rx_Flag == USBGAP_DATA_STANDBY) && (USB_Rx_Count == 0))
    {
      USB_PrepareGap();
    }
    
    if ((LogEnable) && (USB_Log_Flag == USBGAP_DATA_STANDBY) || (USB_Log_Flag == USBGAP_DATA_SUCCESS))
    {
      USB_ReloadLog();
      USB_UpdateStatus();
    }
  }
  
  return USBD_OK;
}

/*******************************************************************************
* Function    : USB_UpdateStatus
* Caption     : .
* Description : .
*******************************************************************************/
void USB_UpdateStatus()
{   
  DCD_EP_Flush(&USB_OTG_dev, USB_CMD_IN_EP);

  DCD_EP_Tx (&USB_OTG_dev,
             USB_CMD_IN_EP,
             (unsigned char*)&UsbGap_Status,
             USB_CMD_PACKED_SIZE);  
  
}

/*******************************************************************************
* Function    : USB_PrepareGap
* Caption     : .
* Description : .
*******************************************************************************/
void USB_PrepareGap()
{
  USB_Rx_Buffer = (uint8_t*)&GapBuffer;
  USB_Rx_Count = 0;
  USB_Rx_Flag = USBGAP_DATA_READY;

  //DCD_EP_ClrStall(&USB_OTG_dev, USB_GAP_OUT_EP);

  DCD_EP_PrepareRx(&USB_OTG_dev,
			   USB_GAP_OUT_EP,
			   USB_Rx_Buffer,
			   USB_GAP_PACKED_SIZE);
}

/*******************************************************************************
* Function    : USB_ReloadGap
* Caption     : .
*  @Param     : 1.Length - 
* Description : .
*******************************************************************************/
void USB_ReloadGap()
{ 
  uint8_t USB_Tx_Length;
  
  USB_Tx_Buffer = (uint8_t*)&GapBuffer;
  USB_Tx_Flag = USBGAP_DATA_READY;
  USB_Tx_Length = USB_Tx_Count;
  UsbGap_Status.GapLiveLen = USB_Tx_Count;
  
  //DCD_EP_ClrStall(&USB_OTG_dev, USB_GAP_IN_EP);
  DCD_EP_Flush(&USB_OTG_dev, USB_GAP_IN_EP);
  
  if (USB_Tx_Length > USB_GAP_PACKED_SIZE)
  {
    USB_Tx_Length = USB_GAP_PACKED_SIZE;
  }
  
  DCD_EP_Tx (&USB_OTG_dev,
             USB_GAP_IN_EP,
             USB_Tx_Buffer,
             USB_Tx_Length);
}

/*******************************************************************************
* Function    : USB_ReloadLog
* Caption     : .
* Description : .
*******************************************************************************/
void USB_ReloadLog()
{  
  uint16_t  USB_Log_Count;
  USB_Log_Count = LogLen[LogReadIndex];
   
  if (USB_Log_Count)
  {
    if (USB_Log_Count > 256)
    {
      USB_Log_Count = 256;
    }
    
    USB_Log_Flag = USBGAP_DATA_READY;
    USB_Log_Buffer = (uint8_t*)&LogBuffer;
    USB_Log_Buffer += LogPos[LogReadIndex];
    UsbGap_Status.LogLiveLen = USB_Log_Count;

    LogPos[LogReadIndex] = 0;
    LogLen[LogReadIndex] = 0;
    
    LogReadIndex++;
    if (LogReadIndex >= USBGAP_LOG_LIST_COUNT) LogReadIndex = 0;
    
    //DCD_EP_ClrStall(&USB_OTG_dev, USB_LOG_IN_EP);
    DCD_EP_Flush(&USB_OTG_dev, USB_LOG_IN_EP);
         
    if (USB_Log_Count > USB_LOG_PACKED_SIZE)
    {
      USB_Log_Count = USB_LOG_PACKED_SIZE;
    }
    
    DCD_EP_Tx (&USB_OTG_dev,
               USB_LOG_IN_EP,
               USB_Log_Buffer,
               USB_Log_Count);
  }
  else
  {
    USB_Log_Flag = USBGAP_DATA_NULL;
  }
}

/*******************************************************************************
* Function    : GAP_IN_Callback
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void GAP_IN_Callback(void)
{
  uint16_t USB_Tx_length;
  
  if ((USB_Tx_Flag == USBGAP_DATA_READY) && (UsbGap_Status.GapLiveLen > 0))
  {
    USB_Tx_length = USB_OTG_dev.dev.in_ep[1].xfer_count;
    
    UsbGap_Status.GapLiveLen -= USB_Tx_length;
    
    if (UsbGap_Status.GapLiveLen == 0)
    {
      USB_Tx_Flag = USBGAP_DATA_SUCCESS;
      //USB_Tx_Count = 0;
    }
    else
    {
      USB_Tx_Buffer += USB_Tx_length;
    }
    
    USB_UpdateStatus();
  }
    
  if ((USB_Tx_Flag == USBGAP_DATA_READY) && (UsbGap_Status.GapLiveLen > 0))
  {
    USB_Tx_length = UsbGap_Status.GapLiveLen;
    
    if (USB_Tx_length > USB_GAP_PACKED_SIZE)
    {
      USB_Tx_length = USB_GAP_PACKED_SIZE;
    }
    
    DCD_EP_Tx (&USB_OTG_dev,
               USB_GAP_IN_EP,
               USB_Tx_Buffer,
               USB_Tx_length);
  }
  else
  {
    //DCD_EP_Stall(&USB_OTG_dev, USB_GAP_IN_EP);
  }
}

/*******************************************************************************
* Function    : GAP_OUT_Callback
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void GAP_OUT_Callback (void)
{
  uint16_t  USB_Rx_Cnt;
  uint16_t  I = 0;
  
  if (USB_Rx_Flag == USBGAP_DATA_READY)
  {
    USB_Rx_Cnt = USB_OTG_dev.dev.out_ep[1].xfer_count;
    
    if (USB_Rx_Cnt > 0) do
    {
      if (USB_Rx_Count == 0)
      {
        if (GapBuffer[0] == GAP_PTC_RS)
        {
          do
          {
            if (GapBuffer[I] != GAP_PTC_RS)
            {
              break;
            }
            else
            {
              I++;
            }
          } while (I < USB_Rx_Cnt);
            
          if (I >= USB_Rx_Cnt)
          {
            break;
          }
        }
        
        if (GapBuffer[I] != GAP_PTC_BEGIN)
        {
          USB_Rx_Flag = USBGAP_DATA_ERROR;
          break;
        }
      }
      
      if ((USB_Rx_Count + USB_Rx_Cnt) > GAP_ENCODE_SIZE)
      {
        USB_Rx_Flag = USBGAP_DATA_OVERRAM;
        break;
      }
      
      USB_Rx_Count += USB_Rx_Cnt;
      USB_Rx_Buffer += USB_Rx_Cnt;
      
      if (GapBuffer[USB_Rx_Count - 1] == GAP_PTC_END)
      {
        USB_Rx_Flag = USBGAP_DATA_SUCCESS;
        USB_OnDecodeGap();
        //CommandManage_Resume();
      }        
    } while(0);
  } 
  
  if (USB_Rx_Flag == USBGAP_DATA_READY)
  {
    USB_Rx_Cnt = GAP_ENCODE_SIZE - USB_Rx_Count;
    
    if (USB_Rx_Cnt > USB_GAP_PACKED_SIZE)
    {
      USB_Rx_Cnt = USB_GAP_PACKED_SIZE;
    }
    
    DCD_EP_PrepareRx(&USB_OTG_dev,
                 USB_GAP_OUT_EP,
                 USB_Rx_Buffer,
                 USB_Rx_Cnt);
  }
}

/*******************************************************************************
* Function Name  : CMD_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CMD_IN_Callback(void)
{
  if ((LogEnable) && (UsbGap_Status.LogLiveLen == 0) && (USB_Log_Flag != 1))
  {
    USB_ReloadLog();
  }

  USB_UpdateStatus();
}

/*******************************************************************************
* Function Name  : CMD_OUT_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CMD_OUT_Callback(void)
{
  switch (UsbGap_Cmd.Query)
  {
    case USBGAP_CMD_SCRIPT:
    {
      USB_OnRunScript(UsbGap_Cmd.Param1);
      //ScriptFlag = UsbGap_Cmd.Param1;
      //CrabAppManage_Resume();
      break;
    }
    case USBGAP_CMD_LOG:
    {
      Log_Command(UsbGap_Cmd.Param1);
      USB_UpdateStatus();
            
      break;
    }
    case USBGAP_CMD_RELOADGAP:
    {
      USB_ReloadGap();
      break;
    }
    case USBGAP_CMD_RELOADLOG:
    {
      USB_ReloadLog();
      break;
    }
    default:
    {
      USB_UpdateStatus();
    }
  }
}

/*******************************************************************************
* Function Name  : LOG_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void LOG_IN_Callback (void)
{
  uint16_t USB_Log_Count;
  
  if ((LogEnable) && (USB_Log_Flag == USBGAP_DATA_READY))
  {
    USB_Log_Count = USB_OTG_dev.dev.in_ep[3].xfer_count;
    
    if (UsbGap_Status.LogLiveLen > 0)
    {
      UsbGap_Status.LogLiveLen -= USB_Log_Count;
      
      if (UsbGap_Status.LogLiveLen == 0)
      {
        USB_Log_Flag = USBGAP_DATA_SUCCESS;
      }
      else
      {
        USB_Log_Buffer += USB_Log_Count;
      }
      
      USB_UpdateStatus();
    }
    
    if (UsbGap_Status.LogLiveLen > 0)
    {
      USB_Log_Count = UsbGap_Status.LogLiveLen;
      
      if (USB_Log_Count > USB_LOG_PACKED_SIZE)
      {
        USB_Log_Count = USB_LOG_PACKED_SIZE;
      }
      
      DCD_EP_Tx (&USB_OTG_dev,
                 USB_LOG_IN_EP,
                 USB_Log_Buffer,
                 USB_Log_Count);            
    }
    else
    {
      //DCD_EP_Tx (&USB_OTG_dev,
      //           USB_LOG_IN_EP,
      //           USB_Log_Buffer,
      //           0);
      
      if (USB_Log_Flag == USBGAP_DATA_READY)
      {
        USB_Log_Flag = USBGAP_DATA_SUCCESS;
      }
    }
    
  }
  else
  {
    //DCD_EP_Stall(&USB_OTG_dev, USB_LOG_IN_EP);
  }
}

/*******************************************************************************
* Function    : USB_ReceiveSuccess
* Caption     : .
*  @Param     : 1.State - 
* Description : .
*******************************************************************************/
uint8_t USB_ReceiveSuccess()
{
  return ((USB_Rx_Flag == USBGAP_DATA_SUCCESS) && (USB_Rx_Count > 0));
}

/*******************************************************************************
* Function    : USB_ReceiveComplete
* Caption     : .
*  @Param     : 1.State - 
* Description : .
*******************************************************************************/
void USB_ReceiveComplete(uint8_t State)
{
  if (State)
  {
    USB_Rx_Count = 0;
    USB_Rx_Flag = USBGAP_DATA_STANDBY;      
  }
  else
  {
    USB_Rx_Count = 0;
    USB_Rx_Flag = USBGAP_DATA_ERROR;
  }
}

/*******************************************************************************
* Function    : USB_TransmitComplete
* Caption     : .
*  @Param     : 1.State - 
*  @Param     : 1.Size - 
* Description : .
*******************************************************************************/
void USB_TransmitComplete(uint8_t State, uint16_t Size)
{
  if (State)
  {
    USB_Tx_Count = Size;
    USB_Tx_Flag = USBGAP_DATA_STANDBY;
  }
  else
  {
    USB_Tx_Count = 0;
    USB_Tx_Flag = USBGAP_DATA_ERROR;
  }
}


/*******************************************************************************
* Function    : Log_Command
* Caption     : .
*  @Param     : 1.Status - 
* Description : .
*******************************************************************************/
void Log_Command(uint8_t Status)
{
  LogEnable = Status;
  LogReadIndex = 0;
  LogWriteIndex = 0;
  LogWritePos = 0;
  USB_Log_Flag = 0;
  //USB_Log_Count = 0;  

  memset(&GapBuffer, 0 , GAP_ENCODE_SIZE);
  memset(&LogBuffer, 0 , USBGAP_LOG_BUFFER_SIZE);
  memset(&LogPos, 0 , sizeof(LogPos));
  memset(&LogLen, 0 , sizeof(LogLen));  
  
  if (LogEnable)
  {
    UsbGap_Status.Status |= USBGAP_LOG_ENABLE;
  }
  else
  {
    UsbGap_Status.Status &= ~USBGAP_LOG_ENABLE;
  }
  
}


/*******************************************************************************
* Function    : Log
* Caption     : .
*  @Param     : 1.fmt - 
* Description : 自动加回车换行
*******************************************************************************/
void Log(char* fmt, ...)
{
  uint16_t Count;
  
  char *Buf;
    
  va_list argPt;
  va_start(argPt, fmt);
          
  if (!Log_Check(&Buf, 0)) return;
  Count = vsnprintf(Buf, 255, fmt, argPt);
  Buf[Count] = '\n';
  Log_Add(0, Count + 1);
}

/*******************************************************************************
* Function    : Logc
* Caption     : .
*  @Param     : 1.fmt - 
* Description : 不加回车换行
*******************************************************************************/
void Logc(char* fmt, ...)
{
  uint16_t Count;
  
  char *Buf;
    
  va_list argPt;
  va_start(argPt, fmt);
          
  if (!Log_Check(&Buf, 0)) return;
  Count = vsnprintf(Buf, 255, fmt, argPt);
  Log_Add(0, Count);
}

/*******************************************************************************
* Function    : Log_Check
* Caption     : .
*  @Param     : 1.Buf - 
*  @Param     : 2.MaxCount - 
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t Log_Check(char **Buf, uint16_t MaxCount)
{
  if (!LogEnable) return 0;
  
  *Buf = (char*)&LogBuffer;
  
  if (MaxCount == 0) MaxCount = 255;
          
  if ((LogWritePos + MaxCount) < USBGAP_LOG_BUFFER_SIZE)
  {
    *Buf += LogWritePos;
  }
  else
  {
    LogWritePos = 0;
  }
  
  return 1;
}

/*******************************************************************************
* Function    : Log_Add
* Caption     : .
*  @Param     : 1.Offset - 
*  @Param     : 2.Count - 
* Description : .
*******************************************************************************/
void Log_Add(uint16_t Offset, uint16_t Count)
{
  if ((!LogEnable) || (Count == 0)) return;

  LogPos[LogWriteIndex] = LogWritePos + Offset;
  LogLen[LogWriteIndex] = Count;
  
  LogWritePos += Count + Offset;
  LogWriteIndex++;
  
  if (LogWriteIndex >= USBGAP_LOG_LIST_COUNT)
  {
    LogWriteIndex = 0;
  }
  
  if ((LogEnable) && (USB_Log_Flag == USBGAP_DATA_NULL))
  {
    USB_Log_Flag = USBGAP_DATA_STANDBY;
  }
}

/*****END OF FILE****/
