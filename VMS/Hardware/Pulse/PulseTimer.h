/******************** Copyright wisearm.com *********************************
* File Name         : PulseTimer.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2017-07-19
* Description       : 定时脉冲控制
********************************************************************************/
#ifndef __PULSE_TIMER_H
#define __PULSE_TIMER_H

#ifdef __cplusplus
 extern "C" {
#endif
   
#include "stm32ext.h"
      
#define TIM_ADDR_MAX   16
   
//定时脉冲地址
uint32_t  PulseTimer_GetFrequ(uint8_t Index);
//定时脉冲配置
void      PulseTimer_Config(uint8_t TIM, uint32_t Period, uint32_t Prescaler);
//定时脉冲配置，频率方式
uint32_t  PulseTimer_ConfigEx(uint8_t TIM, uint32_t Frequ);
//计算定时脉冲宽度
uint32_t  PulseTimer_CalcWidth(uint32_t Period, int8_t Speed);
//定时脉冲输出
void      PulseTimer_SetOutput(uint8_t TIM, uint8_t OC, uint32_t Width);
//定时脉冲中断
void      PulseTimer_Interrupt(uint8_t TIM, uint8_t Status);
#endif
/** @} */
