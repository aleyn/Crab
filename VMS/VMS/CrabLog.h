/******************** Copyright wisearm.com *********************************
* File Name         : CrabLog.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2017-08-19
* Description       : ��־��ʽ
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