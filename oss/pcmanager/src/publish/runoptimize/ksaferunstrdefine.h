#pragma once


#define KSAFE_RUN_XML_ROOT			_T("xml")
#define KSAFE_RUN_XML_ITEM			_T("item")
#define KSAFE_RUN_XML_ITEM_ID		_T("id")
#define KSAFE_RUN_XML_ITEM_TYPE		_T("type")
#define KSAFE_RUN_XML_ITEM_NAME		_T("name")
#define KSAFE_RUN_XML_ITEM_DESC		_T("desc")
#define KSAFE_RUN_XML_ITEM_WARNING	_T("warning")
#define KSAFE_RUN_XML_ITEM_DISPLAY	_T("display")
#define KSAFE_RUN_XML_ITEM_APPNAME	_T("appname")
#define KSAFE_RUN_XML_ITEM_ADVICE	_T("advice")
#define KSAFE_RUN_XML_ITEM_SYSTEM	_T("system")
#define KSAFE_RUN_XML_ITEM_NODELAY	_T("nodelay")
#define KSAFE_RUN_XML_ITEM_REGPATH	_T("regpath")
#define KSAFE_RUN_XML_ITEM_SHOW_REMAINS		_T("show_remain")
#define	KSAFE_RUN_XML_ITEM_EXTRA_FLAG		_T("extra_flag")
#define KSAFE_RUN_XML_ITEM_OPENRATE			_T("openrate")
#define KSAFE_RUN_XML_ITEM_USERNUM			_T("usercount")

class KSRunInfo
{
public:
	KSRunInfo()
	{
		nItemId = 0;
		nType	= 0;
		nAdvice	= 0;
		bNoDealyShow = FALSE;
		bSystem	= FALSE;
		bRegPath = FALSE;
		bShowRemain = TRUE;
		nExtraFlag = 0x00;
		nUserCount = 0;
	}

	DWORD		nItemId;		//ÿ��ΩһID
	DWORD		nType;			//����
	CString		strName;		//����
	CString		strDesc;		//����
	CString		strAppName;		//��Ӧ��APP������
	CString		strDisplay;		//��������ʾ������
	DWORD		nAdvice;		//�������
	CString		strWarning;		//��������
	BOOL		bNoDealyShow;	//����ʾ��ʱ����
	BOOL		bSystem;		//�Ƿ���ϵͳ��
	BOOL		bRegPath;		//��ƥ��AppName
	BOOL		bShowRemain;	//����ǲ�����Ƿ���ʾ
	DWORD		nExtraFlag;		//1.0��ʾ�Ƿ���Խ��ã�����ֵ����ʹ��
	CString		strOpenRate;	//������,���ﱣ��ٷֱ��еķ���
	DWORD		nUserCount;		//�û�����
};

//һ���Ż��У�ϵͳ���������Ŀ��ID��ǣ���dwID & 0x80000���������ϵͳ�����Ż���Ŀ��ID 
#define KSAFE_ONEKEY_OPT_SYSCFG_ID_FLAG			0x80000

//[ϵͳ�����Ż�]ע�����ֶζ��壺
#define KSAFE_REG_SYSOPT_XML_ROOT				_T("xml")
#define KSAFE_REG_SYSOPT_XML_ITEM				_T("item")
#define KSAFE_REG_SYSOPT_XML_ITEM_ID			_T("id")
#define KSAFE_REG_SYSOPT_XML_ITEM_TYPE			_T("type")
#define KSAFE_REG_SYSOPT_XML_ITEM_DESC			_T("desc")
#define KSAFE_REG_SYSOPT_XML_ITEM_VISTA			_T("nt6")
#define KSAFE_REG_SYSOPT_XML_ITEM_REGKEY		_T("regkey")
#define KSAFE_REG_SYSOPT_XML_ITEM_VALUE_TYPE	_T("value_type")
#define KSAFE_REG_SYSOPT_XML_ITEM_DEF_VALUE		_T("def_value")
#define KSAFE_REG_SYSOPT_XML_ITEM_OPT_VALUE		_T("opt_value")
#define KSAFE_REG_SYSOPT_XML_ITEM_COMPARE		_T("compare_type")

//�Ƚ�����
#define KSAFE_REGSYSOPT_COMPARE_TYPE_EQUAL	1
#define KSAFE_REGSYSOPT_COMPARE_TYPE_LESS	2
#define KSAFE_REGSYSOPT_COMPARE_TYPE_MORE	3

//���ĳ���Ż�����Ҫ�Ķ�����һ����ע�����Щע�����á�;��������ͬ���ģ����ǵ�Ĭ��ֵ���Ż����ֵҲ�á�;������
#define KSAFE_REGSYSOPT_SEPARATOR			_T(";")

#define KSAFE_REGSYSOPT_BACKSLASH			_T('\\')

//���ϵͳ��Ĭ�ϲ����ڸü�ֵ��������NULL���
#define KSAFE_REGSYSOPT_KEY_NULL			_T("NULL")

//ע����ֵ������
#define KSAFE_REG_VALUE_TYPE_REG_NONE		REG_NONE		//0
#define KSAFE_REG_VALUE_TYPE_REG_SZ			REG_SZ			//1
#define KSAFE_REG_VALUE_TYPE_REG_EXPAND_SZ	REG_EXPAND_SZ	//2
#define KSAFE_REG_VALUE_TYPE_REG_BINARY		REG_BINARY		//3
#define KSAFE_REG_VALUE_TYPE_REG_DWORD		REG_DWORD		//4

//ע����������
#define KSAFE_REG_ROOT_HKCU					_T("HKCU")
#define KSAFE_REG_ROOT_HKLM					_T("HKLM")

class KSysotpRegInfo
{
public:
	KSysotpRegInfo()
	{
		nID		= 0;
		nType	= 0;
		bNt6OnlyHave = FALSE;
		nRegValueType= KSAFE_REG_VALUE_TYPE_REG_SZ;
		nCompareType = 0;
	}

	DWORD		nID;				//ÿ��ΩһID
	DWORD		nType;				//���ͣ��������;�����������ʾ������硰���ػ����١�����ϵͳ�������ȶ�������ͨ���Ż�����.
	BOOL		bNt6OnlyHave;		//���Ż��������õĲ���ϵͳ�汾��0��ͨ�á�1��nt6���С�2��nt5���С�
	CString		strDesc;			//���Ż��������
	CString		strRegKey;			//��Ӧ��ע����
	CString		strDefaultValue;	//Ĭ��ֵ
	CString		strOptimizedValue;	//�Ż����ֵ
	DWORD		nRegValueType;		//ע���ֵ������
	DWORD		nCompareType;		//�Ƚ����͡�1���Ƿ���ڣ�2���Ƿ���ڣ�3���Ƿ�С��
};

class CKSafeSysoptRegInfo
{
public:
	CKSafeSysoptRegInfo()
	{
		m_nID	= 0;
		m_nType = 1;
		m_bIsNt6OnlyHave = FALSE;
		m_hKeyRoot		 = HKEY_CURRENT_USER;
		m_nRegValueType	 = KSAFE_REG_VALUE_TYPE_REG_SZ;
		m_nCompareType   = KSAFE_REGSYSOPT_COMPARE_TYPE_EQUAL;
	}

	~CKSafeSysoptRegInfo(){}

	BOOL IsNt6OnlyHave()
	{
		return m_bIsNt6OnlyHave;
	}

	BOOL IsCanOptimize(CString strSysValue, CString strOptimizeValue)
	{
		BOOL bRet = FALSE;
		if (m_nCompareType == KSAFE_REGSYSOPT_COMPARE_TYPE_EQUAL)
		{
			bRet = (strSysValue.CompareNoCase(strOptimizeValue) != 0);
			goto Exit0;
		}
		else if (m_nCompareType == KSAFE_REGSYSOPT_COMPARE_TYPE_LESS)
		{
			bRet = (_wtoi(strSysValue.GetString()) < _wtoi(strOptimizeValue.GetString()));
			goto Exit0;
		}
		else if (m_nCompareType == KSAFE_REGSYSOPT_COMPARE_TYPE_MORE)
		{
			bRet = (_wtoi(strSysValue.GetString()) > _wtoi(strOptimizeValue.GetString()));
			goto Exit0;
		}
		else
		{
			goto Exit0;
		}
Exit0:
		return bRet;
	}

	LPCTSTR GetTitleFormatStr()
	{
		if (m_nType == 1)		
		{
			return _T("���ػ������Ż��%d��");
		}
		else if (m_nType == 2)
		{
			return _T("ϵͳ���м����Ż��%d��");
		}
		else if (m_nType == 3)
		{
			return _T("ϵͳ�ȶ��Ż��%d��");
		}
		else if (m_nType == 4)
		{
			return _T("ͨ���Ż��%d��");
		}
		else if (m_nType == 5)
		{
			return _T("�ļ����ٶ��Ż���%d��");
		}
		else if (m_nType == 6)
		{
			return _T("�����Ż���%d��");
		}
		else
		{	//û�ж�������Ҳ���롰ͨ���Ż��
			return _T("ͨ���Ż��%d��");
		}
	}

	LPCTSTR GetTitleStr()
	{
		if (m_nType == 1)		
		{
			return _T("���ػ������Ż���");
		}
		else if (m_nType == 2)
		{
			return _T("ϵͳ���м����Ż���");
		}
		else if (m_nType == 3)
		{
			return _T("ϵͳ�ȶ��Ż���");
		}
		else if (m_nType == 4)
		{
			return _T("ͨ���Ż���");
		}
		else if (m_nType == 5)
		{
			return _T("�ļ����ٶ��Ż�");
		}
		else if (m_nType == 6)
		{
			return _T("�����Ż�");
		}
		else
		{	//û�ж�������Ҳ���롰ͨ���Ż��
			return _T("ͨ���Ż���");
		}
	}

public:
	DWORD		m_nID;					//ID
	DWORD		m_nType;				//���
	BOOL		m_bIsNt6OnlyHave;		////���Ż��������õĲ���ϵͳ�汾��0��ͨ�á�1��nt6���С�2��nt5���С�
	CString		m_strDesc;				//����
	HKEY		m_hKeyRoot;				//ע������
	CString		m_strSubKey;			//ע����Ӽ�
	CString 	m_strValueName;			//ע������
	DWORD		m_nRegValueType;		//ע�������
	CString		m_strDefalutValue;		//���б����ϵͳĬ��ֵ
	CString		m_strOptimizedValue;	//�Ż����ֵ
	DWORD		m_nCompareType;			//�Ƚ�����
	CString		m_strInitValue;			//ö�ٵ���ϵͳ��ʼֵ
};