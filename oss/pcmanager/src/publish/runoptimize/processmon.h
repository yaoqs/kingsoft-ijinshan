////////////////////////////////////////////////////////////////////////////////
//      
//      File for process info mon
//      
//      File      : processmon.h
//      Version   : 1.0
//      Comment   : ���ӵ�ǰ���н��̵���Ϣ
//      
//      Create at : 2011-1-27
//      Create by : liupeng
//		Motify by : 
//      
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../common/sharememlock.h"

// ����ʹ��
struct KProcInfoItem
{
	DWORD					m_nCbSize;
	WCHAR					m_strProcPath[MAX_PATH];// ����·��
	DWORD					m_nProcessID;			// ����ID
	ULONGLONG				m_nCreateID;			// ���̴���ID
	DWORD					m_nTrustMode;			// ��ȫ��Ϣ
	
	DWORD					m_nReserved[20];		// ������
};

struct KPocessInfoList
{
	DWORD					m_nSize;
	ShareMemLock			m_lock;
	// ������Է�system����Ϣ
	DWORD					m_nMaxCnt;
	DWORD					m_nCurrentCnt;
	DWORD					m_nReserved[100];
	KProcInfoItem			m_Items[1];
};

#define PROC_INFO_MON_FILE_MAGIC		('PRI')
#define PROC_INFO_MON_FILE_FILE			((1 << 16) | 1)

typedef struct _tagProcInfoMonCacheFileHeader
{
	DWORD			m_nMagic;					// 'PROC_INFO_MON_FILE_MAGIC'
	DWORD			m_nFileVersion;				// �ļ��汾 PROC_INFO_MON_FILE_FILE
	DWORD			m_nDataDirs;
	DWORD			m_nDataOffset[20];			// ����offsetDir
}ProcInfoMonCacheFileHeader;

#define PROC_INFO_MON_DATA_CACHE		0		// ��һ����cfg

#define PROC_INFO_MON_MAPDATA_NAME		(TEXT("Global\\DE99E467-C2DA-4207-84DD-D2D0B0D7FE90"))

class KProcInfoMonCacheReader
{
private:
	HANDLE				m_hFileMap;
	LPVOID				m_pBufView;

public:
	KProcInfoMonCacheReader():m_hFileMap(NULL),
		m_pBufView(NULL)
	{
	}

	~KProcInfoMonCacheReader()
	{
		Uninit();
	}

	HRESULT	Init()
	{
		HANDLE hFileMap = NULL;
		BYTE* pMapBuf = NULL;
		SIZE_T sizeToMap = {0};

		if (m_hFileMap != NULL && m_pBufView != NULL)
			return S_OK;

		hFileMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, PROC_INFO_MON_MAPDATA_NAME);
		if (NULL == hFileMap)
		{
			hFileMap = ::OpenFileMapping(FILE_MAP_READ, FALSE, PROC_INFO_MON_MAPDATA_NAME);
			if (NULL == hFileMap)
			{
				printf("OpenFileMapping failed: %d\n", ::GetLastError());
				goto exit0;
			}

			pMapBuf = (BYTE*)::MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 0);		
			if (!pMapBuf)
			{
				printf("MapViewOfFile failed: %d\n", ::GetLastError());
				goto exit0;
			}
		}
		else
		{
			pMapBuf = (BYTE*)::MapViewOfFile(hFileMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
			if (!pMapBuf)
			{
				printf("MapViewOfFile failed: %d\n", ::GetLastError());
				goto exit0;
			}
		}


		m_hFileMap = hFileMap;
		m_pBufView = pMapBuf;
		return S_OK;

exit0:
		if (pMapBuf)
		{
			::UnmapViewOfFile(pMapBuf);
			pMapBuf = NULL;
		}

		if (hFileMap)
		{
			::CloseHandle(hFileMap);
			hFileMap = NULL;
		}

		return E_FAIL;
	}

	HRESULT	Uninit()
	{
		if (m_pBufView && m_hFileMap)
		{
			::UnmapViewOfFile(m_pBufView);
			m_pBufView = NULL;
		}
		if (m_hFileMap)
		{
			::CloseHandle(m_hFileMap);
			m_hFileMap = NULL;
		}
		return S_OK;
	}

	KPocessInfoList*	GetProcessPerfList()
	{
		if (m_pBufView)
		{
			return (KPocessInfoList*)((BYTE*)m_pBufView + ((ProcInfoMonCacheFileHeader*)(m_pBufView))->m_nDataOffset[PROC_INFO_MON_DATA_CACHE]);
		}
		return NULL;
	}


};


