#pragma once
#include <atlbase.h>
#include <atlpath.h>
#include <atlsecurity.h>
#include <shlobj.h>
#include "winmod/winpath.h"

#define INSTALL_KEY L"SOFTWARE\\KSafe"
#define APP_PATH    L"Install Path"
#define DATA_PATH   L"DataPath"
#define QUARA_PATH  L"QuarantinePath"


#define DATA_DIR    L"Data"
#define CFG_DIR     L"Cfg"
#define QURAR_DIR  L"KSafeQuarantine"
#define CACHE_DIR  L"Cache"
#define LOG_DIR    L"AppData"
#define TMP_DIR    L"Temp"
#define AVS_DIR     L"KEng"
#define HOTFIX_DIR	L"Hotfix"

#define APPDATA_DIR L"KSafe"
#define RECYCLE_DIR L"KSafeRecycle"

class   CAppPath
{
public:
    static  CAppPath& Instance()
    {
        static  CAppPath _ins;
        return  _ins;
    }

public:
    // return S_FALSE, Ŀ¼�Ѵ���
    // return S_OK, Ŀ¼���´���
    // return E_XX, ʧ��
    HRESULT CreateFullPath(
        LPCWSTR lpszFileName, 
        DWORD dwFileAttribute = FILE_ATTRIBUTE_NORMAL
        )
    {
        HRESULT hr = S_FALSE;
        CString strPath = lpszFileName;

        if (!strPath.IsEmpty() && L'\\' != strPath[strPath.GetLength() - 1])
        {
            strPath.AppendChar(L'\\');
        }


        int nPos = strPath.Find(L'\\');
        while (-1 != nPos)
        {
            CString strParent    = strPath.Left(nPos);
            DWORD   dwFileAttrib = ::GetFileAttributes(strParent);
            if (INVALID_FILE_ATTRIBUTES == dwFileAttrib)
            {
                BOOL bRet = ::CreateDirectory(strParent, NULL);
                if (!bRet)
                    return GetLastError() ? AtlHresultFromLastError() : E_FAIL;

                ::SetFileAttributes( strParent, dwFileAttribute );
                hr = S_OK;
            }

            nPos = strPath.Find(_T('\\'), nPos + 1);
        }

        return hr;
    }


public:
    HRESULT GetLeidianAppdataFolderPath( CString& strPath )
    {
        CPath   path;
        WCHAR   wszBuffer[ MAX_PATH + 1 ] = { 0 };

        HRESULT hr = ::SHGetFolderPath(
            NULL,
            CSIDL_COMMON_APPDATA | CSIDL_FLAG_CREATE,
            NULL,
            SHGFP_TYPE_CURRENT,
            wszBuffer
            );
        if ( FAILED( hr ) )
        {
            goto Exit0;
        }

        path.m_strPath = wszBuffer;
        path.Append( APPDATA_DIR );

        strPath = path.m_strPath;
Exit0:
        return hr;
    }

    HRESULT GetLeidianAppPath( CString& strPath, BOOL bSelfModePath = TRUE )
    {
        if ( bSelfModePath )
        {
            return GetPath( strPath, APP_PATH, NULL, ( HMODULE )&__ImageBase );
        }
        else
        {
            return GetPath( strPath, APP_PATH, NULL, NULL );
        }
    }

	HRESULT GetLeidianHotFixPath(CString& strPath,BOOL bCreate=TRUE, BOOL bSelfModePath = TRUE)
	{
		HRESULT hr = S_OK;
		CPath   path;

		hr = GetLeidianAppPath( path.m_strPath, bSelfModePath );
		if ( SUCCEEDED( hr ) )
		{
			path.Append( HOTFIX_DIR );
			strPath = path.m_strPath;

			if ( bCreate )
			{
				hr = CreateFullPath( strPath );
				if ( S_OK == hr )
				{
					hr = FixFilePrivilege( strPath );
					if ( FAILED( hr ) )
					{
						hr = S_FALSE;
					}
				}
			}
		}

		return hr;
	}

    HRESULT GetLeidianDataPath( CString& strPath, BOOL bCreate = FALSE, BOOL bSelfModePath = TRUE )
    {
        HRESULT hr = S_OK;

        if ( bSelfModePath )
        {
            hr = GetPath( strPath, DATA_PATH, DATA_DIR, ( HMODULE )&__ImageBase );
        }
        else
        {
            hr = GetPath( strPath, DATA_PATH, DATA_DIR, NULL );
        }

        if ( SUCCEEDED( hr ) && bCreate )
        {
            hr = CreateFullPath( strPath );
            if ( S_OK == hr )
            {
                hr = FixFilePrivilege( strPath );
                if ( FAILED( hr ) )
                {
                    hr = S_FALSE;
                }
            }
        }

        return hr;
    }

    HRESULT GetLeidianQuarantinePath( CString& strPath )
    {
        CPath   path;
        HRESULT hr = S_OK;

        hr = GetLeidianAppdataFolderPath( path.m_strPath );
        if ( FAILED( hr ) )
        {
            goto Exit0;
        }

        path.RemoveFileSpec();
        path.Append( QURAR_DIR );

        strPath = path.m_strPath;
Exit0:
        return hr;
    }

    // ��������Ŀ¼���ҷ��ظ���Ŀ¼
    HRESULT CreateLeidianQuarantinePath( CString& strPath )
    {
        HRESULT hr = S_OK;

        hr = GetLeidianQuarantinePath( strPath );
        if ( FAILED( hr ) )
        {
            return hr;
        }

		if ( !ATLPath::FileExists(strPath) )
		{
			hr = CreateFullPath( strPath, FILE_ATTRIBUTE_HIDDEN );
			if ( FAILED( hr ) )
			{
				return hr;
			}

			if ( S_OK == hr )
			{
				hr = FixFilePrivilege( strPath, FILE_GENERIC_READ, FILE_EXECUTE );
				if ( FAILED( hr ) )
				{
					hr = S_FALSE;
				}
			}
		}

        return hr;
    }

    HRESULT GetLeidianCfgPath( CString& strPath, BOOL bCreate = FALSE, BOOL bSelfModePath = TRUE )
    {
        HRESULT hr = S_OK;
        CPath   path;

        hr = GetLeidianAppPath( path.m_strPath, bSelfModePath );
        if ( SUCCEEDED( hr ) )
        {
            path.Append( CFG_DIR );
            strPath = path.m_strPath;

            if ( bCreate )
            {
                hr = CreateFullPath( strPath );
                if ( S_OK == hr )
                {
                    hr = FixFilePrivilege( strPath );
                    if ( FAILED( hr ) )
                    {
                        hr = S_FALSE;
                    }
                }
            }
        }

        return hr;
    }

    HRESULT GetLeidianCachePath( CString& strPath, BOOL bCreate = FALSE )
    {
        HRESULT hr = S_OK;
        CPath   path;

        hr = GetLeidianAppdataFolderPath( path.m_strPath );
        if ( SUCCEEDED( hr ) )
        {
            path.Append( CACHE_DIR );
            strPath = path.m_strPath;
            if ( bCreate )
            {
                hr = CreateFullPath( strPath );
                if ( S_OK == hr )
                {
                    hr = FixFilePrivilege( strPath );
                    if ( FAILED( hr ) )
                    {
                        hr = S_FALSE;
                    }
                }
            }
        }

        return hr;
    }

    HRESULT GetLeidianLogPath( CString& strPath, BOOL bCreate = TRUE, BOOL bSelfModePath = TRUE )
    {
        HRESULT hr = S_OK;
        CPath   path;

        hr = GetLeidianAppPath( path.m_strPath, bSelfModePath );
        if ( SUCCEEDED( hr ) )
        {
            path.Append( LOG_DIR );
            strPath = path.m_strPath;

            if ( bCreate )
            {
                hr = CreateFullPath( strPath );
                if ( S_OK == hr )
                {
                    hr = FixFilePrivilege( strPath );
                    if ( FAILED( hr ) )
                    {
                        hr = S_FALSE;
                    }
                }
            }
        }

        return hr;
    }

    HRESULT GetLeidianTempPath( CString& strPath, BOOL bCreate = FALSE, BOOL bSelfModePath = TRUE )
    {
        HRESULT hr = S_OK;
        CPath   path;

        hr = GetLeidianAppPath( path.m_strPath, bSelfModePath );
        if ( SUCCEEDED( hr ) )
        {
            path.Append( TMP_DIR );
            strPath = path.m_strPath;

            if ( bCreate )
            {
                hr = CreateFullPath( strPath );
                if ( S_OK == hr )
                {
                    hr = FixFilePrivilege( strPath );
                    if ( FAILED( hr ) )
                    {
                        hr = S_FALSE;
                    }
                }
            }
        }

        return hr;
    }

    HRESULT GetLeidianScanTempPath( CString& strPath, BOOL bCreate )
    {
        return GetLeidianTempPath( strPath, bCreate );
    }

    HRESULT GetLeidianAvsPath( CString& strPath, BOOL bCreate = TRUE, BOOL bSelfModePath = TRUE )
    {
        HRESULT hr = S_OK;
        CPath   path;

        hr = GetLeidianAppPath( path.m_strPath, bSelfModePath );
        if ( SUCCEEDED( hr ) )
        {
            path.Append( AVS_DIR );
            strPath = path.m_strPath;

            if ( bCreate )
            {
                hr = CreateFullPath( strPath );
                if ( S_OK == hr )
                {
                    hr = FixFilePrivilege( strPath );
                    if ( FAILED( hr ) )
                    {
                        hr = S_FALSE;
                    }
                }
            }
        }

        return hr;
    }

    HRESULT GetLeidianRecyclePath( const CString& strReference, CString& strPath )
    {
        CPath   path( strReference );

        path.StripToRoot();
        path.Append( RECYCLE_DIR );

        strPath = path.m_strPath;
        return S_OK;
    }

    HRESULT CreateLeidianRecyclePath( const CString& strReference, CString& strPath )
    {
        HRESULT hr = S_OK;

        hr = GetLeidianRecyclePath( strReference, strPath );
        if ( FAILED( hr ) )
        {
            return hr;
        }

        if( !ATLPath::FileExists( strPath ) )
        {
            hr = ::CreateDirectory( strPath, NULL );
            if ( FAILED( hr ) )
            {
                return hr;
            }

            SetFileAttributes( strPath, FILE_ATTRIBUTE_HIDDEN );

            hr = FixFilePrivilege( strPath, FILE_GENERIC_READ, FILE_EXECUTE );
            if ( FAILED( hr ) )
            {
                hr = S_FALSE;
            }
        }


        return hr;
    }

    HRESULT FixFilePrivilege(
        LPCWSTR lpszFileName, 
        DWORD dwAllowACE = FILE_ALL_ACCESS, 
        DWORD dwDeniedACE = 0 
        )
    {
        HRESULT hr = S_FALSE;

        if ( IsVistaOrLater() )
        {
            return S_OK;
        }

        try
        {
            CDacl dacl;

            BOOL bRet = ATL::AtlGetDacl(lpszFileName, SE_FILE_OBJECT, &dacl);
            if (!bRet)
                return GetLastError() ? AtlHresultFromLastError() : E_FAIL;

            dacl.RemoveAllAces();

            // ����users�û�
            bRet = dacl.AddAllowedAce( Sids::Users(), dwAllowACE, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE );
            if (!bRet)
                return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
            // �ܾ�everyone
            bRet = dacl.AddDeniedAce( Sids::World(), dwDeniedACE, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE );
            if (!bRet)
                return GetLastError() ? AtlHresultFromLastError() : E_FAIL;

            bRet = ATL::AtlSetDacl(lpszFileName, SE_FILE_OBJECT, dacl);
            if (!bRet)
                return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


            return S_OK;
        }
        catch (...)
        {
            hr = S_FALSE;
        }

        return hr;
    }
private:
    HRESULT GetPath( 
        CString& strPath, 
        LPCWSTR lpwszValueName, 
        LPCTSTR lpwszDefaultDirName,
        HMODULE hBaseModule // ָ��һ����Ʒ�ľ��������ȡ��Ʒ��װ·��
        )
    {
        LONG    lret = 0;
        DWORD   dwRet = 0;
        CRegKey reg;
        HRESULT hr = S_OK;
        CPath   path;
        WCHAR   wszBuffer[ MAX_PATH + 1 ] = { 0 };

        if ( NULL == lpwszValueName )
        {
            hr = E_INVALIDARG;
            goto Exit0;
        }

        lret = reg.Open( HKEY_LOCAL_MACHINE, INSTALL_KEY, KEY_READ );
        if ( ERROR_SUCCESS == lret )
        {
            dwRet = MAX_PATH;
            lret = reg.QueryStringValue( 
                lpwszValueName,
                wszBuffer,
                &dwRet
                );
            if ( ERROR_SUCCESS == lret )
            {
                wszBuffer[ MAX_PATH ] = L'\0';
                path.m_strPath = wszBuffer;

                goto Exit0;            
            }
        }

        // local path
        dwRet = ::GetModuleFileName( 
            hBaseModule, 
            wszBuffer, 
            MAX_PATH
            );
        if ( 0 == dwRet )
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            goto Exit0;
        }

        path.m_strPath = wszBuffer;
        path.RemoveFileSpec();
        if ( lpwszDefaultDirName )
        {
            path.Append( lpwszDefaultDirName );
        }
Exit0:
        if ( SUCCEEDED( hr ) )
        {
            strPath = path.m_strPath;
        }
        return hr;
    }

    inline BOOL IsVistaOrLater()
    {
        OSVERSIONINFO osInfo;
        osInfo.dwOSVersionInfoSize = sizeof(osInfo);
        ::GetVersionEx(&osInfo);

        return ( 0 <= ( ( int )( osInfo.dwMajorVersion - 6 ) ) );
    }

};
