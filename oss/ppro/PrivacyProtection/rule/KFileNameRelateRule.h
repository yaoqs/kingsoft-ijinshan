#ifndef __KFileNameRelateRule_h__
#define __KFileNameRelateRule_h__

#include "IRule.h"

/*
ClassName	: KFileNameRelateRule
Creator		: zhongzhendong
Brief		: �ļ����������̹����ж��ļ�Ĭ�ϴ򿪽����Ƿ���ϵͳ������̻����Զ�������б�
*/

class KFileNameRelateRule : public IRule
{
public:
	DECLARE_RULE_NAME(KFileNameRelateRule);

	virtual BOOL Match(KAccessData* pData);
	virtual void DbgPrint(void);

	void AddFileNameRelate(LPCTSTR szFileName, LPCTSTR szRelateProc);
	void RemoveFileNameRelate(LPCTSTR szFileName, LPCTSTR szRelateProc);
	void Clear(void);

private:
	std::map<CString, std::vector<CString>> m_mapFileNameRelates;
};

#endif