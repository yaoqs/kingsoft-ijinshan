/***********************************************************************
* @file   kxescanservice_def.h
* @author luopeng
* @date   2008-10-13
* @brief  
************************************************************************/

#pragma once
#include <string>
#include "include/kxe_serialize.h"
#include "kxedatastructdef.h"

/**
 * @defgroup kxescan_subsystem_data_struct KXEngine Scan SubSystem Data Struct
 * @{
 */

/**
 * @brief ɨ�������
 */
enum EM_KXE_GENERIC_SCAN_ATTRIBUTES
{
	em_Sess_Attr_None             = (ULONG)0x00000000,   ///< ����������
	em_Sess_Attr_Transaction_Log  = (ULONG)0x00000001,   ///< ����������־,�Ա�Ự�رպ���Ա��ָ�
	em_Sess_Attr_Resume_Session   = (ULONG)0x00000002,   ///< �ָ�һ��֮ǰ�����򿪵ĻỰ
	em_Sess_Attr_Low_Resource_Use = (ULONG)0x00000004   ///< ����Դռ��,�ٶȽ���
};
KXE_JSON_DDX_ENUM(EM_KXE_GENERIC_SCAN_ATTRIBUTES);



/**
* @brief ɨ�������
*/
enum EM_KXE_SCAN_DISK_STATUS
{
	em_Wait             = (ULONG)0x00000000,   ///< �ȴ�ɨ��
	em_Scanning		    = (ULONG)0x00000001,   ///< ����ɨ��
	em_Finish			= (ULONG)0x00000002,   ///< ���ɨ��
};
KXE_JSON_DDX_ENUM(EM_KXE_SCAN_DISK_STATUS);


/**
* @brief ����ɨ�跢����״̬
*/
enum EM_KXE_GENERIC_SCAN_LAUCH
{
    em_KXE_GENERIC_SCAN_NONE = 0,					 // ��ʼ��
    em_KXE_GENERIC_SCAN_MAINUI = 1,					 // 1���û������������������ɱ
    em_KXE_GENERIC_SCAN_RIGHTMENU = 2,				 // 2���û����ļ������Ҽ�ѡ���ɱ
    em_KXE_GENERIC_SCAN_SCHEME = 3,					 // 3����ʱ�鶾��
    em_KXE_GENERIC_SCAN_SCREENSAVER = 4,             // 4�������鶾��
    em_KXE_GENERIC_SCAN_EMBEDDING = 5,               // 5������������MSN��Ѹ�׵ȣ����ö��Բ�ɱ��
    em_KXE_GENERIC_SCAN_COMMANDLINE = 6,			 // 6: ʹ�������в�ɱ��2��3��4��5���������
};
KXE_JSON_DDX_ENUM(EM_KXE_GENERIC_SCAN_LAUCH);


/**
 * @brief    KSE��ɨ��Ự���ƿ�
 */
typedef struct _S_KXE_GENERICSCAN_SESSION_BLOCK
{
    UUID        name;               ///< �Ự��uuid,�ɵ��÷�ָ��.\n
                                    ///< ���ָ���� em_Sess_Attr_Resume_Session,
                                    ///< ����,֮ǰ������ͬ name ������ָ���� em_Sess_Attr_Transaction_Log, \n
                                    ///< ��ô,������ᱻ�ָ�,�Ա����ɨ�����,\n
                                    ///< ��ɨ�������,��sessionID�����Ա�����ȡ�ز�ɱ���.\n
                                    ///< ��� name Ϊȫ0,��ô�ڲ���Ϊ���������һ��uuid.\n
                                    ///< \n
                                    ///< ���ڴ������ɱ����,����ÿ������һ���µ�uuid,
                                    ///< ���ڻỰ����Ժ�,������uuid.\n

    EM_KXE_GENERIC_SCAN_ATTRIBUTES attributes; ///< �Ự����������
    DWORD						   dwTargetID; ///< ɨ��Ŀ������,���ڴ�����ͬ�������ѯͨ��
    EM_KXE_GENERIC_SCAN_LAUCH      emLauchWay;   ///< ����ɨ��ķ�ʽ
    _S_KXE_GENERICSCAN_SESSION_BLOCK():dwTargetID(0), attributes(em_Sess_Attr_None),emLauchWay(em_KXE_GENERIC_SCAN_NONE)
    {}
}S_KXE_GENERICSCAN_SESSION_BLOCK;

KXE_JSON_DDX_BEGIN(S_KXE_GENERICSCAN_SESSION_BLOCK)
	KXE_JSON_DDX_MEMBER("Name", name)
	KXE_JSON_DDX_MEMBER("Attributes", attributes)
    KXE_JSON_DDX_MEMBER("TargetID", dwTargetID)
    KXE_JSON_DDX_MEMBER("LauchWay", emLauchWay)
KXE_JSON_DDX_END()
/**
 * @brief    KSE��ɨ��Ự���
 */
typedef struct _S_KXE_GENERICSCAN_HANDLE
{
    UUID    name;                   ///< �Ự��uuid
    UUID    key;                    ///< ɨ��Ự����Կ,����ȷ�� name ����Ч��
}S_KXE_GENERICSCAN_HANDLE;

KXE_JSON_DDX_BEGIN(S_KXE_GENERICSCAN_HANDLE)
	KXE_JSON_DDX_MEMBER("name", name)
	KXE_JSON_DDX_MEMBER("key", key)
KXE_JSON_DDX_END()

/**
 * @brief SignLib�������
 */
typedef struct _S_KXE_SIGN_LIB
{
	UUID SignLibKey;                            ///< ��ѡ�������Key��������֤Ҫ���صĲ����⡣
	EM_KXE_KSESIGN_TYPE	SignLibType;            ///< �����������
	EM_KXE_SIGNLIB_POLICY_TYPE SignPolicyType;  ///< ���������
    _S_KXE_SIGN_LIB():SignLibType(em_SignType_AllVirusSign), SignPolicyType(em_SignPolicy_AllSign){}
}S_KXE_SIGN_LIB;

KXE_JSON_DDX_BEGIN(S_KXE_SIGN_LIB)
	KXE_JSON_DDX_MEMBER("SignLibKey", SignLibKey)
	KXE_JSON_DDX_MEMBER("SignLibType", SignLibType)
	KXE_JSON_DDX_MEMBER("SignPolicyType", SignPolicyType)
KXE_JSON_DDX_END()

/**
 * @brief ���ڶ�ָ����ScanHandle����MalwareThreadList����ز���
 */
typedef struct _S_KXE_QUERY_THREAT
{
	DWORD dwStartIndex;///<Ҫ��ѯ��в����ʼ����
	DWORD dwTotalCount;///<���β�ѯ��෵�ص�����
    _S_KXE_QUERY_THREAT():dwStartIndex(0), dwTotalCount(-1){}
}S_KXE_QUERY_THREAT;

KXE_JSON_DDX_BEGIN(S_KXE_QUERY_THREAT)
	KXE_JSON_DDX_MEMBER("StartIndex", dwStartIndex)
	KXE_JSON_DDX_MEMBER("TotalCount", dwTotalCount)
KXE_JSON_DDX_END()

/**
 * @brief ���ڶ�ָ����ScanHandle�����Ӧ����������
 *        ���bClearAllThreadΪTRUE, emProcessRequestΪem_Process_Ignore����ThreatIndexList��Ӧ���б��ᱻ����
 */
typedef struct _S_KXE_PROCESS_SCAN_TARGET
{
    BOOL bClearAllThread;                           ///< �Ƿ����������в
	EM_KXE_THREAT_PROCESS_REQUEST emProcessRequest; ///< Ҫ����Ĵ�����������ʽ
	std::vector<DWORD> ThreatIndexList;             ///< �ύ�����������в�������б���в�����ڲ�ѯ��вʱ��ã�
    _S_KXE_PROCESS_SCAN_TARGET():bClearAllThread(false), emProcessRequest(em_Process_Do){}
}S_KXE_PROCESS_SCAN_TARGET;

KXE_JSON_DDX_BEGIN(S_KXE_PROCESS_SCAN_TARGET)
    KXE_JSON_DDX_MEMBER("ClearAllThread", bClearAllThread)
	KXE_JSON_DDX_MEMBER("ProcessRequest", emProcessRequest)
	KXE_JSON_DDX_MEMBER("ThreatIndexList", ThreatIndexList)
KXE_JSON_DDX_END()

/**
* @brief ���ڶ�ָ����ScanHandle��ѯ�����Ӧ����������
*/
typedef struct _S_KXE_QUERY_PROCESS_TARGET
{
    EM_KXE_THREAT_TYPE emThreatType;   ///<Ҫ��ѯ����в����
    std::vector<DWORD> vecThreatList;  ///<��вID�б�
}S_KXE_QUERY_PROCESS_TARGET;

KXE_JSON_DDX_BEGIN(S_KXE_QUERY_PROCESS_TARGET)
    KXE_JSON_DDX_MEMBER("QueryProcess", emThreatType)
    KXE_JSON_DDX_MEMBER("ThreatList", vecThreatList)
KXE_JSON_DDX_END()

/**
 * @brief �ļ�����SDK����
 */
typedef struct _S_KXE_FILEVIRUS_RESULT
{
	DWORD    dwFileSize;                      ///< �˽ṹ�Ĵ�С,�����������ʱ,��Ҫ��ʼ��
	BOOL     bFoundVirus;                     ///< ��־�Ƿ��ֲ���
	BOOL     bVirusInWrapper;                 ///< ��ѹ�����ڴ��ڲ���
    DWORD    dwThreatID;                      ///< ��IDΪ��в���ڴ��ڵ�ID
    WCHAR    szVirusDescription[MAX_PATH];    ///< ��������
    EM_KXE_THREAT_PROCESS_RESULT eResult;     ///< ������
	int      nErrCode;                        ///< ���������,��0ʱ��Ҫ���
}S_KXE_FILEVIRUS_RESULT;
/**
 * @}
 */


/**
* @brief �ļ����������Ϣ����
*/
typedef struct _S_KXE_FILE_ENGINE_INFO
{
    DWORD    dwSize;                          ///< ���ṹ���С�������������ʱ����Ҫ��ʼ��
    UINT32   uBWMVersion;                     ///< �ļ�����ڰ׻������ļ��汾��YYYYMMDDBB��ʽ
    UINT32   uPolicyID;                       ///< �ļ����没��������ļ�ID
    UINT32   uSignVersion;                    ///< �ļ����没����汾�ţ�YYYYMMDDBB��ʽ
    INT32    nSignCount;                      ///< �ļ����没������������
}S_KXE_FILE_ENGINE_INFO;
/**
* @}
*/



/**
* @brief ����������Ϣ
*/
typedef struct _S_KXE_PROGRESS_OPTION
{
	DWORD dwUpdateDays;         ///< ȫ��ɨ���ļ�����ʧЧ������
	DWORD dwSampleSize;         ///< ���������Ĵ�С	
}S_KXE_PROGRESS_OPTION;
KXE_JSON_DDX_BEGIN(S_KXE_PROGRESS_OPTION)
KXE_JSON_DDX_MEMBER("UpdateDays", dwUpdateDays)
KXE_JSON_DDX_MEMBER("SampleSize", dwSampleSize)
KXE_JSON_DDX_END()
/**
* @}
*/

/**
* @brief ��ȡ������Ϣ
*/
typedef struct _S_KXE_PROGRESS_INFO
{
	DWORD dwTimeProgress;         ///< ʣ���ʱ��(ms)
	DWORD dwStreamProgress;       ///< ��ȡ�����������Ľ���  (0 - 100)      	
	DWORD dwFilesProgress;        ///< ��ȡ�����ļ����Ľ���  (0 - 100)
	DWORD dwFilesTotalCount;      ///< ��ȡɨ���ļ�������	
    _S_KXE_PROGRESS_INFO():
    dwTimeProgress(0),
    dwStreamProgress(0),
    dwFilesProgress(0),
    dwFilesTotalCount(0)
    {}
}S_KXE_PROGRESS_INFO;
KXE_JSON_DDX_BEGIN(S_KXE_PROGRESS_INFO)
KXE_JSON_DDX_MEMBER("RestTime",		dwTimeProgress)
KXE_JSON_DDX_MEMBER("DataProgress", dwStreamProgress)
KXE_JSON_DDX_MEMBER("FileProgress", dwFilesProgress)
KXE_JSON_DDX_MEMBER("TotalCount",	dwFilesTotalCount)
KXE_JSON_DDX_END()
/**
* @}
*/


/**
* @brief ����ɨ����ͳ����Ϣ
*/
typedef struct _S_KXE_DISKSCANITEM_INFO
{
	std::wstring strDriverName;			 ///< ����������
	DWORD		 dwScanItems;			 ///< �Ѿ�ɨ���������
	DWORD        dwFindThreats;          ///< ���ֵĲ�����
    int			 nStatus;				 ///< ��ʾ��ǰ��״̬  �ο�EM_KXE_SCAN_DISK_STATUS
    _S_KXE_DISKSCANITEM_INFO():
    dwScanItems(0),
    dwFindThreats(0),
    nStatus(em_Wait)
    {}
}S_KXE_DISKSCANITEM_INFO;
KXE_JSON_DDX_BEGIN(S_KXE_DISKSCANITEM_INFO)
KXE_JSON_DDX_MEMBER("DriverName",		strDriverName)
KXE_JSON_DDX_MEMBER("ScanItems",		dwScanItems)
KXE_JSON_DDX_MEMBER("FindThreats",		dwFindThreats)
KXE_JSON_DDX_MEMBER("Status",			nStatus)
KXE_JSON_DDX_END()
/**
* @}
*/


/**
* @brief ͳ�ƴ�����״̬��Ϣ
*/
typedef struct _S_KXE_PROCESS_RESULT_INFO
{
	DWORD		 dwUndisposed;			 ///< δ���������
	DWORD		 dwProcessed;			 ///< �Ѿ����������
	DWORD		 dwUnsuccessed;          ///< ����ʧ�ܵ�����
	DWORD        dwRebootClean;          ///< ��������������
	DWORD        dwRebootDelete;		 ///< �����ɾ��������
    _S_KXE_PROCESS_RESULT_INFO():
    dwUndisposed(0),
    dwProcessed(0),
    dwUnsuccessed(0),
    dwRebootClean(0),
    dwRebootDelete(0)
    {}
}S_KXE_PROCESS_RESULT_INFO;
KXE_JSON_DDX_BEGIN(S_KXE_PROCESS_RESULT_INFO)
KXE_JSON_DDX_MEMBER("Undisposed",	dwUndisposed)
KXE_JSON_DDX_MEMBER("Processed",	dwProcessed)
KXE_JSON_DDX_MEMBER("Unsuccessed",	dwUnsuccessed)
KXE_JSON_DDX_MEMBER("RebootClean",	dwRebootClean)
KXE_JSON_DDX_MEMBER("RebootDelete",	dwRebootDelete)
KXE_JSON_DDX_END()


/**
* @brief ȫ��ɨ���ʱ��״̬��Ϣ�Ĳ�ѯ
*/
typedef struct _S_KXE_FULLDISK_STATUS_INFO
{
	S_KXE_SCAN_STATUS		ScanStatus;
	S_KXE_PROGRESS_INFO		Progress;
	std::vector<S_KXE_DISKSCANITEM_INFO> DiskInfo;
}S_KXE_FULLDISK_STATUS_INFO;
KXE_JSON_DDX_BEGIN(S_KXE_FULLDISK_STATUS_INFO)
KXE_JSON_DDX_MEMBER("ScanStatus",	ScanStatus)
KXE_JSON_DDX_MEMBER("Progress",	    Progress)
KXE_JSON_DDX_MEMBER("DiskInfo",		DiskInfo)
KXE_JSON_DDX_END()

/**
* @brief �ָ��ļ���ʱ��ʹ��
*/
typedef struct _S_KXE_RESTOREFILE_LIST
{
	std::vector<unsigned int> FileIndexList;
}S_KXE_RESTOREFILE_LIST;
KXE_JSON_DDX_BEGIN(S_KXE_RESTOREFILE_LIST)
KXE_JSON_DDX_MEMBER("FileIndexList",FileIndexList)
KXE_JSON_DDX_END()