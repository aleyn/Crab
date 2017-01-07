/******************** Copyright wisearm.com *********************************
* File Name         : Gap.cpp
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.1
* Create Date       : 2010-09-16
* Last Update       : 2016-01-12
* Description       : GAP firmware library.
********************************************************************************/
#include "Gap.h"
//#include "SysUtils.h"


/*******************************************************************************
** CRC16查询表                                                                
*******************************************************************************/
#ifdef  __ICCARM__  
      GapWord   //载入到内存中，CRC会更快一些
#else
const GapWord 
#endif  
GAP_CRC_TABLE[16] = {
      0x0000, 0x1021, 0x2042, 0x3063,
      0x4084, 0x50a5, 0x60c6, 0x70e7,
      0x8108, 0x9129, 0xa14a, 0xb16b,
      0xc18c, 0xd1ad, 0xe1ce, 0xf1ef
};

/*******************************************************************************
* Function    : GapCommandToRespond
* Caption     : 将命令转为回复
*  @Param     : 1.Cmd - 命令
* Return      : GapByte
* Description : .
*******************************************************************************/
GapByte GapCommandToRespond(GapByte Cmd)
{
  GapByte Result = 0;
  
  switch (Cmd)
  {
    case  GAP_CMD_DETECT: { Result = GAP_RPD_DETECT;  break;}
    case  GAP_CMD_SETUP:  { Result = GAP_RPD_SETUP;   break;}
    case  GAP_CMD_READ:   { Result = GAP_RPD_READ;    break;}
    case  GAP_CMD_WRITE:  { Result = GAP_RPD_WRITE;   break;}
    case  GAP_CMD_CONTROL:{ Result = GAP_RPD_CONTROL; break;}
    case  GAP_CMD_ECHO:   { Result = GAP_RPD_ECHO;    break;}
  }
  
  return Result;
}

/*******************************************************************************
* Function    : GapEncodeChar
* Caption     : 对当前数据进行编码
*  @Param     : 1.Data - 源始数据
* Return      : GapByte
* Description : 如果源始数据被转义，则返回转义后的数据，否则返回0
*******************************************************************************/
GapByte GapEncodeChar(GapByte Data)
{
  GapByte Result;

  switch (Data)
  {
    case GAP_PTC_BEGIN: {Result = GAP_ESC_BEGIN; break;}
    case GAP_PTC_END:   {Result = GAP_ESC_END;   break;}
    case GAP_PTC_CRC:   {Result = GAP_ESC_CRC;   break;}
    case GAP_PTC_RS:    {Result = GAP_ESC_RS;    break;}
    case GAP_PTC_ESC:   {Result = GAP_ESC_DOL;   break;}
    default: {Result = 0;}
  }

  return Result;
}

/*******************************************************************************
* Function    : GapDecodeChar
* Caption     : 对当前数据进行解码
*  @Param     : 1.Data - 已编码的数据
* Return      : GapByte
* Description : 如果源始数据被转义，则返回转义前的源始数据，否则返回0
*******************************************************************************/
GapByte GapDecodeChar(GapByte Data)
{
  GapByte Result;

  switch (Data)
  {
    case GAP_ESC_BEGIN: {Result = GAP_PTC_BEGIN; break;}
    case GAP_ESC_END:   {Result = GAP_PTC_END;   break;}
    case GAP_ESC_CRC:   {Result = GAP_PTC_CRC;   break;}
    case GAP_ESC_RS:    {Result = GAP_PTC_RS;    break;}
    case GAP_ESC_DOL:   {Result = GAP_PTC_ESC;   break;}
    default: {Result = 0;}
  }

  return Result;
}

/*******************************************************************************
* Function    : GapInit
* Caption     : 初始化GAP
*  @Param     : 1.Gap - GAP结构指针
*  @Param     : 2.Buffer - GAP数据缓冲区
*  @Param     : 3.Count - 缓冲区大小
* Description : .
*******************************************************************************/
void GapInit(PGap Gap, GapByte *Buffer, GapWord Count)
{
  Gap->SourceBuffer = Buffer;
  Gap->SourceSize = Count;
  GapReset(Gap);
}

/*******************************************************************************
* Function    : GapReset
* Caption     : 复位GAP
*  @Param     : 1.Gap - 
* Description : 清除当前的状态，回复到待机状态
*******************************************************************************/
void GapReset(PGap Gap)
{
  Gap->ResultSize = 0;
  Gap->CRC_In = 0;
  Gap->CRC_Out = 0;
  //Gap->Status = GAP_EncodeStandBy;
}

/*******************************************************************************
* Function    : GapEncodeBuffer
* Caption     : 编码用户数据到缓冲区
*  @Param     : 1.Gap - GAP结构
*  @Param     : 2.GapData - 用户数据
*  @Param     : 3.Count - 数据个数
* Return      : GapByte 当前已处理的“发送缓冲区”个数
* Description : 对当前数据进行编码，当放到发送缓冲区
*******************************************************************************/
GapByte GapEncodeBuffer(PGap Gap, PGapData GapData, GapWord Count)
{
  GapByte  *Buffer = (GapByte *)GapData;
  GapWord   BufferSize = Count;
  GapByte   TmpData = 0;
  GapByte  *CurrentBuffer = Gap->SourceBuffer;
  GapWord   CurrentSize = Gap->SourceSize;
  GapByte   Status;

  if ((BufferSize == 0) || (CurrentSize == 0))
  {
    return GAP_Faild;
  }  
  
  Status = GAP_Pressing;

  *CurrentBuffer++ = GAP_PTC_BEGIN;
  CurrentSize--;
  
  while ((CurrentSize > 0 ) && (BufferSize > 0))
  {
    TmpData = GapEncodeChar(*Buffer);

    if (TmpData != 0)
    {
      *CurrentBuffer++ = GAP_PTC_ESC;
      CurrentSize--;

      if (CurrentSize > 0)
      {
        *CurrentBuffer++ = TmpData;
        CurrentSize--;
      }
      else
      {
        Status = GAP_OutBuffer;
        break;
      }
    }
    else
    {
      *CurrentBuffer++ = *Buffer;
      CurrentSize--;
    }
    
    Buffer++;
    BufferSize--;
    
    if (BufferSize == 0)
    {
      if (Status == GAP_InCRC)
      {
        Status = GAP_EndChar;
        break;
      }
      if (Status == GAP_Pressing)
      {
        Status = GAP_InCRC;
        Gap->CRC_Out = GapCalcCrc(GapData, Count);
        Buffer = (GapByte*)&Gap->CRC_Out;
        
        if (CurrentSize > 0)
        {
          *CurrentBuffer++ = GAP_PTC_CRC;
          CurrentSize--;
          BufferSize = 2;
        }
        else
        {
          Status = GAP_OutBuffer;
          break;
        }        
      }
    }
  }
  
  if ((Status == GAP_EndChar) && (BufferSize == 0))
  {
    if (CurrentSize > 0)
    {
      *CurrentBuffer++ = GAP_PTC_END;
      CurrentSize--;
      Gap->ResultSize = Gap->SourceSize - CurrentSize;
      Status = GAP_Success;
    }
    else
    {
      Status = GAP_OutBuffer;
    }   
  }
  else
  {
    Status = GAP_Faild;
  }

  return Status;
}

/*******************************************************************************
* Function    : GapEncodeBuffer
* Caption     : 编码用户数据到缓冲区
*  @Param     : 1.Gap - GAP结构
*  @Param     : 2.GapData - 用户数据
*  @Param     : 3.Count - 数据个数
* Return      : GapByte 当前已处理的“发送缓冲区”个数
* Description : 对当前数据进行编码，当放到发送缓冲区
*******************************************************************************/

/*******************************************************************************
* Function    : GapDecodeBuffer
* Caption     : 解码缓冲区到用户数据
*  @Param     : 1.Gap - GAP结构
*  @Param     : 2.GapData - 用户数据
*  @Param     : 3.Count - 数据个数
* Return      : GapByte
* Description : 对缓冲区进行解码，并放到到用户数据中
*******************************************************************************/
GapByte GapDecodeBuffer(PGap Gap, PGapData GapData, GapWord Count)
{
  GapByte  *Buffer = (GapByte *)GapData;
  GapWord   BufferSize = Count;
  GapByte   TmpData = 0;
  GapByte  *CurrentBuffer = Gap->SourceBuffer;
  GapWord   CurrentSize = Gap->SourceSize;
  GapByte   Status;

  if ((BufferSize == 0) || (CurrentSize == 0))
  {
    return GAP_Faild;
  }  
  
  Status = GAP_StandBy;
  
  while (CurrentSize > 0)
  {
    TmpData = *CurrentBuffer;
    CurrentBuffer++;
    CurrentSize--;
    
    if (TmpData == GAP_PTC_BEGIN)
    {
      if (Status == GAP_StandBy)
      {
        Status = GAP_Pressing;
      }
      else
      {
        Status = GAP_Faild;
        break;
      }
    }
    else if (TmpData == GAP_PTC_RS)
    {
      //do nothing;
    }
    else if (TmpData == GAP_PTC_END)
    {
      if (Status == GAP_InCRC)
      {
        Status = GAP_EndChar;
      }
      else
      {
        Status = GAP_Faild;
      }
      break;
    }
    else if (TmpData == GAP_PTC_CRC)
    {
      if (Status == GAP_Pressing)
      {
        Status = GAP_InCRC;
        Gap->ResultSize = Count - BufferSize;
        Buffer = (GapByte*)&Gap->CRC_In;
        BufferSize = 2;
      }
      else
      {
        Status = GAP_Faild;
        break;
      }
    }
    else if ((Status == GAP_Pressing) || (Status == GAP_InCRC))
    {
      if (TmpData == GAP_PTC_ESC)
      {
        if (CurrentSize >0)
        {
          TmpData = GapDecodeChar(*CurrentBuffer);
          CurrentBuffer++;
          CurrentSize--;
        }
        else
        {
          Status = GAP_OutBuffer;
          break;
        }
      }

      if (BufferSize > 0)
      {
        *Buffer++ = TmpData;
        BufferSize--;
      }
      else
      {
        Status = GAP_OutBuffer;
        break;
      }
    }
  }

  if (Status == GAP_EndChar)
  {
    Gap->CRC_Out = GapCalcCrc(GapData, Gap->ResultSize);
    if (Gap->CRC_In == Gap->CRC_Out)
    {
      Status = GAP_Success;
    }
  }
  
  return Status;
}

/*******************************************************************************
* Function    : GapCalcCrc
* Caption     : 计算CRC数据
*  @Param     : 1.GapData - 数据指针
*  @Param     : 2.Count - 数据长度
* Return      : GapWord - CRC 16位数据
* Description : .
*******************************************************************************/
GapWord GapCalcCrc(PGapData GapData, GapWord Count)
{
  GapByte *ptr = (GapByte*) GapData;
  GapWord Crc = 0;
  GapByte da;

  while(Count)
  {
    da = Crc >> 12;
    Crc <<= 4;
    da ^= *ptr >> 4;
    Crc ^= GAP_CRC_TABLE[da];
    
    da = Crc >> 12;
    Crc <<= 4;
    da ^= *ptr & 0x0f;
    Crc ^= GAP_CRC_TABLE[da];
    
    ptr++;
    Count--;
  }
  
  return(Crc);
}

/*******************************************************************************
* Function    : GapContinueCrc
* Caption     : 计算CRC数据
*  @Param     : 1.Data - 数据
*  @Param     : 2.Crc - 源始Crc
* Return      : GapWord - CRC 16位数据
* Description : .
*******************************************************************************/
GapWord GapContinueCrc(GapByte Data, GapWord Crc)
{
    GapByte da;

    da = Crc >> 12;
    Crc <<= 4;
    da = da ^ (Data >> 4);
    Crc ^= GAP_CRC_TABLE[da];

    da = Crc >> 12;
    Crc <<= 4;
    da = da ^ (Data & 0x0f);
    Crc ^= GAP_CRC_TABLE[da];

    return Crc;
}


/*******************************************************************************
**                                END OF FILE                                 **
*******************************************************************************/
