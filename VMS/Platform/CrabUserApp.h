/******************** Copyright wisearm.com *********************************
* File Name         : CrabUserApp.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 用户程序管控
********************************************************************************/

#ifndef __CRAB_USER_APP__
#define __CRAB_USER_APP__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

//虚拟机复位事件
void CrabApplicationReset();

//虚拟机停止事件
void CrabApplicationStop();

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE