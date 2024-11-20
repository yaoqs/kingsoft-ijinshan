// Copyright (c) 2010 Kingsoft Corporation. All rights reserved.
// Copyright (c) 2010 The KSafe Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _GETINSTALLPATH_H_
#define _GETINSTALLPATH_H_
#include "kscgetpathfromuninst.h"
#include <string>
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
		return lRet;


	lRet = reg.QueryStringValue( pszValue, pszBuffer, &ulBufSize );
	if( lRet != ERROR_SUCCESS )
		return lRet;


	return lRet;
}

inline BOOL SearchSoftwarePath(const KSearchSoftwareStruct* psss, wstring& strPath)
{
	if( psss == NULL || psss->pszMainFileName == NULL || psss->pszMainFileName[0] == 0 )
		return FALSE;


	BOOL  bRet = FALSE;
	TCHAR szFolderPath[MAX_PATH] = {0};

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
	// ��ж���б��в���
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