#ifndef __KProcFileRule_h__
#define __KProcFileRule_h__

#include "IRule.h"

/*
ClassName	: KFilePathRule
Creator		: zhongzhendong
Brief		: �ļ�����ͬһĿ¼�����ж��ļ��Ƿ��ڽ���Ŀ¼��
*/

class KProcFileRule : public IRule
{
public:
	DECLARE_RULE_NAME(KProcFileRule);

	virtual BOOL Match(KAccessData* pData);
	virtual void DbgPrint(void);
};

#endif