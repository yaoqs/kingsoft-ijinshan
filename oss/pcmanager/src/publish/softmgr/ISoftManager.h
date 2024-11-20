/**
* @file    ISoftManager.h
* @brief   �������
* @author  liveck
* @date    2010/04/07 21:50
*/

#pragma once

typedef void (*GetInfoCallback)(void* soft,wchar_t* name,wchar_t* value);

static void GetInfoUseMap(void* soft,wchar_t* name,wchar_t* value)
{
	CAtlMap<CString,CString>* p =(CAtlMap<CString,CString>*)soft;
	p->SetAt(name,value);
}

typedef void (*GetCatlogCallback)(void* cat,wchar_t* name);

static void GetCatlogUseArr(void* cat,wchar_t* name)
{
	CAtlArray<CString>* p =(CAtlArray<CString>*)cat;
	p->Add(name);
}


// NECESS	-  necessary  ��Ҫ��, �����, ��Ȼ��

struct NECESS_SOFT				// �ر��������������
{
public:
	NECESS_SOFT()
	{
		nSortIndex = 0;
	}
	bool operator < (NECESS_SOFT& cmp)
	{
		return nSortIndex<cmp.nSortIndex;
	}

	CString		strSoftID;		// ���ID
	DWORD		nSortIndex;		// ����
};

struct NECESS_TYPE
{
public:
	NECESS_TYPE()
	{
		nSortIndex = 0;
	}
	bool operator < (NECESS_TYPE& cmp)
	{
		return nSortIndex<cmp.nSortIndex;
	}

	CString		strTypeName;				// ��������
	DWORD		nSortIndex;					// ����
	CSimpleArray<NECESS_SOFT>	softList;	// �ر����
};

struct NECESS_GROUP
{
public:
	NECESS_GROUP()
	{
		nSortIndex = 0;
	}

	bool operator < (NECESS_GROUP& cmp)
	{
		return nSortIndex<cmp.nSortIndex;
	}

	CString		strGroupName;				// ������
	DWORD		nSortIndex;					// ������
	CSimpleArray<NECESS_TYPE>	typeList;	// �ر���type�б�
};


struct ONE_KEY_SOFT				// һ��װ�����������
{
public:
	ONE_KEY_SOFT()
	{
		nSortIndex	= 0;
		bCheck		= FALSE;
	}
	bool operator < (ONE_KEY_SOFT& cmp)
	{
		return nSortIndex<cmp.nSortIndex;
	}
	CString		strSoftID;		// ���ID
	DWORD		nSortIndex;		// ����
	BOOL		bCheck;
	CString		strShowName;	// ��ʾ����
};
struct ONE_KEY_TYPE
{
public:
	ONE_KEY_TYPE()
	{
		nSortIndex = 0;
	}
	bool operator < (ONE_KEY_TYPE& cmp)
	{
		return nSortIndex<cmp.nSortIndex;
	}
	CString		strTypeName;				// ��������
	DWORD		nSortIndex;					// ����
	CSimpleArray<ONE_KEY_SOFT>	softList;	// �ر����
};
struct ONE_KEY_GROUP
{
public:
	ONE_KEY_GROUP()
	{
		nSortIndex = 0;
	}
	bool operator < (ONE_KEY_GROUP& cmp)
	{
		return nSortIndex<cmp.nSortIndex;
	}
	CString		strGroupName;				// ������
	DWORD		nSortIndex;					// ������
	CSimpleArray<ONE_KEY_TYPE>	typeList;	// �ر���type�б�
};
class __declspec(uuid("2442A51E-7C0F-4225-BFEF-2B8B1EA3B8C5")) ISoftManager
{
public:
	/**
	* ���������
	* @return   int
	* @param CString lib_file
	* @param bool reload
	*/
	virtual int LoadSoftDB(CString lib_file) = 0;

	/**
	* ��������
	* @return   int
	*/
	virtual int FreeSoftDB() = 0;

	/**
	* �������
	* @return   int
	* @param CString cat
	*/
	virtual int GetSoftCount(CString cat) = 0;

	/**
	* ����idȡ�����Ϣ
	* @return   int
	* @param CString id
	* @param CAtlMap<CString
	* @param CString> & soft
	*/
	virtual int GetSoftById(CString id, GetInfoCallback func ,void* pSoft) = 0;

	/**
	* ��ȡװ���ر������Ϣ
	* @return   void*
	* @param CString cat
	*/
	virtual void* GetLast50Soft() = 0;

	/**
	* ��ȡװ���ر������Ϣ
	* @return   void*
	* @param CString cat
	*/
	virtual void* GetEssentialSoft(CString cat,CString rank=L"") = 0;

	/**
	* ����cat������Ϣ��ȡ�����Ϣ
	* 
	* @return   void*
	* @param CString cat catΪ""ʱ��ȡ��ȫ�������Ϣ
	* @param CString rank �����ȶ�����
	*/
	virtual void* GetAllSoft(CString cat,CString rank=L"") = 0;

	/**
	* ��ȡ����װ���ر������Ϣ
	*/
	virtual void* GetAllNecessSoft() = 0;


	/**
	* ���ݹؼ�������
	* @return   void*
	* @param CString cat
	* @param CString rank �����ȶ�����
	*/
	virtual void* SearchSoft(CString word,CString rank="") = 0;

	/**
	* GetAllSoft SearchSolft ֮�������ȡ�þ������Ϣ
	* @return   int
	* @param void * pos
	* @param CAtlMap<CString,CString> & soft
	*/
	virtual int GetNextSoft(void* pos, GetInfoCallback func ,void* soft) = 0;

	
	/**
	* ��ȡ�������Ϣ������ͷ�pos��������ڴ�й¶
	* @return   int
	* @param void * pos
	*/
	virtual int FinalizeGet(void* pos) = 0;

	/**
	* �����ȶ��ļ�
	* @return   CString rank_name Ĭ���ȶ�����
	* @param CString lib_file �ȶ��ļ�·��
	*/
	virtual CString LoadRank(CString lib_file) = 0;


	/**
	* �ͷ��ȶȿ�
	* @return   int
	* @param CString rank_name
	*/
	virtual int FreeRank(CString rank_name) = 0;


	/**
	* ��ȡ�������
	* @return   int ��������
	* @param CAtlArray<CString> & result
	*/
	virtual int GetCatalog(GetCatlogCallback func,void* para) = 0;

	/**
	* �²�ж��һ�仰����
	* @return   CString
	* @param CString name
	*/
	virtual CString GetUnistallInfo(CString name, GetInfoCallback func ,void* soft) = 0;
	

	///���ڲ�������
	virtual int Combine(CString diff_file)=0;

	//��ȡ����
	virtual int GetCategroy(GetInfoCallback func ,void* pParam) = 0;


	// ����װ���ر��Ŀ�
	virtual BOOL LoadNecessDat(LPCTSTR strLibFile) = 0;

	// ��ȡװ���ر�����
	virtual BOOL GetNecessSoftInfo( CSimpleArray<NECESS_GROUP>** ppInfo ) = 0;

	virtual BOOL GetOneKeySoftInfo( CSimpleArray<ONE_KEY_GROUP>** ppInfo) = 0;
	// �ͷ�װ���ر������ڴ�
	virtual VOID FreeNecessInfo() = 0;

	// ��ͷ����Ϣˢ�½������ݿ�
	virtual void UpdateCache() = 0;

	//�жϿ��ļ��������ļ��Ƿ�汾��һ��
	virtual BOOL IsLibUpdate() = 0;
};