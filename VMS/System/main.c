/******************** Copyright wisearm.com *********************************
* File Name         : Main.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 主程序
********************************************************************************/
#include "CrabVMS.h"

int main(void)
{ 
  //运行虚拟机
  application_start();
  vTaskStartScheduler();
  
  return 0;
}


