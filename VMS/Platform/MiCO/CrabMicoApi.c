/******************** Copyright wisearm.com *********************************
* File Name         : CrabMicoApi.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2016-06-15
* Last Update       : 2017-01-09
* Description       : API for MICO
********************************************************************************/
#include "CrabVMS.h"
#include "CrabNet.h"
#include <time.h>
#include "mico.h"
#include "common.h"
#include "platform_peripheral.h"
#include "mico_platform.h"
#include "json_c/json.h"
#include "sntp.h"

crabapi CrabApiHelp();
crabapi CrabApiNetScan();
crabapi CrabApiNetConnect();
crabapi CrabApiNetInfo();
crabapi CrabApiNetGetDns();
crabapi CrabApiNetGetLocalIP();
crabapi CrabApiNetGetServerDatetime ();
crabapi CrabApiNetSoftAP();
crabapi CrabApiNetLinkStatus();
crabapi CrabApiNetUdpOpen();
crabapi CrabApiNetUdpClose();
crabapi CrabApiNetUdpStatus();
crabapi CrabApiNetUdpReceive();
crabapi CrabApiNetUdpSend();
crabapi CrabApiNetUdpRemoteIP();
crabapi CrabApiNetUdpRemotePort();

CrabString WIFI_SSID = null;

/*******************************************************************************
* Function    : CrabRegisterMicoApi
* Caption     : 注册MiCO专属API函数
* Description : .
*******************************************************************************/
void CrabRegisterMicoApi()
{  
  CrabExtern_RegisterApi("Help", CrabApiHelp);
  CrabExtern_RegisterApi("NetScan", CrabApiNetScan);
  CrabExtern_RegisterApi("NetConnect", CrabApiNetConnect);
  CrabExtern_RegisterApi("NetInfo", CrabApiNetInfo);
  CrabExtern_RegisterApi("NetLinkStatus", CrabApiNetLinkStatus);
  CrabExtern_RegisterApi("NetGetDns", CrabApiNetGetDns);
  CrabExtern_RegisterApi("NetLocalIP", CrabApiNetGetLocalIP);
  CrabExtern_RegisterApi("NetGetDns", CrabApiNetGetDns);
  CrabExtern_RegisterApi("NetServerDatetime", CrabApiNetGetServerDatetime);
  CrabExtern_RegisterApi("NetSoftAP", CrabApiNetSoftAP);

  CrabExtern_RegisterApi("NetUdpOpen", CrabApiNetUdpOpen);
  CrabExtern_RegisterApi("NetUdpClose", CrabApiNetUdpClose);
  CrabExtern_RegisterApi("NetUdpStatus", CrabApiNetUdpStatus);
  CrabExtern_RegisterApi("NetUdpReceive", CrabApiNetUdpReceive);
  CrabExtern_RegisterApi("NetUdpSend", CrabApiNetUdpSend);
  CrabExtern_RegisterApi("NetUdpRemoteIP", CrabApiNetUdpRemoteIP);
  CrabExtern_RegisterApi("NetUdpRemotePort", CrabApiNetUdpRemotePort);
}

/*******************************************************************************
* Function    : CrabApiHelp
* Caption     : 帮助信息
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiHelp ()
{
   CrabString *Result;
   //CrabString TmpStr;

   if (!CrabExtern_CreateArrayAsString(Result, 3)) return;

   Result[0] = CrabStringCreateFromAnsi("Hello World",0);
   Result[1] = CrabStringCreateFromAnsi("Windows",0);
   Result[2] = CrabStringCreateFromAnsi("中文测试",0);

   CrabExtern_ReturnValueAsArray(Result);
}

/*******************************************************************************
* Function    : CrabApiNetScan
* Caption     : 扫描WIFI路由器
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetScan ()
{
  CrabVMS_log("start scan mode, please wait...");
  
  mico_rtos_init_semaphore( &wait_sem, 1 );
  micoWlanStartScan( );
  //micoWlanStartScanAdv();
  mico_rtos_get_semaphore( &wait_sem, MICO_WAIT_FOREVER );
  
  if ( wait_sem != NULL )
  {
    mico_rtos_deinit_semaphore( &wait_sem );
  }
  
  //CrabExtern_ReturnValueAsArray(ApList);
}

/*******************************************************************************
* Function    : CrabApiNetConnect
* Caption     : 连接到WIFI路由器
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetConnect ()
{     
  CrabBool   Result;
  CrabString SSID, Password;

  network_InitTypeDef_adv_st  wNetConfigAdv;
  IPStatusTypedef para;
  
  //CrabVMS_log("CrabApiNetConnect Entry ===");
  if (!CrabExtern_PopupParamAsString(SSID)) return;
  if (!CrabExtern_PopupParamAsString(Password)) return;

  
  if (WIFI_SSID == null)
  {
    WIFI_SSID = CrabStringAlloc(32);
  }
  
  CrabStringClear(WIFI_SSID);
  CrabStringAppend(WIFI_SSID, SSID);
  
  /* Initialize wlan parameters */
  memset( &wNetConfigAdv, 0x0, sizeof(wNetConfigAdv) );
  
  strncpy((char*)wNetConfigAdv.ap_info.ssid, SSID->Data, SSID->Len);       /* wlan ssid string */  
  strncpy((char*)wNetConfigAdv.key, Password->Data, Password->Len);
    
  wNetConfigAdv.key_len = Password->Len;                        /* wlan key length */
  wNetConfigAdv.ap_info.security = SECURITY_TYPE_AUTO;          /* wlan security mode */
  wNetConfigAdv.ap_info.channel = 0;                            /* Select channel automatically */
  wNetConfigAdv.dhcpMode = DHCP_Client;                         /* Fetch Ip address from DHCP server */
  wNetConfigAdv.wifi_retry_interval = 100;                      /* Retry interval after a failure connection */
  
  mico_rtos_init_semaphore( &wait_sem, 1 );
  
  /* Connect Now! */
  //CrabVMS_log("connecting to %s...", wNetConfigAdv.ap_info.ssid);  
  micoWlanStartAdv(&wNetConfigAdv);
  mico_rtos_get_semaphore( &wait_sem, MICO_WAIT_FOREVER );

  if (NetState)
  {
    micoWlanGetIPStatus( &para, Station );
    //CrabVMS_log( "WI-FI connected, Local ip address: %s", para.ip );
    Result = CrabTrue;
  }
  else
  {
    //CrabVMS_log("WI-FI connect faild" );
    Result = CrabFalse;
  }
  
  if ( wait_sem != NULL )
  {
    mico_rtos_deinit_semaphore( &wait_sem );
  }
  
  CrabExtern_ReturnValueAsBool(Result);
}

/*******************************************************************************
* Function    : CrabApiNetInfo
* Caption     : 获取网络信息
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetInfo ()
{
  CrabString *Result;
  CrabBool   AddCaption;
  
  IPStatusTypedef ip_status={0}; 
  CrabInt I;

  if (!CrabExtern_PopupParamAsBool(AddCaption)) return;
  if (!CrabExtern_CreateArrayAsString(Result, 8)) return;
  
  if (WIFI_SSID == null)
  {
    if (AddCaption)
    {
      Result[0] = CrabStringCreateFromAnsi("SSID: null", 0);
    }
    else
    {
      Result[0] = CrabStringCreateFromAnsi("null", 0);
    }
  }
  else
  {
    Result[0] = CrabStringAlloc(WIFI_SSID->Size + 6);
    if (AddCaption)
    {
      CrabStringAppendAnsi(Result[0], "SSID: ", 0);
    }
    CrabStringAppend(Result[0], WIFI_SSID);
  }
  
  micoWlanGetIPStatus(&ip_status, Station);
  
  for (I=1; I<8; I++)
  {
    Result[I] = CrabStringAlloc(32);
  }
  
  if (AddCaption)
  {
    CrabStringAppendAnsi(Result[1], "IP Address: ", 0 ); 
    CrabStringAppendAnsi(Result[2], "Mask: ", 0 ); 
    CrabStringAppendAnsi(Result[3], "Gateway: ", 0 ); 
    CrabStringAppendAnsi(Result[4], "Broadcast: ", 0 ); 
    CrabStringAppendAnsi(Result[5], "DNS Server: ", 0 ); 
    CrabStringAppendAnsi(Result[6], "Mac Address: ", 0); 
    CrabStringAppendAnsi(Result[7], "DHCP: ", 0);
  }
  
  CrabStringAppendAnsi(Result[1], ip_status.ip, 0); 
  CrabStringAppendAnsi(Result[2], ip_status.mask, 0); 
  CrabStringAppendAnsi(Result[3], ip_status.gate, 0); 
  CrabStringAppendAnsi(Result[4], ip_status.broadcastip, 0); 
  CrabStringAppendAnsi(Result[5], ip_status.dns, 0); 
  CrabStringAppendAnsi(Result[6], ip_status.mac, 0); 
 
  
  
  switch (ip_status.dhcp)
  {
    case DHCP_Client:
    {
      CrabStringAppendAnsi(Result[7], "Client", 0);
      break;
    }
    case DHCP_Server:
    {
      CrabStringAppendAnsi(Result[7], "Server", 0);
      break;
    }
    default:
    {
      CrabStringAppendAnsi(Result[7], "Disable", 0);
      break;
    }
  }  
  
  CrabExtern_ReturnValueAsArray(Result);
}

/*******************************************************************************
* Function    : CrabApiNetLinkStatus
* Caption     : 获取连接状态
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetLinkStatus()
{
  CrabBool Result = CrabFalse;
  
  LinkStatusTypeDef link_status={0}; 
  
  micoWlanGetLinkStatus(&link_status); 
  
  //msleep(100); 
  
  //检查连接是否成功 
  if (link_status.is_connected == 1)
  {
    Result = CrabTrue;
  }
  
  CrabExtern_ReturnValueAsBool(Result);
}

/*******************************************************************************
* Function    : CrabApiNetGetDns
* Caption     : 获取域名DNS地址
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetGetDns ()
{
  CrabString Result = null;
  CrabString TmpStr;
  
  struct in_addr addr;

  if (!CrabExtern_PopupParamAsString(TmpStr)) return;
  
  if (!NetState)
  {
    CrabVMS_log("Please Connect to WI-FI");
    CrabExtern_ReturnValueAsString(Result);
    return;
  }
  
  if (GetHostIpByName( TmpStr->Data, &addr))
  {
    Result = CrabStringAlloc(64);
    CrabStringAssignAnsi(Result, inet_ntoa(addr));
    CrabExtern_ReturnValueAsString(Result);
  };

}

/*******************************************************************************
* Function    : CrabApiNetGetLocalIP
* Caption     : 获取本地IP地址
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetGetLocalIP ()
{
  CrabString Result = null;
  IPStatusTypedef para; 
  
  if (!NetState)
  {
    CrabVMS_log("Please Connect to WI-FI");
    CrabExtern_ReturnValueAsString(Result);
    return;
  }    
  
  Result = CrabStringAlloc(64);
  micoWlanGetIPStatus( &para, Station );
  CrabStringAssignAnsi(Result, para.ip);
  CrabExtern_ReturnValueAsString(Result);
}

/*******************************************************************************
* Function    : CrabApiNetGetServerDate
* Caption     : 获取服务器日期时间
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetGetServerDatetime ()
{
  CrabDatetime  Result;
  CrabString    Domain;
  CrabInt       DateOffset;
  CrabInt       TimeOffset;

  struct tm *      currentTime;
  ntp_timestamp_t  utc_time;
  struct in_addr addr;
  
  Result.Date = 0;
  Result.Time = 0;  
  
  if (!CrabExtern_PopupParamAsString(Domain)) return;
  if (!CrabExtern_PopupParamAsInt(DateOffset)) return;
  if (!CrabExtern_PopupParamAsInt(TimeOffset)) return;
  
  if (!NetState)
  {
    CrabVMS_log("Please Connect to WI-FI");
    CrabExtern_ReturnValueAsDatetime(Result);
    return;
  }    
  
  if (GetHostIpByName( Domain->Data, &addr ))
  {
    if (sntp_get_time(&addr, &utc_time) == kNoErr)
    {
      currentTime = localtime( (const time_t *)&utc_time);
      Result.Date = CrabDate_Encode(currentTime->tm_year + 1900, currentTime->tm_mon+1, currentTime->tm_mday + DateOffset);
      Result.Time = CrabTime_Encode(currentTime->tm_hour + TimeOffset, currentTime->tm_min,currentTime->tm_sec, 0);
    }
  }
  
  CrabExtern_ReturnValueAsDatetime(Result);
}

/*******************************************************************************
* Function    : CrabApiNetSoftAP
* Caption     : 成为WIFI接入点
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetSoftAP ()
{     
  CrabBool Result;
  CrabString SSID, Password;

  network_InitTypeDef_st wNetConfig; 
    
  if (!CrabExtern_PopupParamAsString(SSID)) return;
  if (!CrabExtern_PopupParamAsString(Password)) return;

  /* Initialize wlan parameters */
  memset( &wNetConfig, 0x0, sizeof(wNetConfig) );
  
  //strncpy((char*)wNetConfig.ap_info.ssid, SSID->Data, SSID->Len);       /* wlan ssid string */  
  //strncpy((char*)wNetConfig.key, Password->Data, Password->Len);
  
  strncpy((char*)wNetConfig.wifi_ssid, SSID->Data, SSID->Len);       /* wlan ssid string */  
  strncpy((char*)wNetConfig.wifi_key, Password->Data, Password->Len);
    
  strcpy((char*)wNetConfig.local_ip_addr, "192.168.0.1");
  strcpy((char*)wNetConfig.net_mask, "255.255.255.0");
  strcpy((char*)wNetConfig.dnsServer_ip_addr, "192.168.0.1");
  
  //wNetConfig.ap_info.security = SECURITY_TYPE_WPA2_AES;
  //wNetConfig.ap_info.channel = 0;
  //wNetConfig.key_len = Password->Len;                          /* wlan key length */    
  
  wNetConfig.wifi_mode = Soft_AP;
  wNetConfig.dhcpMode = DHCP_Server;  
  wNetConfig.wifi_retry_interval = 100;                      /* Retry interval after a failure connection */
  
  //CrabVMS_log("ssid:%s  key:%s", wNetConfig.ap_info.ssid, wNetConfig.key);
  micoWlanStart(&wNetConfig);
  
  Result = CrabTrue;
  CrabExtern_ReturnValueAsBool(Result);
}

/*******************************************************************************
* Function    : CrabApiNetUdpOpen
* Caption     : 建立UDP单播连接
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetUdpOpen()
{
  CrabBool Result = CrabFalse;
  CrabUint Port;
    
  if (!CrabExtern_PopupParamAsUint(Port)) return;
  
  if (CrabUdpUnicast_Status() == CrabFalse)
  {
    UdpUnicastPort = Port;
    
    CrabUdpUnicast_Cmd(CrabUdpUnicast_Cmd_Create);    
    Result = CrabTrue;
  }
  
  CrabExtern_ReturnValueAsBool(Result);  
}

/*******************************************************************************
* Function    : CrabApiNetUdpClose
* Caption     : 关闭UDP单播连接
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetUdpClose()
{
  CrabBool Result = CrabFalse;

  if ( CrabUdpUnicast_Status() )
  {
    UdpUnicastPort = 0;
    CrabUdpUnicast_Cmd(CrabUdpUnicast_Cmd_Free);
    
    Result = CrabTrue;
  }
  
  CrabExtern_ReturnValueAsBool(Result);
}

/*******************************************************************************
* Function    : CrabApiNetUdpStatus
* Caption     : 获取UDP单播状态
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetUdpStatus()
{
  CrabBool Result = CrabFalse;

  if ( CrabUdpUnicast_Status() )
  {
    Result = CrabTrue;
  }
  
  CrabExtern_ReturnValueAsBool(Result);
}

/*******************************************************************************
* Function    : CrabApiNetUdpReceive
* Caption     : 获取UDP单播所接收的字符串
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetUdpReceive()
{
  CrabString Result = null;

  if (( UdpRecvStr != null ) && ( CrabUdpUnicast_Status() ))
  {
    Result = CrabStringAlloc(UdpRecvStr->Size);
    CrabStringAssign(Result, UdpRecvStr);
    CrabStringClear(UdpRecvStr);
  }
  
  CrabExtern_ReturnValueAsString(Result);
}

/*******************************************************************************
* Function    : CrabApiNetUdpSend
* Caption     : 发送字符串到UDP单播
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetUdpSend()
{
  CrabBool Result = CrabFalse;
  CrabString TmpStr;

  if (( UdpSendStr != null ) && ( CrabUdpUnicast_Status() ))
  {
    if (!CrabExtern_PopupParamAsString(TmpStr)) return;
    
    if (TmpStr != null)
    {
      CrabStringAssign(UdpSendStr, TmpStr);
      //CrabUdpUnicast_Cmd(CrabUdpUnicast_Cmd_Resume);
    }
  }
  
  CrabExtern_ReturnValueAsBool(Result);
}

/*******************************************************************************
* Function    : CrabApiNetUdpRemoteIP
* Caption     : 获取UDP单播所接收的远端IP
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetUdpRemoteIP()
{
  CrabString Result = null;

  if (( UdpRemoteIP != null ) && ( CrabUdpUnicast_Status() ))
  {
    Result = CrabStringAlloc(UdpRemoteIP->Size);
    CrabStringAssign(Result, UdpRemoteIP);
  }
  
  CrabExtern_ReturnValueAsString(Result);
}

/*******************************************************************************
* Function    : CrabApiNetUdpRemotePort
* Caption     : 获取UDP单播所接收的远端Port
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetUdpRemotePort()
{
  CrabUint Result = 0;

  if ( CrabUdpUnicast_Status() )
  {
    Result = UdpRemotePort;
  }
  
  CrabExtern_ReturnValueAsUint(Result);
}

/*******************************************************************************
* Function    : CrabApiMyAPIFunc
* Caption     : API函数演示
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiMyAPIFunc ()
{
  CrabInt       Result;
  CrabInt       Param1;
  CrabInt       Param2;

  if (!CrabExtern_PopupParamAsInt(Param1)) return;
  if (!CrabExtern_PopupParamAsInt(Param2)) return;

  Result = Param1 + Param2;
  CrabExtern_ReturnValueAsInt(Result);
}