#ifndef _H_INCLUDE_GLOBAL_DATA_IESCANENG
#define _H_INCLUDE_GLOBAL_DATA_IESCANENG

namespace IEScanEng
{
#define CAPTION_MAX_LEN 100
#define REGPATH_MAX_LEN 512
#define FILEPATH_MAX_LEN 512
#define PATH_MAX_LEN 1024
#define DEFAULT_BUFFER_MAX_LEN 50
#define DES_MAX_LEN 256
#define IESCANENG_VER 1

#define ZEROMEM(x) ZeroMemory(x, sizeof(x))
#define SAFE_DELETE_PTR(x) if ((NULL != x)){delete (x); x = NULL;}

	//�ص�����
	typedef int (WINAPI *PFNIEScanEngCallBack)(ULONG uMsg, WPARAM wParam, LPARAM lParam, void* lpConext);

	//////////////////////////////////////////////////////////////////////////
	//�ṹ��

	typedef struct _ITEM_STRUCT_INFO_EXPORT
	{//����������ṹ
		int _nSubItemID;//����ID
		int _nGroupID;//��ID
		WCHAR _pszSubItemCaption[CAPTION_MAX_LEN];//�������
		_ITEM_STRUCT_INFO_EXPORT()
		{
			_nSubItemID = -1;
			_nGroupID = -1;
			ZEROMEM(_pszSubItemCaption);
		}
	}ITEM_STRUCT_INFO_EXPORT, *LPITEM_STRUCT_INFO_EXPORT;


	typedef struct _GROUP_STRUCT_INFO_EXPORT
	{//�����ķ�����Ϣ
		int _nGroupID;
		WCHAR _pszGroupCaption[CAPTION_MAX_LEN];
		int _nShow;//�Ƿ���ʾ
		int _nCheck;//�Ƿ�ѡ��

		CAtlArray<ITEM_STRUCT_INFO_EXPORT*> _vetSubItem;
		_GROUP_STRUCT_INFO_EXPORT()
		{
			_nShow = -1;
			_nCheck = -1;
			_nGroupID = -1;
			ZEROMEM(_pszGroupCaption);
			_vetSubItem.RemoveAll();
		}
	}GROUP_STRUCT_INFO_EXPORT, *LPGROUP_STRUCT_INFO_EXPORT;

	typedef struct _SCAN_RESULT_EXPORT
	{//�ص������е����Ľṹ��
		int _nGroupID;
		int _nSubItemID;
		int _nLevel;
		int _nScanIndex;//���ֵ��ʾ��ɨ������һ������ֵ����Ψһ��
		WCHAR _pszPath[PATH_MAX_LEN];//ɨ���·��
		WCHAR _pszFilePath[FILEPATH_MAX_LEN];//�ļ�·����Ϣ
		WCHAR _pszCaption[DEFAULT_BUFFER_MAX_LEN];//����ɨ��������������Ϣ
		WCHAR _pszDes[DES_MAX_LEN];//ɨ��������������Ϣ
		WCHAR _pszValue[REGPATH_MAX_LEN];//ɨ�赽��ֵ
		WCHAR _pszDefValue[REGPATH_MAX_LEN];//ϵͳĬ�ϵ�ֵ
		WCHAR _pszFixValue[REGPATH_MAX_LEN];//ָ��ʹ�õ��޸�ֵ
		_SCAN_RESULT_EXPORT()
		{
			_nGroupID = -1;
			_nSubItemID = -1;
			_nScanIndex = -1;
			_nLevel = -1;
			ZEROMEM(_pszCaption);
			ZEROMEM(_pszDes);
			ZEROMEM(_pszPath);
			ZEROMEM(_pszValue);
			ZEROMEM(_pszDefValue);
			ZEROMEM(_pszFixValue);
			ZEROMEM(_pszCaption);
		}
	}SCAN_RESULT_EXPORT, *LPSCAN_RESULT_EXPORT;

	//�����ӿ�
	interface IIEScanEng
	{
		//�����ȵ�������ӿڣ�����汾��һ�£��ͻ�����ʼ��ʧ�ܣ�����ĽӿھͲ��õ�����
		virtual int InitIEScanEng() = 0;
		//���ݸ�������ID, ������ID������ɨ�裬���nGroup = -1 && nID == -1��ö�����еģ�
		//���nGroup != -1 && nID == -1��ö��ָ�����µ���������, 
		//ע��nGroup����Ϊ��Чֵ
		virtual int Scan(int nGroup, int nID, PFNIEScanEngCallBack pfnCallBack, void* lpConext) = 0;
		//���ݸ�������Ϣ��ȥִ���޸�����
		//ע��nGroup����Ϊ��Чֵ
		virtual int Fix(LPSCAN_RESULT_EXPORT lpFixStruct) = 0;
		//ͨ��ID�޸���һ�㶼��ֱ���޸���Ĭ��ֵ
		virtual int Fix(int nGroup, int nID) = 0;
		//��ȡ��ȫ�ȼ�������Ϣ
		virtual int GetSafeLevel(int nLevel, LPWSTR pszSafeLevel, DWORD cbSize) = 0;
		//��ȡ�޸���ʽ������Ϣ
		virtual int GetFixOp(int nFixOp, LPWSTR pszFixOp, DWORD cbSize) = 0;
		//��ȡɨ�赽�ķ���ĸ���
		virtual int GetGroupCount() = 0;
		//ö��ɨ�赽�Ľṹ��
		virtual GROUP_STRUCT_INFO_EXPORT* EnumGroup(ULONG uIndex = 0) = 0;
		//��ȡָ���ķ���
		virtual GROUP_STRUCT_INFO_EXPORT* GetAnGroup(ULONG uGroupID = 0) = 0;
	};
}

#endif