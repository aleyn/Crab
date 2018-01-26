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

CrabInt MotorSpeed[MOTOR_COUNT] = {0};

crabapi CrabGetKey ();
crabapi CrabGetInput();
crabapi CrabSetLED ();
crabapi CrabGetGPIO ();
crabapi CrabSetGPIO ();

crabapi CrabGetMotor();
crabapi CrabSetMotor();

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

  CrabExtern_RegisterApi("GetMotor", CrabGetMotor);
  CrabExtern_RegisterApi("SetMotor", CrabSetMotor);
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
  GPIO_PORT   gPort = 0;
  CrabByte    Value;
  
  //CrabUint nValue = CrabExtern_GetUintParam(1);
  if (!CrabExtern_ReadFromPortAsByte(Value)) return;
  
  switch (Port)
  {
    case 1:
    {
#ifdef LED_1
      gPort = LED_1;
#endif
      break;
    }
    case 2:
    {
#ifdef LED_2
      gPort = LED_2;
#endif
      break;
    }
  }

  if (gPort)
  {
    LED_Output(gPort, Value);
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
  CrabUint  Port = CrabExtern_GetPortAddr();
  GPIO_PORT gPort = CrabHW_GPIO_GetAddr(Port);
  CrabByte  Value = 0;

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
  CrabUint  Port = CrabExtern_GetPortAddr();
  GPIO_PORT gPort = CrabHW_GPIO_GetAddr(Port);
  CrabByte  Value;
  
  if (!CrabExtern_ReadFromPortAsByte(Value)) return;

  if (gPort)
  {
    GPIO_InitPort(gPort, GPIO_MODE_PUT, 0);
    GPIO_SetBit(gPort, Value);
  }  
}


/*******************************************************************************
* Function    : CrabGetMotor
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetMotor()
{
  CrabUint      Port = CrabExtern_GetPortAddr();
  CrabInt       Speed;
    
  if ((Port > 0) && (Port <= MOTOR_COUNT))
  {
    Speed = MotorSpeed[Port-1];
  }
  else
  {
    Speed = 0;
  }
  
  CrabExtern_WriteToPortAsInt(Speed);
}

/*******************************************************************************
* Function    : CrabSetMotor
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabSetMotor()
{
  CrabUint      Port = CrabExtern_GetPortAddr();
  CrabInt       Speed;
  
  if (!CrabExtern_ReadFromPortAsInt(Speed)) return;
  
  if ((Port > 0) && (Port <= MOTOR_COUNT))
  {
    if (MotorSpeed[Port-1] != Speed)
    {
      PulseWave_Config(Port, Speed != 0);
      MotorSpeed[Port-1] = Speed;
    }
    PulseWave_Control(Port, Speed);
  }
  else
  {
    return;
  }
}
