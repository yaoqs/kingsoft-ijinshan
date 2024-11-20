////////////////////////////////////////////////////////////////////////////////
//      
//      File for netmon
//      
//      File      : advflt.h
//      Version   : 1.0
//      Comment   : ���ڸ߼������������ļ�
//      
//      Create at : 2008-4-7
//      Create by : liupeng
//      
///////////////////////////////////////////////////////////////////////////////

#pragma once 
#include "kis/kpfw/filecomm.h"
#include "framework/kis_file.h"
#include "kis/kpfw/errorcode.h"
#include "framework/kis_crypt.h"

#define ADVIP_FILE_MAGIC						( ((int('L')) << 24) | ((int('R')) << 16) | ((int('D')) << 8) | ((int('A'))) )

// ip�����ļ�ͷ
struct ADVFLTFileHeader
{
	DWORD				cbSize;				// �ļ�ͷ��С
	DWORD				nMagic;				// ��־
	INT					nVer;				// �ļ��汾
	DWORD				nAdvFltCnt;			// �߼��������ø���
	BYTE				CheckSum[16];		// �߼����������ݵ�md5
	DWORD				nIpRuleOffset;		// ip��ʼλ��
};

interface IKAdvTemplateList
{
	virtual INT		GetTemplateCnt()		PURE;

	virtual	INT		GetBufferSize()			PURE;

	virtual	void	WriteBuffer(BYTE* pBuff)	PURE;
};

class KAdvFltFile
{
private:
	kis::KFileRead*		m_pFile;
public:
	KAdvFltFile(): m_pFile(NULL)
	{

	}

	~KAdvFltFile()
	{
		if (m_pFile)
		{
			delete m_pFile;
			m_pFile = NULL;
		}
	}

	inline HRESULT Load(LPCWSTR strFile);

	inline HRESULT Save(LPCWSTR strFile, KPackTemplate* pTemplate, INT nBufSize, INT nCnt);

	inline HRESULT Save(LPCWSTR strFile, IKAdvTemplateList* pTempList);

	inline INT	   GetTemplateCnt();

	inline KPackTemplate* GetFirstTemplate();
};

