/******************** Copyright wisearm.com ************************************
* File Name         : CrabExtern.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : API函数管理器
********************************************************************************/

#ifndef __CRAB_EXTERN__
#define __CRAB_EXTERN__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define CrabUserApiBase      0x000010
#define CrabExtern_RegisterApi(Name, Addr)   CrabExtern_RegisterFuncName(Name, __ref Addr)

#define CrabExtern_PopupParamAsTiny(a)          CrabExtern_PopupParam(&a, CRABTYPE_TINY)
#define CrabExtern_PopupParamAsShort(a)         CrabExtern_PopupParam(&a, CRABTYPE_SHORT)
#define CrabExtern_PopupParamAsInt(a)           CrabExtern_PopupParam(&a, CRABTYPE_INT)
#define CrabExtern_PopupParamAsLong(a)          CrabExtern_PopupParam(&a, CRABTYPE_LONG)

#define CrabExtern_PopupParamAsByte(a)          CrabExtern_PopupParam(&a, CRABTYPE_BYTE)
#define CrabExtern_PopupParamAsUShort(a)        CrabExtern_PopupParam(&a, CRABTYPE_USHORT)
#define CrabExtern_PopupParamAsUint(a)          CrabExtern_PopupParam(&a, CRABTYPE_UINT)
#define CrabExtern_PopupParamAsULong(a)         CrabExtern_PopupParam(&a, CRABTYPE_ULONG)

#define CrabExtern_PopupParamAsBool(a)          CrabExtern_PopupParam(&a, CRABTYPE_BOOL)
#define CrabExtern_PopupParamAsChar(a)          CrabExtern_PopupParam(&a, CRABTYPE_CHAR)
#define CrabExtern_PopupParamAsString(a)        CrabExtern_PopupParam(&a, CRABTYPE_STRING)

#define CrabExtern_PopupParamAsFloat(a)         CrabExtern_PopupParam(&a, CRABTYPE_FLOAT)
#define CrabExtern_PopupParamAsDouble(a)        CrabExtern_PopupParam(&a, CRABTYPE_DOUBLE)

#define CrabExtern_PopupParamAsDate(a)          CrabExtern_PopupParam(&a, CRABTYPE_DATE)
#define CrabExtern_PopupParamAsTime(a)          CrabExtern_PopupParam(&a, CRABTYPE_TIME)
#define CrabExtern_PopupParamAsDatetime(a)      CrabExtern_PopupParam(&a, CRABTYPE_DATETIME)

#define CrabExtern_PopupParamAsArray(a)         CrabExtern_PopupParam(&a, CRABTYPE_ARRAY)
#define CrabExtern_PopupParamAsObject(a)        CrabExtern_PopupParam(&a, CRABTYPE_OBJECT)


#define CrabExtern_ReturnValueAsTiny(a)          CrabExtern_ReturnValue(&a, CRABTYPE_TINY)
#define CrabExtern_ReturnValueAsShort(a)         CrabExtern_ReturnValue(&a, CRABTYPE_SHORT)
#define CrabExtern_ReturnValueAsInt(a)           CrabExtern_ReturnValue(&a, CRABTYPE_INT)
#define CrabExtern_ReturnValueAsLong(a)          CrabExtern_ReturnValue(&a, CRABTYPE_LONG)

#define CrabExtern_ReturnValueAsByte(a)          CrabExtern_ReturnValue(&a, CRABTYPE_BYTE)
#define CrabExtern_ReturnValueAsUShort(a)        CrabExtern_ReturnValue(&a, CRABTYPE_USHORT)
#define CrabExtern_ReturnValueAsUint(a)          CrabExtern_ReturnValue(&a, CRABTYPE_UINT)
#define CrabExtern_ReturnValueAsULong(a)         CrabExtern_ReturnValue(&a, CRABTYPE_ULONG)

#define CrabExtern_ReturnValueAsBool(a)          CrabExtern_ReturnValue(&a, CRABTYPE_BOOL)
#define CrabExtern_ReturnValueAsChar(a)          CrabExtern_ReturnValue(&a, CRABTYPE_CHAR)
#define CrabExtern_ReturnValueAsString(a)        CrabExtern_ReturnValue(&a, CRABTYPE_STRING)

#define CrabExtern_ReturnValueAsFloat(a)         CrabExtern_ReturnValue(&a, CRABTYPE_FLOAT)
#define CrabExtern_ReturnValueAsDouble(a)        CrabExtern_ReturnValue(&a, CRABTYPE_DOUBLE)

#define CrabExtern_ReturnValueAsDate(a)          CrabExtern_ReturnValue(&a, CRABTYPE_DATE)
#define CrabExtern_ReturnValueAsTime(a)          CrabExtern_ReturnValue(&a, CRABTYPE_TIME)
#define CrabExtern_ReturnValueAsDatetime(a)      CrabExtern_ReturnValue(&a, CRABTYPE_DATETIME)

#define CrabExtern_ReturnValueAsArray(a)         CrabExtern_ReturnValue(&a, CRABTYPE_ARRAY)
#define CrabExtern_ReturnValueAsObject(a)        CrabExtern_ReturnValue(&a, CRABTYPE_OBJECT)

#define CrabExtern_ReadFromPortAsTiny(a)        CrabExtern_ReadFromPort(&a, CRABTYPE_TINY)
#define CrabExtern_ReadFromPortAsShort(a)       CrabExtern_ReadFromPort(&a, CRABTYPE_SHORT)
#define CrabExtern_ReadFromPortAsInt(a)         CrabExtern_ReadFromPort(&a, CRABTYPE_INT)
#define CrabExtern_ReadFromPortAsLong(a)        CrabExtern_ReadFromPort(&a, CRABTYPE_LONG)

#define CrabExtern_ReadFromPortAsByte(a)        CrabExtern_ReadFromPort(&a, CRABTYPE_BYTE)
#define CrabExtern_ReadFromPortAsUShort(a)      CrabExtern_ReadFromPort(&a, CRABTYPE_USHORT)
#define CrabExtern_ReadFromPortAsUint(a)        CrabExtern_ReadFromPort(&a, CRABTYPE_UINT)
#define CrabExtern_ReadFromPortAsULong(a)       CrabExtern_ReadFromPort(&a, CRABTYPE_ULONG)

#define CrabExtern_ReadFromPortAsBool(a)        CrabExtern_ReadFromPort(&a, CRABTYPE_BOOL)
#define CrabExtern_ReadFromPortAsChar(a)        CrabExtern_ReadFromPort(&a, CRABTYPE_CHAR)
#define CrabExtern_ReadFromPortAsString(a)      CrabExtern_ReadFromPort(&a, CRABTYPE_STRING)

#define CrabExtern_ReadFromPortAsFloat(a)       CrabExtern_ReadFromPort(&a, CRABTYPE_FLOAT)
#define CrabExtern_ReadFromPortAsDouble(a)      CrabExtern_ReadFromPort(&a, CRABTYPE_DOUBLE)

#define CrabExtern_ReadFromPortAsDate(a)        CrabExtern_ReadFromPort(&a, CRABTYPE_DATE)
#define CrabExtern_ReadFromPortAsTime(a)        CrabExtern_ReadFromPort(&a, CRABTYPE_TIME)
#define CrabExtern_ReadFromPortAsDatetime(a)    CrabExtern_ReadFromPort(&a, CRABTYPE_DATETIME)


#define CrabExtern_WriteToPortAsTiny(a)         CrabExtern_WriteToPort(&a, CRABTYPE_TINY)
#define CrabExtern_WriteToPortAsShort(a)        CrabExtern_WriteToPort(&a, CRABTYPE_SHORT)
#define CrabExtern_WriteToPortAsInt(a)          CrabExtern_WriteToPort(&a, CRABTYPE_INT)
#define CrabExtern_WriteToPortAsLong(a)         CrabExtern_WriteToPort(&a, CRABTYPE_LONG)

#define CrabExtern_WriteToPortAsByte(a)         CrabExtern_WriteToPort(&a, CRABTYPE_BYTE)
#define CrabExtern_WriteToPortAsUShort(a)       CrabExtern_WriteToPort(&a, CRABTYPE_USHORT)
#define CrabExtern_WriteToPortAsUint(a)         CrabExtern_WriteToPort(&a, CRABTYPE_UINT)
#define CrabExtern_WriteToPortAsULong(a)        CrabExtern_WriteToPort(&a, CRABTYPE_ULONG)

#define CrabExtern_WriteToPortAsBool(a)         CrabExtern_WriteToPort(&a, CRABTYPE_BOOL)
#define CrabExtern_WriteToPortAsChar(a)         CrabExtern_WriteToPort(&a, CRABTYPE_CHAR)
#define CrabExtern_WriteToPortAsString(a)       CrabExtern_WriteToPort(&a, CRABTYPE_STRING)

#define CrabExtern_WriteToPortAsFloat(a)        CrabExtern_WriteToPort(&a, CRABTYPE_FLOAT)
#define CrabExtern_WriteToPortAsDouble(a)       CrabExtern_WriteToPort(&a, CRABTYPE_DOUBLE)

#define CrabExtern_WriteToPortAsDate(a)         CrabExtern_WriteToPort(&a, CRABTYPE_DATE)
#define CrabExtern_WriteToPortAsTime(a)         CrabExtern_WriteToPort(&a, CRABTYPE_TIME)
#define CrabExtern_WriteToPortAsDatetime(a)     CrabExtern_WriteToPort(&a, CRABTYPE_DATETIME)


#define CrabExtern_ReadFromHelperAsTiny(a)        CrabExtern_ReadFromHelper(&a, CRABTYPE_TINY)
#define CrabExtern_ReadFromHelperAsShort(a)       CrabExtern_ReadFromHelper(&a, CRABTYPE_SHORT)
#define CrabExtern_ReadFromHelperAsInt(a)         CrabExtern_ReadFromHelper(&a, CRABTYPE_INT)
#define CrabExtern_ReadFromHelperAsLong(a)        CrabExtern_ReadFromHelper(&a, CRABTYPE_LONG)

#define CrabExtern_ReadFromHelperAsByte(a)        CrabExtern_ReadFromHelper(&a, CRABTYPE_BYTE)
#define CrabExtern_ReadFromHelperAsUShort(a)      CrabExtern_ReadFromHelper(&a, CRABTYPE_USHORT)
#define CrabExtern_ReadFromHelperAsUint(a)        CrabExtern_ReadFromHelper(&a, CRABTYPE_UINT)
#define CrabExtern_ReadFromHelperAsULong(a)       CrabExtern_ReadFromHelper(&a, CRABTYPE_ULONG)

#define CrabExtern_ReadFromHelperAsBool(a)        CrabExtern_ReadFromHelper(&a, CRABTYPE_BOOL)
#define CrabExtern_ReadFromHelperAsChar(a)        CrabExtern_ReadFromHelper(&a, CRABTYPE_CHAR)
#define CrabExtern_ReadFromHelperAsString(a)      CrabExtern_ReadFromHelper(&a, CRABTYPE_STRING)

#define CrabExtern_ReadFromHelperAsFloat(a)       CrabExtern_ReadFromHelper(&a, CRABTYPE_FLOAT)
#define CrabExtern_ReadFromHelperAsDouble(a)      CrabExtern_ReadFromHelper(&a, CRABTYPE_DOUBLE)

#define CrabExtern_ReadFromHelperAsDate(a)        CrabExtern_ReadFromHelper(&a, CRABTYPE_DATE)
#define CrabExtern_ReadFromHelperAsTime(a)        CrabExtern_ReadFromHelper(&a, CRABTYPE_TIME)
#define CrabExtern_ReadFromHelperAsDatetime(a)    CrabExtern_ReadFromHelper(&a, CRABTYPE_DATETIME)


#define CrabExtern_WriteToHelperAsTiny(a)         CrabExtern_WriteToHelper(&a, CRABTYPE_TINY)
#define CrabExtern_WriteToHelperAsShort(a)        CrabExtern_WriteToHelper(&a, CRABTYPE_SHORT)
#define CrabExtern_WriteToHelperAsInt(a)          CrabExtern_WriteToHelper(&a, CRABTYPE_INT)
#define CrabExtern_WriteToHelperAsLong(a)         CrabExtern_WriteToHelper(&a, CRABTYPE_LONG)

#define CrabExtern_WriteToHelperAsByte(a)         CrabExtern_WriteToHelper(&a, CRABTYPE_BYTE)
#define CrabExtern_WriteToHelperAsUShort(a)       CrabExtern_WriteToHelper(&a, CRABTYPE_USHORT)
#define CrabExtern_WriteToHelperAsUint(a)         CrabExtern_WriteToHelper(&a, CRABTYPE_UINT)
#define CrabExtern_WriteToHelperAsULong(a)        CrabExtern_WriteToHelper(&a, CRABTYPE_ULONG)

#define CrabExtern_WriteToHelperAsBool(a)         CrabExtern_WriteToHelper(&a, CRABTYPE_BOOL)
#define CrabExtern_WriteToHelperAsChar(a)         CrabExtern_WriteToHelper(&a, CRABTYPE_CHAR)
#define CrabExtern_WriteToHelperAsString(a)       CrabExtern_WriteToHelper(&a, CRABTYPE_STRING)

#define CrabExtern_WriteToHelperAsFloat(a)        CrabExtern_WriteToHelper(&a, CRABTYPE_FLOAT)
#define CrabExtern_WriteToHelperAsDouble(a)       CrabExtern_WriteToHelper(&a, CRABTYPE_DOUBLE)

#define CrabExtern_WriteToHelperAsDate(a)         CrabExtern_WriteToHelper(&a, CRABTYPE_DATE)
#define CrabExtern_WriteToHelperAsTime(a)         CrabExtern_WriteToHelper(&a, CRABTYPE_TIME)
#define CrabExtern_WriteToHelperAsDatetime(a)     CrabExtern_WriteToHelper(&a, CRABTYPE_DATETIME)

#define CrabExtern_CreateArrayAsTiny(a, b)       CrabExtern_CreateArray(&a, CRABTYPE_TINY, b)
#define CrabExtern_CreateArrayAsShort(a, b)      CrabExtern_CreateArray(&a, CRABTYPE_SHORT, b)
#define CrabExtern_CreateArrayAsInt(a, b)        CrabExtern_CreateArray(&a, CRABTYPE_INT, b)
#define CrabExtern_CreateArrayAsLong(a, b)       CrabExtern_CreateArray(&a, CRABTYPE_LONG, b)

#define CrabExtern_CreateArrayAsByte(a, b)       CrabExtern_CreateArray(&a, CRABTYPE_BYTE, b)
#define CrabExtern_CreateArrayAsUShort(a, b)     CrabExtern_CreateArray(&a, CRABTYPE_USHORT, b)
#define CrabExtern_CreateArrayAsUint(a, b)       CrabExtern_CreateArray(&a, CRABTYPE_UINT, b)
#define CrabExtern_CreateArrayAsULong(a, b)      CrabExtern_CreateArray(&a, CRABTYPE_ULONG, b)

#define CrabExtern_CreateArrayAsBool(a, b)       CrabExtern_CreateArray(&a, CRABTYPE_BOOL, b)
#define CrabExtern_CreateArrayAsChar(a, b)       CrabExtern_CreateArray(&a, CRABTYPE_CHAR, b)
#define CrabExtern_CreateArrayAsString(a, b)     CrabExtern_CreateArray(&a, CRABTYPE_STRING, b)

#define CrabExtern_CreateArrayAsFloat(a, b)      CrabExtern_CreateArray(&a, CRABTYPE_FLOAT, b)
#define CrabExtern_CreateArrayAsDouble(a, b)     CrabExtern_CreateArray(&a, CRABTYPE_DOUBLE, b)

#define CrabExtern_CreateArrayAsDate(a, b)       CrabExtern_CreateArray(&a, CRABTYPE_DATE, b)
#define CrabExtern_CreateArrayAsTime(a, b)       CrabExtern_CreateArray(&a, CRABTYPE_TIME, b)
#define CrabExtern_CreateArrayAsDatetime(a, b)   CrabExtern_CreateArray(&a, CRABTYPE_DATETIME, b)

#define CrabExtern_CreateArrayAsArray(a, b)      CrabExtern_CreateArray(&a, CRABTYPE_ARRAY, b)
#define CrabExtern_CreateArrayAsObject(a, b)     CrabExtern_CreateArray(&a, CRABTYPE_OBJECT, b)

//定义API函数调用接口
typedef crabapi(*TCrabApiFunc)    ();
typedef crabapi(*TCrabEventFunc)  (CrabBool State);
typedef crabapi(*TCrabInput)      (CrabUint Type, CrabAnsi Buffer, PCrabUint Length);
typedef crabapi(*TCrabPrint)      (CrabAnsi Text, CrabUint Length, CrabBool LineEnd);
typedef crabapi(*TCrabDelay)      (CrabUint MSec);

#pragma pack(1)
typedef struct
{
  TCrabApiFunc   getClock;   //读时钟
  TCrabApiFunc   setClock;   //写时钟
  TCrabApiFunc   getBus;     //读总线
  TCrabApiFunc   setBus;     //写总线
} TCrabStaticPort, *PCrabStaticPort;

#pragma pack(1)
typedef struct
{
  TCrabEventFunc    EventIntr;
  TCrabInput        Input;
  TCrabPrint        Print;
  TCrabDelay        Delay;
} TCrabStaticApi, *PCrabStaticApi;

extern TCrabStaticPort      CrabStaticPort;
extern TCrabStaticApi       CrabStaticApi;

//打印格式字符串到终端显示器
CrabVoid CrabExtern_PrintFormat(CrabAnsi Format, ...);

//打印字符串到终端显示器
CrabVoid CrabExtern_PrintString(CrabString Text);

//打印字符串到终端显示器，添加LineEnd(\r\n)
CrabVoid CrabExtern_PrintLine(CrabString Text);

//注册API函数
CrabBool CrabExtern_RegisterFunction(CrabUShort ApiIndex, TCrabApiFunc ApiAddr);

//注销API函数
CrabBool CrabExtern_UnregisterFunction(CrabUShort ApiIndex);

//注册API函数，名称方式
CrabBool CrabExtern_RegisterFuncName(const CrabAnsi ApiName, TCrabApiFunc ApiAddr);

//查找API函数索引位置
CrabBool CrabExtern_FindFuncIndex(const CrabAnsi ApiName, CrabUShort __var ApiIndex, CrabBool IgnoreUsed);

//载入API函数地址
CrabUint CrabExtern_GetFuncAddr(CrabUShort ApiIndex);

//获取端口地址
CrabUint CrabExtern_GetPortAddr();

//载入API函数名称
CrabBool CrabExtern_LoadFuncName(CrabUShort ApiIndex, CrabString ApiName);

//获取参数
CrabBool CrabExtern_PopupParam(void *ParamAddr, CrabByte ParamType);

//返回值
CrabBool CrabExtern_ReturnValue(void *ParamAddr, CrabByte ParamType);

//读取端口值
CrabBool CrabExtern_ReadFromPort(void *ParamAddr, CrabByte ParamType);

//写回端口值
CrabBool CrabExtern_WriteToPort(void *ParamAddr, CrabByte ParamType);

//读取端口值
CrabBool CrabExtern_ReadFromHelper(void *ParamAddr, CrabByte ParamType);

//写回端口值
CrabBool CrabExtern_WriteToHelper(void *ParamAddr, CrabByte ParamType);

//建立数组
CrabBool CrabExtern_CreateArray(void *ArrayAddr, CrabByte ArrayType, CrabUint ArrayCount);

//定位数组元素地址
CrabBool CrabExtern_SeekArrayItem(void * ArrayAddr, void *ItemAddr, CrabUint ItemIndex);

//CrabString  CrabExtern_

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE