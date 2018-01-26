/******************** Copyright wisearm.com *********************************
* File Name         : CrabAPI.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : API注册
********************************************************************************/
#include "CrabVMS.h"
#include "CrabAPI.h"

/*******************************************************************************
* Function    : CrabRegisterApi
* Caption     : 注册所有的API函数 
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
