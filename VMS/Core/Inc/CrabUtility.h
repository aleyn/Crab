/******************** Copyright wisearm.com ************************************
* File Name         : CrabUtility.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 常用工具集
********************************************************************************/
#ifndef __CRAB_UTILITY__
#define __CRAB_UTILITY__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#pragma pack(1)
typedef struct
{
  CrabByte      Major;
  CrabByte      Minor;
  CrabUShort    Build;
} TCrabVersion, *PCrabVersion;

#pragma pack(1)
typedef struct
{
  CrabPoint     Memory;         //用户内存地址
  CrabUint      MemorySize;     //用户内存大小
  CrabPoint     Cache;          //指令缓冲区
  CrabUint      CacheSize;      //指令缓冲区大小
  CrabUint      FifoCount;      //事件FIFO个数
  CrabUint      StrPoolCount;   //全长字符串缓冲池个数
  CrabUint      ArrayDimCount;  //数组维数栈个数
} TCrabConfig, *PCrabConfig;

//将地址或值转为三字节
CrabUint    CrabThreeByte(CrabUint Addr);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE