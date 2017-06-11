/******************** Copyright wisearm.com *********************************
* File Name         : CrabVMS.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 配置文件
********************************************************************************/

#ifndef __CRAB_VMS_MANAGE__
#define __CRAB_VMS_MANAGE__

#include "CrabHardware.h"
#include "CrabConfig.h"
#include "CrabBaseType.h"
#include "CrabErrorMsg.h"
#include "CrabString.h"
#include "CrabStream.h"
#include "CrabStoreStream.h"
#include "CrabStorage.h"
#include "CrabExecute.h"
#include "CrabExtern.h"
#include "CrabDefaultApi.h"
#include "CrabDatetime.h"
#include "CrabFifo.h"
#include "CrabPlatform.h"
#include "CrabTask.h"
#include "CrabApplication.h"
#include "CrabCommand.h"
#include "CrabSystem.h"
#include "CrabEvent.h"
#include "CrabUserApp.h"
#include "CrabUserDebug.h"
#include "CrabUtility.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define CrabVMS_log(MSG, ...)  Log(MSG, ##__VA_ARGS__)

//版本信息
#define CRAB_DEVICE_ID            101
#define CRAB_VENDER_ID            2282902
#define CRAB_HW_VER               0x0101   

#ifdef CRABBOARD
int application_start( void );
#endif

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE