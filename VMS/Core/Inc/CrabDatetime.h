/******************** Copyright wisearm.com ************************************
* File Name         : CrabDatetime.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 日期时间函数
********************************************************************************/

#ifndef __CRAB_DATETIME__
#define __CRAB_DATETIME__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

//取得公元以来到某一年的日期总和.
CrabUint  CrabDate_GetYearSumDay(CrabWord Year);

//取得一年中从1月到指定月份的日期总和.
CrabUint  CrabDate_GetMonthSumDay(CrabWord Year, CrabWord Month);

//取得一年中某个月份的日期数
CrabUint  CrabDate_GetMonthDay(CrabWord Year, CrabWord Month);

//将单独日期编译成日期格式
CrabDate  CrabDate_Encode(CrabWord Year, CrabByte Month, CrabByte Day);

//将日期格式解译成单独日期
CrabBool  CrabDate_Decode(CrabDate Date, CrabWord __var wYear, CrabByte __var bMonth, CrabByte __var bDay);

//日期格式转为整型
CrabDate  CrabDate_Packed(TCrabDate Date);

//整型转为日期型
TCrabDate CrabDate_Unpacked(CrabUint Date);

//将单独时间编译成时间格式
CrabTime  CrabTime_Encode(CrabByte Hour, CrabByte Min, CrabByte Sec, CrabWord MSec);

//将时间格式解译成单独时间
CrabBool  CrabTime_Decode(CrabTime Time, CrabByte __var Hour, CrabByte __var Min, CrabByte __var Sec, CrabWord __var MSec);

//时间型转为整型
CrabTime  CrabTime_Packed(TCrabTime Time);

//整型转为时间型
TCrabTime CrabTime_Unpacked(CrabTime Time);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE