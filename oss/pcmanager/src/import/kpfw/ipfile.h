////////////////////////////////////////////////////////////////////////////////
//      
//      File for netmon
//      
//      File      : ipfile.h
//      Version   : 1.0
//      Comment   : ����ip�����ļ���д
//      
//      Create at : 2008-4-7
//      Create by : liupeng
//      
///////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "kis/kpfw/filecomm.h"
#include "framework/kis_file.h"
#include "kis/kpfw/errorcode.h"

#define IP_FILE_MAGIC						( ((int('L')) << 24) | ((int('R')) << 16) | ((int('P')) << 8) | ((int('I'))) )

// ip�����ļ�ͷ
struct IPFileHeader
{
	DWORD				cbSize;				// �ļ�ͷ��С
	DWORD				nMagic;				// ��־
	INT					nVer;				// �ļ��汾
	DWORD				nIpRuleOffset;		// ip��ʼλ��
};
class KIpRuleVec;
class KIpRule;

class KIpFile
{
private:
	KIpRuleVec*		m_pIPMgr;
public:
	KIpFile(KIpRuleVec* pMgr):m_pIPMgr(pMgr)		{}

	inline HRESULT Load(LPWSTR strFile);

	inline HRESULT Save(LPWSTR strFile);

private:
	inline HRESULT ReadIpRules(KRecord* pRecord);
	
	inline HRESULT	ReadRuleList(KRecord* pRecord);
	
	inline HRESULT	ReadRule(KRecord* pRecord);

	inline HRESULT SaveIpRules(KRecordWriter* pWriter);

	inline HRESULT SaveIpRule(KRecordWriter* pWriter, KIpRule* pRule);

};