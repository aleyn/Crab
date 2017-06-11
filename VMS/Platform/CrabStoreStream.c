/******************** Copyright wisearm.com *********************************
* File Name         : CrabStoreStream.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : .
********************************************************************************/
#include "CrabVMS.h"
#include "CrabHardware.h"

#define FlashProtectMask     0x1C
#define FlashProtectEnable   0x1C
#define FlashProtectDisable  0x00

CrabUint CrabStoreStream_GetSize(TCrabStreamDevice Device);
CrabUint CrabStoreStream_SetSize(TCrabStreamDevice Device, CrabUint Size);
CrabUint CrabStoreStream_Position(TCrabStreamDevice Device);
CrabUint CrabStoreStream_Seek(TCrabStreamDevice Device, CrabUint Offset, CrabInt Origin);
CrabBool CrabStoreStream_Eof(TCrabStreamDevice Device);
CrabUint CrabStoreStream_Free(TCrabStreamDevice Device);

CrabUint CrabStoreStream_ReadFlash(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count);
CrabUint CrabStoreStream_WriteFlash(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count);

CrabUint CrabStoreStream_ReadEEprom(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count);
CrabUint CrabStoreStream_WriteEEprom(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count);

/********************************************************************************
* Function    : CrabStoreStream_Create()
* Caption     : 建立文件流
*  @Param     : Stream - 流结构
*  @Param     : Type - 流类型
*  @Param     : Offset - 绝对偏移位置
*  @Param     : Size - 流大小
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_Create(PCrabStream Stream, CrabStoreInfo StoreInfo)
{  
  if (StoreInfo != null)
  {
    Stream->Device = (TCrabStreamDevice)StoreInfo;
    Stream->GetSize = CrabStoreStream_GetSize;
    Stream->SetSize = CrabStoreStream_SetSize;
    Stream->Position = CrabStoreStream_Position;
    Stream->Seek = CrabStoreStream_Seek;
    Stream->Eof = CrabStoreStream_Eof;
    Stream->Free = CrabStoreStream_Free;

    switch (StoreInfo->Type)
    {
      case CRAB_STORE_TYPE_FLASH:
      {
        Stream->Read = CrabStoreStream_ReadFlash;
        Stream->Write = CrabStoreStream_WriteFlash;
        break;
      }
      case CRAB_STORE_TYPE_EEPROM:
      {
        Stream->Read = CrabStoreStream_ReadEEprom;
        Stream->Write = CrabStoreStream_WriteEEprom;
        break;
      }
    }   

   StoreInfo->Addr = 0;
   return Stream->Device;
  }
  else
  {
    CrabStream_Init(Stream);
    return CrabStream_Error;
  }

}

/********************************************************************************
* Function    : CrabStoreStream_Free()
* Caption     : 释放文件流
*  @Param     : Stream - 流结构
* Return      : CrabUint
* Description : 文件句柄对应Stream.Device
********************************************************************************/
CrabUint CrabStoreStream_Free(TCrabStreamDevice Device)
{
  if (Device != CrabStream_InvaildDevice)
  {
    return 0;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_Create()
* Caption     : 更新流信息
*  @Param     : Stream - 流结构
*  @Param     : Offset - 绝对偏移位置
*  @Param     : Size - 流大小
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_Update(PCrabStream Stream, CrabUint Offset, CrabUint Size)
{
  CrabStoreInfo StoreInfo = (CrabStoreInfo)Stream->Device;

  if (StoreInfo != null)
  {
    StoreInfo->Offset = Offset;
    StoreInfo->Size = Size;
    StoreInfo->Addr = 0;
    
    return 0;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_WriteProtect()
* Caption     : 打开或解除存储器的写保护
*  @Param     : Stream - 流结构
*  @Param     : State - 写保护状态
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_WriteProtect(PCrabStream Stream, CrabBool State)
{
  CrabStoreInfo StoreInfo = (CrabStoreInfo)Stream->Device;
  CrabByte Tmp;

  if (StoreInfo != null)
  {
    if (StoreInfo->Type == CRAB_STORE_TYPE_FLASH)
    {

      if (State)
      {
        State = FlashProtectEnable;
      }
      else
      {
        State = FlashProtectDisable;
      }

      sFLASH_WriteStatus(State);
      Tmp = sFLASH_ReadStatus();
      
      if ((Tmp & FlashProtectMask) == State)
      {
        return CrabTrue;
      }
      else
      {
        return CrabFalse;
      }
      
    }
    
    return 0;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_EarseAll()
* Caption     : 删除所有的扇区
*  @Param     : Stream - 流结构
*  @Param     : State - 写保护状态
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_EarseAll(PCrabStream Stream)
{
  CrabStoreInfo StoreInfo = (CrabStoreInfo)Stream->Device;

  if (StoreInfo != null)
  {
    if (StoreInfo->Type == CRAB_STORE_TYPE_FLASH)
    {  
      sFLASH_EraseBulk();
      sFLASH_WaitForWriteEnd();
    }
    
    return 0;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_WriteProtect()
* Caption     : 删除单个扇区
*  @Param     : Stream - 流结构
*  @Param     : SecAddr - 扇区地址
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_EarseSector(PCrabStream Stream, CrabUint SecAddr, CrabUint Count)
{
  CrabStoreInfo StoreInfo = (CrabStoreInfo)Stream->Device;
  CrabUint I;

  if (StoreInfo != null)
  {
    if (StoreInfo->Type == CRAB_STORE_TYPE_FLASH)
    {      
      if (Count > CRAB_FLASH_SECTION_COUNT)
      {
        Count = CRAB_FLASH_SECTION_COUNT;
      }

      for (I=0; I<Count; I++)
      {
        sFLASH_EraseSector(SecAddr, sFLASH_SECTOR_4K);
        SecAddr += CRAB_FLASH_SECTION_SIZE;
      }      
    }
    
    return 0;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_GetSize()
* Caption     : 取得文件流大小
*  @Param     : Device - 文件句柄
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_GetSize(TCrabStreamDevice Device)
{
  if (Device != CrabStream_InvaildDevice)
  {
    return ((CrabStoreInfo)Device)->Size;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_SetSize()
* Caption     : 设置文件流大小
*  @Param     : Device - 文件句柄
*  @Param     : Size - 大小
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_SetSize(TCrabStreamDevice Device, CrabUint Size)
{
  if (Device != CrabStream_InvaildDevice)
  {
		//未实现
		return 0;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_Position()
* Caption     : 取得文件流当前位置
*  @Param     : Device - 文件句柄
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_Position(TCrabStreamDevice Device)
{
  if (Device != CrabStream_InvaildDevice)
  {
    return ((CrabStoreInfo)Device)->Addr;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_Seek()
* Caption     : 定位文件流位置
*  @Param     : Device - 文件句柄
*  @Param     : Offset - 偏移值
*  @Param     : Origin - 偏移模式
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_Seek(TCrabStreamDevice Device, CrabUint Offset, CrabInt Origin)
{
  if (Device != CrabStream_InvaildDevice)
  {
    CrabStoreInfo StoreInfo = (CrabStoreInfo)Device;

    switch (Origin)
    {
      case csoBeginning:
      {
        StoreInfo->Addr = Offset;
        break;
      }
      case csoCurrent:
      {
        StoreInfo->Addr += Offset;
        break;
      }
      case csoEnd:
      {
        StoreInfo->Addr = StoreInfo->Size - Offset;
        break;
      }
    }
    
    return StoreInfo->Addr;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_ReadFlash()
* Caption     : 读取文件流数据
*  @Param     : Device - 文件句柄
*  @Param     : Buffer - 缓冲区
*  @Param     : Count - 数量
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_ReadFlash(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count)
{
  if (Device != CrabStream_InvaildDevice)
  {
    CrabStoreInfo StoreInfo = (CrabStoreInfo)Device;
    CrabUint  Addr;

    if ((StoreInfo->Addr + Count) <= StoreInfo->Size)
    {
      Addr = StoreInfo->Offset + StoreInfo->Addr;      
      sFLASH_ReadBuffer(Buffer, Addr, Count);
      StoreInfo->Addr += Count;

      return Count;
    }
    else
    {
      return CrabStream_Error;
    }
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_WriteFlash()
* Caption     : 写入文件流数据
*  @Param     : Device - 文件句柄
*  @Param     : Buffer - 缓冲区
*  @Param     : Count - 数量
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_WriteFlash(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count)
{
  if (Device != CrabStream_InvaildDevice)
  {
    CrabStoreInfo StoreInfo = (CrabStoreInfo)Device;
    CrabUint  Addr;

    if ((StoreInfo->Addr + Count) <= StoreInfo->Size)
    {
      Addr = StoreInfo->Offset + StoreInfo->Addr; 
      
      //
      /*if ((Addr & 0x000000FF) > 0)
      {
        Addr += 0x100 - (Addr & 0x000000FF);
      }*/
      
      sFLASH_WriteBuffer(Buffer, Addr, Count);
      //sFLASH_PageWrite(Buffer, Addr, Count);
      //sFLASH_ByteWrite(Buffer, Addr, Count);
      StoreInfo->Addr += Count;
      
      return Count;
    }
    else
    {
      return CrabStream_Error;
    }
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_ReadEEprom()
* Caption     : 读取文件流数据
*  @Param     : Device - 文件句柄
*  @Param     : Buffer - 缓冲区
*  @Param     : Count - 数量
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_ReadEEprom(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count)
{
  if (Device != CrabStream_InvaildDevice)
  {
    CrabStoreInfo StoreInfo = (CrabStoreInfo)Device;
    CrabUint  Addr;

    if ((StoreInfo->Addr + Count) <= StoreInfo->Size)
    {
      Addr = StoreInfo->Offset + StoreInfo->Addr;      
      if (EEPROM_BufferRead(Buffer, Addr, Count) == EEPROM_Success)
      {
        StoreInfo->Addr += Count;

        return Count;
      }
      else
      {
        return CrabStream_Error;
      }
    }
    else
    {
      return CrabStream_Error;
    }
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_WriteEEprom()
* Caption     : 写入文件流数据
*  @Param     : Device - 文件句柄
*  @Param     : Buffer - 缓冲区
*  @Param     : Count - 数量
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_WriteEEprom(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count)
{
  if (Device != CrabStream_InvaildDevice)
  {
    CrabStoreInfo StoreInfo = (CrabStoreInfo)Device;
    CrabUint  Addr;

    if ((StoreInfo->Addr + Count) <= StoreInfo->Size)
    {
      Addr = StoreInfo->Offset + StoreInfo->Addr; 
      if (EEPROM_BufferWrite(Buffer, Addr, Count) == EEPROM_Success)
      {
        StoreInfo->Addr += Count;
        return Count;
      }
      else
      {
        return CrabStream_Error;
      }      
    }
    else
    {
      return CrabStream_Error;
    }
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_Eof()
* Caption     : 判断文件流是否已经结束
*  @Param     : Device - 
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabBool CrabStoreStream_Eof(TCrabStreamDevice Device)
{
  if (Device != CrabStream_InvaildDevice)
  {
    CrabStoreInfo StoreInfo = (CrabStoreInfo)Device;
    
    if (StoreInfo->Addr >= StoreInfo->Size)
    {
      return CrabTrue;
    }
    else
    {
      return CrabFalse;
    }
  }
  else
  {
    return CrabTrue;
  }
}

