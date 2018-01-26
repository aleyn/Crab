/******************** Copyright wisearm.com *********************************
* File Name         : CrabStaticApi.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ��̬API����
********************************************************************************/
#include "CrabVMS.h"
#include "FreeRTOS.h"
#include "task.h"
#include "CrabHardware.h"

/*******************************************************************************
* Function    : CrabRegisterStaticApi
* Caption     : ע�ᾲ̬API���� 
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
* Caption     : ������¼��ܿ���
*  @Param     : 1.State - ����״̬
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
* Caption     : ��׼����
*  @Param     : 1.Type - ��������
*  @Param     : 2.Buffer - ���뻺����
*  @Param     : 3.Length - ����������
* Return      : crabapi
* Description : ��׼��������Ǽ��̣����ڣ��ֱ����ȵ�
*******************************************************************************/
crabapi CrabInput (CrabUint Type, CrabAnsi Buffer, PCrabUint Length)
{
}

/*******************************************************************************
* Function    : CrabPrint
* Caption     : ��׼���
*  @Param     : 1.Text - �ı��ַ���
*  @Param     : 2.Length - �ַ�������
* Return      : crabapi
* Description : ��׼�����Ŀ�꣬�����Ǵ��ڣ�USB����Ļ����ӡ�����ȵ�
*******************************************************************************/
crabapi CrabPrint (CrabAnsi Text, CrabUint Length, CrabBool LineEnd)
{ 
  //CrabChar *Buf;
  
  if (Length == 0)
  {
    Length = strlen(Text);
  }
 
  //USBGAP��ʽ
  /*if (LineEnd)
  {
    if (!Log_Check(&Buf, Length + 2)) return;
    CrabMemCopy(Buf, Text, Length);
    
    Buf+=Length;
    
    Buf[0] = 0x0D;
    Buf[1] = 0x0A;
    
    Log_Add(0, Length + 2);
  }
  else
  {
    if (!Log_Check(&Buf, Length)) return;
    CrabMemCopy(Buf, Text, Length);
    Log_Add(0, Length);
  }*/
  
  //���ڷ�ʽ
  CrabHW_PutString(Text, Length);
  
  if (LineEnd)
  {
    putchar(0x0D);
    putchar(0x0A);
  }
}

/*******************************************************************************
* Function    : CrabDelay
* Caption     : ��ʱ����
*  @Param     : 1.MS - ����
* Description : �ŽӺ�����RTOS����ʱ
*******************************************************************************/
crabapi CrabDelay (CrabUint MSec)
{
   vTaskDelay(MSec);
}
