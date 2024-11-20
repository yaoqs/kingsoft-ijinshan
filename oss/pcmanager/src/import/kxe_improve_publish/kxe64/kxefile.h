//////////////////////////////////////////////////////////////////////
///		@file		kxefile.h
///		@author		luopeng
///		@date		2008-10-27 09:07:58
///
///		@brief		�ļ����64λ����ϵͳ�ķ�װ,�Ա�֤���еĲ�������
///                 ������ԭ�����ļ�Ŀ¼�ṹ
//////////////////////////////////////////////////////////////////////

#pragma once
#include <Windows.h>
#include <tchar.h>
#include "kxeprocess.h"

/**
 * @defgroup kxefile_wow64_interface KXEngine Architecture File WOW64 Interface
 * @{
 */

typedef 
BOOL
WINAPI
Wow64DisableWow64FsRedirectionFunction(
	__out PVOID *OldValue
	);

typedef 
BOOL
WINAPI
Wow64RevertWow64FsRedirectionFunction(
	__in PVOID OlValue
	);

/**
 * @brief �ر�Wow64�µ��ļ��ض���
 * @param[out] ppVoidValue ���ڴ洢�ڲ�����,��KxEWow64RevertWow64FsRedirection����
 * @attention ��LoadLibrary���ڵ�������,���������KxEWow64DisableWow64FsRedirection,����Ѿ���
 *            ��,��Ҫ����KxEWow64RevertWow64FsRedirection��ԭ,������ܳ��ֲ���Ԥ֪�Ĵ���.
 * @remark �˺���ΪWow64DisableWow64FsRedirection�ļ�ӵ��÷�ʽ,����ֱ������,����WIN32���޷�����
 * @return true �ɹ�, false ʧ��
 */
inline BOOL __stdcall KxEWow64DisableWow64FsRedirection(PVOID* ppVoidValue)
{
	Wow64DisableWow64FsRedirectionFunction* pfnWow64DisableWow64FsRedirection = 
		(Wow64DisableWow64FsRedirectionFunction*)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "Wow64DisableWow64FsRedirection");
	if (pfnWow64DisableWow64FsRedirection == NULL)
	{
		return FALSE;
	}

	return pfnWow64DisableWow64FsRedirection(ppVoidValue);
}

/**
 * @brief ��ԭWow64�µ��ļ��ض���
 * @param[in] pOldValue ���ڴ洢�ڲ�����,��KxEWow64DisableWow64FsRedirection��ȡ
 * @remark �˺���ΪWow64DisableWow64FsRedirection�ļ�ӵ��÷�ʽ,����ֱ������,����WIN32���޷�����
 * @return true �ɹ�, false ʧ��
 */
inline BOOL __stdcall KxEWow64RevertWow64FsRedirection(PVOID pOldValue)
{
	Wow64RevertWow64FsRedirectionFunction* pfnWow64RevertWow64FsRedirection = 
		(Wow64RevertWow64FsRedirectionFunction*)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "Wow64RevertWow64FsRedirection");
	if (pfnWow64RevertWow64FsRedirection == NULL)
	{
		return FALSE;
	}

	return pfnWow64RevertWow64FsRedirection(pOldValue);
}

/**
 * @brief �����ھֲ�������ݹر�Wow64�µ��ļ��ض�����
 */
class KxEFileWow64Guard
{
public:
	KxEFileWow64Guard()
	{
		m_bWow64 = false;
		if (KxEIsWow64Process(GetCurrentProcess(), &m_bWow64) && m_bWow64)
		{
			KxEWow64DisableWow64FsRedirection(&m_pVoidValue);
		}
	}

	~KxEFileWow64Guard()
	{
		if (m_bWow64)
		{
			KxEWow64RevertWow64FsRedirection(m_pVoidValue);
		}
	}

private:
	BOOL m_bWow64;
	PVOID m_pVoidValue;
};


/**
 * @}
 */
