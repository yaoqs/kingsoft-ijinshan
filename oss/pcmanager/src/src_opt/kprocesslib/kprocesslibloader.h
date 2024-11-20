#pragma once


class ProcessLib;
class KSProcessInfo;

class KProcessLibLoader
{
public:
    KProcessLibLoader(void);
    ~KProcessLibLoader(void);

	// ��ȡĬ�Ͻ��̿��·��
	static CString GetDefaultLibPath();

    BOOL LoadLib(LPCTSTR szLibDatPath = NULL);

	BOOL FindInfo(LPCTSTR szFilePath,  KSProcessInfo& processInfo);

protected:
    

protected:
    BOOL						m_bLoaded;
    CString						m_strDatPath;
    ProcessLib*                 m_pProcessLib;

};
