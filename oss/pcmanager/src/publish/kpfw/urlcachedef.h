////////////////////////////////////////////////////////////////////////////////
//      
//      File for url cache manager
//      
//      File      : urlcachedata.h
//      Version   : 1.0
//      Comment   : ���ܷ���թ��վ���url��������
//      
//      Create at : 2010-2-3
//      Create by : liupeng
//		Motify by : 
//      
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../common/sharememlock.h"

typedef enum _URL_TYPE
{
	enumUrlType_UnIdent = -1,		// δ����
	enumUrlType_ExtAttri = 0x80000000,		// ��չ����
	enumUrlType_Unk = 0,		// δ֪
	enumUrlType_InIdent = 1,     // ������
	enumUrlType_Safe = 2,         // ��ȫ��վ
	enumUrlType_Horse = 4,       // ������
	enumUrlType_Phishing = 8,    // ������ַ
	enumUrlType_PhishingDownload = 16,   // ��թ����
	enumUrlType_AdSide = 32,      // �����վ
	enumUrlType_Sexy = 64,         // ɫ����վ
	enumUrlType_LineToMalSide = 128,        // �ض��򵽶�����վ
	enumUrlType_ExploitAttSide = 256,        // �����������������վ
	enumUrlType_MalSide = 512,                 // ����������վ
	enumUrlType_IEIndex = 1024,		// ��ieindex�е����host
	enumUrlType_WhiteDomain = 2048,		// �����ڰ�������
} URL_TYPE;

#define MAKE_URL_TYPE(p, v, t) { *p = v | t ;}

typedef enum _URL_TYPE_EXT
{
	enumUrlTypeExt_None=0,
	enumUrlTypeExt_QQPhishing,           // QQ��թ��վ �����н�֮���
	enumUrlTypeExt_TaobaoPhishing,  // Taobao����թ��վ
	enumUrlTypeExt_PhishingDownLink,   // ������������թ
	enumUrlTypeExt_PhishingLink,      // ������������թ
	enumUrlTypeExt_Relocat,             // ��Ҫ�ص�����վ�ϵ�
} URL_TYPE_EXT;

//////////////////////////////////////////////////////////////////////////
/*
�ύ
http://www.pc120.net/check.asp?url=xxxxxx
xxxxxΪ�ύ��URLȫ��ַ

����ֵ
1::80000000::00000000::0::(�ض�����ַ)

�����ֵ��˫ð�ŷָ�

A:
��ַ����״̬
0->δ����(��δ���жӼ���)
1->�Ѽ����� �н����
2->������(�����Ӻ���н��)

B:
��ַ����(1) DWORD
UrlType_HaveExtType	0x80000000	//�Ƿ�����һ����չ����
UrlType_Unk		0x0	// δ֪��վ
UrlType_Safe		0x1	// ��ȫ��վ
UrlType_Horse	0x2	// ������
UrlType_Phishing	0x4	// ������վ
UrlType_AdSide	0x10	// �����վ
UrlType_Sexy		0x20	// ������վ
UrlType_LinkToMalSide	0x40	//��վ�ض��򵽶�����վ
UrlType_ExploitAttSide	0x80	// ��վ���������������
UrlType_MalSide	0x100	// ����������վ

C:
��ַ����(2) DWORD
UrlTypeExt_HaveExtType	0x80000000

D:
�Ƿ���Ҫ�ض���
0->�����ض���
1->�ض���ָ����ַ

E:
�����һ���ض�����ַ
�ض�����վ��URL�����ض���Ļ���Ϊ��

��ַ������������һ��,�����λ�����Ƿ�����һ����ַ����,
�����ɱ�־λ��ɵ� ��һ����վ��һ����֪�ĵ�����վ,
���ҷ�����Ҫ�ض���htt
��ô����ֵӦ����
1::00000004::1::
*/

#define UrlType_HaveExtType	0x80000000	//�Ƿ�����һ����չ����
#define UrlType_Unk		0x0	// δ֪��վ
#define UrlType_Safe		0x1	// ��ȫ��վ
#define UrlType_Horse	0x2	// ������
#define UrlType_Phishing	0x4	// ������վ
#define UrlType_AdSide	0x10	// �����վ
#define UrlType_Sexy		0x20	// ������վ
#define UrlType_LinkToMalSide	0x40	//��վ�ض��򵽶�����վ
#define UrlType_ExploitAttSide	0x80	// ��վ���������������
#define UrlType_MalSide	0x100	// ����������վ

typedef enum _MATCH_TYPE
{
	enumUndef = 0,
	enumDomainWithoutPort,
	enumDomainWithPort,
	enumParantDomain,
	enumFullUrl,
	enumUrlWithoutParam,
	enumIPAddress,
	enumIPAddressWithPort
} MATCH_TYPE;

//////////////////////////////////////////////////////////////////////////
struct UrlCacheItem
{
	BYTE		urlMd5[16];
	URL_TYPE	enumUrlType;
	MATCH_TYPE	enumMatchType;
	__time64_t	lastUpdateTime;
	DWORD		m_nReserve[4];

	UrlCacheItem&	operator= (const UrlCacheItem& item2)
	{
		memcpy(this, &item2, sizeof(UrlCacheItem));
		return *this;
	}
};

inline bool operator< (const UrlCacheItem& item1, const UrlCacheItem& item2)
{
	return memcmp(item1.urlMd5, item2.urlMd5, sizeof(item1.urlMd5)) < 0;
}

inline bool operator== (const UrlCacheItem& item1, const UrlCacheItem& item2)
{
	return memcmp(item1.urlMd5, item2.urlMd5, sizeof(item1.urlMd5)) == 0;
}

typedef struct _tagUrlCacheMapDescription
{
	ShareMemLock			m_lock;
	DWORD					m_nMaxItemCnt;
	DWORD					m_nUsedItemCnt;
	DWORD					m_nReserve[10];
	UrlCacheItem			m_CacheItems[1];
}UrlCacheMapDescription;

#define URL_CACHE_MAPDATA_NAME		(TEXT("Global\\34CA103F-299E-49eb-A0B1-BC09D2D1A64D"))

//////////////////////////////////////////////////////////////////////////
typedef struct _tagUrlCacheFileMapItem
{
	volatile DWORD			m_nMapType;				// map������
	volatile DWORD			m_nOffset;				// ������ļ�ͷλ��
	volatile DWORD			m_nMapSize;				// �����Ĵ�С
	volatile DWORD			m_nDataVersion;			// map�����ݰ汾
}UrlCacheFileMapItem;

#define URL_CACHE_MAX_MAP_TABLE		(20)
#define URL_CACHE_FILE_MAGIC		('ULC')
#define URL_CAHCE_FILE_VERSION		((1 << 16) | 1)

typedef struct _tagUrlCacheFileHeader
{
	volatile DWORD			m_nMagic;				// 'URLC'
	volatile DWORD			m_nFileVersion;			// �ļ��汾
	ShareMemLock	m_Lock;					// ��д��
	volatile DWORD			m_nMapCnt;				// �Ѿ�ʹ�õ�map����
	UrlCacheFileMapItem	m_MapTable[URL_CACHE_MAX_MAP_TABLE]; // map������
}UrlCacheFileHeader;

#define URL_CACHE_HOST				0
#define URL_CACHE_BLACKURL			1

#define URL_CACHE_SIZE			(1024*1024)