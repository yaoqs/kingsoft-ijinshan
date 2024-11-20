/////////////////////////////////////////////////////////////////
//
//	Filename: 	kselitecanservice_def.h
//	Creator:	yangjun  <yangjun@kingsoft.com>
//	Date:		2010-10-18  20:05
//	Comment:	
//
///////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <string>
#include "include/kxe_serialize.h"
#include "kxedatastructdef.h"

/**
* @brief    Lite��ɨ��Ự���
*/
typedef struct _S_KSE_LITESCAN_SESSION
{
    UUID    name; ///< �Ự��uuid
    UUID    key;  ///< ɨ��Ự����Կ,����ȷ�� name ����Ч��
}S_KSE_LITESCAN_SESSION;

KXE_JSON_DDX_BEGIN(S_KSE_LITESCAN_SESSION)
    KXE_JSON_DDX_MEMBER("name", name)
    KXE_JSON_DDX_MEMBER("key", key)
KXE_JSON_DDX_END()




//////////////////////////////////////////////////////////////////////////
// KSE_LITETASK_SCAN_MASK ɨ���������

#define  KSE_LITETASK_SCAN_MASK_NOCLOUD       (ULONG)0x00000001  ///< ��ʹ���Ƽ��
#define  KSE_LITETASK_SCAN_MASK_AUTOFIX       (ULONG)0x00000002  ///< �Զ�������
#define  KSE_LITETASK_SCAN_MASK_NO_WHITECACHE (ULONG)0x00000004  ///< ��ʹ�ð���������
#define  KSE_LITETASK_SCAN_MASK_NO_USERTRUST  (ULONG)0x00000008  ///< ��ʹ���û������б�

/**
* @brief  ���Ŀ¼�ṹ
*/
typedef struct _S_KSE_LITESCAN_TARGET_INFO
{
    DWORD                     dwScanMask;   ///< ɨ���������,��KSE_LITETASK_SCAN
    std::vector<std::wstring> vecScanFiles; ///< ɨ����ļ��б�
    DWORD                     dwTimeOut;    ///< �ȴ�������ĳ�ʱֵ,0����-1Ϊ���޵ȴ�
    _S_KSE_LITESCAN_TARGET_INFO():
    dwScanMask(0),
    dwTimeOut(0)
    {}
}S_KSE_LITESCAN_TARGET_INFO;

KXE_JSON_DDX_BEGIN(S_KSE_LITESCAN_TARGET_INFO)
KXE_JSON_DDX_MEMBER("ScanMask", dwScanMask)
KXE_JSON_DDX_MEMBER("ScanFiles", vecScanFiles)
KXE_JSON_DDX_MEMBER("TimeOut", dwTimeOut)
KXE_JSON_DDX_END()


/**
* @brief �ļ���ȫ�ȼ�
*/
enum EM_KSE_SECURITY_LEVAL
{
    EM_KSE_SECURITY_LEVAL_NONE   =   (ULONG)0x00000000, ///< ���ʧ�ܣ��ް�ȫ�ȼ�
    EM_KSE_SECURITY_LEVAL_GRAY   =   (ULONG)0x00000001, ///< ���ļ�(��PE)
    EM_KSE_SECURITY_LEVAL_GRAYPE =   (ULONG)0x00000002, ///< ��PE�ļ�
    EM_KSE_SECURITY_LEVAL_SAFE   =   (ULONG)0x00000003, ///< ��ȫ
    EM_KSE_SECURITY_LEVAL_VIRUS  =   (ULONG)0x00000004  ///< ����
};
KXE_JSON_DDX_ENUM(EM_KSE_SECURITY_LEVAL);

/**
* @brief   �ļ������
*/
typedef struct _S_KSE_LITESCAN_RESULT
{
    EM_KSE_SECURITY_LEVAL emleval;            ///< ��ȫ�ȼ�
    DWORD                 dwVirusID;          ///< ����ID
    std::wstring          strFileMD5;         ///< MD5�ַ���, ���ΪL""����û��MD5��Ϣ,(��ǰ��֧��MD5��Ϣ���)
    std::wstring          strVirusName;       ///< ������, emlevalΪEM_KSE_SECURITY_LEVAL_VIRUSʱ��Ч
    HRESULT               hErrorCode;         ///< ������
    EM_KXE_THREAT_PROCESS_RESULT emProResult; ///< ������, Ҫ���Զ�����ʱ���
    _S_KSE_LITESCAN_RESULT():
    emleval(EM_KSE_SECURITY_LEVAL_NONE),
    dwVirusID(0),
    hErrorCode(0),
    emProResult(em_Threat_Process_No_Op)
    {}
}S_KSE_LITESCAN_RESULT;

KXE_JSON_DDX_BEGIN(S_KSE_LITESCAN_RESULT)
    KXE_JSON_DDX_MEMBER("Leval", emleval)
    KXE_JSON_DDX_MEMBER("FileMD5", strFileMD5)
    KXE_JSON_DDX_MEMBER("VirusID", dwVirusID)
    KXE_JSON_DDX_MEMBER("VirusName", strVirusName)
    KXE_JSON_DDX_MEMBER("ErrorCode", hErrorCode)
    KXE_JSON_DDX_MEMBER("ProResult", emProResult)
KXE_JSON_DDX_END()



//////////////////////////////////////////////////////////////////////////
// KSE_PROCESS_FILE_MASK �����ļ���������

#define  KSE_PROCESS_FILE_MASK_NO_BOOTCLEAN (ULONG)0x00000001  ///< ��ʹ��BootClean
#define  KSE_PROCESS_FILE_MASK_NO_BACKUP    (ULONG)0x00000002  ///< �������ļ�

/**
* @brief  �����ļ������ݽṹ
*/
typedef struct _S_KSE_PROCESS_FILE_INFO
{
    DWORD        dwProcessMask;   ///< �����������,��KSE_PROCESS_FILE_MASK
    std::wstring strFileName;     ///< Ҫ������ļ���
    std::wstring strVirusName;    ///< �ļ�������(�Ǳ���)
    DWORD        dwVirusID;      ///< �ļ�����ID(�Ǳ���)
    _S_KSE_PROCESS_FILE_INFO():
    dwProcessMask(0),dwVirusID(0)
    {}
}S_KSE_PROCESS_FILE_INFO;

KXE_JSON_DDX_BEGIN(S_KSE_PROCESS_FILE_INFO)
    KXE_JSON_DDX_MEMBER("ProcessMask", dwProcessMask)
    KXE_JSON_DDX_MEMBER("FileName",  strFileName)
    KXE_JSON_DDX_MEMBER("VirusName", strVirusName)
    KXE_JSON_DDX_MEMBER("VirusID",  dwVirusID)
KXE_JSON_DDX_END()


/**
* @brief  �����ļ��Ľ�����ݽṹ
*/
typedef struct _S_KSE_PROCESS_FILE_RESULT
{
    bool bNeedReBoot; 
    bool bBackUpSuccess;
}S_KSE_PROCESS_FILE_RESULT;

KXE_JSON_DDX_BEGIN(S_KSE_PROCESS_FILE_RESULT)
KXE_JSON_DDX_MEMBER("NeedReBoot",     bNeedReBoot)
KXE_JSON_DDX_MEMBER("BackUpSuccess",  bBackUpSuccess)
KXE_JSON_DDX_END()