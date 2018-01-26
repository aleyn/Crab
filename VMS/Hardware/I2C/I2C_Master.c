/******************** Copyright wisearm.com ************************************
* File Name         : I2C_Master.c
* Author            : aleyn.wu
* Version           : v1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2017-09-20
* Description       : I2C 主设备驱动程序
*******************************************************************************/
#include "I2C_Master.h"

void I2CM_DefaultSet(I2C_Master_Def * I2Cx)
{
  I2Cx->I2C = I2C1;
  I2Cx->GpioInit = 0;
  I2Cx->BlockMode = I2CM_BlockMode;
  I2Cx->PageSize = I2CM_PageSize;
  I2Cx->AddrSize = I2CM_AddrSize;

  I2Cx->Speed = I2CM_Speed;
  I2Cx->MasterAddr = I2CM_MASTER_Address;
  I2Cx->DeviceAddr = I2CM_DeviceAddr;
  I2Cx->CheckTime = I2CM_CheckTime;
}

/*******************************************************************************
* Function    : I2C_Config
* Caption     : I2C配置
*  @Param     : 1 - 无
* Description : .
*******************************************************************************/
void I2CM_Config(I2C_Master_Def * I2Cx)
{    
  //RCC_APB1PeriphClockCmd(I2Cx->I2C_RCC, ENABLE);
  I2C_InitTypeDef  I2C_InitStructure;
  
  I2C_DeInit(I2Cx->I2C);

  if (I2Cx->GpioInit != 0)
  {
    I2Cx->GpioInit();
  }
  
  I2C_SoftwareResetCmd(I2Cx->I2C, ENABLE);
  I2C_SoftwareResetCmd(I2Cx->I2C, DISABLE);  
  
  /* I2C configuration */
  I2C_InitStructure.I2C_OwnAddress1 = I2Cx->MasterAddr;
  I2C_InitStructure.I2C_ClockSpeed = I2Cx->Speed;
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  
  /* I2C Peripheral Enable */
  I2C_Cmd(I2Cx->I2C, ENABLE);

  /* Apply I2C configuration after enabling it */
  I2C_Init(I2Cx->I2C, &I2C_InitStructure);
  I2C_AcknowledgeConfig(I2Cx->I2C, ENABLE);
  
  I2C_Cmd(I2Cx->I2C, DISABLE);
}

/*******************************************************************************
* Function    : I2CM_Start
* Caption     : I2C复拉
*  @Param     : 1 - 无
* Description : .
*******************************************************************************/
void     I2CM_Start(I2C_Master_Def * I2Cx)
{
  I2C_Cmd(I2Cx->I2C, ENABLE);
  I2C_AcknowledgeConfig(I2Cx->I2C, ENABLE);
}

/*******************************************************************************
* Function    : I2CM_Stop
* Caption     : I2C复拉
*  @Param     : 1 - 无
* Description : .
*******************************************************************************/
void     I2CM_Stop(I2C_Master_Def * I2Cx)
{
  //I2C_SoftwareResetCmd(I2Cx->I2C, ENABLE);
  //I2C_SoftwareResetCmd(I2Cx->I2C, DISABLE);
  I2C_Cmd(I2Cx->I2C, DISABLE);
}


/*******************************************************************************
* Function    : I2CM_Reset
* Caption     : I2C复拉
*  @Param     : 1 - 无
* Description : .
*******************************************************************************/
void     I2CM_Reset(I2C_Master_Def * I2Cx)
{
  uint32_t I;
  
  I2C_SoftwareResetCmd(I2Cx->I2C, ENABLE);
  I2C_SoftwareResetCmd(I2Cx->I2C, DISABLE);  
  
  I2C_InitTypeDef  I2C_InitStructure;
  
  I2C_DeInit(I2Cx->I2C);
  
  if (I2Cx->GpioDeInit != 0)
  {
    I2Cx->GpioDeInit();
  }  
  
  for (I = 0; I < 1000000; I++)
  {
    //Status = 1;
  }
  
  if (I2Cx->GpioInit != 0)
  {
    I2Cx->GpioInit();
  }  
  
  I2C_InitStructure.I2C_OwnAddress1 = I2Cx->MasterAddr;
  I2C_InitStructure.I2C_ClockSpeed = I2Cx->Speed;
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  
  I2C_Cmd(I2Cx->I2C, ENABLE);

  I2C_Init(I2Cx->I2C, &I2C_InitStructure);
  I2C_AcknowledgeConfig(I2Cx->I2C, ENABLE);
  
}

/*******************************************************************************
* Function    : I2CM_CheckStatus
* Caption     : 检查I2C状态
*  @Param     : 1.I2C_FLAG - 
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t I2CM_CheckStatus(I2C_Master_Def * I2Cx, uint32_t I2C_FLAG)
{
  uint32_t Timeout = I2Cx->CheckTime;

  while (I2C_GetFlagStatus(I2Cx->I2C, I2C_FLAG))
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
* Function    : I2CM_WaitForEvent
* Caption     : 检查I2C事件
*  @Param     : 1.I2C_EVENT - 
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t I2CM_WaitForEvent(I2C_Master_Def * I2Cx, uint32_t I2C_EVENT)
{
  uint32_t Timeout = I2Cx->CheckTime;

  /* Test on EVENT and clear it */
  while (!I2C_CheckEvent(I2Cx->I2C, I2C_EVENT))
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
* Function    : I2CM_BusStart
* Caption     : 发起I2C起始时序
*  @Param     : 1.MemoryAddr - 
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t I2CM_BusStart(I2C_Master_Def * I2Cx, uint16_t MemoryAddr)
{  
  uint32_t Result = I2CM_Success;
  
  do
  {
    if (!I2CM_CheckStatus(I2Cx, I2C_FLAG_BUSY))
    {
      Result = I2CM_Timeout;
      break;
    }
    
    /* Send STRAT condition */
    I2C_GenerateSTART(I2Cx->I2C, ENABLE);

    /* Test on EV5 and clear it */
    if (!I2CM_WaitForEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
    {
      Result = I2CM_Timeout;
      break;
    }

    if (I2Cx->BlockMode)
    {
      uint8_t  Addr = (I2Cx->DeviceAddr) | ((MemoryAddr >> 7) & 0x000E);
            
      /* Send EEPROM address for write */
      I2C_Send7bitAddress(I2Cx->I2C, Addr, I2C_Direction_Transmitter);  //
    }
    else
    {
      /* Send EEPROM address for write */
      I2C_Send7bitAddress(I2Cx->I2C, I2Cx->DeviceAddr, I2C_Direction_Transmitter);  //
    }
    
    /* Test on EV6 and clear it */
    if (!I2CM_WaitForEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
      Result = I2CM_Timeout;
      break;
    }
    
    if (I2Cx->AddrSize == 2)
    {
      /* Send the EEPROM's internal address to write to */
      I2C_SendData(I2Cx->I2C, (MemoryAddr >> 8) & 0x00FF);
      
      /* Test on EV8 and clear it */
      if (!I2CM_WaitForEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
      {
        Result = I2CM_Timeout;
        break;
      }
    }

    /* Send the EEPROM's internal address to write to */
    I2C_SendData(I2Cx->I2C, MemoryAddr & 0x00FF);
    
    /* Test on EV8 and clear it */
    if (!I2CM_WaitForEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
      Result = I2CM_Timeout;
      break;
    }
  }while(0);
  
  return Result;
}

/*******************************************************************************
* Function    : I2CM_ByteWrite
* Caption     : 将单个字节写入EEPROM
*  @Param     : 1.Data - 数据
*  @Param     : 2.WriteAddr - 写入地址
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t I2CM_ByteWrite(I2C_Master_Def * I2Cx, uint8_t Data, uint16_t WriteAddr)
{
  uint32_t Result = I2CM_Success;

  do
  {    
    Result = I2CM_BusStart(I2Cx, WriteAddr);
    
    if (Result == I2CM_Timeout)
    {
      break;
    }

    /* Send the byte to be written */
    I2C_SendData(I2Cx->I2C, Data); 
     
    /* Test on EV8 and clear it */
    if (!I2CM_WaitForEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
      Result = I2CM_Timeout;
      break;
    }
    
    /* Send STOP condition */
    I2C_GenerateSTOP(I2Cx->I2C, ENABLE);
  } while (0);
  
  if (Result == I2CM_Timeout)
  {
#if (I2CM_TimeoutReset == 1)
    I2CM_Reset(I2Cx);
#endif
  }
  
  return Result;
}


/*******************************************************************************
* Function    : I2CM_PageWrite
* Caption     : 按页方式将缓冲区数据写入EEPROM
*  @Param     : 1.pBuffer - 缓冲区
*  @Param     : 2.WriteAddr -  写入地址
*  @Param     : 3.NumByteToWrite - 写入数量
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t I2CM_PageWrite(I2C_Master_Def * I2Cx, uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
  uint32_t Result = I2CM_Success;
  uint8_t  AutoEnd = (NumByteToWrite == 0);
  
  do
  {    
    Result = I2CM_BusStart(I2Cx, WriteAddr);
    
    if (Result == I2CM_Timeout)
    {
      break;
    }
    
    /* While there is data to be written */
    while (AutoEnd || NumByteToWrite)
    {      
      /* Send the current byte */
      I2C_SendData(I2Cx->I2C, *pBuffer); 

      /* Point to the next byte to be written */
      pBuffer++;
          
      /* Test on EV8 and clear it */
      if (!I2CM_WaitForEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
      {
        Result = I2CM_Timeout;
        break;
      }
      
      if (AutoEnd)
      {
        if (*pBuffer == 0) break;
      }
      else
      {
        NumByteToWrite--;
      }
    }
    
    /* Send STOP condition */
    I2C_GenerateSTOP(I2Cx->I2C, ENABLE);
  } while(0);
  
  if (Result == I2CM_Timeout)
  {
#if (I2CM_TimeoutReset == 1)
    I2CM_Reset(I2Cx);
#endif
  }
  
  return Result;
}

/*******************************************************************************
* Function    : I2CM_DirectRead
* Caption     : 从EEPROM读入数据到缓冲区，无地址模式
*  @Param     : 1.pBuffer - 缓冲区
*  @Param     : 2.NumByteToRead - 读取数量
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t I2CM_DirectRead(I2C_Master_Def * I2Cx, uint8_t* pBuffer, uint16_t NumByteToRead)
{  
  uint32_t Result = I2CM_Success;
  
  do
  {        
    /* Send STRAT condition a second time */  
    I2C_GenerateSTART(I2Cx->I2C, ENABLE);
    
    /* Test on EV5 and clear it */
    if (!I2CM_WaitForEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
    {
      Result = I2CM_Timeout;
      break;
    }
    
    /* Send EEPROM address for write */
    I2C_Send7bitAddress(I2Cx->I2C, I2Cx->DeviceAddr, I2C_Direction_Receiver);
        
    /* Test on EV6 and clear it */
    if (!I2CM_WaitForEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
      Result = I2CM_Timeout;
      break;
    }    
    
    /* While there is data to be read */
    while(NumByteToRead)  
    {
      if(NumByteToRead == 1)
      {
        /* Disable Acknowledgement */
        I2C_AcknowledgeConfig(I2Cx->I2C, DISABLE);
        
        /* Send STOP Condition */
        I2C_GenerateSTOP(I2Cx->I2C, ENABLE);
      }

      /* Test on EV7 and clear it */
      if(I2CM_WaitForEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))  
      {      
        /* Read a byte from the EEPROM */
        *pBuffer = I2C_ReceiveData(I2Cx->I2C);

        /* Point to the next location where the byte read will be saved */
        pBuffer++; 
        
        /* Decrement the read bytes counter */
        NumByteToRead--;        
      }
      else
      {
        Result = I2CM_Timeout;
        break;
      }
    }
    
    I2C_AcknowledgeConfig(I2Cx->I2C, ENABLE);
  } while (0);
  
  /* Enable Acknowledgement to be ready for another reception */
  //I2C_Cmd(I2Cx->I2C, DISABLE);
  
  if (Result == I2CM_Timeout)
  {
#if (I2CM_TimeoutReset == 1)
    I2CM_Reset(I2Cx);
#endif
  }
  
  return Result;
}

/*******************************************************************************
* Function    : I2CM_BufferRead
* Caption     : 从EEPROM读入数据到缓冲区
*  @Param     : 1.pBuffer - 缓冲区
*  @Param     : 2.ReadAddr - 读取地址
*  @Param     : 3.NumByteToRead - 读取数量
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t I2CM_BufferRead(I2C_Master_Def * I2Cx, uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead)
{  
  uint32_t Result = I2CM_Success;
  
  do
  {    
    Result = I2CM_BusStart(I2Cx, ReadAddr);
    
    if (Result == I2CM_Timeout)
    {
      break;
    }
    
    /* Send STRAT condition a second time */  
    I2C_GenerateSTART(I2Cx->I2C, ENABLE);
    
    /* Test on EV5 and clear it */
    if (!I2CM_WaitForEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
    {
      Result = I2CM_Timeout;
      break;
    }
    
    if (I2Cx->BlockMode)
    {
      uint8_t  Addr = (I2Cx->DeviceAddr) | ((ReadAddr >> 7) & 0x000E);
            
      /* Send EEPROM address for write */
      I2C_Send7bitAddress(I2Cx->I2C, Addr, I2C_Direction_Receiver);
    }
    else
    {
      /* Send EEPROM address for write */
      I2C_Send7bitAddress(I2Cx->I2C, I2Cx->DeviceAddr, I2C_Direction_Receiver);
    }
        
    /* Test on EV6 and clear it */
    if (!I2CM_WaitForEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
      Result = I2CM_Timeout;
      break;
    }
    
    
    /* While there is data to be read */
    while(NumByteToRead)  
    {
      if(NumByteToRead == 1)
      {
        /* Disable Acknowledgement */
        I2C_AcknowledgeConfig(I2Cx->I2C, DISABLE);
        
        /* Send STOP Condition */
        I2C_GenerateSTOP(I2Cx->I2C, ENABLE);
      }

      /* Test on EV7 and clear it */
      if(I2CM_WaitForEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))  
      {      
        /* Read a byte from the EEPROM */
        *pBuffer = I2C_ReceiveData(I2Cx->I2C);

        /* Point to the next location where the byte read will be saved */
        pBuffer++; 
        
        /* Decrement the read bytes counter */
        NumByteToRead--;        
      }
      else
      {
        Result = I2CM_Timeout;
        break;
      }
    }
    
    I2C_AcknowledgeConfig(I2Cx->I2C, ENABLE);
  } while (0);
  
  /* Enable Acknowledgement to be ready for another reception */
  //I2C_Cmd(I2Cx->I2C, DISABLE);
  
  if (Result == I2CM_Timeout)
  {
#if (I2CM_TimeoutReset == 1)
    I2CM_Reset(I2Cx);
#endif
  }
  
  return Result;
}


/*******************************************************************************
* Function    : I2CM_WaitEepromStandbyState
* Caption     : 等待EEPROM操作完成
*  @Param     : 1 - 无
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t I2CM_WaitEepromStandbyState(I2C_Master_Def * I2Cx, uint16_t MemoryAddr)
{
  __IO uint16_t SR1_Tmp = 0;
  uint32_t Timeout = I2Cx->CheckTime;
  
  do
  {
    /* Send START condition */
    I2C_GenerateSTART(I2Cx->I2C, ENABLE);
    /* Read I2C1 SR1 register */
    SR1_Tmp = I2C_ReadRegister(I2Cx->I2C, I2C_Register_SR1);
    
    if (I2Cx->BlockMode)
    {
      uint8_t  Addr = (I2Cx->DeviceAddr) | ((MemoryAddr >> 7) & 0x000E);
            
      /* Send EEPROM address for write */
      I2C_Send7bitAddress(I2Cx->I2C, Addr, I2C_Direction_Transmitter);
    }
    else
    {
      /* Send EEPROM address for write */
      I2C_Send7bitAddress(I2Cx->I2C, I2Cx->DeviceAddr, I2C_Direction_Transmitter);
    }
    
    Timeout--;
    if (!Timeout)
    {
      break;
    }
    
  }while(!(I2C_ReadRegister(I2Cx->I2C, I2C_Register_SR1) & 0x0002));
  
  /* Clear AF flag */
  I2C_ClearFlag(I2Cx->I2C, I2C_FLAG_AF);
  
  /* STOP condition */    
  I2C_GenerateSTOP(I2Cx->I2C, ENABLE);  

  if (Timeout == 0)
  {
#if (I2CM_TimeoutReset == 1)
    I2CM_Reset(I2Cx);
#endif
    return I2CM_Timeout;
  }
  else
  {
    return I2CM_Success;
  }
}


  






