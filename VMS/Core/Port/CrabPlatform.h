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

#ifdef  __ICCARM__  
#define __flash _Pragma("location=\".rodata\"")
#define __cache _Pragma("location=\".ccmram\"")
#define __ram   _Pragma("location=\".data\"")
#else
#define __flash
#define __cache
#define __ram
#endif

#ifdef __BORLANDC__
  #define CrabMemAlloc(a, b)  (a)malloc(b)    //申请内存
  #define CrabMemFree(a)      free(a)         //释放内存
  #define CrabMemFZero(a,b)   memset(a,0,b)   //内存清零
  #define CrabMemFill(a,b,c)  memset(a,c,b)   //内存填充
  #define CrabMemCopy(a,b,c)  memcpy(a,b,c)   //内存复制
#else
  #define CrabMemAlloc(a, b)  (a)malloc(b)    //申请内存
  #define CrabMemFree(a)      free(a)         //释放内存
  #define CrabMemFZero(a,b)   memset(a,0,b)   //内存清零
  #define CrabMemFill(a,b,c)  memset(a,c,b)   //内存填充
  #define CrabMemCopy(a,b,c)  memcpy(a,b,c)   //内存复制, 在IAR中，调用此函数需要加 #include "string.h"
#endif

#ifdef __BORLANDC__
  #define strcasecmp          stricmp
  #define strncasecmp         strnicmp
  #define StrToInt            atoi            //字符串转为整型
  #define StrToFloat          atof            //字符串转为浮点型
  #define IntToStr            itoa            //整形转为字符串
  #define FloatToStr          ftoa            //浮点型转为字符串
#else
  #define strcasecmp          stricmp
  #define strncasecmp         strnicmp
  #define StrToInt            atoi            //字符串转为整型
  #define StrToFloat          atof            //字符串转为浮点型
  #define IntToStr            itoa            //整形转为字符串
  #define FloatToStr          ftoa            //浮点型转为字符串
#endif  

//注册API函数
void CrabRegisterApi();

//EVENT 事件开关
crabapi CrabEventIntr (CrabBool State);

//标准输入API
crabapi CrabInput (CrabUint Type, CrabAnsi Buffer, PCrabUint Length);

//标准输出API
crabapi CrabPrint (CrabAnsi Text, CrabUint Length, CrabBool LineEnd);

//延时API，毫秒
crabapi CrabDelay (CrabUint MSec);  
  
#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE