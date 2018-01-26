/******************** (C)Copyright wisearm.com *********************************
* File Name         : Hardware.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2016-02-18
* Last Update       : 2016-12-16
* Description       : 硬件配置与设置
********************************************************************************/
#include "Hardware.h"

__IO uint16_t ADCValue[8];
#define ADC_CDR_ADDRESS    ((uint32_t)0x40012308)
#define ADC1_DR_Address    ((uint32_t)0x4001204C)

__IO uint32_t AsynchPrediv = 0, SynchPrediv = 0;

uint8_t nRF24_TX_addr[nRF24_ADDR_WIDTH] = {'A','l','e','y','n'};
uint8_t nRF24_RX_addr[nRF24_ADDR_WIDTH] = {'A','l','e','y','n'};
uint8_t nRF24_Channel = 40;

const uint32_t GPIO_ADDR[GPIO_ADDR_MAX] = 
{
  GPIO_PA0, GPIO_PA1, GPIO_PA3, GPIO_PA5,
  GPIO_PA6, GPIO_PA7, GPIO_PB0, GPIO_PB1,
  GPIO_PB8, GPIO_PB9
};

/*******************************************************************************
* Description : 内部调用配置过程
*******************************************************************************/
void GPIO_Config(void);
void NVIC_Config(void);
void ADC_Config(void);
void USART_Config();
void RTC_Config(void);
void nRF24_Config(void);
/*******************************************************************************
* Function    : Hardware_Init
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void Hardware_Init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  RTC_Config();
  SystemCoreClockUpdate();
    
  NVIC_Config();
  GPIO_Config();
  USART_Config();  
  USB_HW_DeInit();
}

/*******************************************************************************
* Function    : Device_Init
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void Device_Init(void)
{
  ADC_Config();
  EEPROM_Init();
  sFLASH_Init(); 
  PulseWave_Init();
  
#if (nRF24_ACTIVE == 1)
  nRF24_Config();
#endif
  USB_InitDevice();    
}

/*******************************************************************************
* Function    : GPIO_Config
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void GPIO_Config(void)
{   
  /* Enable the GPIO Clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);	 
  
  GPIO_InitPort(SYS_LED, GPIO_MODE_GET, 0);
  GPIO_InitPort(SYS_ESC, GPIO_MODE_KEY, 0);
  
  //GPIO_InitPort(GPIO_PB9, GPIO_MODE_INT, 0);
  //EXTI_InitLine(GPIO_PB9);
}

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function    : NVIC_Config
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  // 4位抢占优先级, 0位响应优先级
  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
  
  NVIC_InitStructure.NVIC_IRQChannel= SECOND_IRQn;                //更新中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd= ENABLE;
  NVIC_Init( &NVIC_InitStructure );
  
  
  /*NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);*/
  
  /*
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);  */  
}

/*******************************************************************************
* Function    : ADC_Config
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void ADC_Config(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef DMA_InitStructure;

  GPIO_InitPort(ADC_1, GPIO_MODE_ADC, 0);
  GPIO_InitPort(ADC_2, GPIO_MODE_ADC, 0); 
  
  /* Enable peripheral clocks */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  
  
  /* DMA2 Stream0 channel0 configuration */
  DMA_InitStructure.DMA_Channel = DMA_Channel_0; 
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADCValue;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 8;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);

  /* DMA2_Stream0 enable */
  DMA_Cmd(DMA2_Stream0, ENABLE); 
  
  /* ADC Common Init */
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);
  
  /* ADC1 regular channel configuration ************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 2;
  ADC_Init(ADC1, &ADC_InitStructure);
  
  /* ADC1 regular channel configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_CH1, 1, ADC_SimpleTime); 
  ADC_RegularChannelConfig(ADC1, ADC_CH2, 2, ADC_SimpleTime);

  /* ADC2 regular channel 12 configuration ************************************/
  //ADC_Init(ADC2, &ADC_InitStructure);
  
  /* ADC2 regular channel12 configuration */
  //ADC_RegularChannelConfig(ADC2, ADC_Channel_9,  1, ADC_SimpleTime);

  /* Enable DMA request after last transfer (multi-ADC mode) ******************/
  //ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);

 /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);  
  
  /* Enable ADC1 **************************************************************/
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC2 **************************************************************/
  //ADC_Cmd(ADC2, ENABLE);
 
  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConv(ADC1);
}

/*******************************************************************************
* Function    : USART_Config
* Caption     : .
* Description : .
*******************************************************************************/
void USART_Config()
{
  //GPIO_InitExTypeDef   GPIO_InitStructure;
  USART_InitTypeDef  USART_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);


  /* Configure USART1 Tx as alternate function  */
  GPIO_InitPort(GPIO_PA9, GPIO_MODE_USART, GPIO_AF_USART1);

  /* Configure USART1 Rx as alternate function  */
  GPIO_InitPort(GPIO_PA10, GPIO_MODE_USART, GPIO_AF_USART1);

  /* Configure USART2 Tx as alternate function  */
  //GPIO_InitPort(GPIO_PA2, GPIO_MODE_USART, GPIO_AF_USART2);
  
  /* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = DEVICE_COM_BR;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
  
  /* USART configuration */
  //USART_Init(USER_COM, &USART_InitStructure);
  //USART_Init(PROTOCOL_COM, &USART_InitStructure);
  USART_Init(PRINTF_COM, &USART_InitStructure);

  /* Enable USART */
  //USART_Cmd(USER_COM, ENABLE);
  //USART_Cmd(PROTOCOL_COM, ENABLE);
  USART_Cmd(PRINTF_COM, ENABLE);
}

/*******************************************************************************
* Function    : RTC_Config
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void RTC_Config(void)
{
  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);

  /* Enable the LSE OSC */
  RCC_LSEConfig(RCC_LSE_ON);

  /* Wait till LSE is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  SynchPrediv = 0xFF;
  AsynchPrediv = 0x7F;
  
  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();

  /* Enable The TimeStamp */
  //RTC_TimeStampCmd(RTC_TimeStampEdge_Falling, ENABLE);    
}

/*******************************************************************************
* Function    : nRF24_Config
* Caption     : .
*  @Param     : 1 - 
* Description : .
*******************************************************************************/
void nRF24_Config(void)
{
  uint8_t   Count = 10;
  uint32_t  Tick = 1000;
  
  //printf("Congif nRF24 receive channel[%d]...", nRF24_Channel);
  nRF24_Init();
  
  while (Count)
  {
    Tick --;
    
    if (Tick == 0)
    {
      if (nRF24_Check())
      {
        Count--;
        Tick = 1;
      }
      else
      {
        break;
      }
    }
  }
  
  if (Count)
  {
    nRF24_Setup(nRF24_Channel);
    nRF24_SetAddress(nRF24_ENDP_P1, nRF24_RX_addr);
    nRF24_SetEndpipe(nRF24_ENDP_P1, nRF24_DATAWIDTH);
    nRF24_FlashFifo(1, 1);
    nRF24_Command(0);
    //printf("success.\n");
  }
  else
  {
    nRF24_Channel = 0;
    //printf("faild.\n");
  }
}



