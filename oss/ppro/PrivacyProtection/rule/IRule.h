#ifndef __IRule_h__
#define __IRule_h__

#define PRINT_RULE_RESULT

enum KEMRuleResult
{
	emRuleResult_Async = -1,
	emRuleResult_Error = 0,				//������
	emRuleResult_Show = 1,				//Υ����ʣ�Ҫ��ʾ��
	emRuleResult_Distrustful = 2,		//���ɵ�
	emRuleResult_Unknown = 3,			//δ֪��
	emRuleResult_Disscard = 4,			//����
	emRuleResult_Trust = 5,				//���ε�
};

struct KAccessData
{
	TCHAR szProcPath[MAX_PATH];
	int nProcPathLen;
	int nProcDirLen;

	TCHAR szFilePath[MAX_PATH];
	int nFilePathLen;
	int nFileDirLen;
	int nFileExtLen;

	int nResult;
	TCHAR szInfo[100];
	void* pExtendData;

	KAccessData()
	{
		szProcPath[0] = 0;
		nProcPathLen = 0;
		nProcDirLen = -1;
		szFilePath[0] = 0;
		nFilePathLen = 0;
		nFileDirLen = -1;
		nFileExtLen = -1;
		nResult = -1;
		pExtendData = NULL;
	}
};

//#define PRINT_RULE_RESULT
#define DECLARE_RULE_NAME(name) virtual LPCTSTR Name(void){ return L#name; }

/*
ClassName	: IRule
Creator		: zhongzhendong
Brief		: ����Ľӿ�
*/

class IRule
{
public:
	virtual LPCTSTR Name(void) = 0;
	virtual void Enable(BOOL bEnable){}
	virtual BOOL Match(KAccessData* pData) = 0;
	virtual void DbgPrint(void) = 0;
};

/*
�����б�
	1.��չ������
	2.�������ļ�ͬĿ¼����
	3.�ļ�·������
	4.�ļ�Ŀ¼����
	5.����·������
	6.����Ŀ¼����
	7.��չ�������������Զ�����չ����������
	8.�Զ���Ŀ¼��������
	9.����ǩ������
	10.�Զ����ļ��������̹���
*/

struct KProcName
{
	CString strProcName;
	CStringA strSign;
	CString strFileName;
};

#endif