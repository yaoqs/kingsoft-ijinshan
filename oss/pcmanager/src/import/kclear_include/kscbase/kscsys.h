#ifndef KSCSYS_INC_
#define KSCSYS_INC_

//////////////////////////////////////////////////////////////////////////

#include "kscbase.h"

//////////////////////////////////////////////////////////////////////////

typedef enum tagWinVersion {
	WINVERSION_PRE_2000 = 0,
	WINVERSION_2000 = 1,
	WINVERSION_XP = 2,
	WINVERSION_SERVER_2003 = 3,
	WINVERSION_VISTA = 4,
	WINVERSION_2008 = 5,
	WINVERSION_WIN7 = 6,
} WinVersion;

// ��ò���ϵͳ�汾
WinVersion KGetWinVersion();

// ���ServicePack�İ汾
void KGetServicePackLevel(int* major, int* minor);

// ���CPU�ĸ���
int KNumberOfProcessors();

// ��������ڴ������
__int64 KAmountOfPhysicalMemory();

// ��ô��̿��е�����
__int64 KAmountOfFreeDiskSpace(const std::wstring& path);

// ��ò���ϵͳ�İ汾��
void KGetOsVersion(unsigned int *major, unsigned int *minor);

// �����ʾ���ĸ���
int KGetDisplayCount();

// �ж���64λ����ϵͳ
BOOL IsX64System();

// �ر�64λ���ļ��ض���
BOOL DisableWow64FsRedirection(void** oldvalue);

// �ָ�64λ���ļ��ض���
BOOL RevertWow64FsRedirection(void* oldvalue);

//////////////////////////////////////////////////////////////////////////

#endif	// KSCSYS_INC_
