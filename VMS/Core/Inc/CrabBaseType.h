/******************** Copyright wisearm.com ************************************
* File Name         : CrabBaseType.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ��������
********************************************************************************/
#ifndef __CRAB_BASE_TYPE__
#define __CRAB_BASE_TYPE__

//#include "xxx.h"

#ifdef  __cplusplus
extern "C" {
#endif

//�ض���
#define  crabapi   void                //����
#define  __var     *                   //�������
#define  __ref     &                   //������ַ
#define  nil       ((void *)0)         //��ָ��
#define  null      ((void *)0)         //��ָ��
#define  nullstr   ((char *)0)         //���ַ���
#define  not       !                   //�߼���
#define  and       &&                  //�߼���
#define  or        ||                  //�߼���

#define  False     0                   //�߼���
#define  True      !False              //�߼���

#define  CrabNull           null        //��ָ��
#define  CrabTrue           1           //True  - CrabBool ��ֵ
#define  CrabFalse          0           //False - CrabBool ��ֵ

#define CRABTYPE_VOID       0x01
#define CRABTYPE_BOOL       0x11

#define CRABTYPE_TINY       0x21
#define CRABTYPE_SHORT      0x22
#define CRABTYPE_INT        0x24
#define CRABTYPE_LONG       0x28

#define CRABTYPE_BYTE       0x31
#define CRABTYPE_USHORT     0x32
#define CRABTYPE_UINT       0x34
#define CRABTYPE_ULONG      0x38

#define CRABTYPE_FLOAT      0x44
#define CRABTYPE_DOUBLE     0x48

#define CRABTYPE_CHAR       0x52
#define CRABTYPE_STRING     0x54

#define CRABTYPE_TIME       0x64
#define CRABTYPE_DATE       0x74
#define CRABTYPE_DATETIME   0x68

#define CRABTYPE_ARRAY      0x84
#define CRABTYPE_STRUCT     0x94
#define CRABTYPE_OBJECT     0xA4

//��������
typedef             void     CrabVoid;      //������
typedef unsigned    char     CrabBool;      //������
typedef             char     CrabChar;      //�ַ��ͣ����ֽ�ANSI
#ifdef __BORLANDC__
typedef             wchar_t  CrabText;      //�ı��ͣ�˫�ֽ�UNICODE
#else
typedef             short    CrabText;      //�ı��ͣ�˫�ֽ�UNICODE
#endif
typedef unsigned    char     CrabByte;      //���ֽ�
typedef unsigned    short    CrabUShort;    //˫�ֽ�
typedef unsigned    int      CrabUint;      //���ֽڣ��޷�������
#ifdef __BORLANDC__
typedef unsigned  __int64    CrabULong;     //���ֽڣ��޷��ų�����
#else
typedef unsigned long long   CrabULong;     //���ֽڣ��޷��ų�����
#endif
typedef             char     CrabTiny;      //�з���,���ֽ�
typedef             short    CrabShort;     //�з���,˫�ֽ�
typedef             int      CrabInt;       //�з�������,���ֽ�
#ifdef __BORLANDC__
typedef           __int64    CrabLong;      //�з��ų�����,���ֽ�
#else
typedef          long long   CrabLong;      //�з��ų�����,���ֽ�
#endif
typedef             float    CrabFloat;     //�����ȸ�����
typedef             double   CrabDouble;    //˫���ȸ�����
typedef unsigned    int      CrabUID;       //Ωһ��ֵ
typedef unsigned    int      CrabHandle;    //�����
typedef             int      CrabState;     //״̬��

typedef CrabChar       *PCrabChar;
typedef CrabText       *PCrabText;
typedef CrabByte       *PCrabByte;
typedef CrabUShort     *PCrabUShort;
typedef CrabUint       *PCrabUint;
typedef CrabULong      *PCrabULong;
typedef CrabTiny       *PCrabTiny;
typedef CrabShort      *PCrabShort;
typedef CrabInt        *PCrabInt;
typedef CrabLong       *PCrabLong;
typedef CrabBool       *PCrabBool;
typedef CrabFloat      *PCrabFloat;
typedef CrabDouble     *PCrabDouble;
typedef CrabVoid       *CrabPoint;

typedef CrabChar       *CrabAnsi; //C����ȱʡ�ַ�������
typedef CrabText       *CrabWide; //ϵͳȱʡ���ַ�������

#pragma pack(1)
typedef union
{
  CrabText              Text;     //�����ַ���
  CrabUShort            Unicode;  //����UNICODE��
  struct
  {
    CrabChar            Char1;    //ANSI �ַ�1
    CrabChar            Char2;    //ANSI �ַ�2
  };
} CrabUnicode, *PCrabUnicode;

#pragma pack(1)
//������
typedef CrabUint      CrabDate;
typedef union
{
  CrabDate            Date;
  struct
  {
    CrabUShort        Year;
    CrabByte          Month;
    CrabByte          Day;
  };
} TCrabDate, *PCrabDate;   //������

#pragma pack(1)
//ʱ����
typedef CrabUint      CrabTime;
typedef union
{
  CrabTime          Time;
  struct
  {
    CrabByte        Hour;
    CrabByte        Min;
  };
  struct
  {
    CrabUint        Res  :16;
    CrabUint        Sec  :6;
    CrabUint        MSec :10;
  };
} TCrabTime, *PCrabTime;   //ʱ����

//����ʱ����
#pragma pack(1)
typedef union
{
  CrabULong     FullValue;
  struct
  {
    CrabTime    Time;            //ʱ���ڵ�λ
    CrabDate    Date;            //�����ڸ�λ
  };
  struct
  {
    CrabUShort    LowTime;         //��λֵ��˫�ֽ�
    CrabUShort    HighTime;        //��λֵ��˫�ֽ�
    CrabUShort    LowDate;         //��λֵ��˫�ֽ�
    CrabUShort    HighDate;        //��λֵ��˫�ֽ�
  };
} TCrabDatetime, *PCrabDatetime, CrabDatetime;  //����ʱ����

//�ַ����ͣ���ϵͳ�ã�ʵ�������ڴ��СΪԭʼ����+3;
#pragma pack(1)
typedef struct
{
  CrabShort     Refer;                     //�ַ������ü�����
  CrabByte      Size;                      //�ַ����ڴ��С;
  CrabByte      Len;                       //�ַ�����ǰ���ȣ�Len <= Size;
  CrabChar      Data[0];                   //�ַ����ı�����
} TCrabString, *PCrabString, *CrabString;  //�ַ�����

//˫�ֽڵ�ַ
#pragma pack(1)
typedef union
{
  CrabUShort    Addr;
  CrabByte      Addrs[2];
} TCrabUnionWord;               //˫�ֽڹ���

//���ֽڵ�ַ
#pragma pack(1)
typedef union
{
  CrabByte      Values[3];          //����ֵ�����ֽ�
  struct
  {
    CrabUShort  LowValue;         //��λֵ��˫�ֽ�
    CrabByte    HighValue;        //��λֵ�����ֽ�
  };
} TCrabThree, TCrabCodeAddr;   //���ֽڵ�ַ

//�Ľ�������
#pragma pack(1)
typedef union
{
  CrabUint        FullValue;
  CrabByte        Values[4];      //����ֵ��4�ֽ�
  struct
  {
    CrabUShort    LowValue;       //��λֵ��˫�ֽ�
    CrabUShort    HighValue;      //��λֵ��˫�ֽ�
  };
} TCrabUnion, *PCrabUnion, CrabUnion;       //�Ľ�������

#pragma pack(1)
typedef union
{
  CrabULong   LongValue;
  CrabByte    Values[8];
  struct
  {
    CrabUnion LowUnion;
    CrabUnion HighUnion;
  };
} TCrabLongUnion, *PCrabLongUnion, CrabLongUnion;

#pragma pack()

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE