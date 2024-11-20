#ifndef __KFileDirRule_h__
#define __KFileDirRule_h__

#include "IRule.h"

/*
ClassName	: KFileDirRule
Creator		: zhongzhendong
Brief		: �ļ�Ŀ¼���򣬲鿴�ļ�Ŀ¼�Ƿ������Ŀ¼�б��С�
*/

class KFileDirRule : public IRule
{
public:
	DECLARE_RULE_NAME(KFileDirRule);

	virtual BOOL Match(KAccessData* pData);
	virtual void DbgPrint(void);

	void AddFileDir(LPCTSTR szFileDir);
	void RemoveFileDir(LPCTSTR szFileDir);
	void Clear(void);

protected:
	void AddNotusedFileDir(LPCTSTR szFileDir);
	void UsesNotusedFileDir(void);

private:
	std::vector<CString> m_vecFileDirs;
	std::vector<CString> m_vecNotUsed;
	std::vector<CString> m_vecWildcardFileDirs;
};
#endif