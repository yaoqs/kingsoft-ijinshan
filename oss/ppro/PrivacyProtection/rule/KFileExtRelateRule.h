#ifndef __KFileExtRelateRule_h__
#define __KFileExtRelateRule_h__

#include "IRule.h"

/*
ClassName	: KFileExtRelateRule
Creator		: zhongzhendong
Brief		: �ļ���չ���������򣬲鿴���ʴ��ļ��ĳ����Ƿ����û�����Ĺ������򣬻������Զ���Ĺ�������
*/

class KFileExtRelateRule : public IRule
{
public:
	DECLARE_RULE_NAME(KFileExtRelateRule);

	virtual BOOL Match(KAccessData* pData);
	virtual void DbgPrint(void);

	void AddExtRelate(LPCTSTR szExtName, LPCTSTR szRelateProc);
	void RemoveExtRelate(LPCTSTR szExtName, LPCTSTR szRelateProc);
	void Clear(void);

protected:
	void GetSystemRelate(LPCTSTR szExtName, CString& strRelate);

private:
	std::map<CString, std::vector<CString>> m_mapExtRelates;
};

#endif