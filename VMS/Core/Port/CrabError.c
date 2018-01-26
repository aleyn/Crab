/******************** Copyright wisearm.com ************************************
* File Name         : CrabError.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ������Ϣ
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
* Caption     : ���ݴ�����뷵�ش�����Ϣ
*  @Param     : ErrCode - �������
*  @Param     : Result - ������Ϣ(����)
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
      CrabStringAssignAnsi(Result, ""); // "ִ����ȷ"
      break;
    }
    case CrabErrorNotSupportCommand:
    {
      CrabStringAssignAnsi(Result, "Not support command."); //"��֧�ֵ�ָ��");
      break;
    }
    case CrabErrorOutOfMemory:
    {
      CrabStringAssignAnsi(Result, "Out of memory."); //"�ڴ����");
      break;
    }
    case  CrabErrorOutOfCodeRom:
    {
      CrabStringAssignAnsi(Result, "Out of code ROM."); //"����������뷶Χ");
      break;
    }
    case  CrabErrorSetupRegFaild:
    {
      CrabStringAssignAnsi(Result, "Setup REG faild."); //"��ʼ���Ĵ���ʧ��");
      break;
    }
    case CrabErrorOutOfRegIndex:
    {
      CrabStringAssignAnsi(Result, "Out of REG index."); //"�Ĵ���ID������Χ");
      break;
    }
    case CrabErrorOutOfVarMemory:
    {
      CrabStringAssignAnsi(Result, "Out of var memory."); //"�ֲ������ڴ泬����Χ");
      break;
    }
    case CrabErrorOutOfObjMemory:
    {
      CrabStringAssignAnsi(Result, "Out of object memory."); //"ʵ���ڴ��ѳ�����Χ");
      break;
    }
    case CrabErrorOutOfStackMemory:
    {
      CrabStringAssignAnsi(Result, "Out of stack memory."); //"ջ�ڴ泬����Χ");
      break;
    }
    case CrabErrorOutOfRegStrMemory:
    {
      CrabStringAssignAnsi(Result, "Out of REG string Memory."); //"�Ĵ����ַ���ID������Χ");
      break;
    }
    case CrabErrorInvaildVarType:
    {
      CrabStringAssignAnsi(Result, "Invaild var type."); //"��Ч�ı�������");
      break;
    }
    case CrabErrorInvaildVarAddr:
    {
      CrabStringAssignAnsi(Result, "Invaild var addr."); //"��Ч�ı���ָ���ַ");
      break;
    }
    case CrabErrorInvaildVarHeader:
    {
      CrabStringAssignAnsi(Result, "Invaild var header."); //"��Ч�ı�������ͷ");
      break;
    }
    case CrabErrorInvaildCodeAddr:
    {
      CrabStringAssignAnsi(Result, "INvaild code addr."); //"��Ч�Ĵ����ַ");
      break;
    }
    case CrabErrorInvaildObjAddr:
    {
      CrabStringAssignAnsi(Result, "Invaild object addr."); //"��Ч��ʵ���������ַ");
      break;
    }
    case CrabErrorInvaildStringCount:
    {
      CrabStringAssignAnsi(Result, "Invaild string length."); //"��Ч���ַ�������");
      break;
    }
    case CrabErrorNotEnoughTotalMemory:
    {
      CrabStringAssignAnsi(Result, "Not enough total memory."); //"û���㹻���ڴ�");
      break;
    }
    case CrabErrorNotEnoughVarMemory:
    {
      CrabStringAssignAnsi(Result, "Not enough var memory."); //"û���㹻�ľֲ������ڴ�");
      break;
    }
    case CrabErrorNotEnoughStackMemory:
    {
      CrabStringAssignAnsi(Result, "Not enough stack memory."); //"û���㹻��ջ�ڴ�");
      break;
    }
    case CrabErrorNotEnoughPFString:
    {
      CrabStringAssignAnsi(Result, "Not enough Full-string pool buffer."); //û���㹻��ȫ���ַ���������
      break;
    }
    case  CrabErrorApiFuncNotFound:
    {
      CrabStringAssignAnsi(Result, "API function not found."); //"��Ч��API��������");
      break;
    }
    case  CrabErrorStackPushFaild:
    {
      CrabStringAssignAnsi(Result, "Stack push faild."); //"��ջʧ��");
      break;
    }
    case  CrabErrorStackPopFaild:
    {
      CrabStringAssignAnsi(Result, "Stack pop faild."); //"��ջʧ��");
      break;
    }
    case  CrabErrorInvaildArrayDim:
    {
      CrabStringAssignAnsi(Result, "Invaild array dimension."); //"��Ч������ά������");
      break;
    }
    case  CrabErrorInvaildObjectSize:
    {
      CrabStringAssignAnsi(Result, "Invaild object size."); //"��Ч����ʵ����С");
      break;
    }
    case  CrabErrorInvaildAssignment:
    {
      CrabStringAssignAnsi(Result, "Invaild assignment."); //"��Ч�ĸ�ֵ��ʽ");
      break;
    }
    case  CrabErrorInvaildFormula:
    {
      CrabStringAssignAnsi(Result, "Invaild formula."); //"��Ч�ļ�������");
      break;
    }
    default:
    {
      CrabStringAssignAnsi(Result, "Unknown error code."); //"δ֪�Ĵ������");
      break;
    }
  }

  return Result;
}
