#include "stdafx.h"
#include "SoftMgrUpdateHelper.h"

#define OPEN_VCDIFF 1

#if OPEN_VCDIFF

#include <stlsoft/memory/auto_buffer.hpp>
using namespace stlsoft;
#include <libheader/libheader.h>
#include <softmgr/open_vcdiff/inc/vcdecoder.h>
using namespace open_vcdiff;
#ifdef _DEBUG
#	pragma comment(lib, "../../publish/softmgr/open_vcdiff/lib/vcdcomd.lib")
#	pragma comment(lib, "../../publish/softmgr/open_vcdiff/lib/vcddecd.lib")
#else
#	pragma comment(lib, "../../publish/softmgr/open_vcdiff/lib/vcdcom.lib")
#	pragma comment(lib, "../../publish/softmgr/open_vcdiff/lib/vcddec.lib")
#endif

#endif

#if OPEN_VCDIFF

namespace
{

class Output2File : public OutputStringInterface
{
public:
	Output2File(CAtlTemporaryFile &file) : _file(file), _totalBytes(0) { }

	virtual OutputStringInterface& append(const char* s, size_t n)
	{ _totalBytes += n; DWORD bytes; _file.Write(s, n, &bytes); return *this; }

	virtual void clear() {}

	virtual void push_back(char c) 
	{ _totalBytes += 1; DWORD bytes; _file.Write(&c, 1, &bytes); }

	// �ܹ���Ҫ�������ֽ��� = ��ǰ���յ��ֽ��� + ֪ͨ�������ֽ���
	virtual void ReserveAdditionalBytes(size_t res_arg) {}

	virtual size_t size() const 
	{ ULONGLONG pos = 0; _file.GetPosition(pos); return static_cast<size_t>(pos); }

	size_t GetTotalBytes() const { return _totalBytes; }

private:
	size_t _totalBytes;
	CAtlTemporaryFile &_file;
};

}

#endif
//////////////////////////////////////////////////////////////////////////
CSoftMgrUpdateHelper::CSoftMgrUpdateHelper(void)
{
}

CSoftMgrUpdateHelper::~CSoftMgrUpdateHelper(void)
{
}

HRESULT STDMETHODCALLTYPE CSoftMgrUpdateHelper::Combine( LPCWSTR lpwszDifflib )
{
#if OPEN_VCDIFF
	// ����Delta
	BkDatLibContent delta;
	CDataFileLoader	loader;
	if(!loader.GetLibDatContent(lpwszDifflib, delta)) return ::HRESULT_FROM_WIN32(ERROR_BAD_FORMAT);

	// Ŀ���ļ�·��
	wchar_t szDstPath[MAX_PATH] = {0};
	{
		::GetModuleFileNameW(NULL, szDstPath, MAX_PATH);

		::PathRemoveFileSpecW(szDstPath);
		wcscat_s(szDstPath, MAX_PATH, L"\\KSoft\\Data\\");
		wcscat_s(szDstPath, MAX_PATH, ::PathFindFileNameW(lpwszDifflib));

		//
		//@Issue
		// �����������жϿ�����
		//
		//@Note
		// ��������Ϊ��libname_old_new.dat
		//
		LPWSTR pSep = wcschr(::PathFindFileNameW(szDstPath), L'_');
		if(pSep == NULL) return ::HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);

		pSep[0] = L'\0';
		wcscat_s(szDstPath, MAX_PATH,  L".dat");
	}

	// �����ֵ��ļ�
	CAtlFile dictFile;
	HRESULT hr = dictFile.Create(szDstPath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);
	if(!SUCCEEDED(hr)) return hr;

	ULONGLONG dictSize;
	hr = dictFile.GetSize(dictSize);
	if(!SUCCEEDED(hr)) return hr;

	auto_buffer<char> dict(static_cast<size_t>(dictSize));
	if(dict.empty()) return ::HRESULT_FROM_WIN32(ERROR_OUTOFMEMORY);

	DWORD bytesRead;
	hr = dictFile.Read(dict.data(), static_cast<DWORD>(dict.size()), bytesRead);
	if(!SUCCEEDED(hr)) return hr;

	dictFile.Close();

	// ����Ŀ����ʱ�ļ�
	CAtlTemporaryFile tempTarget;
	hr = tempTarget.Create();
	if(!SUCCEEDED(hr)) return hr;

	//
	// ��ʼ�ϲ�
	//
	//@Note
	// Dict(Source) + Delta => Target
	//
	Output2File output2File(tempTarget);
	{
		VCDiffStreamingDecoder decoder;
		decoder.StartDecoding(&dict[0], dict.size());

		size_t beg = 0;
		size_t end = static_cast<size_t>(delta.nLen);
		LPCSTR pDelta = reinterpret_cast<LPCSTR>(delta.pBuffer);

		while(beg < end)
		{
			static const size_t MAX_THUNK_SIZE = 16*1024;

			size_t size = end - beg;
			if(size > MAX_THUNK_SIZE) size = MAX_THUNK_SIZE;

			if(!decoder.DecodeChunkToInterface(pDelta + beg, size, &output2File))
				return ::HRESULT_FROM_WIN32(ERROR_BAD_FORMAT);

			beg += size;
		}

		if(!decoder.FinishDecoding())
			return ::HRESULT_FROM_WIN32(ERROR_BAD_FORMAT);
	}

	// ����д���ļ���С��������С���ж��Ƿ�ϲ��ɹ�
	ULONGLONG dstSize;
	hr = tempTarget.GetPosition(dstSize);
	if(!SUCCEEDED(hr) || dstSize != output2File.GetTotalBytes()) return ::HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);

	// �ƶ���Ŀ��·��
	return tempTarget.Close(szDstPath);
#else
	return S_OK;
#endif
}

HRESULT STDMETHODCALLTYPE CSoftMgrUpdateHelper::Notify( LPCWSTR lpwszFileName )
{
	return S_OK;
}