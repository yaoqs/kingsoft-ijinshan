///////////////////////////////////////////////////////////////
//
//	Filename: 	KSearchSoftwarePathFromUninstallList.h
//	Creator:	lichenglin  <lichenglin@kingsoft.net>
//	Date:		2007-10-30  18:45
//	Comment:	
//
///////////////////////////////////////////////////////////////

#ifndef _KSearchSoftwarePathFromUninstallList_h_
#define _KSearchSoftwarePathFromUninstallList_h_
#include <atlpath.h>
#include <atlrx.h>

//-------------------------------------------------------------
// 
// ͨ������ж���б� �����������Ŀ¼
//
//-------------------------------------------------------------


class KSearchSoftwarePathFromUninstallList
{
public:

	/**
	* @brief   ��ж���б��в����Ѱ�װ���������Ŀ¼
	* @param   [in]  pszDisplayName,    [��������1] ж���б����ʾ�����б���������ַ���.
											����������ΪNULL, �Ҵ�Сд����.

	* @param   [in]  pszFileName,       [��������2] �������Ŀ¼�±������ָ�����ļ�. 
											�ļ�����������·��, �����Ժ����·��,
											����: "Plugins\\TraceEraser.dll".
											����������ΪNULL

	* @param   [out] pszMainDir,        �ҵ�����Ŀ¼

	* @param   [in]  nOutSize,          ����Ŀ¼�������С, ����MAX_PATH.

	* @return  �����ɹ�����TURE��û���ҵ�����FALSE
	* @remark  
	*/
	BOOL SearchSoftwarePathFromUninstallList( 
		LPCTSTR  pszDisplayName,
		LPCTSTR  pszFileName,
		LPTSTR   pszMainDir,
		int      nOutSize
		);

private:
	class UNINSTALL_DATA 
	{
	public:
		CString strDisplayName;
		CString strDisplayIcon;
		CString strUninstallString;
	};


private:
	BOOL QueryUninstallData();

	BOOL OnFoundUninstallItem( const UNINSTALL_DATA* pUninstallData );

	BOOL GetPathFromDisplayIcon( LPCTSTR pszDisplayIcon, CString& strPath );

	BOOL GetPathFromUninstallString( LPCTSTR pszUninstallString, CString& strPath );

	BOOL SearchFileInSpecPath( LPCTSTR pszFileName, LPCTSTR pszStartPath, ATL::CPath& strPath );

	BOOL SearchFirstPath( LPCTSTR pszCmdLine, LPCTSTR* ppszStart, LPCTSTR* ppszEnd );

	BOOL GetFirstPath( LPCTSTR pszCmdLine, LPTSTR pszFileName, int nSize );

	BOOL _KillParamEx( LPCTSTR pszCmdLine, LPTSTR pszFileName, int nSize );

	BOOL IsFileExists( LPCTSTR pszFile );

	BOOL IsPossibleSeperator( TCHAR c );

	BOOL IsAlpha( TCHAR c );

	BOOL IsNumber( TCHAR c );

	LPCTSTR HasRundll( LPCTSTR pszCmdLine );

private:
	LPCTSTR  m_pszDisplayName;
	LPCTSTR  m_pszFileName;
	LPTSTR   m_pszMainDir;
	int      m_nOutSize;
};



#endif // _KSearchSoftwarePathFromUninstallList_h_