/******************** Copyright wisearm.com ************************************
* File Name         : CrabErrorMsg.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 错误信息表
********************************************************************************/
#ifndef __CRAB_ERRORMSG__
#define __CRAB_ERRORMSG__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

//错误代码
#define  CrabErrorSuccess                0  //无异常
#define  CrabErrorRaiseLast             -99 //抛出最后一个异常
#define  CrabErrorNotSupportCommand     -1  //不支持的指令
#define  CrabErrorOutOfMemory           -2  //内存溢出
#define  CrabErrorOutOfCodeRom          -3  //超出程序代码范围
#define  CrabErrorOutOfRegIndex         -11 //寄存器ID超出范围
#define  CrabErrorOutOfVarMemory        -12 //局部变量内存超出范围
#define  CrabErrorOutOfObjMemory        -13 //实例内存或堆超出范围
#define  CrabErrorOutOfStackMemory      -14 //栈内存超出范围
#define  CrabErrorOutOfRegStrMemory     -15 //寄存器字符串ID超出范围
#define  CrabErrorInvaildVarType        -21 //无效的变量类型
#define  CrabErrorInvaildVarAddr        -22 //无效的变量指向地址
#define  CrabErrorInvaildVarHeader      -23 //无效的变量类型头
#define  CrabErrorInvaildCodeAddr       -24 //无效的代码地址
#define  CrabErrorInvaildObjAddr        -25 //无效的变量指向地址
#define  CrabErrorInvaildStringCount    -26 //无效的字符串长度
#define  CrabErrorInvaildStrBufIndex    -27 //无效的寄存器字符串缓冲索引
#define  CrabErrorNotEnoughTotalMemory  -31 //没有足够的内存
#define  CrabErrorNotEnoughVarMemory    -32 //没有足够的局部变量内存
#define  CrabErrorNotEnoughStackMemory  -33 //没有足够的栈内存
#define  CrabErrorApiFuncNotFound       -41 //无效的API函数索引
#define  CrabErrorStackPushFaild        -51 //入栈失败
#define  CrabErrorStackPopFaild         -52 //出栈失败

//错误信息
CrabString  CrabErrorMessage(CrabInt ErrCode, CrabString Result);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE