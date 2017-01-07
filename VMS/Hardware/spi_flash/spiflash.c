/**
  ******************************************************************************
  * @file    SPI/SPI_FLASH/spi_flash.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   This file provides a set of functions needed to manage the SPI M25Pxxx
  *          FLASH memory. 
  *            
  *          ===================================================================      
  *          Notes: 
  *           - There is no SPI FLASH memory available in STM324xG-EVAL board,
  *             to use this driver you have to build your own hardware.     
  *          ===================================================================
  *   
  *          It implements a high level communication layer for read and write 
  *          from/to this memory. The needed STM32 hardware resources (SPI and 
  *          GPIO) are defined in spi_flash.h file, and the initialization is 
  *          performed in sFLASH_LowLevel_Init() function.
  *            
  *          You can easily tailor this driver to any development board, by just
  *          adapting the defines for hardware resources and sFLASH_LowLevel_Init()
  *          function.
  *            
  *          +-----------------------------------------------------------+
  *          |                     Pin assignment                        |
  *          +-----------------------------+---------------+-------------+
  *          |  STM32 SPI Pins             |     sFLASH    |    Pin      |
  *          +-----------------------------+---------------+-------------+
  *          | sFLASH_CS_PIN               | ChipSelect(/S)|    1        |
  *          | sFLASH_SPI_MISO_PIN / MISO  |   DataOut(Q)  |    2        |
  *          |                             |   VCC         |    3 (3.3 V)|
  *          |                             |   GND         |    4 (0 V)  |
  *          | sFLASH_SPI_MOSI_PIN / MOSI  |   DataIn(D)   |    5        |
  *          | sFLASH_SPI_SCK_PIN / SCK    |   Clock(C)    |    6        |
  *          |                             |    VCC        |    7 (3.3 V)|
  *          |                             |    VCC        |    8 (3.3 V)|  
  *          +-----------------------------+---------------+-------------+  
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

/* Includes ------------------------------------------------------------------*/
#include "spiflash.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup SPI_FLASH
  * @{
  */  

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void sFLASH_LowLevel_DeInit(void);
void sFLASH_LowLevel_Init(void); 

/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
* Function    : sFLASH_DeInit
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void sFLASH_DeInit(void)
{
  sFLASH_LowLevel_DeInit();
}


/*******************************************************************************
* Function    : sFLASH_Init
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void sFLASH_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;

  sFLASH_LowLevel_Init();
    
  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();

  /*!< SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = sFLASH_SPI_BaudRate;

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(sFLASH_SPI, &SPI_InitStructure);

  /*!< Enable the sFLASH_SPI  */
  SPI_Cmd(sFLASH_SPI, ENABLE);
}


/*******************************************************************************
* Function    : sFLASH_EraseSector
* Caption     : .
*  @Param     : 1.SectorAddr - 
*  @Param     : 2.SectorSize - 
* Description : .
*******************************************************************************/
void sFLASH_EraseSector(uint32_t SectorAddr, uint32_t SectorSize)
{
  /*!< Send write enable instruction */
  sFLASH_WriteCmd(sFLASH_CMD_WREN);

  /*!< Sector Erase */
  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();
  /*!< Send Sector Erase instruction */
  
  switch (SectorSize)
  {
    case sFLASH_SECTOR_4K:
    {
      sFLASH_SendByte(sFLASH_CMD_SE04);
      break;
    }
    case sFLASH_SECTOR_32K:
    {
      sFLASH_SendByte(sFLASH_CMD_SE32);
      break;
    }
    case sFLASH_SECTOR_64K:
    {
      sFLASH_SendByte(sFLASH_CMD_SE64);
      break;
    }
    default:
    {
      sFLASH_SendByte(sFLASH_CMD_SE04);
      break;
    }
  }
  
  sFLASH_SendAddr(SectorAddr);
   
  sFLASH_CS_HIGH();
  sFLASH_WriteCmd(sFLASH_CMD_WRDI);

  /*!< Wait the end of Flash writing */
  sFLASH_WaitForWriteEnd();
}


/*******************************************************************************
* Function    : sFLASH_EraseBulk
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void sFLASH_EraseBulk(void)
{
  /*!< Send write enable instruction */
  sFLASH_WriteCmd(sFLASH_CMD_WREN);

  /*!< Bulk Erase */
  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();
  /*!< Send Bulk Erase instruction  */
  sFLASH_SendByte(sFLASH_CMD_BE);
  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();

  /*!< Wait the end of Flash writing */
  sFLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function    : sFLASH_ByteWrite
* Caption     : .
*  @Param     : 1.pBuffer - 
*  @Param     : 2.WriteAddr - 
*  @Param     : 3.NumByteToWrite - 
* Description : .
*******************************************************************************/
void sFLASH_ByteWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  /*!< Enable the write access to the FLASH */
  sFLASH_WriteCmd(sFLASH_CMD_WREN);
  
  while (NumByteToWrite)
  {
    /*!< Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();
    
    sFLASH_SendByte(sFLASH_CMD_WRITE); 
    sFLASH_SendAddr(WriteAddr);
    
    /*!< Send the current byte */
    sFLASH_SendByte(*pBuffer);

    /*!< Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();
    
    pBuffer++;
    NumByteToWrite--;
    WriteAddr++;

    /*!< Wait the end of Flash writing */
    sFLASH_WaitForWriteEnd();
  }
  
  sFLASH_WriteCmd(sFLASH_CMD_WRDI);

}


/*******************************************************************************
* Function    : sFLASH_PageWrite
* Caption     : .
*  @Param     : 1.pBuffer - 
*  @Param     : 2.WriteAddr - 
*  @Param     : 3.NumByteToWrite - 
* Description : .
*******************************************************************************/
void sFLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  /*!< Enable the write access to the FLASH */
  sFLASH_WriteCmd(sFLASH_CMD_WREN);
  
  /* Enable SO as RD/BY */
  //sFLASH_WriteCmd(sFLASH_CMD_EBSY);

  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();
  
  /*!< Send "Write to Memory " instruction */
  sFLASH_SendByte(sFLASH_CMD_WAAI);
  
  sFLASH_SendAddr(WriteAddr);
  
  /*!< while there is data to be written on the FLASH */
  while (NumByteToWrite)
  {
    /*!< Send the current byte */
    sFLASH_SendByte(*pBuffer);
    /*!< Point on the next byte to be written */
    pBuffer++;

    /*!< Send the current byte */
    sFLASH_SendByte(*pBuffer);
    /*!< Point on the next byte to be written */
    pBuffer++;
    
    NumByteToWrite -= 2;
    sFLASH_CS_HIGH();
    
    sFLASH_WaitForWriteEnd();
    
    if (NumByteToWrite)
    {
      sFLASH_CS_LOW();
      sFLASH_SendByte(sFLASH_CMD_WAAI);
    }
  }

  /*!< Deselect the FLASH: Chip Select high */
  
  //sFLASH_WriteCmd(sFLASH_CMD_DBSY);
  sFLASH_WriteCmd(sFLASH_CMD_WRDI);

  /*!< Wait the end of Flash writing */
  //sFLASH_WaitForWriteEnd();
}


/*******************************************************************************
* Function    : sFLASH_WriteBuffer
* Caption     : .
*  @Param     : 1.pBuffer - 
*  @Param     : 2.WriteAddr - 
*  @Param     : 3.NumByteToWrite - 
* Description : .
*******************************************************************************/
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = WriteAddr % sFLASH_SPI_PAGESIZE;
  count = sFLASH_SPI_PAGESIZE - Addr;
  NumOfPage =  NumByteToWrite / sFLASH_SPI_PAGESIZE;
  NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

  if (Addr == 0) /*!< WriteAddr is sFLASH_PAGESIZE aligned  */
  {
    if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
    {
      sFLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /*!< NumByteToWrite > sFLASH_PAGESIZE */
    {
      while (NumOfPage--)
      {
        sFLASH_PageWrite(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
        WriteAddr +=  sFLASH_SPI_PAGESIZE;
        pBuffer += sFLASH_SPI_PAGESIZE;
      }

      sFLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else /*!< WriteAddr is not sFLASH_PAGESIZE aligned  */
  {
    if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
    {
      if (NumOfSingle > count) /*!< (NumByteToWrite + WriteAddr) > sFLASH_PAGESIZE */
      {
        temp = NumOfSingle - count;

        sFLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;

        sFLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        sFLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /*!< NumByteToWrite > sFLASH_PAGESIZE */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / sFLASH_SPI_PAGESIZE;
      NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

      sFLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        sFLASH_PageWrite(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
        WriteAddr +=  sFLASH_SPI_PAGESIZE;
        pBuffer += sFLASH_SPI_PAGESIZE;
      }

      if (NumOfSingle != 0)
      {
        sFLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}


/*******************************************************************************
* Function    : sFLASH_ReadBuffer
* Caption     : .
*  @Param     : 1.pBuffer - 
*  @Param     : 2.ReadAddr - 
*  @Param     : 3.NumByteToRead - 
* Description : .
*******************************************************************************/
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();

  /*!< Send "Read from Memory " instruction */
  sFLASH_SendByte(sFLASH_CMD_READ);

  sFLASH_SendAddr(ReadAddr);

  while (NumByteToRead) /*!< while there is data to be read */
  {
    /*!< Read a byte from the FLASH */
    *pBuffer = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    /*!< Point to the next location where the byte read will be saved */
    pBuffer++;
    NumByteToRead--;
  }

  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();
}


/*******************************************************************************
* Function    : sFLASH_ReadID
* Caption     : .
*  @Param     : 1 - 
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t sFLASH_ReadID(void)
{
  uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();

  /*!< Send "RDID " instruction */
  sFLASH_SendByte(sFLASH_CMD_RDID);

  /*!< Read a byte from the FLASH */
  Temp0 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

  /*!< Read a byte from the FLASH */
  Temp1 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

  /*!< Read a byte from the FLASH */
  Temp2 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();

  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

  return Temp;
}

/*******************************************************************************
* Function    : sFLASH_ReadStatus
* Caption     : .
*  @Param     : 1 - 
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t sFLASH_ReadStatus(void)
{
  uint8_t Result;
  
  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();

  /*!< Send "RDSR " instruction */
  sFLASH_SendByte(sFLASH_CMD_RDSR);

  /*!< Read a byte from the FLASH */
  Result = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();
  
  return Result;
}

/*******************************************************************************
* Function    : sFLASH_WriteStatus
* Caption     : .
*  @Param     : 1.Status - 
* Description : .
*******************************************************************************/
void sFLASH_WriteStatus(uint8_t Status)
{ 
  sFLASH_WriteCmd(sFLASH_CMD_EWSR);

  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();

  sFLASH_SendByte(sFLASH_CMD_WRSR);
  sFLASH_SendByte(Status);

  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();  
}


/*******************************************************************************
* Function    : sFLASH_StartReadSequence
* Caption     : .
*  @Param     : 1.ReadAddr - 
* Description : .
*******************************************************************************/
void sFLASH_StartReadSequence(uint32_t ReadAddr)
{
  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();

  /*!< Send "Read from Memory " instruction */
  sFLASH_SendByte(sFLASH_CMD_READ);
  /*!< Send the 24-bit address of the address to read from -------------------*/
  sFLASH_SendAddr(ReadAddr);
}


/*******************************************************************************
* Function    : sFLASH_ReadByte
* Caption     : .
*  @Param     : 1 - 
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t sFLASH_ReadByte(void)
{
  return (sFLASH_SendByte(sFLASH_DUMMY_BYTE));
}

/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *         from the SPI bus.
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint8_t sFLASH_SendByte(uint8_t byte)
{
  /*!< Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /*!< Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(sFLASH_SPI, byte);

  /*!< Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /*!< Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(sFLASH_SPI);
}


/*******************************************************************************
* Function    : sFLASH_SendHalfWord
* Caption     : .
*  @Param     : 1.HalfWord - 
* Return      : uint16_t
* Description : .
*******************************************************************************/
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord)
{
  /*!< Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /*!< Send Half Word through the sFLASH peripheral */
  SPI_I2S_SendData(sFLASH_SPI, HalfWord);

  /*!< Wait to receive a Half Word */
  while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /*!< Return the Half Word read from the SPI bus */
  return SPI_I2S_ReceiveData(sFLASH_SPI);
}


/*******************************************************************************
* Function    : sFLASH_SendAddr
* Caption     : .
*  @Param     : 1.Addr - 
* Description : .
*******************************************************************************/
void sFLASH_SendAddr(uint32_t Addr)
{
  /*!< Send the 24-bit address of the address to next action -------------------*/
  /*!< Send Addr high nibble address byte */
  sFLASH_SendByte((Addr & 0xFF0000) >> 16);
  /*!< Send Addr medium nibble address byte */
  sFLASH_SendByte((Addr& 0xFF00) >> 8);
  /*!< Send Addr low nibble address byte */
  sFLASH_SendByte(Addr & 0xFF);
}


/*******************************************************************************
* Function    : sFLASH_WriteCmd
* Caption     : .
*  @Param     : 1.Cmd - 
* Description : .
*******************************************************************************/
void sFLASH_WriteCmd(uint8_t Cmd)
{
  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();

  /*!< Send Command instruction */
  sFLASH_SendByte(Cmd);

  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();
}


/*******************************************************************************
* Function    : sFLASH_WaitForWriteEnd
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void sFLASH_WaitForWriteEnd(void)
{
  uint8_t flashstatus = 0;

  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();

  /*!< Send "Read Status Register" instruction */
  sFLASH_SendByte(sFLASH_CMD_RDSR);

  /*!< Loop as long as the memory is busy with a write cycle */
  do
  {
    /*!< Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    flashstatus = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

  }
  while ((flashstatus & sFLASH_WIP_FLAG) == SET); /* Write in progress */

  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();
}

/*******************************************************************************
* Function    : sFLASH_LowLevel_Init
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void sFLASH_LowLevel_Init(void)
{
  /*!< Enable the SPI clock */
  sFLASH_SPI_CLK_INIT(sFLASH_SPI_CLK, ENABLE);
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

  GPIO_InitPort(sFLASH_SPI_SCK_PIN, GPIO_MODE_SPI, sFLASH_SPI_AF);
  GPIO_InitPort(sFLASH_SPI_MISO_PIN, GPIO_MODE_SPI, sFLASH_SPI_AF);
  GPIO_InitPort(sFLASH_SPI_MOSI_PIN, GPIO_MODE_SPI, sFLASH_SPI_AF);
  GPIO_InitPort(sFLASH_SPI_CS_PIN, GPIO_MODE_PUT, 0);
}


/*******************************************************************************
* Function    : sFLASH_LowLevel_DeInit
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void sFLASH_LowLevel_DeInit(void)
{
  /*!< Disable the sFLASH_SPI  ************************************************/
  SPI_Cmd(sFLASH_SPI, DISABLE);
  
  /*!< DeInitializes the sFLASH_SPI *******************************************/
  SPI_I2S_DeInit(sFLASH_SPI);
  
  /*!< sFLASH_SPI Periph clock disable ****************************************/
  sFLASH_SPI_CLK_INIT(sFLASH_SPI_CLK, DISABLE);
      
  GPIO_InitPort(sFLASH_SPI_SCK_PIN, GPIO_MODE_GET, 0);
  GPIO_InitPort(sFLASH_SPI_MISO_PIN, GPIO_MODE_GET, 0);
  GPIO_InitPort(sFLASH_SPI_MOSI_PIN, GPIO_MODE_GET, 0);
  GPIO_InitPort(sFLASH_SPI_CS_PIN, GPIO_MODE_PUT, 0);
}

/*****END OF FILE****/
