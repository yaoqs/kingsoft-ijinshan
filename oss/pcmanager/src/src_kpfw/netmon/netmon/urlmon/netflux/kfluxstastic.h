////////////////////////////////////////////////////////////////////////////////
//      
//      File for net flux
//      
//      File      : kfluxstastic.h
//      Version   : 1.0
//      Comment   : ����ͳ��
//      
//      Create at : 2010-12-30
//      Create by : liupeng
//		Motify by : 
//      
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "kpfw/netstastic.h"
#include "../kurlcachemgr.h"
#include <map>
#include <vector>
using namespace std;

struct KStasticFluxProcessList;

//////////////////////////////////////////////////////////////////////////
class KStasticFluxCacheMgr
{
public:
	KStasticFluxCacheMgr();
	~KStasticFluxCacheMgr();

	HRESULT		Init(LPCWSTR strCacheFile, LPCWSTR urlMapName);
	HRESULT		UnInit();
	KStasticFluxProcessList* GetStasticFluxList();
	HRESULT		FlushToDisk();

private:
	BOOL	CreateCacheFile();
	BOOL	InitCacheFile(BYTE* pData, DWORD nSize);
	BOOL	InitFluxListData(KStasticFluxProcessList* pData, DWORD nSize, BOOL bFirstInit);
	BOOL	ResizeFileToSize(HANDLE hFile, DWORD nSize);

	BOOL	OpenCacheFile();
	BOOL	VerifyCacheFile(HANDLE hFile);
	BOOL	VerifyCacheFile(BYTE* pData, DWORD nFileSize);
	BOOL	VerifyFluxListData(KStasticFluxProcessList* pData);

	BOOL	InitMapData(BYTE* pData, DWORD nSize);
	BOOL	SetObjectToLowIntegrity(HANDLE hObject, SE_OBJECT_TYPE type = SE_KERNEL_OBJECT);
	DWORD	GetDataSize();

private:
	HANDLE				m_hFile;
	HANDLE				m_hFileMap;

	LPVOID				m_pData;
	ATL::CString		m_strCacheFile;
	LPCWSTR				m_strUrlMapName;
};

//////////////////////////////////////////////////////////////////////////
class KStasticProgramFlux
{
public:
	KStasticProgramFlux();
	~KStasticProgramFlux();

	HRESULT Init(KProcFluxItem* pItem);
	HRESULT Init(KFluxStasticProcItem* pItem);
	BOOL	IsMatch(KProcFluxItem* pItem);
	BOOL	IsMatch(KStasticProgramFlux* pItem);

	HRESULT	UpdateData(KProcFluxItem* pItem);
	HRESULT	GetFlux(KFluxStasticProcItem* pItem);
	LPCWSTR GetProgramePath() {return m_strProgramPath;}

	ATL::CString			m_strProgramPath;
	ULONGLONG				m_nTotalRecv;			// �ܼƽ��ܵ�����
	ULONGLONG				m_nTotalSend;			// �ܼƷ��͵�����
};

//////////////////////////////////////////////////////////////////////////
// ����ͳ��Ҫ����3�����������
// 1��ϵͳ���������������
//		��ÿ��������ж����Ƿ�����ͬһ�죬��������ڣ���ô�����ǰ�����ݣ����¿�ʼͳ��
// 2��ϵͳ�������ڵ����ٴο��������
//		�ڵ�ǰͳ����Ϣ�б�����¼��ʱ��
// 3��������������ʿ�˳����ִ򿪵����
//		�۲�ÿ����������������Կ����ڷ�������ʱ�����һ������
//		��֤ÿ�η����������0��ʼ����

class KFluxStastic
{
public:
	KFluxStastic();
	~KFluxStastic();

	HRESULT		Init();
	HRESULT		UnInit();
	HRESULT		UpdateFlux(KProcessFluxList* pFluxList, __int64 nDisableTime);

private:
	HRESULT		RefreshToCache(__int64 nTimeNow, __int64 nDisableTime);
	HRESULT		ResetToday(__int64 nTimeNow);
	KStasticProgramFlux* GetStasticFlux(KProcFluxItem* pItem);
	HRESULT		Clear();
	__int64		GetDayLastTime(__int64 nTime);
	__int64		GetDayStartTime(__int64 nTime);

private:
	KStasticFluxCacheMgr*				m_pCacheMgr;

	__int64								m_nTimeLastWatch;
	__int64								m_nTimeStartWatch;
	__int64								m_nTimeTodayStartTime;
	__int64								m_nTimeTodayLastTime;

	vector<KStasticProgramFlux*>		m_todayPrograms;
	map<ULONGLONG, size_t>				m_procToProgramMap;

	ULONGLONG							m_nFluxRecv;
	ULONGLONG							m_nFluxSend;

	// Ϊ�˷�ֹ��������ʱ�򣬷����ܵõ�֪ͨ��ֱ���˳���ʹ��һ��������
	// ˢ��
	DWORD								m_nFlushCounter; 
};