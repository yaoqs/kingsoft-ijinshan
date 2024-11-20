#include "StdAfx.h"
#include "bigfilescan.h"
#include "bigfilemgr.h"
#include "msgdefine.h"
#include <algorithm>
#include "kscbase/kscfilepath.h"
#include "linkchecker.h"
#include "kclear/libheader.h"

CBigFileScan::CBigFileScan(void)
{
    m_bstopscan     = false;
    m_hThread    = NULL;
    m_dwThreadID = 0;
    m_nCurrentIndex = -1;
    m_strRecursive = L"";
    m_strSystemRecursive = L"";

    m_hSystemThread = NULL;
    m_dwSystemThreadID = 0;
    m_bstopsystemscan = false;

    ExtMap[L"avi"] = L"��Ƶ�ļ�";
    ExtMap[L"mkv"] = L"��Ƶ�ļ�";
    ExtMap[L"ogm"] = L"��Ƶ�ļ�";
    ExtMap[L"mp4"] = L"��Ƶ�ļ�";
    ExtMap[L"m4p"] = L"��Ƶ�ļ�";
    ExtMap[L"m4b"] = L"��Ƶ�ļ�";
    ExtMap[L"mpg"] = L"��Ƶ�ļ�";
    ExtMap[L"mpeg"] = L"��Ƶ�ļ�";
    ExtMap[L"pss"] = L"��Ƶ�ļ�";
    ExtMap[L"pav"] = L"��Ƶ�ļ�";
    ExtMap[L"vob"] = L"��Ƶ�ļ�";
    ExtMap[L"mpe"] = L"��Ƶ�ļ�";
    ExtMap[L"wv"] = L"��Ƶ�ļ�";
    ExtMap[L"m2ts"] = L"��Ƶ�ļ�";
    ExtMap[L"ra"] = L"��Ƶ�ļ�";
    ExtMap[L"ram"] = L"��Ƶ�ļ�";
    ExtMap[L"rm"] = L"��Ƶ�ļ�";
    ExtMap[L"rmvp"] = L"��Ƶ�ļ�";
    ExtMap[L"rp"] = L"��Ƶ�ļ�";
    ExtMap[L"rpm"] = L"��Ƶ�ļ�";
    ExtMap[L"m4v"] = L"��Ƶ�ļ�";
    ExtMap[L"f4v"] = L"��Ƶ�ļ�";
    ExtMap[L"flv"] = L"��Ƶ�ļ�";
    ExtMap[L"swf"] = L"��Ƶ�ļ�";
    ExtMap[L"rmvb"] = L"��Ƶ�ļ�";

    ExtMap[L"rsc"] = L"��Ƶ�ļ�";
    ExtMap[L"rt"] = L"��Ƶ�ļ�";
    ExtMap[L"wmv"] = L"��Ƶ�ļ�";
    ExtMap[L"wmp"] = L"��Ƶ�ļ�";
    ExtMap[L"wm"] = L"��Ƶ�ļ�";
    ExtMap[L"wma"] = L"��Ƶ�ļ�";
    ExtMap[L"asf"] = L"��Ƶ�ļ�";
    ExtMap[L"mp3"] = L"��Ƶ�ļ�";
    ExtMap[L"ogg"] = L"��Ƶ�ļ�";
    ExtMap[L"cda"] = L"��Ƶ�ļ�";
    ExtMap[L"wav"] = L"��Ƶ�ļ�";
    ExtMap[L"ape"] = L"��Ƶ�ļ�";

    ExtMap[L"doc"] = L"�ĵ�";
    ExtMap[L"xls"] = L"�ĵ�";
    ExtMap[L"docx"] = L"�ĵ�";
    ExtMap[L"ppt"] = L"�ĵ�";
    ExtMap[L"xlsx"] = L"�ĵ�";
    ExtMap[L"pptx"] = L"�ĵ�";
    ExtMap[L"pdf"] = L"�ĵ�";
    ExtMap[L"caj"] = L"�ĵ�";
    ExtMap[L"vss"] = L"�ĵ�";
    ExtMap[L"et"] = L"�ĵ�";
    ExtMap[L"dps"] = L"�ĵ�";
    ExtMap[L"wps"] = L"�ĵ�";
    
   

    ExtMap[L"msi"] = L"��װ�ļ�";
    ExtMap[L"exe"] = L"Ӧ�ó���";
    ExtMap[L"iso"] = L"�����ļ�";
    ExtMap[L"img"] = L"�����ļ�";
    ExtMap[L"gho"] = L"�����ļ�";
   

    ExtMap[L"jpg"] = L"ͼ���ļ�";
    ExtMap[L"png"] = L"ͼ���ļ�";
    ExtMap[L"ico"] = L"ͼ���ļ�";
    ExtMap[L"gif"] = L"ͼ���ļ�";
    ExtMap[L"jpeg"] = L"ͼ���ļ�";
    ExtMap[L"bmp"] = L"ͼ���ļ�";

    ExtMap[L"zip"] = L"ѹ���ļ�";
    ExtMap[L"rar"] = L"ѹ���ļ�";
    ExtMap[L"7z"] = L"ѹ���ļ�";
    ExtMap[L"cab"] = L"ѹ���ļ�";

	_LoadBigFileRule();

    _GetMyDeskTop(strDesktopPath);
    _GetDownLoadsDir(strDownLoadPath);
    _GetMyDocument(strDocPath);
	strDesktopPath = strDesktopPath.Mid(strDesktopPath.Find(L'\\'));
	strDownLoadPath = strDownLoadPath.Mid(strDownLoadPath.Find(L'\\'));
	strDocPath = strDocPath.Mid(strDocPath.Find(L'\\'));
    strDesktopPath.MakeLower();
    strDownLoadPath.MakeLower();
    strDocPath.MakeLower();

}

CBigFileScan::~CBigFileScan(void)
{
}

BOOL CBigFileScan::Initialize()
{

    BOOL bRet = FALSE;
    CAtlList<CString> dirs;
    POSITION pos;
    

    if(m_DirWork.size() == 0)
    {
        BIGDIRECTORY dirData;

        dirData.nIndex = 0;
        dirData.strCaptionName = L"���ļ�";
        dirData.dirDesc = L"Ϊ��ɨ���ϵͳ��������50���ļ�����";
        _GetDrive(dirs);
        pos = dirs.GetHeadPosition();
        dirData.strDirectory.clear();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        dirData.ulSize = 0;
        dirData.bScanFlag = TRUE;
        m_DirWork.push_back(dirData);

        dirData.nIndex = 1;
        dirData.strCaptionName = L"�ҵ��ĵ�";
        dirData.dirDesc = L"����ϵͳ���ϴ���д����ĵ����ݡ����������Գ��Խ����е��ļ�Ǩ�Ƶ������̷����Խ�ʡϵͳ�̿ռ䡣";
        _GetMyDocumentDir(dirs);
        pos = dirs.GetHeadPosition();
        dirData.strDirectory.clear();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        dirData.ulSize = 0;
        dirData.bScanFlag = TRUE;
        m_DirWork.push_back(dirData);

        dirData.nIndex = 2;
        dirData.strCaptionName = L"����";
        dirData.dirDesc = L"�����������˽϶���ļ���������ѡ��ɾ����Ǩ����Щ�ļ��������������Խ�ʡϵͳ�̿ռ䡣";
        _GetMyDeskTopDir(dirs);
        pos = dirs.GetHeadPosition();
        dirData.strDirectory.clear();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        dirData.ulSize = 0;
        dirData.bScanFlag = TRUE;
        m_DirWork.push_back(dirData);

        dirData.nIndex = 3;
        dirData.strCaptionName = L"����Ŀ¼";
        dirData.dirDesc = L"�����ص��ļ�ռ���˽϶�ռ䣬�����Ը�����Ҫɾ����Ǩ����Щ�ļ����Խ�ʡϵͳ�̿ռ䡣";
        _GetChormeBigDir(dirs);
        pos = dirs.GetHeadPosition();
        dirData.strDirectory.clear();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        _GetFirefoxBigDir(dirs);
        pos = dirs.GetHeadPosition();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        _Get360BigDir(dirs);
        pos = dirs.GetHeadPosition();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        _GetTheworldBigDir(dirs);
        pos = dirs.GetHeadPosition();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        _GetMaxmonthBigDir(dirs);
        pos = dirs.GetHeadPosition();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        _GetFlashGetBigDirs(dirs);
        pos = dirs.GetHeadPosition();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        _GetXunLeiBigDirs(dirs);
        pos = dirs.GetHeadPosition();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        _GetBitCometBigDirs(dirs);
        pos = dirs.GetHeadPosition();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        _GetQQDownLoadBigDirs(dirs);
        pos = dirs.GetHeadPosition();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        dirData.ulSize = 0;
        dirData.bScanFlag = TRUE;
        m_DirWork.push_back(dirData);

        
        

        dirData.nIndex = 4;
        dirData.strCaptionName = L"��ƵĿ¼";
		dirData.dirDesc = L"������Ƶ������������˽϶���Ƶ�ļ��������Ը�����Ҫɾ����Ǩ����Щ��Ƶ�ļ����Խ�ʡϵͳ�̿ռ䡣";
        _GetYouKuBigDirs(dirs);
        pos = dirs.GetHeadPosition();
        dirData.strDirectory.clear();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        _GetKu6BigDirs(dirs);
        pos = dirs.GetHeadPosition();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        _GetXunleiKankanBigDirs(dirs);
        pos = dirs.GetHeadPosition();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        dirData.ulSize = 0;
        dirData.bScanFlag = TRUE;
        m_DirWork.push_back(dirData);


        dirData.nIndex = 5;
        dirData.strCaptionName = L"����Ŀ¼";
        dirData.dirDesc = L"������Ƶ������������˽϶���Ƶ�ļ��������Ը�����Ҫɾ����Ǩ����Щ��Ƶ�ļ����Խ�ʡϵͳ�̿ռ䡣";
        _GetKuwoBigDirs(dirs);
        pos = dirs.GetHeadPosition();
        dirData.strDirectory.clear();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        _GetKugouBigDirs(dirs);
        pos = dirs.GetHeadPosition();
        while(pos!=NULL)
        {
            CString dirTmp(dirs.GetNext(pos));
            if(dirTmp.GetAt(dirTmp.GetLength()-1)!=L'\\')
                dirTmp+=L"\\";
            dirData.strDirectory.insert(dirTmp.MakeLower());
        }
        dirData.ulSize = 0;
        dirData.bScanFlag = TRUE;
        m_DirWork.push_back(dirData);
        
        m_FileList.resize(m_DirWork.size());
    }

    bRet = TRUE;
    return bRet;
}

bool CBigFileScan::StartScan()
{
    std::vector<BIGDIRECTORY>::iterator iter ;
    bool bResult = TRUE;
    Initialize();

    if (IsScaning())
    {
        bResult = FALSE;
        goto Exit0;
    }

    m_ulTotalFileSize = 0; 
    iter = m_DirWork.begin();

    for (int nIndex = 0; nIndex < (int)m_FileList.size(); nIndex++)
    {
        if(m_DirWork.at(nIndex).bScanFlag)
        {
            m_FileList.at(nIndex).ulAllFileSize = 0;
            m_FileList.at(nIndex).itemArray.clear();
        }
    }

    m_bstopscan = FALSE;

    m_hThread = CreateThread(NULL, 
        0, 
        ScanFileThread, 
        (LPVOID)this,
        NULL,
        &m_dwThreadID);

    if (m_hThread == NULL)   
        bResult = FALSE;

Exit0:
    return bResult;
}



bool CBigFileScan::StopScan()
{
    
    if (IsScaning())
    {
        m_bstopscan = TRUE;
        WaitForSingleObject(m_hSystemThread,1000);
        
    }
    return true;
}

BOOL CBigFileScan::IsScaning() const
{
    return m_hThread != NULL;
}


BOOL CBigFileScan::StartSystemDriveScan()
{
    BOOL bResult = TRUE;

    if (IsSystemDriveScaning())
    {
        bResult = FALSE;
        goto Exit0;
    }

  

    m_bstopsystemscan = FALSE;

    m_hSystemThread = CreateThread(NULL, 
        0, 
        ScanSystemFileThread, 
        (LPVOID)this,
        NULL,
        &m_dwSystemThreadID);

    if (m_hSystemThread == NULL)   
        bResult = FALSE;

Exit0:
    return bResult;
}



bool CBigFileScan::StopSystemDriveScan()
{
    if (IsSystemDriveScaning())
    {
        m_bstopsystemscan = TRUE;
        WaitForSingleObject(m_hSystemThread,1000);
    }
    return true;
}

BOOL CBigFileScan::IsSystemDriveScaning() const
{
    return m_hSystemThread != NULL;
}


BOOL CBigFileScan::FindFileInDirectory(LPCTSTR pszFullPath)
{
    BOOL bResult = FALSE;
    WIN32_FIND_DATA ff = { 0 }; 

    if ( m_bstopscan )
    {
        bResult = TRUE;
        goto Exit0;
    }

    // �ݹ�������Ŀ¼
    TCHAR szFindName[MAX_PATH] = {0};
    _tcsncpy_s( szFindName, MAX_PATH, pszFullPath,  MAX_PATH - 1 );
    _tcsncat_s( szFindName, MAX_PATH, TEXT("*.*") , MAX_PATH - _tcslen(pszFullPath) - 1 );
    
    HANDLE findhandle = ::FindFirstFile( szFindName, &ff ); 

    if( findhandle == INVALID_HANDLE_VALUE )
    {
        bResult = FALSE;
        goto Exit0;
    }

    BOOL res = TRUE;

    while( res && !m_bstopscan )
    {
        if( ff.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )  
        {
            if (( _tcscmp( ff.cFileName, _T( "."  ) ) != 0) 
                && ( _tcscmp( ff.cFileName, _T( ".." ) ) != 0 ))
            {
                memset(szFindName, 0, sizeof(szFindName));
                _tcsncpy_s( szFindName, MAX_PATH, pszFullPath,
                    MAX_PATH - 1 );
                _tcsncat_s( szFindName, MAX_PATH, ff.cFileName, 
                    MAX_PATH - _tcslen(szFindName) - 1 );
                _tcsncat_s( szFindName, MAX_PATH,TEXT("\\"),
                    MAX_PATH - _tcslen(szFindName) - 1 );

               
                    FindFileInDirectory(szFindName);  
            }
        }
        else if (!FileFilter(ff.cFileName) )
        {
            CString fileext =  GetExtName(ff.cFileName);
            FILEDATA TraverseFileData;

            TraverseFileData.strExt  = fileext;
            TraverseFileData.strFileName = ff.cFileName;
            TraverseFileData.uFileSize   = ff.nFileSizeHigh;
            TraverseFileData.uFileSize   = TraverseFileData.uFileSize << 32;
            TraverseFileData.uFileSize  |= ff.nFileSizeLow;

            CString subPath(pszFullPath);
            int nPos = m_strRecursive.GetLength()-1;
            subPath = subPath.Mid(nPos);

            TraverseFileData.strSubPathName = subPath;
            TraverseFileData.strFullPath = pszFullPath;
            TraverseFileData.ftCreateDate = ff.ftCreationTime;

            if(ExtMap.find(fileext)!=ExtMap.end()&&m_nCurrentIndex==1 || m_nCurrentIndex > 1)
            {
                
                if (TraverseFileData.uFileSize > 1024*1024*2)
                {
                    
                    BOOL bFind = FALSE;
                    for(int curPos = 0;curPos<(int)m_FileList.at(m_nCurrentIndex).itemArray.size();curPos++)
                    {
                        FILEDATA tempData = m_FileList.at(m_nCurrentIndex).itemArray.at(curPos);
                        CString strFullname = tempData.strFullPath+tempData.strFileName;
                        if(strFullname.CompareNoCase(TraverseFileData.strFullPath+TraverseFileData.strFileName)==0)
                        {
                            bFind = TRUE;
                            break;
                        }
                        
                    }
                    if(!bFind)
                    {
                        m_FileList.at(m_nCurrentIndex).ulAllFileSize += TraverseFileData.uFileSize;
                        m_FileList.at(m_nCurrentIndex).itemArray.push_back(TraverseFileData);
                        m_ulTotalFileSize += TraverseFileData.uFileSize;
                     //   InterlockedExchangeAdd((LONG*)&m_ulTotalFileSize,TraverseFileData.uFileSize);

                    }
                   
                }
                

            }
            
        }

        res = ::FindNextFile( findhandle, &ff );
    }

    ::FindClose( findhandle );
Exit0:
    return bResult;       
}


BOOL CBigFileScan::FileExtFilter(CString pszFileName)
{
    BOOL nRet = FALSE;
    CString fileext = GetExtName(pszFileName);
	fileext.MakeLower();
	if (m_pszFilterExt.Find(fileext) != NULL)
	{
		nRet = TRUE;
	}
  
    return nRet;
}

BOOL CBigFileScan::FileFilter( LPCTSTR pszFileName)
{

    BOOL nRet = FALSE;
	CString strFile(pszFileName);
	strFile.MakeLower();
	if (m_pszFilterFile.Find(strFile) != NULL)
	{
		nRet = TRUE;
	}
    return nRet;
}

BOOL CBigFileScan::DirFilter(CString strDirName)
{
    BOOL nRet = FALSE;
	POSITION pos;
	pos = m_pszFilterDir.GetHeadPosition();
	while (pos)
	{
		CString str = m_pszFilterDir.GetNext(pos);
		if (strDirName.Find(str) != -1)
		{
			nRet = TRUE;
			break;
		}
	}
    
    return nRet;
}

BOOL CBigFileScan::UserDirFilter(CString strDirName)
{
    BOOL nRet = FALSE;
	POSITION pos;
	pos = m_pszFilterDir.GetHeadPosition();
	while (pos)
	{
		CString str = m_pszFilterDir.GetNext(pos);
		if (strDirName.Find(str) != -1&&str!=L"\\users"&&str!=L"\\documents and settings")
		{
			nRet = TRUE;
			break;
		}
	}

    return nRet;
}


DWORD WINAPI CBigFileScan::ScanFileThread(LPVOID lpVoid)
{

    CBigFileScan* pThis = (CBigFileScan*)lpVoid;
    pThis->RunScanFile();
    InterlockedExchange((LONG*)&pThis->m_hThread, NULL);
    InterlockedExchange((LONG*)&pThis->m_dwThreadID, 0);
    return 0;
}

DWORD WINAPI CBigFileScan::ScanSystemFileThread(LPVOID lpVoid)
{

    CBigFileScan* pThis = (CBigFileScan*)lpVoid;
    
    pThis->m_BigFileVec.clear();

    std::set<CString>::iterator iter= pThis->m_DirWork.at(0).strDirectory.begin();


    for (;iter!=pThis->m_DirWork.at(0).strDirectory.end();iter++)
    {
        if((*iter).GetLength()<=0)
            continue;
        pThis->m_strSystemRecursive = *iter;
        pThis->FindSystemFileInDirectory(*iter);  

    }

    

    int nCount = 0;
    pThis->m_FileList.at(0).ulAllFileSize = 0;
    pThis->m_FileList.at(0).itemArray.clear();

    
    std::sort(pThis->m_BigFileVec.begin(),pThis->m_BigFileVec.end(),SortComp);


    
    for (std::vector<FILEDATA>::iterator iter_bigfile = pThis->m_BigFileVec.begin();iter_bigfile!=pThis->m_BigFileVec.end();iter_bigfile++)
    {
        pThis->m_FileList.at(0).ulAllFileSize += (*iter_bigfile).uFileSize;
        pThis->m_FileList.at(0).itemArray.push_back(*iter_bigfile);
        nCount++;
        if(nCount>49)
            break;
       // InterlockedExchangeAdd((LONG*)&pThis->m_ulTotalFileSize,(*iter_bigfile).uFileSize);
    }

    pThis->m_DirWork.at(0).ulSize = pThis->m_FileList.at(0).ulAllFileSize;

    ::SendMessage(pThis->ParentHWND, MSG_USER_DIRLIST_SCANEND,0, (LPARAM)&pThis->m_DirWork.at(0));
    
    InterlockedExchange((LONG*)&pThis->m_hSystemThread, NULL);
    InterlockedExchange((LONG*)&pThis->m_dwSystemThreadID, 0);
    return 0;
}

void CBigFileScan::RunScanFile()
{
    CString strDirectory = _T("");


    for (int i = 0; i < (int)m_DirWork.size() && !m_bstopscan; i++)
    {

        m_nCurrentIndex = i;

        if(m_nCurrentIndex == 0)
        { 
            ::SendMessage(ParentHWND, MSG_USER_DIRLIST_ADD,0, (LPARAM)&m_DirWork.at(i));
            continue;
        }
       
        if(!m_DirWork.at(i).bScanFlag)
           continue;

        std::set<CString>::iterator iter= m_DirWork.at(i).strDirectory.begin();

       // ::SendMessage(ParentHWND, MSG_USER_DIRLIST_SCANING,(WPARAM)m_ulTotalFileSize, (LPARAM)&m_DirWork.at(i));
        
        for(;iter!=m_DirWork.at(i).strDirectory.end();iter++)
        {
            if((*iter).GetLength()<=0)
                continue;
             m_strRecursive = *iter;
             if(m_strRecursive.GetLength()>3&&!UserDirFilter(m_strRecursive))
                FindFileInDirectory(*iter);  

        }
        m_DirWork.at(i).ulSize = m_FileList.at(m_nCurrentIndex).ulAllFileSize;

        std::sort(m_FileList.at(m_nCurrentIndex).itemArray.begin(),m_FileList.at(m_nCurrentIndex).itemArray.end(),SortComp);

        ::SendMessage(ParentHWND, MSG_USER_DIRLIST_ADD,0, (LPARAM)&m_DirWork.at(i));

        m_DirWork.at(i).bScanFlag = FALSE;

        
    }
       // ::SendMessage(ParentHWND, MSG_USER_DIRLIST_SCANEND,(WPARAM)m_ulTotalFileSize, 0);
        
}


BOOL CBigFileScan::FindSystemFileInDirectory(LPCTSTR pszFullPath)
{
    BOOL bResult = FALSE;
    WIN32_FIND_DATA ff = { 0 }; 
   

    if ( m_bstopsystemscan )
    {
        bResult = TRUE;
        goto Exit0;
    }

    if(CLinkChecker::Instance().IsDirectoryJunction(pszFullPath))
    {
        bResult = TRUE;
        goto Exit0;
    }

    // �ݹ�������Ŀ¼
    TCHAR szFindName[MAX_PATH] = {0};
    _tcsncpy_s( szFindName, MAX_PATH, pszFullPath,  MAX_PATH - 1 );
    _tcsncat_s( szFindName, MAX_PATH, TEXT("*.*") , MAX_PATH - _tcslen(pszFullPath) - 1 );

    HANDLE findhandle = ::FindFirstFile( szFindName, &ff ); 

    if( findhandle == INVALID_HANDLE_VALUE )
    {
        bResult = FALSE;
        goto Exit0;
    }

    BOOL res = TRUE;

    while( res && !m_bstopsystemscan )
    {
        if( ff.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )  
        {
            if (( _tcscmp( ff.cFileName, _T( "."  ) ) != 0) 
                && ( _tcscmp( ff.cFileName, _T( ".." ) ) != 0 ))
            {
                memset(szFindName, 0, sizeof(szFindName));
                _tcsncpy_s( szFindName, MAX_PATH, pszFullPath,
                    MAX_PATH - 1 );
                _tcsncat_s( szFindName, MAX_PATH, ff.cFileName, 
                    MAX_PATH - _tcslen(szFindName) - 1 );
                _tcsncat_s( szFindName, MAX_PATH,TEXT("\\"),
                    MAX_PATH - _tcslen(szFindName) - 1 );

                CString subPath(pszFullPath);
                int nPos = m_strSystemRecursive.GetLength()-1;
                subPath = subPath.Mid(nPos);
                subPath = subPath.MakeLower();
                CString strCmpName = subPath;
                strCmpName += ff.cFileName;
                strCmpName = strCmpName.MakeLower();
               
                CString FileFiltWindows(strCmpName.Left(8));


                if(!DirFilter(strCmpName))
                {
                    ::SendMessage(ParentHWND, MSG_USER_DIRLIST_SCANING,(WPARAM)szFindName, 0);
                    ::Sleep(1);
                    FindSystemFileInDirectory(szFindName);  
                }
                else if(FileFiltWindows.CompareNoCase(L"\\windows")==0)
                {
                    if(strCmpName.CompareNoCase(L"\\windows")==0)
                    {
                        ::SendMessage(ParentHWND, MSG_USER_DIRLIST_SCANING,(WPARAM)szFindName, 0);
                        ::Sleep(1);
                        FindSystemFileInDirectory(szFindName);  

                    }
                }
                else if (strCmpName.Find(L"users")!=-1||strCmpName.Find(L"documents and settings")!=-1)
                {
                    ::Sleep(1);
				//	if(strCmpName.Find(strDocPath.GetBuffer())!=-1
				//		||strCmpName.Find(strDownLoadPath.GetBuffer())!=-1
				//		||strCmpName.Find(strDesktopPath.GetBuffer())!=-1)
					::SendMessage(ParentHWND, MSG_USER_DIRLIST_SCANING,(WPARAM)szFindName, 0);

                    FindSystemFileInDirectory(szFindName);  

                }
                
            }
        }
        else if (!FileFilter(ff.cFileName)&&!FileExtFilter(ff.cFileName))
        {
            CString fileext =  GetExtName(ff.cFileName);
            FILEDATA TraverseFileData;

            TraverseFileData.strExt  = fileext;
            TraverseFileData.strFileName = ff.cFileName;
            TraverseFileData.uFileSize   = ff.nFileSizeHigh;
            TraverseFileData.uFileSize   = TraverseFileData.uFileSize << 32;
            TraverseFileData.uFileSize  |= ff.nFileSizeLow;

            CString subPath(pszFullPath);
            int nPos = m_strSystemRecursive.GetLength()-1;
            subPath = subPath.Mid(nPos);
            subPath = subPath.MakeLower();

            TraverseFileData.strSubPathName = subPath;
            TraverseFileData.strFullPath = pszFullPath;
            TraverseFileData.ftCreateDate = ff.ftCreationTime;
            
           
            CString FileFiltWindows(subPath.Left(8));
            
            if (!DirFilter(subPath))
            {
				if(TraverseFileData.uFileSize>=1024*1024)
					m_BigFileVec.push_back(TraverseFileData);

            }
            else if (FileFiltWindows.CompareNoCase(L"\\windows") == 0)
            {
                CString strTempFile  = subPath.Left(13);
                if(strTempFile.CompareNoCase(L"\\windows\\temp")==0 
                    || TraverseFileData.strFileName.CompareNoCase(L"memory.dmp")==0)
                {
					if(TraverseFileData.uFileSize>=1024*1024)
						m_BigFileVec.push_back(TraverseFileData);

                }

            }
            else if (subPath.Find(L"users")!=-1||subPath.Find(L"documents and settings")!=-1)
            {
                if(subPath.Find(strDocPath.GetBuffer())!=-1
                    ||subPath.Find(strDownLoadPath.GetBuffer())!=-1
                    ||subPath.Find(strDesktopPath.GetBuffer())!=-1)
					if(TraverseFileData.uFileSize>=1024*1024)
						m_BigFileVec.push_back(TraverseFileData);

            }

            
           


        }

        res = ::FindNextFile( findhandle, &ff );
    }

    ::FindClose( findhandle );
Exit0:
    return bResult;       
}

bool SortComp(FILEDATA item1,FILEDATA item2){  
    return item1.uFileSize > item2.uFileSize;  
} 

// BOOL CBigFileScan::_LoadBigFileRule()
// {
// 	BOOL retval = FALSE;
// 	TiXmlDocument xmlDoc;
// 	const TiXmlElement *pXmlHistory = NULL;
// 	const TiXmlElement *pXmlMove = NULL;
// 	KFilePath xmlPath = KFilePath::GetFilePath(NULL);
// 	CString strFilter;
// 
// 	xmlPath.RemoveFileSpec();
// 	xmlPath.Append(L"cfg\\bigfilerule.xml");
// 	if (!xmlDoc.LoadFile(UnicodeToAnsi(xmlPath.value()).c_str(), TIXML_ENCODING_UTF8))
// 		goto clean0;
// 
// 	pXmlHistory = xmlDoc.FirstChildElement("setting");
// 	if (!pXmlHistory)
// 		goto clean0;
// 
// 	pXmlMove = pXmlHistory->FirstChildElement("filter_ext");
// 	while (pXmlMove)
// 	{
// 		strFilter = KUTF8_To_UTF16(pXmlMove->Attribute("src"));
//         strFilter.MakeLower();
// 		m_pszFilterExt.AddTail(strFilter);
// 		pXmlMove = pXmlMove->NextSiblingElement("filter_ext");
// 	}
// 
// 	pXmlMove = pXmlHistory->FirstChildElement("filter_file");
// 	while (pXmlMove)
// 	{
// 		strFilter = KUTF8_To_UTF16(pXmlMove->Attribute("src"));
//         strFilter.MakeLower();
// 		m_pszFilterFile.AddTail(strFilter);
// 		pXmlMove = pXmlMove->NextSiblingElement("filter_file");
// 	}
// 
// 	pXmlMove = pXmlHistory->FirstChildElement("filter_dir");
// 	while (pXmlMove)
// 	{
// 		strFilter = KUTF8_To_UTF16(pXmlMove->Attribute("src"));
//         strFilter.MakeLower();
// 		m_pszFilterDir.AddTail(strFilter);
// 		pXmlMove = pXmlMove->NextSiblingElement("filter_dir");
// 	}
// 
// 	retval = TRUE;
// 
// clean0:
// 	return retval;
// }


BOOL CBigFileScan::_LoadBigFileRule()
{
    BOOL retval = FALSE;
    CDataFileLoader dataLoader;
    TiXmlDocument xmlDoc;
    const TiXmlElement *pXmlHistory = NULL;
    const TiXmlElement *pXmlMove = NULL;
    TCHAR szConfPath[MAX_PATH] = { 0 };
    CString strXmlUtf16;
    CStringA strXmlAnsi;
    CString strFilter;

    

    GetModuleFileName(NULL, szConfPath, MAX_PATH);
    PathRemoveFileSpec(szConfPath);
    PathAppend(szConfPath, _T("cfg\\bigfilerule.dat"));


    if (!dataLoader.LoadFile(szConfPath, strXmlUtf16))
        goto clean0;

    strXmlAnsi = KUTF16_To_ANSI(strXmlUtf16);

    if (!xmlDoc.LoadBuffer((LPSTR)(LPCSTR)strXmlAnsi, strXmlAnsi.GetLength(), TIXML_ENCODING_UTF8))
        goto clean0;

    pXmlHistory = xmlDoc.FirstChildElement("setting");
    if (!pXmlHistory)
        goto clean0;

    pXmlMove = pXmlHistory->FirstChildElement("filter_ext");
    while (pXmlMove)
    {
        strFilter = KUTF8_To_UTF16(pXmlMove->Attribute("src"));
        strFilter.MakeLower();
        m_pszFilterExt.AddTail(strFilter);
        pXmlMove = pXmlMove->NextSiblingElement("filter_ext");
    }

    pXmlMove = pXmlHistory->FirstChildElement("filter_file");
    while (pXmlMove)
    {
        strFilter = KUTF8_To_UTF16(pXmlMove->Attribute("src"));
        strFilter.MakeLower();
        m_pszFilterFile.AddTail(strFilter);
        pXmlMove = pXmlMove->NextSiblingElement("filter_file");
    }

    pXmlMove = pXmlHistory->FirstChildElement("filter_dir");
    while (pXmlMove)
    {
        strFilter = KUTF8_To_UTF16(pXmlMove->Attribute("src"));
        strFilter.MakeLower();
        m_pszFilterDir.AddTail(strFilter);
        pXmlMove = pXmlMove->NextSiblingElement("filter_dir");
    }

    retval = TRUE;

clean0:
    return retval;
}