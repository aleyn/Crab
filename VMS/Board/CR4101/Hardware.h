/******************** (C)Copyright wisearm.com *********************************
* File Name         : Hardware.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2016-02-18
* Last Update       : 2016-11-16
* Description       : 硬件配置与设置
********************************************************************************/
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f4xx.h"
#include "stm32ext.h"
#include "eeprom.h"
#include "spiflash.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_gap.h"
#include "nRF24L01.h"
#include "PulseTimer.h"
#include "PulseWave.h"

//核心系统IO
#define SYS_LED               GPIO_PB10
#define SYS_ESC               GPIO_PB2

//硬件驱动调试
#ifdef  CRABVMS_DEBUG
#define DEBUG_KEY             GPIO_PB8
#define DEBUG_LED             GPIO_PA6
#endif   
   
//USB
#define USB_DM                GPIO_PA11
#define USB_DP                GPIO_PA12
#define USB_PULL              GPIO_PC13

//秒信号定时器  TIM6
#define SECOND_TIM            TIM10
#define SECOND_TIM_IDX        10
//秒信号定时器校准值
#define SECOND_CALI           10
//秒信号中断函数
#define SECOND_IRQHandler     TIM1_UP_TIM10_IRQHandler
#define SECOND_IRQn           TIM1_UP_TIM10_IRQn
   
#define BEP_IO                GPIO_PA2
#define BEP_TIM               9
#define BEP_CHANNEL           1
#define BEP_AF                GPIO_AF_TIM9
   
#define LED_1                 GPIO_PA7
#define LED_2                 GPIO_PA6

#define MOTOR_COUNT           2

#define MOTO1_TIM             5
#define MOTO1_AF              GPIO_AF_TIM5
#define MOTO1_A_IO            GPIO_PA0
#define MOTO1_A_CH            1
#define MOTO1_B_IO            GPIO_PA1
#define MOTO1_B_CH            2

#define MOTO2_TIM             2
#define MOTO2_AF              GPIO_AF_TIM2
#define MOTO2_A_IO            GPIO_PA3
#define MOTO2_A_CH            4
#define MOTO2_B_IO            GPIO_PA5
#define MOTO2_B_CH            1  

#define KEY_SCAN              1
#define KEY_BUFFER_MODE       0
#define KEY_1                 GPIO_PB8
#define KEY_2                 GPIO_PB9
   
#define ADC_1                 GPIO_PB0
#define ADC_2                 GPIO_PB1
#define ADC_CH1               ADC_Channel_8
#define ADC_CH2               ADC_Channel_9

#define ADC_SimpleTime        ADC_SampleTime_56Cycles  
#define ADC_REF               406
  
#define PRINTF_COM            USART1
#define PROTOCOL_COM          USART1
#define DEVICE_COM_BR         115200

#define GPIO_ADDR_MAX 16
extern const  uint32_t        GPIO_ADDR[];
extern __IO   uint16_t        ADCValue[];
extern        uint8_t         nRF24_Channel;

void Hardware_Init(void);
void Device_Init(void);

#ifdef __cplusplus
}
#endif
#endif

