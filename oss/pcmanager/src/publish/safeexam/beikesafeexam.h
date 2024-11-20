#pragma once

#include <Unknwn.h>
#include <atlcoll.h>

#define BK_SAFEEXAM_DLL_VERSION 4

#define EXAM_GUEST_STR L"GUEST"
#define EXAM_REMOTEDESK_STR L"REMOTEDESK"
#define EXAM_DUBA	L"Duba"
#define EVENT_EXAM_SHARE_DATA	L"Global\\EB225E90-D3CF-43b6-B618-9333BCF198C0"
#define NAME_EXAM_SHARE_MEM		L"Global\\196B4819-9676-4ec9-8FC8-7DE9CFB5E047"
#define EVENT_EXAM_RECV			L"Global\\D7A5FD89-4CFF-4b43-9D65-2722661A4301"
#define SIZE_EXAM_SHARE_MEM		0x400*0x400

//����лᴥ�����¼�
#define MSG_EXAM_SCAN_ITEM           (WM_APP + 1)
#define MSG_EXAM_SCAN_PROGRESS		 (WM_APP + 11)



//�����Ŀ��Ӧ��ID�����������һ����ID�Ѿ�����ʹ���ˣ�����Ϊ�˱���ԭ����˳���û�������
namespace BkSafeExamItem
{
    enum
    {
        Invalid = 0,						//������
        CriticalPathVirusScan   = 1,        // �ؼ�Ŀ¼����ɨ��->1
        SystemLeakScan,                     // ϵͳ©��ɨ��->2
        MalwareScan,                        // ������ɨ��->3
        HandShake,                          // ����->4
        ConfigAutoReport,                   // �Զ��ϴ��ļ�����->5
        ConfigAutoUpdate,                   // �Զ���������->6
        ConfigSystemMonitor,                // ���״̬->7
        DenyChangeIEMainPage,               // ��ֹ�û�����IE��ҳ->8
        LongTimeNoScan,                     // ̫��ûȫ��ɨ����->9
        LocalInfo,                          // ������Ϣ->10
		//////////////////////////////////////////////////////////////////////////
		//����Ϊ�����������Ŀ
		EXAM_HOMEPAGE=11,				    //���IE��ҳ->11
		EXAM_IE_LNKFILE_PARAM,				//IE ��ݷ�ʽָ������->12
		EXAM_IE_RIGHT_MENU,					//IE�Ҽ��˵�->13
		EXAM_IE_TOOLBAR_ICON,				//������ͼ��->14
		EXAM_IE_TOOLBAR,					//Σ�չ�����->15
		EXAM_IE_DEFAULT_SEARCH_ENG,			//IEĬ����������->16
		EXAM_IE_DIY_SEARCH_ENG,				//IE�Զ�����������->17
		EXAM_IE_SEARCH_PAGE,				//IEĬ������ҳ��->18
		EXAM_HOSTS_FILE,					//���HOSTS�ļ�->19
		EXAM_IE_SAFE_WEB,					//IE������վ��->20
		EXAM_IE_BROWSE,						//INTERNETѡ��->21
		EXAM_HTML_FILE,						//HTML�ļ�����->22
		EXAM_PROTOCOL_DEFAULT,				//���Ĭ��Э�����->23
		EXAM_PROXY_SERVER,					//���������->24
		EXAM_HOMEPAGE_CAN_SET,				//���IE��ҳ�Ƿ�����Զ�������->25
		EXAM_REGEDIT_RUN,					//���ע���༭���Ƿ����->26
		EXAM_GPEDIT_RUN,					//���������Ƿ����->27
		EXAM_GUEST_RUN,						//���GUEST�˻��Ƿ����->28
		EXAM_HIDE_FOLDER_RUN,				//��������ļ����Ƿ����->29
		EXAM_SHARE_RESOUCE,					//��⹲����Դ->30
		EXAM_REMOTE_DESKTOP,				//���Զ������->31
		EXAM_KWS_MON,						//������ܱ���->32			
        EXAM_CONNECT_SRV,					//����->33
		EXAM_TRASH,							//���ϵͳ���Ƿ��������->34 �������������� [7/19/2010 zhangbaoliang]
		EXAM_DRIVERORDIRECTORYOPEN,			//�����̣��ļ��д��Ƿ�����->35
		//////////////////////////////////////////////////////////////////////////
		//�����������Ҫʹ�����ܽ���������Ŀ
		EXAM_FAVORITES_URL,					//����ղؼ����Ƿ���ڶ����ƹ����ַ->36
		EXAM_SYSTEM_EXCEPTION,				//�Ƿ����ϵͳ�쳣->37
		EXAM_NOTIE_LNK,						//��IE�������ݷ�ʽ�Ƿ񱻴۸�->38
		EXAM_DESKTOP_SYSTEM_EXCEPTION_ICON,	//�������ͼ��->39
		EXAM_DESKTOP_EXCEPTION_ICON,		//�쳣������ͼ��->40
		EXAM_RUNOPT_ONKEY,					//һ���Ż�->41
		EXAM_CHECK_UPDATE,					//����������->42
		EXAM_CHECK_AV,						//���ɱ�����->43

        Count                               // ��ֹ���
    };

	//
	struct STRUCT_BKSAFE_EXAM_ITEM
	{
		DWORD dwID;
		int nGroupID;
		int nSubItemID;
		LPCTSTR pszCaption;

	};
}

//���ɨ�����������ݽṹ
namespace BKSafeExamItemEx
{
	struct SHARE_RESOURCES 
	{
		CString pszName;
		CString pszPath;
		SHARE_RESOURCES()
		{
			pszPath.Empty();
			pszName.Empty();
		}
	};

	//©����չ���
// 	struct BKSafeExamLeakEx 
// 	{
// 		int nHightLeakCount;//��Σ
// 		int nOptionLeakCount;//��ѡ
// 		int nSpLeakCount;//SP����
// 		BKSafeExamLeakEx()
// 		{
// 			nHightLeakCount = 0;
// 			nOptionLeakCount = 0;
// 			nSpLeakCount = 0;
// 		}
// 	};

	struct BKSafeExamEx
	{
		union
		{
			//©����չ���
			struct BKSafeExamLeakEx 
			{
				int nHightLeakCount;//��Σ
				int nOptionLeakCount;//��ѡ
				int nSpLeakCount;//SP����
				void Reset()
				{
					nHightLeakCount = 0;
					nOptionLeakCount = 0;
					nSpLeakCount = 0;
				}
			}ExamLeakEx;
			//����ɨ����չ��Ϣ
			struct BKSafeExamKWSResultEx
			{
				int nItemID;
				int nDangerCount;
				void Reset()
				{
					nItemID = -1;
					nDangerCount = 0;
				}
			}ExamKwsResultEx;
			//����
			struct BKSafeExamTrash
			{
				int nSize;
				void Reset()
				{
					nSize = -1;
				}
			}Trash;
			//�������,��Ҫ�������������
			struct BKSafeCheckUpdate
			{
				int nNeedUpdateCount;
				void Reset()
				{
					nNeedUpdateCount = 0;
				}
			}BKSafeUpdate;
            //ʵʱ�������ؽ��
            struct BKSafeMonitorInfo
            {
                int nDisableCount;
                int arrDisableID[10];

                void Reset()
                {
                    nDisableCount = 0;
                    memset(arrDisableID, -1, sizeof(arrDisableID));
                }
            }BKSafeMonitor;
		}u;
		BOOL bInvalid;

		void Reset()
		{
			bInvalid = FALSE;
		}

	};
}

//���ɨ��ʱ��Ҫ����Ϣ
class BKSAFE_EXAM_RESULT_ITEM
{
public:

	int     nLevel;
	CString strItemNoticeText;
	CString strOperationText;
	CString strItemNavigateString;
	CString strItemDetailUrl;
	CString strDetail;
	BKSafeExamItemEx::BKSafeExamEx SafeExamItemEx;
};

//����޸�ʱ��Ҫ����Ϣ
struct REMOVE_EXAM_RESULT_ITEM
{
	union
	{
		struct _RemoveItemInfo 
		{
			DWORD dwItemID;					//���ID
			DWORD dwTotalDangerCount;		//��ǰID�ܹ��ж��ٸ�Σ����Ŀ
			DWORD dwRemoveDangerCount;		//�������˼���Σ����Ŀ
			int Reset()
			{//����
				dwItemID = -1;
				dwTotalDangerCount = 0;
				dwRemoveDangerCount = 0;
				return 0;
			}
			_RemoveItemInfo& operator =(int nItem)
			{
				dwItemID = nItem;
				dwTotalDangerCount = 0;
				dwRemoveDangerCount = 0;

				return *this;
			}
		}RemoveItemInfo;
	}uRemoveItem;
};
//��칲�����ݽṹ

struct BKSafe_Exam_ShareData
{
	DWORD	cbSize;
	UINT	uMsg;
	int		nItem;
	union
	{
		struct BKSAFE_EXAM_SCAN_ITEM
		{
			int     nLevel;
// 			WCHAR   pszItemNoticeText[MAX_PATH];
// 			WCHAR	pszOperationText[MAX_PATH];
// 			WCHAR	pszItemNavigateString[MAX_PATH];
// 			WCHAR	pszItemDetailUrl[MAX_PATH*2];
// 			WCHAR	pszDetail[MAX_PATH];
			BKSafeExamItemEx::BKSafeExamEx SafeExamItemEx;
			void Reset()
			{
				nLevel = -1;
// 				ZeroMemory(pszDetail, sizeof(pszDetail));
// 				ZeroMemory(pszItemDetailUrl, sizeof(pszItemDetailUrl));
// 				ZeroMemory(pszItemNavigateString, sizeof(pszItemNavigateString));
// 				ZeroMemory(pszItemNoticeText, sizeof(pszItemNoticeText));
// 				ZeroMemory(pszOperationText, sizeof(pszOperationText));
			}

			BKSAFE_EXAM_SCAN_ITEM& operator =(BKSAFE_EXAM_RESULT_ITEM& scanitem)
			{
				this->nLevel = scanitem.nLevel;
// 				_sntprintf_s(pszDetail, sizeof(pszDetail), L"%s", scanitem.strDetail);
// 				_sntprintf_s(pszItemDetailUrl, sizeof(pszItemDetailUrl), L"%s", scanitem.strItemDetailUrl);
// 				_sntprintf_s(pszItemNavigateString, sizeof(pszItemNavigateString), L"%s", scanitem.strItemNavigateString);
// 				_sntprintf_s(pszItemNoticeText, sizeof(pszItemNoticeText), L"%s", scanitem.strItemNoticeText);
// 				_sntprintf_s(pszOperationText, sizeof(pszOperationText), L"%s", scanitem.strOperationText);
				SafeExamItemEx = scanitem.SafeExamItemEx;

				return *this;
			}
		}BKSafe_Exam_Scan_Item;

		struct BKSAFE_EXAM_REMOVE_ITEM 
		{
			REMOVE_EXAM_RESULT_ITEM RemoveItemData;
		}BKSafe_Exam_Remove_Item;

		struct BKSAFE_EXAM_PROGRESS
		{
			int nProgress;
		}BKSafe_Exam_Progress;

		struct BKSAFE_EXAM_STATE
		{//0����ʼ��죬1��ȡ����죬2��������
			int nState;
		}ExamState;

	}u;
};
//���������б����ݽṹ
namespace BkSafeExamLib
{
	class LocalLibExport
	{
	public:
		LocalLibExport(){ZeroMemory(pszValue, 1024);nType = -1;};
		int nType;
		WCHAR pszValue[1024];
	};
	class LocalLib
	{
	public:
		LocalLib(){nType = -1;strValue = L"";};
		~LocalLib(){nType = -1;strValue = L"";};
		int nType;
		CString strValue;
	};

	class LocalLibInfo
	{
	public:
		CString strCaption;
		CAtlArray<LocalLib> arrLib;	
	};

	struct HostFileItem
	{
		int nGroupID;
		int nItemID;
		int nLevel;
		CString strHostItem;
		HostFileItem()
		{
			nLevel = -1;
			nGroupID = -1;
			nItemID = -1;
			strHostItem.Empty();
		}
	};
}

//����п��ܷ��ص�Σ�յȼ�
namespace BkSafeExamItemLevel
{
    enum
    {
        Unknown   			= -1,		//δ֪
        Safe      			= 0,		//��ȫ
        Info      			= 1,		//δʹ��
        RiskInfo  			= 2,		//δʹ��
        Critical  			= 3,		//Σ��
        Risk_0    			= 4,		//����
		Scan_Error			= 5,		//ɨ��ʧ��
		Optimization		= 6			//���Ż���Ŀ
    };
}

namespace BkSafeExamItemExOperate
{
	enum
	{
		UnKnown = -1,
		RemoveItem = 1000,	//�����޸�
	};

	enum
	{
		Unknown = -1,
		ErrorMsg = 2000,
	};
}

interface IBkSafeExamineCallback
{
    virtual HRESULT WINAPI OnItemExamFinish(
        int     nItem, 
        int     nLevel, 
        LPCWSTR lpszItemNoticeText, 
        LPCWSTR lpszOperationText, 
        LPCWSTR lpszItemNavigateString, 
        LPCWSTR lpszItemDetailUrl, 
        LPCWSTR lpszDetail) = 0;
    virtual HRESULT WINAPI OnFinish() = 0;
    virtual HRESULT WINAPI OnProgress(DWORD dwProgress, int nExamItem = -1) = 0;
};

interface  __declspec(uuid("EA024B3E-9484-4536-8841-FDFA3FC0EA0E"))
IBkSafeExaminer
    : public IUnknown
{

	//@
	//@:Initialize
	//@:���ģ��ĳ�ʼ���ӿڣ�����ģ��֮���ȵ��������ʼ������
	//@
    virtual HRESULT WINAPI Initialize(LPVOID pvParam) = 0;

	//@
	//@:Uninitialize
	//@;����ʼ��
	//@
    virtual HRESULT WINAPI Uninitialize() = 0;

	//@
	//@:Examine���ӿ�
	//@:piCallback������ص��ӿ�ָ�룬hStopEventֹͣ�¼����
	//@
    virtual HRESULT WINAPI Examine(IBkSafeExamineCallback *piCallback, HANDLE hStopEvent, BOOL bSlowMode = FALSE) = 0;

	//@
	//@:ExpressExamine
	//@:�Ͻӿ���ʱ�Ѿ���ʹ��
	//@
    virtual HRESULT WINAPI ExpressExamine(IBkSafeExamineCallback *piCallback, HANDLE hStopEvent) = 0;

	//@
	//@:Echo
	//@�Ͻӿ��Ѿ���ʹ��
	//@
    virtual HRESULT WINAPI Echo(IBkSafeExamineCallback *piCallback, HANDLE hStopEvent) = 0;

	//@
	//@:FixItem
	//@:���ģ����޸��ӿ�(��Ϊ��ʿ�е�����޸���������ͨ���л�������TAB����Ӧ��ģ���������޸���
	//  ����Ŀǰ����ӿڣ�ֻ�Ǳ������޸���������Դ��Զ�����棬GUEST�˻��������޵�����)
	//@:nItemID��Ҫ�޸���Ŀ��ID��pExData�޸�ĳ��Ҫʹ�õ�����
	//@
	virtual HRESULT WINAPI FixItem(int nItemID, void* pExData = NULL) = 0;

	//@
	//@:ResetIgnoreArray
	//@:�Ͻӿڣ��Ѿ���ʹ��
	//@
    virtual HRESULT WINAPI ResetIgnoreArray() = 0;

	//@
	//@:PushAnIgnoreItem
	//@:�Ͻӿڣ��Ѿ���ʹ��
	//@
	virtual HRESULT WINAPI PushAnIgnoreItem(int nItemID) = 0;

	//@
	//@:GetItemCount
	//@:�û�����ȡ��쵽��Σ����Ŀ�µ��������,���繲����Դ��������ش��ڹ�����Դ�ĸ���
	//@:nItemID�����ĿID��nCount ������Ŀ
	//@
    virtual HRESULT WINAPI GetItemCount(int nItemID, int& nCount) = 0;

	//@
	//@:EnumItemData
	//@:ö�������Ŀ�е���������
	//@��nItemID �����ĿID��nIndex�������Ŀ����������pData����������
    virtual HRESULT WINAPI EnumItemData(int nItemID, int nIndex, void** pData) = 0;

	//@
	//@:SetItemSafe
	//@:�������ι���.�������Ը�����Ŀ�������ι��ܡ�(Զ�����棬guest�˻�)
	//@:nItemID�������ĿID�� pData������������Ŀ����Ϣ(Զ�����洫�ݣ�REMOTEDESK, guest���ݣ�GUEST���������������ļ������к궨��)
	//@
    virtual HRESULT WINAPI SetItemSafe(int nItemID, void** pData) = 0;

	//@
	//@:SetHostItemFix
	//@:�Ͻӿ��ݲ�ʹ��
	//@
	virtual HRESULT WINAPI SetHostItemFix(int nIndex) = 0;

	//@
	//@:RemoveLocalLibItem
	//@:ȡ������ĳ��������б����Ƴ�(���������ļ���cfg/LocalLib.dat)
	//@:nItemID�������ĿID��pValue��ȡ��������Ϣ(������������Ϣһ��)
	//@
	virtual HRESULT WINAPI RemoveLocalLibItem(int nItemID, void* pValue) = 0;

	//@
	//@:GetSafeLibItemCount
	//@:��ȡ���������б����������ݵ�����
	//@:nCount������ֵ��������������
	//@
	virtual HRESULT WINAPI GetSafeLibItemCount(int& nCount) = 0;

	//@
	//@:EnumSafeLibItem
	//@:ö����������(��Ҫ�Ǳ��ع�����Դʹ��)
	//@
	virtual HRESULT WINAPI EnumSafeLibItem(int nIndex, BkSafeExamLib::LocalLibExport& libItem) = 0;

	//@
	//@:LocalLibIsHaveItem
	//@:��Ҫ�û�GUEST,��Զ�����棬����Ƿ񱻺��Թ�
	//@
	virtual HRESULT WINAPI LocalLibIsHaveItem(int nItemID, BOOL& bHave) = 0;

	//@
	//@:StartupAnUse
	//@:����ĳ��ܡ�(��������ʹ����GUEST,��Զ�����棬����ʱ���������GUEST,
	//  Զ�������Ѿ������ã��ṩ�������ܣ����������û����ʹ���Ŀ¼)
	//@
	virtual HRESULT WINAPI StartupAnUse(int nItemID) = 0;

	//@
	//@:ExamItem
	//@:�������ĳ���ֱ�ӷ��ؽӿ�,����ӿ�����ֻ�Ǳ�����������ã���Ϊ���������ʱ��ѡ�����Ŀ��ʱ���
	//  ���Ĭ�ϵ��õ�ѡ���ǲ�һ���ģ����������˶��λ�ɨ
	//@:ExamItemData�������������
	virtual HRESULT WINAPI ExamItem(int nItemID, BKSafeExamItemEx::BKSafeExamEx& ExamItemData) = 0;
};


#define FN_BkSafeCreateObject               "BkSafeCreateObject"
typedef HRESULT (WINAPI *PFN_BkSafeCreateObject)(DWORD dwNeedDllVersion, REFCLSID rclsid, LPVOID *ppiOut);

#define BKSF_EXAM_LOCAL_INFO_FILE_NAME      "msg.ini"

namespace ExamPubFunc
{
	const static DWORD g_KwsItem[] = {11, 40, 12, 39, 21, 16, 38, 36, 22,37};
	class CExamPubFunc
	{
	public:
		~CExamPubFunc(){};
		static CExamPubFunc* GetPubFuncPtr()
		{
			static CExamPubFunc func;
			return &func;
		}
		
		int GetKwsExamItem(CSimpleArray<int>& arrExamItem)
		{
			arrExamItem.RemoveAll();
			int nCount = sizeof(g_KwsItem)/sizeof(DWORD);
			for (int i = 0; i < nCount; i++)
			{
				arrExamItem.Add(g_KwsItem[i]);
			}
			return arrExamItem.GetSize();
		}

		int ConvertKWSIDToExamID(int nKwsID)
		{
			int nExamID = -1;
			switch(nKwsID)
			{
			case 0:
				{//����������ҳ�Ƿ񱻶���۸�ָ���쳣��ַ
					nExamID = BkSafeExamItem::EXAM_HOMEPAGE;
				}
				break;
			case 1:
				{//����Ƿ������å����ƹ���쳣����ͼ��
					nExamID = BkSafeExamItem::EXAM_DESKTOP_EXCEPTION_ICON;
				}
				break;
			case 2:
				{//���IE�������ݷ�ʽ�Ƿ񱻶���۸�
					nExamID = BkSafeExamItem::EXAM_IE_LNKFILE_PARAM;
				}
				break;
			case 3:
				{//��ⳣ������ͼ���Ƿ񱻶���۸�
					nExamID = BkSafeExamItem::EXAM_DESKTOP_SYSTEM_EXCEPTION_ICON;
				}
				break;
			case 4:
				{//���Internetѡ���IE����������Ƿ�����쳣
					nExamID = BkSafeExamItem::EXAM_IE_BROWSE;
				}
				break;
			case 5:
				{//��������Ĭ�����������Ƿ�����쳣
					nExamID = BkSafeExamItem::EXAM_IE_DEFAULT_SEARCH_ENG;
				}
				break;
			case 6:
				{//����IE������������Ŀ�ݷ�ʽ�Ƿ񱻶���۸�
					nExamID = BkSafeExamItem::EXAM_NOTIE_LNK;
				}
				break;
			case 7:
				{//����ղؼ��Ƿ���ڶ����ƹ����ַ
					nExamID = BkSafeExamItem::EXAM_FAVORITES_URL;
				}
				break;
			case 8:
				{//���httpЭ�鼰��ҳ�ļ������Ƿ�����
					nExamID = BkSafeExamItem::EXAM_HTML_FILE;
				}
				break;
			case 9:
				{//����Ƿ����������ϵͳ�쳣����
					nExamID = BkSafeExamItem::EXAM_SYSTEM_EXCEPTION;
				}
				break;
			case 10:
				{
				}
				break;
			case 11:
				{
				}
				break;
			case 12:
				{
				}
				break;
			}
			return nExamID;
		}

	};
}
