#pragma once

#include <list>
#include <string>
#include <utility>
#include "ConewTask.h"
#include "SoftUninstallDef.h"
#include "SoftUninstallEnum.h"
#include <atltime.h>

namespace ksm
{

//
// ��������
//
const LONG TASK_TYPE_INIT = 1;						// ��ʼ������
const LONG TASK_TYPE_DATA_UNINST = 2;				// ���ж������
const LONG TASK_TYPE_RUBBISH_SWEEP = 7;				// ��������ɨ����
const LONG TASK_TYPE_DATA_REFRESH = 8;				// ���ˢ������
const LONG TASK_TYPE_LINK_REFRESH = 9;				// ����ˢ������
const LONG TASK_TYPE_LINK_DESKTOP_REFRESH = 10;		// ����ˢ������
const LONG TASK_TYPE_LINK_START_REFRESSH = 11;		// ��ʼˢ������
const LONG TASK_TYPE_LINK_QUICK_REFRESH = 12;		// ��������ˢ������
const LONG TASK_TYPE_LINK_TRAY_REFRESH = 13;		// ����ˢ������
const LONG TASK_TYPE_LINK_PROCESS_REFRESH = 14;		// ����ˢ������
const LONG TASK_TYPE_DATA_CALC_SPACE = 15;			// �����С����
const LONG TASK_TYPE_DATA_LAST_USE = 16;			// ���ʹ��ʱ������
const LONG TASK_TYPE_RUBBISH_REFRESH = 17;			// ������ˢ������

//
// �������ȼ�
//
const ULONG TASK_PRI_INIT = conew::IBaseTask::TP_Highest;
const ULONG TASK_PRI_DATA_UNINST = conew::IBaseTask::TP_Above_Normal;
const ULONG TASK_PRI_LINK_SWEEP = conew::IBaseTask::TP_Above_Normal;
const ULONG TASK_PRI_RUBBISH_SWEEP = conew::IBaseTask::TP_Above_Normal;
const ULONG TASK_PRI_DATA_REFRESH = conew::IBaseTask::TP_Normal;
const ULONG TASK_PRI_LINK_REFRESH = conew::IBaseTask::TP_Below_Normal;
const ULONG TASK_PRI_RUBBISH_REFRESH = conew::IBaseTask::TP_Below_Normal;
const ULONG TASK_PRI_DATA_CALC_SPACE = conew::IBaseTask::TP_Lowest;
const ULONG TASK_PRI_DATA_LAST_USE = conew::IBaseTask::TP_Lowest;

//
// ǰ������
//
class CSoftUninstall;

//
// �������
//
class CSoftTask : public conew::IBaseTask
{
public:
	CSoftTask(CSoftUninstall *pSoftUninst, LONG type)
		: conew::IBaseTask(type), _pSoftUninst(pSoftUninst) {}

	BOOL IsExited(conew::CTaskMgr *pMgr);

protected:
	CSoftUninstall *_pSoftUninst;
};

//
// ��ʼ������
//
class CSoftInitTask : public CSoftTask
{
public:
	CSoftInitTask(CSoftUninstall *pSoftUninst) 
		: CSoftTask(pSoftUninst, TASK_TYPE_INIT)
	{ SetPriority(TASK_PRI_INIT); }

	virtual BOOL TaskProcess(conew::CTaskMgr *pMgr);

private:
	BOOL CacheIsValid() const;
	BOOL ImportSoftUninstData();
	void UpdateCacheFlag();
};

//
// ��������ɨ����
//
class CSoftRubbishSweep : public CSoftTask
						, public ISoftRubbishSweep
{
public:
	CSoftRubbishSweep(CSoftUninstall *pSoftUnint);
	~CSoftRubbishSweep();

	virtual BOOL TaskProcess(conew::CTaskMgr *pMgr);

	virtual void __stdcall Uninitialize();
	virtual ISoftRubbishEnum* __stdcall RubbishSweepingEnum();
	virtual BOOL __stdcall RubbishSetSweep(PCSoftRubbish pcData);
	virtual BOOL __stdcall RubbishSweep(BOOL recycle);
	virtual BOOL __stdcall RubbishCancelSweep();

private:
	SoftRubbish2List _delList;
	SoftRubbish2List _notifyList;
	CSoftRubbishEnum _enum;

	BOOL _exited;
	BOOL _recycle;
	HANDLE _hEvent;
};

//
// ���ˢ������
//
class CSoftRefreshTask : public CSoftTask
{
public:
	CSoftRefreshTask(CSoftUninstall *pSoftUninst)
		: CSoftTask(pSoftUninst, TASK_TYPE_DATA_REFRESH) 
	{ SetPriority(TASK_PRI_DATA_REFRESH); }

	virtual BOOL TaskProcess(conew::CTaskMgr *pMgr);

private:
	BOOL Need2Refresh();
	void LoadSoftData2Key(SoftData2List &softData2List);
	void DeleteSoftData2(const SoftData2List &softData2List);
};

//
// ����ˢ������
//
class CSoftLinkRefreshTask : public CSoftTask
{
public:
	CSoftLinkRefreshTask(CSoftUninstall *pSoftUninst, 
		LONG taskType, SoftItemAttri linkType)
		: CSoftTask(pSoftUninst, taskType), _linkType(linkType)
	{ SetPriority(TASK_PRI_LINK_REFRESH); }

	virtual BOOL TaskProcess(conew::CTaskMgr *pMgr);

private:
	void ParseLinkList(const WStrList &linkList, WStrList &dirList);
	void ParseDstSoft(WStrList &dirList);
	void EnumTray(WStrList &dirList);
	void EnumProcess(WStrList &dirList);
	std::wstring CanonicalizePath(LPCWSTR pPath);
	BOOL GetProcessPath(DWORD pid, std::wstring &path);

private:
	SoftItemAttri _linkType;
	WStrList _softList;	// Ŀ¼����б�
	SoftRubbish2List _rubbishList;
};

//
// ������ˢ������
//
class CSoftRubbishRefreshTask : public CSoftTask
{
public:
	CSoftRubbishRefreshTask(CSoftUninstall *pSoftUninst)
		: CSoftTask(pSoftUninst, TASK_TYPE_RUBBISH_REFRESH) 
	{ SetPriority(TASK_PRI_RUBBISH_REFRESH); }

	virtual BOOL TaskProcess(conew::CTaskMgr *pMgr);

private:
	void ParseLinkList(const WStrList &linkList, SoftItemAttri type, SoftRubbish2List &rubbish2List);
};

class CSoftCalcSpaceTask : public CSoftTask
{
public:
	CSoftCalcSpaceTask(CSoftUninstall *pSoftUninst)
		: CSoftTask(pSoftUninst, TASK_TYPE_DATA_CALC_SPACE)
	{ SetPriority(TASK_PRI_DATA_CALC_SPACE); }

	virtual BOOL TaskProcess(conew::CTaskMgr *pMgr);

private:
	ULONGLONG CalcSpace(const std::wstring &root);

private:
	SoftData2Iter _it;
	SoftData2List _softData2List;
};

class CSoftLastUseTask : public CSoftTask
{
public:
	CSoftLastUseTask(CSoftUninstall *pSoftUninst)
		: CSoftTask(pSoftUninst, TASK_TYPE_DATA_LAST_USE) 
	{ SetPriority(TASK_PRI_DATA_LAST_USE); }

	virtual BOOL TaskProcess(conew::CTaskMgr *pMgr);

private:
	int	UpdateCount( LPCTSTR pszFile, LPCTSTR pszIni, CTime& tLastUse );
	int GetDayOver( CTime& timeCur, CTime& timeLast );
};

}