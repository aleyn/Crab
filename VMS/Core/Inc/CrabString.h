/******************** Copyright wisearm.com ************************************
* File Name         : CrabString.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 字符串函数
********************************************************************************/

#ifndef __CRAB_STRING__
#define __CRAB_STRING__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define  CrabStrShortSize   2                                   //短字符串最大字符个数，不可随意修改
#define  CrabStrLongSize    255                                 //长字符串最大的字符个数，这个不要随便乱改

#pragma pack(1)
typedef union
{
  CrabUint   FullData;
  struct
  {
    CrabByte Size;
    CrabByte Len;
    CrabChar Data[CrabStrShortSize];
  };
} TCrabShortString, *PCrabShortString, *CrabShortString;   //结构方式必须与CrabString兼容

#pragma pack(1)
typedef struct
{
  CrabByte Size;
  CrabByte Len;
  CrabChar Data[CrabStrLongSize];
} TCrabFullString, *PCrabFullString, *CrabFullString;      //结构方式必须与CrabString兼容

#define  CrabStringBuffer(Name, Len)   CrabChar   Name[Len + 2]   //建立字符串缓冲区，适合局部变量自动申请的方式

#define  CrabStringCreate(Name, Len) \
         CrabChar    Name##_Buffer[Len + 2]; \
         CrabString  Name = CrabStringAssign(Name##_Buffer, Len, CrabTrue)

//指定某个缓冲区为字符串（适合局部变量自动申请的方式)
CrabString CrabStringAssign(PCrabChar Buffer, CrabByte Len, CrabBool FillZero);

//从ANSI字符串中建立字符串，当Str为Null时，则直接申请字符串
CrabString  CrabStringAlloc(CrabAnsi Str, CrabByte Len);

//申请短字符串
CrabString  CrabStringAllocShort();

//申请全长字符串
CrabString  CrabStringAllocFull();

//释放字符串
CrabString  CrabStringFree(CrabString Str);

//清空字符串
CrabString  CrabStringClear(CrabString Str);

//字符串复制，Char方式
CrabString  CrabStringCopyChar(CrabString DstStr, CrabByte DstIdx, CrabChar SrcChar);

//字符串复制，ANSI方式
CrabString  CrabStringCopyAnsi(CrabString DstStr, CrabByte DstIdx, CrabAnsi SrcStr, CrabByte SrcLen);

//字符串复制
CrabString  CrabStringCopy(CrabString DstStr, CrabByte DstIdx, CrabString SrcStr);

//字符串尾增，Char方式
CrabString  CrabStringAppendChar(CrabString DstStr, CrabChar SrcChar);

//字符串尾增，ANSI方式
CrabString  CrabStringAppendAnsi(CrabString DstStr, CrabAnsi SrcStr, CrabByte SrcLen);

//字符串尾增
CrabString  CrabStringAppend(CrabString DstStr, CrabString SrcStr);

//字符串剪切, ANSI方式
CrabString  CrabStringCutAnsi(CrabString DstStr, CrabAnsi SrcStr, CrabByte SrcIdx, CrabByte SrcLen);

//字符串剪切
CrabString  CrabStringCut(CrabString DstStr, CrabString SrcStr, CrabByte SrcIdx, CrabByte SrcLen);

//字符串从ANSI中导入
CrabString  CrabStringAssignAnsi(CrabString DstStr, CrabAnsi SrcStr);

//将普通字符串编译成IDE字符串,ANSI模式
CrabUint  CrabStringEncodeAnsi(CrabAnsi DstStr, CrabAnsi SrcStr, CrabByte SrcLen);

//将普通字符串编译成IDE字符串
CrabString  CrabStringEncode(CrabString DstStr, CrabString SrcStr, CrabBool Clear);

//将IDE字符串解译成普通字符串,ANSI模式
CrabUint  CrabStringDecodeAnsi(CrabAnsi DstStr, CrabAnsi SrcStr, CrabByte SrcLen);

//将IDE字符串解译成普通字符串
CrabString  CrabStringDecode(CrabString DstStr, CrabString SrcStr, CrabBool Clear);

//查找字符串中某个子串
CrabInt CrabStringFind(CrabString Str, CrabString Sub);

//查找字符串中某个字符
CrabInt CrabStringFindC(CrabString Str, CrabChar C);

//打印字符串
CrabBool  CrabStringPrint(CrabString Str);

//16进制字符串转为半字节
CrabByte CrabHexToHalfByte(CrabChar HexChar);

//半字节转为16进制字符串
CrabChar CrabHexFromHalfByte(CrabByte Data);

//将16进制字符串转为无符号整型
CrabUint CrabHexToUint(CrabString HexStr, CrabBool IdeMode);

//将16进制字符串转为有符号整型
CrabInt CrabHexToInt(CrabString HexStr, CrabBool IdeMode);

//将16进制字符串转为普通字符串
CrabString CrabHexToString(CrabString HexStr, CrabString Result);

//将数值转为16进制字符串
CrabString  CrabHexFromUint(CrabUint Data, CrabUint Digits, CrabBool Clear, CrabString Result);

//将转义数值转为字符
CrabChar CragEscToChar(CrabString EscStr);

//未做
CrabString  CrabDateTimeName(CrabString Format, CrabDatetime Datetime, CrabString Result);   //未做

//字符串转布尔型
CrabBool    CrabStringToBool  (CrabString Value);

//字符串转无符号整型
CrabUint    CrabStringToUint  (CrabString Value);

//字符串转整形
CrabInt     CrabStringToInt   (CrabString Value);

//字符串转浮点型
CrabFloat   CrabStringToFloat (CrabString Value);

//字符串转日期型
CrabDate    CrabStringToDate  (CrabString Value);

//字符串转时间型
CrabTime    CrabStringToTime  (CrabString Value);

//字符串是否是整型
CrabBool    CrabStringIsInt   (CrabString Value);

//字符串是否是无符号整型
CrabBool    CrabStringIsUint  (CrabString Value);

//字符串是否是浮点型
CrabBool    CrabStringIsFloat (CrabString Value);

//将布尔型转为字符串
CrabString  CrabStringFromBool  (CrabBool V, CrabBool Clear, CrabString Result);

//将整形转为字符串
CrabString  CrabStringFromInt   (CrabInt V, CrabBool Clear, CrabString Result);

//将无符号整型转为字符串
CrabString  CrabStringFromUint    (CrabUint V, CrabBool Clear, CrabString Result);
CrabString  CrabStringFromUintIDE (CrabUint V, CrabBool Clear, CrabString Result);

//将浮点型转为字符串
CrabString  CrabStringFromFloat    (CrabFloat V, CrabBool Clear, CrabString Result);
CrabString  CrabStringFromFloatIDE (CrabFloat V, CrabBool Clear, CrabString Result);

//将日期型转为字符串
CrabString  CrabStringFromDate     (CrabDate V, CrabBool Clear, CrabString Result);
CrabString  CrabStringFromDateIDE  (CrabDate V, CrabBool Clear, CrabString Result);

//将时间型转为字符串
CrabString  CrabStringFromTime     (CrabTime V, CrabBool Clear, CrabString Result);
CrabString  CrabStringFromTimeIDE  (CrabTime V, CrabBool Clear, CrabString Result);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE