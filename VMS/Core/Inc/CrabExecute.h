/******************** Copyright wisearm.com ************************************
* File Name         : CrabExecute.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 虚拟机执行程序
********************************************************************************/

#ifndef __CRAB_EXECUTE__
#define __CRAB_EXECUTE__

#include "CrabBaseType.h"
#include "CrabStream.h"
#include "CrabPlatform.h"

#ifdef  __cplusplus
extern "C" {
#endif

//建立环境
CrabBool CrabExecute_Create(PCrabConfig Config);

//释放环境
CrabBool CrabExecute_Destroy();

//复位环境
CrabBool CrabExecute_Clear();

//载入流
CrabBool CrabExecute_LoadStream(PCrabStream CodeStream, PCrabStream StoreStream);

//重新启动应用
CrabBool CrabExecute_Restart();

//停止执行
CrabBool CrabExecute_Stop();

//获取状态
CrabBool CrabExecute_Actived();

//预处理当前指令
CrabBool CrabExecute_PrepareNextLine();

//执行当前的指令
CrabBool CrabExecute_RunCurrentLine();

//检查是否有事件，如果有则跳转
CrabBool CrabExecute_EventDispatch();

//抛出错误代码
CrabVoid CrabExecute_RaiseError(CrabInt ErrCode);

//获取错误代码
CrabUint CrabExecute_GetErrorCode();

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE