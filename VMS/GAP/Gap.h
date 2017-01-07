/******************** Copyright wisearm.com *********************************
* File Name         : Gap.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.1
* Create Date       : 2010-09-16
* Last Update       : 2016-01-12
* Description       : GAP firmware library.
********************************************************************************/
#ifndef _GAP_H
#define _GAP_H

#ifdef __cplusplus
 extern "C" {
#endif 

//协议定义和转义
#define  GAP_PTC_BEGIN          0x1A  //协议包开始标志
#define  GAP_PTC_CRC            0x1C  //协议包CRC部分
#define  GAP_PTC_END            0x1D  //协议包结束标志
#define  GAP_PTC_RS             0x1F  //协议包请求信号
#define  GAP_PTC_ESC            0x1B  //协议的转义命令
#define  GAP_ESC_BEGIN          0x11  //把0x1A 转为 0x11
#define  GAP_ESC_CRC            0x13  //把0x1C 转为 0x13
#define  GAP_ESC_END            0x14  //把0x1D 转为 0x14
#define  GAP_ESC_RS             0x15  //把0x1F 转为 0x15
#define  GAP_ESC_DOL            0x0B  //把0x1B 转为 0x0B

//命令
#define  GAP_CMD_DETECT         0xF0  //设备搜索和检测
#define  GAP_CMD_SETUP          0xE1  //设置参数
#define  GAP_CMD_READ           0xD2  //读数据(从设备到主机)
#define  GAP_CMD_WRITE    	    0xC3  //写数据(从主机至设备)
#define  GAP_CMD_CONTROL        0xB4  //端口控制
#define  GAP_CMD_ECHO           0xA5  //回响(设备将主机的数据区原封不动回复给主机)

//回应
#define  GAP_RPD_DETECT         0x0F  //设备搜索和检测
#define  GAP_RPD_SETUP          0x1E  //设置参数
#define  GAP_RPD_READ           0x2D  //读数据(从设备到主机)
#define  GAP_RPD_WRITE    	    0x3C  //写数据(从主机至设备)
#define  GAP_RPD_CONTROL        0x4B  //端口控制
#define  GAP_RPD_ECHO           0x5A  //回响(设备将主机的数据区原封不动回复给主机)

//回应状态
#define  GAP_STS_SUCCESS        0x00  //接收成功
#define  GAP_STS_FAILED         0x01  //接收失败（或者是CRC错误）
#define  GAP_STS_NOT_READY      0x02  //下位机没准备好
#define  GAP_STS_INVALID_CMD    0x04  //无效的命令

//协议数据大小
#define  GAP_HEAD_SIZE          4     //协议头固定长度
#define  GAP_DATA_SIZE          252   //数据区最大长度
#define  GAP_MAX_SIZE           256   //协议最大长度
#define  GAP_ENCODE_SIZE        512   //协议缓冲区最大长度
#define  GAP_MINISIZE_SETUP     4     //参数类型(SETUP)最小长度
#define  GAP_MINISIZE_RW        8     //数据读写(READ/WRITE)最小长度
#define  GAP_MINISIZE_CONTROL   4     //读写端口(CONTROL)最小长度
  
#define  GapGetSize(G)          (G.Size + GAP_HEAD_SIZE)
#define  GapGetPSize(G)         (G->Size + GAP_HEAD_SIZE)

/*******************************************************************************
** GAP协议数据结构                                                            **
*******************************************************************************/

typedef          char  GapChar;      //字符型
typedef unsigned char  GapByte;      //单字节
typedef unsigned short GapWord;      //双字节
typedef unsigned int   GapUint;      //四字节
typedef          int   GapInt;       //四字节

#pragma pack(1)
typedef struct
{
  union
  {
    struct
    {                                        //主机端:
      GapByte     Command;                   //命令[CMD]
      GapByte     Detail;                    //二级命令
    };
    struct
    {                                        //设备端:
      GapByte     Respond;                   //回复命令[RPD]，与发送主机的主机命令相对应
      GapByte     Status;                    //命令状态[STS]，只在返回中用。
    };
  };

  GapWord         Size;                      //数据区大小 
} TGapHeader, *PGapHeader, GapHeader;

#pragma pack(1)
typedef union
{
  struct
  {
    GapByte       Major;                     //主版本
    GapByte       Minor;                     //副版本
    GapWord       Build;                     //编译版本
  };
  GapByte         bVerInfo[4];               //版本信息
  GapUint         uVerInfo;
} TGapVersion, *PGapVersion;

#pragma pack(1)
typedef struct
{
  GapByte         Index;                     //索引地址
  GapByte         Len;                       //描述长度
} TGapDescript, *PGapDescript;

#pragma pack(1)
typedef struct
{
  GapUint         DeviceID;                  //设备ID
  GapUint         VenderID;                  //厂家ID
  TGapVersion     Hardware;                  //硬件版本
  TGapVersion     Firmware;                  //固件版本
  TGapDescript    HWDescript;                //硬件描述符
  TGapDescript    FWDescript;                //固件描述符
  GapChar         Descript[1];               //描述符起始位置
} TGapDetect, *PGapDetect;

#pragma pack(1)
typedef struct
{
  GapUint         Category;                   //参数类型(SETUP)
  union
  {
    GapByte       bParam[1];                  //Byte型参数
    GapWord       wParam[1];                  //Word型参数
    GapUint       uParam[1];                  //Uint型参数
  };
} TGapSetup, *PGapSetup;

#pragma pack(1)
typedef struct
{
  GapUint         Count;                     //数据长度(READ/WRITE)
  GapUint         Address;                   //读写地址(READ/WRITE)
  union
  {
    GapByte       bData[1];                  //Byte型数据
    GapWord       wData[1];                  //Word型数据
    GapUint       uData[1];                  //Uint型数据
  };
} TGapReadWrite, *PGapReadWrite;

#pragma pack(1)
typedef struct
{
  GapUint         Port;                      //读写端口(CONTROL)
  union
  {
    GapByte       bValue[1];                 //Byte型数据
    GapWord       wValue[1];                 //Word型数据
    GapUint       uValue[1];                 //Uint型数据
  };
} TGapControl, *PGapControl;

#pragma pack(1)
typedef struct
{
  GapByte         bReply[GAP_DATA_SIZE];      //Byte型数据
  GapWord         wReply[1];                  //Word型数据
  GapUint         uReply[1];                  //Uint型数据
} TGapEcho, *PGapEcho;

#pragma pack(1)
typedef struct
{
  TGapHeader;
  union
  {
    TGapDetect    Detect;                    //设备信息
    TGapSetup     Setup;                     //参数设置
    TGapReadWrite ReadWrite;                 //读写数据
    TGapControl   Control;                   //端口控制
    TGapEcho      Echo;                      //数据回显  
  };
} TGapData, *PGapData;                       //协议缓冲区

typedef enum GAP_Status_Enum
{
  GAP_StandBy       = 0,
  GAP_Pressing      = 1,
  GAP_InCRC         = 2,
  GAP_EndChar       = 3,
  GAP_OutBuffer     = 4,
  GAP_CrcFaild      = 5,
  GAP_Faild         = 6,
  GAP_Success       = 9
} TGapStatus;

#pragma pack(1)
typedef struct
{
  GapByte  *SourceBuffer;
  GapWord   SourceSize;

  GapWord   CRC_In;
  GapWord   CRC_Out;

  //GapByte   Status;
  GapWord   ResultSize;
  
} TGap, *PGap;


void GapInit(PGap Gap, GapByte *Buffer, GapWord Count);
void GapReset(PGap Gap);

GapByte GapCommandToRespond(GapByte Cmd);

GapByte GapEncodeChar(GapByte Data);
GapByte GapDecodeChar(GapByte Data);

GapByte GapEncodeBuffer(PGap Gap, PGapData GapData, GapWord Count);
GapByte GapDecodeBuffer(PGap Gap, PGapData GapData, GapWord Count);

GapWord GapCalcCrc(PGapData GapData, GapWord Count);
GapWord GapContinueCrc(GapByte Data, GapWord Crc);

#ifdef __cplusplus
}
#endif

#endif

/*******************************************************************************
**                                END OF FILE                                 **
*******************************************************************************/
