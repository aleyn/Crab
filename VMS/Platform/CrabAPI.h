/******************** Copyright wisearm.com *********************************
* File Name         : CrabAPI.h
* Author            : Îâ´´Ã÷(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : API×¢²á
********************************************************************************/

#ifndef __CRAB_API_MANAGE__
#define __CRAB_API_MANAGE__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif
      
//×¢²á¾²Ì¬APIº¯Êý
void CrabRegisterStaticApi(); 

//×¢²áÊ±ÖÓAPIº¯Êý
void CrabRegisterClockApi(); 

//×¢²áÇá¶Ë¿ÚAPIº¯Êý
void CrabRegisterPortApi();

//×¢²á°åÔØAPIº¯Êý
void CrabRegisterFuncApi();

//×¢²áMiCO×¨ÊôAPIº¯Êý
void CrabRegisterMicoApi();

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE