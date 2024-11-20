#ifndef __KFilePathRule_h__
#define __KFilePathRule_h__

#include "IRule.h"

/*
ClassName	: KFilePathRule
Creator		: zhongzhendong
Brief		: �ļ�ȫ·�������ж��ļ�·���Ƿ���ָ�����ļ��б���
*/

class KFilePathRule : public IRule
{
public:
	DECLARE_RULE_NAME(KFilePathRule);

	virtual BOOL Match(KAccessData* pData);
	virtual void DbgPrint(void);

	void AddFilePath(LPCTSTR szFilePath);
	void RemoveFilePath(LPCTSTR szFilePath);
	void Clear(void);

private:
	std::vector<CString> m_vecFilePaths;
};

#endif