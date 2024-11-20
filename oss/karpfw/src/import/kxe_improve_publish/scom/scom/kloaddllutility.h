/********************************************************************
* CreatedOn: 2006-9-6   16:12
* FileName: KLoadDllUtility.h
* CreatedBy: qiuruifeng <qiuruifeng@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/
#ifndef KLOADDLLUTILITY_H
#define KLOADDLLUTILITY_H

#include "KSearchFile.h"

namespace KLoadDllUtility
{
	//���ݲ��Ҳ���(�Ȳ�ע�����Ȳ鵱ǰĿ¼)Ѱ��scom.dll
	inline HMODULE __stdcall AutoSearchLoadLibrary(const TCHAR* pszFileName, BOOL bRegFirst = TRUE)
	{
		if (NULL == pszFileName)
			return NULL;

		HMODULE handle = NULL;

		KSearchFile search(pszFileName);
		TCHAR szFilePath[MAX_PATH] = { 0 };
		int nResult = E_FAIL;
		
		if (bRegFirst)
		{	//��ע���������
			nResult = search.SearchInReg(szFilePath, MAX_PATH);
			if (0 == nResult)
			{
				handle = LoadLibrary(szFilePath);
				if (handle)
					return handle;	
			}
		}

		//�ڵ�ǰdllĿ¼����
		nResult = search.SearchInCurModuleDir(szFilePath, MAX_PATH);
		if (0 == nResult)
		{
			handle = LoadLibrary(szFilePath);
			if (handle)
			{
				if (bRegFirst)
					search.WritePathToReg(szFilePath);

				return handle;
			}
		}

		//�ڵ�ǰexeĿ¼����
		nResult = search.SearchInCurProcessDir(szFilePath, MAX_PATH);
		if (0 == nResult)
		{
			handle = LoadLibrary(szFilePath);
			if (handle)
			{
				if (bRegFirst)
					search.WritePathToReg(szFilePath);

				return handle;
			}				 
		}

		if (!bRegFirst)
		{	//��ע���������
			nResult = search.SearchInReg(szFilePath, MAX_PATH);
			if (0 == nResult)
			{
				handle = LoadLibrary(szFilePath);
				if (handle)
					return handle;	
			}
		}

		//��ϵͳ�Զ���
		handle = LoadLibrary(pszFileName);
		return handle;	
	}
}


#endif //KLOADDLLUTILITY_H