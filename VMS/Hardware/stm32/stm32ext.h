/******************** Copyright wisearm.com *********************************
* File Name         : stm32ext.h
* Author            : Îâ´´Ã÷(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2009-02-02
* Last Update       : 2012-08-05
* Description       : EXT firmware library.
********************************************************************************/
#ifndef __STM32EXT_H
#define __STM32EXT_H

#if defined (STM32F0)
  #include "stm32f0xx.h"
#elif defined (STM32F1)
  #include "stm32f10x.h"
  #include "stm32f10x_gpio.h"
  #include "stm32f10x_usart.h"
  #include "stm32gpio.h"
#elif defined (STM32F4)
  #include "stm32f4xx.h"
#endif

#ifdef __cplusplus
 extern "C" {
#endif

typedef uint32_t  GPIO_PORT;
typedef uint32_t  GPIO_MODE;
typedef uint32_t  GPIO_AF;

typedef union
{
  struct{
    uint16_t Pin;
    uint16_t Port;
  };
  uint32_t   PortPin;
} TGPIO_PortPin, *PGPIO_PortPin;

typedef struct
{
#if defined (STM32F1)
  GPIO_InitTypeDef;
  uint32_t            GPIO_AlterFunc;
#else  
  GPIO_InitTypeDef;
  uint16_t            GPIO_PinSource;
  uint8_t             GPIO_AlterFunc;
#endif
} GPIO_InitExTypeDef, GPIO_InitExDef;

typedef uint16_t GPIO_PIN_SET;
typedef uint32_t GPIO_PORT_SET;

/* ExPORTed constants --------------------------------------------------------*/
/* GPIO PINs define ----------------------------------------------------------*/
#define GPIO_PIN_0                  ((GPIO_PIN_SET)0x0001)  /* PIN 0 selected */
#define GPIO_PIN_1                  ((GPIO_PIN_SET)0x0002)  /* PIN 1 selected */
#define GPIO_PIN_2                  ((GPIO_PIN_SET)0x0004)  /* PIN 2 selected */
#define GPIO_PIN_3                  ((GPIO_PIN_SET)0x0008)  /* PIN 3 selected */
#define GPIO_PIN_4                  ((GPIO_PIN_SET)0x0010)  /* PIN 4 selected */
#define GPIO_PIN_5                  ((GPIO_PIN_SET)0x0020)  /* PIN 5 selected */
#define GPIO_PIN_6                  ((GPIO_PIN_SET)0x0040)  /* PIN 6 selected */
#define GPIO_PIN_7                  ((GPIO_PIN_SET)0x0080)  /* PIN 7 selected */
#define GPIO_PIN_8                  ((GPIO_PIN_SET)0x0100)  /* PIN 8 selected */
#define GPIO_PIN_9                  ((GPIO_PIN_SET)0x0200)  /* PIN 9 selected */
#define GPIO_PIN_10                 ((GPIO_PIN_SET)0x0400)  /* PIN 10 selected */
#define GPIO_PIN_11                 ((GPIO_PIN_SET)0x0800)  /* PIN 11 selected */
#define GPIO_PIN_12                 ((GPIO_PIN_SET)0x1000)  /* PIN 12 selected */
#define GPIO_PIN_13                 ((GPIO_PIN_SET)0x2000)  /* PIN 13 selected */
#define GPIO_PIN_14                 ((GPIO_PIN_SET)0x4000)  /* PIN 14 selected */
#define GPIO_PIN_15                 ((GPIO_PIN_SET)0x8000)  /* PIN 15 selected */
#define GPIO_PIN_ALL                ((GPIO_PIN_SET)0xFFFF)  /* All PINs selected */

#if defined (STM32F0)
  #define GPIO_PORT_A                 ((GPIO_PORT_SET)0x00000000)
  #define GPIO_PORT_B                 ((GPIO_PORT_SET)0x04000000)
  #define GPIO_PORT_C                 ((GPIO_PORT_SET)0x08000000)
  #define GPIO_PORT_D                 ((GPIO_PORT_SET)0x0C000000)
  #define GPIO_PORT_E                 ((GPIO_PORT_SET)0x10000000)
  #define GPIO_PORT_F                 ((GPIO_PORT_SET)0x14000000)
  #define GPIO_PORT_G                 ((GPIO_PORT_SET)0x18000000)
#elif defined (STM32F1)
  #define GPIO_PORT_A                 ((GPIO_PORT_SET)0x08000000)
  #define GPIO_PORT_B                 ((GPIO_PORT_SET)0x0C000000)
  #define GPIO_PORT_C                 ((GPIO_PORT_SET)0x10000000)
  #define GPIO_PORT_D                 ((GPIO_PORT_SET)0x14000000)
  #define GPIO_PORT_E                 ((GPIO_PORT_SET)0x18000000)
  #define GPIO_PORT_F                 ((GPIO_PORT_SET)0x1C000000)
  #define GPIO_PORT_G                 ((GPIO_PORT_SET)0x20000000)
#elif defined (STM32F4)
  #define GPIO_PORT_A                 ((GPIO_PORT_SET)0x00000000)
  #define GPIO_PORT_B                 ((GPIO_PORT_SET)0x04000000)
  #define GPIO_PORT_C                 ((GPIO_PORT_SET)0x08000000)
  #define GPIO_PORT_D                 ((GPIO_PORT_SET)0x0C000000)
  #define GPIO_PORT_E                 ((GPIO_PORT_SET)0x10000000)
  #define GPIO_PORT_F                 ((GPIO_PORT_SET)0x14000000)
  #define GPIO_PORT_G                 ((GPIO_PORT_SET)0x18000000)
  #define GPIO_PORT_H                 ((GPIO_PORT_SET)0x1C000000)
  #define GPIO_PORT_I                 ((GPIO_PORT_SET)0x20000000)
  #define GPIO_PORT_J                 ((GPIO_PORT_SET)0x24000000)
  #define GPIO_PORT_K                 ((GPIO_PORT_SET)0x28000000)
#endif

#define GPIO_NULL                   0

#define GPIO_PA(PIN)                ((GPIO_PORT_A) | (PIN))
#define GPIO_PA0                    ((GPIO_PORT_A) | (GPIO_PIN_0))
#define GPIO_PA1                    ((GPIO_PORT_A) | (GPIO_PIN_1))
#define GPIO_PA2                    ((GPIO_PORT_A) | (GPIO_PIN_2))
#define GPIO_PA3                    ((GPIO_PORT_A) | (GPIO_PIN_3))
#define GPIO_PA4                    ((GPIO_PORT_A) | (GPIO_PIN_4))
#define GPIO_PA5                    ((GPIO_PORT_A) | (GPIO_PIN_5))
#define GPIO_PA6                    ((GPIO_PORT_A) | (GPIO_PIN_6))
#define GPIO_PA7                    ((GPIO_PORT_A) | (GPIO_PIN_7))
#define GPIO_PA8                    ((GPIO_PORT_A) | (GPIO_PIN_8))
#define GPIO_PA9                    ((GPIO_PORT_A) | (GPIO_PIN_9))
#define GPIO_PA10                   ((GPIO_PORT_A) | (GPIO_PIN_10))
#define GPIO_PA11                   ((GPIO_PORT_A) | (GPIO_PIN_11))
#define GPIO_PA12                   ((GPIO_PORT_A) | (GPIO_PIN_12))
#define GPIO_PA13                   ((GPIO_PORT_A) | (GPIO_PIN_13))
#define GPIO_PA14                   ((GPIO_PORT_A) | (GPIO_PIN_14))
#define GPIO_PA15                   ((GPIO_PORT_A) | (GPIO_PIN_15))

#define GPIO_PB(PIN)                ((GPIO_PORT_B) | (PIN))
#define GPIO_PB0                    ((GPIO_PORT_B) | (GPIO_PIN_0))
#define GPIO_PB1                    ((GPIO_PORT_B) | (GPIO_PIN_1))
#define GPIO_PB2                    ((GPIO_PORT_B) | (GPIO_PIN_2))
#define GPIO_PB3                    ((GPIO_PORT_B) | (GPIO_PIN_3))
#define GPIO_PB4                    ((GPIO_PORT_B) | (GPIO_PIN_4))
#define GPIO_PB5                    ((GPIO_PORT_B) | (GPIO_PIN_5))
#define GPIO_PB6                    ((GPIO_PORT_B) | (GPIO_PIN_6))
#define GPIO_PB7                    ((GPIO_PORT_B) | (GPIO_PIN_7))
#define GPIO_PB8                    ((GPIO_PORT_B) | (GPIO_PIN_8))
#define GPIO_PB9                    ((GPIO_PORT_B) | (GPIO_PIN_9))
#define GPIO_PB10                   ((GPIO_PORT_B) | (GPIO_PIN_10))
#define GPIO_PB11                   ((GPIO_PORT_B) | (GPIO_PIN_11))
#define GPIO_PB12                   ((GPIO_PORT_B) | (GPIO_PIN_12))
#define GPIO_PB13                   ((GPIO_PORT_B) | (GPIO_PIN_13))
#define GPIO_PB14                   ((GPIO_PORT_B) | (GPIO_PIN_14))
#define GPIO_PB15                   ((GPIO_PORT_B) | (GPIO_PIN_15))

#define GPIO_PC(PIN)                ((GPIO_PORT_C) | (PIN))
#define GPIO_PC0                    ((GPIO_PORT_C) | (GPIO_PIN_0))
#define GPIO_PC1                    ((GPIO_PORT_C) | (GPIO_PIN_1))
#define GPIO_PC2                    ((GPIO_PORT_C) | (GPIO_PIN_2))
#define GPIO_PC3                    ((GPIO_PORT_C) | (GPIO_PIN_3))
#define GPIO_PC4                    ((GPIO_PORT_C) | (GPIO_PIN_4))
#define GPIO_PC5                    ((GPIO_PORT_C) | (GPIO_PIN_5))
#define GPIO_PC6                    ((GPIO_PORT_C) | (GPIO_PIN_6))
#define GPIO_PC7                    ((GPIO_PORT_C) | (GPIO_PIN_7))
#define GPIO_PC8                    ((GPIO_PORT_C) | (GPIO_PIN_8))
#define GPIO_PC9                    ((GPIO_PORT_C) | (GPIO_PIN_9))
#define GPIO_PC10                   ((GPIO_PORT_C) | (GPIO_PIN_10))
#define GPIO_PC11                   ((GPIO_PORT_C) | (GPIO_PIN_11))
#define GPIO_PC12                   ((GPIO_PORT_C) | (GPIO_PIN_12))
#define GPIO_PC13                   ((GPIO_PORT_C) | (GPIO_PIN_13))
#define GPIO_PC14                   ((GPIO_PORT_C) | (GPIO_PIN_14))
#define GPIO_PC15                   ((GPIO_PORT_C) | (GPIO_PIN_15))

#define GPIO_PD(PIN)                ((GPIO_PORT_D) | (PIN))
#define GPIO_PD0                    ((GPIO_PORT_D) | (GPIO_PIN_0))
#define GPIO_PD1                    ((GPIO_PORT_D) | (GPIO_PIN_1))
#define GPIO_PD2                    ((GPIO_PORT_D) | (GPIO_PIN_2))
#define GPIO_PD3                    ((GPIO_PORT_D) | (GPIO_PIN_3))
#define GPIO_PD4                    ((GPIO_PORT_D) | (GPIO_PIN_4))
#define GPIO_PD5                    ((GPIO_PORT_D) | (GPIO_PIN_5))
#define GPIO_PD6                    ((GPIO_PORT_D) | (GPIO_PIN_6))
#define GPIO_PD7                    ((GPIO_PORT_D) | (GPIO_PIN_7))
#define GPIO_PD8                    ((GPIO_PORT_D) | (GPIO_PIN_8))
#define GPIO_PD9                    ((GPIO_PORT_D) | (GPIO_PIN_9))
#define GPIO_PD10                   ((GPIO_PORT_D) | (GPIO_PIN_10))
#define GPIO_PD11                   ((GPIO_PORT_D) | (GPIO_PIN_11))
#define GPIO_PD12                   ((GPIO_PORT_D) | (GPIO_PIN_12))
#define GPIO_PD13                   ((GPIO_PORT_D) | (GPIO_PIN_13))
#define GPIO_PD14                   ((GPIO_PORT_D) | (GPIO_PIN_14))
#define GPIO_PD15                   ((GPIO_PORT_D) | (GPIO_PIN_15))

#define GPIO_PE(PIN)                ((GPIO_PORT_E) | (PIN))
#define GPIO_PE0                    ((GPIO_PORT_E) | (GPIO_PIN_0))
#define GPIO_PE1                    ((GPIO_PORT_E) | (GPIO_PIN_1))
#define GPIO_PE2                    ((GPIO_PORT_E) | (GPIO_PIN_2))
#define GPIO_PE3                    ((GPIO_PORT_E) | (GPIO_PIN_3))
#define GPIO_PE4                    ((GPIO_PORT_E) | (GPIO_PIN_4))
#define GPIO_PE5                    ((GPIO_PORT_E) | (GPIO_PIN_5))
#define GPIO_PE6                    ((GPIO_PORT_E) | (GPIO_PIN_6))
#define GPIO_PE7                    ((GPIO_PORT_E) | (GPIO_PIN_7))
#define GPIO_PE8                    ((GPIO_PORT_E) | (GPIO_PIN_8))
#define GPIO_PE9                    ((GPIO_PORT_E) | (GPIO_PIN_9))
#define GPIO_PE10                   ((GPIO_PORT_E) | (GPIO_PIN_10))
#define GPIO_PE11                   ((GPIO_PORT_E) | (GPIO_PIN_11))
#define GPIO_PE12                   ((GPIO_PORT_E) | (GPIO_PIN_12))
#define GPIO_PE13                   ((GPIO_PORT_E) | (GPIO_PIN_13))
#define GPIO_PE14                   ((GPIO_PORT_E) | (GPIO_PIN_14))
#define GPIO_PE15                   ((GPIO_PORT_E) | (GPIO_PIN_15))

#define GPIO_PF(PIN)                ((GPIO_PORT_F) | (PIN))
#define GPIO_PF0                    ((GPIO_PORT_F) | (GPIO_PIN_0))
#define GPIO_PF1                    ((GPIO_PORT_F) | (GPIO_PIN_1))
#define GPIO_PF2                    ((GPIO_PORT_F) | (GPIO_PIN_2))
#define GPIO_PF3                    ((GPIO_PORT_F) | (GPIO_PIN_3))
#define GPIO_PF4                    ((GPIO_PORT_F) | (GPIO_PIN_4))
#define GPIO_PF5                    ((GPIO_PORT_F) | (GPIO_PIN_5))
#define GPIO_PF6                    ((GPIO_PORT_F) | (GPIO_PIN_6))
#define GPIO_PF7                    ((GPIO_PORT_F) | (GPIO_PIN_7))
#define GPIO_PF8                    ((GPIO_PORT_F) | (GPIO_PIN_8))
#define GPIO_PF9                    ((GPIO_PORT_F) | (GPIO_PIN_9))
#define GPIO_PF10                   ((GPIO_PORT_F) | (GPIO_PIN_10))
#define GPIO_PF11                   ((GPIO_PORT_F) | (GPIO_PIN_11))
#define GPIO_PF12                   ((GPIO_PORT_F) | (GPIO_PIN_12))
#define GPIO_PF13                   ((GPIO_PORT_F) | (GPIO_PIN_13))
#define GPIO_PF14                   ((GPIO_PORT_F) | (GPIO_PIN_14))
#define GPIO_PF15                   ((GPIO_PORT_F) | (GPIO_PIN_15))

#define GPIO_PG(PIN)                ((GPIO_PORT_G) | (PIN))
#define GPIO_PG0                    ((GPIO_PORT_G) | (GPIO_PIN_0))
#define GPIO_PG1                    ((GPIO_PORT_G) | (GPIO_PIN_1))
#define GPIO_PG2                    ((GPIO_PORT_G) | (GPIO_PIN_2))
#define GPIO_PG3                    ((GPIO_PORT_G) | (GPIO_PIN_3))
#define GPIO_PG4                    ((GPIO_PORT_G) | (GPIO_PIN_4))
#define GPIO_PG5                    ((GPIO_PORT_G) | (GPIO_PIN_5))
#define GPIO_PG6                    ((GPIO_PORT_G) | (GPIO_PIN_6))
#define GPIO_PG7                    ((GPIO_PORT_G) | (GPIO_PIN_7))
#define GPIO_PG8                    ((GPIO_PORT_G) | (GPIO_PIN_8))
#define GPIO_PG9                    ((GPIO_PORT_G) | (GPIO_PIN_9))
#define GPIO_PG10                   ((GPIO_PORT_G) | (GPIO_PIN_10))
#define GPIO_PG11                   ((GPIO_PORT_G) | (GPIO_PIN_11))
#define GPIO_PG12                   ((GPIO_PORT_G) | (GPIO_PIN_12))
#define GPIO_PG13                   ((GPIO_PORT_G) | (GPIO_PIN_13))
#define GPIO_PG14                   ((GPIO_PORT_G) | (GPIO_PIN_14))
#define GPIO_PG15                   ((GPIO_PORT_G) | (GPIO_PIN_15))

#define GPIO_PH(PIN)                ((GPIO_PORT_H) | (PIN))
#define GPIO_PH0                    ((GPIO_PORT_H) | (GPIO_PIN_0))
#define GPIO_PH1                    ((GPIO_PORT_H) | (GPIO_PIN_1))
#define GPIO_PH2                    ((GPIO_PORT_H) | (GPIO_PIN_2))
#define GPIO_PH3                    ((GPIO_PORT_H) | (GPIO_PIN_3))
#define GPIO_PH4                    ((GPIO_PORT_H) | (GPIO_PIN_4))
#define GPIO_PH5                    ((GPIO_PORT_H) | (GPIO_PIN_5))
#define GPIO_PH6                    ((GPIO_PORT_H) | (GPIO_PIN_6))
#define GPIO_PH7                    ((GPIO_PORT_H) | (GPIO_PIN_7))
#define GPIO_PH8                    ((GPIO_PORT_H) | (GPIO_PIN_8))
#define GPIO_PH9                    ((GPIO_PORT_H) | (GPIO_PIN_9))
#define GPIO_PH10                   ((GPIO_PORT_H) | (GPIO_PIN_10))
#define GPIO_PH11                   ((GPIO_PORT_H) | (GPIO_PIN_11))
#define GPIO_PH12                   ((GPIO_PORT_H) | (GPIO_PIN_12))
#define GPIO_PH13                   ((GPIO_PORT_H) | (GPIO_PIN_13))
#define GPIO_PH14                   ((GPIO_PORT_H) | (GPIO_PIN_14))
#define GPIO_PH15                   ((GPIO_PORT_H) | (GPIO_PIN_15))

#define GPIO_PI(PIN)                ((GPIO_PORT_I) | (PIN))
#define GPIO_PI0                    ((GPIO_PORT_I) | (GPIO_PIN_0))
#define GPIO_PI1                    ((GPIO_PORT_I) | (GPIO_PIN_1))
#define GPIO_PI2                    ((GPIO_PORT_I) | (GPIO_PIN_2))
#define GPIO_PI3                    ((GPIO_PORT_I) | (GPIO_PIN_3))
#define GPIO_PI4                    ((GPIO_PORT_I) | (GPIO_PIN_4))
#define GPIO_PI5                    ((GPIO_PORT_I) | (GPIO_PIN_5))
#define GPIO_PI6                    ((GPIO_PORT_I) | (GPIO_PIN_6))
#define GPIO_PI7                    ((GPIO_PORT_I) | (GPIO_PIN_7))
#define GPIO_PI8                    ((GPIO_PORT_I) | (GPIO_PIN_8))
#define GPIO_PI9                    ((GPIO_PORT_I) | (GPIO_PIN_9))
#define GPIO_PI10                   ((GPIO_PORT_I) | (GPIO_PIN_10))
#define GPIO_PI11                   ((GPIO_PORT_I) | (GPIO_PIN_11))
#define GPIO_PI12                   ((GPIO_PORT_I) | (GPIO_PIN_12))
#define GPIO_PI13                   ((GPIO_PORT_I) | (GPIO_PIN_13))
#define GPIO_PI14                   ((GPIO_PORT_I) | (GPIO_PIN_14))
#define GPIO_PI15                   ((GPIO_PORT_I) | (GPIO_PIN_15))

#define GPIO_PJ(PIN)                ((GPIO_PORT_J) | (PIN))
#define GPIO_PJ0                    ((GPIO_PORT_J) | (GPIO_PIN_0))
#define GPIO_PJ1                    ((GPIO_PORT_J) | (GPIO_PIN_1))
#define GPIO_PJ2                    ((GPIO_PORT_J) | (GPIO_PIN_2))
#define GPIO_PJ3                    ((GPIO_PORT_J) | (GPIO_PIN_3))
#define GPIO_PJ4                    ((GPIO_PORT_J) | (GPIO_PIN_4))
#define GPIO_PJ5                    ((GPIO_PORT_J) | (GPIO_PIN_5))
#define GPIO_PJ6                    ((GPIO_PORT_J) | (GPIO_PIN_6))
#define GPIO_PJ7                    ((GPIO_PORT_J) | (GPIO_PIN_7))
#define GPIO_PJ8                    ((GPIO_PORT_J) | (GPIO_PIN_8))
#define GPIO_PJ9                    ((GPIO_PORT_J) | (GPIO_PIN_9))
#define GPIO_PJ10                   ((GPIO_PORT_J) | (GPIO_PIN_10))
#define GPIO_PJ11                   ((GPIO_PORT_J) | (GPIO_PIN_11))
#define GPIO_PJ12                   ((GPIO_PORT_J) | (GPIO_PIN_12))
#define GPIO_PJ13                   ((GPIO_PORT_J) | (GPIO_PIN_13))
#define GPIO_PJ14                   ((GPIO_PORT_J) | (GPIO_PIN_14))
#define GPIO_PJ15                   ((GPIO_PORT_J) | (GPIO_PIN_15))

#define GPIO_SETUP(A, B, C, D) (((uint32_t)A << 24) | ((uint32_t) B<< 16) | ((uint32_t)C << 8) | (uint32_t)D)

#define GPIO_AF_NULL      0

#if defined (STM32F0)
  #define GPIO_Speed_Low   GPIO_Speed_2MHz
  #define GPIO_Speed_Mid   GPIO_Speed_10MHz
  #define GPIO_Speed_High  GPIO_Speed_50MHz
#elif defined (STM32F1)
  #define GPIO_Speed_Low   GPIO_Speed_2MHz
  #define GPIO_Speed_Mid   GPIO_Speed_10MHz
  #define GPIO_Speed_High  GPIO_Speed_50MHz
#elif defined (STM32F4)
  #define GPIO_Speed_Low   GPIO_Speed_2MHz
  #define GPIO_Speed_Mid   GPIO_Speed_50MHz
  #define GPIO_Speed_High  GPIO_Speed_100MHz
#endif

#define GPIO_MODE_IND     GPIO_SETUP(GPIO_Mode_IN,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_DOWN)
#define GPIO_MODE_INU     GPIO_SETUP(GPIO_Mode_IN,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_UP)
#define GPIO_MODE_GET     GPIO_SETUP(GPIO_Mode_IN,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_NOPULL)
#define GPIO_MODE_PUT     GPIO_SETUP(GPIO_Mode_OUT, GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_NOPULL)
#define GPIO_MODE_INT     GPIO_SETUP(GPIO_Mode_IN,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_UP)
#define GPIO_MODE_KEY     GPIO_SETUP(GPIO_Mode_IN,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_NOPULL)
#define GPIO_MODE_LED     GPIO_SETUP(GPIO_Mode_OUT, GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_DOWN)
#define GPIO_MODE_DAT     GPIO_SETUP(GPIO_Mode_OUT, GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_UP)
#define GPIO_MODE_ADC     GPIO_SETUP(GPIO_Mode_AN,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_NOPULL)
#define GPIO_MODE_I2C     GPIO_SETUP(GPIO_Mode_AF,  GPIO_Speed_Low,  GPIO_OType_OD, GPIO_PuPd_NOPULL)
#define GPIO_MODE_PWM     GPIO_SETUP(GPIO_Mode_AF,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_UP)
#define GPIO_MODE_USB     GPIO_SETUP(GPIO_Mode_AF,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_NOPULL)
#define GPIO_MODE_USART   GPIO_SETUP(GPIO_Mode_AF,  GPIO_Speed_Mid,  GPIO_OType_PP, GPIO_PuPd_UP)
#define GPIO_MODE_SPI     GPIO_SETUP(GPIO_Mode_AF,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_NOPULL)

#define GPIO_GetInputBit(PortPin)                GPIO_GetBit(PortPin, GPIO_Mode_IN)
#define GPIO_GetOutputBit(PortPin)               GPIO_GetBit(PortPin, GPIO_Mode_OUT)
#define GPIO_GetInputBitMap(PortPin, Count)      GPIO_GetBitMap(PortPin, GPIO_Mode_IN,  Count)
#define GPIO_GetOutputBitMap(PortPin, Count)     GPIO_GetBitMap(PortPin, GPIO_Mode_OUT, Count)

void     GPIO_InitEx(GPIO_TypeDef* GPIOx, GPIO_InitExDef* GPIO_InitStruct);
void     GPIO_InitPort(GPIO_PORT PortPin, GPIO_MODE Mode, GPIO_AF AlterFunc);

uint8_t  GPIO_GetBit(GPIO_PORT PortPin, uint8_t InOut);
void     GPIO_SetBit(GPIO_PORT PortPin, uint8_t BitValue);
void     GPIO_ToggleBit(GPIO_PORT PortPin);

uint32_t GPIO_GetBitMap(GPIO_PORT *PortPinMap, uint8_t InOut, uint32_t Count);
void     GPIO_SetBitMap(GPIO_PORT *PortPinMap, uint32_t BitMapValue, uint32_t Count);

uint32_t GPIO_PortToSrc(GPIO_PORT PortPin);
void     EXTI_InitLine(GPIO_PORT PortPin);

#if defined (STM32F0)
  #define SPI_SendData(a, b)      SPI_SendData8(a, b)
  #define SPI_ReceiveData(a)      SPI_ReceiveData8(a)
  #define SPI_GetStatus(a, b)     SPI_I2S_GetFlagStatus(a, b)
#elif defined (STM32F1)
  #define SPI_SendData(a, b)      SPI_I2S_SendData(a, b)
  #define SPI_ReceiveData(a)      SPI_I2S_ReceiveData(a)
  #define SPI_GetStatus(a, b)     SPI_I2S_GetFlagStatus(a, b)
#elif defined (STM32F4)
  #if !defined(SPI_SendData)
    #define SPI_SendData(a, b)      SPI_I2S_SendData(a, b)
  #endif
  #if !defined(SPI_ReceiveData)
    #define SPI_ReceiveData(a)      SPI_I2S_ReceiveData(a)
  #endif
  #define SPI_GetStatus(a, b)     SPI_GetFlagStatus(a, b)
#endif

void USART_InitEasy(USART_TypeDef *USART, uint32_t BaudRate);


#define  LED_OFF   0
#define  LED_LOW   1
#define  LED_HIGH  2
#define  LED_GREEN 1
#define  LED_RED   2
#define  TurnLED(a,b)  TurnLed(a,b)

void TurnLed(GPIO_PORT LED_PIN, uint8_t Status);

#ifdef __cplusplus
}
#endif
#endif 
/*******************************************************************************
**                                END OF FILE                                 **
*******************************************************************************/
