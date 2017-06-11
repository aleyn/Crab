/******************** Copyright wisearm.com ************************************
* File Name         : CrabError.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 错误信息
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>
#include "CrabBaseType.h"
#include "CrabString.h"
#include "CrabErrorMsg.h"

/********************************************************************************
* Function    : CrabErrorMessage()
* Caption     : 根据错误代码返回错误信息
*  @Param     : ErrCode - 错误代码
*  @Param     : Result - 错误信息(返回)
* Return      : CrabString
* Description : .
********************************************************************************/
CrabString  CrabErrorMessage(CrabInt ErrCode, CrabString Result)
{
  if (Result == null)
  {
    return Result;
  }
  
  switch (ErrCode)
  {
    case CrabErrorSuccess:
    {
      CrabStringAssignAnsi(Result, "执行正确");
      break;
    }
    case CrabErrorNotSupportCommand:
    {
      CrabStringAssignAnsi(Result, "不支持的指令");
      break;
    }
    case CrabErrorOutOfMemory:
    {
      CrabStringAssignAnsi(Result, "内存溢出");
      break;
    }
    case  CrabErrorOutOfCodeRom:
    {
      CrabStringAssignAnsi(Result, "超出程序代码范围");
      break;
    }
    case  CrabErrorSetupRegFaild:
    {
      CrabStringAssignAnsi(Result, "初始化寄存器失败");
      break;
    }
    case CrabErrorOutOfRegIndex:
    {
      CrabStringAssignAnsi(Result, "寄存器ID超出范围");
      break;
    }
    case CrabErrorOutOfVarMemory:
    {
      CrabStringAssignAnsi(Result, "局部变量内存超出范围");
      break;
    }
    case CrabErrorOutOfObjMemory:
    {
      CrabStringAssignAnsi(Result, "实例内存或堆超出范围");
      break;
    }
    case CrabErrorOutOfStackMemory:
    {
      CrabStringAssignAnsi(Result, "栈内存超出范围");
      break;
    }
    case CrabErrorOutOfRegStrMemory:
    {
      CrabStringAssignAnsi(Result, "寄存器字符串ID超出范围");
      break;
    }
    case CrabErrorInvaildVarType:
    {
      CrabStringAssignAnsi(Result, "无效的变量类型");
      break;
    }
    case CrabErrorInvaildVarAddr:
    {
      CrabStringAssignAnsi(Result, "无效的变量指向地址");
      break;
    }
    case CrabErrorInvaildVarHeader:
    {
      CrabStringAssignAnsi(Result, "无效的变量类型头");
      break;
    }
    case CrabErrorInvaildCodeAddr:
    {
      CrabStringAssignAnsi(Result, "无效的代码地址");
      break;
    }
    case CrabErrorInvaildObjAddr:
    {
      CrabStringAssignAnsi(Result, "无效的实例或数组地址");
      break;
    }
    case CrabErrorInvaildStringCount:
    {
      CrabStringAssignAnsi(Result, "无效的字符串长度");
      break;
    }
    case CrabErrorNotEnoughTotalMemory:
    {
      CrabStringAssignAnsi(Result, "没有足够的内存");
      break;
    }
    case CrabErrorNotEnoughVarMemory:
    {
      CrabStringAssignAnsi(Result, "没有足够的局部变量内存");
      break;
    }
    case CrabErrorNotEnoughStackMemory:
    {
      CrabStringAssignAnsi(Result, "没有足够的栈内存");
      break;
    }
    case  CrabErrorApiFuncNotFound:
    {
      CrabStringAssignAnsi(Result, "无效的API函数索引");
      break;
    }
    case  CrabErrorStackPushFaild:
    {
      CrabStringAssignAnsi(Result, "入栈失败");
      break;
    }
    case  CrabErrorStackPopFaild:
    {
      CrabStringAssignAnsi(Result, "出栈失败");
      break;
    }
    case  CrabErrorInvaildArrayDim:
    {
      CrabStringAssignAnsi(Result, "无效的数组维数类型");
      break;
    }
    case  CrabErrorInvaildObjectSize:
    {
      CrabStringAssignAnsi(Result, "无效的类实例大小");
      break;
    }
    case  CrabErrorInvaildAssignment:
    {
      CrabStringAssignAnsi(Result, "无效的赋值方式");
      break;
    }
    case  CrabErrorInvaildFormula:
    {
      CrabStringAssignAnsi(Result, "无效的计算类型");
      break;
    }
    default:
    {
      CrabStringAssignAnsi(Result, "未知的错误代码");
      break;
    }
  }

  return Result;
}
