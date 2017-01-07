/**
  ******************************************************************************
  * @file    spi_flash.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   This file contains all the functions prototypes for the spi_flash
  *          firmware driver.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32ext.h"
#include "spiflashcfg.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* M25P SPI Flash supported commands */  
#define sFLASH_CMD_READ           0x03  /* Read from Memory instruction */
#define sFLASH_CMD_RAAI           0x0B  /* High Speed Read from Memory instruction */
#define sFLASH_CMD_WRITE          0x02  /* Write to Memory instruction */
#define sFLASH_CMD_WAAI           0xAD  /* Write to Memory AAI Mode */
#define sFLASH_CMD_WREN           0x06  /* Write enable instruction */
#define sFLASH_CMD_WRDI           0x04  /* Write Disable instruction */
#define sFLASH_CMD_RDSR           0x05  /* Read Status Register instruction  */
#define sFLASH_CMD_WRSR           0x01  /* Write Status Register instruction */
#define sFLASH_CMD_EWSR           0x50  /* Enable Write Status Register instruction */
#define sFLASH_CMD_RDID           0x9F  /* Read identification */
#define sFLASH_CMD_SE04           0x20  /* Sector Erase instruction  4K Memory*/
#define sFLASH_CMD_SE32           0x52  /* Sector Erase instruction 32K Memory*/
#define sFLASH_CMD_SE64           0xD8  /* Sector Erase instruction 64K Memory*/
#define sFLASH_CMD_BE             0xC7  /* Bulk Erase instruction */
#define sFLASH_CMD_EBSY           0x70  /* Enable SO as RD/BY instruction */
#define sFLASH_CMD_DBSY           0x80  /* Disable SO as RD/BY instruction */

#define sFLASH_WIP_FLAG           0x01  /* Write In Progress (WIP) flag */

#define sFLASH_DUMMY_BYTE         0xA5
#define sFLASH_SPI_PAGESIZE       0x100
   
#define sFLASH_SECTOR_4K          0x1000   /* Sector  4K Memory*/
#define sFLASH_SECTOR_32K         0x8000   /* Sector 32K Memory*/
#define sFLASH_SECTOR_64K         0x10000  /* Sector 64K Memory*/

#define sFLASH_M25P128_ID         0x202018
#define sFLASH_M25P64_ID          0x202017
#define sFLASH_M25P32_ID          0x202016   
#define sFLASH_M25P16_ID          0x202015
  
/* Exported macro ------------------------------------------------------------*/
/* Select sFLASH: Chip Select pin low */
#define sFLASH_CS_LOW()       GPIO_SetBit(sFLASH_SPI_CS_PIN, 0)
/* Deselect sFLASH: Chip Select pin high */
#define sFLASH_CS_HIGH()      GPIO_SetBit(sFLASH_SPI_CS_PIN, 1)   

#define sFLASH_SO_STAT()      GPIO_GetInputBit(sFLASH_SPI_MISO_PIN)

/* Exported functions ------------------------------------------------------- */

/* High layer functions  */
void sFLASH_DeInit(void);
void sFLASH_Init(void);
void sFLASH_LowLevel_Init(void);
void sFLASH_EraseSector(uint32_t SectorAddr, uint32_t SectorSize);
void sFLASH_EraseBulk(void);
void sFLASH_ByteWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t sFLASH_ReadID(void);
uint8_t sFLASH_ReadStatus(void);
void sFLASH_WriteStatus(uint8_t Status);
void sFLASH_StartReadSequence(uint32_t ReadAddr);

/* Low layer functions */
uint8_t sFLASH_ReadByte(void);
uint8_t sFLASH_SendByte(uint8_t byte);
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord);
void sFLASH_SendAddr(uint32_t Addr);
void sFLASH_WriteCmd(uint8_t Cmd);
void sFLASH_WaitForWriteEnd(void);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_FLASH_H */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
