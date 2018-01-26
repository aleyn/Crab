/******************** Copyright wisearm.com *********************************
* File Name         : CrabAPI.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : APIע��
********************************************************************************/

#ifndef __CRAB_API_MANAGE__
#define __CRAB_API_MANAGE__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif
      
//ע�ᾲ̬API����
void CrabRegisterStaticApi(); 

//ע��ʱ��API����
void CrabRegisterClockApi(); 

//ע����˿�API����
void CrabRegisterPortApi();

//ע�����API����
void CrabRegisterFuncApi();

//ע�ᴫ����ר��API����
void CrabRegisterSensorApi();

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE