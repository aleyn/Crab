/******************** Copyright wisearm.com *********************************
* File Name         : usbd_conf.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2015-02-18
* Last Update       : 2016-12-16
* Description       : USB
*******************************************************************************/
#ifndef __USBD_CONF__H__
#define __USBD_CONF__H__

#include "stm32ext.h"

#define USBD_CFG_MAX_NUM           1
#define USBD_ITF_MAX_NUM           1

#define USB_MAX_STR_DESC_SIZ       64 
#define USBD_EP0_MAX_PACKET_SIZE   64

//USB中断优先级
#define USB_IRQ_PRIORITY           6

#endif //__USBD_CONF__H__


