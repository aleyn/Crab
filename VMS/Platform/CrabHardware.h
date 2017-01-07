/******************** Copyright wisearm.com *********************************
* File Name         : CrabHardware.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 硬件配置与设置
********************************************************************************/
#ifndef __CRAB_HARDWARE_H
#define __CRAB_HARDWARE_H

#ifdef __cplusplus
 extern "C" {
#endif
   
#include "stm32ext.h"
#include "Hardware.h"
            
#define KEY_BUF_MAX   10
#define KEY_F1        0x01
#define KEY_F2        0x02
#define KEY_F3        0x04
#define KEY_F4        0x08
   
#define KEY_B1        0x14
#define KEY_B2        0x18
#define KEY_B3        0x12
#define KEY_B4        0x28
#define KEY_B5        0x24
#define KEY_B6        0x48   
   
#define BEP_TIM          9
#define BEP_CHANNEL      1
#define BEP_SCALE        (10 - 1)
#define BEP_PULSE        (9600000 / 2200)
#define BEP_WIDTH        (9600000 / 2200 / 2)
      
#define TIM_ADDR_MAX   16

void CrabHW_InitExtern();

void CrabHW_LED_Change(uint32_t LED_PIN, uint8_t Status);
#define CrabHW_LED_ChangeSys(Status)  CrabHW_LED_Change(SYS_LED, Status)


void CrabHW_BEEP_Enable();
void CrabHW_BEEP_Disable();
void CrabHW_BEEP_Start();
void CrabHW_BEEP_Stop();

uint32_t  CrabHW_KEY_Scan();
uint8_t   CrabHW_KEY_Read();
void      CrabHW_KEY_Write(uint8_t Key);

uint32_t CrabHW_GPIO_GetAddr(uint8_t Index);

uint32_t CrabHW_TIM_GetAddr(uint8_t Index);
void     CrabHW_TIM_Config(uint8_t TIM, uint32_t Period, uint32_t Prescaler);
void     CrabHW_TIM_SetPwm(uint8_t TIM, uint8_t OC, uint32_t Value);


#endif
/** @} */
