/******************** Copyright wisearm.com ************************************
* File Name         : nRF24L01.c
* Author            : aleyn.wu
* Version           : v1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-31
* Description       : 2.4G无线驱动模式
*******************************************************************************/
#include <nRF24L01.h>

// SPI initialization with given prescaler
void nRF24_SPI_Init(void) 
{
	SPI_InitTypeDef SPI_InitStructure;
  
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(nRF24_SPI, &SPI_InitStructure);

	// NSS must be set to '1' due to NSS_Soft settings (otherwise it will be Multimaster mode).  
	SPI_NSSInternalSoftwareConfig(nRF24_SPI, SPI_NSSInternalSoft_Set);
  
#if defined (STM32F0)  
  // Set SPI 8Bit Width
  SPI_RxFIFOThresholdConfig(nRF24_SPI, SPI_RxFIFOThreshold_QF);
#endif  
  SPI_CalculateCRC(nRF24_SPI, DISABLE);
  
	SPI_Cmd(nRF24_SPI, ENABLE);
}

// GPIO and SPI initialization
void nRF24_Init(void) 
{
	nRF23_SPI_CLK(nRF24_SPI_RCC, ENABLE);

  GPIO_InitPort(nRF24_MOSI_PIN, GPIO_MODE_SPI, nRF24_SPI_AF);
  GPIO_InitPort(nRF24_MISO_PIN, GPIO_MODE_SPI, nRF24_SPI_AF);
  GPIO_InitPort(nRF24_SCK_PIN,  GPIO_MODE_SPI, nRF24_SPI_AF);
  
  GPIO_InitPort(nRF24_CS_PIN,   GPIO_MODE_DAT, 0);
  GPIO_InitPort(nRF24_CE_PIN,   GPIO_MODE_DAT, 0);
  GPIO_InitPort(nRF24_IRQ_PIN,  GPIO_MODE_INT, 0);

	nRF24_SPI_Init();
  
#if (nRF24_EXTI == 1)
  EXTI_InitLine(nRF24_IRQ_PIN);
#endif

	nRF24_CSN_H();
	nRF24_CE_L();
}

uint8_t nRF24_ReadWrite(uint8_t data) 
{
	while (SPI_GetStatus(nRF24_SPI, SPI_I2S_FLAG_TXE) == RESET); // Wait while DR register is not empty
  
	SPI_SendData(nRF24_SPI, data); // Send byte to SPI
  
	while (SPI_GetStatus(nRF24_SPI, SPI_I2S_FLAG_RXNE) == RESET); // Wait to receive byte
  
	return SPI_ReceiveData(nRF24_SPI); // Read byte from SPI bus
}

uint8_t nRF24_ReadReg(uint8_t reg) 
{
	uint8_t value;

	nRF24_CSN_L();
	nRF24_ReadWrite(nRF24_CMD_RREG | reg);
	value = nRF24_ReadWrite(nRF24_DUMMY_BYTE);
	nRF24_CSN_H();

	return value;
}

uint8_t nRF24_ReadBuf(uint8_t reg, uint8_t *pBuf, uint8_t count) 
{
	uint8_t status;
  //uint32_t Delay;

	nRF24_CSN_L();
	status = nRF24_ReadWrite(nRF24_CMD_RREG | reg);
  
  while (count)
  {
    //for (Delay = 0; Delay<100; Delay++);
    *pBuf++ = nRF24_ReadWrite(nRF24_DUMMY_BYTE);
    count--;
  }
  
	nRF24_CSN_H();

	return status;
}
  
uint8_t nRF24_WriteReg(uint8_t reg, uint8_t value) 
{
	uint8_t status;

	nRF24_CSN_L();
	status = nRF24_ReadWrite(nRF24_CMD_WREG | reg); // Select register
	nRF24_ReadWrite(value); // Write value to register
	nRF24_CSN_H();

	return status;
}

uint8_t nRF24_WriteBuf(uint8_t reg, uint8_t *pBuf, uint8_t count) 
{
	uint8_t status;

	nRF24_CSN_L();
	status = nRF24_ReadWrite(nRF24_CMD_WREG | reg);
  
  while (count)
  {
    nRF24_ReadWrite(*pBuf++);
    count--;
  }
  
	nRF24_CSN_H();

	return status;
}

uint8_t nRF24_Check(void) 
{
	uint8_t txbuf[nRF24_ADDR_WIDTH] = {0x5A, 0x24, 0x3C, 0x81, 0x0F};
  uint8_t rxbuf[nRF24_ADDR_WIDTH] = {0, 0, 0, 0, 0};
	uint8_t i;

	nRF24_WriteBuf(nRF24_REG_TX_ADDR, txbuf, nRF24_ADDR_WIDTH); // Write fake TX address
  nRF24_ReadBuf(nRF24_REG_TX_ADDR, rxbuf, nRF24_ADDR_WIDTH); // Try to read TX_ADDR register
  
  for (i = 0; i < nRF24_ADDR_WIDTH; i++)
  {
    if (rxbuf[i] != txbuf[i]) return 1;
  }

  return 0;
}

uint8_t nRF24_Command(uint8_t TransmitMode)
{
  uint8_t Status;
  uint8_t Cmd = nRF24_ReadReg(nRF24_REG_CONFIG);
  
  nRF24_CE_L();
  
  Cmd &= ~(nRF24_PWR_UP | nRF24_PRIM_RX);
  
  if (TransmitMode)
  {
    Cmd |= nRF24_PWR_UP | nRF24_PRIM_TX;    
  }
  else
  {
    Cmd |= nRF24_PWR_UP | nRF24_PRIM_RX;   
  }
  
  Status = nRF24_WriteReg(nRF24_REG_CONFIG, Cmd);
  nRF24_CE_H();
  return Status;
}

uint8_t nRF24_Setup(uint8_t Channel)
{
  uint8_t Status;
  
  if (Channel > 125) Channel = 125;
  nRF24_CE_L();
  
	Status = nRF24_WriteReg(nRF24_REG_CONFIG,   nRF24_CRC_ENABLE | nRF24_CRC_WORD | nRF24_PWR_UP);
	nRF24_WriteReg(nRF24_REG_RF_SETUP, 0x0F); // Setup: 2Mbps, 0dBm, LNA off
	nRF24_WriteReg(nRF24_REG_SETUP_RETR, 0x33); //Delay 1000us, Retry 3 Count; 
  nRF24_WriteReg(nRF24_REG_RF_CH, Channel); // Set frequency channel
  nRF24_WriteReg(nRF24_REG_SETUP_AW, nRF24_ADDR_WIDTH - 2); // Address Width
	nRF24_WriteReg(nRF24_REG_FEATURE,  0x04); //Enable Dynamic Payload
  
  return Status;
}

uint8_t nRF24_SetAddress(int8_t Endpipe, uint8_t *pAddr)
{
  uint8_t Status;
  uint8_t Length;
  
  if (Endpipe > 5) Endpipe = 5;
  if (Endpipe < 2) 
  {
    Length = nRF24_ADDR_WIDTH;
  }
  else
  {
    Length = 1;
  }
    
  if (Endpipe < 0)
  {
    Status = nRF24_WriteBuf(nRF24_REG_TX_ADDR, pAddr, Length); // Set static TX address
    nRF24_WriteBuf(nRF24_REG_RX_ADDR_P0, pAddr, Length); // Set static Ack TX address
  }
  else
  {
    Status = nRF24_WriteBuf(nRF24_REG_RX_ADDR_P0 + Endpipe, pAddr, Length); // Set static RX address
  }
  return Status;
}

uint8_t nRF24_SetEndpipe(int8_t Endpipe, int8_t Width)
{
  uint8_t Status;
  uint8_t PipeAddr = nRF24_ReadReg(nRF24_REG_EN_RXADDR);
  uint8_t Ack = nRF24_ReadReg(nRF24_REG_EN_AA);
  uint8_t Dynpd = nRF24_ReadReg(nRF24_REG_DYNPD);
  
  if (Endpipe > 5) Endpipe = 5;
  if (Width > 32) Width = 32;
  
  if (Width)
  {
    PipeAddr |= (0x01 << Endpipe);
    Ack      |= (0x01 << Endpipe);
    Dynpd    |= (0x01 << Endpipe);
  }
  else
  {
    PipeAddr &= ~(0x01 << Endpipe);
    Ack      &= ~(0x01 << Endpipe);
    Dynpd    &= ~(0x01 << Endpipe);
  }

  Status = nRF24_WriteReg(nRF24_REG_RX_PW_P0 + Endpipe, Width); //Set RX payload length  
  nRF24_WriteReg(nRF24_REG_EN_RXADDR, PipeAddr); // Enable data pipe
	nRF24_WriteReg(nRF24_REG_EN_AA, Ack); // Enable ShockBurst for data pipe 0
  nRF24_WriteReg(nRF24_REG_DYNPD, Dynpd);  //Enable Dynamic Payload
  return Status;
}


uint8_t nRF24_DataReady(int8_t Endpipe) 
{
	uint8_t Status;
  uint8_t FifoStatus;

  if (nRF24_IRQ_Active())    
  {
    Status = nRF24_ReadReg(nRF24_REG_STATUS); // Read status register
    FifoStatus = nRF24_ReadReg(nRF24_REG_FIFO_STATUS); // Read FIFO register
  
    if ((Status & nRF24_MASK_RX_DR) && ((Status & 0x0E) == Endpipe) && ((FifoStatus & 0x01) == 0))
    {
      Status = 1;
    }
    else
    {
      Status = 0;
    }
  }
  else
  {
    Status = 0;
  }
  
  return Status;
}

uint8_t nRF24_RXPacket(uint8_t* pBuf, uint8_t Length) 
{
	uint8_t Status;

  Status = nRF24_ReadReg(nRF24_REG_STATUS); // Read status register
  
  if (Status & nRF24_MASK_RX_DR)
  {
    nRF24_ReadBuf(nRF24_CMD_R_RX_PAYLOAD, pBuf, Length); // read received payload from RX FIFO buffer  
    Status = 1;
  }
  else
  {
    Status = 0;
  }
  
  return Status;
}


uint8_t nRF24_TXPacket(uint8_t * pBuf, uint8_t Length) 
{
  uint8_t Status;
  uint32_t Cnt;
 
  nRF24_CE_L();
  nRF24_WriteBuf(nRF24_CMD_W_TX_PAYLOAD, pBuf, Length); // Write specified buffer to FIFO
  nRF24_Command(1);
  
  for (Cnt = 0; Cnt<10000; Cnt++)
  {
    if (nRF24_IRQ_Active()) break;
  }
  
  nRF24_CE_L();   
  
  Status = nRF24_ReadReg(nRF24_REG_STATUS); // Read status register  
  return Status;
}

// Clear all IRQ flags
uint8_t nRF24_ClearIRQFlags(void) 
{
	uint8_t Status;

  Status = nRF24_ReadReg(nRF24_REG_STATUS);
	nRF24_WriteReg(nRF24_REG_STATUS, Status | 0x70); // Clear RX_DR, TX_DS, MAX_RT flags
  
  return Status;
}

uint8_t nRF24_FlashFifo(uint8_t RX, uint8_t TX)
{
  uint8_t Status;
  Status = nRF24_ReadReg(nRF24_REG_STATUS); // Read status register
  
  if (TX)
  {
    if ((Status & nRF24_MASK_MAX_RT) || (Status & nRF24_MASK_TX_DS))
    {
      // Auto retransmit counter exceeds the programmed maximum limit. FIFO is not removed.
      Status = nRF24_WriteReg(nRF24_CMD_FLUSH_TX, 0xFF); // Flush TX FIFO buffer
      nRF24_WriteReg(nRF24_REG_STATUS, Status | 0x30); // Clear TX_DS, MAX_RT
    };  
  }
  
  if (RX)
  {
    if (Status & nRF24_MASK_RX_DR)
    {
      Status = nRF24_ReadWrite(nRF24_CMD_FLUSH_RX); // Flush RX FIFO buffer
      nRF24_WriteReg(nRF24_REG_STATUS, Status | 0x40); // Clear RX_DR
    }
  }
  
  return Status;
}
