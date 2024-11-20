////////////////////////////////////////////////////////////////////////////////
//      
//      File for netmon
//      
//      File      : blackurlfile.h
//      Version   : 1.0
//      Comment   : ������ַ��֤�ļ�����
//      
//      Create at : 2009-6-30
//      Create by : liupeng
//      
///////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "framework/kis_file.h"
#include "kis/kpfw/errorcode.h"
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

//////////////////////////////////////////////////////////////////////////
#define BLACKURL_FILE_MAGIC						( ((int('L')) << 24) | ((int('R')) << 16) | ((int('U')) << 8) | ((int('B'))) )

// �ļ�ͷ
struct BlackUrlFileHeader
{
	DWORD				cbSize;				// �ļ�ͷ��С
	DWORD				nMagic;				// ��־
	INT					nVer;				// �ļ��汾
	DWORD				BlackUrlCnt;		// url�ĸ���
	DWORD				BlackUrlData;		// 
	char				strLastVersion[128];// ��ǰ��汾
};

enum BlackUrlTrustLevel
{
	BlackUrl_Warning	= 3,
	BlackUrl_Danger		= 4,
};

struct BlackUrlItem
{
	BYTE				md5[16];			// url��md5
	INT					trustLevel;			// ���εȼ� BlackUrlTrustLevel
};

struct BlackUrlMergeItem
{
	BlackUrlItem		item;
	BOOL				itemToDel;			// �Ƿ���Ҫ��ɾ����
};

inline bool operator<(const BlackUrlMergeItem& item1, const BlackUrlMergeItem& item2)
{
	return memcmp(item1.item.md5, item2.item.md5, sizeof(item1.item.md5)) < 0;
}

//////////////////////////////////////////////////////////////////////////
class KBlackUrlMergeItemVec
{
private:
	BlackUrlMergeItem*		m_pItem;
	INT						m_nTotalCnt;
	INT						m_nCurCnt;

public:
	KBlackUrlMergeItemVec(): m_pItem(NULL), m_nTotalCnt(0), m_nCurCnt(0)
	{
		m_nTotalCnt = 512;
		m_pItem = new BlackUrlMergeItem[m_nTotalCnt];
		if (!m_pItem)
			m_nTotalCnt = 0;
	}
	~KBlackUrlMergeItemVec()
	{
		if (m_pItem)
		{
			delete [] m_pItem;
			m_pItem = NULL;
		}
		m_nTotalCnt = 0;
		m_nCurCnt = 0;
	}

	INT					GetCnt()
	{
		return m_nCurCnt;
	}

	BlackUrlMergeItem*	NewItem()
	{
		if (m_nCurCnt + 1 > m_nTotalCnt)
		{
			INT nNewTotal = m_nTotalCnt ? m_nTotalCnt*2 : 512;

			BlackUrlMergeItem* pItem = new BlackUrlMergeItem[nNewTotal];
			if (!pItem)		return NULL;

			memset(pItem, 0 , sizeof(BlackUrlMergeItem)*nNewTotal);
			if (m_pItem)
			{
				memcpy(pItem, m_pItem, sizeof(BlackUrlMergeItem)*m_nCurCnt);
				delete [] m_pItem;
				m_pItem = pItem;

				m_nTotalCnt = nNewTotal;
				m_nCurCnt++;
			}
		}
		else
			m_nCurCnt++;
		return m_pItem + m_nCurCnt - 1;
	}

	BlackUrlMergeItem*	GetItem(INT i)
	{
		if (i >= 0 && i < m_nCurCnt)
			return m_pItem + i;
		return NULL;
	}

	void	Sort()
	{
		if (m_nCurCnt > 0)
			std::sort(m_pItem, m_pItem+m_nCurCnt);
	}
};

//////////////////////////////////////////////////////////////////////////
class KBlackUrlFile
{
private:
	ATL::CString		m_strFileName;
	kis::KFileRead*		m_pFile;
	BlackUrlFileHeader*	m_pFileHeader;
	BlackUrlItem*		m_pUrlItem;
	
public:
	KBlackUrlFile():m_pFile(NULL),m_pFileHeader(NULL),m_pUrlItem(NULL)		{}
	~KBlackUrlFile()
	{
		if (m_pFile)
		{
			delete m_pFile;
			m_pFile = NULL;
		}
		m_pFileHeader = NULL;
		m_pUrlItem = NULL;
	}

	inline HRESULT Load(LPWSTR strFile);

	inline HRESULT	Reload();

	inline BOOL	 Find(BYTE md5[16], INT& nType);

	inline HRESULT	MergePackageFile(LPCWSTR strFile, LPCWSTR orgFile);

	inline const char* GetVersion();

	inline static BOOL ParseFromMD5String(const string&  strIn, BYTE md5bin[16]);

	inline static BOOL IsHexNum(char ch, BYTE* pHexDigit);

private:
	inline	HRESULT	BuildMergeItems(LPCWSTR strFile, KBlackUrlMergeItemVec& items,string& version);

	inline	HRESULT	SaveToFile(BlackUrlItem* pItems, INT nCnt, string& version, LPCWSTR strFile);
};

//////////////////////////////////////////////////////////////////////////
// ���������е�patch�ļ��ṹ

#define PATCH_BLACKURL_FILE_MAGIC			( ((int('L')) << 24) | ((int('R')) << 16) | ((int('U')) << 8) | ((int('P'))) )

// �ļ�ͷ
struct PathcBlackUrlFileHeader
{
	DWORD				cbSize;				// �ļ�ͷ��С
	DWORD				nMagic;				// ��־
	INT					nVer;				// �ļ��汾
	DWORD				PatchBlockCnt;		// ���ļ��е�patch��ĸ���
	DWORD				MaxPatchVersion;	// ���patch�汾
	DWORD				MinPatchVersion;	// ��Сpatch�汾
};

struct BlackUrlPatchBlock
{
	DWORD				cbSize;				// ����Ĵ�С
	DWORD				PatchVersionFrom;	// patch�汾����ʼ�汾
	DWORD				PatchVersionTo;		// patch������汾
	DWORD				BlackUrlCnt;		// ��patch������url��
	BlackUrlItem		Urls[1];			// patch�е�url
};

//////////////////////////////////////////////////////////////////////////
class  KPatcchBlackUrlFile
{
public:
	KPatcchBlackUrlFile();
	~KPatcchBlackUrlFile();
};