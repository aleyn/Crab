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

#define  CrabNull           null              //空指针
#define  CrabNullString     (CrabString)(0)   //空字符串
#define  CrabTrue           0x00000001        //True  - CrabBool 真值
#define  CrabFalse          0x00000000        //False - CrabBool 否值
  
#ifdef  __ICCARM__  
#define __flash _Pragma("location=\".rodata\"")
#define __cache _Pragma("location=\".ccmram\"")
#define __ram   _Pragma("location=\".data\"")
#else
#define __flash
#define __cache
#define __ram
#endif

//基本类型
typedef          char  CrabChar;      //字符型
typedef unsigned char  CrabByte;      //单字节
typedef unsigned short CrabWord;      //双字节
typedef unsigned int   CrabUint;      //四字节，无符号整型
typedef unsigned long  CrabULong;     //八字节，无符号长整型
typedef unsigned int   CrabBool;      //布尔型
typedef          int   CrabInt;       //有符号整形
typedef          long  CrabLong;      //有符号长整型
typedef          float CrabFloat;     //浮点型
typedef unsigned int   CrabUID;       //惟一键值
typedef unsigned int   CrabHandle;    //句柄型
typedef          void  CrabVoid;      //无类型

typedef CrabChar      *PCrabChar;
typedef CrabByte      *PCrabByte;
typedef CrabWord      *PCrabWord;
typedef CrabUint      *PCrabUint;
typedef CrabBool      *PCrabBool;
typedef CrabFloat     *PCrabFloat;
typedef CrabVoid      *CrabPoint;

typedef CrabChar      *CrabAnsi; //C语言缺省字符串类型

#pragma pack(1)
//日期型
typedef CrabUint      CrabDate;
typedef union
{
  CrabDate            Date;
  struct
  {
    CrabWord          Year;
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
  CrabDate       Date;
  CrabTime       Time;
} TCrabDatetime, *PCrabDatetime, CrabDatetime;  //日期时间型

//字符串型，仅系统用，实际申请内存大小为原始长度+3;
typedef struct
{
  CrabByte Size;                           //字符串内存大小;
  CrabByte Len;                            //字符串当前长度，Len <= Size;
  CrabChar Data[0];                        //字符串数据，(最后一个字符为\0，兼容ANSI C的方式)
} TCrabString, *PCrabString, *CrabString;  //字符串型

//双字节地址
typedef union
{
  CrabWord Addr;
  CrabByte Addrs[2];
} TCrabUnionWord;               //双字节共用

//三字节地址
typedef union
{
  CrabByte Values[3];          //数组值，三字节
  struct
  {
    CrabWord LowValue;         //低位值，双字节
    CrabByte HighValue;        //高位值，单字节
  };
} TCrabThree, TCrabCodeAddr;   //三字节地址

//四节字联用
typedef union
{
  CrabUint     FullValue;      //合并值，无符号整型
  CrabInt      IntValue;       //有符号整型
  CrabByte     Values[4];      //数组值，四字节
  struct
  {
    CrabWord   LowValue;       //低位值，双字节
    CrabWord   HighValue;      //高位值，双字节
  };
  struct  
  {
    CrabByte   ByteValue0;
    CrabByte   ByteValue1;
    CrabByte   ByteValue2;
    CrabByte   ByteValue3;
  };
} TCrabUnion, CrabUnion;                  //四节字联用

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE