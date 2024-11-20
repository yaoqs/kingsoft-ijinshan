/* -------------------------------------------------------------------------
// �ļ���		:	common/commondefine.h
// ������		:	chenghui
// ����ʱ��		:	2009-3-31 17:34:01
// ��������     :	
//
// $Id: $
// -----------------------------------------------------------------------*/
#ifndef __COMMON_COMMONDEFINE_H__
#define __COMMON_COMMONDEFINE_H__


#define KWS_SERVICE_NAME  L"Kingsoft Antivirus WebShield Service"


// -------------------------------------------------------------------------
#define KWSCMD_MAINVER		L"beta"

// ������Ļ���������
#define KWS_MUTEX L"AFX_KWSMAIN2_CPP__2E3C367A-9ED5-4d83-B23B-5FD132BDE717__"

// �����������ж���
#define KWSCMD_INSTALL		L"/install"			// ��װ����
#define KWSCMD_UNINSTALL	L"/uninstall"		// ж�ص���

#define KWSCMD_SHOWMAIN			L"/showmain"		// ��ʾ������
#define KWSCMD_SHOWSETTING		L"/showsetting"		// ��ʾ����ҳ��
#define KWSCMD_SHOWTRUSTLIST	L"/showtrustlist"	//��ʾ���õ������б�ҳ
#define KWSCMD_DELTRUSTURL		L"/deltrusturl"		//ɾ��һ������url������ʾ�����б�ҳ
#define KWSCMD_SHOWADFILTER		L"/showadfilter"	// ��ʾ����
#define KWSCMD_SHOWADFILTER_KSAFE		L"/do:UI_kwssetting"	// ��ʾ����
#define KWSCMD_SHOWFEEDBACK		L"/showfeedback"	// ��ʾ����ҳ
#define KWSCMD_SHOWLOG			L"/showlog"			// ��ʾ��־ҳ
#define KWSCMD_SHOWWHITEBLACK	L"/showwhiteblack"			// ��ʾ�ڰ�����ҳ
#define KWSCMD_SHOWLSP			L"/showlsp"			// ��ʾ��ҳ����ҳ
#define KWSCMD_FEEDBACK			L"/feedback"			// ��ʾ��ҳ����ҳ

#define KWSCMD_SCANFILE			L"/scanfile"       // ɨ���ļ�

#define KWSCMD_SHOWDNSF			L"/showdownfile"	//�����ذ�ȫҳ

// ԭ����������������С�Ϊ�˼��ݣ�������������������л�ֱ�Ӱ������������Լ��˳���
#define KWSCMD_STARTUP			L"/start" 

#define KWSCMD_CLOSE			L"/close"		// �ر������棨���̵��ã�
#define KWSCMD_ENABLE			L"/kwsenable"	// �������������̵��ã�
#define KWSCMD_DISABLE			L"/kwsdisable"	// �رձ��������̵��ã�
//----------------------------------------------------------------------------------
// ���̵�exe
#define KWSTIP_FILENAME			L"kwstray.exe"
#define KWSTRAY_MUTEX			L"{5BA2D87A-A0C4-4e0e-883E-9993AB132272}"

// ���̵�������
#define KWSTRAY_CMD_STARTUP		L"/start"		// ��������
#define KWSTRAY_CMD_POP			L"/pop"			// ����������tray�����񴥷���
#define KWSTRAY_CMD_SHOWTRAY	L"/showtray"	// ��������ʾ������tray����������������ʾ�����񴥷���

#define KWSTRAY_CMD_CLOSE		L"/close"		// �ر�����
#define KWSTRAY_CMD_INSTALL		L"/install"		// ��װ����

#define KWSTRAY_CMD_CLOSE_ANOTHER	L"/cl_another"	//�ر�����ʵ��

#define KWSTRAY_CMD_DISUPREP    L"/disuprep"  // �ر�upreport

//----------------------------------------------------------------------------------
//���������С����ʡ���ַ������
//Add by: Xu yixin 20100317

#define KWSTRAY_CMD_SOW_SHELLEXECUTE	L"/sow_shellexecute"

//----------------------------------------------------------------------------------

// �������exe
#define KWSMAIN_FILENAME		L"kwsmain.exe"
#define KWSTIP_FILENAME_A		 "kwstray.exe"
#define KWSTIP_REGPATH_A		 "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
#define KWSTIP_REGKEY_W			L"kwstray"
#define KWSTIP_REGKEY_A			 "kwstray"

// pop
#define KWSPOP_DLL_NAME			L"kwspop.dll"

// kwsupd.exe
#define KWSUPDATE_EXE			L"kwsupd.exe"
// -------------------------------------------------------------------------
// ���������Ƿ�����MUTEX���ṩ��������ʹ���߲�ѯ����״̬
#define KWS_ENABLE_MUTEX		L"Global\\KWS_ENABLE_MUTEX_658B4D40-E61C-48b1-858A-0DA882FD9C67"

// ���������Ƿ�װ�ڻ����ϵ�ע���λ��
#define KWS_CHECK_INSTALL_KEY "SOFTWARE\\Kingsoft\\KSWSVC"
#define KWS_CHECK_INSTALL_VAL "installpath"

// ����ж��������־
#define	KWS_REBOOT_KEY_PATH "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"
#define	KWS_REBOOT_KEY_NAME	"kwsuninstalldel"

// -------------------------------------------------------------------------
// �°�Ľ���exe��صĲ�������
#define KWSMAIN_HTMLPANEL_MAIN			L"panel=0"
#define KWSMAIN_HTMLPANEL_SETTING		L"panel=1"
#define KWSMAIN_HTMLPANEL_WHITEBLACK	L"panel=2"
#define KWSMAIN_HTMLPANEL_LOG			L"panel=3"
#define KWSMAIN_HTMLPANEL_FEEDBACK		L"panel=4"
#define KWSMAIN_HTMLPANEL_LSP			L"panel=5"

/// 2009.11.06 yaojianfeng
/// Ϊ���������ļ���Ϣ����������������ļ���ӵ�ж����������������������ļ���Ϣ
/// ���º��������ñ��������ļ���ŵĶ�������ص�ַ���������ֵ���Լ��������ϵ�
/// �����ļ�����Ϣ
#define KWS_MALICE_DOWNLOAD_CONFIG_SECTION	L"LibUpdate"
#define KWS_MALICE_DOWNLOAD_CONFIG_KEY	L"URL"
#define KWS_MALICE_DOWNLOAD_INDEX_FILE L"kws_malice.index"

/// 2010.01.08 yaojianfeng
/// �������������
#define KWS_KSM_FUSION_DOWNLOAD_LOCAL_DIR_NAME L"ksys"
#define KWS_KSM_FUSION_DOWNLOAD_FILE_NAME L"ksysdiag.exe"
#define KWS_KSM_FUSION_REPAIR_FILE_NAME L"RepairKXE.exe"
#define KWS_KSM_FUSION_UNINSTALL_PARAM L"/uninstall"
#define KWS_KSM_FUSION_DOWNLOAD_PROCESS_PARAM L"/update"
#define KWS_KSM_DOWNLOAD_URL L"http://i2u.www.duba.net/i2u/kws3upd/ksys/ksysdiag.exe"
#define KWS_KSM_REPAIR_URL L"http://i2u.www.duba.net/i2u/kws3upd/ksys/RepairKXE.exe"

/// ���������־�ļ�����
#define KWS_ADBLOG   L"adblog.log"

// -------------------------------------------------------------------------
// $Log: $

#endif /* __COMMON_COMMONDEFINE_H__ */
