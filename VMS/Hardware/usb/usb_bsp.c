/******************** Copyright wisearm.com ************************************
* File Name         : usb_bsp.c
* Author            : Îâ´´Ã÷(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-16
* Description       : USB
*******************************************************************************/
#include "usb_bsp.h"

/*******************************************************************************
* Function    : USB_OTG_BSP_Init
* Caption     : .
*  @Param     : 1.pdev - 
* Description : .
*******************************************************************************/
void USB_OTG_BSP_Init(USB_OTG_CORE_HANDLE *pdev)
{
}

/*******************************************************************************
* Function    : USB_OTG_BSP_EnableInterrupt
* Caption     : .
*  @Param     : 1.pdev - 
* Description : .
*******************************************************************************/
void USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE *pdev)
{

}

/*******************************************************************************
* Function    : USB_OTG_BSP_DriveVBUS
* Caption     : .
*  @Param     : 1.speed - 
*  @Param     : 2.state - 
* Description : .
*******************************************************************************/
void USB_OTG_BSP_DriveVBUS(uint32_t speed, uint8_t state)
{

}

/*******************************************************************************
* Function    : USB_OTG_BSP_ConfigVBUS
* Caption     : .
*  @Param     : 1.speed - 
* Description : .
*******************************************************************************/
void  USB_OTG_BSP_ConfigVBUS(uint32_t speed)
{

}

/*******************************************************************************
* Function    : USB_OTG_BSP_TimeInit
* Caption     : .
* Description : .
*******************************************************************************/
void USB_OTG_BSP_TimeInit ( void )
{

}

/*******************************************************************************
* Function    : USB_OTG_BSP_uDelay
* Caption     : .
*  @Param In  : 1.usec - 
* Description : .
*******************************************************************************/
void USB_OTG_BSP_uDelay (const uint32_t usec)
{

  uint32_t count = 0;
  const uint32_t utime = (120 * usec / 7);
  do
  {
    if ( ++count > utime )
    {
      return ;
    }
  }
  while (1);

}

/*******************************************************************************
* Function    : USB_OTG_BSP_mDelay
* Caption     : .
*  @Param In  : 1.msec - 
* Description : .
*******************************************************************************/
void USB_OTG_BSP_mDelay (const uint32_t msec)
{

    USB_OTG_BSP_uDelay(msec * 1000);

}

/*******************************************************************************
* Function    : USB_OTG_BSP_TimerIRQ
* Caption     : .
* Description : .
*******************************************************************************/
void USB_OTG_BSP_TimerIRQ (void)
{

} 

