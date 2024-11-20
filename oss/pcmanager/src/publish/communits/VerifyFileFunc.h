
#pragma once

#include <winmod/wintrustverifier.h>
#include "communits/FileVersionInfo.h"
using namespace WinMod;

#define KINGSOFT_SINGER_INFO				TEXT("Zhuhai  Kingsoft Software Co.,Ltd")
#define KINGSOFT_SINGER_INFO2				TEXT("Kingsoft Security Co.,Ltd")
#define KENIU_SINGER_INFO					TEXT("Keniu Network Technology (Beijing) Co., Ltd.")
#define BEIKE_SINGER_INFO					TEXT("Beike Internet Security Technology Co.,Ltd")

#ifndef _H_INCLUDE_VERIFY_FILE_FUNC
#define _H_INCLUDE_VERIFY_FILE_FUNC

class CVerifyFileFunc
{
public:
	static CVerifyFileFunc* GetPtr()
	{
		static CVerifyFileFunc ver;
		return &ver;
	}
	~CVerifyFileFunc(){}
public:
	int CheckKingSoftFileSigner(LPCTSTR pszFile)
	{
		return CVerifyFileFunc::GetPtr()->FileSignerIsValid(pszFile, m_arrKingSoftSinger);
	}

	//��ȡ���ǩ�����ַ���
	int GetFileSignerStr(LPCTSTR pszFile, CString& strSingerStr)
	{
		int nRet = -1;

		CWinTrustVerifier verifile;
		CWinTrustSignerInfoChain SingerInfo;
		verifile.TryLoadDll();
		DWORD dwWinTrust = 0;
		HRESULT hr = S_OK;
		strSingerStr.Empty();
		dwWinTrust = verifile.VerifyFile(pszFile, &SingerInfo);

		if (dwWinTrust <= 0x0000FFFF)
			hr = AtlHresultFromWin32(dwWinTrust);
		else
			hr = dwWinTrust;

		if ( SUCCEEDED( hr ) )
		{
			strSingerStr = SingerInfo.m_chain.GetHead().m_strIsserName;
			nRet = 0;
		}

		return nRet;
	}

	int FileSignerIsValid(LPCTSTR pszFile, CAtlArray<CString>& arrSinger)
	{
		int nRet = -1;
		CWinTrustVerifier verifile;
		CWinTrustSignerInfoChain SingerInfo;
		verifile.TryLoadDll();
		DWORD dwWinTrust = 0, nCount = arrSinger.GetCount();
		HRESULT hr = S_OK;
		dwWinTrust = verifile.VerifyFile(pszFile, &SingerInfo);

		if (dwWinTrust <= 0x0000FFFF)
			hr = AtlHresultFromWin32(dwWinTrust);
		else
			hr = dwWinTrust;

		if ( SUCCEEDED( hr ) )
		{
			if ( !SingerInfo.m_chain.IsEmpty() )
			{
				for ( int i = 0; i < nCount; i++)
				{
					if (0 == SingerInfo.m_chain.GetHead().m_strIsserName.Compare(arrSinger[i]))
					{//�����֤���幫˾��ǩ�����ڸ�����ǩ���б��������һ��ƥ���Ͼ���ɹ���
						nRet = 0;
						break;
					}
				}

				//�������֤���幫˾��ǩ�����ߵ���һ���Ѿ����ǳɹ���
				if (0 == nCount)
					nRet = 0;
			}
		}

		return nRet;
	}

	LPCTSTR GetKSafeProductVersion()
	{
		static TCHAR szVersion[MAX_PATH];
		static BOOL bInited = FALSE;

		if ( !bInited )
		{
			bInited = TRUE;

			CString strVersion;
			CString strFilePath;

			CAppPath::Instance().GetLeidianAppPath(strFilePath);
			strFilePath += _T("\\ksafever.dll");

			CFileVersionInfo fileVer;
			if ( fileVer.Create(strFilePath) )
			{
				_tcsncpy(szVersion, fileVer.GetProductVersion(), MAX_PATH);
				szVersion[MAX_PATH - 1] = 0;
			}
		}

		return szVersion;
	}
private:
	CVerifyFileFunc(){
		//��Ҫ��֤ǩ�����б�
		m_arrKingSoftSinger.Add(KINGSOFT_SINGER_INFO);
		m_arrKingSoftSinger.Add(KINGSOFT_SINGER_INFO2);
		m_arrKingSoftSinger.Add(BEIKE_SINGER_INFO);
		m_arrKingSoftSinger.Add(KENIU_SINGER_INFO);

	}
	CAtlArray<CString> m_arrKingSoftSinger;
};

#endif