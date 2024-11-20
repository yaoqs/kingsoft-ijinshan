// ----------------------------------------------------------------------------- 
//	FileName	: oeminforw.h
//	Author		: Zqy
//	Create On	: 2007-11-10 18:17:57
//	Description	: 
//
// ----------------------------------------------------------------------------- 
#ifndef _OEMINFORW_H_
#define _OEMINFORW_H_
// ----------------------------------------------------------------------------- 
#include <vector>


#pragma pack(4)
#pragma warning( push )
#pragma warning( disable : 4200 )


enum FDRecType
{
	rtStart	  = 0x100,	//��һ����¼	
	rtGroup	  = 0x101,	//��ʼһ������
	rtIntData = 0x102,	//����			FDIntData
	rtStrData = 0x103,	//�ַ�������	FDStrData
	rtEnd	  = 0xFFF,	//��ʾ����
};

struct FDPackInfoHeader
{
	WORD wType;
	WORD wTotalSize;
};
struct FDRecHeader
{
	WORD type;
	WORD len;
};

struct FDStart
{
	int filever;		//FeatureData����İ汾��
						//2008�� 12
	int datas;			//�ж��ٸ�FeatureData
	int reserved[4];	//������Ϊ0
	int groups;			//�ж��ٸ�����
	int offset[0];		//ÿ�������¼(FDGroup)�ļ�¼ͷ���ļ��е�ƫ����
};

//GROUPID������ID��
#define FDGROUPID_MASK 0xFFFF0000

struct FDGroup
{
	int groupid;	//�����
	int fdcnt;		//�����е�FeatureData����
	int offset[0];	//������ÿһ��ֵ�ļ�¼ͷ(FDRecHeader)���ļ��е�ƫ����
};

struct FDIntData
{
	DWORD id;
	DWORD val;
};

struct FDStrData
{
	DWORD id;
	DWORD len; //����������0
	WCHAR val[0];
};

struct FDEnd
{
	DWORD reserved;
};

#pragma warning( pop )
#pragma pack()

#define MAX_GROUP 4

class KFeatureReader
{
	BYTE* m_buf;
	BYTE* m_end;	//rtEnd��¼ͷ����

	FDGroup* m_groups[MAX_GROUP];
	FDStart* m_FDStart;
	
	FDRecHeader* Find(int id);
	FDGroup* FindGroup(int id);
	BOOL ValidRange(void* p, int size = 0);
public:
	KFeatureReader();
	~KFeatureReader();

	FDStart* GetFDStart();
	int QueryInt(int id);
	LPCWSTR QueryStr(int id);
	HRESULT Load(LPCWSTR lpcwFile);

protected:
	HRESULT Clear();
};

class KFeatureWriter
{
	struct GROUP : std::vector<FDRecHeader*>
	{
		BOOL used;
		int datasize;	//�����������ݴ�С
	};

	BYTE m_bufStart[sizeof(FDStart) + sizeof(int) * MAX_GROUP];
	FDStart* m_start;
	GROUP  m_groups[MAX_GROUP];
	GROUP* m_grp;

	BOOL m_failed;
	BOOL CheckID(int id);
public:
	KFeatureWriter();
	~KFeatureWriter();
	
	void Over();

	KFeatureWriter& Start();
	KFeatureWriter& StartGroup(int grpid);
	KFeatureWriter& AddFeature(int id, int Val);
	KFeatureWriter& AddFeature(int id, LPCWSTR lpcwVal);
	KFeatureWriter& EndGroup(int grpid);

	HRESULT End();

	HRESULT Write(LPCWSTR lpcwPath);
};


// ----------------------------------------------------------------------------- 
#endif //_OEMINFORW_H_
