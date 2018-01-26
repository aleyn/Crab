/******************** Copyright wisearm.com *********************************
* File Name         : Gap.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.1
* Create Date       : 2010-09-16
* Last Update       : 2016-01-12
* Description       : GAP firmware library.
********************************************************************************/
#ifndef _GAP_H
#define _GAP_H

#ifdef __cplusplus
 extern "C" {
#endif 

//Э�鶨���ת��
#define  GAP_PTC_BEGIN          0x1A  //Э�����ʼ��־
#define  GAP_PTC_CRC            0x1C  //Э���CRC����
#define  GAP_PTC_END            0x1D  //Э���������־
#define  GAP_PTC_RS             0x1F  //Э��������ź�
#define  GAP_PTC_ESC            0x1B  //Э���ת������
#define  GAP_ESC_BEGIN          0x11  //��0x1A תΪ 0x11
#define  GAP_ESC_CRC            0x13  //��0x1C תΪ 0x13
#define  GAP_ESC_END            0x14  //��0x1D תΪ 0x14
#define  GAP_ESC_RS             0x15  //��0x1F תΪ 0x15
#define  GAP_ESC_DOL            0x0B  //��0x1B תΪ 0x0B

//����
#define  GAP_CMD_DETECT         0xF0  //�豸�����ͼ��
#define  GAP_CMD_SETUP          0xE1  //���ò���
#define  GAP_CMD_READ           0xD2  //������(���豸������)
#define  GAP_CMD_WRITE    	    0xC3  //д����(���������豸)
#define  GAP_CMD_CONTROL        0xB4  //�˿ڿ���
#define  GAP_CMD_ECHO           0xA5  //����(�豸��������������ԭ�ⲻ���ظ�������)

//��Ӧ
#define  GAP_RPD_DETECT         0x0F  //�豸�����ͼ��
#define  GAP_RPD_SETUP          0x1E  //���ò���
#define  GAP_RPD_READ           0x2D  //������(���豸������)
#define  GAP_RPD_WRITE    	    0x3C  //д����(���������豸)
#define  GAP_RPD_CONTROL        0x4B  //�˿ڿ���
#define  GAP_RPD_ECHO           0x5A  //����(�豸��������������ԭ�ⲻ���ظ�������)

//��Ӧ״̬
#define  GAP_STS_SUCCESS        0x00  //���ճɹ�
#define  GAP_STS_FAILED         0x01  //����ʧ�ܣ�������CRC����
#define  GAP_STS_NOT_READY      0x02  //��λ��û׼����
#define  GAP_STS_INVALID_CMD    0x04  //��Ч������

//Э�����ݴ�С
#define  GAP_HEAD_SIZE          4     //Э��ͷ�̶�����
#define  GAP_DATA_SIZE          252   //��������󳤶�
#define  GAP_MAX_SIZE           256   //Э����󳤶�
#define  GAP_ENCODE_SIZE        512   //Э�黺������󳤶�
#define  GAP_MINISIZE_SETUP     4     //��������(SETUP)��С����
#define  GAP_MINISIZE_RW        8     //���ݶ�д(READ/WRITE)��С����
#define  GAP_MINISIZE_CONTROL   4     //��д�˿�(CONTROL)��С����
  
#define  GapGetSize(G)          (G.Size + GAP_HEAD_SIZE)
#define  GapGetPSize(G)         (G->Size + GAP_HEAD_SIZE)

/*******************************************************************************
** GAPЭ�����ݽṹ                                                            **
*******************************************************************************/

typedef          char  GapChar;      //�ַ���
typedef unsigned char  GapByte;      //���ֽ�
typedef unsigned short GapWord;      //˫�ֽ�
typedef unsigned int   GapUint;      //���ֽ�
typedef          int   GapInt;       //���ֽ�

#pragma pack(1)
typedef struct
{
  union
  {
    struct
    {                                        //������:
      GapByte     Command;                   //����[CMD]
      GapByte     Detail;                    //��������
    };
    struct
    {                                        //�豸��:
      GapByte     Respond;                   //�ظ�����[RPD]���뷢�������������������Ӧ
      GapByte     Status;                    //����״̬[STS]��ֻ�ڷ������á�
    };
  };

  GapWord         Size;                      //��������С 
} TGapHeader, *PGapHeader, GapHeader;

#pragma pack(1)
typedef union
{
  struct
  {
    GapByte       Major;                     //���汾
    GapByte       Minor;                     //���汾
    GapWord       Build;                     //����汾
  };
  GapByte         bVerInfo[4];               //�汾��Ϣ
  GapUint         uVerInfo;
} TGapVersion, *PGapVersion;

#pragma pack(1)
typedef struct
{
  GapByte         Index;                     //������ַ
  GapByte         Len;                       //��������
} TGapDescript, *PGapDescript;

#pragma pack(1)
typedef struct
{
  GapUint         DeviceID;                  //�豸ID
  GapUint         VenderID;                  //����ID
  TGapVersion     Hardware;                  //Ӳ���汾
  TGapVersion     Firmware;                  //�̼��汾
  TGapDescript    HWDescript;                //Ӳ��������
  TGapDescript    FWDescript;                //�̼�������
  GapChar         Descript[1];               //��������ʼλ��
} TGapDetect, *PGapDetect;

#pragma pack(1)
typedef struct
{
  GapUint         Category;                   //��������(SETUP)
  union
  {
    GapByte       bParam[1];                  //Byte�Ͳ���
    GapWord       wParam[1];                  //Word�Ͳ���
    GapUint       uParam[1];                  //Uint�Ͳ���
  };
} TGapSetup, *PGapSetup;

#pragma pack(1)
typedef struct
{
  GapUint         Count;                     //���ݳ���(READ/WRITE)
  GapUint         Address;                   //��д��ַ(READ/WRITE)
  union
  {
    GapByte       bData[1];                  //Byte������
    GapWord       wData[1];                  //Word������
    GapUint       uData[1];                  //Uint������
  };
} TGapReadWrite, *PGapReadWrite;

#pragma pack(1)
typedef struct
{
  GapUint         Port;                      //��д�˿�(CONTROL)
  union
  {
    GapByte       bValue[1];                 //Byte������
    GapWord       wValue[1];                 //Word������
    GapUint       uValue[1];                 //Uint������
  };
} TGapControl, *PGapControl;

#pragma pack(1)
typedef struct
{
  GapByte         bReply[GAP_DATA_SIZE];      //Byte������
  GapWord         wReply[1];                  //Word������
  GapUint         uReply[1];                  //Uint������
} TGapEcho, *PGapEcho;

#pragma pack(1)
typedef struct
{
  TGapHeader;
  union
  {
    TGapDetect    Detect;                    //�豸��Ϣ
    TGapSetup     Setup;                     //��������
    TGapReadWrite ReadWrite;                 //��д����
    TGapControl   Control;                   //�˿ڿ���
    TGapEcho      Echo;                      //���ݻ���  
  };
} TGapData, *PGapData;                       //Э�黺����

typedef enum GAP_Status_Enum
{
  GAP_StandBy       = 0,
  GAP_Pressing      = 1,
  GAP_InCRC         = 2,
  GAP_EndChar       = 3,
  GAP_OutBuffer     = 4,
  GAP_CrcFaild      = 5,
  GAP_Faild         = 6,
  GAP_Success       = 9
} TGapStatus;

#pragma pack(1)
typedef struct
{
  GapByte  *SourceBuffer;
  GapWord   SourceSize;

  GapWord   CRC_In;
  GapWord   CRC_Out;

  //GapByte   Status;
  GapWord   ResultSize;
  
} TGap, *PGap;
#pragma pack()

void GapInit(PGap Gap, GapByte *Buffer, GapWord Count);
void GapReset(PGap Gap);

GapByte GapCommandToRespond(GapByte Cmd);

GapByte GapEncodeChar(GapByte Data);
GapByte GapDecodeChar(GapByte Data);

GapByte GapEncodeBuffer(PGap Gap, PGapData GapData, GapWord Count);
GapByte GapDecodeBuffer(PGap Gap, PGapData GapData, GapWord Count);

GapWord GapCalcCrc(PGapData GapData, GapWord Count);
GapWord GapContinueCrc(GapByte Data, GapWord Crc);

#ifdef __cplusplus
}
#endif

#endif

/*******************************************************************************
**                                END OF FILE                                 **
*******************************************************************************/
