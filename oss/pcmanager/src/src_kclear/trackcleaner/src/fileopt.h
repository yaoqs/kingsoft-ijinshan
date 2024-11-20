#ifndef _FILEOPT_H_
#define _FILEOPT_H_

#include <Windows.h>
#include <atlstr.h>
#include <process.h>
#include <atlconv.h>
#include "CleanProc.h"

typedef BOOL (WINAPI *EnumerateFunc) (LPCTSTR lpFileOrPath, void* pUserData,LARGE_INTEGER iFileSize);
typedef BOOL (WINAPI *EnumerateFuncEx) (int iType,LPCTSTR lpFileOrPath, void* pUserData,LARGE_INTEGER iFileSize);

class CFileOpt
{
public:
	CFileOpt(){ s_bUserBreak = FALSE; };
	~CFileOpt(){};
public:
	void		UserBreadFlag(BOOL bUserBreak) { s_bUserBreak = bUserBreak; };
	//ȫ·��ö��
	

	void		DoFileEnumeration(LPCTSTR lpPath,BOOL bRecursion, BOOL bEnumFiles,EnumerateFunc pFunc, void* pUserData);
	
	//ͨ���ö��
	void		DoFileEnumeration(LPCTSTR lpPath,CSimpleArray<CString>& vec_wildCard ,BOOL bRecursion, BOOL bEnumFiles, EnumerateFunc pFunc, void* pUserData);
	
	//�Դ�����ö��
	void		DoFileEnumerationEx(LPCTSTR lpPath,CSimpleArray<FILEEXTS_IN>& vec_wildCard ,BOOL bRecursion, BOOL bEnumFiles, EnumerateFuncEx pFunc, void* pUserData);
	
	//ö���ļ���
	void		DoFileFolder(LPCTSTR lpPath,CSimpleArray<CString>& vec_folder,BOOL bRecursion=FALSE,BOOL bFullPath  = TRUE);
	
	//ɾ�����ļ���
	void		DeleteEmptyDirectories(LPCTSTR dir);

	BOOL		DeleteDirectory(LPCTSTR *DirName);
	
	BOOL		ConvetPath(CString& strSourcPath);

	BOOL		s_bUserBreak;
};

#endif //_FILEOPT_H_