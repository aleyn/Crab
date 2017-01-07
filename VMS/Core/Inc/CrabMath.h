/******************** Copyright wisearm.com ************************************
* File Name         : CrabMath.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 数学函数
********************************************************************************/

#ifndef __CRAB_MATH__
#define __CRAB_MATH__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

//取浮点数的整数部分
CrabInt  CrabFloatTrunc(CrabFloat V);

//取浮点数的小数点部分
CrabFloat  CrabFloatFract(CrabFloat V);

//浮点数求余
CrabFloat  CrabFloatMod(CrabFloat V1, CrabFloat V2);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE