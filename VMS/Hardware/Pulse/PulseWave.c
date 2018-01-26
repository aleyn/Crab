/******************** Copyright wisearm.com *********************************
* File Name         : PulseWave.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2017-07-18
* Last Update       : 2017-07-18
* Description       : ���岨��Ԫ
********************************************************************************/
#include "PulseWave.h"

uint32_t PulseWavePeriod = 0; //���岨��Ƶ����
uint8_t  PulseWaveCount = 0; //���岨����

PulseWaveModeDef PulseWaveConfig;
PulseWaveDef*  PulseWaves[PulseWave_MAX_COUNT];

/*******************************************************************************
* Function    : PulseWave_Init
* Caption     : ���岨��ʼ��
* Return      : crabapi
* Description : .
*******************************************************************************/
void PulseWave_Init()
{
  PulseWaveCount = PulseWave_LoadData(&PulseWaveConfig, PulseWaves);
}

/*******************************************************************************
* Function    : PulseWave_SetupIO
* Caption     : ���岨IO����
* Return      : crabapi
* Description : .
*******************************************************************************/
void PulseWave_SetupIO(PulseWaveIODef *PulseWaveIO, uint32_t Width)
{
  if (PulseWaveIO->TIM == 0) return;

  if (Width)
  {
    GPIO_InitPort(PulseWaveIO->GIO, PulseWaveConfig.OpenMode, PulseWaveIO->AF);
    PulseTimer_SetOutput(PulseWaveIO->TIM, PulseWaveIO->OC, Width);
  }
  else
  {
    GPIO_InitPort(PulseWaveIO->GIO, PulseWaveConfig.CloseMode, 0);
    GPIO_SetBit(PulseWaveIO->GIO, 0);
    PulseTimer_SetOutput(PulseWaveIO->TIM, PulseWaveIO->OC, 0);
  }
}

/*******************************************************************************
* Function    : PulseWave_ConfigAll
* Caption     : ���岨����
*  @Param     : 1.Enable - �Ƿ񼤻�
* Return      : crabapi
* Description : .
*******************************************************************************/
void PulseWave_ConfigAll(uint8_t Enable)
{
  uint8_t I;

  for (I = 1; I <= PulseWaveCount; I++)
  {   
    PulseWave_Config(I, Enable);
  } 
}

/*******************************************************************************
* Function    : PulseWave_Config
* Caption     : ���岨����
*  @Param     : 1.Index - ���岨������
*  @Param     : 2.Enable - �Ƿ񼤻�
* Return      : crabapi
* Description : .
*******************************************************************************/
void PulseWave_Config(uint8_t Index, uint8_t Enable)
{
  uint8_t TIM;
  uint32_t Frequ;
  uint32_t OldFrequ;
  PulseWaveDef *PulseWave;
  
  if ((Index == 0) || (Index > PulseWaveCount)) return;
  PulseWave = PulseWaves[Index - 1];
  
  if (Enable)
  {
    Frequ = PulseWaveConfig.Frequ;
  }
  else
  {
    Frequ = 0;
  }

  TIM = PulseWave->A.TIM;
  OldFrequ = PulseTimer_GetFrequ(TIM);

  if ((TIM > 0) && (OldFrequ != Frequ))
  {
    PulseWavePeriod = PulseTimer_ConfigEx(TIM, Frequ);
  }
  
  if (PulseWave->A.MTR != 0)
  {
    GPIO_InitPort(PulseWave->A.MTR, PulseWaveConfig.MTRMode, 0);
  }
  
  TIM = PulseWave->B.TIM;
  OldFrequ = PulseTimer_GetFrequ(TIM);

  if ((TIM > 0) && (OldFrequ != Frequ))
  {
    PulseWavePeriod = PulseTimer_ConfigEx(TIM, Frequ);
  }    

  if (PulseWave->B.MTR != 0)
  {
    GPIO_InitPort(PulseWave->B.MTR, PulseWaveConfig.MTRMode, 0);
  }
}

/*******************************************************************************
* Function    : PulseWave_Control
* Caption     : ���岨����
*  @Param     : 1.Index - ���岨������
*  @Param     : 2.Speed - �ٶ��뼫��:
*                      0: �ر�
*                1 ~ 100: �����ٶ�
*             -1 ~ - 100: �����ٶ�
* Description : .
*******************************************************************************/
int8_t PulseWave_Control(uint8_t Index, int8_t Speed)
{
  uint32_t Width;
  PulseWaveDef *PulseWave;
  
  if ((Index == 0) || (Index > PulseWaveCount)) return 0;
  PulseWave = PulseWaves[Index - 1];
  
  if (Speed == 0)
  {
    PulseWave_SetupIO(&PulseWave->A, 0);
    PulseWave_SetupIO(&PulseWave->B, 0);
    
    return 0;
  }
    
  Width = PulseTimer_CalcWidth(PulseWavePeriod, Speed);

  if (Speed > 0)
  {
    PulseWave_SetupIO(&PulseWave->B, 0);

    if (PulseWave->A.MTR != 0)
    {
      if (GPIO_GetInputBit(PulseWave->A.MTR) == 0)
      {
        PulseWave_SetupIO(&PulseWave->A, 0);
        return 0;
      }
    }
    
    PulseWave_SetupIO(&PulseWave->A, Width);
  }
  else
  {
    PulseWave_SetupIO(&PulseWave->A, 0);
    
    if (PulseWave->B.MTR != 0)
    {
      if (GPIO_GetInputBit(PulseWave->B.MTR) == 0)
      {
        PulseWave_SetupIO(&PulseWave->B, 0);
        return 0;
      }
    }
    
    PulseWave_SetupIO(&PulseWave->B, Width);
  }
  
  return Speed;
}

/*******************************************************************************
* Function    : PulseWave_CheckMTR
* Caption     : �����λ����
*  @Param     : 1.Index - ���岨������
*  @Param     : 2.Speed - �ٶ��뼫��:
*                      0: �ر�
*                1 ~ 100: �����ٶ�
*             -1 ~ - 100: �����ٶ�
* Description : .
*******************************************************************************/
int8_t  PulseWave_CheckMTR(uint8_t Index, int8_t Speed)
{
  PulseWaveDef *PulseWave;
  
  if ((Index == 0) || (Index > PulseWaveCount)) return 0;
  PulseWave = PulseWaves[Index - 1];
  
  if (Speed == 0)
  {    
    return 0;
  }
    
  if (Speed > 0)
  {
    if (PulseWave->A.MTR != 0)
    {
      if (GPIO_GetInputBit(PulseWave->A.MTR) == 0)
      {
        PulseWave_SetupIO(&PulseWave->A, 0);
        return 0;
      }
    }    
  }
  else
  {    
    if (PulseWave->B.MTR != 0)
    {
      if (GPIO_GetInputBit(PulseWave->B.MTR) == 0)
      {
        PulseWave_SetupIO(&PulseWave->B, 0);
        return 0;
      }
    }
  }
  
  return Speed;
}