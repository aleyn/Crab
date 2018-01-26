/******************** Copyright wisearm.com ************************************
* File Name         : CrabDatetime.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ����ʱ�亯��
********************************************************************************/

#ifndef __CRAB_DATETIME__
#define __CRAB_DATETIME__

#include "CrabBaseType.h"

#define CRABTIMEMAX  93600000
#define CRABDATEMAX   3659634

#ifdef  __cplusplus
extern "C" {
#endif

//ȡ�ù�Ԫ������ĳһ��������ܺ�.
CrabUint  CrabDate_GetYearSumDay(CrabUShort Year);

//ȡ��һ���д�1�µ�ָ���·ݵ������ܺ�.
CrabUint  CrabDate_GetMonthSumDay(CrabUShort Year, CrabUShort Month);

//ȡ��һ����ĳ���·ݵ�������
CrabUint  CrabDate_GetMonthDay(CrabUShort Year, CrabUShort Month);

//���������ڱ�������ڸ�ʽ
CrabDate  CrabDate_Encode(CrabUShort Year, CrabByte Month, CrabByte Day);

//�����ڸ�ʽ����ɵ�������
CrabBool  CrabDate_Decode(CrabDate Date, CrabUShort __var wYear, CrabByte __var bMonth, CrabByte __var bDay);

//ȡ��ĳһ��Ϊ���ڼ�
CrabBool  CrabDate_GetWeek(CrabDate Date, CrabByte __var bWeek);

//���ڸ�ʽתΪ����
CrabDate  CrabDate_Packed(TCrabDate Date);

//����תΪ������
TCrabDate CrabDate_Unpacked(CrabUint Date);

//�޸���������
CrabDate  CrabDate_FixValue(CrabDate Date);

//������ʱ������ʱ���ʽ
CrabTime  CrabTime_Encode(CrabByte Hour, CrabByte Min, CrabByte Sec, CrabUShort MSec);

//��ʱ���ʽ����ɵ���ʱ��
CrabBool  CrabTime_Decode(CrabTime Time, CrabByte __var Hour, CrabByte __var Min, CrabByte __var Sec, CrabUShort __var MSec);

//ʱ����תΪ����
CrabTime  CrabTime_Packed(TCrabTime Time);

//����תΪʱ����
TCrabTime CrabTime_Unpacked(CrabTime Time);

//�޸�����ʱ��
CrabTime  CrabTime_FixValue(CrabTime Time);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE