/******************** Copyright wisearm.com ************************************
* File Name         : eeprom.h
* Author            : aleyn.wu
* Version           : v1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-31
* Description       : EEPROMÇý¶¯Ä£Ê½
*******************************************************************************/
#ifndef _EEPROM_H_
#define _EEPROM_H_

#ifdef __cplusplus
 extern "C" {
#endif
   
#include "stm32f4xx.h"
#include "stm32ext.h"
#include "eepromCfg.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MASTER_Address            0xC0
#define EEPROM_Speed              100000
#define EEPROM_PageSize           8
#define EEPROM_DefAddress         0xA0 /* Device Address */ 
#define EEPROM_AddrSize           2
#define EEPROM_CheckTime          100000
#define EEPROM_Timeout            0
#define EEPROM_Success            0xFFFFFFFF

void I2C_Config(void);

void EEPROM_Init(void);
uint32_t EEPROM_ByteWrite(uint8_t  Data, uint16_t WriteAddr);
uint32_t EEPROM_PageWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t NumByteToWrite);
uint32_t EEPROM_BufferWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
uint32_t EEPROM_BufferRead(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);
uint32_t EEPROM_WaitEepromStandbyState(void);

#ifdef __cplusplus
}
#endif

#endif
