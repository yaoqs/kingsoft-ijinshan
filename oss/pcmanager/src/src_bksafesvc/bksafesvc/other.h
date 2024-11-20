#pragma once
#include "comproxy\comdata_scan_def.h"
#include "skylark2\bklog.h"




inline VOID InitFileResult( BK_FILE_RESULT& FileResult )
{
    FileResult.FileName     = L"";                         //�ļ���
    FileResult.Type         = BkQueryInfoFileTypeNull;     //ɨ��������
    FileResult.Status       = BkFileStateNull;			   //�ļ�״̬����Ҫ���������ɹ������ʧ�ܵȣ�
    FileResult.Track        = BkFileTrackNull;			   //��������ʱ���ڵ�ɨ�貽�裨�ڴ棬������ȣ�
    FileResult.VirusType    = BkVirusTypeNull;		       //��������
    FileResult.MD5          = L"";                         //�ļ�MD5
    FileResult.CRC          = 0;			               //�ļ�CRC
    FileResult.VirusName    = L"";                         //������ 
    FileResult.SecLevel     = 0;
    FileResult.bHashed      = FALSE;
}


struct BK_FILE_RESULT_EX
{
    CString		FileName;		                //�ļ���
    DWORD		Type;                           //ɨ��������
    DWORD		Status;			                //�ļ�״̬����Ҫ���������ɹ������ʧ�ܵȣ�
    DWORD		Track;			                //�ļ���Դ���ڴ棬�����ϵͳ�ؼ�Ŀ¼��������ͨ�ļ�ö�ٵȣ�
    DWORD		VirusType;		                //��������
    BYTE		MD5[16];			            //�ļ�MD5
    DWORD		CRC;			                //�ļ�CRC
    CString		VirusName;		                //������
    //һ�±�����Ŀǰֻ�ڱ�����־ʱ�õ���
    UINT32          uScanResult;        ///< ɨ����,ȡֵΪBKAVE_SCAN_RESULT_xxx
    UINT32          uCleanResult;       ///< ������,ȡֵΪBKAVE_CLEAN_RESULT_xxx
    UINT32          uSecLevel;          ///< �ļ���ȫ�ȼ�,ȡֵΪSLPTL_LEVEL_MARK___xxx
    BOOLEAN         bHashed;            ///< �Ƿ���hash���
    BOOLEAN         bNeedUpload;        ///< �Ƿ���Ҫ�ϴ�
};

inline VOID InitFileResultEx( BK_FILE_RESULT_EX& FileResultEx )
{
    FileResultEx.FileName     = L"";                         //�ļ���
    FileResultEx.Type         = BkQueryInfoFileTypeNull;     //ɨ��������
    FileResultEx.Status       = BkFileStateNull;			   //�ļ�״̬����Ҫ���������ɹ������ʧ�ܵȣ�
    FileResultEx.Track        = BkFileTrackNull;			   //��������ʱ���ڵ�ɨ�貽�裨�ڴ棬������ȣ�
    FileResultEx.VirusType    = BkVirusTypeNull;		       //��������
    ::ZeroMemory( FileResultEx.MD5, sizeof(FileResultEx.MD5) );                       //�ļ�MD5
    FileResultEx.CRC          = 0;			               //�ļ�CRC
    FileResultEx.VirusName    = L"";                         //������ 
    
    FileResultEx.bHashed      = FALSE;
    FileResultEx.uCleanResult = 0;
    FileResultEx.uScanResult  = 0;
    FileResultEx.uSecLevel    = 0;
}

class CMD5
{
public:
	static void GetStrMd5( const BYTE md5[], CString& StrMd5 )
	{
		StrMd5.Format(
			L"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
			md5[0],  md5[1],  md5[2],  md5[3], 
			md5[4],  md5[5],  md5[6],  md5[7], 
			md5[8],  md5[9],  md5[10], md5[11], 
			md5[12], md5[13], md5[14], md5[15] );
	}
};


class CCrc
{
public:
	static void GetStrCrc( DWORD dwCRC32, CString& StrCrc )
	{
		StrCrc.Format(
			L"%08x", 
			StrCrc );
	}
};

class COther
{
	public:
		static DWORD GetVirusType( UINT32 ScanResult );
		static DWORD GetScanResult( DWORD SrcResult );
        static DWORD GetCleanResult( DWORD SrcResult );
        static int TranslateScanStepToTrack( int ScanStep );
        static int TranslateScanStep( int ScanStep );
        static void TranslateFileResultExToScanLog( const BK_FILE_RESULT_EX& FileResultEx, Skylark::BKENG_SCAN_LOG& ScanLog );
        static BOOL GetQQInstallDir( CString& InstallDir  );
        static BOOL GetMsnReceiveDir( CAtlArray<CString>& ReceiveDirArray );
};

class CDiskCheck
{
public:
    static BOOL IsDriveDeviceAccessible( WCHAR cRoot );
};


class CSetting
{
public:
    static void TranslateSetting( const BK_SCAN_SETTING& ScanSet, Skylark::BKENG_SETTINGS& BkengSet );


    static DWORD   ReadDWORDValue(LPCWSTR lpszFile, LPCWSTR lpszApp, LPCWSTR lpszKey, DWORD dwDefaultValue);
    static void    WriteDWORDValue(LPCWSTR lpszFile, LPCWSTR lpszApp, LPCWSTR lpszKey, DWORD dwValue);

};


#define BUFSIZ  512
class COtherUserCurReg
{
public:
    static HRESULT GetOtherUsrCurReg( CAtlArray<HKEY>& OtherUserCurReg )
    {
        OtherUserCurReg.RemoveAll();

        WCHAR szSID[BUFSIZ] = {0};
        DWORD dwIndex = 0;
        while (ERROR_SUCCESS == ::RegEnumKey(HKEY_USERS, dwIndex, szSID, _countof(szSID) - 1))
        {
            szSID[_countof(szSID) - 1]  = L'\0';
            HKEY hUser = NULL;
            LONG lRet = ::RegOpenKeyEx(HKEY_USERS, szSID, 0, KEY_ALL_ACCESS, &hUser);
            if (ERROR_SUCCESS == lRet)
            {
                OtherUserCurReg.Add(hUser);
            }

            ++dwIndex;
        }
        return S_OK;
    }
};