/******************** Copyright wisearm.com *********************************
* File Name         : CrabApplication.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : Ӧ�ó���������
********************************************************************************/
#include "CrabVMS.h"
#include "CrabApplication.h"
#include "CrabExecute.h"

CrabByte CrabAppMemory[CRAB_MEMORY_SIZE];
CrabByte CrabAppCache[CRAB_CACHE_SIZE];
CrabByte CrabAppStatus = CRAB_APP_OFF;

/*******************************************************************************
* Function    : CrabApplicationInit
* Caption     : ��ʼ�����������
* Description : .
*******************************************************************************/
void CrabApplicationInit()
{
  TCrabConfig Config;

  Config.Memory = &CrabAppMemory;
  Config.MemorySize = CRAB_MEMORY_SIZE;
  Config.FifoCount = CRAB_FIFO_COUNT;
  Config.Cache = &CrabAppCache;
  Config.CacheSize = CRAB_CACHE_SIZE;
  Config.StrPoolCount = CRAB_REG_STR_POOL_COUNT;
  Config.ArrayDimCount = CRAB_ARRAY_DIM_COUNT;  
  
  CrabExecute_Create(&Config);  
}

/*******************************************************************************
* Function    : CrabChangeAppState
* Caption     : �ı����������״̬
* Description : .
*******************************************************************************/
void CrabChangeAppState(CrabByte State)
{
  switch (State)
  {
    case CRAB_APP_OFF:
    case CRAB_APP_STOPPING:
    case CRAB_APP_LOADROM:
    case CRAB_APP_ERROR:
    case CRAB_APP_STANDBY:
    {
      CrabAppStatus = State;
      break;
    }
    case CRAB_APP_RESET:
    {
      switch (CrabAppStatus)
      {
        case CRAB_APP_RUNNING:
        case CRAB_APP_PAUSE:
        case CRAB_APP_STEP:
        case CRAB_APP_ERROR:
        {
          CrabAppStatus = CRAB_APP_RESET;
          break;
        }
        default:
        {
          CrabAppStatus = CRAB_APP_LOADROM;
        }
      }
      break;
    }
    case CRAB_APP_PAUSE:
    {
      if (CrabAppStatus == CRAB_APP_RUNNING)
      {
        CrabAppStatus = CRAB_APP_PAUSE;
      }
      else if (CrabAppStatus == CRAB_APP_PAUSE)
      {
      }
      else
      {
        CrabAppStatus = CRAB_APP_STOPPING;
      }
      break;
    }
    case CRAB_APP_STEP:
    {
      if (CrabAppStatus == CRAB_APP_RUNNING)
      {
        CrabAppStatus = CRAB_APP_STEP;
      }
      else if (CrabAppStatus == CRAB_APP_PAUSE)
      {
        CrabAppStatus = CRAB_APP_STEP;
      }
      else if (CrabAppStatus == CRAB_APP_STEP)
      {
        //CrabAppStatus = CRAB_APP_STEP;
      }
      else
      {
        CrabAppStatus = CRAB_APP_STOPPING;
      }
      break;
    }
    case CRAB_APP_CONTINUE:
    case CRAB_APP_RUNNING:
    {
      if (CrabAppStatus == CRAB_APP_PAUSE)
      {
        CrabAppStatus = CRAB_APP_CONTINUE;
      }
      else if (CrabAppStatus == CRAB_APP_RUNNING)
      {
      }
      else
      {
        CrabAppStatus = CRAB_APP_LOADROM;
      }
      break;
    }
    default:
    {
      CrabAppStatus = CRAB_APP_OFF;
    }
  }
}

/*******************************************************************************
* Function    : CrabApplicationTask
* Caption     : Ӧ������
* Description : �û�����Ӧ�ó����ڴ�����
*******************************************************************************/
void CrabApplicationTask()
{
  CrabBool IsContinue;
  CrabUint ErrCode;
  CrabUint ExecAddr;
  
  CrabApplicationInit();
  //CrabApplicationReset();
  CrabTaskSuspend(CRAB_TASK_APPLICATION);

  do
  {    
    switch (CrabAppStatus)
    {
      case CRAB_APP_OFF:
      {
        CrabUpdateLEDStatus();
        break;
      }
      case CRAB_APP_LOADROM:
      {
        IsContinue = CrabLoadFileToCodeStream() > 0;
        
        if (IsContinue) IsContinue = CrabExecute_LoadStream(&CodeStream, &EEpromStream);        
        if (IsContinue)
        {
          CrabVMS_log("Load app rom success.");
          CrabAppStatus = CRAB_APP_RESET;
        }
        else
        {
          CrabVMS_log("Load app rom faild.");
          CrabAppStatus = CRAB_APP_ERROR;
        }
        
        CrabUpdateLEDStatus();
        continue;
      }
      case CRAB_APP_RESET:
      case CRAB_APP_STANDBY:
      {
        CrabApplicationReset();        
        IsContinue = CrabExecute_Restart();
        
        if (IsContinue) IsContinue = CrabExecute_PrepareNextLine();
        
        if (IsContinue)
        {
          if (CrabAppStatus == CRAB_APP_STANDBY)
          {
            CrabAppStatus = CRAB_APP_PAUSE;
          }
          else
          {
            CrabVMS_log("App running.");
            CrabAppStatus = CRAB_APP_RUNNING;
          }
          CrabTaskResume(CRAB_TASK_EVENT);
        }
        else
        {
          CrabString ErrMsg;
          
          ErrCode = CrabExecute_GetErrorCode();
          ExecAddr = CrabExecute_GetCmdAddr();
          ErrMsg = CrabStringAlloc(255);
          CrabErrorMessage(ErrCode, ErrMsg);          
          
          CrabVMS_Log("Prepare next line faild (Addr:%8.8X, ErrCode:%d).", ExecAddr, ErrCode);
          CrabVMS_Log(ErrMsg->Data);
          CrabStringFree(ErrMsg);
          CrabAppStatus = CRAB_APP_ERROR;
        }

        CrabUpdateLEDStatus();
        continue;
      }
      case CRAB_APP_CONTINUE:
      {
        CrabVMS_log("App continue.");
        CrabTaskResume(CRAB_TASK_EVENT);
        CrabAppStatus = CRAB_APP_RUNNING;
        CrabUpdateLEDStatus();
      }
      case CRAB_APP_STEP:
      case CRAB_APP_RUNNING:
      {
        if (!CrabExecute_Actived())
        {
          CrabAppStatus = CRAB_APP_STOPPING;
          continue;
        }

        if (CrabExecute_RunCurrentLine())
        {
          if (!CrabExecute_Actived())
          {
            CrabAppStatus = CRAB_APP_STOPPING;
            continue;
          }
          
          CrabExecute_EventDispatch();
          
          if (CrabExecute_PrepareNextLine())
          {
            if (CrabAppStatus == CRAB_APP_STEP)
            {
              CrabAppStatus = CRAB_APP_PAUSE;
            }
          }
          else
          {
            CrabString ErrMsg;
            
            ErrCode = CrabExecute_GetErrorCode();            
            ExecAddr = CrabExecute_GetCmdAddr();
            ErrMsg = CrabStringAlloc(255);
            CrabErrorMessage(ErrCode, ErrMsg); 
            
            CrabVMS_Log("Prepare next line faild (Addr:%8.8X, ErrCode:%d).", ExecAddr, ErrCode);
            CrabVMS_Log(ErrMsg->Data);
            CrabStringFree(ErrMsg);
            CrabAppStatus = CRAB_APP_ERROR;
          }
        }
        else
        {
          CrabString ErrMsg;
          
          ErrCode = CrabExecute_GetErrorCode();            
          ExecAddr = CrabExecute_GetCmdAddr();
          ErrMsg = CrabStringAlloc(255);
          CrabErrorMessage(ErrCode, ErrMsg);
            
          CrabVMS_Log("Runtime error (Addr:%8.8X, ErrCode:%d).", ExecAddr, ErrCode);
          CrabVMS_Log(ErrMsg->Data);
          CrabStringFree(ErrMsg);
          CrabAppStatus = CRAB_APP_ERROR;
        }

        continue;
      }
      case CRAB_APP_PAUSE:
      {
        CrabVMS_log("App pause.");
        CrabUpdateLEDStatus();
        CrabTaskSuspend(CRAB_TASK_EVENT);
        break;
      }
      case CRAB_APP_ERROR:
      { 
        CrabApplicationStop();
        CrabUpdateLEDStatus();
        CrabTaskSuspend(CRAB_TASK_EVENT);
        break;
      }
      case CRAB_APP_STOPPING:
      { 
        CrabVMS_log("App stop.");
        CrabApplicationStop();
        CrabUpdateLEDStatus();
        CrabTaskSuspend(CRAB_TASK_EVENT);
        CrabAppStatus = CRAB_APP_OFF;
        break;
      }
    }
    
    CrabTaskSuspend(CRAB_TASK_APPLICATION);
  }
  while ( CrabAppStatus != CRAB_APP_EXCEPTION);

  CrabExecute_Destroy();
}
