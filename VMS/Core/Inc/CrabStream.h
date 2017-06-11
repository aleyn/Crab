/******************** Copyright wisearm.com ************************************
* File Name         : CrabStream.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 内存流桥接器
********************************************************************************/

#ifndef __CRAB_STREAM__
#define __CRAB_STREAM__

#include <stdio.h>
#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define CrabStream_Success               0
#define CrabStream_Error                 0xFFFFFFFF
#define CrabStream_InvaildDevice        -1
#define CrabStream_InvaildApiFunc       -2
#define CrabStream_InvaildAddr          -3
#define CrabStream_ReadFaild            -4
#define CrabStream_WriteFaild           -5

#define CrabStream_ReadTiny(a, b)           CrabStream_ReadType(a, &b, CRABTYPE_TINY)
#define CrabStream_ReadShort(a, b)          CrabStream_ReadType(a, &b, CRABTYPE_SHORT)
#define CrabStream_ReadInt(a, b)            CrabStream_ReadType(a, &b, CRABTYPE_INT)
#define CrabStream_ReadLong(a, b)           CrabStream_ReadType(a, &b, CRABTYPE_LONG)

#define CrabStream_ReadByte(a, b)           CrabStream_ReadType(a, &b, CRABTYPE_BYTE)
#define CrabStream_ReadUShort(a, b)         CrabStream_ReadType(a, &b, CRABTYPE_USHORT)
#define CrabStream_ReadUint(a, b)           CrabStream_ReadType(a, &b, CRABTYPE_UINT)
#define CrabStream_ReadULong(a, b)          CrabStream_ReadType(a, &b, CRABTYPE_ULONG)

#define CrabStream_ReadBool(a, b)           CrabStream_ReadType(a, &b, CRABTYPE_BOOL)
#define CrabStream_ReadChar(a, b)           CrabStream_ReadType(a, &b, CRABTYPE_CHAR)
//#define CrabStream_ReadString(a, b)         CrabStream_ReadType(a, &b, CRABTYPE_STRING)

#define CrabStream_ReadFloat(a, b)          CrabStream_ReadType(a, &b, CRABTYPE_FLOAT)
#define CrabStream_ReadDouble(a, b)         CrabStream_ReadType(a, &b, CRABTYPE_DOUBLE)

#define CrabStream_ReadDate(a, b)           CrabStream_ReadType(a, &b, CRABTYPE_DATE)
#define CrabStream_ReadTime(a, b)           CrabStream_ReadType(a, &b, CRABTYPE_TIME)
#define CrabStream_ReadDatetime(a, b)       CrabStream_ReadType(a, &b, CRABTYPE_DATETIME)

#define CrabStream_WriteTiny(a, b)          CrabStream_WriteType(a, &b, CRABTYPE_TINY)
#define CrabStream_WriteShort(a, b)         CrabStream_WriteType(a, &b, CRABTYPE_SHORT)
#define CrabStream_WriteInt(a, b)           CrabStream_WriteType(a, &b, CRABTYPE_INT)
#define CrabStream_WriteLong(a, b)          CrabStream_WriteType(a, &b, CRABTYPE_LONG)

#define CrabStream_WriteByte(a, b)          CrabStream_WriteType(a, &b, CRABTYPE_BYTE)
#define CrabStream_WriteUShort(a, b)        CrabStream_WriteType(a, &b, CRABTYPE_USHORT)
#define CrabStream_WriteUint(a, b)          CrabStream_WriteType(a, &b, CRABTYPE_UINT)
#define CrabStream_WriteULong(a, b)         CrabStream_WriteType(a, &b, CRABTYPE_ULONG)

#define CrabStream_WriteBool(a, b)          CrabStream_WriteType(a, &b, CRABTYPE_BOOL)
#define CrabStream_WriteChar(a, b)          CrabStream_WriteType(a, &b, CRABTYPE_CHAR)
//#define CrabStream_WriteString(a, b)        CrabStream_WriteType(a, &b, CRABTYPE_STRING)

#define CrabStream_WriteFloat(a, b)         CrabStream_WriteType(a, &b, CRABTYPE_FLOAT)
#define CrabStream_WriteDouble(a, b)        CrabStream_WriteType(a, &b, CRABTYPE_DOUBLE)

#define CrabStream_WriteDate(a, b)          CrabStream_WriteType(a, &b, CRABTYPE_DATE)
#define CrabStream_WriteTime(a, b)          CrabStream_WriteType(a, &b, CRABTYPE_TIME)
#define CrabStream_WriteDatetime(a, b)      CrabStream_WriteType(a, &b, CRABTYPE_DATETIME)

typedef enum
{
	csoBeginning = SEEK_SET,          //从起始位置 (SEEK_SET)
	csoCurrent   = SEEK_CUR,          //从当前位置 (SEEK_CUR)
  csoEnd       = SEEK_END           //从结束位置 (SEEK_END)
} TCrabStreamOrigin;               //定位模式

typedef enum
{
	csmOpenRead = 0,           //只读
	csmOpenWrite = 1,          //只写
	csmOpenReadWrite = 2,      //读写
  csmCreate = 3              //创建一个可以读写的 
} TCrabStreamMode;

typedef CrabUint TCrabStreamDevice;

typedef CrabUint(*TCrabStream_GetSize)  (TCrabStreamDevice Device);
typedef CrabUint(*TCrabStream_SetSize)  (TCrabStreamDevice Device, CrabUint Size);
typedef CrabUint(*TCrabStream_Position) (TCrabStreamDevice Device);
typedef CrabUint(*TCrabStream_Seek)     (TCrabStreamDevice Device, CrabUint Offset, CrabInt Origin);
typedef CrabUint(*TCrabStream_Read)     (TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count);
typedef CrabUint(*TCrabStream_Write)    (TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count);
typedef CrabBool(*TCrabStream_Eof)      (TCrabStreamDevice Device);
typedef CrabUint(*TCrabStream_Free)     (TCrabStreamDevice Device);

//内存流结构函数
typedef struct
{
  TCrabStreamDevice    Device;        //设备信息
  CrabInt              ErrCode;       //最后的错误信息

  TCrabStream_GetSize  GetSize;       //获取长度
  TCrabStream_SetSize  SetSize;       //设置长度
  TCrabStream_Position Position;      //获取当前位置
  TCrabStream_Seek     Seek;          //定位函数
  TCrabStream_Read     Read;          //读函数
  TCrabStream_Write    Write;         //写函数
  TCrabStream_Eof      Eof;           //是否结束位置
  TCrabStream_Free     Free;          //释放流
} TCrabStream, *PCrabStream;

//初始化流结构
CrabVoid CrabStream_Init(PCrabStream Stream);

//检查流结构
CrabUint CrabStream_Check(PCrabStream Stream, CrabUint ApiAddr);

//释放流
CrabUint CrabStream_Free(PCrabStream Stream);

//获取流大小
CrabUint CrabStream_GetSize(PCrabStream Stream);

//设置流大小
CrabUint CrabStream_SetSize(PCrabStream Stream, CrabUint Size);

//获取流的当前位置
CrabUint CrabStream_Position(PCrabStream Stream);

//设置新的流位置
CrabUint CrabStream_Seek(PCrabStream Stream, CrabUint Offset, CrabInt Origin);
#define CrabStream_SeekAddr(Stream, Addr)  CrabStream_Seek(Stream, Addr, csoBeginning)

//读取流数据
CrabUint CrabStream_Read(PCrabStream Stream, CrabPoint Buffer, CrabUint Count);

//写入流数据
CrabUint CrabStream_Write(PCrabStream Stream, CrabPoint Buffer, CrabUint Count);

//读取流数据
CrabUint CrabStream_ReadType(PCrabStream Stream, CrabPoint Buffer, CrabByte BufType);

//写入流数据
CrabUint CrabStream_WriteType(PCrabStream Stream, CrabPoint Buffer, CrabByte BufType);

//判断流是否已经结束
CrabBool CrabStream_Eof(PCrabStream Stream);

//从流中读取一个字符串型
CrabUint CrabStream_ReadString(PCrabStream Stream, CrabString Result);

//写一个字符串到流中
CrabUint CrabStream_WriteString(PCrabStream Stream, CrabString Value, CrabByte MaxLength);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE