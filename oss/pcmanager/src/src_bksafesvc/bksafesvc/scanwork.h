#pragma once
#define USE_OPENSSL_H
#include "bkengex.h"
#include "bklogex.h"
#include "backupex.h"
#include "svccallback.h"
#include "scancontext.h"
#include "common/whitelist.h"

class CScanWork :
    public Skylark::IBKEngineCallback,
    public IEnumOperation
{
public:
    CScanWork();
    ~CScanWork();


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /**
    * @brief    ��ʼ��ɨ���߼�ʵ��
    */
    HRESULT Initialize( DWORD CliendPid, IScanFileCallBack* pSvcCallback );

    /**
    * @brief    ����ʼ��ɨ���߼�ʵ��
    */
    HRESULT Uninitialize();

    /**
    *@brief     ��ʼ��ɱ
    *@param     ScanMod Ϊɨ�����ͣ������١��ؼ�λ�ò�ɱ��ȫ�̡��Զ���ȣ�
    *@param     CustomPath  ���Ӳ���������ɹ��Զ���ɨ�����Զ���Ŀ¼��
    */
    HRESULT Scan(
        /* [in ] */int ScanMod,
        /* [in ] */BOOL bBackGround,
        /* [in ] */const CAtlArray<CString>& CustomParam );

    HRESULT Scan2( 
        int ScanMod, 
        BOOL bBackGround, 
        const CAtlArray<BK_SCAN_ADDITIONAL_PATH>& CustomParam 
        );
    /**
    *@brief     ��ͣ��ɱ
    */
    HRESULT  Pause(
        );

    /**
    *@brief     ��ͣ��ɱ
    */
    HRESULT Resume(
        );

    /**
    *@brief     ֹͣ��ɱ
    */
    HRESULT Stop(
        );


    HRESULT QueryScanStep( int ScanMode, CAtlArray<int>& ScanStep );
    /**
    *@brief     ��ѯ��ɱ��Ϣ
    *@param     ScanInfo ���ز�ɱ��Ϣ
    */
    HRESULT QueryScanInfo(
        /* [out ] */BK_SCAN_INFO& ScanInfo 
        );

    /**
    *@brief		��ѯ�����Ϣ
    *@param     CleanInfo ���������Ϣ
    */
    HRESULT QueryCleanInfo(
        /* [out ] */BK_CLEAN_INFO& CleanInfo
        );

    /**
    *@brief		��ѯ�ļ���Ϣ
    *@param     Type     �ļ����ͣ�δ֪��������
    *@param     Index    �ļ�����
    *@param     FileInfo �����ļ���Ϣ
    */
    HRESULT QueryFileInfo(
        /* [in  ] */int       Type,
        /* [in  ] */DWORD       Index,
        /* [out ] */BK_FILE_INFO& FileInfo
        );

    /**
    *@brief		����ļ�
    *@param     IndexArr	���������ļ���������
    */
    HRESULT Clean(
        /* [in  ] */const  CAtlArray<DWORD>& fileIndex
        );


    /**
    *@brief		��ѯ�ϴ�ɨ����Ϣ
    *@param		ScanInfo    ��ɱ��Ϣ
    */
    HRESULT  QueryLastScanInfo(
        /* [out ] */BK_SCAN_INFO&	ScanInfo
        );

    /**
    *@brief		����ɨ������
    *@param		
    */
    HRESULT  SetScanSetting(
        /* [in  ] */const BK_SCAN_SETTING&  Setting
        );


    /**
    *@brief		��ȡɨ��ѡ��
    *@param		Setting ɨ��ѡ��
    */
    HRESULT  GetScanSetting(
        /* [out ] */BK_SCAN_SETTING&  Setting 
        );
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////


protected:
    ////////////////////////////////////////////////////////////////////////
    /**
    * @brief        ɨ���ļ�ǰ����
    * @param[in]    lpszFilePath    ԭʼ�ļ�·��
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */
    virtual HRESULT STDMETHODCALLTYPE BeforeScanFile(
        /* [in ] */ LPCWSTR             lpszFilePath,
        /* [in ] */ void*               pvFlag);


    /**
    * @brief        ɨ���ļ������
    * @param[in]    lpszFilePath    ԭʼ�ļ�·��
    * @param[in]    pResult         ��ǰ�ļ���ɨ����
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */
    virtual HRESULT STDMETHODCALLTYPE AfterScanFile(
        /* [in ] */ LPCWSTR             lpszFilePath,
        /* [in ] */ const Skylark::BKENG_RESULT* pResult,
        /* [in ] */ void*               pvFlag);


    /**
    * @brief        ����ļ�ǰ���� (�����Զ����ʱ,������ô˻ص�)
    * @param[in]    lpszFilePath    ԭʼ�ļ�·��
    * @param[in]    pResult         ��ǰ�ļ���ɨ����
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */
    virtual HRESULT STDMETHODCALLTYPE BeforeCleanFile(
        /* [in ] */ LPCWSTR             lpszFilePath,
        /* [in ] */ const Skylark::BKENG_RESULT* pResult,
        /* [in ] */ void*               pvFlag);


    /**
    * @brief        ����ļ������ (�����Զ����ʱ,������ô˻ص�)
    * @param[in]    lpszFilePath    ԭʼ�ļ�·��
    * @param[in]    pResult         ��ǰ�ļ���������
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */
    virtual HRESULT STDMETHODCALLTYPE AfterCleanFile(
        /* [in ] */ LPCWSTR             lpszFilePath,
        /* [in ] */ const Skylark::BKENG_RESULT* pResult,
        /* [in ] */ void*               pvFlag);


    /**
    * @brief        ɨ������з���ϸ�� (�����Ϣ,ѹ�����еĲ�����...)
    * @param[in]    lpszVirtualPath ɨ����������·��
    * @param[in]    pResult         ɨ������ɨ����
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */ 
    virtual HRESULT STDMETHODCALLTYPE OnScanDetail(
        /* [in ] */ LPCWSTR             lpszVirtualPath,
        /* [in ] */ const Skylark::BKENG_RESULT* pResult,
        /* [in ] */ void*               pvFlag);



    virtual HRESULT STDMETHODCALLTYPE OnIdle();


    /**
    * @brief        ����ʱ�ص�
    * @param[in]    hrFinishCode    ɨ�践�صĴ�����
    */ 
    virtual HRESULT STDMETHODCALLTYPE OnFinish(
        HRESULT             hrFinishCode);

    //ö�ٻص�
    virtual HRESULT OperateFile( const CString& FilePath, const WIN32_FIND_DATAW* pFindData, DWORD dwScanMask, void*   pvFlag,  PVOID pParam );
    virtual BOOL    IsExitEnumWork();

    ////////////////////////////////////////////////////////////////////////


private:

    static unsigned int __stdcall EnumScanFileProc( void * lpParameter )
    {
        _ASSERT( NULL != lpParameter );

        CScanWork * pThis = static_cast<CScanWork*>(lpParameter);
        pThis->_EnumFileWork();

        return 0;
    }

    static unsigned int __stdcall CleanVirusFileProc( void * lpParameter )
    {
        _ASSERT( NULL != lpParameter );

        CScanWork * pThis = static_cast<CScanWork*>(lpParameter);
        pThis->_CleanWork();

        return 0;
    }

    //���ݳ�ʼ����
    HRESULT     _ResetForScan();
    HRESULT     _ResetForClean();

    //ɨ�� ���
    HRESULT     _ScanWork();
    HRESULT     _CleanWork();


    //ɨ��ʱ���ļ�ö��
    DWORD       _EnumFileWork(); 

    //�˳�clean�̡߳�
    VOID        _ExitCleanVirusThread();
    //�˳�ö��
    VOID        _ExitEnumFileThread();
    //ֹͣɨ��
    VOID        _StopScan();
    //�ظ���ͣ
    HRESULT        _Resume();
    //����ɨ��ʱ��
    VOID        _SetScanTime();
    //����ɨ�����
    VOID        _SetScanProgress();

    VOID        _SaveLastScanInfo();

    //�ص�����
    BOOL        _IsFindFile( CAtlArray<BK_FILE_RESULT_EX>& FileArray, LPCWSTR pszFilePath );
    VOID        _UpdateScanResult( LPCWSTR  lpszFilePath, const Skylark::BKENG_RESULT* pResult, void* pvFlag );
    VOID        _UpdateScanInfo( LPCWSTR  lpszFilePath, const Skylark::BKENG_RESULT* pResult, void* pvFlag );
    VOID        _UpdateCleanResult( LPCWSTR  lpszFilePath, const Skylark::BKENG_RESULT* pResult, void* pvFlag );
    VOID        _UpdateCleanInfo( LPCWSTR  lpszFilePath, const Skylark::BKENG_RESULT* pResult, void* pvFlag, UINT32 uOldCleanResult = BKENG_CLEAN_RESULT_NO_OP);

    //��¼ɨ����־
    VOID        _RecordScanLog();

private:
    typedef CComAutoCriticalSection                     CObjLock;
    typedef CComCritSecLock<CComAutoCriticalSection>    CObjGuard;

    ///////
    CObjLock    m_LockData;
    CAtlArray<BK_FILE_RESULT_EX>   m_VirusFileArray;
    CAtlArray<BK_FILE_RESULT_EX>   m_UnknownFileArray;
    BK_CLEAN_INFO				   m_CleanInfo;
    /////// 
    CObjLock                    m_LockOther;
    BOOL				        m_bScanEnableEntry;
    ///////
    //����
    BOOL                        m_bCommitFinish;
    CScanProgress2              m_ScanProgress;
    //ɨ�貽��
    CScanStep                   m_ScanStep;
    //ɨ��ʱ��
    DWORD                       m_StartTimeForScanTime;
    DWORD                       m_BeginPauseTime;
    DWORD                       m_PauseTime;
    //ɨ��ģʽ
    DWORD                       m_ScanMode;

    //�������
    CAtlArray<DWORD>            m_CleanIndexArray;
    //����
    BK_SCAN_SETTING			    m_Setting;

    //�Զ������
    CAtlArray<CString>          m_CustomParam;
    CAtlArray<BK_SCAN_ADDITIONAL_PATH>  m_CustomParam2;
    BOOL                        m_bScan2;
    //clean �ж�
    BOOL                        m_bClean;

    //ö���߳�
    HANDLE				        m_hEnumFileThread;
    CEvent				        m_ExitEnumFileEvent;

    //ɨ������
    CBkScanEngEx                m_ScanEngEx;

    //ɨ��������
    CScanContext                m_ScanContext;

    //clean��������
    CEngineLiteEx               m_CleanVirusOperation;
    //clean�߳�
    HANDLE                      m_hCleanThread;
    CEvent                      m_ExitCleanEvent;

    //��¼��־�ӿ�
    CBkScanLog                  m_ScanLogWriter;

    //���벡���ӿ�
    CBackupVirusFile            m_BackupVirusFile;

    //����ص�
    IScanFileCallBack*               m_pSvcCallback;
    CAtlMap<CString, int>       m_whiteMap;
};





class CBkMultiFileScan :
    public Skylark::IBKEngineCallback
{
public:
    CBkMultiFileScan();
    ~CBkMultiFileScan();


    HRESULT  Initialize(
        );


    HRESULT  Uninitialize(
        );

    HRESULT Stop();

    HRESULT  Scan( 
        const CAtlArray<CString>& FilePathArray,
        CAtlArray<BK_FILE_RESULT>& FileResultArray
        );

    HRESULT Scan2(
        const CAtlArray<CString>& FilePathArray,
        CAtlArray<BK_FILE_RESULT>& FileResultArray,
        CAtlArray<size_t>& unKnownIndex
        );

    HRESULT ScanHash( 
        const CAtlArray<CString>& hashArray, 
        CAtlArray<BK_FILE_RESULT>& frArray 
        );

    HRESULT  SetScanSetting( 
        /* [in ] */const BK_SCAN_SETTING& Setting
        );


    HRESULT  GetScanSetting(
        /* [out ] */BK_SCAN_SETTING& Setting 
        );

    ///////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    /**
    * @brief        ɨ���ļ�ǰ����
    * @param[in]    lpszFilePath    ԭʼ�ļ�·��
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */
    virtual HRESULT STDMETHODCALLTYPE BeforeScanFile(
        /* [in ] */ LPCWSTR             lpszFilePath,
        /* [in ] */ void*               pvFlag);


    /**
    * @brief        ɨ���ļ������
    * @param[in]    lpszFilePath    ԭʼ�ļ�·��
    * @param[in]    pResult         ��ǰ�ļ���ɨ����
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */
    virtual HRESULT STDMETHODCALLTYPE AfterScanFile(
        /* [in ] */ LPCWSTR             lpszFilePath,
        /* [in ] */ const Skylark::BKENG_RESULT* pResult,
        /* [in ] */ void*               pvFlag);


    /**
    * @brief        ����ļ�ǰ���� (�����Զ����ʱ,������ô˻ص�)
    * @param[in]    lpszFilePath    ԭʼ�ļ�·��
    * @param[in]    pResult         ��ǰ�ļ���ɨ����
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */
    virtual HRESULT STDMETHODCALLTYPE BeforeCleanFile(
        /* [in ] */ LPCWSTR             lpszFilePath,
        /* [in ] */ const Skylark::BKENG_RESULT* pResult,
        /* [in ] */ void*               pvFlag);


    /**
    * @brief        ����ļ������ (�����Զ����ʱ,������ô˻ص�)
    * @param[in]    lpszFilePath    ԭʼ�ļ�·��
    * @param[in]    pResult         ��ǰ�ļ���������
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */
    virtual HRESULT STDMETHODCALLTYPE AfterCleanFile(
        /* [in ] */ LPCWSTR             lpszFilePath,
        /* [in ] */ const Skylark::BKENG_RESULT* pResult,
        /* [in ] */ void*               pvFlag);


    /**
    * @brief        ɨ������з���ϸ�� (�����Ϣ,ѹ�����еĲ�����...)
    * @param[in]    lpszVirtualPath ɨ����������·��
    * @param[in]    pResult         ɨ������ɨ����
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */ 
    virtual HRESULT STDMETHODCALLTYPE OnScanDetail(
        /* [in ] */ LPCWSTR             lpszVirtualPath,
        /* [in ] */ const Skylark::BKENG_RESULT* pResult,
        /* [in ] */ void*               pvFlag);



    virtual HRESULT STDMETHODCALLTYPE OnIdle();


    /**
    * @brief        ����ʱ�ص�
    * @param[in]    hrFinishCode    ɨ�践�صĴ�����
    */ 
    virtual HRESULT STDMETHODCALLTYPE OnFinish(
        HRESULT             hrFinishCode);
    ////////////////////////////////////////////////////////////////////////

private:
    VOID _Reset( const CAtlArray<CString>& FilePathArray );

    BK_SCAN_SETTING			    m_Setting;
    CAtlArray<BK_FILE_RESULT>   m_FileResultArray;
    CAtlArray<size_t>           m_unKnownIndex;
    //ɨ������
    CBkScanEngEx                m_ScanEngEx;
    CEngineLiteEx               m_EngineLiteEx;
    //���벡���ӿ�
    CBackupVirusFile            m_BackupVirusFile;
    //��¼��־�ӿ�
    CBkScanLog                  m_ScanLogWriter;
};


class CBkFileScan 
    : public Skylark::IBKEngineCallback
{
public:
    CBkFileScan()
    {
        m_Setting.Reset();
		m_ubackid = 0;
    }
    ~CBkFileScan(){};


    HRESULT  Initialize( DWORD CliendPid );


    HRESULT  Uninitialize();


    HRESULT  GetScanSetting( BK_SCAN_SETTING& Setting );


    HRESULT  SetScanSetting(const BK_SCAN_SETTING& Setting );


    HRESULT  Scan(
        CString&        FilePath,
        DWORD           dwScanMask,
        BK_FILE_RESULT& ScanResult
        );

	HRESULT  ForceClean(
		CString& FilePath,
		BK_FORCE_CLEAN_DETAIL& detail,
		BK_FILE_RESULT&   ScanResult
		);

public:

    virtual HRESULT STDMETHODCALLTYPE BeforeScanFile(
        /* [in ] */ LPCWSTR             lpszFilePath,
        /* [in ] */ void*               pvFlag)
    {
        return S_OK;
    }



    virtual HRESULT STDMETHODCALLTYPE AfterScanFile(
        /* [in ] */ LPCWSTR             lpszFilePath,
        /* [in ] */ const Skylark::BKENG_RESULT* pResult,
        /* [in ] */ void*               pvFlag)
    {
        if ( pResult->bIsVirus 
            && (FALSE == m_Setting.bAutoClean) )
        {
            m_ScanLogWriter.WriteResultAsLog( lpszFilePath, pResult );
            m_ScanLogWriter.SaveToFile();
        }
        return S_OK;
    }



    virtual HRESULT STDMETHODCALLTYPE BeforeCleanFile(
        /* [in ] */ LPCWSTR             lpszFilePath,
        /* [in ] */ const Skylark::BKENG_RESULT* pResult,
        /* [in ] */ void*               pvFlag)
    {
        if ( pResult->bIsVirus && m_Setting.bAutoClean )
        {
            m_ScanLogWriter.WriteResultAsLog( lpszFilePath, pResult );
            m_ScanLogWriter.SaveToFile();
        }

        if ( pResult->bIsVirus && m_Setting.bQuarantineVirus )
        {
            if (SLPTL_LEVEL_MARK___LOCAL_HEURIST == pResult->uSecLevel)
            {
                // ��������ʽɨ��Ĳ�ɾ��,����Ҳ���ᱸ��
            }
            else if (SLPTL_LEVEL_MARK___BLACK_HEURIST_LOW_RISK == pResult->uSecLevel)
            {
                // �ƶ�����ʽ�ĵͷ��ղ�ɾ��,����Ҳ���ᱸ��
            }
            else
            {
                m_BackupVirusFile.BackupFile( lpszFilePath, pResult, m_ubackid, pvFlag );
            }
        }

        return S_OK;
    }



    virtual HRESULT STDMETHODCALLTYPE AfterCleanFile(
        /* [in ] */ LPCWSTR             lpszFilePath,
        /* [in ] */ const Skylark::BKENG_RESULT* pResult,
        /* [in ] */ void*               pvFlag)
    {
        return S_OK;
    }



    virtual HRESULT STDMETHODCALLTYPE OnScanDetail(
        /* [in ] */ LPCWSTR             lpszVirtualPath,
        /* [in ] */ const Skylark::BKENG_RESULT* pResult,
        /* [in ] */ void*               pvFlag)
    {
        return S_OK;
    }



    virtual HRESULT STDMETHODCALLTYPE OnIdle()
    {
        return S_OK;
    }



    virtual HRESULT STDMETHODCALLTYPE OnFinish(
        HRESULT             hrFinishCode)
    {   
        return S_OK;
    }
    ////////////////////////////////////////////////////////////////////////
private:
    HRESULT _SetBKEngSetting( const BK_SCAN_SETTING& Setting );

	HRESULT ReportFile( 
		CString& FilePath, 
		DWORD  dwTrack,
		UINT64 ubackid
		);

	BOOL TranslateVirusName( LPCWSTR lpVirusName, CString& strTranslateVirusName );
	void TransformResult(const Skylark::BKENG_RESULT& bkResult, BK_FILE_RESULT& FileResult);
	HRESULT GenerateRecycleFilePath( LPCWSTR lpszRecycleFile, CString& strRecycleFilePath );

    CEngineLiteEx               m_EngineLiteEx;
    BK_SCAN_SETTING             m_Setting;

    //���벡���ӿ�
    CBackupVirusFile            m_BackupVirusFile;
    //��¼��־�ӿ�
    CBkScanLog                  m_ScanLogWriter;
	UINT64						m_ubackid;
};

