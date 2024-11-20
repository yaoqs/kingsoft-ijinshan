////////////////////////////////////////////////////////////////////////////////
//      
//      common include File for kpfw
//      
//      File      : filecomm.h
//      Version   : 1.0
//      Comment   : �������ں��������ļ������ݽṹ
//      
//      Create at : 2008-4-7
//      Create by : liupeng
//      
////////////////////////////////////////////////////////////////////////////////

#pragma once 

#pragma pack(push, 1)
// ���ݽṹ��ͷ������
typedef struct _tgRecordHeader
{
	unsigned int		cbSize;								// �����ṹ���С
	unsigned char		bCompRecord;						// �Ƿ��Ǹ��Ͻṹ��
	unsigned char		nVer;								// �ṹ��汾
	unsigned short		nType;								// �ṹ������
} RecordHeader;

// ���Խṹ��
typedef struct _tgAttribEntry
{
	unsigned short		nAttribID;							// ��������
	long				nValue;								// ����ֵ
} AttribEntry;

// ������������
typedef struct _tgZoonEntry
{
	unsigned char		MacAddr[6];							// mac��ַ
	unsigned char		bTrusted;							// �Ƿ����
} ZoonEntry;

#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////
// �ṹ�����Ͷ���

// �ṹ���������ͷ���

enum
{
	Rct_Class_Comm			= 0,							// �����ṹ����
	Rct_Class_AppRule		= 0x1000,						// Ӧ�ó�������ļ�ʹ��
	Rct_Class_IpRule		= 0x2000,						// ip�����ļ�ʹ��
	Rct_Class_Area			= 0x3000,						// �����ļ�
};

// �����ṹ������
enum
{
	Rct_Comm_AttrList		= Rct_Class_Comm | 1,			// �����б�
	Rct_Comm_DataBuf		= Rct_Class_Comm | 2,			// ԭʼ����

	Rct_PortRangeList		= Rct_Class_Comm | 3,			// �˿ڷ�Χ�б�
	Rct_PortList			= Rct_Class_Comm | 4,			// �˿��б�

	Rct_IPRangeList			= Rct_Class_Comm | 5,			// ip��Χ�б�
	Rct_IPList				= Rct_Class_Comm | 6,			// ip�б�
};

// Ӧ�ó�������ļ��нṹ������
enum
{
	AppRule_Root			= Rct_Class_AppRule | 0x0101,	// Ӧ�ó������ʼ
	AppRule_RuleList		= Rct_Class_AppRule | 0x0102,	// Ӧ�ó�������б�
	AppRule_Rule			= Rct_Class_AppRule | 0x0103,	// Ӧ�ó��������
	AppRule_RuleID			= Rct_Class_AppRule | 0x0104,	// ����id
	AppRule_ExePath			= Rct_Class_AppRule | 0x0105,	// ����·��
	AppRule_UserMode		= Rct_Class_AppRule | 0x0106,	// �û�ѡ���ģʽ
	AppRule_TrustMode		= Rct_Class_AppRule | 0x0107,	// �Զ��жϵ�ģʽ
	AppRule_CheckSum		= Rct_Class_AppRule | 0x0108,	// У���
	AppRule_LastFileTime	= Rct_Class_AppRule | 0x010a,	// �ϴ��ļ��ı��ʱ��

	AppRule_Creator			= Rct_Class_AppRule | 0x0201,	// ������
	AppRule_CreateDate		= Rct_Class_AppRule | 0x0202,	// ��������
	AppRule_CreateReason	= Rct_Class_AppRule | 0x0203,	// ����ԭ��
	AppRule_LastModifyDate	= Rct_Class_AppRule | 0x0204,	// ����޸�����
	AppRule_LastModifyer	= Rct_Class_AppRule | 0x0205,	// ����޸���

	AppRule_DenyPortList	= Rct_Class_AppRule | 0x0301,	// �ܾ��˿��б�
	AppRule_TcpRemotePortList	= Rct_Class_AppRule | 0x0302,	// tcp Զ�̶˿��б�
	AppRule_TcpLocalPortList	= Rct_Class_AppRule | 0x0303,	// tcp ���ض˿��б�
	AppRule_UdpRemotePortList	= Rct_Class_AppRule | 0x0304,	// udp Զ�̶˿��б�
	AppRule_UdpLocalPortList	= Rct_Class_AppRule | 0x0305,	// udp ���ض˿��б�
};

// ip�����ļ��ṹ���Ͷ���
enum
{
	IpRule_Root				= Rct_Class_IpRule	| 0x0101,	// ip�������ݿ�ʼ
	IpRule_RuleList			= Rct_Class_IpRule	| 0x0102,	// ip�����б�
	IpRule_Rule				= Rct_Class_IpRule	| 0x0103,	// ����ip����

	IpRule_RuleName			= Rct_Class_IpRule	| 0x0105,	// ip��������
	IpRule_RuleDesc			= Rct_Class_IpRule	| 0x0106,	// ip��������
	IpRule_Valid			= Rct_Class_IpRule	| 0x0107,	// ip�����Ƿ�������

	IpRule_Creator			= Rct_Class_IpRule	| 0x0201,	// ������
	IpRule_CreateDate		= Rct_Class_IpRule	| 0x0202,	// ��������
	IpRule_CreateReason		= Rct_Class_IpRule	| 0x0203,	// ����ԭ��
	IpRule_LastModifyDate	= Rct_Class_IpRule	| 0x0204,	// ����޸�����
	IpRule_LastModifyer		= Rct_Class_IpRule	| 0x0205,	// ����޸���

	IpRule_FilterInfo		= Rct_Class_IpRule	| 0x0301,	// ������Ϣ
};

// �����ļ���Ϣ
enum
{
	AreaInfo_Root			= Rct_Class_Area	| 0x0101,	// �������ݿ�ʼ
	AreaInfo_AreaList		= Rct_Class_Area	| 0x0102,	// ��֪�����
	AreaInfo_Area			= Rct_Class_Area	| 0x0103,	// һ��������Ϣ
	
	AreaInfo_Name			= Rct_Class_Area	| 0x0201,	// ������
	AreaInfo_CreateDate		= Rct_Class_Area	| 0x0202,	// ���򴴽�ʱ��
	AreaInfo_Type			= Rct_Class_Area	| 0x0203,	// ��������
	AreaInfo_Gate			= Rct_Class_Area	| 0x0204,	// ��������mac��ַ
	AreaInfo_GateIp			= Rct_Class_Area	| 0x0205,	// ��������IP��ַ
};

//////////////////////////////////////////////////////////////////////////
// �ṹ���ȡ������
class KRecord
{
private:
	BYTE*				m_pBuf;								// �ṹ��ʼ

public:
	KRecord(BYTE* pBuf): m_pBuf(pBuf)
	{
	}

	BOOL	Ok()
	{
		return GetSize() >= sizeof(RecordHeader);
	}

	INT		GetSize()
	{
		return ((RecordHeader*)m_pBuf)->cbSize;
	}

	BOOL	IsComposed()
	{
		return ((RecordHeader*)m_pBuf)->bCompRecord;
	}

	INT		GetVersion()
	{
		return ((RecordHeader*)m_pBuf)->nVer;
	}

	INT		GetType()
	{
		return ((RecordHeader*)m_pBuf)->nType;
	}

	BYTE*	GetData()
	{
		return m_pBuf + sizeof(RecordHeader);
	}

	INT		GetDataSize()
	{
		return GetSize() - sizeof(RecordHeader);
	}

	KRecord	NextRecord()
	{
		return KRecord( m_pBuf + GetSize() );
	}

	KRecord	FirstSubRecord()
	{
		ASSERT(IsComposed());
		return KRecord( m_pBuf + sizeof(RecordHeader) );
	}

	BOOL	IsSubRecord(KRecord& rcd)
	{
		if (rcd.m_pBuf < GetData())
			return FALSE;
		if (rcd.m_pBuf > ( GetData() + GetDataSize() - sizeof(RecordHeader)))
			return FALSE;
		return TRUE;
	}
};

//////////////////////////////////////////////////////////////////////////
// �ṹ��д�������ӿ�
interface IWriteProxy
{
	virtual BYTE*	GetBuf(INT nPos)		= 0;
	virtual INT		GetCurPos()				= 0;
	virtual BYTE*	Next(INT nBytes)		= 0;
};

#define	INIT_MEM_BUF_SIZE		1024*256

class KMemWriteProxy: public IWriteProxy
{
private:
	BYTE*			m_pBuf;
	BYTE*			m_pCur;
	INT				m_nBufSize;
public:
	KMemWriteProxy()			
	{
		m_nBufSize = INIT_MEM_BUF_SIZE;
		m_pBuf = new BYTE[m_nBufSize];
		m_pCur = m_pBuf;
	}

	~KMemWriteProxy()
	{
		delete [] m_pBuf;
		m_nBufSize = 0;
		m_pCur = 0;
	}

	virtual BYTE*	GetBuf(INT nPos)
	{
		return m_pBuf + nPos;
	}

	virtual INT		GetCurPos()
	{
		return (INT)(m_pCur - m_pBuf);
	}

	virtual BYTE*	Next(INT nBytes)
	{
		if (GetCurPos() + nBytes > m_nBufSize)
			Resize( GetCurPos() + nBytes );

		BYTE* pCur = m_pCur;
		m_pCur += nBytes;
		return pCur;
	}

private:
	INT		Resize(INT nSize)
	{
		INT nNewSize = m_nBufSize;
		while (nNewSize < nSize)
			nNewSize *= 2;

		if (m_pBuf)
		{
			INT nOldPos = (INT)(m_pCur - m_pBuf);

			BYTE*	pBuf = new BYTE[nNewSize];
			memcpy(pBuf, m_pBuf, m_nBufSize);
			delete [] m_pBuf;

			m_nBufSize = nNewSize;
			m_pBuf = pBuf;
			m_pCur = m_pBuf + nOldPos;
		}
		return nNewSize;
	}
};

//////////////////////////////////////////////////////////////////////////
// �ṹ��д��������
class KRecordWriter: public IWriteProxy
{
private:
	IWriteProxy*		m_pProxy;							// д������
	INT					m_pRecordPos;						// ��ǰRecord��ָ��
	INT					m_nSize;							// ��ǰrecord�Ĵ�С
	BOOL				m_bEnd;								// �Ƿ��Ѿ�����
public:
	KRecordWriter(IWriteProxy* pProxy, unsigned char bComp, unsigned char nVersion, unsigned short nType)
	{
		m_pProxy = pProxy;
		m_pRecordPos = m_pProxy->GetCurPos();
		m_nSize = 0;
		m_bEnd = FALSE;

		RecordHeader* pRecord = (RecordHeader*) AddSize( sizeof(RecordHeader) );

		pRecord->bCompRecord = bComp;
		pRecord->nType = nType;
		pRecord->nVer = nVersion;
	}

	virtual BYTE*	GetBuf(INT nPos)
	{
		return m_pProxy->GetBuf(nPos);
	}

	virtual INT		GetCurPos()
	{
		return m_pProxy->GetCurPos();
	}

	virtual BYTE*	Next(INT nBytes)
	{
		return AddSize(nBytes);
	}

	~KRecordWriter()
	{
		ASSERT(m_bEnd);
	}

	RecordHeader* GetRecord()
	{
		return (RecordHeader*) m_pProxy->GetBuf(m_pRecordPos);
	}

	KRecordWriter*	StartRecord(unsigned short nType, int nVer = 0)
	{
		return new KRecordWriter(this, 0, nVer, nType);
	}

	KRecordWriter*	StartCompRecord(unsigned short nType, int nVer = 0)
	{
		return new KRecordWriter(this, 1, nVer, nType);
	}

	BOOL	EndRecord()
	{
		GetRecord()->cbSize = m_nSize;
		m_bEnd = TRUE;
		return TRUE;
	}

	template< typename T>
	BOOL	Write(T& Value)
	{
		ASSERT( !GetRecord()->bCompRecord && "���ϼ�¼�������������" );
		T* pBuf = (T*) AddSize( sizeof(T) );
		*pBuf = Value;
		return TRUE;
	}

	template< typename T>
	BOOL	Write(T* pValue, int nSize = 1)
	{
		ASSERT( !GetRecord()->bCompRecord && "���ϼ�¼�������������" );
		BYTE* pBuf = AddSize( sizeof(T) * nSize );
		memcpy(pBuf, pValue, sizeof(T) * nSize);
		return TRUE;
	}

private:
	BYTE*	AddSize(INT nSize)
	{
		m_nSize += nSize;
		return m_pProxy->Next(nSize);
	}
};

//////////////////////////////////////////////////////////////////////////
// ���÷���
inline HRESULT SaveString(LPCWSTR str, KRecordWriter* pWriter, unsigned short nType, int nVer = 0)
{
	KRecordWriter* pStr = pWriter->StartRecord(nType, nVer);
	pStr->Write(str, (int)(wcslen(str) + 1));

	pStr->EndRecord();
	delete pStr;
	return S_OK;
}

template< typename T>
inline HRESULT SaveStruct(T* pValue, KRecordWriter* pWriter, unsigned short nType, int nVer = 0)
{
	KRecordWriter* pStructWriter = pWriter->StartRecord(nType);
	pStructWriter->Write(pValue);

	pStructWriter->EndRecord();
	delete pStructWriter;
	return S_OK;
}

template< typename T>
inline HRESULT SaveArray(T* pValue, INT nSize, KRecordWriter* pWriter, unsigned short nType, int nVer = 0)
{
	KRecordWriter* pStructWriter = pWriter->StartRecord(nType);
	pStructWriter->Write(pValue, sizeof(T) * nSize);

	pStructWriter->EndRecord();
	delete pStructWriter;
	return S_OK;
}