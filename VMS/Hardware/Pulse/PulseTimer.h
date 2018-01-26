/******************** Copyright wisearm.com *********************************
* File Name         : PulseTimer.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2017-07-19
* Description       : ��ʱ�������
********************************************************************************/
#ifndef __PULSE_TIMER_H
#define __PULSE_TIMER_H

#ifdef __cplusplus
 extern "C" {
#endif
   
#include "stm32ext.h"
      
#define TIM_ADDR_MAX   16
   
//��ʱ�����ַ
uint32_t  PulseTimer_GetFrequ(uint8_t Index);
//��ʱ��������
void      PulseTimer_Config(uint8_t TIM, uint32_t Period, uint32_t Prescaler);
//��ʱ�������ã�Ƶ�ʷ�ʽ
uint32_t  PulseTimer_ConfigEx(uint8_t TIM, uint32_t Frequ);
//���㶨ʱ������
uint32_t  PulseTimer_CalcWidth(uint32_t Period, int8_t Speed);
//��ʱ�������
void      PulseTimer_SetOutput(uint8_t TIM, uint8_t OC, uint32_t Width);
//��ʱ�����ж�
void      PulseTimer_Interrupt(uint8_t TIM, uint8_t Status);
#endif
/** @} */
