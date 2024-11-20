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
};