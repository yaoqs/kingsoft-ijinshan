///////////////////////////////////////////////////////////////////////////////
///		@file		kbootcare_def.h
///		@author		yxdh
///		@date		2009-4-27 10:27:58
///		@brief		
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "include/kxe_serialize.h"
#include "ksrusertrustlist.h"

//-------------------------------------------------------------------------

/**
* @brief    KSE��ɨ��Ự���
*/
typedef struct _S_SESSION_HANDLE
{
	UUID    name;                   ///< �Ự��uuid
	UUID    key;                    ///< ɨ��Ự����Կ, ����ȷ�� name ����Ч��
} S_SESSION_HANDLE;

KXE_JSON_DDX_BEGIN(S_SESSION_HANDLE)
KXE_JSON_DDX_MEMBER("name", name)
KXE_JSON_DDX_MEMBER("key", key)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief ����ɨ������
*/
typedef enum _EM_SCAN_TYPE
{
	enum_All = 0,								///< ȫ��
	enum_Hot_Point,								///< �ȵ�
	enum_Startup_Point,							///< ������
	enum_System_Abnormal_Point,					///< ϵͳ�쳣��
	enum_AV_Point,								///< AV��
    enum_System_Abnormal_Point_Browser,  		///< ϵͳ�쳣��(��������3.5�������ɨ��)
    enum_Browser_Home,                          ///< �ָ��������������ҳ����
    enum_DeskTop_Icon,                          ///< ɾ��������å����ͼ��
    enum_Ie_Link,                               ///< �޸����۸ĵ�IE��ݷ�ʽ
    enum_Sys_Icon,                              ///< �޸����۸�Ϊ��å��վ��ϵͳͼ�꣨����վ�ȣ�
    enum_Ie_Setting,                            ///< �޸�Internet���ü�IE�������޵�����
    enum_Search_engine,                         ///< �޸�Ĭ�����������쳣����
    enum_Browser_Link ,                         ///< �޸����۸ĵ������������ݷ�ʽ
    enum_Abnormal_Url ,                         ///< ɾ���ղؼеĶ����ƹ���ַ
    enum_Http_Protocol ,                        ///< �޸�HTTPЭ�鼰��ҳ�ļ�����
    enum_Other_Sys_Abnormal_Point,              ///< ����
	enum_All_With_Process_Expand_Scan,			///< ȫ�������Ұ������������Ŀ¼PEɨ�裩
	enum_Mbr_Virus_Point,						///< Mbr����
    enum_System_Abnormal_Point_Browser_Without_Startup_Point, ///< ϵͳ�쳣��(��������3.5�������ɨ��,��ɨ�������صĽű���ɨ�����ű���ɨ������)
	enum_System_Repair_Diagnosis,				///< ϵͳ�޸����
	enum_BK_TROJAN_Point,						///< ����ľ��
	enum_Danger_Plugin,							///< ������
	enum_Hosts_Abnormal,                        ///< Hosts �쳣
	enum_Ie_StartPage_Abnormal,					///< IE ��ҳ�쳣				
	enum_Memory_And_Critical_Startup_point		///< �ڴ漰�ؼ�������ɨ�裨��ʿ�����ʹ�ã�
} EM_SCAN_TYPE;

KXE_JSON_DDX_ENUM(EM_SCAN_TYPE)

//-------------------------------------------------------------------------

/**
* @brief ����ɨ���
*/
typedef enum _EM_SCAN_POINT
{
	enum_None_Point = 0x000,

	enum_Hot_Point_MS08067,						///< MS08-067 �񵴲�
	enum_Hot_Point_MS09002,						///< MS09-002 IE
	enum_Hot_Point_Bot,							///< �⼦
	enum_Hot_Point_End,							///< hot point end

	enum_Startup_Point_RegStartup,				///< ����������
	enum_Startup_Point_BrowserPlugIn,			///< ��������
	enum_Startup_Point_IEPlugIn,				///< IE��������
	enum_Startup_Point_SystemScripts,			///< ϵͳ�ű�
	enum_Startup_Point_FileExt,					///< �ļ���չ������
	enum_Startup_Point_Services,				///< ϵͳ����
	enum_Startup_Point_Drivers,					///< ��������
	enum_Startup_Point_WOW,						///< WOW�����
	enum_Startup_Point_Debug,					///< Debug�����
	enum_Startup_Point_Protocols,				///< Э��(PROTOCOLS)
	enum_Startup_Point_ActivePlugIn,			///< Active�ؼ�
	enum_Startup_Point_IFEO,					///< ӳ��ٳ�
	enum_Startup_Point_ScreenSave,				///< ��Ļ��������
	enum_Startup_Point_SPI,						///< SPI
	enum_Startup_Point_SafeBoot,				///< ��ȫģʽ������
	enum_Startup_Point_AutorunInf,				///< Autorun.inf
	enum_Startup_Point_SystemIni,				///< ϵͳini����
	enum_Startup_Point_StartupFolder,			///< �����ļ���
	enum_Startup_Point_SoftwarePulgIn,			///< ������������
	enum_Startup_Point_Process,					///< ��ǰ����
	enum_Startup_Point_RiskFolder,				///< ϵͳ����λ��
	enum_Startup_Point_Hosts,					///< hosts�ļ�
	enum_Startup_Point_TaskScheduler,			///< �ƻ�����
	enum_Startup_Point_Winlogon,				///< ��½������
	enum_Startup_Point_Rootkit,					///< Rootkit����
	enum_Startup_Point_Others,					///< ����������
	enum_Startup_Point_End,

	enum_System_Abnormal_Point_Start,			///< ϵͳ�쳣�㿪ʼ
	enum_System_Abnormal_Point_End,				///< ϵͳ�쳣�����

	enum_Diagnosising,							///< ���ڽ��а�ȫ���

} EM_SCAN_POINT;

KXE_JSON_DDX_ENUM(EM_SCAN_POINT)

//-------------------------------------------------------------------------

/**
* @brief ɨ��Ŀ��
*/
typedef struct _S_SCAN_TARGET
{
	EM_SCAN_TYPE				emTargetType;	///< ɨ�������
	EM_SCAN_POINT				emTargetPoint;	///< ɨ���
	std::wstring				strLocation;	///< λ��
	std::wstring				strFile;		///< �ļ�
} S_SCAN_TARGET;

KXE_JSON_DDX_BEGIN(S_SCAN_TARGET)
KXE_JSON_DDX_MEMBER("TargetType", emTargetType)
KXE_JSON_DDX_MEMBER("TargetPoint", emTargetPoint)
KXE_JSON_DDX_MEMBER("Location", strLocation)
KXE_JSON_DDX_MEMBER("File", strFile)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------
//��ΪEM_SESSION_STATUS�����ö�ٺ�kxedatastructdef.h�г�ͻ,���Ը�����
/**
* @brief Session��״̬
*/
#ifndef KBOOTCARE_DEF_IN_DUBA
typedef enum _EM_SESSION_STATUS
{
	em_ScanStatus_None          = 0,    ///< ��Ч״̬
	em_ScanStatus_Ready         = 1,    ///< �������,׼������(���ݵ�״̬)
	em_ScanStatus_Running       = 2,    ///< ������������
	em_ScanStatus_Complete      = 3		///< �������(�п����Ǳ���ֹ���µ����)
} EM_SESSION_STATUS;

#define KQUICK_SCAN_SCANSTATUS_NONE em_ScanStatus_None

#else
typedef enum _EM_SESSION_STATUS
{
	em_Cloud_ScanStatus_None          = 0,    ///< ��Ч״̬
	em_Cloud_ScanStatus_Ready         = 1,    ///< �������,׼������(���ݵ�״̬)
	em_Cloud_ScanStatus_Running       = 2,    ///< ������������
	em_Cloud_ScanStatus_Complete      = 3		///< �������(�п����Ǳ���ֹ���µ����)
} EM_SESSION_STATUS;

#define KQUICK_SCAN_SCANSTATUS_NONE em_Cloud_ScanStatus_None

#endif

KXE_JSON_DDX_ENUM(EM_SESSION_STATUS);

//-------------------------------------------------------------------------

/**
* @brief ���嵱ǰϵͳ״̬
*/
typedef enum _EM_SYSTEM_STATUS
{
	enum_System_Status_None	= 0,				///< ɨ����
	enum_System_Status_Fluent,					///< ����
	enum_System_Status_Good,					///< ����
	enum_System_Status_SAFE,					///< ��ȫ
	enum_System_Status_SOSO,					///< һ��
	enum_System_Status_Risk,					///< �з���
	enum_System_Status_Sick						///< ���ж�
} EM_SYSTEM_STATUS;

KXE_JSON_DDX_ENUM(EM_SYSTEM_STATUS)

//-------------------------------------------------------------------------

/**
* @brief �����Ʒ����
*/
typedef enum _EM_PRODUCT_TYPE
{
	enum_PT_UNKNOWN           = 0,
	enum_PT_ANTIVIRUS         = 1,				///< ɱ��
	enum_PT_FIREWALL          = 2,				///< ����ǽ
	enum_PT_INTERNETSECURITY  = 3				///< ��װ
} EM_PRODUCT_TYPE;

KXE_JSON_DDX_ENUM(EM_PRODUCT_TYPE)

//-------------------------------------------------------------------------

/**
* @brief ���嵱ǰϵͳ��װ��ɱ�������Ϣ
*/
typedef struct _S_AV_INFO
{
	std::wstring				strName;		///< �������
	std::wstring				strVersion;		///< �汾��Ϣ
	EM_PRODUCT_TYPE				ProductType;	///< ��Ʒ����
	BOOL						bAbnormal;		///< ״̬�Ƿ��쳣
	_S_AV_INFO():ProductType(enum_PT_UNKNOWN),
				bAbnormal(0)
	{
	}
} S_AV_INFO;

KXE_JSON_DDX_BEGIN(S_AV_INFO)
KXE_JSON_DDX_MEMBER("Name", strName)
KXE_JSON_DDX_MEMBER("Version", strVersion)
KXE_JSON_DDX_MEMBER("ProductType", ProductType)
KXE_JSON_DDX_MEMBER("IsAbnormal", bAbnormal)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief �����ȵ���
*/
typedef enum _EM_HOT_POINT_RESULT
{
	enum_HOT_POINT_NOT_EXIST	= 0,			///< ����
	enum_HOT_POINT_EXIST		= 1,			///< ������
	enum_HOT_POINT_MAYBE_EXIST	= 2				///< ����
} EM_HOT_POINT_RESULT;

KXE_JSON_DDX_ENUM(EM_HOT_POINT_RESULT)

//-------------------------------------------------------------------------

/**
* @brief �����ȵ�����
*/
typedef struct _S_HOT_POINT
{
	EM_SCAN_POINT				emHotPoint;		///< ɨ���
	EM_HOT_POINT_RESULT			emResult;		///< ���
} S_HOT_POINT;

KXE_JSON_DDX_BEGIN(S_HOT_POINT)
KXE_JSON_DDX_MEMBER("HotPoint", emHotPoint)
KXE_JSON_DDX_MEMBER("Result", emResult)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief ��ǰ����ɨ���״̬
*/
typedef struct _S_SCAN_STATUS
{
	std::vector<S_SCAN_TARGET>	CurrentTarget;                  ///< ��ǰ����ɨ���Ŀ��
	EM_SESSION_STATUS			emSessionStatus;                ///< ����״̬
	DWORD                       dwTotalQuantity;                ///< �ܵ�������
	DWORD                       dwFinishedQuantity;             ///< ��ɵ�������
	EM_SYSTEM_STATUS			emSystemStatus;					///< ��ǰϵͳ״̬
	std::map<EM_SCAN_TYPE, unsigned int> mapFoundThreats;		///< ���ݲ�ͬ��ɨ������, ������ص����� 
	std::vector<S_HOT_POINT>	HotPointList;					///< �ȵ��б�
	S_AV_INFO					AvInfo;							///< ɱ����Ϣ
	std::wstring				strVersion;						///< ��ǰ����汾��
	__time64_t		            tmSessionStartTime;             ///< ɨ��������ʱ���
	__time64_t		            tmSessionCurrentTime;           ///< ��ǰʱ���,���ڼ����Ѿ�ɨ���˶���ʱ��
	__time64_t                  tmSessionEndTime;               ///< ɨ�������ʱ��㣨��������ɣ�Ҳ�����Ǳ��жϣ�ԭ���SessionSatus��
	HRESULT                     hErrCode;                       ///< ������
	//////////////////////////////////////////////////////////////////////////
	//new data
	DWORD						dwBlackCnt;						///< ���ļ�����	
	DWORD						dwAllCnt;						///< ���ļ�����
	unsigned int				uEmergencyFlag;					///< ������־,Ŀǰ1Ϊ���ָ�Ⱦ�Ͳ���,�����û�ȫ��ɨ��
	//std::vector<std::wstring>	CurrentWhiteList;				///< ��ǰ���ļ��б�
	_S_SCAN_STATUS():	emSessionStatus(KQUICK_SCAN_SCANSTATUS_NONE),
						dwTotalQuantity(0),
						dwFinishedQuantity(0),
						emSystemStatus(enum_System_Status_None),
						tmSessionStartTime(0),
						tmSessionCurrentTime(0),
						tmSessionEndTime(0),
						hErrCode(0),
						dwBlackCnt(0),
						dwAllCnt(0),
						uEmergencyFlag(0)
	{
	}
} S_SCAN_STATUS;

KXE_JSON_DDX_BEGIN(S_SCAN_STATUS)
KXE_JSON_DDX_MEMBER("CurrentTargetList", CurrentTarget)
KXE_JSON_DDX_MEMBER("SessionStatus", emSessionStatus)
KXE_JSON_DDX_MEMBER("TotalQuantity", dwTotalQuantity)
KXE_JSON_DDX_MEMBER("FinishedQuantity", dwFinishedQuantity)
KXE_JSON_DDX_MEMBER("SystemStatus", emSystemStatus)
KXE_JSON_DDX_MEMBER("FoundedThreatsQuantity", mapFoundThreats)
KXE_JSON_DDX_MEMBER("HotPointList", HotPointList)
KXE_JSON_DDX_MEMBER("AvInfo", AvInfo)
KXE_JSON_DDX_MEMBER("Version", strVersion)
KXE_JSON_DDX_MEMBER("SessionStartTime", tmSessionStartTime)
KXE_JSON_DDX_MEMBER("SessionCurrentTime", tmSessionCurrentTime)
KXE_JSON_DDX_MEMBER("SessionEndTime", tmSessionEndTime)
KXE_JSON_DDX_MEMBER("ErrCode", hErrCode)
KXE_JSON_DDX_MEMBER("BlackCnt", dwBlackCnt)
KXE_JSON_DDX_MEMBER("AllCnt", dwAllCnt)
KXE_JSON_DDX_MEMBER("EmergencyFlag", uEmergencyFlag)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief �����ѯ����
*/

typedef enum _EM_QUERY_LEVEL
{
	enum_QUERY_LEVEL_NONE = 0,			///< all
	enum_QUERY_LEVEL_SAFE,				///< ��ȫ
	enum_QUERY_LEVEL_RISK				///< ����
} EM_QUERY_LEVEL;

KXE_JSON_DDX_ENUM(EM_QUERY_LEVEL)

//-------------------------------------------------------------------------

typedef struct _S_QUERY_SETTING
{
	DWORD			dwStartIndex;		///< Ҫ��ѯ��в����ʼ����
	DWORD			dwTotalCount;		///< ���β�ѯ��෵�ص�����
	EM_SCAN_POINT	ScanPoint;			///< ɨ���
	EM_QUERY_LEVEL	emLevel;			///< ����
} S_QUERY_SETTING;

KXE_JSON_DDX_BEGIN(S_QUERY_SETTING)
KXE_JSON_DDX_MEMBER("StartIndex", dwStartIndex)
KXE_JSON_DDX_MEMBER("TotalCount", dwTotalCount)
KXE_JSON_DDX_MEMBER("ScanPoint", ScanPoint)
KXE_JSON_DDX_MEMBER("Level", emLevel)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief ����ɨ�����ĿΣ�ռ���
*/
typedef enum _EM_POINT_LEVEL
{
	enum_POINT_LEVEL_VIRUS				= 1001,	///< ��������		Σ��
	enum_POINT_LEVEL_TROJAN				= 1002,	///< ľ�����		Σ��
	enum_POINT_LEVEL_BACKDOOR			= 1003,	///< ���ų���		Σ��
	enum_POINT_LEVEL_WORM				= 1004,	///< ������		Σ��
	enum_POINT_LEVEL_RISK				= 1005,	///< ���ճ���		Σ��
	enum_POINT_LEVEL_ROOTKIT			= 1006,	///< rootkit����	����
	enum_POINT_LEVEL_UNKNOWN			= 0,	///< δ֪			pe����
	enum_POINT_LEVEL_DOUBT				= 1,	///< ���ɵ�(��)		��pe����
	enum_POINT_LEVEL_SAFE				= 2,	///< ��ȫ(��)		ȫ����
	enum_POINT_LEVEL_DANGER				= 3,	///< Σ��(��)		��
	enum_POINT_LEVEL_NORMAL				= 4,	///< һ��(��PE)		��(���²����׳�)
	enum_POINT_LEVEL_ABNORMAL			= 5,	///< �쳣			��(�������ã�ע���)
	enum_POINT_LEVEL_SYS_FILE_ABNORMAL	= 6,	///< ϵͳ�ļ��쳣	�ڲ���ϵͳ�ļ�
	enum_POINT_LEVEL_NET_DETECT_FAILED	= 7,	///< ��������ʧ��	
	enum_POINT_LEVEL_REG_REMAIN        	= 8		///< ���������		
} EM_POINT_LEVEL;

KXE_JSON_DDX_ENUM(EM_POINT_LEVEL)

//-------------------------------------------------------------------------

/**
* @brief ����ɨ�����Ŀ��������
*/
typedef enum _S_POINT_PROCESS_TYPE
{
	enum_PROCESS_TYPE_CLEAN				= 0,	///< ���
	enum_PROCESS_TYPE_FIX,						///< �޸�
	enum_PROCESS_TYPE_KEEP,						///< ����
	enum_PROCESS_TYPE_DISABLE,					///< ����
	enum_PROCESS_TYPE_UPLOAD					///< �ϴ�
} S_POINT_PROCESS_TYPE;

KXE_JSON_DDX_ENUM(S_POINT_PROCESS_TYPE)

//-------------------------------------------------------------------------

/**
* @brief ������������Ŀ��Ϣ
*/
typedef struct _S_STARTUP_POINT
{
	EM_SCAN_POINT				emType;			///< ɨ���
	DWORD						dwID;			///< ����
	std::wstring				strItemName;	///< ����
	std::wstring				strLocation;	///< λ��(ע���)
	EM_POINT_LEVEL				emLevel;		///< Σ�ռ���
	std::wstring				strFile;		///< �ļ�·��
	std::wstring				strRegValue;	///< ע����ֵ
	S_POINT_PROCESS_TYPE		emStatus;		///< ״̬
	std::wstring				strCmd;			///< ������
} S_STARTUP_POINT;

KXE_JSON_DDX_BEGIN(S_STARTUP_POINT)
KXE_JSON_DDX_MEMBER("Type", emType)
KXE_JSON_DDX_MEMBER("ID", dwID)
KXE_JSON_DDX_MEMBER("Name", strItemName)
KXE_JSON_DDX_MEMBER("Location", strLocation)
KXE_JSON_DDX_MEMBER("Level", emLevel)
KXE_JSON_DDX_MEMBER("File", strFile)
KXE_JSON_DDX_MEMBER("RegValue", strRegValue)
KXE_JSON_DDX_MEMBER("Status", emStatus)
KXE_JSON_DDX_MEMBER("Cmd", strCmd)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief ����ϵͳ�쳣����Ŀ��Ϣ
*/
typedef struct _S_SYSTEM_ABNORMAL_ITEM
{
	DWORD					dwID;				///< �ӽű�����
	std::wstring			strName;			///< �ӽű�����
	std::wstring			strDescript;		///< �ӽű�����
	std::wstring			strAbnormalList;	///< ɨ�赽������ Url ���ļ�·��
    std::wstring			strScriptUuid;	    ///< �ű� uuid

} S_SYSTEM_ABNORMAL_ITEM;

KXE_JSON_DDX_BEGIN(S_SYSTEM_ABNORMAL_ITEM)
KXE_JSON_DDX_MEMBER("ID", dwID)
KXE_JSON_DDX_MEMBER("Name", strName)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

typedef struct _S_SYSTEM_ABNORMAL
{
	std::vector<S_SYSTEM_ABNORMAL_ITEM>	ItemList;	///< �����б�
	DWORD								dwID;		///< ����
	std::wstring						strName;	///< ����
	EM_POINT_LEVEL						emLevel;	///< Σ�ռ���
	S_POINT_PROCESS_TYPE				emAdvice;	///< �������
} S_SYSTEM_ABNORMAL;

KXE_JSON_DDX_BEGIN(S_SYSTEM_ABNORMAL)
KXE_JSON_DDX_MEMBER("ItemList", ItemList)
KXE_JSON_DDX_MEMBER("ID", dwID)
KXE_JSON_DDX_MEMBER("Name", strName)
KXE_JSON_DDX_MEMBER("Level", emLevel)
KXE_JSON_DDX_MEMBER("Status", emAdvice)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

typedef struct _S_MALICIOUS_ITEM
{
	std::wstring				strType;	///< ���ͣ�Url / �ļ�·�� / ...��
	unsigned int				uCount;		///< �����͵�ֵ����Ŀ
	std::vector<std::wstring>	vecValue;	///< ֵ�б�

	_S_MALICIOUS_ITEM() : uCount(0)
	{

	}
} S_MALICIOUS_ITEM;

KXE_JSON_DDX_BEGIN(S_MALICIOUS_ITEM)
KXE_JSON_DDX_MEMBER("InfoType", strType)
KXE_JSON_DDX_MEMBER("InfoCount", uCount)
KXE_JSON_DDX_MEMBER("InfoList", vecValue)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

typedef struct _MALICIOUS_INFO
{
	unsigned int					uItemCount;		///< ������Ŀ
	std::vector<S_MALICIOUS_ITEM>	vecItem;		///< ���͵�ֵ�б�

	_MALICIOUS_INFO() : uItemCount(0)
	{

	}
} MALICIOUS_INFO;

KXE_JSON_DDX_BEGIN(MALICIOUS_INFO)
KXE_JSON_DDX_MEMBER("ItemCount", uItemCount)
KXE_JSON_DDX_MEMBER("ItemList", vecItem)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief ����ɨ�����������
*/
typedef enum _EM_SCAN_ENGINE_TYPE
{
	enum_SCAN_ENGINE_INVALID_TYPE,         ///< ��Ч����
	enum_SCAN_ENGINE_FILEENGINE_TYPE,      ///< �ļ�����
	enum_SCAN_ENGINE_KCLOUD_TYPE,          ///< ��ɽ������
	enum_SCAN_ENGINE_BEIKE_TYPE,           ///< ��ʿ������
	enum_SCAN_ENGINE_SYSTEM_TYPE,           ///< ϵͳ�޸�����
	enum_SCAN_ENGINE_KSAFE_PLUG_TYPE      ///< ��ʿ�������
} EM_SCAN_ENGINE_TYPE;

KXE_JSON_DDX_ENUM(EM_SCAN_ENGINE_TYPE)

//-------------------------------------------------------------------------

/**
* @brief ������Ҫ�޸���Σ������Ϣ
*/
typedef struct _S_FIX_ITEM
{
	EM_SCAN_TYPE				emType;			///< ����
	DWORD						dwID;			///< ����
	std::wstring				strItemName;	///< ����
	EM_POINT_LEVEL				emLevel;		///< Σ�ռ���
	S_POINT_PROCESS_TYPE		Advice;			///< �������
	S_POINT_PROCESS_TYPE		ActionType;		///< �������

	_S_FIX_ITEM():
	emType(enum_All),
		dwID(0),
		emLevel(enum_POINT_LEVEL_UNKNOWN),
		Advice(enum_PROCESS_TYPE_CLEAN),
		ActionType(enum_PROCESS_TYPE_CLEAN)
	{
	}
} S_FIX_ITEM;

KXE_JSON_DDX_BEGIN(S_FIX_ITEM)
KXE_JSON_DDX_MEMBER("Type", emType)
KXE_JSON_DDX_MEMBER("ID", dwID)
KXE_JSON_DDX_MEMBER("Name", strItemName)
KXE_JSON_DDX_MEMBER("Level", emLevel)
KXE_JSON_DDX_MEMBER("Advice", Advice)
KXE_JSON_DDX_MEMBER("ActionType", ActionType)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief ������ʷ��Ϣ
*/
typedef struct _S_HISTORY_ITEM
{
	__time64_t		            tmHistoryTime;  ///< ʱ���
	std::vector<S_FIX_ITEM>		FixedList;		///< �������
} S_HISTORY_ITEM;

KXE_JSON_DDX_BEGIN(S_HISTORY_ITEM)
KXE_JSON_DDX_MEMBER("HistoryTime", tmHistoryTime)
KXE_JSON_DDX_MEMBER("FixedList", FixedList)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief ������չ��ʷ��Ϣ��������ĳ�δ����״̬�����޸�/�ѻ�ԭ��
*/
typedef enum _EM_HISTORY_ITEM_STATE
{
	enum_HISTORY_ITEM_STATE_INVALID				= 0,
	enum_HISTORY_ITEM_STATE_FIXED				= 1,		///< ���޸�
	enum_HISTORY_ITEM_STATE_RESTORED			= 2,		///< �ѱ��û���ԭ
	enum_HISTORY_ITEM_STATE_CANNOT_BE_RESTORED	= 3			///< �޷���ԭ�����޸�ʱû�б��ݵ��£�
} EM_HISTORY_ITEM_STATE;

KXE_JSON_DDX_ENUM(EM_HISTORY_ITEM_STATE)

//-------------------------------------------------------------------------

/*
* @brief	�������Ĵ�������
* @remark	������������ [IDispatch.h][_PROCESS_AT] ����һ�� ������
*/
typedef enum _EM_OBJECT_PROCESS_TYPE
{
	enum_PROCESS_AT_UNDEFINED								= -1,	// �Ƿ�����

	enum_PROCESS_AT_BOOT_DELETE_FILE						= 0,	// ɾ���ļ�

	enum_PROCESS_AT_BOOT_CLEAN_REG_KEY						= 1,
	enum_PROCESS_AT_BOOT_CLEAN_REG_VALUE					= 2,

	enum_PROCESS_AT_BOOT_REPLACE_REG_SZ_VALUE				= 3,
	enum_enum_PROCESS_AT_BOOT_REPLACE_REG_MULTI_SZ_VALUE	= 4,
	enum_PROCESS_AT_BOOT_REPLACE_REG_VALUE_OTHER_TYPE		= 5,
	enum_PROCESS_AT_BOOT_CLEAN_INFECTED_FILE				= 6,	// �޸�����Ⱦ�ļ�
	enum_PROCESS_AT_JUST_RECORED							= 7		// ����¼��Ϣ��������������Ŀǰ��¼���Ǳ����õ��������������Ļ��ļ���
} EM_OBJECT_PROCESS_TYPE;

KXE_JSON_DDX_ENUM(EM_OBJECT_PROCESS_TYPE)

//-------------------------------------------------------------------------

/*
* @brief	������ʷ���������⴫����Ϣ������չʾ��
* @remark	
*/
typedef struct _S_PROCESS_OBJECT_INFO
{
	DWORD					dwIndex;		///< �����ţ��� 0 ��ʼ
	EM_OBJECT_PROCESS_TYPE	processType;	///< ��������
	std::wstring			strInfo_1;		///< processType ��ͬ�����ֶδ������岻ͬ
											///< -----------------------------------------------------
											///<	processType		|		����
											///< -----------------------------------------------------
											///<		0			|	�ļ�·��	
											///<		1			|	ע������·��( key path )
											///<		2			|	ͬ��
											///<		3			|	ͬ��
											///<		4			|	ͬ��
											///<		5			|	δ����
											///<		6			|	�ļ�·��
											///<		7			|	�ļ�·��
	std::wstring			strInfo_2;		///< processType ��ͬ�����ֶδ������岻ͬ
											///< -----------------------------------------------------
											///<	processType		|		����
											///< -----------------------------------------------------
											///<		0			|	δ����
											///<		1			|	δ����
											///<		2			|	ע����ֵ��( value name)
											///<		3			|	ͬ��
											///<		4			|	ͬ��
											///<		5			|	δ����
											///<		6			|	δ����
											///<		7			|	δ����
	std::wstring			strInfo_3;		///< processType ��ͬ�����ֶδ������岻ͬ
											///< -----------------------------------------------------
											///<	processType		|		����
											///< -----------------------------------------------------
											///<		0			|	δ����
											///<		1			|	δ����
											///<		2			|	δ����
											///<		3			|	���õ���ֵ
											///<		4			|	ͬ��
											///<		5			|	δ����
											///<		6			|	δ����
											///<		7			|	δ����
	std::wstring			strVirusName;	///< ����������������Ϊ����ʱ�Ų���

	_S_PROCESS_OBJECT_INFO() : dwIndex(0),
		processType(enum_PROCESS_AT_UNDEFINED)
	{
	}
} S_PROCESS_OBJECT_INFO;

KXE_JSON_DDX_BEGIN(S_PROCESS_OBJECT_INFO)
KXE_JSON_DDX_MEMBER("ID", dwIndex)
KXE_JSON_DDX_MEMBER("ProcessType", processType)
KXE_JSON_DDX_MEMBER("Info_1", strInfo_1)
KXE_JSON_DDX_MEMBER("Info_2", strInfo_2)
KXE_JSON_DDX_MEMBER("Info_3", strInfo_3)
KXE_JSON_DDX_MEMBER("VirusName", strVirusName)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

typedef struct _S_HISTORY_ITEM_INFO : public _S_FIX_ITEM
{
	EM_HISTORY_ITEM_STATE				state;				///< ����״̬�����޸�/�ѻ�ԭ
	std::vector<S_PROCESS_OBJECT_INFO>	vecProcessItems;	///< ��һ������ľ��崦�������Ϣ�б�

	_S_HISTORY_ITEM_INFO() : state(enum_HISTORY_ITEM_STATE_INVALID)
	{
	}
} S_HISTORY_ITEM_INFO;

KXE_JSON_DDX_BEGIN(S_HISTORY_ITEM_INFO)
KXE_JSON_DDX_MEMBER("Type", emType)
KXE_JSON_DDX_MEMBER("ID", dwID)
KXE_JSON_DDX_MEMBER("Name", strItemName)
KXE_JSON_DDX_MEMBER("Level", emLevel)
KXE_JSON_DDX_MEMBER("Advice", Advice)
KXE_JSON_DDX_MEMBER("ActionType", ActionType)
KXE_JSON_DDX_MEMBER("ItemState", state)
KXE_JSON_DDX_MEMBER("ProcessItems", vecProcessItems)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

typedef struct _S_HISTORY_ITEM_EX
{
	__time64_t							tmHistoryTime;  ///< ʱ���
	std::vector<S_HISTORY_ITEM_INFO>	FixedList;		///< �������
} S_HISTORY_ITEM_EX;

KXE_JSON_DDX_BEGIN(S_HISTORY_ITEM_EX)
KXE_JSON_DDX_MEMBER("HistoryTime", tmHistoryTime)
KXE_JSON_DDX_MEMBER("FixedList", FixedList)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/*
* ��ʷ��������ԭ���ܵĽṹ����
*/
typedef struct _S_RECOVER_ITEM
{
	__time64_t							tmHistoryTime;  ///< ʱ���
	std::vector<DWORD>					vecItemIDs;		///< ��ʱ����»�ԭ�� Item �б�
} S_RECOVER_ITEM;

KXE_JSON_DDX_BEGIN(S_RECOVER_ITEM)
KXE_JSON_DDX_MEMBER("HistoryTime", tmHistoryTime)
KXE_JSON_DDX_MEMBER("RecoverList", vecItemIDs)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief ������Ҫ�޸���Σ������Ϣ(�������S_FIX_ITEM��)
*/
typedef struct _S_FIX_ITEM_EX : public _S_FIX_ITEM
{
	//////////////////////////////////////////////////////////////////////////
	//new data
	std::wstring				strFile;				///< �ļ�
	std::wstring				strSubKey;				///< �Ӽ�
	std::wstring				strLocation;			///< λ��
	std::wstring				strDescript;			///< ����
	MALICIOUS_INFO				MaliciousInfo;			///< ������в�б�
	unsigned int				uIndex;					///< �޸��������ֵ
	unsigned int				uFixedStatus;			///< �����״̬,0��δ����,����ֵ���Ѿ�����
	unsigned int				uSelectStatus;			///< ѡ���״̬,0��δѡ��,����ֵ���Ѿ�ѡ��
	EM_SCAN_ENGINE_TYPE         scanEngineType;			///< ɨ�����������
	unsigned int				uIsFileNonPe;			///< �ļ��Ƿ�Ϊ�� PE���� 0 Ϊ�� PE��0 ��Ϊ PE��Ĭ��Ϊ PE�������ֶ�Ĭ��Ϊ 0
	std::wstring				strScriptGuid;			///< �ű� UUID
	BOOL						bScriptCanBeTrusted;	///< ��ʶ�˽ű��Ƿ��ܹ�������
	DWORD						dwSubItemID;			///< ����������С�� ID�����ڽ���չ���Ż���

	_S_FIX_ITEM_EX():
		uIndex(0),
		uFixedStatus(0),
		uSelectStatus(0),
		uIsFileNonPe(0),
		bScriptCanBeTrusted(FALSE),
		dwSubItemID(0)
	{
	}
} S_FIX_ITEM_EX;

KXE_JSON_DDX_BEGIN(S_FIX_ITEM_EX)
KXE_JSON_DDX_MEMBER("Type", emType)
KXE_JSON_DDX_MEMBER("ID", dwID)
KXE_JSON_DDX_MEMBER("Name", strItemName)
KXE_JSON_DDX_MEMBER("Level", emLevel)
KXE_JSON_DDX_MEMBER("Advice", Advice)
KXE_JSON_DDX_MEMBER("ActionType", ActionType)
KXE_JSON_DDX_MEMBER("File", strFile)
KXE_JSON_DDX_MEMBER("SubKey", strSubKey)
KXE_JSON_DDX_MEMBER("Location", strLocation)
KXE_JSON_DDX_MEMBER("Descript", strDescript)
KXE_JSON_DDX_MEMBER("MaliciousList", MaliciousInfo)
KXE_JSON_DDX_MEMBER("Index", uIndex)
KXE_JSON_DDX_MEMBER("FixedStatus", uFixedStatus)
KXE_JSON_DDX_MEMBER("SelectStatus", uSelectStatus)
KXE_JSON_DDX_MEMBER("ScanEngineType", scanEngineType)
KXE_JSON_DDX_MEMBER("IsFileNonPe", uIsFileNonPe)
KXE_JSON_DDX_MEMBER("ScriptGuid", strScriptGuid)
KXE_JSON_DDX_MEMBER("ScriptCanBeTrusted", bScriptCanBeTrusted)
KXE_JSON_DDX_MEMBER("SubItemID", dwSubItemID)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief ������Ҫ�޸�ѡ��״̬�ľ�����
*/
typedef struct _S_CHANGE_SELECT_ITEM
{
	unsigned int				uIndex;			///< ����
	unsigned int				uSelectStatus;	///< 0��ȡ��ѡ��
	unsigned int				uChangeAction;  ///< 0��ʾActionType��Ч,��������Ч
	S_POINT_PROCESS_TYPE		ActionType;		///< �������
	

	_S_CHANGE_SELECT_ITEM():
		uIndex(0),
		uSelectStatus(0),
		uChangeAction(0),
		ActionType(enum_PROCESS_TYPE_CLEAN)
	{
	}
} S_CHANGE_SELECT_ITEM;

KXE_JSON_DDX_BEGIN(S_CHANGE_SELECT_ITEM)
KXE_JSON_DDX_MEMBER("Index", uIndex)
KXE_JSON_DDX_MEMBER("SelectStatus", uSelectStatus)
KXE_JSON_DDX_MEMBER("ChangeAction", uChangeAction)
KXE_JSON_DDX_MEMBER("ActionType", ActionType)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief �����޸�ѡ��״̬������Ϣ
*/
typedef struct _S_CHANGE_SELECT_SETTING
{
	_S_CHANGE_SELECT_SETTING():
		dwSelectAll(0)
	{
	}

	DWORD dwSelectAll;		///< 0�Ǻ���, 1��ѡ��ȫ��, 2��ȡ��ѡ��ȫ��,
							///< ִ����ȫѡ��ȡ��ȫѡ�Ĳ�����,��������������ϸ�б���в���
	std::vector<S_CHANGE_SELECT_ITEM>	ItemList;	///< ��ÿ����в���
} S_CHANGE_SELECT_SETTING;

KXE_JSON_DDX_BEGIN(S_CHANGE_SELECT_SETTING)
KXE_JSON_DDX_MEMBER("SelectAll", dwSelectAll)
KXE_JSON_DDX_MEMBER("ItemList", ItemList)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

typedef struct _S_SELECT_RESULT_STATISTICS
{
	_S_SELECT_RESULT_STATISTICS():	uTotalCount(0),
									uSelectedCount(0)
	{
	}

	unsigned int uTotalCount;
	unsigned int uSelectedCount;
}S_SELECT_RESULT_STATISTICS;
KXE_JSON_DDX_BEGIN(S_SELECT_RESULT_STATISTICS)
KXE_JSON_DDX_MEMBER("TotalCount", uTotalCount)
KXE_JSON_DDX_MEMBER("SelectedCount", uSelectedCount)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

typedef struct _S_FIX_PROC_RESULT_STATISTICS
{
	_S_FIX_PROC_RESULT_STATISTICS():
		uTotalCount(0),
		uProcessCount(0),
		uEmergencyFlag(0),
		uNotProcessCount(0)
	{
	}

	unsigned int uTotalCount;		///< ����
	unsigned int uProcessCount;		///< �մ��������
	unsigned int uEmergencyFlag;	///< ������־,Ŀǰ1Ϊ���ָ�Ⱦ�Ͳ���,�����û�ȫ��ɨ��
	unsigned int uNotProcessCount;	///< δ����ı��

}S_FIX_PROC_RESULT_STATISTICS;
KXE_JSON_DDX_BEGIN(S_FIX_PROC_RESULT_STATISTICS)
KXE_JSON_DDX_MEMBER("TotalCount", uTotalCount)
KXE_JSON_DDX_MEMBER("ProcessCount", uProcessCount)
KXE_JSON_DDX_MEMBER("EmergencyFlag", uEmergencyFlag)
KXE_JSON_DDX_MEMBER("NotProcessCount", uNotProcessCount)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

typedef enum _EM_TRUST_LIST_OPERATION
{
	enum_TRUST_LIST_INVALID		= 0,	///< ��Ч��������
	enum_TRUST_LIST_ADD			= 1,	///< ����ĳ���͵�����������
	enum_TRUST_LIST_DELETE		= 2,	///< ɾ��ĳ���͵�����������
	enum_TRUST_LIST_REPLACE		= 3		///< �滻�����б��ĳһ���������
} EM_TRUST_LIST_OPERATION;
KXE_JSON_DDX_ENUM(EM_TRUST_LIST_OPERATION)

//-------------------------------------------------------------------------

KXE_JSON_DDX_ENUM(EM_TRUST_ITEM_TYPE)

//-------------------------------------------------------------------------

typedef struct _S_TRUST_LIST
{
	EM_TRUST_LIST_OPERATION		operation;		///< ��������
	EM_TRUST_ITEM_TYPE			itemType;		///< ������Ŀ����
	std::vector<std::wstring>	vecItemList;	///< ��Ŀ�б�
} S_TRUST_LIST;
KXE_JSON_DDX_BEGIN(S_TRUST_LIST)
KXE_JSON_DDX_MEMBER("Operation", operation)
KXE_JSON_DDX_MEMBER("Type", itemType)
KXE_JSON_DDX_MEMBER("ItemList", vecItemList)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

typedef struct _S_HISTORY_RECORD_ITEM
{
	__time64_t					tmTime;			///< ����ʱ��
	DWORD						dwItemID;		///< ������ ID
} S_HISTORY_RECORD_ITEM;
KXE_JSON_DDX_BEGIN(S_HISTORY_RECORD_ITEM)
KXE_JSON_DDX_MEMBER("Time", tmTime)
KXE_JSON_DDX_MEMBER("ItemID", dwItemID)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

typedef struct _S_REMOVE_HISTORY_RECORD_OPTION
{
	bool								bClearAll;		///< ��ʶ�Ƿ����������ʷ�����¼
	std::vector<S_HISTORY_RECORD_ITEM>	vecRecords;		///< ���� bClearAll Ϊ��ʱ��ָ��Ҫ��յ���ʷ�����¼�б�
} S_REMOVE_HISTORY_RECORD_OPTION;
KXE_JSON_DDX_BEGIN(S_REMOVE_HISTORY_RECORD_OPTION)
KXE_JSON_DDX_MEMBER("ClearAll", bClearAll)
KXE_JSON_DDX_MEMBER("Records", vecRecords)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief ����������С��ɨ��״̬
*/
typedef enum _EM_SCAN_ITEM_STATUS
{
	enum_SCAN_ITEM_STATUS_UNDEFINED			= -1,			///< ��Ч״̬
	enum_SCAN_ITEM_STATUS_TO_BE_STARTED		= 0,			///< ��δ��ʼ
	enum_SCAN_ITEM_STATUS_SCANNING,							///< ����ɨ��
	enum_SCAN_ITEM_STATUS_NET_DIAGNOSISING,					///< ��ö����ϣ����ڽ���������
	enum_SCAN_ITEM_STATUS_COMPLETED							///< ɨ�����
} EM_SCAN_ITEM_STATUS;

KXE_JSON_DDX_ENUM(EM_SCAN_ITEM_STATUS)

//-------------------------------------------------------------------------

/**
* @brief ����������С����ϸ��Ϣ
*/
typedef struct _S_SCAN_ITEM_DETAIL
{
	DWORD									dwID;				///< ��ţ�Ψһ��
	EM_SCAN_ITEM_STATUS						emScanStatus;		///< ɨ��״̬
	DWORD									dwTotalCount;		///< ɨ������
	EM_POINT_LEVEL							emLevel;			///< Σ�ռ�����ֵΪ��С���з��������쳣���м��������в��һ���Σ�ռ���
	DWORD									dwThreatCount;		///< ������в��Ŀ

	_S_SCAN_ITEM_DETAIL() : dwID(0),
		emScanStatus(enum_SCAN_ITEM_STATUS_UNDEFINED),
		dwTotalCount(0),
		emLevel(enum_POINT_LEVEL_UNKNOWN),
		dwThreatCount(0)
	{
	}
} S_SCAN_ITEM_DETAIL;

KXE_JSON_DDX_BEGIN(S_SCAN_ITEM_DETAIL)
KXE_JSON_DDX_MEMBER("ID", dwID)
KXE_JSON_DDX_MEMBER("TotalCount", dwTotalCount)
KXE_JSON_DDX_MEMBER("ScanStatus", emScanStatus)
KXE_JSON_DDX_MEMBER("Level", emLevel)
KXE_JSON_DDX_MEMBER("ThreatCount", dwThreatCount)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief ����������С����ϸ��Ϣ
*/
typedef struct _S_SCAN_ITEM_SIMPLE_DETAIL
{
	std::wstring							strName;			///< ����
	DWORD									dwID;				///< ��ţ�Ψһ��
	std::wstring							strDecription;		///< ����

	_S_SCAN_ITEM_SIMPLE_DETAIL() : dwID(0)
	{
	}
} S_SCAN_ITEM_SIMPLE_DETAIL;

KXE_JSON_DDX_BEGIN(S_SCAN_ITEM_SIMPLE_DETAIL)
KXE_JSON_DDX_MEMBER("Name", strName)
KXE_JSON_DDX_MEMBER("ID", dwID)
KXE_JSON_DDX_MEMBER("Description", strDecription)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

/**
* @brief ���������������ϸ��Ϣ
*/
typedef struct _S_SCAN_GROUP_DETAIL
{
	std::wstring								strName;		///< ����
	std::vector<S_SCAN_ITEM_SIMPLE_DETAIL>		vecSubItemList;	///< С���б����м�ΪС����
} S_SCAN_GROUP_DETAIL;

KXE_JSON_DDX_BEGIN(S_SCAN_GROUP_DETAIL)
KXE_JSON_DDX_MEMBER("Name", strName)
KXE_JSON_DDX_MEMBER("SubItemList", vecSubItemList)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

typedef struct _S_SCAN_CATEGORY_DETAIL
{
	std::wstring									strName;			///< �ܷ�������
	std::vector<S_SCAN_GROUP_DETAIL>				vecScanItem;		///< �����б�
} S_SCAN_CATEGORY_DETAIL;

KXE_JSON_DDX_BEGIN(S_SCAN_CATEGORY_DETAIL)
KXE_JSON_DDX_MEMBER("Name", strName)
KXE_JSON_DDX_MEMBER("ItemList", vecScanItem)
KXE_JSON_DDX_END()

//-------------------------------------------------------------------------

typedef enum _EM_COMMON_STATUS_ENABLE_FLAGS
{
	enum_dwHistoryRecordCount			= 0x01,					///< ��Ա dwHistoryRecordCount ��Ч
} EM_COMMON_STATUS_ENABLE_FLAGS;

typedef struct _S_COMMON_STATUS_INFO
{
	__int64									nEnableFlags;				///< ��ʶ��Щ��Ա����Ч�ģ�Ϊ��־ EM_COMMON_STATUS_ENABLE_FLAGS ���߼���
	DWORD									dwHistoryRecordCount;		///< ��������ʷ��¼����
	_S_COMMON_STATUS_INFO() :
	nEnableFlags(0),
	dwHistoryRecordCount(0)
	{
	}
} S_COMMON_STATUS_INFO;

KXE_JSON_DDX_BEGIN(S_COMMON_STATUS_INFO)
KXE_JSON_DDX_MEMBER("EnableFlags", nEnableFlags)
KXE_JSON_DDX_MEMBER("RecordCount", dwHistoryRecordCount)
KXE_JSON_DDX_END()
