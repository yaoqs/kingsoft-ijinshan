#ifndef __KDirRelateRule_h__
#define __KDirRelateRule_h__

#include "IRule.h"

/*
ClassName	: KDirRelateRule
Creator		: zhongzhendong
Brief		: Ŀ¼�������򣬲鿴�����ļ�Ŀ¼�Ľ����Ƿ����Զ����������
*/

class KDirRelateRule : public IRule
{
public:
	DECLARE_RULE_NAME(KDirRelateRule);

	virtual BOOL Match(KAccessData* pData);
	virtual void DbgPrint(void);

	void AddRelateProcPath(LPCTSTR szDir, LPCTSTR szRelateProcPath);
	void AddRelateProcName(LPCTSTR szDir, LPCTSTR szProcName);
	void RemoveDirRelate(LPCTSTR szDir, LPCTSTR szRelateProc);
	void Clear(void);

private:
	std::map<CString, std::vector<CString>> m_mapDirRelates;
	std::map<CString, std::vector<CString>> m_mapWildcardDirRelates;

	std::map<CString, std::vector<CString>> m_mapDirRelates2;
	std::map<CString, std::vector<CString>> m_mapWildcardDirRelates2;
};
#endif