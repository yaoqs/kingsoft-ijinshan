//=============================================================================
/**
* @file GetTokenUtil.h
* @brief 
* @author qiuruifeng <qiuruifeng@kingsoft.com>
* @date 2008-5-22   16:37
*/
//=============================================================================
#ifndef GETTOKENUTIL_H
#define GETTOKENUTIL_H

#include <Windows.h>

/**
 * @brief ͨ������ӳ������ȡ����id
 * @remark û�п��Ƕ��û���¼�����,�����Ҫ����,����ͨ���ý���id��ȡtoken,Ȼ���ȡsession��Ϣ
 * @param[in] lpName ����ӳ����
 * @param[out] dwPid ����Ľ���id
 * @return �ɹ�����TURE,ʧ�ܷ���FALSE
 */
BOOL GetPidByName(LPTSTR lpName, DWORD& dwPid);

// �õ�Active Session ID. �ɹ��򷵻�TRUE, whereas return FALSE if failed.
BOOL GetActiveSessionID(DWORD& sessionId);

// ��ĳ��Session�еõ�һ��pid. �ɹ��򷵻�TRUE,ʧ���򷵻�FALSE
BOOL GetOnePidFromSession(DWORD& dwPid,  DWORD dwSessionId);

/**
 * @brief ��pid�л�ȡtoken������
 * @remark 
 * @param[in] dwPid 
 * @param[out] hToken 
 * @return 
 */
BOOL GetPrimaryTokenFromPid(DWORD dwPid, HANDLE& hToken);

/**
 * @brief ��pid�л�ȡtoken������
 * @remark 
 * @param[in] dwPid 
 * @param[out] hToken 
 * @return 
 */
BOOL GetImpersonationTokenFromPid(DWORD dwPid, HANDLE& hToken);

#endif //GETTOKENUTIL_H
