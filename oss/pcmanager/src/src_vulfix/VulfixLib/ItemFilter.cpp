#include "StdAfx.h"
#include "ItemFilter.h"
#include "Utils.h"
#include "LeakDB.h"
#include "EnvUtils.h"
#include "HotfixUtils.h"

inline BOOL IsUserDefinedKB(INT nKBID)
{
	return 	nKBID>=660000 && nKBID<669999;
}

// ���������������Ѱ�װ 1, ��������δ��װ 0, ������ -1
inline BOOL TestIfInstalled( TOptionCondition & condition, int nKBID )
{
	if(!condition.m_strExpInstalled.IsEmpty())
		return EvaluateCondition( condition.m_strExpInstalled );
	return FALSE;
}

void DBFilterBase::Init(DWORD dwFlags)
{
}

///////
// XP 
void DBFilterXp::Init(DWORD dwFlags)
{
	DBFilterBase::Init(dwFlags);
	m_updateInfo.Init(dwFlags);
}

BOOL DBFilterXp::IsInstallable(TOptionCondition & condition, int nKBID, int &nType, DWORD &dwLang)
{
	nType = VTYPE_WINDOWS;
	return EvaluateCondition( condition.m_strCondition );
}

BOOL DBFilterXp::IsInstalled( TOptionCondition &condition, int nKBID )
{
	if( IsUserDefinedKB(nKBID) )
		return TestIfInstalled(condition, nKBID);
	else
		return m_updateInfo.IsUpdateInstalled(nKBID);
}

BOOL DBFilterXp::IsKBInstalled(int nKBID)
{
	return m_updateInfo.IsUpdateInstalled(nKBID);
}

M_KBInfo & DBFilterXp::GetInstalledInfo()
{
	return m_updateInfo.GetInstalledInfo();
}

///////
// vista 
void DBFilterVista::Init(DWORD dwFlags)
{
	autolock<CThreadGuard> _lk(m_guard);
	
	DBFilterBase::Init(dwFlags);
	m_bUseInterface = VULSCAN_USE_IUPDATE & dwFlags;
	m_bExpressScan = VULSCAN_EXPRESS_SCAN & dwFlags;
	m_bCanceled = FALSE;
	if(m_bUseInterface)
	{
		CWUAUpdateInfoVistaLater &wuaInfo = singleton<CWUAUpdateInfoVistaLater>::Instance();
		wuaInfo.Init( dwFlags );
	}
	else
	{
		CWUAUpdateInfoVistaLaterReg &wuaInfo = singleton<CWUAUpdateInfoVistaLaterReg>::Instance();
		wuaInfo.Init( dwFlags );
	}
}

BOOL DBFilterVista::IsInstallable( TOptionCondition & condition, int nKBID, int &nType, DWORD &dwLang )
{
	nType = VTYPE_WINDOWS;
	
	CWUAUpdateInfoVistaLater &wuaInfoInterface = singleton<CWUAUpdateInfoVistaLater>::Instance();	
	
	// ����ɨ��||�ӿڿ��õĻ�, ʹ�ýӿ�
	if(m_bUseInterface 
		|| wuaInfoInterface.IsIUpdateResultAvailable() )
	{
		// �����Զ���KB, ��ʹ�ýӿ�, Ҳʹ�ü������ 
		if(IsUserDefinedKB( nKBID) )
			return EvaluateCondition( condition.m_strCondition );
		else
			return wuaInfoInterface.IsUpdateAvailable( nKBID );
	}
	else
	{
		// NOTE : δ��������Vista up �Ķ����費�ܰ�װ, ����ͨ��ע��� 
		if( condition.m_strCondition.IsEmpty() )
			return FALSE;
		return EvaluateCondition( condition.m_strCondition );
	}
}

BOOL DBFilterVista::IsInstalled( TOptionCondition &condition, int nKBID )
{
	nKBID = GetRealKBID( nKBID );
	CWUAUpdateInfoVistaLater &wuaInfoInterface = singleton<CWUAUpdateInfoVistaLater>::Instance();
	if(m_bUseInterface || wuaInfoInterface.IsIUpdateResultAvailable() )
	{
		if(IsUserDefinedKB( nKBID) )
			return TestIfInstalled(condition, nKBID);
		else
			return wuaInfoInterface.IsUpdateInstalled( nKBID );
	}
	else
	{
		if(IsUserDefinedKB( nKBID) )
			return TestIfInstalled(condition, nKBID);
		else
		{
			CWUAUpdateInfoVistaLaterReg &wuaInfo = singleton<CWUAUpdateInfoVistaLaterReg>::Instance();
			return wuaInfo.IsUpdateInstalled( nKBID );
		}
	}
}

BOOL DBFilterVista::IsKBInstalled( int nKBID )
{
	nKBID = GetRealKBID( nKBID );
	CWUAUpdateInfoVistaLater &wuaInfoInterface = singleton<CWUAUpdateInfoVistaLater>::Instance();
	if(m_bUseInterface|| wuaInfoInterface.IsIUpdateResultAvailable())
	{
		return wuaInfoInterface.IsUpdateInstalled( nKBID );
	}
	else
	{
		CWUAUpdateInfoVistaLaterReg &wuaInfo = singleton<CWUAUpdateInfoVistaLaterReg>::Instance();
		return wuaInfo.IsUpdateInstalled( nKBID );
	}
}

BOOL DBFilterVista::WaitComplete()
{
	if(m_bUseInterface)
	{
		CWUAUpdateInfoVistaLater &wuaInfo = singleton<CWUAUpdateInfoVistaLater>::Instance();
		while(!wuaInfo.IsCompleted() && !m_bCanceled)
		{
			Sleep(100);
		}
		return wuaInfo.IsCompleted();
	}
	return TRUE;
}

void DBFilterVista::Cancel()
{
	m_bCanceled = TRUE;
}

M_KBInfo & DBFilterVista::GetInstalledInfo()
{
	CWUAUpdateInfoVistaLater &wuaInfoInterface = singleton<CWUAUpdateInfoVistaLater>::Instance();
	if(m_bUseInterface|| wuaInfoInterface.IsIUpdateResultAvailable())
	{
		return wuaInfoInterface.GetInstalledInfo();
	}
	else
	{
		CWUAUpdateInfoVistaLaterReg &wuaInfo = singleton<CWUAUpdateInfoVistaLaterReg>::Instance();
		return wuaInfo.GetInstalledInfo();
	}
}