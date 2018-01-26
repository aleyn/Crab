/******************** Copyright wisearm.com *********************************
* File Name         : stm32gpio_mode.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2009-02-02
* Last Update       : 2017-07-18
* Description       : GPIO Mode define.
********************************************************************************/
#ifndef __STM32EXT_GPIO_MODE_H
#define __STM32EXT_GPIO_MODE_H

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

#define GPIO_MODE_IHPD    GPIO_SETUP(GPIO_Mode_IN,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_DOWN)
#define GPIO_MODE_IHPU    GPIO_SETUP(GPIO_Mode_IN,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_UP)
#define GPIO_MODE_IHPN    GPIO_SETUP(GPIO_Mode_IN,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_NOPULL)

#define GPIO_MODE_IHOD    GPIO_SETUP(GPIO_Mode_IN,  GPIO_Speed_High, GPIO_OType_OD, GPIO_PuPd_DOWN)
#define GPIO_MODE_IHOU    GPIO_SETUP(GPIO_Mode_IN,  GPIO_Speed_High, GPIO_OType_OD, GPIO_PuPd_UP)
#define GPIO_MODE_IHON    GPIO_SETUP(GPIO_Mode_IN,  GPIO_Speed_High, GPIO_OType_OD, GPIO_PuPd_NOPULL)

#define GPIO_MODE_OHPD    GPIO_SETUP(GPIO_Mode_OUT,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_DOWN)
#define GPIO_MODE_OHPU    GPIO_SETUP(GPIO_Mode_OUT,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_UP)
#define GPIO_MODE_OHPN    GPIO_SETUP(GPIO_Mode_OUT,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_NOPULL)

#define GPIO_MODE_OHOD    GPIO_SETUP(GPIO_Mode_OUT,  GPIO_Speed_High, GPIO_OType_OD, GPIO_PuPd_DOWN)
#define GPIO_MODE_OHOU    GPIO_SETUP(GPIO_Mode_OUT,  GPIO_Speed_High, GPIO_OType_OD, GPIO_PuPd_UP)
#define GPIO_MODE_OHON    GPIO_SETUP(GPIO_Mode_OUT,  GPIO_Speed_High, GPIO_OType_OD, GPIO_PuPd_NOPULL)

#define GPIO_MODE_AHPD    GPIO_SETUP(GPIO_Mode_AN,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_DOWN)
#define GPIO_MODE_AHPU    GPIO_SETUP(GPIO_Mode_AN,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_UP)
#define GPIO_MODE_AHPN    GPIO_SETUP(GPIO_Mode_AN,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_NOPULL)

#define GPIO_MODE_AHOD    GPIO_SETUP(GPIO_Mode_AN,  GPIO_Speed_High, GPIO_OType_OD, GPIO_PuPd_DOWN)
#define GPIO_MODE_AHOU    GPIO_SETUP(GPIO_Mode_AN,  GPIO_Speed_High, GPIO_OType_OD, GPIO_PuPd_UP)
#define GPIO_MODE_AHON    GPIO_SETUP(GPIO_Mode_AN,  GPIO_Speed_High, GPIO_OType_OD, GPIO_PuPd_NOPULL)

#define GPIO_MODE_FHPD    GPIO_SETUP(GPIO_Mode_AF,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_DOWN)
#define GPIO_MODE_FHPU    GPIO_SETUP(GPIO_Mode_AF,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_UP)
#define GPIO_MODE_FHPN    GPIO_SETUP(GPIO_Mode_AF,  GPIO_Speed_High, GPIO_OType_PP, GPIO_PuPd_NOPULL)

#define GPIO_MODE_FHOD    GPIO_SETUP(GPIO_Mode_AF,  GPIO_Speed_High, GPIO_OType_OD, GPIO_PuPd_DOWN)
#define GPIO_MODE_FHOU    GPIO_SETUP(GPIO_Mode_AF,  GPIO_Speed_High, GPIO_OType_OD, GPIO_PuPd_UP)
#define GPIO_MODE_FHON    GPIO_SETUP(GPIO_Mode_AF,  GPIO_Speed_High, GPIO_OType_OD, GPIO_PuPd_NOPULL)

#endif