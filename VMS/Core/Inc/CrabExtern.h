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

//定义API函数调用接口
typedef crabapi(*TCrabApiFunc)    ();
typedef crabapi(*TCrabEventFunc)  (CrabBool State);
typedef crabapi(*TCrabInput)      (CrabUint Type, CrabAnsi Buffer, PCrabUint Length);
typedef crabapi(*TCrabPrint)      (CrabAnsi Text, CrabUint Length);
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

//注册API函数
CrabBool CrabExtern_RegisterFunction(CrabWord ApiIndex, TCrabApiFunc ApiAddr);

//注销API函数
CrabBool CrabExtern_UnregisterFunction(CrabWord ApiIndex);

//注册API函数，名称方式
CrabBool CrabExtern_RegisterFuncName(const CrabAnsi ApiName, TCrabApiFunc ApiAddr);

//查找API函数索引位置
CrabBool CrabExtern_FindFuncIndex(const CrabAnsi ApiName, CrabWord __var ApiIndex, CrabBool IgnoreUsed);

//载入API函数地址
CrabUint CrabExtern_GetFuncAddr(CrabWord ApiIndex);

//载入API函数名称
CrabBool CrabExtern_LoadFuncName(CrabWord ApiIndex, CrabString ApiName);

//获取参数个数
CrabUint CrabExtern_GetParamCount();

//获取端口地址
CrabUint CrabExtern_GetPortAddr();

//判断参数是否为Null
CrabUint CrabExtern_ParamIsNull(CrabUint ParamIndex);

//判断参数是否为Null
CrabUint CrabExtern_ParamIsString(CrabUint ParamIndex);

//获取布尔型参数
CrabBool CrabExtern_GetBoolParam(CrabUint ParamIndex);

//获取整型参数
CrabInt  CrabExtern_GetIntParam(CrabUint ParamIndex);

//获取无符号整型参数
CrabUint CrabExtern_GetUintParam(CrabUint ParamIndex);

//获取日期型参数
CrabDate CrabExtern_GetDateParam(CrabUint ParamIndex);

//获取时间型参数
CrabTime CrabExtern_GetTimeParam(CrabUint ParamIndex);

//获取浮点型参数
CrabFloat  CrabExtern_GetFloatParam(CrabUint ParamIndex);

//获取字符串型参数
CrabString CrabExtern_GetStringParam(CrabUint ParamIndex);

//将参数转换为字符串型
CrabString CrabExtern_ConvertParamToString(CrabUint ParamIndex, CrabString Result);

//取得临时字符串缓冲区
CrabString CrabExtern_GetTempString();

//返回布尔型
CrabBool CrabExtern_ReturnBoolValue(CrabBool ParamIndex);

//返回空值
CrabBool CrabExtern_ReturnNullValue();

//返回整型
CrabBool CrabExtern_ReturnIntValue(CrabInt Result);

//返回无符号整型
CrabBool CrabExtern_ReturnUintValue(CrabUint Result);

//返回日期型
CrabBool CrabExtern_ReturnDateValue(CrabDate Result);

//返回时间型
CrabBool CrabExtern_ReturnTimeValue(CrabTime Result);

//返回浮点型
CrabBool CrabExtern_ReturnFloatValue(CrabFloat Result);

//返回字符串型
CrabBool CrabExtern_ReturnStringValue(CrabString Result);

//取得函数返回寄存器的字符串缓冲区
CrabString CrabExtern_GetReturnString();



#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE