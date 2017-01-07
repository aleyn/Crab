/******************** Copyright wisearm.com *********************************
* File Name         : CrabClock.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 应用
********************************************************************************/
#include "CrabVMS.h"

RTC_TimeTypeDef RTC_TimeStructure;
RTC_DateTypeDef RTC_DateStructure;

crabapi CrabGetClock();
crabapi CrabSetClock();

/*******************************************************************************
* Function    : CrabRegisterClockApi
* Caption     : 注册时钟API函数 
* Description : .
*******************************************************************************/
void CrabRegisterClockApi()
{
  CrabStaticPort.getClock = CrabGetClock;
  CrabStaticPort.setClock = CrabSetClock;
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
  
  switch (Port)
  {
    case 1: //YYYY 年
    case 2: //MM 月
    case 3: //DD 日
    case 4: //WEEK 周几
    case 9: //DATE 完整日期
    {
      /* Get the current Date */
      RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
      //printf("The current date (yyyy-mm-dd/ww) is :  %0.4d-%0.2d-%0.2d / %0.2d \n", 
      //       RTC_DateStructure.RTC_Year, 
      //       RTC_DateStructure.RTC_Month, 
      //       RTC_DateStructure.RTC_Date, 
      //       RTC_DateStructure.RTC_WeekDay);
      
      break;
    }
    case 5: //HH 时
    case 6: //NN 分
    case 7: //SS 秒
    case 10: //TIME 完整时间
    {
      /* Get the current Time and Date */
      RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
      //printf("The current time (hh:nn:ss) is :  %0.2d:%0.2d:%0.2d \n", 
      //       RTC_TimeStructure.RTC_Hours,
      //       RTC_TimeStructure.RTC_Minutes, 
      //       RTC_TimeStructure.RTC_Seconds);
      
      /* Unfreeze the RTC DR Register */
      (void)RTC->DR;
      
      break;
    }
    case 8: //MSEC 毫秒
    {
      break;
    }
  }
  
  switch (Port)
  {
    case 1: //YYYY 年
    {
      CrabExtern_ReturnUintValue(RTC_DateStructure.RTC_Year + 2000);
      break;
    }
    case 2: //MM 月
    {
      CrabExtern_ReturnUintValue( RTC_DateStructure.RTC_Month);
      break;
    }
    case 3: //DD 日
    {
      CrabExtern_ReturnUintValue( RTC_DateStructure.RTC_Date);
      break;
    }
    case 4: //WEEK 周几
    {
      CrabExtern_ReturnUintValue( RTC_DateStructure.RTC_WeekDay);
      break;
    }
    case 5:  //HH 时
    {
      CrabExtern_ReturnUintValue( RTC_TimeStructure.RTC_Hours);
      break;
    }
    case 6: //NN 分
    {
      CrabExtern_ReturnUintValue( RTC_TimeStructure.RTC_Minutes);
      break;
    }
    case 7: //SS 秒
    {
      CrabExtern_ReturnUintValue( RTC_TimeStructure.RTC_Seconds);
      break;
    }
    case 8: //ZZ 毫秒
    {
      CrabExtern_ReturnUintValue( RTC_GetSubSecond());
      break;
    }        
    case 9: //DATE 完整日期
    {
      CrabDate tmp = CrabDate_Encode(RTC_DateStructure.RTC_Year + 2000,
                                    RTC_DateStructure.RTC_Month,
                                    RTC_DateStructure.RTC_Date);
      CrabExtern_ReturnDateValue( tmp);
      break;
    }
    case 10: //TIME 完整时间
    {
      CrabTime tmp = CrabTime_Encode(RTC_TimeStructure.RTC_Hours, 
                                    RTC_TimeStructure.RTC_Minutes, 
                                    RTC_TimeStructure.RTC_Seconds, 
                                    RTC_GetSubSecond());
      
      CrabExtern_ReturnTimeValue(tmp);
      break;
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
  CrabUint Port = CrabExtern_GetPortAddr();
  
  switch (Port)
  {
    case 1: //YYYY 年
    case 2: //MM 月
    case 3: //DD 日
    case 4: //WEEK 周几
    case 9: //DATE 完整日期
    {
      /* Get the current Date */
      RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
      //printf("The current date (yyyy-mm-dd/ww) is :  %0.4d-%0.2d-%0.2d / %0.2d \n", 
      //       RTC_DateStructure.RTC_Year, 
      //       RTC_DateStructure.RTC_Month, 
      //       RTC_DateStructure.RTC_Date, 
      //       RTC_DateStructure.RTC_WeekDay);
      
      break;
    }
    case 5: //HH 时
    case 6: //NN 分
    case 7: //SS 秒
    case 10: //TIME 完整时间
    {
      /* Get the current Time and Date */
      RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
      //printf("The current time (hh:nn:ss) is :  %0.2d:%0.2d:%0.2d \n", 
      //       RTC_TimeStructure.RTC_Hours,
      //       RTC_TimeStructure.RTC_Minutes, 
      //       RTC_TimeStructure.RTC_Seconds);
      
      /* Unfreeze the RTC DR Register */
      (void)RTC->DR;
      
      break;
    }
  }  
  
  switch (Port)
  {
    case 1: //YYYY 年
    {
      CrabWord Year;
      
      Year = CrabExtern_GetUintParam(1);
      RTC_DateStructure.RTC_Year = Year % 100;
      break;
    }
    case 2: //MM 月
    {
      RTC_DateStructure.RTC_Month = CrabExtern_GetUintParam(1);
      break;
    }
    case 3: //DD 日
    {
      RTC_DateStructure.RTC_Date = CrabExtern_GetUintParam(1);
      break;
    }
    case 4: //WEEK 周几
    {
      RTC_DateStructure.RTC_WeekDay = CrabExtern_GetUintParam(1);
      break;
    }
    case 5:  //HH 时
    {
      RTC_TimeStructure.RTC_Hours = CrabExtern_GetUintParam(1);
      break;
    }
    case 6: //NN 分
    {
      RTC_TimeStructure.RTC_Minutes = CrabExtern_GetUintParam(1);
      break;
    }
    case 7: //SS 秒
    {
      RTC_TimeStructure.RTC_Seconds = CrabExtern_GetUintParam(1);
      break;
    }
    case 8: //ZZ 毫秒
    {
      //毫秒不能设置
      break;
    }        
    case 9: //DATE 完整日期
    {
      CrabWord Year;
      CrabByte Month, Day;
      
      CrabDate tmp = CrabExtern_GetDateParam(1);
      
      CrabDate_Decode(tmp, __ref Year, __ref Month, __ref Day);
      
      RTC_DateStructure.RTC_Year = Year % 100;
      RTC_DateStructure.RTC_Month = Month;
      RTC_DateStructure.RTC_Date = Day;
      break;
    }
    case 10: //TIME 完整时间
    {
      CrabByte Hour, Min, Sec;
      CrabWord MSec;
      
      CrabTime tmp = CrabExtern_GetTimeParam(1);
      CrabTime_Decode(tmp, __ref Hour, __ref Min, __ref Sec, __ref MSec);
      
      RTC_TimeStructure.RTC_Hours = Hour; 
      RTC_TimeStructure.RTC_Minutes = Min;
      RTC_TimeStructure.RTC_Seconds = Sec;
      
      break;
    }
  }
  
  switch (Port)
  {
    case 1: //YYYY 年
    case 2: //MM 月
    case 3: //DD 日
    case 4: //WEEK 周几
    case 9: //DATE 完整日期
    {
        /* Configure the RTC date register */
      if(RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure) == ERROR)
      {
        printf("RTC Set Date failed. !!\n");
      } 
      else
      {
        //printf("The New date (yyyy-mm-dd/ww) is :  %0.4d-%0.2d-%0.2d / %0.2d \n", 
        //     RTC_DateStructure.RTC_Year, 
        //     RTC_DateStructure.RTC_Month, 
        //     RTC_DateStructure.RTC_Date, 
        //     RTC_DateStructure.RTC_WeekDay);
        
        RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
      }
      break;
    }
    case 5: //HH 时
    case 6: //NN 分
    case 7: //SS 秒
    case 10: //TIME 完整时间
    {
      /* Configure the RTC time register */
      if(RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure) == ERROR)
      {
        printf("RTC Set Time failed. !!\n");
      } 
      else
      {
        //printf("The New time (hh:nn:ss) is :  %0.2d:%0.2d:%0.2d \n", 
        //       RTC_TimeStructure.RTC_Hours,
        //       RTC_TimeStructure.RTC_Minutes,
        //       RTC_TimeStructure.RTC_Seconds);

        RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
      }
      break;
    }

  }  
}
