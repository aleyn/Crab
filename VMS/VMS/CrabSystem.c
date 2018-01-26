/******************** Copyright wisearm.com *********************************
* File Name         : CrabSystem.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 系统硬件管理器
********************************************************************************/
#include "CrabVMS.h"
#include "CrabSystem.h"
#include "CrabVersionFW.h"

#pragma pack(1)
typedef struct {
  uint8_t NewStatus;
  uint8_t Count;
  uint8_t Tick;
  uint8_t Flash;
  uint8_t Status;
} TSYSLED;

typedef struct{ 
  uint16_t Count;
  uint8_t  Down;
  uint8_t  Res;
} TESCKEY;

typedef struct{
  uint8_t  NewStatus;
  uint8_t  Flash;
  uint16_t Width;
  uint16_t Tick;
  uint8_t  Count;
  uint8_t  Status;
} TSYSBEP;
#pragma pack()

static TSYSLED SysLed;
static TESCKEY EscKey;
static TSYSBEP SysBep;

extern CrabByte CrabAppStatus;
extern CrabByte CrabCmdStatus;

//闹钟数据
static TCrabAlarmClock  AlarmClock[CRAB_ALARM_COUNT];
uint16_t  AlarmClock_CheckTick = 0;

//CrabTime LastTime = 0;
//CrabUint ErrCount = 0;
//CrabUint TotalCount = 0;

void SYSLED_Process();
void ESCKEY_Process();
void SYSBEP_Process();
void ALARM_Process();

#define CrabSystem_LED_Output(Status)  LED_Output(SYS_LED, Status)
#define CrabSystem_ESC_Input()         GPIO_GetInputBit(SYS_ESC) == 0
#define CrabSystem_DBG_Input()         GPIO_GetInputBit(DEBUG_KEY) == 0

void CrabAlarmUpdateNextCheck(CrabByte Index, CrabBool Flag);

/*******************************************************************************
* Function    : CrabSystem_Running
* Caption     : .
* Description : .
*******************************************************************************/
void CrabSystem_Running()
{
  CrabCreateTask(CRAB_TASK_SYSTEM);
  //vTaskStartScheduler();
}

/*******************************************************************************
* Function    : CrabSystemTask
* Caption     : 系统级任务
* Description : .
*******************************************************************************/
void CrabSystemTask()
{ 
  EscKey.Count = 0;
  SysBep.NewStatus = 0xFF;  
  
  SysLed.NewStatus = CRAB_LED_GREEN_ON;
  SYSLED_Process();
  
  CrabTaskMutexInit();

  CrabTaskMutexEnter(CRAB_TASK_MUTEX_ALARM);
  CrabMemFZero(AlarmClock, sizeof(AlarmClock));
  CrabTaskMutexExit(CRAB_TASK_MUTEX_ALARM);
  
  CrabHW_InitExtern();
  
#if (CRAB_SHOW_LOGO == 1)
  ShowLogo();
#endif
  
  CrabCreateTask(CRAB_TASK_COMMAND);
  CrabCreateTask(CRAB_TASK_EVENT);
  CrabCreateTask(CRAB_TASK_APPLICATION);
  
#ifdef  CRABVMS_DEBUG
  CrabCreateTask(CRAB_TASK_DEBUG);
#endif
  
  CrabDelay(10);
  
  SysLed.NewStatus = CRAB_LED_RED_ON;
  CrabVMS_Log("CRAB Kernel Version %s", CRAB_FW_VERSION);
  CrabVMS_Log("Last Compile %s", CRAB_FW_COMPILE_DATE);
  
#if (CRAB_POWER_ON_LOAD_ROM == 1)
  if (CrabAppStatus == CRAB_APP_OFF)
  {
    CrabDelay(100);
    CrabChangeAppState(CRAB_APP_LOADROM);
    CrabTaskResume(CRAB_TASK_APPLICATION);
  }
#endif
  
  for(;;)
  {
    SYSLED_Process();
    ESCKEY_Process();
    SYSBEP_Process();
    
    if (AlarmClock_CheckTick)
    {
      AlarmClock_CheckTick --;
    }
    else
    {
      ALARM_Process();
      AlarmClock_CheckTick = CRAB_SYSTEM_ALARM_TICK;
    }
    
    CrabDelay(CRAB_SYSTEM_TICK);
  }    
}

/*******************************************************************************
* Function    : SYSLED_Process
* Caption     : 系统LED显示状态处理
* Description : .
*******************************************************************************/
void SYSLED_Process()
{
  if (SysLed.NewStatus != 0xFF)
  {
    switch (SysLed.NewStatus)
    {
      case CRAB_LED_RED_ERROR:
      case CRAB_LED_GREEN_ERROR:
      {
        SysLed.Count = CRAB_SYSTEM_LED_ERROR;
        SysLed.Flash = 1;
        break;
      }
      case CRAB_LED_GREEN_FLASH:
      case CRAB_LED_RED_FLASH:
      {
        SysLed.Count = CRAB_SYSTEM_LED_FLASH;
        SysLed.Flash = 1;
        break;
      }
      case CRAB_LED_RED_ON:
      case CRAB_LED_GREEN_ON:
      {
        SysLed.Count = 0;
        SysLed.Flash = 0;
        break;
      }
      default:
      {
        SysLed.Count = 0;
        SysLed.Flash = 0;
      }
    }
    
    switch (SysLed.NewStatus)
    {
      case CRAB_LED_RED_ERROR:
      case CRAB_LED_RED_FLASH:
      case CRAB_LED_RED_ON:
      {
        SysLed.Status = 1;
        break;
      }
      case CRAB_LED_GREEN_FLASH:
      case CRAB_LED_GREEN_ERROR:
      case CRAB_LED_GREEN_ON:
      {
        SysLed.Status = 2;
        break;
      }
      default:
      {
        SysLed.Status = 0;
      }
    }
    
    SysLed.Tick = 1;
    SysLed.NewStatus = 0xFF;
  }
  
  if (SysLed.Status)
  {
    if (SysLed.Count)
    {
      if (SysLed.Tick > 1)
      {
        SysLed.Tick--;
      }
      else
      {
        if (SysLed.Flash)
        {          
          if (SysLed.Status == 1)
          {
            CrabSystem_LED_Output(CRAB_LED_RED_ON);
          }
          else
          {
            CrabSystem_LED_Output(CRAB_LED_GREEN_ON);
          }
        }
        else
        {
          CrabSystem_LED_Output(CRAB_LED_OFF);
        }
        
        SysLed.Flash = 1 - SysLed.Flash;
        SysLed.Tick = SysLed.Count;
      }
    }
    else
    {
      if (SysLed.Tick)
      {
        if (SysLed.Status == 1)
        {
          CrabSystem_LED_Output(CRAB_LED_RED_ON);
        }
        else
        {
          CrabSystem_LED_Output(CRAB_LED_GREEN_ON);
        }
        
        SysLed.Tick = 0;
      }
    }
  }
  else
  {
    if (SysLed.Tick)
    {
      CrabSystem_LED_Output(CRAB_LED_OFF);
      SysLed.Tick = 0;
    }
  }
}

/*******************************************************************************
* Function    : ESCKEY_Process
* Caption     : 系统ESC按键处理
* Description : .
*******************************************************************************/
void ESCKEY_Process()
{
#ifdef  CRABVMS_DEBUG
  /*if (CrabSystem_DBG_Input())
  {
    while (CrabSystem_DBG_Input());
    CrabTaskResume(CRAB_TASK_DEBUG);
  }*/
#endif
  
  if (CrabSystem_ESC_Input())
  {
    if (EscKey.Count < CRAB_SYSTEM_KEY_LONG) EscKey.Count++;
    if (EscKey.Count > CRAB_SYSTEM_KEY_SHORT)
    {
      if (EscKey.Down !=1)
      {
        EscKey.Down = 1;
        
        if (CrabAppStatus == CRAB_APP_RUNNING)
        {
          CrabChangeAppState(CRAB_APP_STOPPING);          
          //CrabTaskResume(CRAB_TASK_APPLICATION);
        }
        else if (CrabAppStatus == CRAB_APP_PAUSE)
        {
          CrabChangeAppState(CRAB_APP_STOPPING);
          CrabTaskResume(CRAB_TASK_APPLICATION);
        }
        else if (CrabAppStatus != CRAB_APP_OFF)
        {
          CrabChangeAppState(CRAB_APP_OFF); 
          CrabTaskResume(CRAB_TASK_APPLICATION);
        }
      }
    }
  }
  else
  {
    if (EscKey.Count > 1)
    {
      if (EscKey.Count < CRAB_SYSTEM_KEY_SHORT)
      {
        if (CrabAppStatus == CRAB_APP_RUNNING)
        {
          CrabChangeAppState(CRAB_APP_PAUSE);
          //CrabTaskResume(CRAB_TASK_APPLICATION);
        }
        else if (CrabAppStatus == CRAB_APP_PAUSE)
        {
          CrabChangeAppState(CRAB_APP_CONTINUE);
          CrabTaskResume(CRAB_TASK_APPLICATION);
        }
        else if (CrabAppStatus == CRAB_APP_ERROR)
        {
          CrabChangeAppState(CRAB_APP_STOPPING);
          CrabTaskResume(CRAB_TASK_APPLICATION);
        }
        else if (CrabAppStatus == CRAB_APP_OFF)
        {
          CrabChangeAppState(CRAB_APP_LOADROM);
          CrabTaskResume(CRAB_TASK_APPLICATION);
        }
          
      }
    }
    
    EscKey.Count = 0;
    EscKey.Down = 0;
  }
}

/*******************************************************************************
* Function    : SYSBEP_Process
* Caption     : 系统蜂鸣器处理
* Description : .
*******************************************************************************/
void SYSBEP_Process()
{
  if (SysBep.NewStatus != 0xFF)
  {
    if (SysBep.NewStatus)
    {
      CrabHW_BEEP_Enable();
      SysBep.Flash = 0;
    }
    else
    {
      CrabHW_BEEP_Disable();
    }
    
    SysBep.Tick = 1;
    SysBep.Status = SysBep.NewStatus;
    SysBep.NewStatus = 0xFF;
  }
  
  if (SysBep.Status)
  {
    if (SysBep.Width)
    {
      if (SysBep.Tick > 1)
      {
        SysBep.Tick--;
      }
      else if (SysBep.Count)
      {
        SysBep.Tick = SysBep.Width;
        SysBep.Flash = 1 - SysBep.Flash;
        
        if (SysBep.Flash)
        {
          CrabHW_BEEP_Start();
        }
        else
        {
          CrabHW_BEEP_Stop();          
          SysBep.Count --;
        }
      }
      else
      {
        CrabHW_BEEP_Stop();        
        SysBep.Status = CRAB_BEEP_STOP;
        SysBep.Tick = 0;
      }
    }
    else
    {
      if (SysBep.Count)
      {
        if (SysBep.Flash == 0)
        {
          SysBep.Tick = SysBep.Count;
          SysBep.Flash = 1;
          CrabHW_BEEP_Start();
        }
        else if (SysBep.Tick > 1)
        {
          SysBep.Tick --;
        }
        else
        {
          CrabHW_BEEP_Stop(); 
          
          SysBep.Status = CRAB_BEEP_STOP;
          SysBep.Tick = 0;
        }
      }
      else
      {
        if (SysBep.Flash == 0)
        {
          SysBep.Flash = 1;
          CrabHW_BEEP_Start();
        }
      }
    }
  }
  else
  {
    if (SysBep.Tick)
    {
      CrabHW_BEEP_Stop(); 
      SysBep.Tick = 0;
    }
  }
}

/*******************************************************************************
* Function    : CrabUpdateLEDStatus
* Caption     : 更新系统LED显示状态
*  @Param     : 1.Status - 新的状态
* Description : .
*******************************************************************************/
void CrabUpdateLEDStatus()
{
  if (CrabCmdStatus)
  {
    switch (CrabCmdStatus)
    {
      case CRAB_CMD_WORKING:
      {
        SysLed.NewStatus = CRAB_LED_RED_FLASH; 
        break;
      }
      case CRAB_CMD_SUCCESS:
      {
        SysLed.NewStatus = CRAB_LED_RED_ON; 
        break;
      }
      case CRAB_CMD_ERROR:
      {
        SysLed.NewStatus = CRAB_LED_RED_ERROR; 
        break;
      }
    }
  }
  else
  {
    switch (CrabAppStatus)
    {
      case CRAB_APP_OFF:
      case CRAB_APP_STOPPING:
      {
        SysLed.NewStatus = CRAB_LED_RED_ON; 
        break;
      }
      case CRAB_APP_LOADROM:
      case CRAB_APP_RESET:
      case CRAB_APP_STANDBY:
      case CRAB_APP_PAUSE:
      case CRAB_APP_STEP:
      {
        SysLed.NewStatus = CRAB_LED_GREEN_ON; 
        break;
      }
      case CRAB_APP_ERROR:
      {
        SysLed.NewStatus = CRAB_LED_GREEN_ERROR; 
        break;
      }
      case CRAB_APP_CONTINUE:
      case CRAB_APP_RUNNING:
      {
        SysLed.NewStatus = CRAB_LED_GREEN_FLASH; 
        break;
      }
    }
  }
  
  CrabTaskResume(CRAB_TASK_SYSTEM);
}

/*******************************************************************************
* Function    : CrabChangeBeep
* Caption     : 更改系统蜂鸣器发声内容
*  @Param     : 1.Width - 频率宽度
*  @Param     : 2.Count - 发声长度
* Description : .
*******************************************************************************/
void CrabChangeBeep(CrabShort Width, CrabByte Count)
{
  if ((Width == 0) || (Count ==0))
  {
    SysBep.Count = 0;
    SysBep.Width = 0;
    SysBep.NewStatus = CRAB_BEEP_STOP;
  }
  else
  {
    SysBep.Count = Count;
    SysBep.Width = (Width ) / CRAB_SYSTEM_TICK;
    SysBep.NewStatus = CRAB_BEEP_START;
  } 
  CrabTaskResume(CRAB_TASK_SYSTEM);
}

/*******************************************************************************
* Function    : ALARM_Process
* Caption     : 闹钟处理
* Description : .
*******************************************************************************/
void ALARM_Process()
{
  RTC_TimeTypeDef  RTC_TimeStructure;
  RTC_DateTypeDef  RTC_DateStructure; 
  
  CrabUint I;
  CrabBool Flag = CrabFalse;
  CrabDate Date = 0;
  CrabUint Year = 0;
  CrabTime Time;
    
  CrabTaskMutexEnter(CRAB_TASK_MUTEX_ALARM);
  
  for (I = 0; I < CRAB_ALARM_COUNT; I++)
  {
    if (AlarmClock[I].Active)
    {
      Flag = CrabTrue;
      break;
    }
  }
  
  if (!Flag) 
  {
    CrabTaskMutexExit(CRAB_TASK_MUTEX_ALARM);
    return;
  }
  
  
  /* Get the current Date */
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
  //printf("The current date (yyyy-mm-dd/ww) is :  %0.4d-%0.2d-%0.2d / %0.2d \n", 
  //       RTC_DateStructure.RTC_Year, 
  //       RTC_DateStructure.RTC_Month, 
  //       RTC_DateStructure.RTC_Date, 
  //       RTC_DateStructure.RTC_WeekDay);   

  /* Get the current Time and Date */
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
  //printf("The current time (hh:nn:ss) is :  %0.2d:%0.2d:%0.2d \n", 
  //       RTC_TimeStructure.RTC_Hours,
  //       RTC_TimeStructure.RTC_Minutes, 
  //       RTC_TimeStructure.RTC_Seconds);  
  
  Time = CrabTime_Encode(RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds, 0);
  Year = RTC_DateStructure.RTC_Year + 2000;
  
  for (I = 0; I < CRAB_ALARM_COUNT; I++)
  {
    Flag = CrabFalse;
    
    if (AlarmClock[I].Active)
    {
      if (AlarmClock[I].NextCheck)
      {
        AlarmClock[I].NextCheck--;
      }
      else
      {
        switch (AlarmClock[I].AlarmType)
        {
          case CRAB_ALARM_TIME:
          {
            /*CrabByte Hour;
            CrabByte Min;
            CrabByte Sec; 
            CrabUShort MSec;
            CrabTime_Decode(AlarmClock[I].Time, __ref Hour, __ref Min, __ref Sec, __ref MSec);*/
            
            if (AlarmClock[I].Time == Time)
            {
              Flag = CrabTrue;
            }

            CrabAlarmUpdateNextCheck(I, Flag);
            break;
          }
          case CRAB_ALARM_WEEK:
          {
            if ((AlarmClock[I].Date.Day == RTC_DateStructure.RTC_WeekDay) && (AlarmClock[I].Time == Time))
            {
              Flag = CrabTrue;
            }
            
            CrabAlarmUpdateNextCheck(I, Flag);
            break;
          }
          case CRAB_ALARM_DAY:
          {            
            if ((AlarmClock[I].Date.Day == RTC_DateStructure.RTC_Date) && (AlarmClock[I].Time == Time))
            {
              Flag = CrabTrue;
            }
            
            CrabAlarmUpdateNextCheck(I, Flag);
            break;
          }
          case CRAB_ALARM_DATE:
          {
            if (Date == 0)
            {
              Date = CrabDate_Encode(Year, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date);
            }
            
            if ((AlarmClock[I].Date.Date == Date) && (AlarmClock[I].Time == Time))
            {
              Flag = CrabTrue;
              
              if (AlarmClock[I].Active == CRAB_ALARM_LOOP)
              {
                CrabUint Year2;
                
                //如果当前日期是三月及以后，则查下一年的
                if (RTC_DateStructure.RTC_Month >= 3)
                {
                  Year2 = Year + 1;
                }
                else //否则查当前的
                {
                  Year2 = Year;
                }
                
                //查找是否润月
                if (CrabDate_GetMonthDay(Year2, RTC_DateStructure.RTC_Month) == 29)
                {                  
                  AlarmClock[I].Date.Date = Date + 366;
                }
                else
                {
                  AlarmClock[I].Date.Date = Date + 365;
                }
              }
            }            
            
            CrabAlarmUpdateNextCheck(I, Flag);
            break;
          }
        }
      }
      
      if (Flag)
      {
        CrabEventPush(CRAB_ALARM_EVENT | (I + 1));
      }
    }
  }
  
  CrabTaskMutexExit(CRAB_TASK_MUTEX_ALARM);
}

/*******************************************************************************
* Function    : CrabAlarmSetup
* Caption     : 更改闹钟时间设置
*  @Param     : 1.Index - 闹钟编号
*  @Param     : 2.AlarmClockInfo - 闹钟设置
* Description : .
*******************************************************************************/
void CrabAlarmSetup(CrabByte Index, PCrabAlarmClock AlarmClockInfo)
{
  if ((Index == 0) || (Index > CRAB_ALARM_COUNT)) return;
  Index--;
  
  CrabTaskMutexEnter(CRAB_TASK_MUTEX_ALARM);
  CrabMemCopy(&AlarmClock[Index], AlarmClockInfo, sizeof(TCrabAlarmClock));
  CrabTaskMutexExit(CRAB_TASK_MUTEX_ALARM);
}

/*******************************************************************************
* Function    : CrabAlarmClose
* Caption     : 关闭闹钟
*  @Param     : 1.Index - 闹钟编号
* Description : .
*******************************************************************************/
void CrabAlarmClose(CrabByte Index)
{
  if ((Index == 0) || (Index > CRAB_ALARM_COUNT)) return;
  Index--;
  
  CrabTaskMutexEnter(CRAB_TASK_MUTEX_ALARM);
  AlarmClock[Index].AlarmType = CRAB_ALARM_STOP;
  CrabTaskMutexExit(CRAB_TASK_MUTEX_ALARM);
}

/*******************************************************************************
* Function    : CrabAlarmClose
* Caption     : 关闭所有闹钟
* Description : .
*******************************************************************************/
void CrabAlarmCloseAll()
{
  CrabByte Index;

  CrabTaskMutexEnter(CRAB_TASK_MUTEX_ALARM);
  
  for (Index = 0; Index < CRAB_ALARM_COUNT; Index++)
  {  
    AlarmClock[Index].AlarmType = CRAB_ALARM_STOP;
  }
  
  CrabTaskMutexExit(CRAB_TASK_MUTEX_ALARM);
}
/*******************************************************************************
* Function    : CrabAlarmUpdateNextCheck
* Caption     : 更改闹钟时间设置
*  @Param     : 1.Index - 闹钟编号
*  @Param     : 2.Flag - 闹钟已执行标志
* Description : .
*******************************************************************************/
void CrabAlarmUpdateNextCheck(CrabByte Index, CrabBool Flag)
{
  if (AlarmClock[Index].Active == CRAB_ALARM_LOOP)
  {
    if (Flag)
    {
      AlarmClock[Index].NextCheck = CRAB_ALARM_HOUR_CHECK;
    }
    else
    {
      AlarmClock[Index].NextCheck = CRAB_ALARM_SEC_CHECK;
    }
  }
  else
  {
    if (Flag)
    {
      AlarmClock[Index].Active = CRAB_ALARM_STOP;
    }
    else
    {
      AlarmClock[Index].NextCheck = CRAB_ALARM_SEC_CHECK;
    }
  }
}

/*******************************************************************************
* Function    : CrabAlarmSecondEvent
* Caption     : 秒信号定时器事件
* Description : 
*******************************************************************************/
void CrabAlarmSecondEvent(void)
{ 
/*  
  RTC_TimeTypeDef  RTC_TimeStructure;
  CrabTime  Time;
    
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
  printf("Current Time:  %0.2d:%0.2d:%0.2d \r\n", 
         RTC_TimeStructure.RTC_Hours,
         RTC_TimeStructure.RTC_Minutes, 
         RTC_TimeStructure.RTC_Seconds);
    
  TotalCount++;
  Time = CrabTime_Encode(RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds, 0);

  if ((Time > 0) && (Time != (LastTime + 1000)))
  {
    ErrCount++;
    printf("Second Event, Total Count = %d, Error Count = %d \r\n", TotalCount, ErrCount);
  }
  else if ((RTC_TimeStructure.RTC_Minutes % 10 == 0) && (RTC_TimeStructure.RTC_Seconds == 0))
  {
    printf("Second Event, Total Count = %d, Error Count = %d \r\n", TotalCount, ErrCount);
  }
  
  LastTime = Time;  
*/
  CrabTaskMutexEnterISR(CRAB_TASK_MUTEX_EVENT);
  CrabFifo_PushEvent(CRAB_SECOND_EVENT);
  CrabTaskMutexExitISR(CRAB_TASK_MUTEX_EVENT);
}
// END OF FILE