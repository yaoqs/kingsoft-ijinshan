#ifndef __KFileExtensionRule_h__
#define __KFileExtensionRule_h__

#include "IRule.h"

/*
ClassName	: KFileExtensionRule
Creator		: zhongzhendong
Brief		: �ļ���չ�����򣬲鿴�����ļ�����չ���Ƿ�����չ���б���
*/

class KFileExtensionRule : public IRule
{
public:
	DECLARE_RULE_NAME(KFileExtensionRule);

	virtual BOOL Match(KAccessData* pData);
	virtual void DbgPrint(void);

	void AddFileExt(LPCTSTR szFileExt);
	void RemoveFileExt(LPCTSTR szFileExt);
	void Clear(void);

private:
	std::vector<CString> m_vecFileExts;
};

#endif