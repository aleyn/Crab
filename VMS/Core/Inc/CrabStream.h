/******************** Copyright wisearm.com ************************************
* File Name         : CrabStream.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : �ڴ����Ž���
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
	csoBeginning = SEEK_SET,          //����ʼλ�� (SEEK_SET)
	csoCurrent   = SEEK_CUR,          //�ӵ�ǰλ�� (SEEK_CUR)
  csoEnd       = SEEK_END           //�ӽ���λ�� (SEEK_END)
} TCrabStreamOrigin;               //��λģʽ

typedef enum
{
	csmOpenRead = 0,           //ֻ��
	csmOpenWrite = 1,          //ֻд
	csmOpenReadWrite = 2,      //��д
  csmCreate = 3              //����һ�����Զ�д�� 
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

//�ڴ����ṹ����
#pragma pack(1)
typedef struct
{
  TCrabStreamDevice    Device;        //�豸��Ϣ
  CrabInt              ErrCode;       //���Ĵ�����Ϣ

  TCrabStream_GetSize  GetSize;       //��ȡ����
  TCrabStream_SetSize  SetSize;       //���ó���
  TCrabStream_Position Position;      //��ȡ��ǰλ��
  TCrabStream_Seek     Seek;          //��λ����
  TCrabStream_Read     Read;          //������
  TCrabStream_Write    Write;         //д����
  TCrabStream_Eof      Eof;           //�Ƿ����λ��
  TCrabStream_Free     Free;          //�ͷ���
} TCrabStream, *PCrabStream;
#pragma pack()

//��ʼ�����ṹ
CrabVoid CrabStream_Init(PCrabStream Stream);

//������ṹ
CrabUint CrabStream_Check(PCrabStream Stream, CrabUint ApiAddr);

//�ͷ���
CrabUint CrabStream_Free(PCrabStream Stream);

//��ȡ����С
CrabUint CrabStream_GetSize(PCrabStream Stream);

//��������С
CrabUint CrabStream_SetSize(PCrabStream Stream, CrabUint Size);

//��ȡ���ĵ�ǰλ��
CrabUint CrabStream_Position(PCrabStream Stream);

//�����µ���λ��
CrabUint CrabStream_Seek(PCrabStream Stream, CrabUint Offset, CrabInt Origin);
#define CrabStream_SeekAddr(Stream, Addr)  CrabStream_Seek(Stream, Addr, csoBeginning)

//��ȡ������
CrabUint CrabStream_Read(PCrabStream Stream, CrabPoint Buffer, CrabUint Count);

//д��������
CrabUint CrabStream_Write(PCrabStream Stream, CrabPoint Buffer, CrabUint Count);

//��ȡ������
CrabUint CrabStream_ReadType(PCrabStream Stream, CrabPoint Buffer, CrabByte BufType);

//д��������
CrabUint CrabStream_WriteType(PCrabStream Stream, CrabPoint Buffer, CrabByte BufType);

//�ж����Ƿ��Ѿ�����
CrabBool CrabStream_Eof(PCrabStream Stream);

//�����ж�ȡһ���ַ�����
CrabUint CrabStream_ReadString(PCrabStream Stream, CrabString Result);

//дһ���ַ���������
CrabUint CrabStream_WriteString(PCrabStream Stream, CrabString Value, CrabByte MaxLength);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE