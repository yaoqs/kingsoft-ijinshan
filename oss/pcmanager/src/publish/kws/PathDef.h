///////////////////////////////////////////////////////////////
//
//	Filename: 	PathDef.h
//	Creator:	lichenglin  <lichenglin@kingsoft.com>
//	Date:		2009-3-18  18:58
//	Comment:	
//
///////////////////////////////////////////////////////////////


#ifndef _PathDef_h_
#define _PathDef_h_


#define REGKEY_KWS			     "SOFTWARE\\kingsoft\\KSWSVC"
#define REGKEY_PROPATH			 "ProgramPath"

#define REGKEY_KWSSERVICE       "SYSTEM\\CurrentControlSet\\Services\\Kingsoft Antivirus WebShield Service"

#define REGVALUE_ENABLE		     "en"             // �Ƿ�������

#define KWS_SWITCHS				 "switchs"
#define KWS_SWITCHS_DEFVAL       0xFFFF
#define KWS_SWITCH_FISHING		 0x0001			  // ���㿪��
#define KWS_SWITCH_ABICON		 0x0002			  // ��ַ��ͼ�꿪��
#define KWS_SWITCH_UPREPORT		 0x0004			  // upreport����
#define KWS_SWITCH_TIPSBANNER    0x0008           // IE��ʾ�����˿���
#define KWS_SWITCH_PROBRO		 0x0010           // ������������ܿ���
#define KWS_SWITCH_TROJAN        0x0020           /* ľ���� */
// ������ֵʱĬ���������ؿ�������ַ��ͼ�꿪�ؼ���ʾ�����˹ر�
#define KWS_SWITCHS_DEFVAL       (0xFFFF & ~KWS_SWITCH_ABICON) 

#define KWS_SEARCHENGINE_BAIDU      0x0001
#define KWS_SEARCHENGINE_GOOGLE     0x0002
#define KWS_SEARCHENGINE_SOGOU      0x0004
#define KWS_SEARCHENGINE_BING       0x0008
#define KWS_SEARCHENGINE_SOSO       0x0010
#define KWS_SEARCHENGINE_YOUDAO     0x0020

#define REGVALUE_FIRSTRUN	     "FirstRun"       // ��¼�Ƿ��Ѿ���ʾ���û����ܻ�����
#define REGVALUE_USETRAYICON     "usetrayicon"    // �Ƿ���������ͼ��
#define REGVALUE_USETRAYICON_W    L"usetrayicon"    // �Ƿ���������ͼ��
#define REGVALUE_SHOWBAIDUTIP	 L"ShowBaiduTip"		//�����Ƿ��ǰٶȵ�һ��������������Ӧ�����ѿ�
#define REGVALUE_CLOSEBAIDUSHOWED	L"CloseBDShowed"	//�رհٶȵĸ�֪�����Ƿ񵯳�
#define REGVALUE_SHINE           "enshine"        // �Ƿ�����
#define REGVALUE_COLOR_SAFE      "crsafe"         // ��ȫʱ������ɫ
#define REGVALUE_COLOR_WARN      "crwarn"         // ����ʱ������ɫ
#define REGVALUE_COLOR_DANGER    "crdanger"       // Σ��ʱ������ɫ
#define REGVALUE_SHINELEVL       "shinelevel"     // ����ʱ��

#define REGVALUE_SHIELDPROCESS   "shieldprocess"  // �û��Զ�����Ҫ�����Ľ��� 

#define UPDATE_PROGRAM_NAME		 "kwsupd.exe"

#define KWS_SETUP_CONFIG_FILE_NAME L"kwssetup.ini" // ��װ��ɺ��ȡ�������ļ�
#define KWS_SETTING_FILE		L"kws.ini"
#define KWS_SETTING_KEY			L"setting"
#define KWS_UPDATE_KEY			L"update"

#define KWSVALUE_LASTUPDATETIME		L"LastUpdate"	// ���һ������ʱ��
#define KWSVALUE_LASTFEEDBACKTIME		L"LastFeedback"	// ���һ���û�����ʱ��

#define KWSVALUE_SETUP_TIME				L"setupTime"	// ��װʱ��
#define KWSVALUE_DANGER_COUNT		L"dangerCount"	// ��в����

#define KWSVALUE_HIDETRAYBALLOON		L"hideballoon"	// ��������ʱ�����������Ƿ���ʾ	
#define KWSVALUE_SHOWTRAYSHINE			L"showtrayshine"	// ��������ʱ��������

#define KWSVALUE_SCANED_KPP			L"scanedkpp"		// �Ƿ�ɨ����ܱ�

#define KWSVALUE_LASTURLQUERY			L"LastUrlQuery"		// ���һ�β�ѯ�û���صı�����url��ʱ��

#define KWSVALUE_COLLECT			L"uic"		// �Ƿ��ռ����û���Ϣ

#define KWSVALUE_SEARCHENGINE       L"searchengine"

#define KWSVALUE_NEEDBLOCKDLG		L"needblockdlg"

#define KWSVALUE_LASTREPORTTIME     L"LastRep"

#define KWSVALUE_NEEDRCMKPP         L"needrcmkpp"  // �Ƿ���Ҫ�Ƽ��ܱ�
#define KWSVALUE_LASTRCMKPPTIME     L"lastrcmkpp"  // ����Ƽ��ܱ���ʱ��

#define KWSVALUE_LASTCOLUSINTIME    L"lastcousin"  // ����ռ��û���Ϣ��ʱ��

#define KWSVALUE_LASTCOLINFOCTIME	L"lastcolinfoc"		// ���һ���ռ���Ʒ��ʱ��

#define KWS_BIND_CONFIG_FILE_NAME L"kws_bind.cfg" // ��ɽ���ܴ�������Ʒ�İ������ļ���

#define KWS_UPDATE_CONFIG L"update.cfg"		// ��ɽ�������������ļ�

#define REGVALUE_VERSIONTYPE        "vt"		// ���ܰ汾����
#define KWS_VT_STANDARD				0x00		// ������
#define KWS_VT_DUBA					0x04		// ���԰�
#define KWS_VT_MAXTHON			    0x06		// ���ΰ�
#define KWS_VT_SOGOU				0x08		// �ѹ���

#define KWS_STARTPAGE				L"sp"			//������ҳ
#define KWS_LOCKSTARTPAGE			L"locksp"		//�Ƿ���������ҳ
#define KWS_LOCKSPFIRSTFLAG			L"lockspfirstflag" //��ҳ������д���ֵ

#define KWS_ENABLE_DOWN_FILEAUTO_SCAN			L"auto_scan_downfile"	// �����Զ�ɨ��
#define KWS_ENABLE_DOWN_FILEAUTO_CLEARVIRUS		L"auto_clean_virus"		// �����Զ��������
#define KWS_SHOW_SAFE_POP						L"show_safe_pop"		// ��ʾ��ȫ���ļ�������
#define KWS_SHOW_GRAY_POP						L"show_gray_pop"		// ��ʾδ֪���ļ�������
#define KWS_DOWN_FILE_IMPORT_FLAG				L"down_file_import_flag"	// �����ļ���־
#define KWS_DOWN_NEED_SHOW_TIP_POP				L"show_tip_pop"			//�Ƿ���ʾtip����
#define KWS_ENABLE_DOWNFILE_HELPER              L"auto_downfile_helper"  // �����ļ��������ֹ���


#define KWS_DP						L"dp"		   // �Ƿ������ر���
#define KWS_DLSOFT					L"dlsoft"      // ���ر���

#define KWS_HF						L"hfil"			// ��ҳ����

#define KWSVALUE_NEEDRCMLSP         L"needrcmlsp"  // �Ƿ���Ҫ�Ƽ���ҳ����

#define KWS_SVT						L"svt"			// ר��
#define KWS_SVTNAME					L"svtname"		// ר������
#define KWS_URLCHN					L"urlchn"		// url����
#define KWS_SVTURL					L"svturl"		// ר��url

#define KWS_SETUPTIME				L"SetupTime"	//��װʱ��
#define KWS_UNINTALLTIME			L"UninstallTime" //ж��ʱ��
#define KWS_INSTALLSERVER			L"http://kwsdata.duba.net/wdreporter/Install"
#define KWS_UNINSTALLSERVER			L"http://kwsdata.duba.net/wdreporter/Uninstall"

#define KWS_UDFAILED_TIMES			L"failedtimes"
#define KWS_UDFAILED_TIME			L"failedtime"

#define KWS_MOUSEPRO				L"mousepro"				//���ڿ���

#define KWS_BROWSERPRO				L"bspro"				//���������
#define KWS_BROWSERPATH				L"bspt"					//�����·��

#define KWSVALUE_NEEDRCMKSM			L"needrcmksm"			// �Ƽ�ʹ�ü������޸�
#define KWSVALUE_LASTRCMKSMTIME		L"lastrcmksm"		// ����Ƽ��������ʱ��

#define KWSVALUE_LASTSCANANTISF     L"lastscanas"       //���ɨ���Ƿ�װɱ���ʱ��

#define KWSVALUE_LASTFALSE_UPDATE	L"lastfalse"

#define KWSVALUE_LASTEEUTIME		L"lasteeu"			// ���ɨ�������ҳ��ʱ��

#define KWSADGUIDOVERSION           L"AdIdVer"           // ����Guid��version

#define KWSVALUE_SPMODIFYCOUNT      L"spmdcount"        //��ҳ���ĵĴ���

#define KWSVALUE_SHOW360SE			L"ssep"		// 360�����������ʾ����

#define KWSVALUE_RENAVIGATECOUNT    L"renv"     //��ҳ���ĺ�,����ǿת����ҳ�Ĵ���

#define KWSVALUE_MAXNOTIFY          L"maxntdis"    //MAXTHON��������������Ƿ��ֹ

#define KWSVALUE_LOCKSPNOTIFY       L"lockspntdis" //�Ƽ���ҳ���������Ƿ��ֹ
#define KWSVALUE_ADV_URL_BLOCK_DATE _T("ubd")           // ������ӱ����ص�����

#define KWS_TRAY_SHOW_CFGED			"iconConfiged"			//�Ƿ��Ѿ����ù�������ͼ����ʾ������

#define KWSVALUE_LASTSCANSPNTTIME   L"lastscannt"   //�ϴ�����ҳɨ�赯�ݵ�ʱ��

#define	KWSVALUE_NEEDCHECKAD        L"checkad"			//�Ƿ��һ�μ���涩��

#define KWSVALUE_ENABLE_ANTIADVLOG  _T("EnableAntiAdvLog")


#define KWSVALUE_RCM_ADV_DATE       L"timercmadvf"  //�����Ƽ�������ʱ�� 
#define KWSVALUE_LAST_RECOMMEND     L"lastrecmd"   // �ϴ��Ƽ������˹����ʱ��

#define KWSVALUE_NEEDCSC			L"needcsc"			//�Ƿ���Ҫ�޸Ŀ�ݷ�ʽ
#define KWSVALUE_NEEDFIXMXCFG		L"needfmxc"			//�Ƿ���Ҫ�޸İ��ΰ�����

#define KWS_SDBROWSERPATH				L"sdbspt"					//�Զ��������·��

#define KWS_LOCKMAXSP               L"lockmaxsp" //����������ҳ
#define KWS_DISMAXLOCKPOP           L"dismaxlkpop" //���ٵ���ʾ����������ҳ����
#define KWS_BSPPOP                  L"bsppop" //��ҳ�����������ݱ�ʶ

#define	KWSVALUE_MINISITE			L"minisite"			//�Ƿ��һ����ʾmini��
#define	KWSVALUE_MXMINISITE			L"mxminisite"			//�Ƿ��һ����ʾmxmini��
#define	KWSVALUE_MXMINISITE2		L"mxminisite2"			//�Ƿ��һ����ʾmxmini2��
#define	KWSVALUE_MINI36				L"mini36"			//�Ƿ��һ����ʾmini��

#define KWSVALUE_ONEKEY				L"onekey"
#define KWSVALUE_ONEKEY_WAITTIME	L"onekeytime"

#define KWSVALUE_UPD_STATUS         L"updstatus"




#define KWS_CFG_AntiAd_IsEnable      L"kws.antiad.is_enable"
#define KWS_CFG_AntiAd_IsHaveAnyRule L"kws.antiad.is_have_any_rule"

#define KWSVALUE_NEED_AUTORUN_HIT    L"need_autorun_hit"


#endif // _PathDef_h_
