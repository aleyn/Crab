/******************** Copyright wisearm.com *********************************
* File Name         : PulseWaveCfg.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2017-07-18
* Last Update       : 2017-07-18
* Description       : 脉冲波单元
********************************************************************************/
#include "PulseWave.h"
#include "Hardware.h"

const PulseWaveModeDef _PulseWaveConfig = 
{
  .Frequ = 10000,
  .OpenMode  = GPIO_MODE_PWM,
  .CloseMode  = GPIO_MODE_PUT,
};

const PulseWaveDef PulseWave1 = 
{
  .A = {
         .TIM = MOTO1_TIM,
         .OC  = MOTO1_A_CH,
         .GIO = MOTO1_A_IO,
         .AF  = MOTO1_AF,
         .MTR = 0,
       },
  .B = {
         .TIM = MOTO1_TIM,
         .OC  = MOTO1_B_CH,
         .GIO = MOTO1_B_IO,
         .AF  = MOTO1_AF,
         .MTR = 0,
       },
};

const PulseWaveDef PulseWave2 = 
{
  .A = {
         .TIM = MOTO2_TIM,
         .OC  = MOTO2_A_CH,
         .GIO = MOTO2_A_IO,
         .AF  = MOTO2_AF,
         .MTR = 0,
       },
  .B = {
         .TIM = MOTO2_TIM,
         .OC  = MOTO2_B_CH,
         .GIO = MOTO2_B_IO,
         .AF  = MOTO2_AF,
         .MTR = 0,
       },
};

uint8_t PulseWave_LoadData(PulseWaveModeDef* Config, PulseWaveDef* PulseWaves[])
{
  Config->Frequ = _PulseWaveConfig.Frequ;
  Config->OpenMode = _PulseWaveConfig.OpenMode;
  Config->CloseMode = _PulseWaveConfig.CloseMode;
  Config->MTRMode = _PulseWaveConfig.MTRMode;
  
  PulseWaves[0] = (PulseWaveDef*)&PulseWave1;
  PulseWaves[1] = (PulseWaveDef*)&PulseWave2;
  
  return 2;
}
