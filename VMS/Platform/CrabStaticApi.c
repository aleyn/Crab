/******************** Copyright wisearm.com *********************************
* File Name         : CrabStaticApi.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 静态API函数
********************************************************************************/
#include "CrabVMS.h"
#include "FreeRTOS.h"
#include "task.h"

/*******************************************************************************
* Function    : CrabRegisterStaticApi
* Caption     : 注册静态API函数 
* Description : .
*******************************************************************************/
void CrabRegisterStaticApi()
{  
  CrabStaticApi.EventIntr = CrabEventIntr;
  CrabStaticApi.Input = CrabInput;
  CrabStaticApi.Print = CrabPrint;
  CrabStaticApi.Delay = CrabDelay;
}

/*******************************************************************************
* Function    : CrabEventIntr
* Caption     : 虚拟机事件总开关
*  @Param     : 1.State - 开关状态
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabEventIntr (CrabBool State)
{
  /*if (State)
  {
    CrabTaskResume(CRAB_TASK_EVENT);
  }
  else
  {
    CrabTaskSuspend(CRAB_TASK_EVENT);
  }*/
}

/*******************************************************************************
* Function    : CrabInput
* Caption     : 标准输入
*  @Param     : 1.Type - 输入类型
*  @Param     : 2.Buffer - 输入缓冲区
*  @Param     : 3.Length - 缓冲区长度
* Return      : crabapi
* Description : 标准输入可以是键盘，串口，手柄，等等
*******************************************************************************/
crabapi CrabInput (CrabUint Type, CrabAnsi Buffer, PCrabUint Length)
{
}

/*******************************************************************************
* Function    : CrabPrint
* Caption     : 标准输出
*  @Param     : 1.Text - 文本字符串
*  @Param     : 2.Length - 字符串长度
* Return      : crabapi
* Description : 标准输出的目标，可以是串口，USB，屏幕，打印机，等等
*******************************************************************************/
crabapi CrabPrint (CrabAnsi Text, CrabUint Length)
{
  CrabChar *Buf;
  
  if (Length == 0)
  {
    Length = strlen(Text);
  }
  
  if (!Log_Check(&Buf, Length)) return;
  CrabMemCopy(Buf, Text, Length);
  Log_Add(0, Length);
}

/*******************************************************************************
* Function    : CrabDelay
* Caption     : 延时函数
*  @Param     : 1.MS - 毫秒
* Description : 桥接和利用RTOS的延时
*******************************************************************************/
crabapi CrabDelay (CrabUint MSec)
{
   vTaskDelay(MSec);
}
