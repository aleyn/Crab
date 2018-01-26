/******************** Copyright wisearm.com ************************************
* File Name         : I2C_Master.h
* Author            : aleyn.wu
* Version           : v1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2017-09-20
* Description       : I2C 主设备驱动程序
*******************************************************************************/
#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

#ifdef __cplusplus
 extern "C" {
#endif
   
#include "stm32f4xx.h"
#include "stm32ext.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#pragma pack(1)
typedef struct 
{
  I2C_TypeDef*   I2C;
  void           (*GpioInit)(void);
  void           (*GpioDeInit)(void);
  uint8_t        BlockMode;
  uint8_t        PageSize;
  uint8_t        AddrSize;

  uint32_t       Speed;
  uint8_t        MasterAddr;
  uint8_t        DeviceAddr;
  uint32_t       CheckTime;
} I2C_Master_Def;
#pragma pack()

#define I2CM_MASTER_Address    0xC0
#define I2CM_Speed             100000
#define I2CM_PageSize          8
#define I2CM_DeviceAddr        0xA0
#define I2CM_BlockMode         0
#define I2CM_AddrSize          2
#define I2CM_CheckTime         100000
#define I2CM_Timeout           0
#define I2CM_Success           0xFFFFFFFF
#define I2CM_Read              I2C_Direction_Receiver
#define I2CM_Write             I2C_Direction_Transmitter

#define I2CM_TimeoutReset      0

void     I2CM_DefaultSet(I2C_Master_Def * I2Cx);
void     I2CM_Config(I2C_Master_Def * I2Cx);
void     I2CM_Start(I2C_Master_Def * I2Cx);
void     I2CM_Stop(I2C_Master_Def * I2Cx);
void     I2CM_Reset(I2C_Master_Def * I2Cx);
uint32_t I2CM_BusStart(I2C_Master_Def * I2Cx, uint16_t MemoryAddr);
uint32_t I2CM_CheckStatus(I2C_Master_Def * I2Cx, uint32_t I2C_FLAG);
uint32_t I2CM_WaitForEvent(I2C_Master_Def * I2Cx, uint32_t I2C_EVENT);
uint32_t I2CM_ByteWrite(I2C_Master_Def * I2Cx, uint8_t  Data, uint16_t WriteAddr);
uint32_t I2CM_PageWrite(I2C_Master_Def * I2Cx, uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
uint32_t I2CM_DirectRead(I2C_Master_Def * I2Cx, uint8_t* pBuffer, uint16_t NumByteToRead);
uint32_t I2CM_BufferRead(I2C_Master_Def * I2Cx, uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);
uint32_t I2CM_WaitEepromStandbyState(I2C_Master_Def * I2Cx, uint16_t MemoryAddr);

#ifdef __cplusplus
}
#endif

#endif
