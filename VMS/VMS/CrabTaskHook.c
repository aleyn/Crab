/******************** Copyright wisearm.com *********************************
* File Name         : CrabTaskHook.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : �������������
********************************************************************************/

#include "CrabVMS.h"
#include "FreeRTOS.h"
#include "task.h"

uint32_t   TickCount = 0;

/*******************************************************************************
* Function    : vApplicationTickHook
* Caption     : .
* Description : .
*******************************************************************************/
void vApplicationTickHook( void )
{
  TickCount++;
}

/*******************************************************************************
* Function    : vApplicationMallocFailedHook
* Caption     : .
* Description : .
*******************************************************************************/
void vApplicationMallocFailedHook( void )
{
	taskDISABLE_INTERRUPTS();
  CrabVMS_log("Task Malloc Failed");
	for( ;; );
}

/*******************************************************************************
* Function    : vApplicationIdleHook
* Caption     : .
* Description : .
*******************************************************************************/
void vApplicationIdleHook( void )
{
}

/*******************************************************************************
* Function    : vApplicationStackOverflowHook
* Caption     : .
*  @Param     : 1.pxTask - 
*  @Param     : 2.pcTaskName - 
* Description : .
*******************************************************************************/
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	taskDISABLE_INTERRUPTS();
  CrabVMS_log("Task Stack Overflow");
	for( ;; );
}
// END OF FILE