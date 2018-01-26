/******************** Copyright wisearm.com *********************************
* File Name         : CrabEvent.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : �¼�������
********************************************************************************/

#ifndef __CRAB_EVENT_MANAGE__
#define __CRAB_EVENT_MANAGE__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define KEY_DETAIL        1
#define KEY_PRESS         0x01000000
  
#define REMOTE_CONTROL    0x02000000
#define CONTROL_DETAIL    1
#define CONTROL_SIZE      64

//�¼�����
void CrabEventTask();

//�¼�ѹջ
void CrabEventPush(CrabUint Event);
#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE