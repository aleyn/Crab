/******************** Copyright wisearm.com *********************************
* File Name         : CrabHardware.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : Ӳ������������
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
  uint8_t   Active;  //����: true = ��, false = �ر�
  uint8_t   Speed;   //�ٶ�: 0 - 100
  uint32_t  Frequ;   //Ƶ��: 0 - 100000
  uint8_t   Polar;   //����: 0 = ����, 1 = ����
  
  uint8_t   TIM;     //��ʱ��
  uint8_t   A_CH;    //���ͨ��A
  uint8_t   B_CH;    //���ͨ��B
  uint32_t  A_IO;    //Aͨ��IO
  uint32_t  B_IO;    //Bͨ��IO
} CrabMotorDef;   
   
//Ӳ����ʼ��
void CrabHW_InitExtern();

//Ӳ����λ
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

//���ź��ж�
void SECOND_IRQHandler(void);

//�������ź�
void CrabSetupSecondEvent(uint8_t Status);
#endif
/** @} */
