#pragma once

#include <safeexam/beikesafeexam.h>
using namespace BKSafeExamItemEx;

class CExamCheckItemsEx
{
public:
	CExamCheckItemsEx(void);
	~CExamCheckItemsEx(void);
	//GUEST�˻�
	int GuestUserIsEnable();
	int SetGuestUserDisable();
	int StartupGuest();
	//������Դ
	int IsHaveShareResource();
	int RemoveAllShareResource();
	int RemoveShareResource(LPCTSTR pszResource);
	int GetShareResourceCount();
	SHARE_RESOURCES EnumAnResources(int nIndex);
	int SetItemShareResourceSafe(LPCTSTR pszRes);
	int SetItemShareResourceUnSafe(LPCTSTR pszRes);
	//Զ������
	int RemoteDesktopIsEnable();
	int SetRemoteDesktopDisable();
	int StartupRemoteDesktop();
	//�����
	int GpeditIsDisable();
	int SetGpeditEnable();
	//������ʾ�����ļ�
	int ShowHideFileIsEnable();
	int ShowHideFileEnable();
	//�޸������ļ����޷���
	int DriverOrDirectoryOpenIsEnable();
	INT DriverOrDirectoryOpenEnable();
private:
	CSimpleArray<SHARE_RESOURCES> m_arrResource;
	SERVICE_STATUS _GetSrvStatus(LPCTSTR pszSrvName);
	BOOL _StartSrv(LPCTSTR pszSrvName);
};
