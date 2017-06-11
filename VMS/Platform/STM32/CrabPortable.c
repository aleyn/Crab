/******************** Copyright wisearm.com *********************************
* File Name         : CrabPortable.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 应用
********************************************************************************/
#include "CrabVMS.h"

//extern uint16_t ADCValue[];

extern uint16_t BoardKey;
extern uint16_t RemoteKey;

extern CrabMotorDef CrabMotor[];

crabapi CrabGetKey ();
crabapi CrabGetInput();
crabapi CrabSetLED ();
crabapi CrabGetGPIO ();
crabapi CrabSetGPIO ();
crabapi CrabGetADC ();
crabapi CrabApiGetSensor ();

crabapi CrabGetMotorActive();
crabapi CrabSetMotorActive();
crabapi CrabGetMotorSpeed();
crabapi CrabSetMotorSpeed();
crabapi CrabGetMotorFrequ();
crabapi CrabSetMotorFrequ();
crabapi CrabGetMotorPolar();
crabapi CrabSetMotorPolar();

/*******************************************************************************
* Function    : CrabRegisterPortApi
* Caption     : 注册轻端口API函数 
* Description : .
*******************************************************************************/
void    CrabRegisterPortApi()
{
  CrabExtern_RegisterApi("GetKey", CrabGetKey);
  CrabExtern_RegisterApi("GetInput", CrabGetInput);  
  CrabExtern_RegisterApi("SetLED", CrabSetLED);
  CrabExtern_RegisterApi("GetGPIO", CrabGetGPIO);
  CrabExtern_RegisterApi("SetGPIO", CrabSetGPIO);
  CrabExtern_RegisterApi("GetADC", CrabGetADC);
  CrabExtern_RegisterApi("GetSensor", CrabApiGetSensor);
  
  CrabExtern_RegisterApi("GetMotorActive", CrabGetMotorActive);
  CrabExtern_RegisterApi("SetMotorActive", CrabSetMotorActive);
  CrabExtern_RegisterApi("GetMotorSpeed", CrabGetMotorSpeed);
  CrabExtern_RegisterApi("SetMotorSpeed", CrabSetMotorSpeed);
  CrabExtern_RegisterApi("GetMotorFrequ", CrabGetMotorFrequ);
  CrabExtern_RegisterApi("SetMotorFrequ", CrabSetMotorFrequ);
  CrabExtern_RegisterApi("GetMotorPolar", CrabGetMotorPolar);
  CrabExtern_RegisterApi("SetMotorPolar", CrabSetMotorPolar);
}

/*******************************************************************************
* Function    : CrabGetKey
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetKey()
{
  CrabUShort Key = BoardKey; 
    
  BoardKey = 0;
  CrabExtern_WriteToPortAsUShort(Key);
  
}

/*******************************************************************************
* Function    : CrabGetInput
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetInput()
{
  CrabUShort Key = RemoteKey; 
  
  RemoteKey = 0;
  CrabExtern_WriteToPortAsUShort(Key);
}

/*******************************************************************************
* Function    : CrabSetLED
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabSetLED()
{
  CrabUint    Port = CrabExtern_GetPortAddr();
  CrabUint    gPort = 0;
  CrabByte    Value;
  
  //CrabUint nValue = CrabExtern_GetUintParam(1);
  if (!CrabExtern_ReadFromPortAsByte(Value)) return;
  
  switch (Port)
  {
    case 1:
    {
      gPort = LED_1;
      break;
    }
    case 2:
    {
      gPort = LED_2;
      break;
    }
  }

  if (gPort)
  {
    CrabHW_LED_Change(gPort, Value);
  }

}

/*******************************************************************************
* Function    : CrabGetGPIO
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetGPIO()
{
  CrabUint Port = CrabExtern_GetPortAddr();
  CrabUint gPort = CrabHW_GPIO_GetAddr(Port);
  CrabByte Value = 0;

  if (gPort)
  {
    GPIO_InitPort(gPort, GPIO_MODE_GET, 0);
    Value = GPIO_GetInputBit(gPort);
  }
  
  CrabExtern_WriteToPortAsByte(Value);
}

/*******************************************************************************
* Function    : CrabSetGPIO
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabSetGPIO()
{
  CrabUint Port = CrabExtern_GetPortAddr();
  CrabUint gPort = CrabHW_GPIO_GetAddr(Port);
  CrabByte Value;
  
  if (!CrabExtern_ReadFromPortAsByte(Value)) return;

  if (gPort)
  {
    GPIO_InitPort(gPort, GPIO_MODE_PUT, 0);
    GPIO_SetBit(gPort, Value);
  }  
}

/*******************************************************************************
* Function    : CrabGetADC
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetADC()
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
* Caption     : 获取传感器数据
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

/*******************************************************************************
* Function    : CrabGetMotorActive
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetMotorActive()
{
  CrabUint Port = CrabExtern_GetPortAddr();
  CrabBool Active;
  
  switch (Port)
  {
    case 0x10:
    {
      Active = CrabMotor[0].Active;
      break;
    }
    case 0x20:
    {
      Active = CrabMotor[1].Active;
      break;
    }
    default:
    {
      Active = CrabFalse;
    }
  }
  
  CrabExtern_WriteToPortAsBool(Active);
}

/*******************************************************************************
* Function    : CrabSetMotorActive
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabSetMotorActive()
{
  CrabUint Port = CrabExtern_GetPortAddr();
  CrabBool Active;
  CrabMotorDef *Motor;
  
  if (!CrabExtern_ReadFromPortAsBool(Active)) return;
  
  switch (Port)
  {
    case 0x10:
    {
      Motor = &CrabMotor[0];
      break;
    }
    case 0x20:
    {
      Motor = &CrabMotor[1];
      break;
    }
    default:
    {
      return;
    }
  }
  
  Motor->Active = Active;
  
  if (Active)
  {
    Motor->Speed = 50;
    Motor->Frequ = 1000;
    Motor->Polar = 0;
  }
  else
  {
    Motor->Speed = 0;
    Motor->Frequ = 0;
    Motor->Polar = 0;
  }
  
  CrabHW_MotorControl(Motor, CrabTrue);
}

/*******************************************************************************
* Function    : CrabGetMotorSpeed
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetMotorSpeed()
{
  CrabUint      Port = CrabExtern_GetPortAddr();
  CrabUint      Speed;
    
  switch (Port)
  {
    case 0x11:
    {
      Speed = CrabMotor[0].Speed;
      break;
    }
    case 0x21:
    {
      Speed = CrabMotor[1].Speed;
      break;
    }
    default:
    {
      Speed = 0;
    }
  }
  
  CrabExtern_WriteToPortAsUint(Speed);
}

/*******************************************************************************
* Function    : CrabSetMotorSpeed
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabSetMotorSpeed()
{
  CrabUint      Port = CrabExtern_GetPortAddr();
  CrabMotorDef *Motor;
  CrabUint      Speed;
  
  if (!CrabExtern_ReadFromPortAsUint(Speed)) return;
  
  switch (Port)
  {
    case 0x11:
    {
      Motor = &CrabMotor[0];
      break;
    }
    case 0x21:
    {
      Motor = &CrabMotor[1];
      break;
    }
    default:
    {
      return;
    }
  }
  
  if (Motor->Active != CrabTrue) return;
  if (Speed > 100) Speed = 100;

  Motor->Speed = Speed;
  CrabHW_MotorControl(Motor, CrabFalse);
}

/*******************************************************************************
* Function    : CrabGetMotorFrequ
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetMotorFrequ()
{
  CrabUint      Port = CrabExtern_GetPortAddr();
  CrabUint      Frequ;
    
  switch (Port)
  {
    case 0x12:
    {
      Frequ = CrabMotor[0].Frequ;
      break;
    }
    case 0x22:
    {
      Frequ = CrabMotor[1].Frequ;
      break;
    }
    default:
    {
      Frequ = 0;
    }
  }
  
  CrabExtern_WriteToPortAsUint(Frequ);
}

/*******************************************************************************
* Function    : CrabSetMotorFrequ
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabSetMotorFrequ()
{
  CrabUint      Port = CrabExtern_GetPortAddr();
  CrabMotorDef *Motor;
  CrabUint      Frequ;
  
  if (!CrabExtern_ReadFromPortAsUint(Frequ)) return;
  
  switch (Port)
  {
    case 0x12:
    {
      Motor = &CrabMotor[0];
      break;
    }
    case 0x22:
    {
      Motor = &CrabMotor[1];
      break;
    }
    default:
    {
      return;
    }
  }
  
  if (Motor->Active != CrabTrue) return;
  
  if (Frequ > 100000) Frequ = 100000;
  
  Motor->Frequ = Frequ;
  CrabHW_MotorControl(Motor, CrabFalse);
}

/*******************************************************************************
* Function    : CrabGetMotorPolar
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetMotorPolar()
{
  CrabUint      Port = CrabExtern_GetPortAddr();
  CrabByte      Polar;
    
  switch (Port)
  {
    case 0x13:
    {
      Polar = CrabMotor[0].Polar;
      break;
    }
    case 0x23:
    {
      Polar = CrabMotor[1].Polar;
      break;
    }
    default:
    {
      Polar = 0;
    }
  }
  
  CrabExtern_WriteToPortAsByte(Polar);
}

/*******************************************************************************
* Function    : CrabSetMotorPolar
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabSetMotorPolar()
{
  CrabUint      Port = CrabExtern_GetPortAddr();
  CrabMotorDef *Motor;
  CrabByte      Polar;
  
  if (!CrabExtern_ReadFromPortAsByte(Polar)) return;
  
  switch (Port)
  {
    case 0x13:
    {
      Motor = &CrabMotor[0];
      break;
    }
    case 0x23:
    {
      Motor = &CrabMotor[1];
      break;
    }
    default:
    {
      return;
    }
  }
  
  if (Motor->Active != CrabTrue) return;
  
  if (Polar > 0)
  {
    Motor->Polar = CrabTrue;
  }
  else
  {
    Motor->Polar = CrabFalse;
  }
  
  CrabHW_MotorControl(Motor, CrabFalse);
}
