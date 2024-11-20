#include "stdafx.h"
#include "CleanProc.h"
#include <vector>
/************************************************************************/
//˵��
//	���ʱΪ����������ʽ.���Զ�����Ϊȫ��,��������Ϊ��������ʽ,��δ�����޸�
//	�ƻ���һ�������޸�,�����ɨ�轫���ӻ���.ͨ���麯��ͳһ���е���.������
//	���뵽���������н��д���
/************************************************************************/

//����ת��ָ��
extern ScanFileCallBack g_fnScanFile = NULL;
extern ScanRegCallBack  g_fnScanReg = NULL;

//����ӿ�ָ��
extern ScanFileCallBack g_fnOutScanFile = NULL;
extern ScanRegCallBack  g_fnOutScanReg = NULL;

//������Ϣָ��
extern ScanFileCallBackError g_fnScanFileError = NULL;
extern ScanRegCallBackError  g_fnScanRegError = NULL;

//ת������
//�˺������ڽ�ɨ�������Ϣ�Ƚ��д���Ȼ��ת�����ⲿ�ӿ�
BOOL __stdcall _ScanRegCallBack(void* pMain,int iType,LPCTSTR lpcszKeyFullPath,LPCTSTR lpcszValueName,LPCTSTR lpcszValueData);
BOOL __stdcall _ScanFileCallBack(void* pMainError,int iType,LPCTSTR lpcszFileFullPath,DWORD dwFileLowPart,LONG dwFileHighPart);

 
//������ָ��
extern void* g_pMain = NULL;
extern void* g_pMainError = NULL;

//ɨ���߳̾��
extern HANDLE g_hThread = INVALID_HANDLE_VALUE;				//ɨ���߳̾��
extern HANDLE g_hBageThread = INVALID_HANDLE_VALUE;			//ɨ�������ļ�ɨ����
extern HANDLE g_hThreadCleanReg = INVALID_HANDLE_VALUE;		//����ע����߳̾��
extern HANDLE g_hThreadCleanFile = INVALID_HANDLE_VALUE;	//�����ļ��߳̾��

//�߳����б�ʶ
extern BOOL	g_hRun =TRUE;	
extern BOOL	g_hBageRun =TRUE;

//�Ƿ��������
extern BOOL g_bIsClean =FALSE;

//��¼��ǰ�������еĳ���

std::vector<std::wstring> g_listProcessName;
CSimpleArray<int> g_vsNoinstallapp;

//�����̶߳���
unsigned int __stdcall DistributeThread(void* parm);
unsigned int __stdcall CleanRegThread(void* parm);
unsigned int __stdcall CleanFileThread(void* parm);
unsigned int __stdcall BageThread(void* parm);

//������
BOOL CleanFile(int iType,CString& strFileFullPath);
BOOL CleanReg(int iType,CString& strRegeFullPath,CString& strValueName);

//delte file����

//����ͷ�ļ�
#include "shuntproc.h"
#include "ieclean.h"
#include "windowshistory.h"
#include "regclean.h"
#include "garbageclean.h"
#include "apphistory.h"
#include "maxmonth.h"
#include "chromeclean.h"
#include "firefoxclean.h"
#include "ttclean.h"
#include "360clean.h"
#include "wordwinclean.h"
#include "regback.h"
#include "ThunderDownloader.h"
#include "FlashGetDownloader.h"
#include "playertrace.h"
#include "sogoclean.h"
#include "operaclean.h"
#include "kscbase/kcslogging.h"

typedef struct _TYPEINFO  
{
	int iType;

}TYPEINFO;


//ȫ����
CIEClean			g_ieClean;
CWindowsHistory		g_winHistory;
CRegClean			g_regClean;
CAppHistory			g_appHistory;
CGarbageClean		g_garbageClean;	
CChromClean			g_chromClean;
CFireFoxClean		g_firefoxClean;
CMaxmonthClean		g_maxmonthClean;
CTTClean			g_ttClean;
C360Clean			g_360Clean;
CWordWinClean		g_wordWinClean;
CSpecialApp			g_SpecialApp;
CThunderDownloader  g_ThunderDownloader;
CFlashGetDownloader g_FlashGetDownloader;
CBitcometDownloader g_BitcometDowmloader;
CPPSPlayer          g_ppsPlayer;
CPPTVPlayer         g_pptvPlayer;
CQVODPlayer         g_qvodPlayer;
CQQDownloader		g_qqDownloader;
CKSogoClean         g_sogoClean;
CKOperaClean        g_operaClean;
CKFengxingPlay      g_fengxingClean;
CKShenshouPlay      g_sheshouClean;
CKKuwoMusicPlay     g_kuwoClean;
CKFixitPlay         g_FixitClean;
CKAliIm             g_AliimClean;
CKWinLiveMsg        g_Winlivemsg;
//����������;������ɨ��
CRegOpt				g_regOpt;
CFileOpt			g_fileOpt;
//������ע���
CRegBack			g_regBack;

#include "shuntproc.h"

CAtlMap<int,SOFTWAREINFO> CKClearProc::s_map_softwareinfo;

CKClearProc::CKClearProc()
{

}

CKClearProc::~CKClearProc()
{

}


BOOL CKClearProc::DZ_ResetRegsiter(LPCTSTR lpcszRegFilePath)
{
	return g_regBack.RestRegister(lpcszRegFilePath);
}

BOOL CKClearProc:: SoftInfoCallBack(void* pThis,SoftInfo softinfo)
{	
	CKClearProc* pKCleanProc = (CKClearProc*)pThis;
	
	int iType = _wtoi(softinfo.strClearid.GetBuffer());
	softinfo.strClearid.ReleaseBuffer();
	
	//��ѯ�Ƿ��Ѿ�����
	if ( NULL == s_map_softwareinfo.Lookup(iType)  )
	{
		SOFTWAREINFO sofwareInfo;
		sofwareInfo.iType = iType;	
		sofwareInfo.softInfo.Add(softinfo);
		s_map_softwareinfo.SetAt(iType,sofwareInfo);

	}
	else
	{
		 s_map_softwareinfo.Lookup(iType)->m_value.softInfo.Add(softinfo);
	}


	
	return TRUE;
}

void CKClearProc::DZ_IsScanClean(BOOL bClean/* = FALSE */)
{
	g_bIsClean = bClean;
}

BOOL CKClearProc::DZ_GetNoinstallApp(int n)
{
	if (g_vsNoinstallapp.Find(n) == -1)
	{
		return FALSE;
	}
	return TRUE;
}

void CKClearProc::DZ_SetCleanCallBack(ScanRegCallBack fnRegCallBack,ScanFileCallBack fnFileCallBack,void* pMain)
{
	g_pMain = pMain;

	g_fnOutScanFile = fnFileCallBack;
	g_fnOutScanReg = fnRegCallBack;

	g_fnScanFile = _ScanFileCallBack;
	g_fnScanReg = _ScanRegCallBack;
}

void CKClearProc::DZ_SetCleanCallBackError(ScanRegCallBackError fnRegCallBackError,ScanFileCallBackError fnFileCallBackError,void* pMainError)
{
	g_pMainError = pMainError;
	g_fnScanFileError = fnFileCallBackError;
	g_fnScanRegError = fnRegCallBackError;
}

BOOL CKClearProc::DZ_StartScan(int* iTypeList,int iCount)
{	
	CSimpleArray<TYPEINFO> vec_typeInfo;
	for (int i=0;i<iCount;i++)
	{	
		TYPEINFO typeInfo;
		typeInfo.iType = iTypeList[i];
		vec_typeInfo.Add(typeInfo);
	}

	GetCurrentProcessName();
	g_ieClean.Start();
	g_winHistory.Start();
	g_regClean.Start();
	g_appHistory.Start();
	g_chromClean.Start();
	g_firefoxClean.Start();
	g_maxmonthClean.Start();
	g_ttClean.Start();
	g_360Clean.Start();
	g_wordWinClean.Start();
	g_SpecialApp.Start();
	g_ThunderDownloader.Start();
	g_FlashGetDownloader.Start();
	g_BitcometDowmloader.Start();
	g_ppsPlayer.Start();
	g_pptvPlayer.Start();
	g_qvodPlayer.Start();
	g_qqDownloader.Start();
	g_sogoClean.Start();
	g_operaClean.Start();
	g_fengxingClean.Start();
	g_sheshouClean.Start();
	g_kuwoClean.Start();
	g_FixitClean.Start();
	g_AliimClean.Start();
	g_Winlivemsg.Start();
	g_hThread = (HANDLE) _beginthreadex(NULL,NULL,DistributeThread,(void*)&vec_typeInfo,NULL,NULL);
	if (g_hThread == NULL)
		return FALSE;

	Sleep(2000);

	return TRUE;

	return TRUE;
}

BOOL CKClearProc::DZ_StopScan()
{

	g_hRun = FALSE;
	g_wordWinClean.StopScan();
	g_ieClean.StopScan();
	g_winHistory.StopScan();
	g_regClean.StopScan();
	g_appHistory.StopScan();
	g_chromClean.StopScan();
	g_firefoxClean.StopScan();
	g_ttClean.StopScan();
	g_360Clean.StopScan();
	g_maxmonthClean.StopScan();
	g_SpecialApp.StopScan();
	g_ThunderDownloader.StopScan();
	g_FlashGetDownloader.StopScan();
	g_BitcometDowmloader.StopScan();
	g_ppsPlayer.StopScan();
	g_pptvPlayer.StopScan();
	g_qvodPlayer.StopScan();
	g_qqDownloader.StopScan();
	g_sogoClean.StopScan();
	g_operaClean.StopScan();
	g_FixitClean.StopScan();
	g_AliimClean.StopScan();
	g_Winlivemsg.StopScan();
//	g_listProcessName.clear();

	DWORD dwRet = WaitForSingleObject(g_hThread, 1000 );

	if (dwRet == WAIT_TIMEOUT)
	{	
		//��ʱ
		OutputDebugString(_T("DZ_StopScan ��ʱ"));
		return TRUE;
	}
	else if (WAIT_OBJECT_0)
	{
		//�ɹ�
		OutputDebugString(_T("DZ_StopScan ��������"));
		return TRUE;
	}
	else
	{
		//����
		OutputDebugString(_T("DZ_StopScan ����"));
		return TRUE;
	}

	return TRUE;
}

BOOL CKClearProc::DZ_StartScanBage(GARBAINFO* garbInfo)
{
	g_garbageClean.Start();

	GARBAINFO_IN	garbainfo_in;
	for (int i=0;i<garbInfo->iPathCount;i++)
	{	
		SCANPATH_IN scanpath_in;
		scanpath_in.iType = garbInfo->pScanPath[i].iType;
		scanpath_in.strScanFile = garbInfo->pScanPath[i].szScanFile;
		garbainfo_in.vec_scanPathInfo.Add(scanpath_in);
	
	}
	
	for (int i=0;i<garbInfo->iExitsCount;i++)
	{
		FILEEXTS_IN fileexts_in;
		fileexts_in.iType = garbInfo->pFileExts[i].iType;
		fileexts_in.strFileExts = garbInfo->pFileExts[i].szFileExts;
		garbainfo_in.vec_fileExtsInfo.Add(fileexts_in);
	}


	g_hBageThread = (HANDLE) _beginthreadex(NULL,NULL,BageThread,(void*)&garbainfo_in,NULL,NULL);
	if (g_hBageThread == NULL)
		return FALSE;

	Sleep(2000);

	return TRUE;

}

BOOL CKClearProc::DZ_StopScanBage()
{
	g_garbageClean.StopScan();

	DWORD dwRet = WaitForSingleObject(g_hBageThread, 1000 );

	if (dwRet == WAIT_TIMEOUT)
	{	
		//��ʱ
		OutputDebugString(_T("DZ_StopScanBage ��ʱ"));
		return TRUE;
	}
	else if (WAIT_OBJECT_0)
	{
		//�ɹ�
		OutputDebugString(_T("DZ_StopScanBage ��������"));
		return TRUE;
	}
	else
	{
		//����
		OutputDebugString(_T("DZ_StopScanBage ����"));
		return TRUE;
	}

	return TRUE;
}

BOOL CKClearProc::DZ_CleanReg(RegInfo* pRegInfo,int iCount)
{
	
	VEC_REGINFO vec_regInfo;
	for (int i=0;i<iCount;i++)
	{
		RegInfo_in regInfo;
		regInfo.iType = pRegInfo[i].iType;
		regInfo.strKeyFullPath = pRegInfo[i].szKeyFullPath;
		regInfo.strValueName = pRegInfo[i].szValueName;
		vec_regInfo.Add(regInfo);
	}

	g_hThreadCleanReg = (HANDLE) _beginthreadex(NULL,NULL,CleanRegThread,(void*)&vec_regInfo,NULL,NULL);
	if (g_hThreadCleanReg == NULL)
		return FALSE;

	Sleep(2000);
	return TRUE;
}

BOOL CKClearProc::DZ_CleanFile(FileInfo* pFileInfo,int iCount)
{	
	VEC_FILEINFO vec_fileInfo;
	for (int i=0;i<iCount;i++)
	{
		FileInfo_in fileInfo;
		fileInfo.iType = pFileInfo[i].iType;
		fileInfo.strFileFullPath = pFileInfo[i].szFileFullPath;
		vec_fileInfo.Add(fileInfo);
	}

	g_hThreadCleanFile = (HANDLE) _beginthreadex(NULL,NULL,CleanFileThread,(void*)&vec_fileInfo,NULL,NULL);
	if (g_hThreadCleanReg == NULL)
		return FALSE;

	Sleep(2000);

	return TRUE;
}

unsigned int __stdcall DistributeThread(void* parm)
{	
	CSimpleArray<TYPEINFO> vec_typeInfo = *((CSimpleArray<TYPEINFO>* )parm);

	g_hRun = TRUE;

	//����
	for (int i=0;i<vec_typeInfo.GetSize();i++)
	{
		if (!g_hRun)
		{
			break;
		}
		int iType = vec_typeInfo[i].iType/1000;
		switch(iType)
		{
		case 1:
			IEClean(vec_typeInfo[i].iType,g_ieClean);
			break;
		case 2:
			WinsHistory(vec_typeInfo[i].iType,g_winHistory);
			break;
		case 3:
			RegClean(vec_typeInfo[i].iType,g_regClean);
			break;
		case 4:
			GarbClean(vec_typeInfo[i].iType,g_winHistory);
			break;
		case 5:
			switch(vec_typeInfo[i].iType)
			{
			case BROWSERSCLEAN_CHROME:
				g_chromClean.ScanChrome();
				break;
			case BROWSERSCLEAN_FIREFOX:
				g_firefoxClean.ScanFireFox();
				break;
			case BROWSERSCLEAN_MAXTHON:
				g_maxmonthClean.ScanMaxMonthClean();
				break;
			case BROWSERSCLEAN_TT:
				g_ttClean.ScanTT();
				break;
			case BROWSERSCLEAN_360:
				g_360Clean.Scan360Clean();
				break;
			case BROWSERSCLEAN_WORDWIN:
				g_wordWinClean.ScanWordWinClean();
				break;
			case BROWSERSCLEAN_MYIE2:
				g_SpecialApp.CleanMyIE2();
				break;
			case BROWSERSCLEAN_SOGO:
				g_sogoClean.ScanSogoHistory();
				break;
			case SOGO_ADVFORM:
				g_sogoClean.ScanSogoAdvForm();
				break;
			case SOGO_COOKIES:
				g_sogoClean.ScanSogoCookies();
				break;
			case SOGO_FORM:
				g_sogoClean.ScanSogoForm();
				break;
			case SOGO_PASS:
				g_sogoClean.ScanSogoPass();
				break;
			case BROWSERSCLEAN_OPERA:
				g_operaClean.ScanOperaHistory();
				break;
			case OPERA_COOKIES:
				g_operaClean.ScanOperaCookies();
				break;
			case OPERA_FORM:
				g_operaClean.ScanOperaForm();
				break;
			}
		case 6:
			switch(vec_typeInfo[i].iType)
			{
			case IECLEAN_PASSWORD:
				g_ieClean.ScanIEPass(IECLEAN_PASSWORD);
				break;
			case IECLEAN_SAVEFROM:
				g_ieClean.ScanIEFrom(IECLEAN_SAVEFROM);
				break;
			case MAXTHON_PASS:
				g_ieClean.ScanIEFrom(MAXTHON_PASS);
				break;
			case MAXTHON_FORM:
				g_ieClean.ScanIEPass(MAXTHON_FORM);
				break;
			case THEWORLD_PASS:
				g_ieClean.ScanIEFrom(THEWORLD_PASS);
				break;
			case THEWORLD_FORM:
				g_ieClean.ScanIEPass(THEWORLD_FORM);
				break;
			case CHROME_PASSWORD:
				g_chromClean.ScanChromePass();
				break;
			case CHROME_SAVEFROM:
				g_chromClean.ScanChromeFrom();
				break;
			case FIREFOX_PASSWORD:
				g_firefoxClean.ScanFirePass();
					break;
			case FIREFOX_SAVEFROM:
				g_firefoxClean.ScanFireFrom();
					break;
			case PASSANDFROM_360:
				g_360Clean.Scan360User(PASSANDFROM_360);
					break;
			case PASSANDFROM_TT:
				g_360Clean.Scan360User(PASSANDFROM_TT);
				break;
			case WORDWIN_USER:
				g_wordWinClean.ScanWordWinUser();
					break;
			case FIREFOX_COOKIES:
				g_firefoxClean.ScanFireFoxCookies();
				break;
			case CHROME_COOKIES:
				g_chromClean.ScanChormCookies();
				break;

			}
		case 9:
			switch (vec_typeInfo[i].iType)
			{
			case THUNDERDOWNLOADER:
				g_ThunderDownloader.ScanThunder();
				break;
			case FLASHGETDOWNLOADER:
				g_FlashGetDownloader.ScanFlashGet();
				break;
			case BITCOMETDOWNLOADER:
				g_BitcometDowmloader.ScanBitComet();
				break;
			case PPS_PLAYER:
				g_ppsPlayer.ScanPPS();
				break;
			case PPTV_PLAYER:
				g_pptvPlayer.ScanPPTV();
				break;
			case QVOD_PLAYER:
				g_qvodPlayer.ScanQVOD();
				break;
			case QQDOWNLOADER:
				g_qqDownloader.ScanQQDownloader();
				break;
			case FENGXING_PLAYER:
				g_fengxingClean.ScanFengxingPlayer();
				break;
			case SHESHOU_PLAYER:
				g_sheshouClean.ScanSheshouPlayer();
				break;
			case KUWOMUSIC_PLAYER:
				g_kuwoClean.ScanKuwoPlayer();
				break;
			case FUXINPDF_READER:
				g_FixitClean.ScanFixitPlayer();
				break;
			case ALIIM_IM:
				g_AliimClean.ScanAliim();
				break;
			case WINLIVE_MSG:
				g_Winlivemsg.ScanWinlivemsg();
				break;
			case XUNLEI7_DOWNLOADER:
				g_SpecialApp.ScanXunleiSearch(XUNLEI7_DOWNLOADER);
				break;
			default:	
				AppHistory(vec_typeInfo[i].iType,g_appHistory,g_SpecialApp,CKClearProc::s_map_softwareinfo);
				break;
			}
		}		

	}
	
	//������ļ���
	//if(g_bIsClean == TRUE)
	//{	
	//	WCHAR* pEnv;
	//	pEnv = _wgetenv(_T("USERPROFILE"));
	//	if (pEnv !=NULL)
	//	{
	//		g_fileOpt.DeleteEmptyDirectories(pEnv);
	//	}
	//	
	//}
	
//	g_regBack.RegisterExport(NULL);

	g_fnScanFile(g_pMain,0000,_T(""),0,0);
	g_fnScanReg(g_pMain,0000,_T(""),0,0);

	g_listProcessName.clear();
	_endthreadex(0);
	return 0;
}

unsigned int __stdcall BageThread(void* parm)
{	
	OutputDebugString(_T("�����߳̿�ʼ......\n"));

	GARBAINFO_IN vec_typeInfo = *((GARBAINFO_IN*)parm);
	
	g_fnScanFile(g_pMain,BEGINPROC(FILEGARBAGE_EXTS),0,0,0);
	
	for (int i=0; i< vec_typeInfo.vec_scanPathInfo.GetSize() ;i++)
	{	

		g_garbageClean.ScanGarbageFile(
			vec_typeInfo.vec_scanPathInfo[i].strScanFile.GetBuffer(),
			vec_typeInfo.vec_fileExtsInfo
			);
		vec_typeInfo.vec_scanPathInfo[i].strScanFile.ReleaseBuffer();
	}
	
	g_fnScanFile(g_pMain,ENDPROC(FILEGARBAGE_EXTS),0,0,0);

	g_fnScanFile(g_pMain,0000,_T(""),0,0);
	g_fnScanReg(g_pMain,0000,_T(""),0,0);

	_endthreadex(0);
	return 0;
}
/************************************************************************/
/* ע��������߳�
/************************************************************************/

unsigned int __stdcall CleanRegThread(void* parm)
{	
	VEC_REGINFO vec_regInfo = *((VEC_REGINFO*)parm);
	CRegOpt regOpt;
	
	if(vec_regInfo.GetSize()<=0)
		return 0;
	
	g_fnScanRegError(g_pMainError,BEGINPROC(vec_regInfo[0].iType),NULL,NULL);
	int iType =  vec_regInfo[0].iType;

	int i=0;
	for (i=0;i<vec_regInfo.GetSize();i++)
	{	

		if (iType != vec_regInfo[i].iType)
		{	
			//������ϴ����Ͳ�ͬ������ϴ�����,����������
			g_fnScanRegError(g_pMainError,ENDPROC(iType),NULL,NULL);

			g_fnScanRegError(g_pMainError,BEGINPROC(vec_regInfo[i].iType),NULL,NULL);
			iType =  vec_regInfo[i].iType;
		}
		
		if (FALSE==CleanReg(vec_regInfo[i].iType,vec_regInfo[i].strKeyFullPath,vec_regInfo[i].strValueName))
		{
            KCLEAR_LOG(LOG_LEVEL_TRACKCLEAN) << "Clean Failed:" 
                << UnicodeToAnsi(vec_regInfo[i].strKeyFullPath.GetBuffer())
                << "--"
                << UnicodeToAnsi(vec_regInfo[i].strValueName.GetBuffer());
			g_fnScanRegError(g_pMainError,vec_regInfo[i].iType,vec_regInfo[i].strKeyFullPath,vec_regInfo[i].strValueName);
		}
        else
        {
            KCLEAR_LOG(LOG_LEVEL_TRACKCLEAN) << "Clean Successed:" 
                << UnicodeToAnsi(vec_regInfo[i].strKeyFullPath.GetBuffer())
                << "--"
                << UnicodeToAnsi(vec_regInfo[i].strValueName.GetBuffer());
        }
	
	}
	g_fnScanRegError(g_pMainError,ENDPROC(vec_regInfo[i-1].iType),NULL,NULL);

	
//	g_regBack.RegisterExport(NULL);
//	g_regBack.RestRegister(NULL);

	OutputDebugString(_T("Reg�������"));
	g_fnScanRegError(g_pMainError,0000,_T(""),0);

	_endthreadex(0);
	return 0;
}

/************************************************************************/
/* ע���������
/************************************************************************/


BOOL CleanReg(int iType,CString& strRegeFullPath,CString& strValueName)
{	
	OutputDebugString(_T("\n��������ʼ\n"));

	HKEY	hRootKey;
	CString strSubKey;
	//CRegOpt regOpt;
	g_regOpt.CrackRegKey(strRegeFullPath,hRootKey,strSubKey);

	if (strValueName==_T(""))	//���Ϊ����ɾ����ֵ���Ӽ�
	{	
	//	g_regBack.AppendValueToString(hRootKey,strSubKey);

		if (FALSE == g_regOpt.RegDelnode(hRootKey,strSubKey))
		{	
			if (g_regOpt.GetErrorCode() == ERROR_FILE_NOT_FOUND)
				return TRUE;

			return FALSE;

		}

	}
	else //ɾ��ֵ
	{	
		if (strValueName==_T("Ĭ��ֵ"))
		{
			strValueName=_T("");
		}

	//	g_regBack.AppendValueToString(hRootKey,strSubKey,strValueName);
		
		if (FALSE == g_regOpt.RegDelValue(hRootKey,strSubKey,strValueName))
		{	
			DWORD dwErrCode= g_regOpt.GetErrorCode();
			if (dwErrCode == ERROR_FILE_NOT_FOUND)
			{
				OutputDebugString(_T("ɾ���ļ�ʱû���ҵ�"));
				return TRUE;
			}
			else if(dwErrCode == ERROR_ACCESS_DENIED)
			{
				OutputDebugString(_T("ɾ��ע���ܾ�����"));
				return FALSE;
			}
			else
			{	
				OutputDebugString(_T("��������"));
				return FALSE;
			}	
		}

	}	
	

	OutputDebugString(_T("\n����������\n"));

	return TRUE;

}

/************************************************************************/
/* �ļ������߳�
/************************************************************************/
unsigned int __stdcall CleanFileThread(void* parm)
{

	VEC_FILEINFO vec_fileInfo = *((VEC_FILEINFO*)parm);
	
	if(vec_fileInfo.GetSize()<=0)
		return 0;

	g_fnScanFileError(g_pMainError,BEGINPROC(vec_fileInfo[0].iType),NULL,NULL,NULL);
	int iType =  vec_fileInfo[0].iType;
	
	int i;
	for (i=0; i<vec_fileInfo.GetSize();i++)
	{		
		if (iType != vec_fileInfo[i].iType)
		{	
			//������ϴ����Ͳ�ͬ������ϴ�����,����������
			g_fnScanFileError(g_pMainError,ENDPROC(iType),NULL,NULL,NULL);

			g_fnScanFileError(g_pMainError,BEGINPROC(vec_fileInfo[i].iType),NULL,NULL,NULL);
			iType =  vec_fileInfo[i].iType;
		}

		
		if(FALSE==CleanFile(vec_fileInfo[i].iType,vec_fileInfo[i].strFileFullPath))
		{	
            KCLEAR_LOG(LOG_LEVEL_TRACKCLEAN) << "Clean Failed :" << UnicodeToAnsi(vec_fileInfo[i].strFileFullPath.GetBuffer()); 

			MoveFileEx (vec_fileInfo[i].strFileFullPath,  NULL,  MOVEFILE_DELAY_UNTIL_REBOOT);  
			
			WIN32_FIND_DATA fd;
			HANDLE hFindFile = FindFirstFile(vec_fileInfo[i].strFileFullPath.GetBuffer(), &fd);
			vec_fileInfo[i].strFileFullPath.ReleaseBuffer();
			if(hFindFile == INVALID_HANDLE_VALUE)
			{	
				OutputDebugString(_T("�ļ�������"));
				::FindClose(hFindFile);
				continue;
			}
			::FindClose(hFindFile);

			g_fnScanFileError(g_pMainError,
				vec_fileInfo[i].iType,
				vec_fileInfo[i].strFileFullPath,
				fd.nFileSizeLow,fd.nFileSizeHigh
				);
		}
        else
        {
            KCLEAR_LOG(LOG_LEVEL_TRACKCLEAN) << "Clean Successed:" << UnicodeToAnsi(vec_fileInfo[i].strFileFullPath.GetBuffer()); 
        }
	
	}
	g_fnScanFileError(g_pMainError,ENDPROC(vec_fileInfo[i-1].iType),NULL,NULL,NULL);
	

	//ɾ�����ļ���
	//WCHAR* pEnv;
	//pEnv = _wgetenv(_T("USERPROFILE"));
	//if (pEnv !=NULL)
	//{
	//	g_fileOpt.DeleteEmptyDirectories(pEnv);
	//}


	g_fnScanFileError(g_pMainError,0,_T(""),0,0);
	
	OutputDebugString(_T("File�������"));
	_endthreadex(0);
	return 0;
}

/************************************************************************/
/* �ļ�������
/************************************************************************/
BOOL CleanFile(int _iType,CString& strFileFullPath)
{	
	int iType = _iType/1000;

	switch (iType)
	{
	case 1:
		switch (_iType)
		{
		case IECLEAN_INDEXDATA:		//index.dat��ַ��¼
			{
				g_ieClean.CleanIndexDat();
				return TRUE;
			}
		case IECLEAN_HISTORY:
			{
				if (g_ieClean.CleanIEHistory(strFileFullPath))
				{
					return TRUE;
				}
			}
			break;
		default:
			{

			}
		}
		break;

	case 2:
		switch (_iType)
		{
		case WINSHISTORY_CLIPBOARD:
			if (OpenClipboard(NULL)==TRUE)
			{
				EmptyClipboard();
			}
			CloseClipboard();
			return TRUE;
		case WINDOWS_RECYCLE:	//����վ
			{
				SHEmptyRecycleBin(NULL,NULL,SHERB_NOCONFIRMATION|SHERB_NOPROGRESSUI|
					SHERB_NOSOUND);
				return TRUE;
			}
		}
		break;

	case 3:
		break;

	case 4:
		switch (_iType)
		{
		case FILEGARBAGE_RECYCLED:	//����վ
			{
				SHEmptyRecycleBin(NULL,NULL,SHERB_NOCONFIRMATION|SHERB_NOPROGRESSUI|
					SHERB_NOSOUND);
				return TRUE;
			}
		}
		break;

	case 5:
		switch (_iType)
		{
		case BROWSERSCLEAN_MYIE2:		//myie2
			{
				if (g_SpecialApp.CleanMyIE2_Clean(iType,strFileFullPath))
				{
					return FALSE;
				}
				return TRUE;	
			}
        case BROWSERSCLEAN_FIREFOX:		//���
            {
                if (g_firefoxClean.CleanFireFox(strFileFullPath))
                {
                    return TRUE;
                }
                
            }
			break;
        case BROWSERSCLEAN_CHROME:
            {
                if (g_chromClean.CleanChrome(strFileFullPath))
				{
					return TRUE;
				}
				

            }
			break;
        case BROWSERSCLEAN_TT:
            {
                if (g_ttClean.CleanTT(strFileFullPath))
				{
					return TRUE;
				}
				
            }
			break;
		case BROWSERSCLEAN_WORDWIN:
			{
				if (g_wordWinClean.CleanWorldIni(strFileFullPath))
				{
					return TRUE;
				}

			}
			break;
		case BROWSERSCLEAN_MAXTHON:
			{
				if (g_maxmonthClean.CleanMaxmonthIni(strFileFullPath))
				{
					return TRUE;
				}

			}
			break;
		case SOGO_COOKIES:
			{
				if (g_sogoClean.CleanSogoCookies(strFileFullPath.GetBuffer()))
				{
					return TRUE;
				}

			}
			break;
		case SOGO_ADVFORM:
			{
				if (g_sogoClean.CleanSogoAdvForm(strFileFullPath.GetBuffer()))
				{
					return TRUE;
				}

			}
			break;
		case BROWSERSCLEAN_SOGO:
			{
				if (g_sogoClean.CleanSogoHistory(strFileFullPath.GetBuffer()))
				{
					return TRUE;
				}

			}
			break;
		case SOGO_PASS:
			{
				if (g_sogoClean.CleanSogoPass())
				{
					return TRUE;
				}

			}
			break;
		case SOGO_FORM:
			{
				if (g_sogoClean.CleanSogoForm())
				{
					return TRUE;
				}

			}
			break;
		case BROWSERSCLEAN_OPERA:
			{
				if (g_operaClean.CleanOperaHistory(strFileFullPath.GetBuffer()))
				{
					return TRUE;
				}
			}
		default: break;

		}
		break;
	
	case 6:
		switch (_iType)
		{
		case IECLEAN_PASSWORD:		//ie����
			{
				g_ieClean.IEFrom_Clean();
				return TRUE;
			}
			break;
		case IECLEAN_SAVEFROM:		//ie��
			{
				g_ieClean.CleanIEPassword();
				return TRUE;
			}
			break;

		case MAXTHON_PASS:		//ie����
			{
				g_ieClean.IEFrom_Clean();
				return TRUE;
			}
			break;
		case MAXTHON_FORM:		//ie��
			{
				g_ieClean.CleanIEPassword();
				return TRUE;
			}
			break;
            
        case FIREFOX_SAVEFROM:		//�����
            {
                g_firefoxClean.CleanFireFoxForm(strFileFullPath);
                return TRUE;
            }
            break;
		case FIREFOX_PASSWORD:
			{
				g_firefoxClean.CleanFireFoxPass(strFileFullPath);
				return TRUE;

			}
        case CHROME_SAVEFROM:
            {
                g_chromClean.CleanChromeForm(strFileFullPath);
                return TRUE;
            }
			break;
		case CHROME_COOKIES:
			{
				g_chromClean.CleanChromCookies(strFileFullPath);
				return TRUE;
			}
			break;
        case CHROME_PASSWORD:
            {
                g_chromClean.CleanChromePass(strFileFullPath);
                return TRUE;
            }
			break;
		case WORDWIN_USER:
			{
				g_wordWinClean.CleanWordWinUser(strFileFullPath);
				return TRUE;
			}
			break;
		case PASSANDFROM_360:
			{
				g_360Clean.Clean360User(strFileFullPath);
				return TRUE;
			}
			break;
		case PASSANDFROM_TT:
			{
				g_360Clean.Clean360User(strFileFullPath);
				return TRUE;
			}
			break;
		case FIREFOX_COOKIES:
			{
				g_firefoxClean.CleanFireFoxCookies(strFileFullPath);
				return TRUE;
			}
			break;
		}

		break;

	case 9:
		switch (_iType)
		{
		case 9029:					//UltralEdit
			if (TRUE ==g_SpecialApp.CleanUltraEdit_Clean(iType,strFileFullPath))
			{
				return TRUE;
			}	
			break;
		case 9010:					//Kugoo
			if (TRUE == g_SpecialApp.CleanKuGoo_Clean(iType,strFileFullPath))
			{
				return TRUE;
			}
			break;	
		case 9008:					//����Ӱ��,�������FALSE����fun����Ϊ��ͨ������
			if (TRUE == g_SpecialApp.CleanStorm_Clean(iType,strFileFullPath))
			{
				return TRUE;
			}
			break;
		case 9043:
			if (TRUE == g_qvodPlayer.CleanQcod(iType, strFileFullPath))
			{
				return TRUE;
			}
			break;

		case 9042:
			if (TRUE == g_pptvPlayer.CleanPPTV(strFileFullPath))
			{
				return TRUE;
			}
			break;
		case BITCOMETDOWNLOADER:
			if (TRUE == g_BitcometDowmloader.CleanBitcomet(strFileFullPath))
			{
				return TRUE;
			}
			break;
		case PPS_PLAYER:
			if (TRUE == g_ppsPlayer.CleanPPS(strFileFullPath))
			{
				return TRUE;
			}
			break;
		case KUWOMUSIC_PLAYER:
			if (TRUE == g_kuwoClean.CleanKuWo(strFileFullPath))
			{
				return TRUE;
			}
			break;
		case XUNLEI7_DOWNLOADER:
			if (TRUE == g_SpecialApp.CleanXunleiSearch(strFileFullPath))
			{
				return TRUE;
			}
		//case THUNDERDOWNLOADER:
		//	if (TRUE == g_ThunderDownloader.CleanThunder(strFileFullPath))
		//	{
		//		return TRUE;
		//	}
		//	break;
		}	
		break;
	}

	::OutputDebugString(strFileFullPath);
	if(FALSE==DeleteFile(strFileFullPath))
	{
		DWORD dwErrCode = GetLastError();
		if (dwErrCode == ERROR_FILE_NOT_FOUND)
		{
			OutputDebugString(_T("�ļ�û���ҵ�"));
			return TRUE;
		}
		else if (dwErrCode == ERROR_ACCESS_DENIED)
		{
			OutputDebugString(_T("û�з���Ȩ��"));
		}
		else
		{
			OutputDebugString(_T("��������"));
		}
		return FALSE;
	}
	
	return TRUE;
}

/************************************************************************/
/* ɨ��ת������
/************************************************************************/

BOOL __stdcall _ScanRegCallBack(void* pMain,int iType,LPCTSTR lpcszKeyFullPath,LPCTSTR lpcszValueName,LPCTSTR lpcszValueData)
{	
	OutputDebugString(_T("\n��ʼ\n"));
	g_fnOutScanReg(pMain,iType,lpcszKeyFullPath,lpcszValueName,lpcszValueData);
	
	if (FALSE == g_bIsClean)
		return TRUE;


	//����Ч����Ϣ,ActriveX,����Ч�����Ľ������⴦��,��֤����ȫɾ�� ����Ϣ..Ȼ���� Activex ���Ϊ������

	static VEC_REGINFO vec_speci_regInfo;
	if(iType == BEGINPROC(REGCLEAN_FAILCLASS)||
		iType == BEGINPROC(REGCLEAN_FAILACTIVEX)||
		iType == BEGINPROC(REGCLEAN_FAILAFILEASS)
	)
	{	
		return TRUE;
	}
	else if (iType == REGCLEAN_FAILCLASS||
		iType == REGCLEAN_FAILACTIVEX||
		iType == REGCLEAN_FAILAFILEASS
		)
	{
		RegInfo_in regInfo;
		regInfo.iType = iType;
		regInfo.strKeyFullPath = lpcszKeyFullPath;
		if(wcscmp(lpcszValueName,_T("Ĭ��ֵ"))==0)
			regInfo.strValueName = _T("");
		else
			regInfo.strValueName = lpcszValueName;

		vec_speci_regInfo.Add(regInfo);
		return TRUE;
	}
	else if (iType == ENDPROC(REGCLEAN_FAILCLASS)||
		iType == ENDPROC(REGCLEAN_FAILACTIVEX)||
		iType == ENDPROC(REGCLEAN_FAILAFILEASS)
		)
	{
		for (int i=0;i<vec_speci_regInfo.GetSize();i++)
		{	
			//���ֵ
			CString strRegFullPath = vec_speci_regInfo[i].strKeyFullPath;
			CString strValueName= vec_speci_regInfo[i].strValueName;
			if (FALSE==CleanReg(iType,strRegFullPath,strValueName))
			{
				g_fnScanRegError(g_pMainError,vec_speci_regInfo[i].iType,
					vec_speci_regInfo[i].strKeyFullPath,
					vec_speci_regInfo[i].strValueName
					);
			}

		}
		vec_speci_regInfo.RemoveAll();

		return TRUE;
	}


	//ͨ�ô���
	static VEC_REGINFO vec_regInfo;
	
	if (((iType/100)-((iType/1000)*10)) == 1)	//��ʼ���
	{
		return TRUE;
	}
	else if (((iType/100)-((iType/1000)*10)) == 2||
		iType == 0
		) //�������
	{
		for (int i=0;i<vec_regInfo.GetSize();i++)
		{	
			//���ֵ
			CString strRegFullPath = vec_regInfo[i].strKeyFullPath;
			CString strValueName= vec_regInfo[i].strValueName;
			if (FALSE==CleanReg(iType,strRegFullPath,strValueName))
			{
				g_fnScanRegError(g_pMainError,vec_regInfo[i].iType,
					vec_regInfo[i].strKeyFullPath,
					vec_regInfo[i].strValueName
					);
			}

		}
		
		vec_regInfo.RemoveAll();
	}
	else
	{
		RegInfo_in regInfo;
		regInfo.iType = iType;
		regInfo.strKeyFullPath = lpcszKeyFullPath;
		if(wcscmp(lpcszValueName,_T("Ĭ��ֵ"))==0)
			regInfo.strValueName = _T("");
		else
			regInfo.strValueName = lpcszValueName;
		vec_regInfo.Add(regInfo);
	}
	
	OutputDebugString(_T("\n����\n"));

	return TRUE;
}

BOOL __stdcall _ScanFileCallBack(void* pMain,int iType,LPCTSTR lpcszFileFullPath,DWORD dwFileLowPart,LONG dwFileHighPart)
{	

	g_fnOutScanFile(pMain,iType,lpcszFileFullPath,dwFileLowPart,dwFileHighPart);
	
	if (lpcszFileFullPath==NULL||wcscmp(lpcszFileFullPath,_T(""))==0)
	{
		return TRUE;
	}

	if (TRUE == g_bIsClean)
	{	
		CString strFileFullPath = lpcszFileFullPath;
		if (FALSE==CleanFile(iType,strFileFullPath))
		{
			MoveFileEx (strFileFullPath,  NULL,  MOVEFILE_DELAY_UNTIL_REBOOT);  

			WIN32_FIND_DATA fd;
			HANDLE hFindFile = FindFirstFile(strFileFullPath.GetBuffer(), &fd);
			strFileFullPath.ReleaseBuffer();
			if(hFindFile == INVALID_HANDLE_VALUE)
			{	
				OutputDebugString(_T("\n�ļ�������\n"));
				::FindClose(hFindFile);
				return TRUE;
			}
			::FindClose(hFindFile);

			g_fnScanFileError(g_pMainError,
				iType,
				lpcszFileFullPath,
				fd.nFileSizeLow,fd.nFileSizeHigh
				);
		}
		
	}
	else
	{
		
	}
	

	return TRUE;
}

DWORD GetProcessIdFromName(LPCTSTR szProcessName)
{
	PROCESSENTRY32 pe;
	DWORD id = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	if( !Process32First(hSnapshot,&pe) )
		return 0;
	while(1)
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if( Process32Next(hSnapshot,&pe)==FALSE )
			break;
		if(wcscmp(pe.szExeFile,szProcessName) == 0)
		{
			id = pe.th32ProcessID;
			break;
		}

	}
	CloseHandle(hSnapshot);
	return id;
}

DWORD GetCurrentProcessName()
{
	PROCESSENTRY32 pe;
	DWORD id = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	g_listProcessName.clear();
	if( !Process32First(hSnapshot,&pe) )
		return 0;
	while(1)
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if( Process32Next(hSnapshot,&pe)==FALSE )
			break;
		g_listProcessName.push_back(pe.szExeFile);
	}
	CloseHandle(hSnapshot);
	return id;
}