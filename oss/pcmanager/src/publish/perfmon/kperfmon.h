////////////////////////////////////////////////////////////////////////////////
//      
//      File for perf mon
//      
//      File      : kperfmon.h
//      Version   : 1.0
//      Comment   : ϵͳ���ܼ���
//      
//      Create at : 2011-2-14
//      Create by : liupeng
//		Motify by : 
//      
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <WinPerf.h>
#include <map>
#include <vector>

using namespace std;

//////////////////////////////////////////////////////////////////////////
#define TOTALBYTES    819200
#define BYTEINCREMENT 102400

inline PPERF_OBJECT_TYPE FirstObject( PPERF_DATA_BLOCK PerfData )
{
	return( (PPERF_OBJECT_TYPE)((PBYTE)PerfData + 
		PerfData->HeaderLength) );
}

inline PPERF_OBJECT_TYPE NextObject( PPERF_OBJECT_TYPE PerfObj )
{
	return( (PPERF_OBJECT_TYPE)((PBYTE)PerfObj + 
		PerfObj->TotalByteLength) );
}

inline PPERF_INSTANCE_DEFINITION FirstInstance( PPERF_OBJECT_TYPE PerfObj )
{
	return( (PPERF_INSTANCE_DEFINITION)((PBYTE)PerfObj + 
		PerfObj->DefinitionLength) );
}

inline PPERF_INSTANCE_DEFINITION NextInstance( 
									   PPERF_INSTANCE_DEFINITION PerfInst )
{
	PPERF_COUNTER_BLOCK PerfCntrBlk;

	PerfCntrBlk = (PPERF_COUNTER_BLOCK)((PBYTE)PerfInst + 
		PerfInst->ByteLength);

	return( (PPERF_INSTANCE_DEFINITION)((PBYTE)PerfCntrBlk + 
		PerfCntrBlk->ByteLength) );
}

inline PPERF_COUNTER_DEFINITION FirstCounter( PPERF_OBJECT_TYPE PerfObj )
{
	return( (PPERF_COUNTER_DEFINITION) ((PBYTE)PerfObj + 
		PerfObj->HeaderLength) );
}

inline PPERF_COUNTER_DEFINITION NextCounter( 
									 PPERF_COUNTER_DEFINITION PerfCntr )
{
	return( (PPERF_COUNTER_DEFINITION)((PBYTE)PerfCntr + 
		PerfCntr->ByteLength) );

}

inline LPBYTE GetCounterData(PPERF_INSTANCE_DEFINITION PerfInst, PPERF_COUNTER_DEFINITION PerfCntr)
{
	return (PBYTE)PerfInst + PerfInst->ByteLength + PerfCntr->CounterOffset;
}

inline LPBYTE GetCounterData(PPERF_OBJECT_TYPE PerfObj, PPERF_COUNTER_DEFINITION PerfCntr)
{
	return (PBYTE)PerfObj + PerfObj->DefinitionLength + PerfCntr->CounterOffset;
}

inline LPBYTE GetCounterData(PPERF_COUNTER_BLOCK PerfCounterBlock, PPERF_COUNTER_DEFINITION PerfCntr)
{
	return (PBYTE)PerfCounterBlock + PerfCntr->CounterOffset;
}

inline DWORD	GetCounterDword(PPERF_INSTANCE_DEFINITION  PerfInst, PPERF_COUNTER_DEFINITION Counter)
{
	LPBYTE pData = GetCounterData(PerfInst, Counter);
	if (pData) return *((DWORD*)pData);
	return -1;
}

inline ULONGLONG GetCounterUlonglong(PPERF_INSTANCE_DEFINITION  PerfInst, PPERF_COUNTER_DEFINITION Counter)
{
	LPBYTE pData = GetCounterData(PerfInst, Counter);
	if (pData) return *((ULONGLONG*)pData);
	return -1;
}

inline DWORD	GetCounterDword(PPERF_COUNTER_BLOCK  PerfCounterBlock, PPERF_COUNTER_DEFINITION Counter)
{
	LPBYTE pData = GetCounterData(PerfCounterBlock, Counter);
	if (pData) return *((DWORD*)pData);
	return -1;
}

inline ULONGLONG GetCounterUlonglong(PPERF_COUNTER_BLOCK  PerfCounterBlock, PPERF_COUNTER_DEFINITION Counter)
{
	LPBYTE pData = GetCounterData(PerfCounterBlock, Counter);
	if (pData) return *((ULONGLONG*)pData);
	return -1;
}

/*****************************************************************
*                                                               *
* Display the indexes and/or names for all performance objects, *
* instances, and counters.                                      *
*                                                               *
*****************************************************************/
// 230: process
// 232: threads
// 2:	system

enum ProcessDataIDs
{
	// ���̴�������������ʹ��ʱ�䣬100nsΪ��λ�ļ�����
	Proc_Perf_Data_Processor_Time = 0,

	// ���̴������������û�̬��ʱ�� 100nsΪ��λ�ļ�����
	Proc_Perf_Data_User_Time = 1,

	// ���̴������������û�̬��ʱ�� 100nsΪ��λ�ļ�����
	Proc_Perf_Data_Privileged_Time = 2,

	// ���̴����������ʹ�õ������ڴ��ֽ���
	Proc_Perf_Data_Virtual_Mem_Peak_Bytes = 3,

	// ���̵�ǰʹ�õ������ڴ��ֽ���
	Proc_Perf_Data_Virtual_Bytes = 4,

	// ���̵�ǰ��ҳ�������
	Proc_Perf_Data_Page_Fault_Per_Sec = 5,

	// ���̹���������С
	Proc_Perf_Data_Working_Set_Peak = 6,

	// ���̹�������С
	Proc_Perf_Data_Working_Set = 7,

	// ����ҳ���ļ�ʹ������ֵ
	Proc_Perf_Data_Page_File_Peak_Bytes = 8,

	// ����ҳ���ļ�ʹ����
	Proc_Perf_Data_Page_File = 9,

	// ����˽���ڴ�ʹ����
	Proc_Perf_Data_Private_Bytes = 10,

	// ���̵��߳���
	Proc_Perf_Data_Thread_Count = 11,

	// �������ȼ�����
	Proc_Perf_Data_Priority_Base = 12,

	Proc_Perf_Data_Elapsed_Time = 13,

	// ����ID
	Proc_Perf_Data_Process_ID = 14,

	// ������ID
	Proc_Perf_Data_Creator_ID = 15,

	// ��ҳ�ڴ��ʹ����
	Proc_Perf_Data_Pool_Paged_Bytes = 16,

	// δ��ҳ�ڴ��ʹ����
	Proc_Perf_Data_Pool_NonPaged_Bytes = 17,

	// �����
	Proc_Perf_Data_Handle_Count = 18,

	// ÿ��io����������
	Proc_Perf_Data_IO_Read_Per_Sec = 19,

	// ÿ��ioд��������
	Proc_Perf_Data_IO_Write_Per_Sec = 20,

	// ÿ��io���ݲ�������
	Proc_Perf_Data_IO_Data_Per_Sec = 21,

	// ÿ������io����
	Proc_Perf_Data_IO_Other_Per_Sec = 22,

	// ÿ��io�������ٶ�
	Proc_Perf_Data_IO_Read_Bytes_Per_Sec = 23,

	// ÿ��ioд�����ٶ�
	Proc_Perf_Data_IO_Write_Bytes_Per_Sec = 24,

	// ÿ��io���ݲ����ٶ�
	Proc_Perf_Data_IO_Data_Bytes_Per_Sec = 25,

	// ÿ��io�����������ݻ�ȡ�ٶ�
	Proc_Perf_Data_IO_Other_Bytes_Per_Sec = 26,

	// ����˽�й�������С
	Proc_Perf_Data_Working_Set_Private = 27,

	// �����������ֵ
	Proc_Perf_Data_Max,
};

//////////////////////////////////////////////////////////////////////////
// ����ϵͳ�еļ�����������
class KPerfNameMgr
{
public:
	KPerfNameMgr();
	~KPerfNameMgr();
	
	LPTSTR	GetName(INT nID);
	INT	GetDataIDByCounterID(INT nCounterNameID);

private:
	BOOL KPerfNameMgr::BuildNameMap();
	void			AddToFixMap(int nID, int nDataID);
private:
	LPTSTR*					m_pNameArray;
	INT						m_nMaxNameID;
	LPTSTR					m_NameBuf;
	map<int, int>			m_FixCounterNameIDToDataID;
	static LPTSTR			m_ProcessDataNames[Proc_Perf_Data_Max+1];
};



//////////////////////////////////////////////////////////////////////////
// һ�����̵�����ͳ������
class KProcessPerfData
{
public:
	KProcessPerfData(DWORD nCpuCount);
	~KProcessPerfData();

	ATL::CString GetProcessName() { return m_strProcName; }
	ATL::CString GetProcessPath() { return m_strPath; }

	BOOL IsSpecialProcess() {
		if (m_nProcessID == 4 || m_nProcessID == 0)
			return TRUE;
		return FALSE;
	}

	DWORD GetProcessTrustMode()
	{
		if (m_nProcessID == 4 || m_nProcessID == 0)
			return 2;//enumTM_Safe
		else
			return m_nTrustMode; 
	}
	DWORD GetProcessID() { return m_nProcessID; }
	ULONGLONG GetMemUsage() { return m_memUsage; }
	ULONGLONG GetIOSpeed()	{ return m_ioSpeed; }

	double GetCpuUsage() {return m_cpuUsage;}
	void   SetCpuUsage(double f) { m_cpuUsage = f;}
	BOOL UpdateData(PPERF_INSTANCE_DEFINITION  PerfInst,
		PPERF_COUNTER_DEFINITION   ProcessCounters[Proc_Perf_Data_Max],
		PPERF_OBJECT_TYPE PerfObj);
	void	SetProcessPath( const LPCTSTR lpwszPath )
	{
		if ( lpwszPath )
		{
			m_strPath = lpwszPath;
		}
	}

	void	SetTrustMode( DWORD	dwTrustMode ){ m_nTrustMode = dwTrustMode; }

	BOOL IsNewCreate() {return m_nNewCreate;}

private:
	DWORD	_GetProcessID(PPERF_INSTANCE_DEFINITION  PerfInst, PPERF_COUNTER_DEFINITION Counter)
	{
		LPBYTE pData = GetCounterData(PerfInst, Counter);
		if (pData) return *((DWORD*)pData);
		return -1;
	}

	ULONGLONG _GetUlonglong(PPERF_INSTANCE_DEFINITION  PerfInst, PPERF_COUNTER_DEFINITION Counter)
	{
		LPBYTE pData = GetCounterData(PerfInst, Counter);
		if (pData) return *((ULONGLONG*)pData);
		return -1;
	}

	ULONGLONG _GetCpuCounter(PPERF_INSTANCE_DEFINITION  PerfInst, PPERF_COUNTER_DEFINITION Counter)
	{
		LPBYTE pData = GetCounterData(PerfInst, Counter);
		if (pData) return *((ULONGLONG*)pData);
		return -1;
	}

private:
	// ����CPUռ����
	double					m_cpuUsage;

	// ����ID
	DWORD					m_nProcessID;

	// ������
	ATL::CString			m_strProcName;

	// ����exe·��
	ATL::CString			m_strPath;

	ULONGLONG				m_timeLast;
	ULONGLONG				m_cpuCounterLast;
	ULONGLONG				m_cpuCounterLastTime;

	// �ڴ�ʹ�ã���ǰ������
	ULONGLONG				m_memUsage;

	// ����IO
	ULONGLONG				m_ioSpeed;
	ULONGLONG				m_ioCounterLast;
	ULONGLONG				m_ioCounterLastTime;
	DWORD					m_nTrustMode;

	DWORD					m_nCpuCount;

	BOOL					m_nNewCreate;
};

//////////////////////////////////////////////////////////////////////////
// �����������ݹ�����
enum Perf_Update_Type
{
	Update_Unknown = -1,
	Update_Only_Process_Perf_Data,
	Update_Perf_Data_And_Calc,
};

class KProcessPerfMgr
{
public:
	KProcessPerfMgr();
	~KProcessPerfMgr();

	HRESULT Init();
	HRESULT UnInit();
	HRESULT Update(Perf_Update_Type ut);
	map<DWORD, KProcessPerfData*>& GetPerfData() {return m_ProcessInfo;}
	double	GetSysMemUsage() {return m_nMemUsage;}
	double  GetSysCpuUsage();
	ULONGLONG GetTotalIo();
	void	PrintProcessInfos();

	DWORD   GetProcessNum() {return m_ProcessInfo.size();}
	BOOL PrintTotalInfo();
private:
	void UpdateSystemCpuAndMem();
	void UpdatePerfData();
	void SwapPerfData();
	void CalcPerfData();
	void CalcOnlyTotalProcessPerfData();
	BOOL GetCurrentPerfData();
	BOOL PrintProcessInfo(PPERF_INSTANCE_DEFINITION PerfInst);
	BOOL PrintSystemInfo();
	BOOL PrintMemInfo();
	BOOL PrintCacheInfo();
	BOOL PrintData(LPCWSTR str);
	BOOL PrintObj(PPERF_OBJECT_TYPE pObj);
	

	void UpdatePerfData(PPERF_OBJECT_TYPE PerfObj);
	BOOL _UpdateCounterInfo(PPERF_OBJECT_TYPE PerfObj);

	KProcessPerfData* _UpdateProcessTotal(PPERF_INSTANCE_DEFINITION PerfInst, PPERF_OBJECT_TYPE PerfObj);
	KProcessPerfData* _UpdateProcessIdle(PPERF_INSTANCE_DEFINITION PerfInst, PPERF_OBJECT_TYPE PerfObj);
	KProcessPerfData* _UpdateProcessData(PPERF_INSTANCE_DEFINITION PerfInst, PPERF_OBJECT_TYPE PerfObj);
	KProcessPerfData* _GetProcessData(DWORD nProcessID);
	DWORD _GetProcessID(PPERF_INSTANCE_DEFINITION PerfInst);
	void	_ClearProcessInfo();

private:
	PPERF_COUNTER_DEFINITION	  m_ProcessCounters[Proc_Perf_Data_Max];
	map<DWORD, KProcessPerfData*> m_ProcessInfo;
	map<DWORD, int>				  m_mapProcessData2CounterID;
	KPerfNameMgr*				  m_pNameMgr;
	KProcessPerfData*			  m_pIdleProcessData;
	KProcessPerfData*			  m_pTotalProcessData;

	Perf_Update_Type			  m_LastUpdateOp;

	PPERF_DATA_BLOCK			  m_PerfDataLast;
	DWORD						  m_nPerfDataSizeLast;

	PPERF_DATA_BLOCK			  m_PerfData;
	DWORD						  m_nPerfDataSize;

	DWORD						  m_nPerfSize;
	double						  m_nMemUsage;
	DWORD						  m_nCpuNum;
};
