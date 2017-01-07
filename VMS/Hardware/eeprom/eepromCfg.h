/******************** Copyright wisearm.com ************************************
* File Name         : eepromCfg.h
* Author            : aleyn.wu
* Version           : v1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-31
* Description       : EEPROMÇý¶¯Ä£Ê½ÅäÖÃ
*******************************************************************************/
#ifndef _EEPROM_CFG_H_
#define _EEPROM_CFG_H_

#ifdef __cplusplus
 extern "C" {
#endif
   
#define EEPROM_I2C            I2C1
#define EEPROM_I2C_RCC        RCC_APB1Periph_I2C1
#define EEPROM_I2C_AF         GPIO_AF_I2C1

#define EEPROM_I2C_SCL_PIN    GPIO_PB6
#define EEPROM_I2C_SDA_PIN    GPIO_PB7

#ifdef __cplusplus
}
#endif

#endif
