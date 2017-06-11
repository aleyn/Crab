/******************** Copyright wisearm.com ************************************
* File Name         : eeprom.c
* Author            : aleyn.wu
* Version           : v1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-31
* Description       : EEPROM驱动模式
*******************************************************************************/
#include "eeprom.h"

uint16_t EEPROM_Address;

uint32_t EEPROM_Start(uint16_t MemoryAddr);
uint32_t EEPROM_CheckStatus(uint32_t I2C_FLAG);
uint32_t EEPROM_CheckEvent(uint32_t I2C_EVENT);

/*******************************************************************************
* Function    : EEPROM_GPIO_Config
* Caption     : EEPROM GPIO初始化
*  @Param     : 1 - 无
* Description : .
*******************************************************************************/
void EEPROM_GPIO_Config(void)
{
    RCC_APB1PeriphClockCmd(EEPROM_I2C_RCC, ENABLE);
    GPIO_InitPort(EEPROM_I2C_SCL_PIN, GPIO_MODE_I2C, EEPROM_I2C_AF);
    GPIO_InitPort(EEPROM_I2C_SDA_PIN, GPIO_MODE_I2C, EEPROM_I2C_AF);
}

/*******************************************************************************
* Function    : I2C_Config
* Caption     : I2C配置
*  @Param     : 1 - 无
* Description : .
*******************************************************************************/
void I2C_Config(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    
    //RCC_APB1PeriphClockCmd(EEPROM_I2C_RCC, ENABLE);

    I2C_SoftwareResetCmd(EEPROM_I2C, ENABLE);
    I2C_SoftwareResetCmd(EEPROM_I2C, DISABLE);
    
    /*!< I2C configuration */
    /* I2C configuration */
    I2C_InitStructure.I2C_OwnAddress1 = MASTER_Address;
    I2C_InitStructure.I2C_ClockSpeed = EEPROM_Speed;

    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    
    /* I2C Peripheral Enable */
    I2C_Cmd(EEPROM_I2C, ENABLE);
    /* Apply I2C configuration after enabling it */
    I2C_Init(EEPROM_I2C, &I2C_InitStructure);
    I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
    //I2C_Cmd(EEPROM_I2C, DISABLE);
}

/*******************************************************************************
* Function    : EEPROM_Init
* Caption     : EEPROM 硬件初始化
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void EEPROM_Init(void)
{
    EEPROM_GPIO_Config();
    I2C_Config();

    EEPROM_Address = EEPROM_DefAddress; //Default Address;
}

/*******************************************************************************
* Function    : EERPOM_CheckStatus
* Caption     : 检查I2C状态
*  @Param     : 1.I2C_FLAG - 
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t EERPOM_CheckStatus(uint32_t I2C_FLAG)
{
  uint32_t Timeout = EEPROM_CheckTime;

  while (I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG))
  {
    Timeout--;
    if (!Timeout)
    {
      break;
    }
  }
  
  return Timeout;
}

/*******************************************************************************
* Function    : EEPROM_CheckEvent
* Caption     : 检查I2C事件
*  @Param     : 1.I2C_EVENT - 
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t EEPROM_CheckEvent(uint32_t I2C_EVENT)
{
  uint32_t Timeout = EEPROM_CheckTime;
  /* Test on EVENT and clear it */
  while (!I2C_CheckEvent(EEPROM_I2C, I2C_EVENT))
  {
    Timeout--;
    if (!Timeout)
    {
      break;
    }
  }
  
  return Timeout;
}




/*******************************************************************************
* Function    : EEPROM_Start
* Caption     : 发起I2C起始时序
*  @Param     : 1.MemoryAddr - 
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t EEPROM_Start(uint16_t MemoryAddr)
{  
  uint32_t Result = EEPROM_Success;
  
  do
  {
    if (!EERPOM_CheckStatus(I2C_FLAG_BUSY))
    {
      Result = EEPROM_Timeout;
      break;
    }
    
    /* Send STRAT condition */
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);

    /* Test on EV5 and clear it */
    if (!EEPROM_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT))
    {
      Result = EEPROM_Timeout;
      break;
    }

    if (EEPROM_BlockMode)
    {
      uint8_t  Addr = EEPROM_Address | ((MemoryAddr >> 7) & 0x000E);
            
      /* Send EEPROM address for write */
      I2C_Send7bitAddress(EEPROM_I2C, Addr, I2C_Direction_Transmitter);
    }
    else
    {
      /* Send EEPROM address for write */
      I2C_Send7bitAddress(EEPROM_I2C, EEPROM_Address, I2C_Direction_Transmitter);
    }
    
    /* Test on EV6 and clear it */
    if (!EEPROM_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
      Result = EEPROM_Timeout;
      break;
    }
    
    if (EEPROM_AddrSize == 2)
    {
      /* Send the EEPROM's internal address to write to */
      I2C_SendData(EEPROM_I2C, (MemoryAddr >> 8) & 0x00FF);
      
      /* Test on EV8 and clear it */
      if (!EEPROM_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))
      {
        Result = EEPROM_Timeout;
        break;
      }
    }

    /* Send the EEPROM's internal address to write to */
    I2C_SendData(EEPROM_I2C, MemoryAddr & 0x00FF);
    
    /* Test on EV8 and clear it */
    if (!EEPROM_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
      Result = EEPROM_Timeout;
      break;
    }
  }while(0);
  
  return Result;
}

/*******************************************************************************
* Function    : EEPROM_BufferWrite
* Caption     : 将缓冲区数据写入EEPROM
*  @Param     : 1.pBuffer -  缓冲区
*  @Param     : 2.WriteAddr -  写入地址
*  @Param     : 3.NumByteToWrite - 写入数量
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t EEPROM_BufferWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
  uint32_t Result = EEPROM_Success;
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

  Addr = WriteAddr % EEPROM_PageSize;
  count = EEPROM_PageSize - Addr;
  NumOfPage =  NumByteToWrite / EEPROM_PageSize;
  NumOfSingle = NumByteToWrite % EEPROM_PageSize;
 
  /* If WriteAddr is EEPROM_PageSize aligned  */
  if(Addr == 0) 
  {
    /* If NumByteToWrite < EEPROM_PageSize */
    if(NumOfPage == 0) 
    {
      Result = EEPROM_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      if (Result == EEPROM_Success)
      {
        Result = EEPROM_WaitEepromStandbyState(WriteAddr);
      }
    }
    /* If NumByteToWrite > EEPROM_PageSize */
    else  
    {
      while ((Result == EEPROM_Success) && (NumOfPage--))
      {
        Result = EEPROM_PageWrite(pBuffer, WriteAddr, EEPROM_PageSize); 
    	  if (Result == EEPROM_Success)
        {
          Result = EEPROM_WaitEepromStandbyState(WriteAddr);
          WriteAddr +=  EEPROM_PageSize;
          pBuffer += EEPROM_PageSize;
        }
      }

      if ((Result == EEPROM_Success) && (NumOfSingle!=0))
      {
        Result = EEPROM_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        if (Result == EEPROM_Success)
        {
          Result = EEPROM_WaitEepromStandbyState(WriteAddr);
        }
      }
    }
  }
  /* If WriteAddr is not EEPROM_PageSize aligned  */
  else 
  {
    /* If NumByteToWrite < EEPROM_PageSize */
    if(NumOfPage== 0) 
    {
      Result = EEPROM_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      if (Result == EEPROM_Success)
      {
        Result = EEPROM_WaitEepromStandbyState(WriteAddr);
      }
    }
    /* If NumByteToWrite > EEPROM_PageSize */
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / EEPROM_PageSize;
      NumOfSingle = NumByteToWrite % EEPROM_PageSize;	
      
      if(count != 0)
      {  
        Result = EEPROM_PageWrite(pBuffer, WriteAddr, count);
        if (Result == EEPROM_Success)
        {
          Result = EEPROM_WaitEepromStandbyState(WriteAddr);
          WriteAddr += count;
          pBuffer += count;
        }
      } 
      
      while ((Result == EEPROM_Success) && (NumOfPage--))
      {
        Result = EEPROM_PageWrite(pBuffer, WriteAddr, EEPROM_PageSize);
        if (Result == EEPROM_Success)
        {
          Result = EEPROM_WaitEepromStandbyState(WriteAddr);
          WriteAddr +=  EEPROM_PageSize;
          pBuffer += EEPROM_PageSize;  
        }
      }
      
      if ((Result == EEPROM_Success) && (NumOfSingle != 0))
      {
        Result = EEPROM_PageWrite(pBuffer, WriteAddr, NumOfSingle); 
        if (Result == EEPROM_Success)
        {
          Result = EEPROM_WaitEepromStandbyState(WriteAddr);
        }
      }
    }
  }
  
  return Result;
}



/*******************************************************************************
* Function    : EEPROM_ByteWrite
* Caption     : 将单个字节写入EEPROM
*  @Param     : 1.Data - 数据
*  @Param     : 2.WriteAddr - 写入地址
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t EEPROM_ByteWrite(uint8_t Data, uint16_t WriteAddr)
{
  uint32_t Result = EEPROM_Success;

  do
  {    
    Result = EEPROM_Start(WriteAddr);
    
    if (Result == EEPROM_Timeout)
    {
      break;
    }

    /* Send the byte to be written */
    I2C_SendData(EEPROM_I2C, Data); 
     
    /* Test on EV8 and clear it */
    if (!EEPROM_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
      Result = EEPROM_Timeout;
      break;
    }
    
    /* Send STOP condition */
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
  } while (0);
  
  if (Result == EEPROM_Timeout)
  {
    I2C_SoftwareResetCmd(EEPROM_I2C, ENABLE);
  }
  
  return Result;
}


/*******************************************************************************
* Function    : EEPROM_PageWrite
* Caption     : 按页方式将缓冲区数据写入EEPROM
*  @Param     : 1.pBuffer - 缓冲区
*  @Param     : 2.WriteAddr -  写入地址
*  @Param     : 3.NumByteToWrite - 写入数量
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t EEPROM_PageWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t NumByteToWrite)
{
  uint32_t Result = EEPROM_Success;
  
  do
  {    
    Result = EEPROM_Start(WriteAddr);
    
    if (Result == EEPROM_Timeout)
    {
      break;
    }
    
    /* While there is data to be written */
    while(NumByteToWrite--)  
    {
      /* Send the current byte */
      I2C_SendData(EEPROM_I2C, *pBuffer); 

      /* Point to the next byte to be written */
      pBuffer++; 
    
      /* Test on EV8 and clear it */
      if (!EEPROM_CheckEvent( I2C_EVENT_MASTER_BYTE_TRANSMITTED))
      {
        Result = EEPROM_Timeout;
        break;
      }
    }
    
    /* Send STOP condition */
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
  } while(0);
  
  if (Result == EEPROM_Timeout)
  {
    I2C_SoftwareResetCmd(EEPROM_I2C, ENABLE);
  }
  
  return Result;
}


/*******************************************************************************
* Function    : EEPROM_BufferRead
* Caption     : 从EEPROM读入数据到缓冲区
*  @Param     : 1.pBuffer - 缓冲区
*  @Param     : 2.ReadAddr - 读取地址
*  @Param     : 3.NumByteToRead - 读取数量
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t EEPROM_BufferRead(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead)
{  
  uint32_t Result = EEPROM_Success;
  
  do
  {    
    Result = EEPROM_Start(ReadAddr);
    
    if (Result == EEPROM_Timeout)
    {
      break;
    }
    
    /* Send STRAT condition a second time */  
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);
    
    /* Test on EV5 and clear it */
    if (!EEPROM_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT))
    {
      Result = EEPROM_Timeout;
      break;
    }
    
    if (EEPROM_BlockMode)
    {
      uint8_t  Addr = EEPROM_Address | ((ReadAddr >> 7) & 0x000E);
            
      /* Send EEPROM address for write */
      I2C_Send7bitAddress(EEPROM_I2C, Addr, I2C_Direction_Receiver);
    }
    else
    {
      /* Send EEPROM address for write */
      I2C_Send7bitAddress(EEPROM_I2C, EEPROM_Address, I2C_Direction_Receiver);
    }
        
    /* Test on EV6 and clear it */
    if (!EEPROM_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
      Result = EEPROM_Timeout;
      break;
    }
    
    
    /* While there is data to be read */
    while(NumByteToRead)  
    {
      if(NumByteToRead == 1)
      {
        /* Disable Acknowledgement */
        I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
        
        /* Send STOP Condition */
        I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
      }

      /* Test on EV7 and clear it */
      if(EEPROM_CheckEvent(I2C_EVENT_MASTER_BYTE_RECEIVED))  
      {      
        /* Read a byte from the EEPROM */
        *pBuffer = I2C_ReceiveData(EEPROM_I2C);

        /* Point to the next location where the byte read will be saved */
        pBuffer++; 
        
        /* Decrement the read bytes counter */
        NumByteToRead--;        
      }
      else
      {
        Result = EEPROM_Timeout;
        break;
      }
    }
    
    I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
  } while (0);
  
  /* Enable Acknowledgement to be ready for another reception */
  //I2C_Cmd(EEPROM_I2C, DISABLE);
  
  if (Result == EEPROM_Timeout)
  {
    I2C_SoftwareResetCmd(EEPROM_I2C, ENABLE);
  }
  
  return Result;
}


/*******************************************************************************
* Function    : EEPROM_WaitEepromStandbyState
* Caption     : 等待EEPROM操作完成
*  @Param     : 1 - 无
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t EEPROM_WaitEepromStandbyState(uint16_t MemoryAddr)
{
  __IO uint16_t SR1_Tmp = 0;
  uint32_t Timeout = EEPROM_CheckTime;
  
  do
  {
    /* Send START condition */
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);
    /* Read I2C1 SR1 register */
    SR1_Tmp = I2C_ReadRegister(EEPROM_I2C, I2C_Register_SR1);
    
    if (EEPROM_BlockMode)
    {
      uint8_t  Addr = EEPROM_Address | ((MemoryAddr >> 7) & 0x000E);
            
      /* Send EEPROM address for write */
      I2C_Send7bitAddress(EEPROM_I2C, Addr, I2C_Direction_Transmitter);
    }
    else
    {
      /* Send EEPROM address for write */
      I2C_Send7bitAddress(EEPROM_I2C, EEPROM_Address, I2C_Direction_Transmitter);
    }
    
    Timeout--;
    if (!Timeout)
    {
      break;
    }
    
  }while(!(I2C_ReadRegister(EEPROM_I2C, I2C_Register_SR1) & 0x0002));
  
  /* Clear AF flag */
  I2C_ClearFlag(EEPROM_I2C, I2C_FLAG_AF);
  
  /* STOP condition */    
  I2C_GenerateSTOP(EEPROM_I2C, ENABLE);  

  if (Timeout == 0)
  {
    I2C_SoftwareResetCmd(EEPROM_I2C, ENABLE);
    return EEPROM_Timeout;
  }
  else
  {
    return EEPROM_Success;
  }
}


  






