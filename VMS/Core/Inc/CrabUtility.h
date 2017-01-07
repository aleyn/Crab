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
  CrabByte Major;
  CrabByte Minor;
  CrabWord Build;
} TCrabVersion, *PCrabVersion;

//将地址或值转为三字节
CrabUint    CrabThreeByte(CrabUint Addr);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE