/******************** Copyright wisearm.com ************************************
* File Name         : nRF24L01Cfg.h
* Author            : aleyn.wu
* Version           : v1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-31
* Description       : 2.4G无线驱动模式
*******************************************************************************/
#ifndef __NRF24L01CFG_H
#define __NRF24L01CFG_H

#include "stm32f4xx_spi.h"

#define nRF24_SCK_PIN   GPIO_PB3
#define nRF24_MISO_PIN  GPIO_PB4     
#define nRF24_MOSI_PIN  GPIO_PB5
#define nRF24_CS_PIN    GPIO_PA15
#define nRF24_CE_PIN    GPIO_PA8
#define nRF24_IRQ_PIN   GPIO_PA4

#define nRF24_SPI       SPI1
#define nRF24_SPI_AF    GPIO_AF_SPI1

#define nRF23_SPI_CLK   RCC_APB2PeriphClockCmd
#define nRF24_SPI_RCC   RCC_APB2Periph_SPI1

#define nRF24_DATAWIDTH 32
#define nRF24_EXTI      1
#endif
