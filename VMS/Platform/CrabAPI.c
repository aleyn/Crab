/******************** Copyright wisearm.com *********************************
* File Name         : CrabAPI.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : APIע��
********************************************************************************/
#include "CrabVMS.h"
#include "CrabAPI.h"

/*******************************************************************************
* Function    : CrabRegisterApi
* Caption     : ע�����е�API���� 
* Description : .
*******************************************************************************/
void CrabRegisterApi()
{
  CrabRegisterClockApi();
  CrabRegisterStaticApi();
  CrabRegisterDefaultApi();
  CrabRegisterPortApi();
  CrabRegisterFuncApi();
  CrabRegisterSensorApi();
}
