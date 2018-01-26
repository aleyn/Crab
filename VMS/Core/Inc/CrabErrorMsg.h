/******************** Copyright wisearm.com ************************************
* File Name         : CrabErrorMsg.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ������Ϣ��
********************************************************************************/
#ifndef __CRAB_ERRORMSG__
#define __CRAB_ERRORMSG__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

//�������
#define  CrabErrorSuccess                0  //���쳣
#define  CrabErrorRaiseLast             -99 //�׳����һ���쳣
#define  CrabErrorNotSupportCommand     -1  //��֧�ֵ�ָ��
#define  CrabErrorOutOfMemory           -2  //�ڴ����
#define  CrabErrorOutOfCodeRom          -3  //����������뷶Χ
#define  CrabErrorSetupRegFaild         -4  //��ʼ���Ĵ���ʧ��
#define  CrabErrorOutOfRegIndex         -11 //�Ĵ���ID������Χ
#define  CrabErrorOutOfVarMemory        -12 //�ֲ������ڴ泬����Χ
#define  CrabErrorOutOfObjMemory        -13 //ʵ���ڴ��ѳ�����Χ
#define  CrabErrorOutOfStackMemory      -14 //ջ�ڴ泬����Χ
#define  CrabErrorOutOfRegStrMemory     -15 //�Ĵ����ַ���ID������Χ
#define  CrabErrorInvaildVarType        -21 //��Ч�ı�������
#define  CrabErrorInvaildVarAddr        -22 //��Ч�ı���ָ���ַ
#define  CrabErrorInvaildVarHeader      -23 //��Ч�ı�������ͷ
#define  CrabErrorInvaildCodeAddr       -24 //��Ч�Ĵ����ַ
#define  CrabErrorInvaildObjAddr        -25 //��Ч��ʵ���������ַ
#define  CrabErrorInvaildStringCount    -26 //��Ч���ַ�������
#define  CrabErrorInvaildAddrType       -27 //��Ч�ĵ�ַ����
#define  CrabErrorNotEnoughTotalMemory  -31 //û���㹻���ڴ�
#define  CrabErrorNotEnoughVarMemory    -32 //û���㹻�ľֲ������ڴ�
#define  CrabErrorNotEnoughStackMemory  -33 //û���㹻��ջ�ڴ�
#define  CrabErrorNotEnoughPFString     -34 //û���㹻��ȫ���ַ���������
#define  CrabErrorApiFuncNotFound       -41 //��Ч��API��������
#define  CrabErrorStackPushFaild        -51 //��ջʧ��
#define  CrabErrorStackPopFaild         -52 //��ջʧ��
#define  CrabErrorInvaildArrayDim       -61 //��Ч������ά������
#define  CrabErrorInvaildObjectSize     -62 //��Ч����ʵ����С
#define  CrabErrorInvaildAssignment     -63 //��Ч�ĸ�ֵ��ʽ
#define  CrabErrorInvaildFormula        -64 //��Ч�ļ�������

//������Ϣ
CrabString  CrabErrorMessage(CrabInt ErrCode, CrabString Result);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE