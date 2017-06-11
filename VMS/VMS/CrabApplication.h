/******************** Copyright wisearm.com *********************************
* File Name         : CrabApplication.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 应用程序运行器
********************************************************************************/

#ifndef __CRAB_APP_MANAGE__
#define __CRAB_APP_MANAGE__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

//初始化虚拟机环境
void CrabApplicationInit();

//更改虚拟机运行状态
void CrabChangeAppState(CrabByte State);

//应用任务
void CrabApplicationTask();

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE