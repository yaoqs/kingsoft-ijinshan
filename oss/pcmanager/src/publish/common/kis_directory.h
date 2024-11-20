////////////////////////////////////////////////////////////////////////////////
//      
//      Kingsoft File for kiscomm
//      
//      File      : kis_directory.h
//      Version   : 1.0
//      Comment   : �ļ��в�����
//      
//      Create at : 2008-3-5
//      Create by : liupeng
//      
////////////////////////////////////////////////////////////////////////////////

#pragma once 
#include <vector>
using namespace std;


namespace kis 
{

// �ļ�ö����
class KFileIterator
{
private:
	ATL::CString			m_strSearch;
	ATL::CString			m_strPath;
	BOOL			m_bSearchRecursive;
	BOOL			m_bFileOnly;
	BOOL			m_bSubDirFirst;
	HANDLE			m_hCurDir;

	HANDLE			m_hDirSearch;
	KFileIterator*	m_pCurDirIter;
	WIN32_FIND_DATA	m_findData;

public:
	KFileIterator(LPCTSTR pstrSearch, ATL::CString strPath, BOOL bSearchRecursive, BOOL bFileOnly = TRUE,
				BOOL bSubDirFirst = FALSE) :
			m_strSearch(pstrSearch),
			m_strPath(strPath),
			m_bSearchRecursive(bSearchRecursive),
			m_bFileOnly(bFileOnly),
			m_bSubDirFirst(bSubDirFirst),
			m_hCurDir(NULL),
			m_hDirSearch(NULL),
			m_pCurDirIter(NULL)
	{
		if (m_strPath[m_strPath.GetLength() - 1] != L'\\')
			m_strPath += L"\\";

		ClearFindData();
	}

	~KFileIterator()
	{
		if (m_pCurDirIter)
		{
			delete m_pCurDirIter;
			m_pCurDirIter = NULL;
		}
		if (m_hCurDir && (m_hCurDir != INVALID_HANDLE_VALUE))
		{
			::FindClose(m_hCurDir);
			m_hCurDir = NULL;
		}
		if (m_hDirSearch && m_hDirSearch != INVALID_HANDLE_VALUE)
		{
			::FindClose(m_hDirSearch);
			m_hDirSearch = NULL;
		}
	}

	BOOL	Next()
	{
		if (m_bSubDirFirst)
		{
			//ASSERT(m_bSearchRecursive);

			if (SearchSubDirs())
				return TRUE;

			return SearchCurDir();
		}
		else
		{
			if (SearchCurDir())
				return TRUE;

			if (!m_bSearchRecursive)
				return FALSE;

			return SearchSubDirs();
		}
	}

	ATL::CString GetFileName()
	{
		if (m_hCurDir && m_hCurDir != INVALID_HANDLE_VALUE)
			return m_strPath + ATL::CString(m_findData.cFileName);

		if (!m_bSearchRecursive || !m_pCurDirIter)
		{
			// ASSERT(!"�Ѿ�û���ļ����Ի�ȡ��!");
			return ATL::CString(_T(""));
		}
		return m_pCurDirIter->GetFileName();
	}

	// ��ǰ���ļ������ļ���
	BOOL	IsDirectory()
	{
		if (m_hCurDir && m_hCurDir != INVALID_HANDLE_VALUE)
			return m_findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
		
		if (!m_bSearchRecursive || !m_pCurDirIter)
		{
			// ASSERT(!"�Ѿ�û���ļ����Ի�ȡ��!");
			return FALSE;
		}
		return m_pCurDirIter->IsDirectory();
	}

private:
	// ������ǰ���ļ��У��������ļ���
	BOOL	SearchCurDir()
	{
		// ���ļ�����������
		if (m_hCurDir == NULL)
		{
			m_hCurDir = ::FindFirstFile(m_strPath + m_strSearch, &m_findData);
			if (m_hCurDir != INVALID_HANDLE_VALUE)
			{
				if (IsFindAttr(&m_findData))
					return TRUE;
				// �����һ���ҵ������ļ���������ô����Ҫ��������
				if (FindFile())
					return TRUE;
			}
		}

		if (m_hCurDir != INVALID_HANDLE_VALUE)
		{
			if (FindFile())
				return TRUE;
		}

		return FALSE;
	}

	// �������ļ���
	BOOL	SearchSubDirs()
	{
		if (m_hDirSearch == NULL)
		{
			m_hDirSearch = ::FindFirstFile(m_strPath + _T("*"), &m_findData);
			if (m_hDirSearch != INVALID_HANDLE_VALUE)
			{
				if (IsDir(&m_findData))
				{
					if (SearchNewSubDir(m_strPath + ATL::CString(m_findData.cFileName) + L"\\"))
						return TRUE;
				}
				while (FindDir())
				{
					if (SearchNewSubDir(m_strPath + ATL::CString(m_findData.cFileName) + L"\\"))
						return TRUE;
				}
			}
		}

		// ĳ�����ļ�������������
		if (m_hDirSearch != INVALID_HANDLE_VALUE)
		{
			// ��ǰ���ļ����ҵ�
			if (SubDirNext())
				return TRUE;

			// ��ǰ���ļ���û�У����������������ļ���
			while (FindDir())
			{
				if (SearchNewSubDir(ATL::CString(m_findData.cFileName)))
					return TRUE;
			} 
		}

		return FALSE;
	}

	BOOL	SearchNewSubDir(ATL::CString strDir)
	{
		//ASSERT(m_pCurDirIter == NULL);
		m_pCurDirIter = new KFileIterator(m_strSearch, strDir, m_bSearchRecursive, m_bFileOnly);
		return SubDirNext();
	}

	void	ClearFindData()
	{
		memset(&m_findData, 0, sizeof(m_findData));
	}

	// �Ƿ�����Ҫ�ҵ��ļ���
	BOOL	IsFindAttr(WIN32_FIND_DATA *pFindData)
	{
		if (pFindData == NULL)
			return FALSE;

		if (_wcsicmp(pFindData->cFileName, L".") == 0 || _wcsicmp(pFindData->cFileName, L"..") == 0)
			return FALSE;

		if (!m_bFileOnly)
			return TRUE;

		return !(pFindData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	}

	// �����ļ�
	BOOL	FindFile()
	{
		BOOL bFind = FALSE;
		while (!bFind)
		{
			ClearFindData();
			if (::FindNextFile(m_hCurDir, &m_findData))
			{
				if (IsFindAttr(&m_findData))
					return TRUE;
			}
			else
			{
				::FindClose(m_hCurDir);
				m_hCurDir = INVALID_HANDLE_VALUE;
				break;
			}
		}
		return FALSE;
	}

	// �Ƿ����ļ���
	BOOL	IsDir(WIN32_FIND_DATA *pFindData)
	{
		if (pFindData == NULL)
			return FALSE;

		if (_wcsicmp(pFindData->cFileName, L".") == 0 || _wcsicmp(pFindData->cFileName, L"..") == 0)
			return FALSE;

		return pFindData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
	}

	// �����ļ���
	BOOL	FindDir()
	{
		BOOL bFind = FALSE;
		while (!bFind)
		{
			ClearFindData();
			if (::FindNextFile(m_hDirSearch, &m_findData))
			{
				if (IsDir(&m_findData))
					return TRUE;
			}
			else
			{
				::FindClose(m_hDirSearch);
				m_hDirSearch = INVALID_HANDLE_VALUE;
				break;
			}
		}
		return FALSE;
	}

	// ������ǰ���ļ���
	BOOL	SubDirNext()
	{
		//ASSERT(m_pCurDirIter);
		if (m_pCurDirIter->Next())
			return TRUE;

		delete m_pCurDirIter;
		m_pCurDirIter = NULL;
		return FALSE;
	}

};

/*
// �ļ��в�����
class KDirectory
{
public:
	KDirectory()		{}

	// ����һ��Ŀ¼������ڸ�����·����ĳЩdir�����ڣ����Զ���������
	static BOOL	Create(ATL::CString strPath)
	{
		KPath path(strPath);
		if (path.Exists())
			return TRUE;

		path.RemoveBackslash();
		if (!Create(CString(path.GetPath())))
			return FALSE;

		::CreateDirectory(path, NULL);
		return TRUE;
	}

	// ɾ��һ��Ŀ¼
	static BOOL	Delete(ATL::CString strPath)
	{
		BOOL bRet = TRUE;
		// ��ɾ�����е�file
		KFileIterator iter(CString(_T("*")), strPath, TRUE, TRUE, TRUE);
		while (iter.Next())
		{
			CString strFileName = iter.GetFileName();
			if (!DeleteFile(strFileName))
			{
				bRet = FALSE;
			}
		}
		if (!bRet)
			return bRet;

		// ɾ�����е�dir
		KFileIterator iter_dir(CString(_T("*")), strPath, TRUE, FALSE, TRUE);
		while (iter.Next())
		{
			CString strFileName = iter.GetFileName();
			if (!RemoveDirectory(strFileName))
				bRet = FALSE;
		}
		return bRet;
	}

	// ����һ��Ŀ¼����Ŀ¼�µ��ļ�
	static BOOL Copy(ATL::CString strFrom, ATL::CString strTo, BOOL bOverwriteExist)
	{
		KFileIterator iter(ATL::CString(_T("*")), strFrom, TRUE, FALSE, FALSE);
		while (iter.Next())
		{
			KPath path(iter.GetFileName());
			path.MakeRelative(KPath(strFrom));

			KPath pathFileTo(strTo);
			pathFileTo.Append(path);

			if (iter.IsDirectory())
			{
				if (!Create(pathFileTo.GetStr()))
				{
					//ASSERT(!"�����ļ���ʧ��!");
					return FALSE;
				}
			}
			else
			{
				if (pathFileTo.Exists() && !bOverwriteExist)
					continue;
				if (!CopyFile(iter.GetFileName(), pathFileTo, FALSE))
				{
					//ASSERT(!"�����ļ�ʧ��!");
					return FALSE;
				}
			}
		}
		return TRUE;
	}
};
*/
} // namespace kis 