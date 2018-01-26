/******************** Copyright wisearm.com *********************************
* File Name         : CrabMicokitSensor.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : �������ӿ�
********************************************************************************/
#include "CrabVMS.h"

crabapi CrabApiGetADC       ();
crabapi CrabApiGetSensor    ();

/*******************************************************************************
* Function    : CrabRegisterSensorApi
* Caption     : ע�ᴫ�����˿�API���� 
* Description : .
*******************************************************************************/
void CrabRegisterSensorApi()
{
  CrabExtern_RegisterApi("GetADC", CrabApiGetADC);
  CrabExtern_RegisterApi("GetSensor", CrabApiGetSensor);
}

/*******************************************************************************
* Function    : CrabGetADC
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiGetADC()
{
  CrabUint Port = CrabExtern_GetPortAddr();
  uint32_t I;
  uint32_t nValue = 0;
  
  if (Port > 0)
  {
    I = Port - 1;
  }
  else
  {
    I = 0;
  }
  
  while (I<8)
  {
    nValue += ADCValue[I];
    I+=2;
  }
  
  nValue >>= 2;
  
  //CrabExtern_ReturnUintValue(nValue);
  CrabExtern_WriteToPortAsUint(nValue);
}

/*******************************************************************************
* Function    : CrabApiGetSensor
* Caption     : ��ȡ����������
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiGetSensor ()
{
  CrabUint Port = CrabExtern_GetPortAddr();
  uint32_t I;
  uint32_t nValue = 0;
  uint16_t Result;
  
  if (Port > 0)
  {
    I = Port - 1;
  }
  else
  {
    I = 0;
  }
  
  while (I<8)
  {
    nValue += ADCValue[I];
    I+=2;
  }
  
  nValue >>=2;
  
  if (nValue)
  {
    Result = (nValue * 10) / 307;
  }
  else
  {
    Result = 0;
  }
  
  CrabExtern_WriteToPortAsUShort(Result);
}
