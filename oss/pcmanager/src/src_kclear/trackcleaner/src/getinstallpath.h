#ifndef _GETINSTALLPATH_H_
#define _GETINSTALLPATH_H_
#include <string>
#include "../../kclear/src/kscgetpathfromuninst.h"
using namespace std;
class KSearchSoftwareStruct
{
public:

	LPCTSTR pszMainFileName;      // �������Ŀ¼�µ�����һ�ļ���


	int     nDefPathFolderCSIDL;  // ���Ĭ�ϰ�ȫ·����CSIDL, ��: CSIDL_PROGRAMSΪ C:\Program files, -1��ʾ��ʹ�ø�������
	LPCTSTR pszDefPath;           // ���Ĭ�ϰ�ȫ·����ȥCSIDL����.


	HKEY    hRegRootKey;          // �ܶ��������ע����м�¼��װ·�� ����
	LPCTSTR pszRegSubKey;         // �ܶ��������ע����м�¼��װ·�� �Ӽ�
	LPCTSTR pszPathValue;         // �ܶ��������ע����м�¼��װ·�� ��¼·����ֵ
	BOOL    bFolder;              // TRUE �������Ŀ¼  FALSE ��������ļ�


	LPCTSTR pszUninstallListName; // ������ж���б��е�����

	LPCTSTR pszFileDesc;          // ָ��������İ汾������Ϣ, ��MUICache�в���



public:
	KSearchSoftwareStruct()
	{
		pszMainFileName      = NULL;      
		nDefPathFolderCSIDL  = -1; 
		pszDefPath           = NULL;   
		hRegRootKey          = NULL;       
		pszRegSubKey         = NULL; 
		pszPathValue         = NULL;     
		bFolder              = TRUE;      
		pszUninstallListName = NULL; 
		pszFileDesc          = NULL; 
	}
};

inline LONG SimpleRegister_QueryStringValue( 
									 HKEY    hRootKey, 
									 LPCTSTR pszSubkey, 
									 LPCTSTR pszValue,
									 LPTSTR  pszBuffer, 
									 ULONG   ulBufSize 
									 )
{
	LONG lRet = ERROR_SUCCESS;

	CRegKey reg;
	lRet = reg.Open( hRootKey, pszSubkey, KEY_READ );
	if( lRet != ERROR_SUCCESS )
		goto clean0;


	lRet = reg.QueryStringValue( pszValue, pszBuffer, &ulBufSize );
	if( lRet != ERROR_SUCCESS )
		goto clean0;

clean0:
	reg.Close();
	return lRet;
}

inline BOOL SearchSoftwarePath(const KSearchSoftwareStruct* psss, wstring& strPath)
{
	if( psss == NULL || psss->pszMainFileName == NULL || psss->pszMainFileName[0] == 0 )
		return FALSE;


	BOOL  bRet = FALSE;
	TCHAR szFolderPath[MAX_PATH] = {0};


	//-------------------------------------
	// ��Ĭ�ϰ�װ·���²���
	if( psss->pszDefPath != NULL && psss->pszDefPath[0] != 0 )
	{
		if( psss->nDefPathFolderCSIDL != -1 )
		{
			if( ::SHGetSpecialFolderPath( NULL, szFolderPath, CSIDL_PROGRAM_FILES, FALSE ) )
				::PathAddBackslash( szFolderPath );
		}


		::PathAppend( szFolderPath, psss->pszDefPath );
		::PathAddBackslash( szFolderPath );

		strPath = szFolderPath;
		strPath += psss->pszMainFileName;

		if( ::PathFileExists( strPath.c_str()) )
			return TRUE;
	}



	//-------------------------------------
	// ���ע����б����˳���װ·��, ���ȡע����ȡ·��
	if( psss->hRegRootKey  != NULL && 
		psss->pszRegSubKey != NULL && 
		psss->pszPathValue != NULL &&
		psss->pszRegSubKey[0] != 0 
		)
	{
		LONG lRet = SimpleRegister_QueryStringValue( 
			psss->hRegRootKey, 
			psss->pszRegSubKey,
			psss->pszPathValue,
			szFolderPath,
			MAX_PATH
			);

		if( lRet == ERROR_SUCCESS )
		{
			if( !psss->bFolder )
				::PathRemoveFileSpec( szFolderPath );

			::PathAddBackslash( szFolderPath );
			strPath = szFolderPath;
			strPath += psss->pszMainFileName ;

			if( ::PathFileExists( strPath.c_str()) )
				return TRUE;
		}
	}


	////-------------------------------------
	//// ��ж���б��в���
	if( psss->pszUninstallListName != NULL && psss->pszUninstallListName[0] != 0 )
	{
		KSearchSoftwarePathFromUninstallList searchpath;
		BOOL bRet = searchpath.SearchSoftwarePathFromUninstallList( 
			psss->pszUninstallListName, 
			psss->pszMainFileName, 
			szFolderPath,
			MAX_PATH
			);

		if( bRet )
		{
			strPath = szFolderPath;
			return TRUE;
		}
	}


	////--------------------------------------
	//// ��MUICache�в���
	//if( psss->pszFileDesc != NULL && psss->pszFileDesc[0] != 0 )
	//{
	//	KSearchSoftwarePathFromMUICache searchpath;
	//	BOOL bRet = searchpath.SearchSoftwarePathFromMUICache(
	//		psss->pszMainFileName,
	//		psss->pszFileDesc,
	//		szFolderPath,
	//		MAX_PATH
	//		);

	//	if( bRet )
	//	{
	//		strPath = szFolderPath;
	//		return TRUE;
	//	}
	//}


	////--------------------------------------
	//// ��App Paths�в���
	//{
	//	KSearchSoftwarePathFromAppPaths searchpath;
	//	BOOL bRet = searchpath.SearchSoftwarePathFromAppPaths(
	//		psss->pszMainFileName,
	//		szFolderPath,
	//		MAX_PATH
	//		);

	//	if( bRet )
	//	{
	//		strPath = szFolderPath;
	//		return TRUE;
	//	}
	//}



	strPath = TEXT( "" );
	return FALSE;
}

#endif