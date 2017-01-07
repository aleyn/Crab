/******************** Copyright wisearm.com *********************************
* File Name         : usbd_hw_init.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-16
* Description       : USB
*******************************************************************************/

#include "usbd_conf.h"
#include "usbd_gap.h"
#include "portmacro.h"

extern USBD_Class_cb_TypeDef  USBD_GAP_cb;
extern USB_OTG_CORE_HANDLE    USB_OTG_dev;


/*******************************************************************************
* Function    : USB_HW_DeInit
* Caption     : .
* Description : .
*******************************************************************************/
void USB_HW_DeInit()
{
  //初始化USB
  GPIO_InitPort(USB_DM, GPIO_MODE_IND, 0);
  GPIO_InitPort(USB_DP, GPIO_MODE_IND, 0);

  //USB上拉控制
  GPIO_InitPort(USB_PULL,  GPIO_MODE_PUT, 0);

  GPIO_SetBit(USB_DM, 0);
  GPIO_SetBit(USB_DP, 0);
  GPIO_SetBit(USB_PULL, 0);
}

/*******************************************************************************
* Function    : USB_HW_Init
* Caption     : .
* Description : .
*******************************************************************************/
void USB_HW_Init()
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  
  //USB 设置
  NVIC_InitStructure.NVIC_IRQChannel = OTG_FS_IRQn;  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = USB_IRQ_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
  
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS, ENABLE) ; 
  
  GPIO_InitPort(USB_DM, GPIO_MODE_USB, GPIO_AF_OTG1_FS);
  GPIO_InitPort(USB_DP, GPIO_MODE_USB, GPIO_AF_OTG1_FS);
}

/*******************************************************************************
* Function    : USBD_Enable
* Caption     : .
* Description : .
*******************************************************************************/
void USB_Enable()
{
  GPIO_SetBit(USB_PULL, 1);
  DCD_DevConnect(&USB_OTG_dev);
}

/*******************************************************************************
* Function    : OTG_FS_IRQHandler
* Caption     : .
* Description : .
*******************************************************************************/
__irq __root void OTG_FS_IRQHandler(void)
{
  //raw_enter_interrupt();
  //vPortEnterCritical();
  USBD_OTG_ISR_Handler (&USB_OTG_dev);   
  //raw_finish_int();
  //vPortExitCritical();
}

/*****END OF FILE****/
