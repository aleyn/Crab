/******************** Copyright wisearm.com *********************************
* File Name         : CrabStorage.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : .
********************************************************************************/
#ifndef __CRAB_STORAGE__
#define __CRAB_STORAGE__

#include "CrabBaseType.h"
#include "CrabStream.h"
#include "CrabStoreStream.h"

#ifdef  __cplusplus
extern "C" {
#endif  
  
#define CRAB_FLASH_MAX_SIZE   (1024 * 1024)
#define CRAB_EEPROM_MAX_SIZE  (256 * 1024)
  
#define CRAB_SCAN_LAST_FILE   0x01
#define CRAB_SCAN_LAST_SPACE  0x02  
  
typedef struct
{
  CrabUint FileAddr;
  CrabUint FileSize;
} TCrabFileTable, *PCrabFileTable;


extern TCrabStream   FlashStream;
extern TCrabStream   EEpromStream;
extern TCrabStream   CodeStream;

//创建三个文件流
CrabBool CrabCreateStoreStream();

//扫描文件索引表，并找到空白位置或最后的文件位置
CrabUint CrabScanFileTable(CrabUint ScanMode, PCrabFileTable FileTable, CrabUint Count);

//更新文件索引表
CrabUint CrabUpdateFileTable(CrabUint Index, PCrabFileTable FileTable);

//从存储器中载入文件数据到文件流中
CrabUint CrabLoadFileToCodeStream();
#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE