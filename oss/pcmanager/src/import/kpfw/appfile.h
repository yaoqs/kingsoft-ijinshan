////////////////////////////////////////////////////////////////////////////////
//      
//      File for netmon
//      
//      File      : appfile.h
//      Version   : 1.0
//      Comment   : ����Ӧ�ó�������ļ���д
//      
//      Create at : 2008-4-7
//      Create by : liupeng
//      
////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "kis/kpfw/filecomm.h"
#include "framework/kis_file.h"
#include "kis/kpfw/errorcode.h"

// appr
#define APP_FILE_MAGIC						( ((int('R')) << 24) | ((int('P')) << 16) | ((int('P')) << 8) | ((int('A'))) )

// Ӧ�ó�������ļ�ͷ
struct AppFileHeader
{
	DWORD				cbSize;				// �ļ�ͷ��С
	DWORD				nMagic;				// ��־
	INT					nVer;				// �ļ��汾
	DWORD				nAppRuleOffset;		// �������ʼλ��
};
class KAppRuleVec;
class KAppRule;

class KAppFile
{
private:
	KAppRuleVec*		m_pAppMgr;

public:
	KAppFile(KAppRuleVec* pMgr):m_pAppMgr(pMgr)		{}

	HRESULT	Load( LPCWSTR strFile ) ;
	HRESULT Save( LPCWSTR strFile );

private:
	HRESULT	ReadAppRules(KRecord* pRecord);
	HRESULT	ReadRuleList(KRecord* pRecord);
	HRESULT	ReadRule(KRecord* pRecord);
	HRESULT ReadDenyPortList(KRecord* pRecord, KAppRule* pRule);

	HRESULT	SaveRuleList(KRecordWriter* pWriter);
	HRESULT SaveRule(KRecordWriter* pWriter, KAppRule* pRule);
};