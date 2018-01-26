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
      CrabStringAssignAnsi(Result, ""); // "执行正确"
      break;
    }
    case CrabErrorNotSupportCommand:
    {
      CrabStringAssignAnsi(Result, "Not support command."); //"不支持的指令");
      break;
    }
    case CrabErrorOutOfMemory:
    {
      CrabStringAssignAnsi(Result, "Out of memory."); //"内存溢出");
      break;
    }
    case  CrabErrorOutOfCodeRom:
    {
      CrabStringAssignAnsi(Result, "Out of code ROM."); //"超出程序代码范围");
      break;
    }
    case  CrabErrorSetupRegFaild:
    {
      CrabStringAssignAnsi(Result, "Setup REG faild."); //"初始化寄存器失败");
      break;
    }
    case CrabErrorOutOfRegIndex:
    {
      CrabStringAssignAnsi(Result, "Out of REG index."); //"寄存器ID超出范围");
      break;
    }
    case CrabErrorOutOfVarMemory:
    {
      CrabStringAssignAnsi(Result, "Out of var memory."); //"局部变量内存超出范围");
      break;
    }
    case CrabErrorOutOfObjMemory:
    {
      CrabStringAssignAnsi(Result, "Out of object memory."); //"实例内存或堆超出范围");
      break;
    }
    case CrabErrorOutOfStackMemory:
    {
      CrabStringAssignAnsi(Result, "Out of stack memory."); //"栈内存超出范围");
      break;
    }
    case CrabErrorOutOfRegStrMemory:
    {
      CrabStringAssignAnsi(Result, "Out of REG string Memory."); //"寄存器字符串ID超出范围");
      break;
    }
    case CrabErrorInvaildVarType:
    {
      CrabStringAssignAnsi(Result, "Invaild var type."); //"无效的变量类型");
      break;
    }
    case CrabErrorInvaildVarAddr:
    {
      CrabStringAssignAnsi(Result, "Invaild var addr."); //"无效的变量指向地址");
      break;
    }
    case CrabErrorInvaildVarHeader:
    {
      CrabStringAssignAnsi(Result, "Invaild var header."); //"无效的变量类型头");
      break;
    }
    case CrabErrorInvaildCodeAddr:
    {
      CrabStringAssignAnsi(Result, "INvaild code addr."); //"无效的代码地址");
      break;
    }
    case CrabErrorInvaildObjAddr:
    {
      CrabStringAssignAnsi(Result, "Invaild object addr."); //"无效的实例或数组地址");
      break;
    }
    case CrabErrorInvaildStringCount:
    {
      CrabStringAssignAnsi(Result, "Invaild string length."); //"无效的字符串长度");
      break;
    }
    case CrabErrorNotEnoughTotalMemory:
    {
      CrabStringAssignAnsi(Result, "Not enough total memory."); //"没有足够的内存");
      break;
    }
    case CrabErrorNotEnoughVarMemory:
    {
      CrabStringAssignAnsi(Result, "Not enough var memory."); //"没有足够的局部变量内存");
      break;
    }
    case CrabErrorNotEnoughStackMemory:
    {
      CrabStringAssignAnsi(Result, "Not enough stack memory."); //"没有足够的栈内存");
      break;
    }
    case CrabErrorNotEnoughPFString:
    {
      CrabStringAssignAnsi(Result, "Not enough Full-string pool buffer."); //没有足够的全长字符串缓冲区
      break;
    }
    case  CrabErrorApiFuncNotFound:
    {
      CrabStringAssignAnsi(Result, "API function not found."); //"无效的API函数索引");
      break;
    }
    case  CrabErrorStackPushFaild:
    {
      CrabStringAssignAnsi(Result, "Stack push faild."); //"入栈失败");
      break;
    }
    case  CrabErrorStackPopFaild:
    {
      CrabStringAssignAnsi(Result, "Stack pop faild."); //"出栈失败");
      break;
    }
    case  CrabErrorInvaildArrayDim:
    {
      CrabStringAssignAnsi(Result, "Invaild array dimension."); //"无效的数组维数类型");
      break;
    }
    case  CrabErrorInvaildObjectSize:
    {
      CrabStringAssignAnsi(Result, "Invaild object size."); //"无效的类实例大小");
      break;
    }
    case  CrabErrorInvaildAssignment:
    {
      CrabStringAssignAnsi(Result, "Invaild assignment."); //"无效的赋值方式");
      break;
    }
    case  CrabErrorInvaildFormula:
    {
      CrabStringAssignAnsi(Result, "Invaild formula."); //"无效的计算类型");
      break;
    }
    default:
    {
      CrabStringAssignAnsi(Result, "Unknown error code."); //"未知的错误代码");
      break;
    }
  }

  return Result;
}
