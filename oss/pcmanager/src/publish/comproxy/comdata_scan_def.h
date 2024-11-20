#pragma once
#include "bkxdx/bkxdx.h"
#include "bkxdx/bkxdx_cursor_bkjson.h"    // use bkjson implements
#include "bkxdx/bkxdx_exchange_c.h"       // support c type exchange
#include "bkxdx/bkxdx_exchange_atl.h"     // support ATL class exchange
#include "common_def.h"




// scan mode
typedef enum
{
    BkScanModeNull			= -1,
    BkScanModeFastScan     = 0,     ///< ����ɨ��
    BkScanModeBootSystemScan,       ///< ����ɨ��
    BkScanModeCheckScan,		    ///< ���ɨ��
    BkScanModeCustomScan,           ///< �Զ���ɨ��
    BkScanModeOnlyCustomScan,       ///< �Զ���ɨ��(�������ڴ�������)
    BKScanModeMoveDiskScan,         ///< �ƶ�����ɨ��
    BkScanModeRightScan,            ///< �Ҽ�ɨ��
    BkScanModeFullScan,             ///< ��ȫɨ��
    BkScanModeIeFix,                ///< IE�޸��õ�ɨ��
    BkScanModeOnlyMemoryScan,       ///< �ڴ�ɨ��
    BkScanModeCacheMemory,          ///< ��װcahce��ɨ��ģʽ
    BkScanModeCacheAutorun,         ///< ��װcache��ɨ��ģʽ
    BkScanModeNum,
};

// scan step
typedef enum 
{
    BkScanStepNull			= -1,
    BkScanStepMemory		= 0,
    BkScanStepAutorun,
    BkScanStepCriticalDir,
    BkScanStepCustomDir,
    BkScanStepAllDisk,
    BkScanStepMoveDisk,
    BkScanStepNum,
};


typedef enum
{
    BkFileTrackNull         = -1,
    BkFileTrackMemory       = 0,
    BkFileTrackAutorun,
    BkFileTrackCriticalDir,
    BkFileTrackNormalDir,
    BkFileTrackNum,
};


// file state��need clean��clean success��clean failed��
typedef enum
{
    BkFileStateNull				= -1,
    //clean���
    BkFileStateNoClean          = 0,
    BkFileStateDeleteSuccess,
    BkFileStateRepairSuccess,
    BkFileStateDeleteFailed,
    BkFileStateRepairFailed,
    BkFileStateDeleteReboot,
    BkFileStateRepairReboot,
    BkFileStateNeedDisable,

    //scan���
    BkFileStateNeedClean        = 1000,
    BkFileStateCannotClean,
    BkFileStateSafe,
    BkFileStateScanFailure,
    BkFileStateDisabled,
};

// virus type
typedef enum
{
    BkVirusTypeNull             = -1,
    BkVirusTypeNeedClean           = 0,
    BkVirusTypeNeedDelete, 
    BkVirusTypeNoOperation, 
    BkVirusTypeNeedDisable,
    BkVirusTypeNum,
};

// request type
typedef enum
{
    BkQueryInfoFileTypeNull			= -1,
    BkQueryInfoFileTypeUnknown		= 0,
    BkQueryInfoFileTypeVirus,
    BkQueryInfoFileTypeSafe,
    BkQueryInfoFileTypeNum,
};

typedef enum
{
    BkScanStateNull         = -1,
    BkScanStateReady        = 0,
    BkScanStateScan,
    BkScanStatePause,
    BkScanStateStop,
    BkScanStateForceStop,
    BkScanStateNum
};



XDX_CLASS_BEGIN(SYSTEMTIME)
    XDX_MEMBER(wYear)
    XDX_MEMBER(wMonth)
    XDX_MEMBER(wDayOfWeek)
    XDX_MEMBER(wDay)
    XDX_MEMBER(wHour)
    XDX_MEMBER(wMinute)
    XDX_MEMBER(wSecond)
    XDX_MEMBER(wMilliseconds)
XDX_CLASS_END

typedef struct _BK_SCAN_INFO 
{
    DWORD	    ScanMode;						//ɨ������
    SYSTEMTIME	StartTime;						//ɨ�迪ʼʱ��
    DWORD		ScanTime;						//ɨ�����ʱ��
    BOOL		ScanFinished;					//ɨ�������־ 
    DWORD		Progress;						//ɨ�����
    int		    Step;							//ɨ�貽�裨1.ϵͳ�ڴ档2.�������3.ϵͳ�ؼ�Ŀ¼��ȫ��Ŀ¼�Լ��Զ���Ŀ¼�ȣ�
    DWORD		ScanFileCount;					//��ɨ���ļ�����
    DWORD		VirusCount;						//ɨ�赽�Ĳ�������
    DWORD		CleanedVirus;					//������Ĳ�������
    DWORD		UnkownCount;					//δ֪�ļ�����
    DWORD		TrustCount;						//�����ļ�����
    DWORD		SafeCount;						//��ȫ�ļ�����
    DWORD		RebootCount;					//��Ҫ�����������
    DWORD		CleanFailedCount;				//���ʧ�ܼ���
    DWORD		QueryFailedCount;				//��ѯʧ�ܼ���
    DWORD		CantCleanVirus;                 //���������������
    CString		LastScanFileName;               //�ϴ�ɨ����ļ�ȫ·��
    int         ScanState;                      //ɨ��״̬
    void    Reset()
    {
        ScanMode = BkScanModeNull;
        ::ZeroMemory( &StartTime, sizeof(StartTime) );
        ScanTime = 0;
        ScanFinished = FALSE;
        Progress = 0;
        Step = BkScanStepNull;
        ScanFileCount = 0;
        VirusCount = 0;
        CleanedVirus = 0;
        UnkownCount = 0;
        TrustCount = 0;
        SafeCount = 0;
        RebootCount = 0;
        CleanFailedCount = 0;
        QueryFailedCount = 0;
        CantCleanVirus = 0;
        LastScanFileName = L"";
        ScanState = BkScanStateReady;
    }

    void    Copy( const struct _BK_SCAN_INFO& src )
    {
        ScanMode = src.ScanMode;
        StartTime = src.StartTime;
        ScanTime = src.ScanTime;
        ScanFinished = src.ScanFinished;
        Progress = src.Progress;
        Step = src.Step;
        ScanFileCount = src.ScanFileCount;
        VirusCount = src.VirusCount;
        CleanedVirus = src.CleanedVirus;
        UnkownCount = src.UnkownCount;
        TrustCount = src.TrustCount;
        SafeCount = src.SafeCount;
        RebootCount = src.RebootCount;
        CleanFailedCount = src.CleanFailedCount;
        QueryFailedCount = src.QueryFailedCount;
        CantCleanVirus = src.CantCleanVirus;
        LastScanFileName = src.LastScanFileName;
        ScanState = src.ScanState;
    }
}BK_SCAN_INFO, *PBK_SCAN_INFO;

XDX_CLASS_BEGIN(BK_SCAN_INFO)
    XDX_MEMBER(ScanMode)
    XDX_MEMBER(StartTime)
    XDX_MEMBER(ScanTime)
    XDX_MEMBER(ScanFinished)
    XDX_MEMBER(Progress)
    XDX_MEMBER(Step)
    XDX_MEMBER(ScanFileCount)
    XDX_MEMBER(VirusCount)
    XDX_MEMBER(CleanedVirus)
    XDX_MEMBER(UnkownCount)
    XDX_MEMBER(TrustCount)
    XDX_MEMBER(SafeCount)
    XDX_MEMBER(RebootCount)
    XDX_MEMBER(CleanFailedCount)
    XDX_MEMBER(QueryFailedCount)
    XDX_MEMBER(CantCleanVirus)
    XDX_MEMBER(LastScanFileName)
    XDX_MEMBER(ScanState)
XDX_CLASS_END

typedef struct _BK_CLEAN_INFO
{
    BK_SCAN_INFO    ScanInfo;                   //��ɱ��Ϣ��������Ҫ�������ݣ�
    DWORD           OperatedVirus;              //��������Ĳ�����
    BOOL	        CleanFinished;              //���������־
    CString	        LastCleanFileName;          //�ϴ�������ļ�ȫ·��

    void    Reset()
    {
        OperatedVirus = 0;
        CleanFinished = 0;
        LastCleanFileName = L"";
        ScanInfo.Reset();
    }

    void    Copy( const struct _BK_CLEAN_INFO& src )
    {
        OperatedVirus = src.OperatedVirus;
        CleanFinished = src.CleanFinished;
        LastCleanFileName = src.LastCleanFileName;
        ScanInfo.Copy( src.ScanInfo );
    }
}BK_CLEAN_INFO, *PBK_CLEAN_INFO;

XDX_CLASS_BEGIN(BK_CLEAN_INFO)
    XDX_MEMBER(ScanInfo)
    XDX_MEMBER(OperatedVirus)
    XDX_MEMBER(CleanFinished)
    XDX_MEMBER(LastCleanFileName)
XDX_CLASS_END

typedef struct _BK_FILE_RESULT
{
    CString		FileName;		                //�ļ���
    DWORD		Type;                           //ɨ��������
    DWORD		Status;			                //�ļ�״̬����Ҫ���������ɹ������ʧ�ܵȣ�
    DWORD		Track;			                //�ļ���Դ���ڴ棬�����ϵͳ�ؼ�Ŀ¼��������ͨ�ļ�ö�ٵȣ�
    DWORD		VirusType;		                //��������
    CString		MD5;			                //�ļ�MD5
    DWORD		CRC;			                //�ļ�CRC
    CString		VirusName;		                //������
    DWORD       SecLevel;                       //�ļ���ȫ�ȼ�,���淵��
    BOOL        bHashed;                        //�Ƿ���hash,FALSE��ʾ�ļ��д���
}BK_FILE_RESULT, *PBK_FILE_RESULT;

XDX_CLASS_BEGIN(BK_FILE_RESULT)
    XDX_MEMBER(FileName)
    XDX_MEMBER(Type)
    XDX_MEMBER(Status)
    XDX_MEMBER(Track)
    XDX_MEMBER(VirusType)
    XDX_MEMBER(MD5)
    XDX_MEMBER(CRC)
    XDX_MEMBER(VirusName)
    XDX_MEMBER(SecLevel)
    XDX_MEMBER(bHashed)
XDX_CLASS_END

typedef struct _BK_FILE_INFO
{
    DWORD			Index;                      //���
    BK_FILE_RESULT	FileResult;                 //�ļ���Ϣ��
}BK_FILE_INFO, *PBK_FILE_INFO;

XDX_CLASS_BEGIN(BK_FILE_INFO)
    XDX_MEMBER(Index)
    XDX_MEMBER(FileResult)
XDX_CLASS_END



//////////////////////////////////////////////////////////////////////////
// ɨ�����
#define SCAN_POLICY_AVE                         0x00000001		///< �Ƿ�ʹ�ñ�������
#define SCAN_POLICY_CLOUD                       0x00000002		///< �Ƿ�������ѯ
#define SCAN_POLICY_CACHE                       0x00000004		///< ʹ��cache
#define SCAN_POLICY_BLACKCACHE                  0x00000008		///< �Ƿ�ʹ�úڻ���
#define SCAN_POLICY_RESERVED_1                  0x00000010      ///< �Ƿ��Ǽ��ģʽ,���ģʽ��ʹ�ýϿ��ɨ������
#define SCAN_POLICY_FORCE_BOOTDELETE            0x00000020      ///< ����Ҫɾ���ļ�ʱ,ǿ��������ɾ��
//#define SCAN_POLICY_DISABLE_OPEN_FILE_FOR_HASH  0x00000040      ///< ��ֹ���ļ�����hash
//#define SCAN_POLICY_DISABLE_WRITE_CACHE         0x00000080      ///< ��ֹд����
//#define SCAN_POLICY_DISABLE_WINTRUST            0x00000100      ///< ��ֹ��֤����ǩ��
//#define SCAN_POLICY_M_ARCHIVED					0x00000200		///< [�����]ɨ��ʱ�ὫSettings.dwScanningModeǿ��������KAV_O_M_ARCHIVED KAV_O_M_MAILBASES KAV_O_M_MAILPLAIN���������
#define SCAN_PLOICY_FOR_RESCAN                  0x00000400      ///< ��ɨ����:��ֹ��ѯ��������,ǿ������

#define SCAN_POLICY_STD_SCAN        ( SCAN_POLICY_CLOUD | SCAN_POLICY_CACHE )

#define SCAN_POLICY_																		
///< ����Ҫɾ���ļ�ʱ,ǿ��������ɾ��
///< ��ֹ���ļ�����hash
///< ��ֹ��֤����ǩ��
///< ��ֹд����

																								
																								
																								
typedef enum																					
{																								
    CleanFailedNull         = -1,
    CleanFailedDefOp        = 0,
    CleanFailedDelete,
    CleanFailedNum          
};

#define MAX_SCAN_SIZE 0x1400000

typedef enum
{
    BkScanFileTypeNull      = -1,
    BkScanFileTypeAllFile   = 0,
    BkScanFileTypeExe       = 1,
    BkScanFileTypeNum,
};

typedef struct _BK_SCAN_SETTING
{
    DWORD   dwSize;
    UINT64  ScanFileSize;                       ///< [=ULONG_MAX]                   ɨ���ļ��Ĵ�С����
    int     nScanFileType;                        //�Ƿ��������,��Σ���ļ���
    BOOL	bScanArchive;                        //�Ƿ�ɨ��ѹ����
    BOOL	bAutoClean;                          //�Ƿ���ɨ������з��ֲ����Զ����	
    int     CleanFailedOp;                      //���ʧ�ܴ���
    DWORD   nScanPolicy;                        //ɨ����ԣ�1.�黺��, 2.���ļ�����, 3. �Ʋ�ɱ���� ��		
    BOOL    bQuarantineVirus;                    //[=TRUE]�Ƿ���벡��
    void    Reset()
    {
        dwSize = sizeof( struct _BK_SCAN_SETTING );
        ScanFileSize    = MAX_SCAN_SIZE;
        nScanFileType   = BkScanFileTypeAllFile;
        bScanArchive    = FALSE;
        bAutoClean      = FALSE;
        CleanFailedOp   = CleanFailedDefOp;
        nScanPolicy     = SCAN_POLICY_STD_SCAN;
        bQuarantineVirus = TRUE;
    }

}BK_SCAN_SETTING, *PBK_SCAN_SETTING;

XDX_CLASS_BEGIN(BK_SCAN_SETTING)  
    XDX_MEMBER(dwSize)
    XDX_MEMBER(ScanFileSize)
    XDX_MEMBER(nScanFileType)
    XDX_MEMBER(bScanArchive)
    XDX_MEMBER(bAutoClean)
    XDX_MEMBER(CleanFailedOp)
    XDX_MEMBER(nScanPolicy)
    XDX_MEMBER(bQuarantineVirus)
XDX_CLASS_END

typedef struct _BK_FORCE_CLEAN_DETAIL
{
    CString strVirusName;
    DWORD   dwSecLevel;
    DWORD   dwScanPolicy;
    BOOL    bNeedUpload;
    DWORD   dwTrack;
}BK_FORCE_CLEAN_DETAIL, *PBK_FORCE_CLEAN_DETAIL;

XDX_CLASS_BEGIN(BK_FORCE_CLEAN_DETAIL)  
    XDX_MEMBER(strVirusName)
    XDX_MEMBER(dwSecLevel)
    XDX_MEMBER(dwScanPolicy)
    XDX_MEMBER(bNeedUpload)
    XDX_MEMBER(dwTrack)
XDX_CLASS_END

typedef struct _BK_SCAN_ADDITIONAL_PATH
{
    CString strFilePath;
    BOOL    bRecursive;
}BK_SCAN_ADDITIONAL_PATH, *PBK_SCAN_ADDITIONAL_PATH;

XDX_CLASS_BEGIN(BK_SCAN_ADDITIONAL_PATH)  
    XDX_MEMBER(strFilePath)
    XDX_MEMBER(bRecursive)
XDX_CLASS_END