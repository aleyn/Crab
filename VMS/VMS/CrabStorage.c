/******************** Copyright wisearm.com *********************************
* File Name         : CrabStorage.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 存储管理器
********************************************************************************/
#include "CrabVMS.h"
#include "CrabStorage.h"

#define CrabFileTableAddr   0x00000008
#define CrabFileEmptyAddr   0xFFFFFFFF
#define CrabFileBeginAddr   0x00001000
#define CrabFileTableMask1  0x00000FFF   
#define CrabFileTableMask2  0xFFFFF000
#define CrabFileTableStep   0x00001000
#define CrabFileTableMax    128

TCrabStream       FlashStream;         
TCrabStoreInfo    FlashStreamInfo;
TCrabStream       EEpromStream;
TCrabStoreInfo    EEpromStreamInfo;
TCrabStream       CodeStream;
TCrabStoreInfo    CodeStreamInfo;

/*******************************************************************************
* Function    : CrabCreateStoreStream
* Caption     : 建立存储器流
* Return      : CrabBool
* Description : .
*******************************************************************************/
CrabBool CrabCreateStoreStream()
{
  //所有外置FLASH空间
  FlashStreamInfo.Type = CRAB_STORE_TYPE_FLASH;
  FlashStreamInfo.Offset = 0;
  FlashStreamInfo.Size = CRAB_FLASH_MAX_SIZE;
  CrabStoreStream_Create(&FlashStream, &FlashStreamInfo);
  
  //所有外置EEPROM空间
  EEpromStreamInfo.Type = CRAB_STORE_TYPE_EEPROM;
  EEpromStreamInfo.Offset = 0;
  EEpromStreamInfo.Size = CRAB_EEPROM_MAX_SIZE;
  CrabStoreStream_Create(&EEpromStream, &EEpromStreamInfo);
  
  //外置FLASH桥接空间，用於代码存储
  CodeStreamInfo.Type = CRAB_STORE_TYPE_FLASH;
  CodeStreamInfo.Offset = 0;
  CodeStreamInfo.Size = 1024;
  CrabStoreStream_Create(&CodeStream, &CodeStreamInfo);
  
  return CrabTrue;
}

/*******************************************************************************
* Function    : CrabScanFileTable
* Caption     : 扫描文件索引表，并找到空白位置或最后的文件位置
*  @Param     : 1.ScanMode - 空白位置，或最后的文件位置
*  @Param     : 2.FileTable - 文件索引表
*  @Param     : 3.Count - 查找深度
* Return      : CrabUint
* Description : 索引位置
*******************************************************************************/
CrabUint CrabScanFileTable(CrabUint ScanMode, PCrabFileTable FileTable, CrabUint Count)
{
  TCrabFileTable  Table1, Table2;
  CrabUint         I;
  CrabUint         Result = 0;
  CrabUint         Addr = CrabFileTableAddr;
  
  if ((Count == 0) || (Count > CrabFileTableMax))
  {
    Count = CrabFileTableMax;
  }
  
  for (I=0; I<Count; I++)
  {
    Table2.FileAddr = Table1.FileAddr;
    Table2.FileSize = Table1.FileSize;          
    
    CrabStream_Seek(&FlashStream, Addr, csoBeginning);
    CrabStream_Read(&FlashStream, (CrabByte*)&Table1, sizeof(TCrabFileTable));

    if ((Table1.FileAddr == CrabFileEmptyAddr) && (Table1.FileSize == CrabFileEmptyAddr))
    {
      if (ScanMode == CRAB_SCAN_LAST_FILE)
      {
        if (I > 0)
        {
          Result = I;
          FileTable->FileAddr = Table2.FileAddr;
          FileTable->FileSize = Table2.FileSize;
        }
        else
        {
          FileTable->FileAddr = 0;
          FileTable->FileSize = 0;
        }
      }
      else if (ScanMode == CRAB_SCAN_LAST_SPACE)
      {
        Result = I + 1;
        FileTable->FileSize = 0;
        
        if (I > 0)
        {
          FileTable->FileAddr = Table2.FileAddr + Table2.FileSize;
          
          if ((FileTable->FileAddr & CrabFileTableMask1) > 0)
          {
            FileTable->FileAddr = (FileTable->FileAddr & CrabFileTableMask2) + CrabFileTableStep;
          }
          
        }
        else
        {
          FileTable->FileAddr = CrabFileBeginAddr;
        }        
      }
      
      break;
    }
    
    Addr += sizeof(TCrabFileTable);
  }
  
  return Result;
}

/*******************************************************************************
* Function    : CrabUpdateFileTable
* Caption     : 更新文件索引表
*  @Param     : 1.Index - 索引位置
*  @Param     : 2.FileTable - 文件索引表
* Return      : CrabUint
* Description : 真实的文件存储起始位置
*******************************************************************************/
CrabUint CrabUpdateFileTable(CrabUint Index, PCrabFileTable FileTable)
{
  CrabUint Result = 0;
  
  if ((Index == 0) || (Index > CrabFileTableMax))
  {
    Index = 1;
  }
  
  Result = CrabFileTableAddr + (Index - 1) * sizeof(TCrabFileTable);
  CrabStream_Seek(&FlashStream, Result, csoBeginning);
  CrabStream_Write(&FlashStream, (CrabByte*)FileTable, sizeof(TCrabFileTable));  
  
  return Result;
}

/*******************************************************************************
* Function    : CrabLoadFileToCodeStream
* Caption     : 从存储器中载入文件数据到文件流中
* Return      : CrabUint
* Description : 成功与否
*******************************************************************************/
CrabUint CrabLoadFileToCodeStream()
{
  TCrabFileTable FileTable;
  CrabUint Index;
  
  Index = CrabScanFileTable(CRAB_SCAN_LAST_FILE, &FileTable, 0);
  if ((Index == 0) || (Index > CrabFileTableMax))
  {
    return 0;
  }
  
  if ((FileTable.FileAddr == CrabFileEmptyAddr) || (FileTable.FileAddr == 0) 
   || (FileTable.FileSize == CrabFileEmptyAddr) || (FileTable.FileSize == 0))
  {
    return 0;
  }
  
  CrabStoreStream_Update(&CodeStream, FileTable.FileAddr, FileTable.FileSize);

  return FileTable.FileSize;
}
