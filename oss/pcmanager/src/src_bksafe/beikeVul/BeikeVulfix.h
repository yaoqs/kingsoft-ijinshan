#pragma once
#undef __BKRES_RC
#include "resource.h"
//#include "bkwinres.rc2"
#include "bkres/bkres.h"
#include "bkwinresource.h"
#include "vulfix/Vulfix.h"

enum {
	WMH_INIT_SCAN = WM_USER + 0x100,
	WMH_SCAN_START,
	WMH_SCAN_DONE,
	WMH_REPAIR_DONE,
	WMH_SCAN_FIXED_BEGIN,
	WMH_SCAN_FIXED_DONE,
	WMH_SCAN_SOFT_BEGIN,
	WMH_SCAN_SOFT_DONE,
	WMH_VULFIX_BASE = WM_USER + 0x200,

	WMH_LISTEX_HOVERCHANGED = WM_USER + 0x300,
	WMH_LISTEX_LINK
};

enum TScanSoftState{
	SCANSTATE_DISPLAY,
	SCANSTATE_SCANNING,
	SCANSTATE_REPAIRING,
};

enum TRepairSubState{
	REPAIRSTATE_ING,
	REPAIRSTATE_DONE,
	REPAIRSTATE_DONE_PART,
	REPAIRSTATE_FAIL,
};


enum TSoftVulStatus
{
	VUL_UPDATE,
	VUL_COM_DISABLED,
	VUL_DISABLE_COM,
};

static LPCTSTR SoftVulStatusDesc[] = 
{
	_T("��������"),
	_T("�Ѿ��������COM"),
	_T("�����COM"),
};

static LPCTSTR SoftVulStatusOP[] = 
{
	_T("���ذ�װ�����"),
	_T("����COM"),
	_T("����COM"),
};

enum TIMER_TYPE
{
	TIMER_RUNNING = 1,
};