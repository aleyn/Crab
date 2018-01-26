/******************** Copyright wisearm.com *********************************
* File Name         : CrabLog.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2017-08-19
* Description       : 日志方式
********************************************************************************/

#ifndef __CRAB_LOG_
#define __CRAB_LOG_

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

void Log(char* Title, char* fmt, ...);  

void ShowLogo();

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE