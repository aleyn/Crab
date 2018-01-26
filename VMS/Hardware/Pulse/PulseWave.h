/******************** Copyright wisearm.com *********************************
* File Name         : PulseWave.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2017-07-18
* Last Update       : 2017-07-18
* Description       : 脉冲波单元
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
  PulseWaveIODef    A;     //A通道
  PulseWaveIODef    B;     //B通道
} PulseWaveDef;

#pragma pack(1)
typedef struct 
{
  uint32_t    Frequ;     //频率
  uint32_t    OpenMode;  //打开时的IO模式
  uint32_t    CloseMode; //关闭时的IO模式
  uint32_t    MTRMode;   //限位触发的IO模式
} PulseWaveModeDef;

#define PulseWave_MAX_COUNT   10 //脉冲波最大个数
extern uint32_t PulseWavePeriod; //脉冲波分频数据
extern uint8_t  PulseWaveCount;  //脉冲波个数

//脉冲波IO设置
void PulseWave_SetupIO(PulseWaveIODef *PulseWaveIO, uint32_t Width);

//脉冲波初始化
void    PulseWave_Init();
//脉冲波配置
void    PulseWave_ConfigAll(uint8_t Enable);
//脉冲波配置
void    PulseWave_Config(uint8_t Index, uint8_t Enable);
//脉冲波控制
int8_t  PulseWave_Control(uint8_t Index, int8_t Speed);
//检查限位开关
int8_t  PulseWave_CheckMTR(uint8_t Index, int8_t Speed);

//载入脉冲波IO数据
uint8_t PulseWave_LoadData(PulseWaveModeDef* Config, PulseWaveDef* PulseWaves[]);

#endif
/** @} */
