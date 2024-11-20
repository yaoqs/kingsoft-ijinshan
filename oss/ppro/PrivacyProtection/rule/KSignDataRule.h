#ifndef __KSignDataRule_h__
#define __KSignDataRule_h__

#include "IRule.h"
#include "Common\KLocker.h"

/*
ClassName	: KSignDataRule
Creator		: zhongzhendong
Brief		: ����ǩ�������ж��ļ�������ǩ���Ƿ����б���
Remark		: ����������������ǩ�����ж�
*/

class KSignDataRule : public IRule
{
public:
	DECLARE_RULE_NAME(KSignDataRule);
	virtual BOOL Match(KAccessData* pData);
	virtual void DbgPrint(void);

	void AddSign(LPCSTR szSign);
	void RemoveSign(LPCSTR szSign);
	void Clear(void);


private:
	std::vector<CStringA> m_vecSigns;
	KCriticalSesion m_lckProcList;
	std::vector<CString> m_vecPassProcList;
	std::vector<CString> m_vecBlockProcList;
};

#endif