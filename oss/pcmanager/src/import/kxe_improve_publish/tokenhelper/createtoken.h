//=============================================================================
/**
* @file CreateToken.h
* @brief 
* @author qiuruifeng <qiuruifeng@kingsoft.com>
* @date 2008-5-20   10:17
*/
//=============================================================================
#ifndef CREATETOKEN_H
#define CREATETOKEN_H

#include <windows.h>
#include <tchar.h>

/**
 * @brief �����й���ԱȨ�޵�token,��ǰ����һ��Ҫ��SeCreateToken��Ȩ
 * @remark ���û�й���Ա�ʺŵ�token,��ô���Բο��ڲ�ʵ��,���о��Ĺ���sid�������Ϣ
 * @param[in] hBasicToken ����token(��Ҫ�ǹ���Ա�˺�,��),��Ӹ�token��sid���ʹ����sid
 * @param[in] pTokenPrivileges token����Ȩ����,���Ϊ����ô��hBasicToken�п���
 * @param[in] pszUserName ����Ա�ʻ���,���Ϊ��,��ô���hBasicToken�л�ȡ��Ӧsid
 * @return �ɹ����طǿյ�token,ʧ�ܷ��ؿ�token
 */
HANDLE CreateAdminToken(HANDLE hBasicToken, PTOKEN_PRIVILEGES pTokenPrivileges, LPCTSTR pszUserName, int* pnErrCode);

/**
* @brief �����й���ԱȨ�޵�token,��ǰ����һ��Ҫ��SeCreateToken��Ȩ
* @remark ���û�й���Ա�ʺŵ�token,��ô���Բο��ڲ�ʵ��,���о��Ĺ���sid�������Ϣ
* @param[in] hBasicToken ����token(��Ҫ�ǹ���Ա�˺�,��),��Ӹ�token��sid���ʹ����sid
* @param[in] pTokenPrivileges token����Ȩ����,���Ϊ����ô��hBasicToken�п���
* @param[in] pUserSid ����Ա�ʻ���sid,���Ϊ��,��ô���hBasicToken�л�ȡ��Ӧsid
* @return �ɹ����طǿյ�token,ʧ�ܷ��ؿ�token
*/
HANDLE CreateAdminTokenWithSid(HANDLE hBasicToken, PTOKEN_PRIVILEGES pTokenPrivileges, PSID pUserSid, int* pnErrCode);

/**
 * @brief ��ȡϵͳ�汾
 * @remark 
 * @param[out] dwPlatformId ƽ̨id
 * @param[out] dwMajor ��汾
 * @param[out] dwMinor С�汾
 * @return �ɹ�����TURE,ʧ�ܷ���FALSE
 */
BOOL GetWindowsVersion(DWORD& dwPlatformId, DWORD& dwMajor, DWORD& dwMinor);

/**
 * @brief ��token�л�ȡsession id
 * @remark 
 * @param[in] hToken ��������
 * @param[out] pdwSession session idָ��
 * @return �ɹ�����TURE,ʧ�ܷ���FALSE
 */
BOOL GetSessionIdFromToken(HANDLE hToken, DWORD* pdwSession);

/**
 * @brief ��ָ����token����Ȩ�޻򽵵�Ȩ��
 * @remark ����������ҪTOKEN_ADJUST_PRIVILEGES����Ȩ��
 * @param[in] hToken ��������
 * @param[in] szPrivName ��Ȩ��
 * @param[in] bEnable �����򽵵�Ȩ�ޱ�ʶ
 * @return �ɹ�����TURE,ʧ�ܷ���FALSE
 */
BOOL EnableTokenPrivilege(HANDLE hToken, LPCTSTR szPrivName, BOOL bEnable = TRUE);

/**
 * @brief ��ָ���Ľ�������Ȩ�޻򽵵�Ȩ��
 * @remark 
 * @param[in] hProcess ���̾��
 * @param[in] szPrivName ��Ȩ��
 * @param[in] bEnable �����򽵵�Ȩ�ޱ�ʶ
 * @return �ɹ�����TURE,ʧ�ܷ���FALSE
 */
BOOL EnableProcessPrivilege(HANDLE hProcess, LPCTSTR szPrivName, BOOL bEnable = TRUE);

/**
 * @brief ����ǰ���������򽵵�Ȩ��
 * @remark 
 * @param szPrivName ��Ȩ��
 * @param bEnable �����򽵵�Ȩ�ޱ�ʶ
 * @return �ɹ�����TURE,ʧ�ܷ���FALSE
 */
BOOL EnableCurrentProcessPrivilege(LPCTSTR szPrivName, BOOL bEnable = TRUE);

/**
 * @brief �жϵ�ǰsid�Ƿ���vista�����ڱ�ʶ��Ȩ�޵���sid
 * @remark 
 * @param[in] pSid �����sid
 * @return ������򷵻�TRUE
 */
BOOL IsLowMandatoryLevelSid(PSID pSid);

/**
* @brief �жϵ�ǰsid�Ƿ���vista�����ڱ�ʶ��Ȩ�޵���sid
* @remark 
* @param[in] pSid �����sid
* @return ������򷵻�TRUE
*/
BOOL IsMediumMandatoryLevelSid(PSID pSid);

/**
* @brief �жϵ�ǰsid�Ƿ���vista�����ڱ�ʶ��Ȩ�޵���sid
* @remark 
* @param[in] pSid �����sid
* @return ������򷵻�TRUE
*/
BOOL IsHighMandatoryLevelSid(PSID pSid);

/**
* @brief �жϵ�ǰsid�Ƿ���vista�����ڱ�ʶϵͳȨ�޵���sid
* @remark 
* @param[in] pSid �����sid
* @return ������򷵻�TRUE
*/
BOOL IsSystemMandatoryLevelSid(PSID pSid);

/**
 * @brief �жϵ�ǰsid�Ƿ��ǹ���Ա��sid
 * @remark 
 * @param[in] pSid �����sid
 * @return ������򷵻�TRUE
 */
BOOL IsAdministratorGroupSid(PSID pSid);

BOOL IsUsersGroupSid(PSID pSid);

BOOL IsSystemUserSid(PSID pSid);
/**
* @brief ��ȡtoken��Ϣ
* @remark 
* @param[in] hToken ��������
* @param[in] Tic ��Ϣ����
* @param[out] pTokenInfoOut ��Ϣ����,�����ڲ�����ռ�,��Ҫʹ��FreeTokenInfo����
* @param[out] pdwOutSize ������ݵĴ�С
* @return �ɹ�����TURE,ʧ�ܷ���FALSE
*/
BOOL GetTokenInfo(HANDLE hToken, TOKEN_INFORMATION_CLASS Tic, PVOID *pTokenInfoOut, DWORD* pdwOutSize);

/**
 * @brief 
 * @remark ����GetTokenInfo���������
 * @param[in] pTokenInfo GetTokenInfo��������ݵ�ָ��
 */
void FreeTokenInfo(PVOID pTokenInfo);

inline BOOL IsNt4System(DWORD dwPlatformId, DWORD dwMajor, DWORD dwMinor)
{
	dwMinor;
	return (dwPlatformId == VER_PLATFORM_WIN32_NT && 4 == dwMajor);
}

inline BOOL IsWin2kSystem(DWORD dwPlatformId, DWORD dwMajor, DWORD dwMinor)
{
	return (dwPlatformId == VER_PLATFORM_WIN32_NT && 5 == dwMajor && 0 == dwMinor);
}

inline BOOL IsWinXpSystem(DWORD dwPlatformId, DWORD dwMajor, DWORD dwMinor)
{
	return (dwPlatformId == VER_PLATFORM_WIN32_NT && 5 == dwMajor && 1 == dwMinor);
}

inline BOOL IsWin2k3System(DWORD dwPlatformId, DWORD dwMajor, DWORD dwMinor)
{
	return (dwPlatformId == VER_PLATFORM_WIN32_NT && 5 == dwMajor && 2 == dwMinor);
}

inline BOOL IsVistaSystem(DWORD dwPlatformId, DWORD dwMajor, DWORD dwMinor)
{
	dwMinor;
	return (dwPlatformId == VER_PLATFORM_WIN32_NT && 6 == dwMajor);
}

#endif //CREATETOKEN_H