/******************** Copyright wisearm.com *********************************
* File Name         : PulseWave.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2017-07-18
* Last Update       : 2017-07-18
* Description       : ���岨��Ԫ
********************************************************************************/
#ifndef __PULSEWAVE_H
#define __PULSEWAVE_H

#ifdef __cplusplus
 extern "C" {
#endif
   
#include "stm32ext.h"
#include "PulseTimer.h"

#pragma pack(1)
typedef struct
{
  uint8_t     TIM;
  uint8_t     OC;
  uint8_t     GIO;
  uint8_t     AF;
  uint8_t     MTR;
} PulseWaveIODef;

#pragma pack(1)
typedef struct
{  
  PulseWaveIODef    A;     //Aͨ��
  PulseWaveIODef    B;     //Bͨ��
} PulseWaveDef;

#pragma pack(1)
typedef struct 
{
  uint32_t    Frequ;     //Ƶ��
  uint32_t    OpenMode;  //��ʱ��IOģʽ
  uint32_t    CloseMode; //�ر�ʱ��IOģʽ
  uint32_t    MTRMode;   //��λ������IOģʽ
} PulseWaveModeDef;

#define PulseWave_MAX_COUNT   10 //���岨������
extern uint32_t PulseWavePeriod; //���岨��Ƶ����
extern uint8_t  PulseWaveCount;  //���岨����

//���岨IO����
void PulseWave_SetupIO(PulseWaveIODef *PulseWaveIO, uint32_t Width);

//���岨��ʼ��
void    PulseWave_Init();
//���岨����
void    PulseWave_ConfigAll(uint8_t Enable);
//���岨����
void    PulseWave_Config(uint8_t Index, uint8_t Enable);
//���岨����
int8_t  PulseWave_Control(uint8_t Index, int8_t Speed);
//�����λ����
int8_t  PulseWave_CheckMTR(uint8_t Index, int8_t Speed);

//�������岨IO����
uint8_t PulseWave_LoadData(PulseWaveModeDef* Config, PulseWaveDef* PulseWaves[]);

#endif
/** @} */
