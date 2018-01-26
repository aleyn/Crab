/******************** Copyright wisearm.com *********************************
* File Name         : CrabUserApp.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : �û�����ܿ�
********************************************************************************/
#include "CrabVMS.h"
#include "CrabUserApp.h"

extern CrabMotorDef CrabMotor[];

/*******************************************************************************
 * Function    : CrabApplicationReset
 * Caption     : �û�����λ�¼�
 * Description : .
 *******************************************************************************/
void CrabApplicationReset()
{
  CrabHW_Reset();
  CrabChangeBeep(0, 0);
}

/*******************************************************************************
 * Function    : CrabApplicationReset
 * Caption     : �û�����λ�¼�
 * Description : .
 *******************************************************************************/
void CrabApplicationStop()
{
  CrabChangeBeep(0, 0);

  CrabMotor[0].Active = 0;
  //CrabHW_MotorControl(&CrabMotor[0], 0);

  CrabMotor[1].Active = 0;
  //CrabHW_MotorControl(&CrabMotor[1], 0);
}

// END OF FILE