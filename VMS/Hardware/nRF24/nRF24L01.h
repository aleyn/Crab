/******************** Copyright wisearm.com ************************************
* File Name         : nRF24L01.c
* Author            : aleyn.wu
* Version           : v1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-31
* Description       : 2.4G无线驱动模式
*******************************************************************************/
#ifndef __NRF24L01_H
#define __NRF24L01_H

#include "stm32ext.h"
#include "nRF24L01Cfg.h"

// Chip Enable Activates RX or TX mode
#define nRF24_CE_L() GPIO_SetBit(nRF24_CE_PIN, 0)
#define nRF24_CE_H() GPIO_SetBit(nRF24_CE_PIN, 1)

// SPI Chip Select
#define nRF24_CSN_L() GPIO_SetBit(nRF24_CS_PIN, 0)
#define nRF24_CSN_H() GPIO_SetBit(nRF24_CS_PIN, 1)

// IQR
#define nRF24_IRQ_Active()  (GPIO_GetInputBit(nRF24_IRQ_PIN) == 0)

#define nRF24_DUMMY_BYTE           0xA5

/* nRF24L0 commands */
#define nRF24_CMD_RREG             0x00  // R_REGISTER -> Read command and status registers
#define nRF24_CMD_WREG             0x20  // W_REGISTER -> Write command and status registers
#define nRF24_CMD_R_RX_PAYLOAD     0x61  // R_RX_PAYLOAD -> Read RX payload
#define nRF24_CMD_W_TX_PAYLOAD     0xA0  // W_TX_PAYLOAD -> Write TX payload
#define nRF24_CMD_FLUSH_TX         0xE1  // FLUSH_TX -> Flush TX FIFO
#define nRF24_CMD_FLUSH_RX         0xE2  // FLUSH_RX -> Flush RX FIFO
#define nRF24_CMD_REUSE_TX_PL      0xE3  // REUSE_TX_PL -> Reuse last transmitted payload
#define nRF24_CMD_R_RX_PL_WID      0x60  // Read RX Payload with for the top
#define nRF24_CMD_W_ACK_PAYLOAD    0xA8  // Write Payload to transmitted with ACK packet
#define nRF24_CMD_W_PAYLOAD_NOACK  0xB0  // Write Payload to transmitted with NOACK packet
#define nRF24_CMD_NOP              0xFF  // No operation (to read status register)

/* nRF24L0 registers */
#define nRF24_REG_CONFIG           0x00  // Configuration register
#define nRF24_REG_EN_AA            0x01  // Enable "Auto acknowledgment"
#define nRF24_REG_EN_RXADDR        0x02  // Enable RX addresses
#define nRF24_REG_SETUP_AW         0x03  // Setup of address widths
#define nRF24_REG_SETUP_RETR       0x04  // Setup of automatic retranslation
#define nRF24_REG_RF_CH            0x05  // RF channel
#define nRF24_REG_RF_SETUP         0x06  // RF setup register
#define nRF24_REG_STATUS           0x07  // Status register
#define nRF24_REG_OBSERVE_TX       0x08  // Transmit observe register
#define nRF24_REG_RPD              0x09  // Carrier detect
#define nRF24_REG_RX_ADDR_P0       0x0A  // Receive address data pipe 0
#define nRF24_REG_RX_ADDR_P1       0x0B  // Receive address data pipe 1
#define nRF24_REG_RX_ADDR_P2       0x0C  // Receive address data pipe 2
#define nRF24_REG_RX_ADDR_P3       0x0D  // Receive address data pipe 3
#define nRF24_REG_RX_ADDR_P4       0x0E  // Receive address data pipe 4
#define nRF24_REG_RX_ADDR_P5       0x0F  // Receive address data pipe 5
#define nRF24_REG_TX_ADDR          0x10  // Transmit address
#define nRF24_REG_RX_PW_P0         0x11  // Number of bytes in RX payload id data pipe 0
#define nRF24_REG_RX_PW_P1         0x12  // Number of bytes in RX payload id data pipe 1
#define nRF24_REG_RX_PW_P2         0x13  // Number of bytes in RX payload id data pipe 2
#define nRF24_REG_RX_PW_P3         0x14  // Number of bytes in RX payload id data pipe 3
#define nRF24_REG_RX_PW_P4         0x15  // Number of bytes in RX payload id data pipe 4
#define nRF24_REG_RX_PW_P5         0x16  // Number of bytes in RX payload id data pipe 5
#define nRF24_REG_FIFO_STATUS      0x17  // FIFO status register
#define nRF24_REG_DYNPD            0x1C  // Enable dynamic payload length
#define nRF24_REG_FEATURE          0x1D  // Feature register 

//#define nRF24_REG_CONFIG           0x00  // Configuration register
    //reserved: bit7, only '0' allowed
    #define nRF24_MASK_RX_DR       0x40  //6 //RW, Mask interrupt caused by RX_DR
    #define nRF24_MASK_TX_DS       0x20  //5 //RW, Mask interrupt caused by TX_DS
    #define nRF24_MASK_MAX_RT      0x10  //4 //RW, Mask interrupt caused by MAX_RT
    #define nRF24_CRC_ENABLE       0x08  //3 //RW, Enable CRC.
    #define nRF24_CRC_WORD         0x04  //2 //RW, CRC encoding scheme, 0: 1 byte, 1: 2 bytes
    #define nRF24_PWR_UP           0x02  //1 //RW, Power up, 1: power up, 0: power down
    #define nRF24_PRIM_RX          0x01  //0 //RW, RX/TX control, 1: PRX, 0: PTX
    #define nRF24_PRIM_TX          0x00  //0 //RW, RX/TX control, 1: PRX, 0: PTX

//#define nRF24_REG_RF_SETUP         0x06  // RF setup register
    #define nRF24_CONT_WAVE        0x80  //7 //RW, Enables continuous carrier transmit when high
    //reserved bit6, only '0' allowed
    #define nRF24_RF_DR_LOW        0x20  //5 //RW, Set RF Data Rate to 250kbps
    #define nRF24_PLL_LOCK         0x10  //4 //RW, Force PLL lock signal, Only used in test
    #define nRF24_RF_DR_HIGH       0x08  //3 //RW, Low-High:00,1Mbps,01,2Mbps,10,250kbps,11,reserved
    //bit2-bit1:
    #define nRF24_PWR_18DB         0x00  //(0x00<<1)
    #define nRF24_PWR_12DB         0x02  //(0x01<<1)
    #define nRF24_PWR_6DB          0x04  //(0x02<<1)
    #define nRF24_PWR_0DB          0x06  //(0x03<<1)
    //reserved, bit0, Do not care

//#define nRF24_REG_STATUS           0x07  // Status register
    //reserved, bit7, only '0' allowed
    #define nRF24_RX_DR            0x40  //6 //RW, Data ready RX FIFO interrupt
    #define nRF24_TX_DS            0x20  //5 //RW, Data sent TX FIFO interrupt
    #define nRF24_MAX_RT           0x10  //4 //RW, Maximum number of TX retransmits interrupt
    //for bit3-bit1, R, Data pipe number for the payload available for reading from
    //RX_FIFO, 000-101, Data pipe number, 110, not used, 111, RX FIFO empty
    #define nRF24_TX_FULL_0        0x01  //0 //R, TX FIFO full flag

//#define nRF24_REG_RPD              0x09  // Carrier detect
    //bit7-bit1, reserved
    #define nRF24_RPD              0x01  //0 //Received power detector

//#define nRF24_REG_FIFO_STATUS      0x17  // FIFO status register
    //bit7, reserved, only '0' allowed
    #define nRF24_TX_REUSE         0x40  //6 //R,
    #define nRF24_TX_FULL_1        0x20  //5 //R, TX FIFO full flag
    #define nRF24_TX_EMPTY         0x10  //4 //R, TX FIFO empty flag
    //bit3-bit2, reserved, only '00'
    #define nRF24_RX_FULL          0x02  //1 //R, RX FIFO full flag
    #define nRF24_RX_EMPTY         0x01  //0 //R, RX FIFO empty flag

#define nRF24_REG_FEATURE          0x1D  // Feature register 
    //reserved, bit7-bit3, only '0000' allowed
    #define nRF24_EN_DPL           0x04  //2 //RW, Enables Dynamic payloard length
    #define nRF24_EN_ACK_PAY       0x02  //1 //RW, Enable Payload with ACK
    #define nRF24_EN_DYN_ACK       0x01  //0 //RW, Enables the W_TX_PAYLOAD_NOACK command

/* Some constants */
#define nRF24_ADDR_WIDTH           5    // nRF24 RX address width
#define nRF24_ENDP_TX              -1
#define nRF24_ENDP_P0              0
#define nRF24_ENDP_P1              1
#define nRF24_ENDP_P2              2
#define nRF24_ENDP_P3              3
#define nRF24_ENDP_P4              4
#define nRF24_ENDP_P5              5

/* Function prototypes */
void nRF24_SPI_Init(void);
void nRF24_Init(void);

uint8_t nRF24_ReadWrite(uint8_t data);
uint8_t nRF24_ReadReg(uint8_t reg);
uint8_t nRF24_ReadBuf(uint8_t reg, uint8_t *pBuf, uint8_t count);
uint8_t nRF24_WriteReg(uint8_t reg, uint8_t value);
uint8_t nRF24_WriteBuf(uint8_t reg, uint8_t *pBuf, uint8_t count);

uint8_t nRF24_Check(void);
uint8_t nRF24_Command(uint8_t TransmitMode);
uint8_t nRF24_Setup(uint8_t Channel);
uint8_t nRF24_SetAddress(int8_t Endpipe, uint8_t *pAddr);
uint8_t nRF24_SetEndpipe(int8_t Endpipe, int8_t Width);
uint8_t nRF24_DataReady(int8_t Endpipe);
uint8_t nRF24_TXPacket(uint8_t *pBuf, uint8_t Length);
uint8_t nRF24_RXPacket(uint8_t *pBuf, uint8_t Length);
uint8_t nRF24_ClearIRQFlags(void);
uint8_t nRF24_FlashFifo(uint8_t RX, uint8_t TX);

#endif
