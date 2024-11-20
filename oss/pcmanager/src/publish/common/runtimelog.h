#pragma once
#include "winmod/winpath.h"
#include "winmod/winlogfile.h"
#include "utility.h"

#define BKSVC_LOG_FILE_NAME         L"KSafeSvc.log"        ///< bksafesvc ����־

#define BKSVC_CFG_INI_FILE          L"KSafeSvc.local.ini"  ///< bksafesvc ��Ӧ�ó��������ļ���
#define BKSVC_CFG_INI_APP_LOG       L"log"                  ///< ��־�����ö�

#define BKSVC_CFG_INI_KEY_LEVEL     L"level"                ///< ��־����

#ifdef _DEBUG
#define BKSVC_DEFAULT_LOG_LEVEL     WINMOD_LLVL_TRACE       ///< ����ģʽ�����������־
#else
#define BKSVC_DEFAULT_LOG_LEVEL     WINMOD_LLVL_INFO        ///< Ĭ�ϵ����ڼ���
#endif

class   CRunTimeLog
{
public:
    static HRESULT WriteLog(DWORD dwLogLevel, LPCWSTR lpszFormat, ...)
    {
        WinMod::CWinLogFile& hLogFile = GetLogFile();

        if (!hLogFile.IsLevelEnabled(dwLogLevel))
            return S_FALSE;

        va_list args;
        va_start(args, lpszFormat);
        hLogFile.LogFormatV(dwLogLevel, lpszFormat, args);
        va_end(args);
        return S_OK;
    }

    static WinMod::CWinLogFile& GetLogFile()
    {
        static WinMod::CWinLogFile s_hLogFile;
        
        return s_hLogFile;
    }

    static HRESULT InitLogFile()
    {
        WinMod::CWinLogFile& hLogFile = GetLogFile();


        if (hLogFile && INVALID_HANDLE_VALUE != hLogFile)
            return S_FALSE;




        // ��ȡ����
        WinMod::CWinPath pathConfigFile;
        HRESULT hr = CAppPath::Instance().GetLeidianCfgPath(pathConfigFile.m_strPath, TRUE);
        if (FAILED(hr))
            return hr;
        pathConfigFile.Append(BKSVC_CFG_INI_FILE);



        // ��ȡ��־����
        DWORD dwLevel = ::GetPrivateProfileInt(
            BKSVC_CFG_INI_APP_LOG,
            BKSVC_CFG_INI_KEY_LEVEL,
            BKSVC_DEFAULT_LOG_LEVEL,
            pathConfigFile.m_strPath);




        // ����־
        WinMod::CWinPath pathLogFile;
        hr = CAppPath::Instance().GetLeidianLogPath(pathLogFile.m_strPath, TRUE);
        if (FAILED(hr))
            return hr;
        pathLogFile.Append(BKSVC_LOG_FILE_NAME);


        hr = hLogFile.CreateAsLogFile(pathLogFile);
        if (FAILED(hr))
            return hr;


        // ������־����
        hLogFile.SetLogLevel(dwLevel);
        return S_OK;
    }


//    static HRESULT  WriteLog(const TCHAR *format, ...)
//    {
//        HRESULT hr = S_OK;
//#ifdef _DEBUG
//        WinMod::CWinPath    logName;
//        WinMod::CWinPath    logpath;
//        LPCWSTR             lpwszFileName = NULL;
//        CString strTrace;
//        va_list args;
//        SYSTEMTIME          localtime;
//
//        GetLocalTime( &localtime );
//
//        CTime               curtime(localtime);
//
//        if ( 0 == logName.GetModuleFileName( NULL ) )
//        {
//            hr = HRESULT_FROM_WIN32( GetLastError() );
//            goto Exit0;
//        }
//
//        lpwszFileName = WinMod::CWinPathApi::FindFileName( logName );
//        if ( !lpwszFileName || !*lpwszFileName )
//        {
//            hr = E_FAIL;
//            goto Exit0;
//        }
//
//        hr = CAppPath::Instance().GetLeidianLogPath( logpath.m_strPath );
//        if ( FAILED( hr ) )
//        {
//            goto Exit0;
//        }
//
//        logpath.Append( L"runtimelog" );
//        CAppPath::Instance().CreateFullPath( logpath );
//        logpath.Append( lpwszFileName );
//        logpath.m_strPath.AppendFormat( L".%s.log", curtime.Format( L"%Y-%m-%d" ) );
//
//        va_start(args, format);
//        strTrace.FormatV(format, args);
//        va_end(args);
//
//        {
//            FILE*   fp = NULL;
//
//            fp = _wfopen( logpath, L"a+" );
//            if ( fp )
//            {
//                fwprintf( fp, L"[%s %s]%s\n", lpwszFileName, curtime.Format( L"%H:%M:%S" ), strTrace );
//                fclose( fp );
//            }
//        }
//Exit0:
//#endif
//        
//        return hr;
//    }
};