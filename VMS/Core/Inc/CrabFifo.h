/******************** Copyright wisearm.com ************************************
* File Name         : CrabFifo.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 事件FIFO管理器
********************************************************************************/

#ifndef __CRAB_FIFO__
#define __CRAB_FIFO__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define  CrabIntrEnable     0x80
#define  CrabIntrDisable    0x00
#define  CrabIntrAction     0x08
#define  CrabIntrActionM    0xF7
#define  CrabIntrMask       0x7F
#define  CrabIntrExecute    0x88

//事件压栈
CrabBool CrabFifo_PushEvent(CrabUint EventHandle);

//事件出栈
CrabBool CrabFifo_PopEvent(CrabWord __var EventIndex);

//事件出栈和事件地址
CrabBool CrabFifo_PopFuncAddr(CrabUint __var FuncAddr);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE