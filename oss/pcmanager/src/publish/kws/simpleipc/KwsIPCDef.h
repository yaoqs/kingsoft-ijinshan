///////////////////////////////////////////////////////////////
//
//	Filename: 	KwsIPCDef.h
//	Creator:	lichenglin  <lichenglin@kingsoft.com>
//	Date:		2009-3-31  17:23
//	Comment:	
//
///////////////////////////////////////////////////////////////


#ifndef _KwsIPCDef_h_
#define _KwsIPCDef_h_

//////////////////////////////////////////////////////////////////////////
//
// ������
//
//////////////////////////////////////////////////////////////////////////

#define KWSIPCERR_OK           0  // OK
#define KWSIPCERR_UNKNOWN      1  // 
#define KWSIPCERR_INVALIDARG   2  // ��Ч����
#define KWSIPCERR_DATASIZE     3  // ���ݰ�̫��, ���ǱȽϴ�, ��֧�ִ�����
#define KWSIPCERR_OBJECT       4  // �����δ����, ���ͨ�Ŷ���ʧ��
#define KWSIPCERR_TIMEOUT      5  // �ȴ���ʱ




//////////////////////////////////////////////////////////////////////////
//
// Э��
//
//////////////////////////////////////////////////////////////////////////

#define MAX_PRTCL_DATA_SIZE  4096    

#define PRTCL_UNKNOWN            0

//-------------------------------------
// ��������
#define PRTCL_SHOWPOPO           1
#define PK_MSG      "msg"        /*[in]*/
#define PK_BTNTEXT  "btn"        /*[in]*/  
#define PK_STYLE    "style"      /*[in]*/    // "0": ����, "1": ����, "2": ����
#define PK_REASON	"reason"	 /*[in]*/    // ��ʾ�����ݵ�ԭ��
#define PK_URL		"url"	 /*[in]*/		// ��ʾ�����ݵ���ַ
#define PK_BROWSER  "browser"               // ��ʾ�����ݵ������

//-------------------------------------
// �������̱��״̬ 
#define PRTCL_SETTRAYSTATUS      2
// in:
#define PK_STATUS   "status"     /*[in]*/    // "0":���, "1": ����


//-------------------------------------
// ��ʾ����
#define PRTCL_SHOWTRAY           3
// in:
#define PK_SHOWTRAY "showtray"   /*[in]*/    // "0":����ʾ "1": ��ʾ
// out:


//-------------------------------------
// ��¼��־
#define PRTCL_LOG                4
// in:
#define PK_LOGFILE  "file"       /*[in]*/
#define PK_LOGMSG   "msg"        /*[in]*/
#define PK_LOGTYPE  "type"       /*[in]*/
typedef int LOGTYPE;
#define TY_ALL      0
#define TY_TROJAN   1
#define TY_FISHING  2

//-------------------------------------
// �˳����̳���
#define PRTCL_QUIT               5


//-------------------------------------
// ��ȡ����״̬
#define PRTCL_QUERYTRAYSTATUS    6
#define PK_TRAYSTATUS "ts"       /*[out]*/    // ��� TRAYSTATUS

#define PK_ACTIVESESSION    "session"     //��ǰ��û�Session

// �������˻Ὣһֱ����״̬�����������ݣ�ȡ���ͻ���Ϊ�����ݣ�
typedef int TRAYSTATUS;
#define TS_DEFAULT	0x00000000	 // Ĭ��״̬��ͼ�����������أ����˳��������ݣ�
#define TS_GRAY     0x00000001   // ͼ����
#define TS_HIDE     0x00000002   // ͼ������
#define TS_QUIT     0x00000004   // ��Ҫ�˳�����
#define TS_POPO     0x00000010   // ��������Ҫ����
#define TS_PROTECTPROGRAM     0x00000020   // �б���������
#define TS_TROJAN	0x00000040	 // ��������
#define TS_FISH		0x00000080	 // �����㿪��
#define TS_ENGINE	0x00000100	 // �������汣��
#define TS_FILTER	0x00000200	 // ��ҳ����



//-------------------------------------
// ��ѯ����, ������ʹ��
#define PRTCL_QUERYPOPOMSG       7
#define PK_POPOEXISTS "pe"       /*[out]*/    // �Ƿ���������Ҫ����   "0" û��   1"��"
//#define PK_MSG      "msg"      /*[out]*/    // ͬ: PRTCL_SHOWPOPO
//#define PK_BTNTEXT  "btn"      /*[out]*/    // ͬ: PRTCL_SHOWPOPO
//#define PK_STYLE    "style"    /*[out]*/    // ͬ: PRTCL_SHOWPOPO



//-------------------------------------
// �������̼�����
#define PRTCL_CALL_AS_USER       8
#define PRTCL_CALL_AS_SYSTEM     9
#define PRTCL_CALL_AS_USER_OR_SYSTEM       13   // �����û����̣������vista�·ǹ���Ա�û��򴴽�ϵͳ����
#define PRTCL_INJECT_SVC			14		  // ע��svchost
#define PRTCL_REG_CHANGE			15		  // ˢ��ע���cache
#define PRTCL_GET_SPDIR             16        // ��ȡ����sp����Ŀ¼
#define PRTCL_GET_KKT				17        // ��ȡ���ܵİ汾���ͣ���������ʿ�����ԣ�
#define PK_CMDLINE    "cmdline"  /*[in]*/     // ����������, �������ȫ·�� Ĭ�ϵ�ǰĿ¼
#define PK_SPDIR      "spdir"   /*[out]*/    // sp����Ŀ¼
#define PK_KKT		  "kkt"      /*[out]*/    // ���ܵİ汾����


//-------------------------------------
// ��ǰ�����Ľ���
#define PRTCL_SET_PROTECTPROGRAM     10
#define PRTCL_GET_PROTECTPROGRAM     11
#define PK_PROGRAMPATH    "programpath"  /*[in]*/     // ��ǰ�����ĳ���ȫ·��
#define PK_PROGRAM_PID    "pid"  /*[in]*/     // ��ǰ���������pid


//-------------------------------------
// ɾ����־�ļ�
#define PRTCL_DELETELOG                12


//-------------------------------------
// ��ȡ����������
#define PRTCL_GET_PROFILESETTING		20
#define PRTCL_SET_PROFILESETTING		21
#define PRTCL_GET_REGSTRINGSETTING      22
#define PRTCL_SET_REGSTRINGSETTING      23
#define PRTCL_GET_REGDWORDSETTING       24
#define PRTCL_SET_REGDWORDSETTING       25
#define PRTCL_DELETE_REGSETTING         26
#define PRTCL_SET_CRREGSTRINGSETTING	27
#define PK_KEY        "key"
#define PK_SUBKEY	  "subkey"
#define PK_VALUE      "value"
#define PK_DEFAULT    "default"

//-------------------------------------
// �ϱ���Ϣ
#define PRTCL_REPORT_INFO				30
#define PK_REPORT_MC			"mc"
#define PK_REPORT_SC			"sc"
#define PK_REPORT_INFO			"info"

#define PRTCL_REPORT_URL				31
#define PK_REPORT_URL			"url"

#define PRTCL_REPORT_INFO_NEW				32
#define PK_REPORT_MC			"mc"
#define PK_REPORT_SC			"sc"
#define PK_REPORT_INFO			"info"

//-------------------------------------
// ������
#define PRTCL_BL_ADD					40
#define PRTCL_BL_DELETE					41
#define PK_BL_URL				"url"
#define PK_BL_REASON			"reason"

#define PRTCL_BL_EXPORT					42
#define PRTCL_BL_IMPORT					43
#define PRTCL_BL_DESUBSCRIBE            44
#define PK_BL_ADNAME            "adname"
#define PK_BL_ADDATE            "addate"
#define PK_BL_FILEPATH			"path"
#define PK_BL_ITEMFLAG          "flag"
#define PK_BL_SUBRULEIID        "ruleid"

#define PRTCL_BL_ADDEX				    45
#define PK_BL_FTURL			    "fturl"
#define PK_BL_EXIST             "urlexist"

//-------------------------------------
// ������ҳ
#define PRTCL_SSP_ADD					50
#define PRTCL_SSP_DELETE				51
#define PRTCL_SSP_GET					52
#define PRTCL_SSP_DELAUTO				53
#define PK_SSP_URL				"ssp"
#define PK_SSP_TYPE				"type"

//-------------------------------------
// ��ҳ����
#define PRTCL_FR_ADD					60
#define PRTCL_FR_DELETE					61
#define PK_FR_RULE				"rule"
#define PK_FR_SET				"set"

#define PRTCL_FR_EXPORT					62
#define PRTCL_FR_IMPORT					63
#define PK_FR_FILEPATH			"path"

//��¼Σ����ַ����ַ�������ṩ����
#define PRTCL_DAN                       64

#define PRTCL_BL_INITADIDNAME           66
#define PRTCL_BL_INSERTBLURLID          67
#define PRTCL_BL_GETBLURLADNAME         68
#define PRTCL_BL_UPDATEIDNAME           69
#define PRTCL_BL_GETADIDOFNAME          70
#define PRTCL_BL_GETADIDOFDATE          71
#define PRTCL_BL_GETFREEADID            72
// in:
#define PK_URLTMPFILE           "durltmp"   /*[in]*/
#define PK_URLMSG               "url"       /*[in]*/

#endif // _KwsIPCDef_h_
