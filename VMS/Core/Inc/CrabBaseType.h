/******************** Copyright wisearm.com ************************************
* File Name         : CrabBaseType.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 基本类型
********************************************************************************/
#ifndef __CRAB_BASE_TYPE__
#define __CRAB_BASE_TYPE__

//#include "xxx.h"

#ifdef  __cplusplus
extern "C" {
#endif

//重定义
#define  crabapi   void                //函数
#define  __var     *                   //参数输出
#define  __ref     &                   //参数传址
#define  nil       ((void *)0)         //空指针
#define  null      ((void *)0)         //空指针
#define  nullstr   ((char *)0)         //空字符串
#define  not       !                   //逻辑否
#define  and       &&                  //逻辑与
#define  or        ||                  //逻辑或

#define  False     0                   //逻辑假
#define  True      !False              //逻辑真

#define  CrabNull           null        //空指针
#define  CrabTrue           1           //True  - CrabBool 真值
#define  CrabFalse          0           //False - CrabBool 否值

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
#define CRABTYPE_DATETIME   0x78

#define CRABTYPE_ARRAY      0x84
#define CRABTYPE_OBJECT     0x94

//基本类型
typedef          void   CrabVoid;      //无类型
typedef unsigned char   CrabBool;      //布尔型
typedef          char   CrabChar;      //字符型，单字节ANSI
#ifdef __BORLANDC__
typedef         wchar_t CrabText;      //文本型，双字节UNICODE
#else
typedef         short   CrabText;      //文本型，双字节UNICODE
#endif
typedef unsigned char   CrabByte;      //单字节
typedef unsigned short  CrabUShort;    //双字节
typedef unsigned int    CrabUint;      //四字节，无符号整型
typedef unsigned long   CrabULong;     //八字节，无符号长整型
typedef          char   CrabTiny;      //有符号单字节
typedef          short  CrabShort;     //有符号双字节
typedef          int    CrabInt;       //有符号整形
typedef          long   CrabLong;      //有符号长整型
typedef          float  CrabFloat;     //单精度浮点型
typedef          double CrabDouble;    //双精度浮点型
typedef unsigned int    CrabUID;       //惟一键值
typedef unsigned int    CrabHandle;    //句柄型
typedef          int    CrabState;     //状态型

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

typedef CrabChar       *CrabAnsi; //C语言缺省字符串类型
typedef CrabText       *CrabWide; //系统缺省宽字符串类型

typedef union
{
  CrabText              Text;     //国际字符型
  CrabUShort            Unicode;  //国际UNICODE码
  struct
  {
    CrabChar            Char1;    //ANSI 字符1
    CrabChar            Char2;    //ANSI 字符2
  };
} CrabUnicode, *PCrabUnicode;

#pragma pack(1)
//日期型
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
} TCrabDate, *PCrabDate;   //日期型

#pragma pack(1)
//时间型
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
} TCrabTime, *PCrabTime;   //时间型

//日期时间型
typedef union
{
  CrabULong     FullValue;
  struct
  {
    CrabTime    Time;            //时间在低位
    CrabDate    Date;            //日期在高位
  };
  struct
  {
    CrabUShort    LowTime;         //低位值，双字节
    CrabUShort    HighTime;        //高位值，双字节
    CrabUShort    LowDate;         //低位值，双字节
    CrabUShort    HighDate;        //高位值，双字节
  };
} TCrabDatetime, *PCrabDatetime, CrabDatetime;  //日期时间型

//字符串型，仅系统用，实际申请内存大小为原始长度+3;
typedef struct
{
  CrabShort     Refer;                     //字符串引用计数器
  CrabByte      Size;                      //字符串内存大小;
  CrabByte      Len;                       //字符串当前长度，Len <= Size;
  CrabChar      Data[0];                   //字符串文本内容
} TCrabString, *PCrabString, *CrabString;  //字符串型

//双字节地址
typedef union
{
  CrabUShort    Addr;
  CrabByte      Addrs[2];
} TCrabUnionWord;               //双字节共用

//三字节地址
typedef union
{
  CrabByte      Values[3];          //数组值，三字节
  struct
  {
    CrabUShort  LowValue;         //低位值，双字节
    CrabByte    HighValue;        //高位值，单字节
  };
} TCrabThree, TCrabCodeAddr;   //三字节地址

//四节字联用
typedef union
{
  CrabUint        FullValue;
  CrabByte        Values[4];      //数组值，4字节
  struct
  {
    CrabUShort    LowValue;       //低位值，双字节
    CrabUShort    HighValue;      //高位值，双字节
  };
} TCrabUnion, *PCrabUnion, CrabUnion;       //四节字联用

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

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE