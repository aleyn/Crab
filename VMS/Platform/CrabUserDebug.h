/******************** Copyright wisearm.com *********************************
* File Name         : CrabUserDebug.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : �û��Զ���Ӳ����������
********************************************************************************/

#ifndef __CRAB_USER_DEBUG_
#define __CRAB_USER_DEBUG_

#include "CrabBaseType.h"
#include "FreeRTOS.h"
#include "task.h"

#ifdef  __cplusplus
extern "C" {
#endif

//��������
void CrabUserDebugTask();
void CrabUserDebug();

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE