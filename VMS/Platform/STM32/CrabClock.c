/******************** Copyright wisearm.com *********************************
* File Name         : CrabClock.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 应用
********************************************************************************/
#include "CrabVMS.h"

crabapi CrabGetClock();
crabapi CrabSetClock();

crabapi CrabApiSecondEvent();         //extern void SecondEvent(boolean Status) : 'SecondEvent';
crabapi CrabApiAlarmClose();          //extern void Close() : 'AlarmClose';
crabapi CrabApiAlarmWithTime();       //extern void UpdateWithTime(time Time, boolean EveryDay) : 'AlarmWithTime';
crabapi CrabApiAlarmWithWeek();       //extern void UpdateWithWeek(int Weekday, time Time, boolean EveryWeek) : 'AlarmWithWeek';
crabapi CrabApiAlarmWithDay();        //extern void UpdateWithDay(int Day, time Time, boolean EveryMonth) : 'AlarmWithDay';
crabapi CrabApiAlarmWithDate();       //extern void UpdateWithDate(date Date, boolean EveryYear) : 'AlarmWithDate';
    
/*******************************************************************************
* Function    : CrabRegisterClockApi
* Caption     : 注册时钟API函数 
* Description : .
*******************************************************************************/
void CrabRegisterClockApi()
{
  CrabStaticPort.getClock = CrabGetClock;
  CrabStaticPort.setClock = CrabSetClock;
  
  CrabExtern_RegisterApi("SecondEvent", CrabApiSecondEvent);

  CrabExtern_RegisterApi("AlarmClose", CrabApiAlarmClose);
  CrabExtern_RegisterApi("AlarmWithTime", CrabApiAlarmWithTime);
  CrabExtern_RegisterApi("AlarmWithWeek", CrabApiAlarmWithWeek);
  CrabExtern_RegisterApi("AlarmWithDay", CrabApiAlarmWithDay);  
  CrabExtern_RegisterApi("AlarmWithDate", CrabApiAlarmWithDate);  
}

/*******************************************************************************
* Function    : CrabGetClock
* Caption     : 从时钟端口读入数据到寄存器中
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetClock()
{
  CrabUint Port = CrabExtern_GetPortAddr();
  
  RTC_TimeTypeDef  RTC_TimeStructure;
  RTC_DateTypeDef  RTC_DateStructure;  
  
  if (Port != 2)  //除了时间型，其它都读日期
  {
    /* Get the current Date */
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
    //printf("The current date (yyyy-mm-dd/ww) is :  %0.4d-%0.2d-%0.2d / %0.2d \n", 
    //       RTC_DateStructure.RTC_Year, 
    //       RTC_DateStructure.RTC_Month, 
    //       RTC_DateStructure.RTC_Date, 
    //       RTC_DateStructure.RTC_WeekDay);   
  }
  
  if (Port != 1) //除了日期型，其它都读时间
  {
    /* Get the current Time and Date */
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
    //printf("The current time (hh:nn:ss) is :  %0.2d:%0.2d:%0.2d \n", 
    //       RTC_TimeStructure.RTC_Hours,
    //       RTC_TimeStructure.RTC_Minutes, 
    //       RTC_TimeStructure.RTC_Seconds);
    
    /* Unfreeze the RTC DR Register */
    (void)RTC->DR;
  }
  
  //RTC_GetSubSecond()  这个是毫秒
  
  switch (Port)
  {
    case 1:
    {
      CrabDate Date;
      Date = CrabDate_Encode(RTC_DateStructure.RTC_Year + 2000, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date);

      CrabExtern_WriteToPortAsDate(Date);
      break;
    }
    case 2:
    {
      CrabTime Time;
      Time = CrabTime_Encode(RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds, 0);

      CrabExtern_WriteToPortAsTime(Time);
      break;
    }
    default:
    {
      CrabDatetime Value;
      Value.Date = CrabDate_Encode(RTC_DateStructure.RTC_Year + 2000, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date);
      Value.Time = CrabTime_Encode(RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds, 0);

      CrabExtern_WriteToPortAsDatetime(Value);
    }
  }  
}

/*******************************************************************************
* Function    : CrabSetClock
* Caption     : 将寄存器的数据写入到时钟端口
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabSetClock()
{
  CrabUint      Port = CrabExtern_GetPortAddr();
  
  RTC_TimeTypeDef  RTC_TimeStructure;
  RTC_DateTypeDef  RTC_DateStructure;   
  
  CrabUShort    Year;
  CrabByte      Month, Day;
  CrabByte      Hour, Min, Sec;
  CrabUShort    MSec;  
  
  if (Port != 2)  //除了时间型，其它都读日期
  {
    /* Get the current Date */
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
    //printf("The current date (yyyy-mm-dd/ww) is :  %0.4d-%0.2d-%0.2d / %0.2d \n", 
    //       RTC_DateStructure.RTC_Year, 
    //       RTC_DateStructure.RTC_Month, 
    //       RTC_DateStructure.RTC_Date, 
    //       RTC_DateStructure.RTC_WeekDay);
  }
  
  if (Port != 1) //除了日期型，其它都读时间
  {
    /* Get the current Time and Date */
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
    //printf("The current time (hh:nn:ss) is :  %0.2d:%0.2d:%0.2d \n", 
    //       RTC_TimeStructure.RTC_Hours,
    //       RTC_TimeStructure.RTC_Minutes, 
    //       RTC_TimeStructure.RTC_Seconds);
    
    /* Unfreeze the RTC DR Register */
    (void)RTC->DR;
  }
  
  switch (Port)
  {
    case 1:
    {
      CrabDate Date;
      if (!CrabExtern_ReadFromPortAsDate(Date)) return;

      CrabDate_Decode(Date, __ref Year, __ref Month, __ref Day);
      break;
    }
    case 2:
    {
      CrabTime Time;
      if (!CrabExtern_ReadFromPortAsTime(Time)) return;

      CrabTime_Decode(Time, __ref Hour, __ref Min, __ref Sec, __ref MSec);

      break;
    }
    default:
    {
      CrabDatetime Value;
      if (!CrabExtern_ReadFromPortAsDatetime(Value)) return;

      CrabDate_Decode(Value.Date, __ref Year, __ref Month, __ref Day);
      CrabTime_Decode(Value.Time, __ref Hour, __ref Min, __ref Sec, __ref MSec);
    }
  }
  
  CrabTaskMutexEnter(CRAB_TASK_MUTEX_ALARM);
  if (Port !=2 ) 
  {
    RTC_DateStructure.RTC_Year = Year % 100;
    RTC_DateStructure.RTC_Month = Month;
    RTC_DateStructure.RTC_Date = Day;
    
    /* Configure the RTC date register */
    if(RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure) == ERROR)
    {
      printf("RTC Set Date failed. !!\n");
    } 
    else
    {
      RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
    }
  }

  if (Port != 1)
  {
    RTC_TimeStructure.RTC_Hours = Hour;
    RTC_TimeStructure.RTC_Minutes = Min;
    RTC_TimeStructure.RTC_Seconds = Sec;

    /* Configure the RTC time register */
    if(RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure) == ERROR)
    {
      printf("RTC Set Time failed. !!\n");
    } 
    else
    {
      RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
    }
  }
  CrabTaskMutexExit(CRAB_TASK_MUTEX_ALARM);
}

/*******************************************************************************
* Function    : CrabApiSecondEvent
* Caption     : 
* Return      : crabapi
* Description : .
*******************************************************************************/
//extern void SecondEvent(boolean Status) : 'SecondEvent';
crabapi CrabApiSecondEvent()
{
  CrabBool          Status;
  
  do
  {
    if (!CrabExtern_PopupParamAsBool(Status)) break;

    CrabSetupSecondEvent(Status);
  } while (0);

}

/*******************************************************************************
* Function    : CrabApiAlarmClose
* Caption     : 
* Return      : crabapi
* Description : .
*******************************************************************************/
//extern void Close() : 'AlarmClose';
crabapi CrabApiAlarmClose()
{
  CrabUint    Index = 0;
  
  do
  {
    if (!CrabExtern_PopupParamAsUint(Index)) break;
    if ((Index == 0) || (Index > CRAB_ALARM_COUNT)) return;
    
    CrabAlarmClose(Index);
    
  } while (0);
  
}

/*******************************************************************************
* Function    : CrabApiAlarmWithTime
* Caption     : 
* Return      : crabapi
* Description : .
*******************************************************************************/
//extern void UpdateWithTime(time Time, boolean EveryDay) : 'AlarmWithTime';
crabapi CrabApiAlarmWithTime()
{
  CrabUint          Index = 0;
  CrabTime          Time;
  CrabBool          EveryDay;
  TCrabAlarmClock   ClockInfo;
  
  do
  {
    if (!CrabExtern_PopupParamAsUint(Index)) break;
    if (!CrabExtern_PopupParamAsTime(Time)) break;
    if (!CrabExtern_PopupParamAsBool(EveryDay)) break;
    
    if ((Index == 0) || (Index > CRAB_ALARM_COUNT)) return;
    
    ClockInfo.AlarmType = CRAB_ALARM_TIME;
    ClockInfo.Time = Time;
    ClockInfo.NextCheck = CRAB_ALARM_SEC_CHECK;
    
    if (EveryDay)
    {
      ClockInfo.Active = CRAB_ALARM_LOOP;
    }
    else
    {
      ClockInfo.Active = CRAB_ALARM_ONCE;
    }
    
    CrabAlarmSetup(Index, &ClockInfo);
  } while (0);

}

/*******************************************************************************
* Function    : CrabApiAlarmWithWeek
* Caption     : 
* Return      : crabapi
* Description : .
*******************************************************************************/
//extern void UpdateWithWeek(int Weekday, time Time, boolean EveryWeek) : 'AlarmWithWeek';
crabapi CrabApiAlarmWithWeek()
{
  CrabUint          Index = 0;
  CrabInt           Weekday;
  CrabTime          Time;
  CrabBool          EveryWeek;
  TCrabAlarmClock   ClockInfo;
  
  do
  {
    if (!CrabExtern_PopupParamAsUint(Index)) break;
    if (!CrabExtern_PopupParamAsInt(Weekday)) break;
    if (!CrabExtern_PopupParamAsTime(Time)) break;
    if (!CrabExtern_PopupParamAsBool(EveryWeek)) break;
    
    if ((Index == 0) || (Index > CRAB_ALARM_COUNT)) return;
    
    ClockInfo.AlarmType = CRAB_ALARM_WEEK;
    ClockInfo.Time = Time;
    ClockInfo.Date.Day = Weekday;
    ClockInfo.NextCheck = CRAB_ALARM_SEC_CHECK;
    
    if (EveryWeek)
    {
      ClockInfo.Active = CRAB_ALARM_LOOP;
    }
    else
    {
      ClockInfo.Active = CRAB_ALARM_ONCE;
    }
    
    CrabAlarmSetup(Index, &ClockInfo);
  } while (0);

}

/*******************************************************************************
* Function    : CrabApiAlarmWithDay
* Caption     : 
* Return      : crabapi
* Description : .
*******************************************************************************/
//extern void UpdateWithDay(int Day, time Time, boolean EveryMonth) : 'AlarmWithDay';
crabapi CrabApiAlarmWithDay()
{
  CrabUint          Index = 0;
  CrabInt           Day;
  CrabTime          Time;
  CrabBool          EveryMonth;
  TCrabAlarmClock   ClockInfo;
  
  do
  {
    if (!CrabExtern_PopupParamAsUint(Index)) break;
    if (!CrabExtern_PopupParamAsInt(Day)) break;
    if (!CrabExtern_PopupParamAsTime(Time)) break;
    if (!CrabExtern_PopupParamAsBool(EveryMonth)) break;
    
    if ((Index == 0) || (Index > CRAB_ALARM_COUNT)) return;
    
    ClockInfo.AlarmType = CRAB_ALARM_DAY;
    ClockInfo.Time = Time;
    ClockInfo.Date.Day = Day;
    ClockInfo.NextCheck = CRAB_ALARM_SEC_CHECK;
    
    if (EveryMonth)
    {
      ClockInfo.Active = CRAB_ALARM_LOOP;
    }
    else
    {
      ClockInfo.Active = CRAB_ALARM_ONCE;
    }
    
    CrabAlarmSetup(Index, &ClockInfo);
  } while (0);

}

/*******************************************************************************
* Function    : UpdateWithDate
* Caption     : 
* Return      : crabapi
* Description : .
*******************************************************************************/
//extern void UpdateWithDate(date Date, boolean EveryYear) : 'AlarmWithDate';
crabapi CrabApiAlarmWithDate()
{
  CrabUint          Index = 0;
  CrabDate          Date;
  CrabBool          EveryYear;
  TCrabAlarmClock   ClockInfo;
  
  do
  {
    if (!CrabExtern_PopupParamAsUint(Index)) break;
    if (!CrabExtern_PopupParamAsDate(Date)) break;
    if (!CrabExtern_PopupParamAsBool(EveryYear)) break;
    
    if ((Index == 0) || (Index > CRAB_ALARM_COUNT)) return;
    
    ClockInfo.AlarmType = CRAB_ALARM_TIME;
    ClockInfo.Date.Date = Date;
    ClockInfo.NextCheck = CRAB_ALARM_SEC_CHECK;
    
    if (EveryYear)
    {
      ClockInfo.Active = CRAB_ALARM_LOOP;
    }
    else
    {
      ClockInfo.Active = CRAB_ALARM_ONCE;
    }
    
    CrabAlarmSetup(Index, &ClockInfo);
  } while (0);

}
