//
// dummyz@126.com

#ifndef _VERIFY_FILE_INC_
#define _VERIFY_FILE_INC_

HANDLE  AcquireVerifyHandle();
void	ReleaseVerifyHandle(HANDLE hHandle);

// ���� 0 ʧ��
// ���� 1 ͨ�� win ǩ��
// ���� 2 ͨ�� cat ǩ�� 
int		VerifyFile(HANDLE hHandle, LPCTSTR lpPath);
BOOL	IsVerifiedFile(LPCTSTR lpPath);

#endif /* _VERIFY_FILE_INC_ */
