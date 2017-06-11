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
   
#define BEP_SCALE        (10 - 1)
#define BEP_PULSE        (9600000 / 2200)
#define BEP_WIDTH        (9600000 / 2200 / 2)
      
#define TIM_ADDR_MAX   16

typedef struct
{
  uint8_t   Active;  //开关: true = 打开, false = 关闭
  uint8_t   Speed;   //速度: 0 - 100
  uint32_t  Frequ;   //频率: 0 - 100000
  uint8_t   Polar;   //极性: 0 = 正向, 1 = 反向
  
  uint8_t   TIM;     //定时器
  uint8_t   A_CH;    //输出通道A
  uint8_t   B_CH;    //输出通道B
  uint32_t  A_IO;    //A通道IO
  uint32_t  B_IO;    //B通道IO
} CrabMotorDef;   
   
//硬件初始化
void CrabHW_InitExtern();

//硬件软复位
void CrabHW_Reset();

void CrabHW_LED_Change(uint32_t LED_PIN, uint8_t Status);
#define CrabHW_LED_ChangeSys(Status)  CrabHW_LED_Change(SYS_LED, Status)

void CrabHW_PutString(char *Data, uint32_t Length);

void CrabHW_BEEP_Enable();
void CrabHW_BEEP_Disable();
void CrabHW_BEEP_Start();
void CrabHW_BEEP_Stop();

uint16_t  CrabHW_KEY_Scan();
uint8_t   CrabHW_KEY_Read();
void      CrabHW_KEY_Write(uint8_t Key);

uint32_t CrabHW_GPIO_GetAddr(uint8_t Index);

uint32_t CrabHW_TIM_GetAddr(uint8_t Index);
void     CrabHW_TIM_Config(uint8_t TIM, uint32_t Period, uint32_t Prescaler);
void     CrabHW_TIM_SetPwmWithGPIO(uint8_t TIM, uint8_t OC, uint32_t GIO, uint32_t Value);

//马达控制
void CrabHW_MotorControl(CrabMotorDef *Motor, uint8_t Reset);
#endif
/** @} */
