/******************** Copyright wisearm.com **********************************
* File Name         : CrabPlatform.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 平台相关
********************************************************************************/

#ifndef __CRAB_PLATFORM__
#define __CRAB_PLATFORM__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define CRAB_APP_OFF              0
#define CRAB_APP_STOPPING         1
#define CRAB_APP_LOADROM          2
#define CRAB_APP_RESET            3
#define CRAB_APP_ERROR            4
#define CRAB_APP_STANDBY          5
#define CRAB_APP_PAUSE            6
#define CRAB_APP_CONTINUE         7
#define CRAB_APP_STEP             8
#define CRAB_APP_RUNNING          9
#define CRAB_APP_EXCEPTION        0xFF

#ifdef __BORLANDC__
  #define CrabMemAlloc(a,b)   a = malloc(b)   //申请内存
  #define CrabMemFree(a)      free(a)         //释放内存
  #define CrabMemFZero(a,b)   memset(a,0,b)   //内存清零
  #define CrabMemFill(a,b,c)  memset(a,c,b)   //内存填充
  #define CrabMemCopy(a,b,c)  memcpy(a,b,c)   //内存复制
#else
  #define CrabMemAlloc(a,b)   a = malloc(b)   //申请内存
  #define CrabMemFree(a)      free(a)         //释放内存
  #define CrabMemFZero(a,b)   memset(a,0,b)   //内存清零
  #define CrabMemFill(a,b,c)  memset(a,c,b)   //内存填充
  #define CrabMemCopy(a,b,c)  memcpy(a,b,c)   //内存复制, 在IAR中，调用此函数需要加 #include "string.h"
#endif  
  
#pragma pack(1)
typedef struct
{
  CrabPoint     Memory;         //用户内存地址
  CrabUint      MemorySize;     //用户内存大小
  CrabPoint     Cache;          //指令缓冲区
  CrabUint      CacheSize;      //指令缓冲区大小
  CrabUint      FifoCount;      //事件FIFO个数
} TCrabConfig, *PCrabConfig;

//注册API函数
void CrabRegisterApi();

//EVENT 事件开关
crabapi CrabEventIntr (CrabBool State);

//标准输入API
crabapi CrabInput (CrabUint Type, CrabAnsi Buffer, PCrabUint Length);

//标准输出API
crabapi CrabPrint (CrabAnsi Text, CrabUint Length);

//延时API，毫秒
crabapi CrabDelay (CrabUint MSec);  
  
#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE