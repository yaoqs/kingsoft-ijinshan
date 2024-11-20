#pragma  once

#include <libheader/libupdhelper.h>
#include <com_s/com/comobject.h>
#include <libheader/libdiff.h>
#include "kprocesslibloader.h"
#include "kprocesslib/ccf/KPath.h"
using namespace Kingsoft::Test::CCF::IO;

class KProcessLibUpdate:public IUpdateHelper
{
public:
	KProcessLibUpdate(){}
	~KProcessLibUpdate(){}

	SCOM_BEGIN_COM_MAP(KProcessLibUpdate)
		SCOM_INTERFACE_ENTRY(IUpdateHelper)
	SCOM_END_COM_MAP()


	virtual HRESULT STDMETHODCALLTYPE Combine( LPCWSTR lpwszDifflib ) 
	{
		// У��DiffLib ,DiffLib�ļ���Ӧ����kproclib��ͷ
		if (KPath::GetFileName(lpwszDifflib).find(STR_KSAFE_PROCESS_LIB_DAT_NAME_PREFIX) != 0)
		{
			return ::HRESULT_FROM_WIN32(ERROR_FILE_INVALID);
		}

		CString libPath = KProcessLibLoader::GetDefaultLibPath();
		CString tempLibPath = libPath + L".0";

		// vs2005�Ե���������ϸ�Debug�汾����Ҫ����,����Assertʧ��
		#define _HAS_ITERATOR_DEBUGGING				0
		HRESULT hResult = LibDiffCombine((LPCWSTR)libPath, lpwszDifflib, (LPCWSTR)tempLibPath);
		if (hResult != S_OK)
		{
			return hResult;
		}

		if (!::MoveFileEx(tempLibPath, libPath, MOVEFILE_REPLACE_EXISTING))
		{
			return ::HRESULT_FROM_WIN32(GetLastError());
		}

		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Notify( LPCWSTR lpwszFileName ) 
	{
		return S_FALSE;
	}
};