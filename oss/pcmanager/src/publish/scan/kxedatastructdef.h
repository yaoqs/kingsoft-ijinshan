/***********************************************************************
* @file     kxedatastructdef.h
* @author   liuguifeng <liuguifeng@kingsoft.com>
* @date     2008-6-11
* @brief    KXEngine ���������ݽṹ�����ĵ�
*           ���ĵ������˴������װ�����ṩ���������ݺ�֧�ֵ����õľ���ṹ��
************************************************************************/

#pragma once

#include "include/kxe_serialize.h"


/**
 * @addtogroup kxescan_subsystem_data_struct
 * @{
 */

/**
 * @brief ָ����Ҫɨ���Ŀ������
 */
enum EM_KXE_SCANTARGET_TYPE
{
    em_Target_None              = 0x00000000,   ///< ��ЧĿ��
    em_Target_Win32_Directory   = 0x00010003,   ///< Win32Ŀ¼,TargetNameΪ·���ַ�����TargetID��ȡֵΪ��0��������Ŀ¼��1����������Ŀ¼��		 
	em_Target_Win32_File        = 0x00010005,   ///< Win32�ļ�,��Ҫָ��TargetNameΪҪɨ���ļ���ȫ·����TargetIDΪ�ա�	
	em_Target_All_Malware       = 0x00010200,   ///< ���ж����������TargetNameΪ�գ�TargetIDΪ��
	em_Target_Malware           = 0x00010201,   ///< �����������,TargetNameΪ�գ���Ҫָ��TargetIDΪ�������ID
	em_Target_All_SysRprPoints,             	///< ����ϵͳ�޸��㣬TargetNameΪ�գ�TargetIDΪ��
	em_Target_SysRprPoints,       	            ///< ϵͳ�޸���,TargetNameΪ�գ���Ҫָ��TargetIDΪϵͳ�޸���ID
	em_Target_Computer,           	            ///< �ҵĵ��ԣ�TargetNameΪ�գ�TargetIDΪ��
	em_Target_Autoruns,           	            ///< ����������TargetNameΪ�գ�TargetIDΪ��
	em_Target_Critical_Area,       	            ///< �ؼ�����TargetNameΪ�գ�TargetIDΪ��
    em_Target_Removable,                        ///< �ƶ��洢�豸
	em_Target_Memory                            ///< �ڴ�ɨ��
};
KXE_JSON_DDX_ENUM(EM_KXE_SCANTARGET_TYPE)

/**
 * @brief ��Ҫɨ���Ŀ������
 */
typedef struct _S_KXE_SCAN_TARGET
{
    EM_KXE_SCANTARGET_TYPE		emTargetType;  ///< ��Ҫɨ�������
    std::wstring				strTargetName; ///< ��Ҫɨ�������,��emTargetType���
    DWORD				        dwTargetID;    ///< ��Ҫɨ���ID,��emTargetType���
}S_KXE_SCAN_TARGET;

/**
 * @brief ɨ���Ŀ��·��ƴ��
 * ���ظ������ѯʹ��
 */
typedef struct _S_KXE_SCAN_PATHS
{
	std::wstring strScanPaths;
} S_KXE_SCAN_PATHS;

KXE_JSON_DDX_BEGIN(S_KXE_SCAN_TARGET)
	KXE_JSON_DDX_MEMBER("TargetType", emTargetType)
	KXE_JSON_DDX_MEMBER("TargetName", strTargetName)
	KXE_JSON_DDX_MEMBER("TargetId", dwTargetID)
KXE_JSON_DDX_END()

KXE_JSON_DDX_BEGIN(S_KXE_SCAN_PATHS)
	KXE_JSON_DDX_MEMBER("ScanPaths", strScanPaths)
KXE_JSON_DDX_END()

/**
 * @brief ָ����Ҫ�����Ŀ��
 */ 
typedef struct _S_KXE_PROCESS_TARGET
{
    EM_KXE_SCANTARGET_TYPE		emTargetType;   ///< ��Ҫ�����Ŀ������
    std::wstring				strTargetName;  ///< ��Ҫ�����Ŀ������,��emTargetType���
    DWORD				        dwTargetID;     ///< ��Ҫ�����ID,��emTargetType���
    _S_KXE_PROCESS_TARGET():
    emTargetType(em_Target_None), 
    dwTargetID(0)
    {}
}S_KXE_PROCESS_TARGET;

KXE_JSON_DDX_BEGIN(S_KXE_PROCESS_TARGET)
	KXE_JSON_DDX_MEMBER("TargetType", emTargetType)
	KXE_JSON_DDX_MEMBER("TargetName", strTargetName)
	KXE_JSON_DDX_MEMBER("TargetId", dwTargetID)
KXE_JSON_DDX_END()

/**
* @brief �ļ����Ͷ���
*/
enum EM_KXE_FILE_REALTYPE
{
	em_FileType_Excutable,		///< ��ִ���ļ�
	em_FileType_OfficeDoc,		///< RTF�ļ�, ����Office�ļ�
	em_FileType_Zipped,			///< ѹ���ļ�
	em_FileType_Image,			///< ͼ���ļ�
	em_FileType_PDF,			///< PDF�ļ�
	em_FileType_Text,			///< �ı��ļ�
};

KXE_JSON_DDX_ENUM(EM_KXE_FILE_REALTYPE)

/**
 * @brief ָ��ɨ��������������
 */
typedef struct _S_KXE_FILE_ENGINE_OPTION
{
    bool    bScanArchieve;              ///< �Ƿ�ɨ��ѹ���ļ�
    bool    bBackupFile;                ///< �Ƿ����ø���,�����,ɾ��ǰ��ʱ������и���
    bool    bAutoFixFile;               ///< ���ֲ���ʱ�Ƿ��Զ�����
    bool    bDeleteOnCleanFail;         ///< true: ���ʧ�ܺ���� false: ����
	bool    bOnlyDocAndProg;            ///< �Ƿ�ֻɨ�������ĵ�
    _S_KXE_FILE_ENGINE_OPTION():
    bScanArchieve(true),
    bBackupFile(true),
    bAutoFixFile(true),
    bDeleteOnCleanFail(true),
    bOnlyDocAndProg(false)
    {}
}S_KXE_FILE_ENGINE_OPTION;

KXE_JSON_DDX_BEGIN(S_KXE_FILE_ENGINE_OPTION)
	KXE_JSON_DDX_MEMBER("ScanArchieve", bScanArchieve)
	KXE_JSON_DDX_MEMBER("BackupFile", bBackupFile)
	KXE_JSON_DDX_MEMBER("AutoFixFile", bAutoFixFile)
	KXE_JSON_DDX_MEMBER("DeleteOnCleanFail", bDeleteOnCleanFail)
	KXE_JSON_DDX_MEMBER("OnlyDocAndProg", bOnlyDocAndProg)
KXE_JSON_DDX_END()

/**
 * @brief ָ��ɨ��,��ع�������
 */
 typedef struct _S_KXE_FILE_FILTER_OPTION
{
    bool    bEnabledFilterFileSize;                  ///< �Ƿ������ļ���С����
    bool    bEnabledFileExtFilter;                   ///< �Ƿ������ļ���չ������
    bool    bEnabledFilePathFilter;                  ///< �Ƿ������ļ�·������
    bool    bEnabledAutoUploadFile;                  ///< �Ƿ��Զ��ϱ�����
    DWORD   dwFileSize;                              ///< �����ļ���С, ��KBΪ��λ
    std::vector<std::wstring> vecExtFilterList;      ///< ��չ�������б�
    std::vector<std::wstring> vecPathFilterList;     ///< �ļ�·�������б�
    _S_KXE_FILE_FILTER_OPTION():
    bEnabledFilterFileSize(false),
    bEnabledFileExtFilter(false),
    bEnabledFilePathFilter(false),
    bEnabledAutoUploadFile(true),
    dwFileSize(0)
    {}
}S_KXE_FILE_FILTER_OPTION;

KXE_JSON_DDX_BEGIN(S_KXE_FILE_FILTER_OPTION)
    KXE_JSON_DDX_MEMBER("EnabledFilterFileSize", bEnabledFilterFileSize)
    KXE_JSON_DDX_MEMBER("EnabledFilterFileExt", bEnabledFileExtFilter)
    KXE_JSON_DDX_MEMBER("EnabledFilterFilePath", bEnabledFilePathFilter)
    KXE_JSON_DDX_MEMBER("EnabledAutoUploadFile", bEnabledAutoUploadFile)
    KXE_JSON_DDX_MEMBER("FilterFileSize", dwFileSize)
    KXE_JSON_DDX_MEMBER("FilterFileExtList", vecExtFilterList)
    KXE_JSON_DDX_MEMBER("FilterFilePathList", vecPathFilterList)
KXE_JSON_DDX_END()


/**
 * @brief ScanSession��״̬
 */
enum EM_KXE_SCANSESSION_STATUS
{
    em_KXE_ScanStatus_None          = 0,    ///< ��Ч״̬
	em_KXE_ScanStatus_Ready         = 1,    ///< �������,׼������(���ݵ�״̬)
	em_KXE_ScanStatus_Running       = 2,    ///< ������������
	em_KXE_ScanStatus_Paused        = 3,    ///< ������ͣ
	em_KXE_ScanStatus_Complete      = 4,    ///< �������(�п����Ǳ���ֹ���µ����)
	em_KXE_ScanStatus_NetDetecting  = 5,    ///< �ȴ�������
};

KXE_JSON_DDX_ENUM(EM_KXE_SCANSESSION_STATUS);

/**
 * @brief �������Ͷ���
 */
enum EM_KXE_THREAT_TYPE
{
    em_ThreatType_MalwareInSystem,		///< ϵͳ�������
    em_ThreatType_FileVirus,			///< �ļ�����
    em_ThreatType_SystemRepairPoint,	///< ϵͳ�޸���
};

KXE_JSON_DDX_ENUM(EM_KXE_THREAT_TYPE)

/**
 * @brief ��ǰ����ɨ���״̬
 */
typedef struct _S_KXE_SCAN_STATUS
{
    S_KXE_SCAN_TARGET           CurrentTarget;                  ///< ��ǰ����ɨ��ؼ����򣬼�����ɨ���Ŀ�궨��
    EM_KXE_SCANSESSION_STATUS   emSessionStatus;                ///< ����״̬
    DWORD                       dwTotalQuantity;                ///< �ܵ�������
    DWORD                       dwFinishedQuantity;             ///< ��ɵ�������
    DWORD                       dwFindThread;                   ///< ������в������
    DWORD                       dwProcessSucceed;               ///< �ɹ�������в������
	std::map<EM_KXE_THREAT_TYPE, unsigned int> mapFoundThreats; ///< ���ݲ�ͬ����в����,������ص����� 
    __time64_t		            tmSessionStartTime;             ///< ɨ��������ʱ���
    __time64_t		            tmSessionCurrentTime;           ///< ɨ����ʱ
    __time64_t                  tmSessionEndTime;               ///< ɨ�������ʱ��㣨��������ɣ�Ҳ�����Ǳ��жϣ�ԭ���SessionSatus��
    HRESULT                     hErrCode;                       ///< ������
    _S_KXE_SCAN_STATUS():
    emSessionStatus(em_KXE_ScanStatus_None),
    dwTotalQuantity(0),
    dwFinishedQuantity(0),
    dwFindThread(0),
    dwProcessSucceed(0),
    tmSessionStartTime(0),
    tmSessionCurrentTime(0),
    tmSessionEndTime(0),
    hErrCode(0)
    {}
}S_KXE_SCAN_STATUS;

KXE_JSON_DDX_BEGIN(S_KXE_SCAN_STATUS)
	KXE_JSON_DDX_MEMBER("CurrentTarget", CurrentTarget)
	KXE_JSON_DDX_MEMBER("SessionStatus", emSessionStatus)
	KXE_JSON_DDX_MEMBER("TotalQuantity", dwTotalQuantity)
	KXE_JSON_DDX_MEMBER("FinishedQuantity", dwFinishedQuantity)
    KXE_JSON_DDX_MEMBER("FindThread", dwFindThread)
    KXE_JSON_DDX_MEMBER("ProcessSucced", dwProcessSucceed)
	KXE_JSON_DDX_MEMBER("FoundedThreatsQuantity", mapFoundThreats)
	KXE_JSON_DDX_MEMBER("SessionStartTime", tmSessionStartTime)
    KXE_JSON_DDX_MEMBER("SessionCurrentTime", tmSessionCurrentTime)
	KXE_JSON_DDX_MEMBER("SessionEndTime", tmSessionEndTime)
    KXE_JSON_DDX_MEMBER("ErrCode", hErrCode)
KXE_JSON_DDX_END()

/**
 * @brief ע��������
 */
typedef struct _S_KXE_REG_ITEM
{
    std::wstring strKey;             ///< ע����
    std::wstring strValue;           ///< ע���ֵ
}S_KXE_REG_ITEM;

KXE_JSON_DDX_BEGIN(S_KXE_REG_ITEM)
	KXE_JSON_DDX_MEMBER("key", strKey)
	KXE_JSON_DDX_MEMBER("value", strValue)
KXE_JSON_DDX_END()

/**
 * @brief ��������
 */
typedef struct _S_KXE_PROCESS_ITEM
{
    DWORD        dwProcessID;        ///< ���̵�ID
    std::wstring strImagePath;       ///< ����ӳ���ȫ·��
    _S_KXE_PROCESS_ITEM():dwProcessID(0){}
}S_KXE_PROCESS_ITEM;

KXE_JSON_DDX_BEGIN(S_KXE_PROCESS_ITEM)
	KXE_JSON_DDX_MEMBER("ProcessId", dwProcessID)
	KXE_JSON_DDX_MEMBER("ImagePath", strImagePath)
KXE_JSON_DDX_END()

/**
 * @brief �����Ĵ�����
 */
enum EM_KXE_THREAT_PROCESS_RESULT
{
    em_Threat_Process_No_Op                            =  0x00000001,   ///< δ����
    em_Threat_Process_Unknown_Fail                     =  0x80000001,   ///< δ֪ʧ��
 
    em_Threat_Process_Delay                            =  0x00000002,   ///< �ӳٴ���
    em_Threat_Process_Skip                             =  0x00000003,   ///< ����

    // �ļ���صĽ��
    em_Threat_Process_Clean_File_Success               =  0x00000004,   ///< ���(�޸�)�ļ��ɹ�
    em_Threat_Process_Clean_File_Fail                  =  0x80000004,   ///< ���(�޸�)�ļ�ʧ��
    em_Threat_Process_Delete_File_Success              =  0x00000005,   ///< ɾ���ļ��ɹ�
    em_Threat_Process_Delete_File_Fail                 =  0x80000005,   ///< ɾ���ļ�ʧ��

    em_Threat_Process_Reboot_Clean_File_Success        =  0x00000006,   ///< ����������ļ�(���óɹ�)
    em_Threat_Process_Reboot_Clean_File_Fail           =  0x80000006,   ///< ����������ļ�(����ʧ��)
    em_Threat_Process_Reboot_Delete_File_Success       =  0x00000007,   ///< ������ɾ���ļ�(���óɹ�)
    em_Threat_Process_Reboot_Delete_File_Fail          =  0x80000007,   ///< ������ɾ���ļ�(����ʧ��)
    em_Threat_Process_Rename_File_Success              =  0x00000008,   ///< �������ļ��ɹ�
    em_Threat_Process_Rename_File_Fail                 =  0x80000008,   ///< �������ļ�ʧ��

    em_Threat_Process_Quarantine_File_Success          =  0x00000009,   ///< �����ļ��ɹ�
    em_Threat_Process_Quarantine_File_Fail             =  0x80000009,   ///< �����ļ�ʧ��
    em_Threat_Process_Reboot_Quarantine_File_Success   =  0x0000000A,   ///< ����������ļ�(���óɹ�)
    em_Threat_Process_Reboot_Quarantine_File_Fail      =  0x8000000A,   ///< ����������ļ�(����ʧ��)

	em_Threat_Process_File_NoExist					   =  0x81000001,    ///< �ļ�������

	em_Threat_Process_File_InWPL					   =  0x00000020,    ///< �ļ��ڴ���������
	em_Threat_Process_File_Restore_Success			   =  0x00000021,    ///< ���ļ��Ѿ����ָ�

};

KXE_JSON_DDX_ENUM(EM_KXE_THREAT_PROCESS_RESULT)

/**
 * @brief �����������
 */
typedef struct _S_KXE_MALWARE_THREAT
{
	DWORD                            dwFoundThreatIndex;     ///< ��ʾ�˻����Ϸ��ֵ�һ������
	DWORD                            dwThreatID;             ///< ��IDΪ��в���ڴ��ڵ�ID
    std::vector<S_KXE_REG_ITEM>      AffectedRegList;        ///< ��Ӱ���ע�����
    std::vector<std::wstring>        FilesToBeFixed;         ///< ��Ҫ���޸����ļ�
    std::vector<std::wstring>        FilesToBeDeleted;       ///< ��Ҫ��ɾ�����ļ�
    std::vector<S_KXE_PROCESS_ITEM>  AffectedProcessList;    ///< ��Ӱ��Ľ���
    EM_KXE_THREAT_PROCESS_RESULT     eResult;                ///< ������
    HRESULT                          hErrCode;               ///< ������
}S_KXE_MALWARE_THREAT;

KXE_JSON_DDX_BEGIN(S_KXE_MALWARE_THREAT)
	KXE_JSON_DDX_MEMBER("FoundThreatIndex", dwFoundThreatIndex)
	KXE_JSON_DDX_MEMBER("ThreatId", dwThreatID)
	KXE_JSON_DDX_MEMBER("AffectedRegList", AffectedRegList)
	KXE_JSON_DDX_MEMBER("FilesToBeFixed", FilesToBeFixed)
	KXE_JSON_DDX_MEMBER("FilesToBeDeleted", FilesToBeDeleted)
	KXE_JSON_DDX_MEMBER("AffectedProcessList", AffectedProcessList)
	KXE_JSON_DDX_MEMBER("Result", eResult)
	KXE_JSON_DDX_MEMBER("ErrorCode", hErrCode)
KXE_JSON_DDX_END()


/**
* @brief   �����Ĳ�ѯ����
*/
enum EM_KXE_THREAT_CHECKING_TYPE
{
    em_KXE_ThreatCheckedByFileEngine,   ///< �ļ����汨��
    em_KXE_ThreatCheckedByCloud,        ///< �Ʋ�ɱ����
};

KXE_JSON_DDX_ENUM(EM_KXE_THREAT_CHECKING_TYPE)


/**
 * @brief   ѹ��,�ѿ��ļ����ݽṹ
 */
typedef struct _S_KXE_ARCHIVE_THREAT
{
    std::wstring                 strFileName;           ///< ѹ��,�ļ���
    std::wstring                 strFullPath;           ///< ����ȫ·��
    std::wstring                 strThreatName;         ///< ��в����
    EM_KXE_THREAT_PROCESS_RESULT eResult;               ///< ������
	DWORD						 dwThreatType;          ///< ��������
    EM_KXE_THREAT_CHECKING_TYPE  eThreatCheckingType;   ///< ��������
    _S_KXE_ARCHIVE_THREAT():
    eResult(em_Threat_Process_No_Op),
    dwThreatType(0),
    eThreatCheckingType(em_KXE_ThreatCheckedByFileEngine)
    {}
}S_KXE_ARCHIVE_THREAT;
KXE_JSON_DDX_BEGIN(S_KXE_ARCHIVE_THREAT)
    KXE_JSON_DDX_MEMBER("FileName", strFileName)
    KXE_JSON_DDX_MEMBER("FullPath", strFullPath)
    KXE_JSON_DDX_MEMBER("ThreatName", strThreatName)
    KXE_JSON_DDX_MEMBER("Result", eResult)
	KXE_JSON_DDX_MEMBER("ThreatType", dwThreatType)
    KXE_JSON_DDX_MEMBER("ThreatCheckingType", eThreatCheckingType)
KXE_JSON_DDX_END()

typedef struct _S_KXE_FILEVIRUS_THREAT
{
	DWORD                               dwFoundThreatIndex;     ///< ��ʾ�˻����Ϸ��ֵ�һ������
	DWORD                               dwThreatID;             ///< ��IDΪ��в���ڴ��ڵ�ID
	bool                                bFileInWrapper;         ///< �Ƿ���ѹ�����е��ļ�(������RTF)
	std::wstring                        strFileFullPath;        ///< �����ļ���ȫ·��
	std::wstring                        strVirusDescription;    ///< ��������
	EM_KXE_THREAT_PROCESS_RESULT        eResult;                ///< ������
	HRESULT                             hErrCode;               ///< ������
	std::vector<S_KXE_ARCHIVE_THREAT>  virtualFile;            ///< ѹ��,�ѿ��ļ��б�
	DWORD			                    dwThreatType;			///< ��������
    EM_KXE_THREAT_CHECKING_TYPE         eThreatCheckingType;    ///< ��������
    _S_KXE_FILEVIRUS_THREAT():
    dwFoundThreatIndex(-1),
    dwThreatID(0),
    bFileInWrapper(false),
    eResult(em_Threat_Process_No_Op),
    hErrCode(0),
    dwThreatType(0),
    eThreatCheckingType(em_KXE_ThreatCheckedByFileEngine)
    {}
}S_KXE_FILEVIRUS_THREAT;
KXE_JSON_DDX_BEGIN(S_KXE_FILEVIRUS_THREAT)
    KXE_JSON_DDX_MEMBER("FoundThreatIndex", dwFoundThreatIndex)
    KXE_JSON_DDX_MEMBER("ThreatId", dwThreatID)
    KXE_JSON_DDX_MEMBER("FileInWrapper", bFileInWrapper)
    KXE_JSON_DDX_MEMBER("FileFullPath", strFileFullPath)
    KXE_JSON_DDX_MEMBER("VirusDesciption", strVirusDescription)
    KXE_JSON_DDX_MEMBER("Result", eResult)
    KXE_JSON_DDX_MEMBER("ErrCode", hErrCode)
    KXE_JSON_DDX_MEMBER("VirtualFiles", virtualFile)
    KXE_JSON_DDX_MEMBER("ThreatType", dwThreatType)
    KXE_JSON_DDX_MEMBER("ThreatCheckingType", eThreatCheckingType)
KXE_JSON_DDX_END()

/**
* @brief ��в������״̬
*/
typedef struct _S_KXE_THREAT_PROCESS_RESULT
{
    DWORD   dwThreadIndex;                  ///< ��в����ID
    EM_KXE_THREAT_PROCESS_RESULT eResult;   ///< ������
    std::vector<EM_KXE_THREAT_PROCESS_RESULT>
                                 vecResult; ///< ѹ����,�ѿ��ļ�������
    _S_KXE_THREAT_PROCESS_RESULT():dwThreadIndex(-1),eResult(em_Threat_Process_No_Op){}
}S_KXE_THREAT_PROCESS_RESULT;
KXE_JSON_DDX_BEGIN(S_KXE_THREAT_PROCESS_RESULT)
    KXE_JSON_DDX_MEMBER("ThreatIndex", dwThreadIndex)
    KXE_JSON_DDX_MEMBER("Result", eResult)
    KXE_JSON_DDX_MEMBER("ResultExt", vecResult)
KXE_JSON_DDX_END()

/**
 * @brief ϵͳ�޸�����
 */
typedef struct _S_KXE_SYSREP_THREAT
{
	DWORD                            dwFoundThreatIndex;     ///< ��ʾ�˻����Ϸ��ֵ�һ������
	DWORD                            dwThreatID;             ///< ��IDΪ��в���ڴ��ڵ�ID
    _S_KXE_SYSREP_THREAT():dwFoundThreatIndex(-1), dwThreatID(0){}
}S_KXE_SYSREP_THREAT;

KXE_JSON_DDX_BEGIN(S_KXE_SYSREP_THREAT)	
	KXE_JSON_DDX_MEMBER("ThreatId", dwThreatID)	
KXE_JSON_DDX_END()

/**
 * @brief �����в��Ҫ����Ķ���
 */
enum EM_KXE_THREAT_PROCESS_REQUEST
{
    em_Process_Do,       ///< ������Щ��в
	em_Process_Ignore    ///< ������Щ��в
};

KXE_JSON_DDX_ENUM(EM_KXE_THREAT_PROCESS_REQUEST)

/**
 * @brief ��������ö��
 */
enum EM_KXE_KSEENGINE_TYPE
{
    em_EngineType_FileEngine,       ///< �ļ�����
    em_EngineType_SpywareEngine,	///< �����������
    em_EngineType_SysRepEngine      ///< ϵͳ�޸�����
};

KXE_JSON_DDX_ENUM(EM_KXE_KSEENGINE_TYPE)

/**
 * @brief ���������ö��
 */
enum EM_KXE_SIGNLIB_POLICY_TYPE
{
	em_SignPolicy_AllSign			///< ʹ�����е�KS3�⣨ȫ����ԣ�
};

KXE_JSON_DDX_ENUM(EM_KXE_SIGNLIB_POLICY_TYPE)

/**
 * @brief ����������ࣨ�����ڿ�ʼ��ɱǰָ����Ҫʹ�õĲ����⣩\n
 *        ÿ��������������ĵ�Ԫ��Ӧ
 */
enum EM_KXE_KSESIGN_TYPE
{
	//�����⣨0x00000FFF��
    em_SignType_AllVirusSign	= 0x00000000,			///< ͨ�ò�����ȫ��
	em_SignType_OnlineVirusSign	= 0x00000001,			///< ����ɱ��������ȫ��
	em_SignType_QQSign			= 0x00000002,			///< QQľ��ר�ÿ�
	//��������⣨0x000FF000��
    em_SignType_AllSpywareSign  = 0x00001000			///< ͨ�ö��������
	
};

KXE_JSON_DDX_ENUM(EM_KXE_KSESIGN_TYPE)

/**
 * @brief ����汾��Ϣ����
 */
typedef struct _S_KXE_ENGINEINFO_ITEM
{
    EM_KXE_KSEENGINE_TYPE   emEngineType;   ///< ��������
    DWORD                   dwHighVersion;  ///< ����汾��32λ
    DWORD                   dwLowVersion;   ///< ����汾��32λ
    _S_KXE_ENGINEINFO_ITEM():
    emEngineType(em_EngineType_FileEngine),
    dwHighVersion(0),
    dwLowVersion(0)
    {}
}S_KXE_ENGINEINFO_ITEM;

KXE_JSON_DDX_BEGIN(S_KXE_ENGINEINFO_ITEM)
	KXE_JSON_DDX_MEMBER("EngineType", emEngineType)
	KXE_JSON_DDX_MEMBER("HighVersion", dwHighVersion)
	KXE_JSON_DDX_MEMBER("LowVersion", dwLowVersion)
KXE_JSON_DDX_END()

/**
 * @brief ������汾��Ϣ����
 */
typedef struct _S_KXE_SIGNINFO_ITEM
{
    EM_KXE_KSESIGN_TYPE     emSignType;     ///< ����������
    DWORD                   dwHighVersion;  ///< ������汾��32λ
    DWORD                   dwLowVersion;   ///< ������汾��32λ
    _S_KXE_SIGNINFO_ITEM():emSignType(em_SignType_AllVirusSign), dwHighVersion(0), dwLowVersion(0){}
}S_KXE_SIGNINFO_ITEM;

KXE_JSON_DDX_BEGIN(S_KXE_SIGNINFO_ITEM)
	KXE_JSON_DDX_MEMBER("SignType", emSignType)
	KXE_JSON_DDX_MEMBER("HighVersion", dwHighVersion)
	KXE_JSON_DDX_MEMBER("LowVersion", dwLowVersion)
KXE_JSON_DDX_END()

/**
* @brief �ļ�������øı���¼�ID,�󶨵��¼�����ΪKXE_FILEMON_SIGN_EVENT
* @see KXE_UPDATE_SIGN_EVENT
*/
#define KXE_FILEMON_SIGN_VERSION_EVENT 1

/**
* @brief �ļ�������øı��¼�
*/

/**
* @brief ֪ͨ�ļ�������øı��¼������ݽṹ
*/
typedef struct _KXE_FILEMON_SIGN_EVENT
{
    int nNullValue;   ///< do nothing
    _KXE_FILEMON_SIGN_EVENT():nNullValue(0){}
}KXE_FILEMON_SIGN_EVENT;

KXE_JSON_DDX_BEGIN(KXE_FILEMON_SIGN_EVENT)
    KXE_JSON_DDX_MEMBER("value", nNullValue)
KXE_JSON_DDX_END()


/**
* @brief �����������
*        
*/
enum EM_KXE_NETPROXY_TYPE
{
    EM_KXE_NETPROXY_TYPE_NOPROXY = 0x00000000, ///< û�����ô���
    EM_KXE_NETPROXY_TYPE_HTTP	 = 0x00000001, ///< Http����
    EM_KXE_NETPROXY_TYPE_SOCKET5 = 0x00000002   ///< Socket5����
};

KXE_JSON_DDX_ENUM(EM_KXE_NETPROXY_TYPE)

/**
* @brief ���ô���������Ϣ
*/
typedef struct _KXE_CLOUD_PROXY_INFO
{
    EM_KXE_NETPROXY_TYPE emProxyType;
    std::wstring strProxyHost;
    DWORD dwProxyPort;
    std::wstring strProxyUsername;
    std::wstring strProxyPassword;
    _KXE_CLOUD_PROXY_INFO():dwProxyPort(80)
    {}
}KXE_CLOUD_PROXY_INFO;

KXE_JSON_DDX_BEGIN(KXE_CLOUD_PROXY_INFO)
KXE_JSON_DDX_MEMBER("ProxyType", emProxyType)
KXE_JSON_DDX_MEMBER("ProxyHost", strProxyHost)
KXE_JSON_DDX_MEMBER("ProxyPort", dwProxyPort)
KXE_JSON_DDX_MEMBER("ProxyUsername", strProxyUsername)
KXE_JSON_DDX_MEMBER("ProxyPassword", strProxyPassword)
KXE_JSON_DDX_END()

KXE_DECLARE_EVENT_ID_TYPE(
                          enum_SubSystem_Scan,
                          KXE_FILEMON_SIGN_VERSION_EVENT,
                          KXE_FILEMON_SIGN_EVENT
                          );


/**
 * @}
 */
