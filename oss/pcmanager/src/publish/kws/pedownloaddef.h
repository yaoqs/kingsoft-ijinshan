////////////////////////////////////////////////////////////////////////////////
//      
//      File for pe download file data
//      
//      File      : pedownloaddef.h
//      Version   : 1.0
//      Comment   : �����ļ���������
//      
//      Create at : 2010-4-21
//      Create by : liupeng
//		Motify by : 
//      
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../common/sharememlock.h"

enum DonwloadProcessClass
{
	DPC_Unkown		= 0,
	DPC_IE			= 1,
	DPC_FLASHGET	= 2,
	DPC_XUNLEI		= 3,
	DPC_QQDOWN		= 4,
	DPC_FIREFOX		= 5,
	DPC_TT			= 6,
	DPC_MAXTHON		= 7,		// ���Σ���Ͱ
	DPC_TheWorld	= 8,		// ����֮��
	DPC_SogouExplorer	= 9,	// �ѹ������
	DPC_chrome		 = 10,		// google�����
	DPC_FlashGetMini = 11,		// ����쳵
	DPC_WebThunder = 12,		// ��ҳѸ��
	DPC_IM_QQ = 13,				// ʹ��qq������ļ�
	DPC_IM_MSN = 14,			// ʹ��MSN������ļ�
	DPC_MINIXUNLEI = 15,		// ����Ѹ��
	DPC_IM_TM = 16,
	DPC_IM_AliIM = 17,
	DPC_Thunder5 = 18,
	DPC_XBrowser = 19,
	DPC_Thunder7 = 20,
	DPC_RayResource = 21,
	DPC_Maxthon2 = 22,
	DPC_NamiRobot = 23,
	DPC_Emule		= 24,
	DPC_Orbit		= 25,
	DPC_QQBROWSER	= 26,
	DPC_UDOWN		= 27, // 115�ŵ�
//	DPC_115BR		= 28, // 115�����
	DPC_BAIDU_JSXZ  = 29, // �ٶȼ�������
};

struct PeDownNotifyParam
{
	DWORD		m_nFileType;				// 1: pe
	WCHAR		m_filePath[MAX_PATH];
	WCHAR		m_strProcess[MAX_PATH];
	DWORD		m_nProcessClass;			// 1: ie, 2: flashget 3: xunlei 4: qq ����
	DWORD		m_nProcessID;
};

struct UrlDownNotifyParam
{
	DWORD		m_nDownType;				// 1: pe
	WCHAR		m_strProcess[MAX_PATH];
	char		m_strUrl[1024];
	BYTE		m_fileHeader[1024];
	INT			m_nFileHeaderLen;
	DWORD		m_nProcessClass;			// 1: ie, 2: flashget 3: xunlei 4: qq ����
	DWORD		m_nProcessID;
};

struct DownToolCacheScanNotifyParam
{
	DWORD		m_nDownType;				// 1: pe
	WCHAR		m_strProcess[MAX_PATH];
	char		m_strUrl[1024];
	WCHAR		m_filePath[MAX_PATH];
	DWORD		m_nProcessClass;			// 1: ie, 2: flashget 3: xunlei 4: qq ����
	DWORD		m_nProcessID;
	__int64		m_nDowntime;
};

struct ClearDangerFile
{
	WCHAR		m_filePath[MAX_PATH];
	HRESULT		m_hResult;
	BOOL		m_bNotClearFile;
};

struct DeleteFileInfo
{
	WCHAR		m_filePath[MAX_PATH];
	HRESULT		m_hResult;
	BOOL		m_bNotDeleteFile;
};

struct DeleteAllFileInfo
{
	BOOL		m_bDeleteSafe;
	BOOL		m_bDeleteUnkonwn;
	BOOL		m_bDeleteDanger;

	BOOL		m_bDeleteFile;
};

struct ModifyFileInfo
{
	WCHAR		m_oldFilePath[MAX_PATH];
	WCHAR		m_newFilePath[MAX_PATH];
	HRESULT		m_hResult;
	BOOL		m_bNotModifyFile;
};

struct NotifySettingChange
{
	BOOL		m_bEnableAutoScan;
};

enum DownSettingID
{
	DFS_AUTO_SCAN			= 1,
	DFS_AUTO_CLEAN_VIRUS	= 2,
	DFS_SHOW_SAFE_POP		= 3,
	DFS_SHOW_GRAP_POP		= 4,
};

struct DownSettingParam
{
	DWORD		m_nSettingID;				// �������ID (DownSettingID)
	DWORD		m_nValue;					// �������ֵ
};

struct RestoreFileParam
{
	WCHAR		m_strFilePath[MAX_PATH];
	HRESULT		m_hr;
};

#define IPC_PROC_OnFindPeDownload		TEXT("OnFindPeDownload")
#define IPC_PROC_OnFindUrlDonwload		TEXT("OnFindUrlDonwload")
#define IPC_PROC_OnFindDownCacheItem	TEXT("OnFindDownCacheItem")
#define IPC_PROC_OnClearDangerItem		TEXT("OnClearDangerItem")
#define IPC_PROC_OnDeleteFileItem       TEXT("OnDeleteFileItem")
#define IPC_PROC_OnModifyFileName       TEXT("OnModifyFileName")
#define IPC_PROC_OnNotifySettingChange	TEXT("OnNotiyfSettingChange")
#define IPC_PROC_OnDeleteAllItems		TEXT("OnDeleteAllItems")
#define IPC_PROC_OnRestoreFile			TEXT("OnRestoreFile")

//////////////////////////////////////////////////////////////////////////
enum DownFileSecurityState
{
	DF_Secu_UnScan					= 0,
	DF_Secu_Gray					= 1,
	DF_Secu_Safe					= 2,
	DF_Secu_Danger					= 3,
	DF_Secu_Ignore_Safe				= 4,
	DF_Secu_Gray_Timeout_Safe		= 5,
	DF_Secu_Gray_NetError			= 6,
};

enum DownFileFlag
{
	DFF_DELETE						= 1,
};

enum DownFileFlagExtra
{
	DFEF_FROM_CACHE						= 1,
};

enum enumPopType
{
	Wtl_SafePop   = 400,
	Wtl_RiskPop,
	Wtl_GrayPop,
	Wtl_ResultPop,
	Wtl_ScanPop,
	Wtl_IMSafePop
};

struct DownFileItem
{
	DWORD		m_nFlag;						// DownFileFlag
	WCHAR		m_strFile[MAX_PATH];
	WCHAR		m_strDwonloader[MAX_PATH];
	WCHAR		m_strVirusOrName[64];			// ����������ļ�����ô��������ƣ������ǲ�������
	char		m_url[1024];
	DWORD		m_nNextItem;
	DWORD		m_eSecuState;
	DWORD		m_nDownProcClass;				// �ο�DonwloadProcessClass
	__int64		m_downTime;
	__int64		m_firstScanTime;
	__int64		m_nextScanTime;
	DWORD		m_nScanCnt;
	DWORD		m_nFlagExtra;
	DWORD		m_nReserve[8];

	DownFileItem&	operator= (const DownFileItem& item2)
	{
		memcpy(this, &item2, sizeof(DownFileItem));
		return *this;
	}
};

inline bool operator< (const DownFileItem& item1, const DownFileItem& item2)
{
	return _wcsicmp(item1.m_strFile, item2.m_strFile) < 0;
}

inline bool operator== (const DownFileItem& item1, const DownFileItem& item2)
{
	return _wcsicmp(item1.m_strFile, item2.m_strFile) == 0;
}

enum
{
	Down_File_Block_Before_Download		= 1,
	Down_File_AutoClear_After_Scan		= 2,
	Down_File_Clear_By_User				= 3,

	// ��������
	Down_File_Block_Before_Download_With_Quarantine		= 4,
	Down_File_AutoClear_After_Scan_With_Quarantine		= 5,
	Down_File_Clear_By_User_With_Quarantine				= 6,
};

struct DownFileClearLogItem
{
	DWORD			m_nSize;
	DWORD			m_nVersion;
	DWORD			m_ClearType;
	DownFileItem	m_data;
};

typedef struct _tagPeDownMapDescription
{
	ShareMemLock			m_lock;							// ���̼����ͬ����
	DWORD					m_nMaxItemCnt;					// �����
	DWORD					m_nUsedItemCnt;					// �Ѿ�ʹ�õ���
	DWORD					m_nFirstNewItem;				// �¼���ĵ�һ���ļ���
	DWORD					m_nFirstFreeItem;				// ��һ��������
	DWORD					m_nFirstUnknownItem;			// ��һ��δ��������
	DWORD					m_nFirstKnownItem;				// ��һ���Ѽᶨ����

	DWORD					m_nReserve[10];
	DownFileItem			m_CacheItems[1];
}PeDownMapDescription;

#define DOWN_FILE_MAPDATA_NAME		(TEXT("Global\\19742972-3E2E-4a79-BE72-0E7D0F1A3AB3"))
#define DOWN_FILE_EANABLE_AND_RUNNING		(TEXT("Global\\kws_down_files_scan_B3525A34_EB2D_44a7_924C_24B04C669282"))

typedef struct _tagDownFileMapItem
{
	volatile DWORD			m_nMapType;				// map������
	volatile DWORD			m_nOffset;				// ������ļ�ͷλ��
	volatile DWORD			m_nMapSize;				// �����Ĵ�С
	volatile DWORD			m_nDataVersion;			// map�����ݰ汾
}DownFileMapItem;

#define DOWN_FILE_MAX_MAP_TABLE		(20)
#define DOWN_FILE_FILE_MAGIC		('UFD')
#define DOWN_FILE_FILE_VERSION		((1 << 16) | 1)

typedef struct _tagDownFilHeader
{
	volatile DWORD			m_nMagic;				// 'UFD'
	volatile DWORD			m_nFileVersion;			// �ļ��汾
	ShareMemLock			m_Lock;					// ��д��
	volatile DWORD			m_nMapCnt;				// �Ѿ�ʹ�õ�map����
	DownFileMapItem			m_MapTable[DOWN_FILE_MAX_MAP_TABLE]; // map������
}DownFileHeader;

#define PEDOWN_CLEAR_LOG_FILE_NAME			TEXT("dflog.dat")

#define PE_DOWNLOAD_MAP				0

#define ZIP_FILE_HEADER_FLAG				0x04034b50

inline BOOL IsZipFileHeader(BYTE* pBuf, DWORD nSize)
{
	if (nSize < 4) return FALSE;
	DWORD* pData = (DWORD*)pBuf;
	return *pData == ZIP_FILE_HEADER_FLAG;
}

inline BOOL IsRarFileHeader(BYTE* pBuf, DWORD nSize)
{
	if (nSize < 7) return FALSE;
	static BYTE flagBuf[7] = {0x52, 0x61, 0x72, 0x21, 0x1a, 0x07, 0x00};
	return (memcmp(pBuf, flagBuf, 7) == 0);
}
