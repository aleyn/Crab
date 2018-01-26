/******************** Copyright wisearm.com *********************************
* File Name         : CrabCommand.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 通讯命令管理器
********************************************************************************/

#ifndef __CRAB_COMMAND_MANAGE__
#define __CRAB_COMMAND_MANAGE__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define CRAB_CMD_STOP             0
#define CRAB_CMD_WORKING          1
#define CRAB_CMD_SUCCESS          2
#define CRAB_CMD_ERROR            4
  
#define CRAB_CMD_TIMEOVER         1000  
//通讯命令任务
void CrabCommandTask();


#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE