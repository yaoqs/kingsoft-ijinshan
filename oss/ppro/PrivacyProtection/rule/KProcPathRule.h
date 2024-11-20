#ifndef __KProcPathRule_h__
#define __KProcPathRule_h__

#include "IRule.h"

/*
ClassName	: KProcPathRule
Creator		: zhongzhendong
Brief		: ����ȫ·�������жϽ���·���Ƿ���ָ�����ļ��б���
*/

class KProcPathRule : public IRule
{
public:
	DECLARE_RULE_NAME(KProcPathRule);

	virtual BOOL Match(KAccessData* pData);
	virtual void DbgPrint(void);

	void AddProcPath(LPCTSTR szPath);
	void RemoveProcPath(LPCTSTR szPath);
	void Clear(void);

private:
	std::vector<CString> m_vecProcPaths;

};

#endif