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

#pragma once

#include <map>
#include <string>
#include <vector>

class CFilterTool;



class CFilterTool
{
public:
    CFilterTool(void);
public:
    ~CFilterTool(void);

     static CFilterTool& Instance();

     //��ʼ��
     BOOL Init();

     //����ʼ��
     BOOL Uninit();

     typedef BOOL (CFilterTool::*FilterOper)(CString strFilePath);

    
     //���ҹ���
     BOOL _DoFindFuncMap(CString& strFuncName,CString strFileName);


protected:

    //��������ӳ���
    BOOL _DoMakeFuncMap(CString strFuncName,FilterOper pHandle);
    

    

    //���ӳ���
    BOOL _DoClearAllFuncMap();

public:

    BOOL CheckWindowsPath(CString strFilePath);
    BOOL CheckDrivePath(CString strFilePath);
    BOOL CheckProgramPath(CString strFilePath);
    BOOL CheckDownloadProPath(CString strFilePath);
    BOOL CheckSpecFile(CString strFile);

private:

    BOOL GetSystemDrive(CString &strSysdriver)
    {
        BOOL bRet = FALSE;
        WCHAR szPath[MAX_PATH] = { 0 };
        strSysdriver = L"";

        if (0 != ::GetSystemDirectory(szPath,MAX_PATH))
        {
            strSysdriver += szPath[0];
            strSysdriver += szPath[1];
            bRet = TRUE;
        }

        return bRet;
    }

    BOOL GetWindowsDir(CString &strWindir)
    {
        BOOL bRet = FALSE;
        WCHAR szPath[MAX_PATH] = { 0 };

        if (0 != ::GetWindowsDirectory(szPath,MAX_PATH))
        {
            strWindir = szPath;  
            bRet = TRUE;
        }

        return bRet;
    }

    CString GetFileExtName(CString strFilePath)
    {
        int pos=strFilePath.Find(L"."); //��ȡ . ��λ��
        if(pos==-1){ //���û���ҵ���ֱ�ӷ��ظ��ַ���
            return strFilePath;
        }else{
            return GetFileExtName(strFilePath.Mid(pos+1)); //�ҵ��˵Ļ�������������ֱ����ײ�
        }
    }

    BOOL Filter(CString &strPath, const CString *g_pszFilt, unsigned int uFilterCount)
    {
        BOOL nRet = FALSE;

        for (int nIndex = 0; nIndex < uFilterCount; nIndex++)
        {
            if (strPath.CompareNoCase(g_pszFilt[nIndex]) == 0)
            {
                nRet = TRUE;
                break;
            }
        }
        return nRet;
    }
   

private:

    BOOL m_bInitFlag;                                    //��ʼ����־
    std::map<CString, FilterOper> m_FilterFuncMap;       //����ӳ���

};

const CString g_pszDownloadFiles[8] = {

    TEXT("FP_AX_CAB_INSTALLER.exe"),
    TEXT("swflash.inf"),
    TEXT("dwusplay.dll"),
    TEXT("dwusplay.exe"),
    TEXT("isusweb.dll"),
    TEXT("IDrop.ocx"),
    TEXT("IDropCHS.dll"),
    TEXT("IDropENU.dll")

};


const CString g_pszSpecFiles[9] = {

    TEXT("desktop.ini"),
    TEXT("INFO2"),
    TEXT("index.dat"),
    TEXT("ntuser.dat"),
	TEXT("~outlook.pst.tmp"),
	TEXT("computer.lnk"),
	TEXT("control panel.lnk"),
	TEXT("run.lnk"),
	TEXT("help.lnk")
	
}; //Ҫ���˵������ļ�

const CString g_pszSpecDirs[4] = {

    TEXT("temp"),
    TEXT("Downloaded Program Files"),
    TEXT("Prefetch"),
    TEXT("SoftwareDistribution\\Download")
};//�������˵�����Ŀ¼

const CString g_pszFilterExt[27] = {

    TEXT("log"),
    TEXT("old"),
    TEXT("lo_"),
    TEXT("tmp"),
    TEXT("_mp"),
    TEXT("gid"),
    TEXT("chk"),
    TEXT("??$"),
    TEXT("??~"),
    TEXT("?~?"),
    TEXT("~*"),
    TEXT("^*"),
    TEXT("temp"),
    TEXT("~mp"),
    TEXT("$*"),
    TEXT("___"),
    TEXT("$$$"),
    TEXT("@@@"),
    TEXT("---"),
    TEXT("ftg"),
    TEXT("fnd"),
    TEXT("fts"),
    TEXT("%%%"),
    TEXT("prv"),
    TEXT("err"),
    TEXT("diz"),
    TEXT("mch")

};//����ɾ���ĺ�׺

const CString g_pszSpecDelFiles[8] = {

    TEXT("mscreate.dir"),
    TEXT("imagedb.aid"),
    TEXT("errorlog.txt"),
    TEXT("comsetup.txt"),
    TEXT("directx.txt"),
    TEXT("mpcsetup.txt"),
    TEXT("netsetup.txt"),
    TEXT("thumbs.db")

}; //Ҫ���˵������ļ�