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

#define CRABCOMPARE_FAILD   0
#define CRABCOMPARE_EQU     0x01
#define CRABCOMPARE_LTN     0x02
#define CRABCOMPARE_GTN     0x04

#define CRABBITOPERAT_BNOT  0x01
#define CRABBITOPERAT_BAND  0x02
#define CRABBITOPERAT_BORR  0x04
#define CRABBITOPERAT_BXOR  0x08


#ifdef  __cplusplus
extern "C" {
#endif

//取浮点数的整数部分
CrabInt  CrabFloatTrunc(CrabFloat V);

//取浮点数的小数点部分
CrabFloat  CrabFloatFract(CrabFloat V);

//浮点数求余
CrabFloat  CrabFloatMod(CrabFloat V1, CrabFloat V2);

//比较整型
CrabByte  CrabCompareInt(CrabInt V1, CrabInt V2);

//比较无符号整型
CrabByte  CrabCompareUint(CrabUint V1, CrabUint V2);

//比较长整型
CrabByte  CrabCompareLong(CrabLong V1, CrabLong V2);

//比较无符号长整型
CrabByte  CrabCompareULong(CrabULong V1, CrabULong V2);

//比较浮点
CrabByte  CrabCompareFloat(CrabFloat V1, CrabFloat V2);

//比较双精浮点
CrabByte  CrabCompareDouble(CrabDouble V1, CrabDouble V2);


#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE