// uplive���ܻص���
#ifndef		_I_K_UPLIVE_CALL_BACK_H_ 
#define		_I_K_UPLIVE_CALL_BACK_H_ 

#include "kcallbackdatadef.h"
#include "ikanalyzecallback.h"
#include "ikdownloadcallback.h"
#include "ikupdatecallback.h"

typedef enum
{
	EVT_K_UPLIVE_SERVER_CONFIG_IS_NOT_EXIST = -1,	//Uplive.svr ������
	EVT_K_UPLIVE_SET_PARAM_FAILED,					//UpdateLogic���ò���ʧ��
	EVT_K_UPLIVE_DISK_SPACE_NO_ENOUGH,				//���̿ռ䲻��

	EVT_K_UPLIVE_USER_BREAK,						//�û��ж�

	EVT_K_UPLIVE_START_VERCTRL,						//��ʼ���а汾�ж�
	EVT_K_UPLIVE_DETECTING_VERCTRL_FAILED,			//�汾�ж�ʧ��
	EVT_K_UPLIVE_DETECTING_VERCTRL_FINISHED,		//�汾�жϳɹ�

	EVT_K_UPLIVE_START_DEMANDBANDWIDTH,				//��ʼ���д�������
	EVT_K_UPLIVE_DETECTING_DEMANDBANDWIDTH_FAILED,	//�������벻ͨ��
	EVT_K_UPLIVE_DETECTING_DEMANDBANDWIDTH_FINISHED,	//��������ɹ�
	
	EVT_K_UPLIVE_ANALYS_INDEX_START,				//��ʼ����Index
	EVT_K_UPLIVE_ANALYS_INDEX_FAILED,				//Index����ʧ��
	EVT_K_UPLIVE_ANALYS_INDEX_FINISHED,				//Index�������

	EVT_K_UPLIVE_DOWNLOAD_FILE_INIT,				//����ģ���ʼ����
	EVT_K_UPLIVE_DOWNLOAD_FILE_START,				//��ʼ�����ļ���
	EVT_K_UPLIVE_DOWNLOAD_FILE_FINISHED,			//�����ļ�������
	
	EVT_K_UPLIVE_UPDATE_FILE_START,					// ��ʼ�����ļ���
	EVT_K_UPLIVE_UPDATE_FILE_FINISHED,				// �����ļ�������

	EVT_K_UPLIVE_VERIFYING_PASSPORT_START,			//��֤ͨ��֤
	EVT_K_UPLIVE_VERIFY_PASSPORT_FAILED,			//��֤ͨ��֤ʧ��
	EVT_K_UPLIVE_VERIFY_PASSPORT_EXPIRED,			//ͨ��֤����
	EVT_K_UPLIVE_UPDATE_TOO_MUCH,					//������������
	EVT_K_UPLIVE_VERIFY_PASSPORT_SUCCESS,			//��֤ͨ��֤�ɹ�

	
	EVT_K_UPLIVE_PRODUCT_CHANNEL_INFO,				//��Ʒ��Ƶ����Ϣ���͵�����


	EVT_K_UPLIVE_GET_CURRENT_POS_X,
	EVT_K_UPLIVE_GET_CURRENT_POS_Y,

	EVT_K_UPLIVE_AUTO_EXIT_APP,						// �Զ��˳�uplive
	EVT_K_UPLIVE_RELOAD_APP,						//����������Ҫ�Ը���
	//EVT_K_UPLIVE_THREAD_EXITED,					//�����߳��ѽ���(�Ѳ���Ҫ�ûص�����ûص�ֻ��ʾ�����߳������˳�)��

	EVT_K_UPLIVE_OFFLINE_PACKAGE_START,				// ������������ʼ��
	EVT_K_UPLIVE_OFFLINE_PACKAGE_FINISHED,			// ������������ɡ�
	EVT_K_UPLIVE_OFFLINE_PACKAGE_DISK_ERROR,		// �������������̲����á�
	EVT_K_UPLIVE_OFFLINE_PACKAGE_INDEX_ERROR,		// ����������index�ļ������ã������ڣ���
	EVT_K_UPLIVE_OFFLINE_PACKAGE_DISK_FULL,			// �������������̿ռ䲻�㡣
	EVT_K_UPLIVE_WIN_PE_INIT_FAILED,				// WinPEͬ����ʼʧ�ܣ�δ��װ���ԣ�Windows�������ô���

} K_UPLIVE_EVT;


typedef enum
{
	EVT_K_DATA_SET_OPTION_AutoRunFlag = 0,			//�Ƿ��̨����
	EVT_K_DATA_SET_OPTION_SelfContinueFlag,				//�Ը��¼�����
	EVT_K_DATA_SET_OPTION_ReUpdateFlag,				//���¸����ļ���
	EVT_K_DATA_SET_OPTION_Proxy,					//����ѡ��
	EVT_K_DATA_SET_OPTION_UpdateMethod,				//������ʽ
	EVT_K_DATA_SET_OPTION_UpdateMode,				//����ģʽ
	EVT_K_DATA_SET_OPTION_NotifyPPWizShowDlg,	//֪ͨPPWsiz��ʾ����
	EVT_K_DATA_SET_OPTION_OnTopWhenRun,				//�Ƿ��ö���ʾ
	EVT_K_DATA_SET_OPTION_SyncToHpa,				//ͬ��ɱ��ƽ̨
	EVT_K_DATA_SET_OPTION_UpdateSelf,				//�Ƿ����Ը���
	EVT_K_DATA_SET_OPTION_LanPath,					//����������·��
	EVT_K_DATA_SET_OPTION_KISCommon_ProductName,	//�������
	EVT_K_DATA_SET_OPTION_KISCommon_IndexName,		//���inde����
	EVT_K_DATA_SET_OPTION_OfflinePackage_SpaceSize,		//������������Ҫ�Ŀռ��С��
	EVT_K_DATA_SET_OPTION_OfflinePackage_FileCount,		//������������Ҫ���ļ���С��

}K_KISDATA_EVT;

typedef struct tagUpdateStatus
{
	DWORD				dwID;
	DWORD				dwSize;
	char*				pszBuf;
} K_UPDATE_STATUS;


class IKUpliveCallBack 
	: public IKAnalyzeCallBack, 
	  public IKDownloadCallBack, 
	  public IKUpdateCallBack
{
public:
	virtual int		OnUpliveEvent(K_UPLIVE_EVT nEvent, const KCallBackParam & stKCallBackParams = KCallBackParam()) = 0;
	virtual int		OnKisDataEvent(K_KISDATA_EVT nEvent, const KCallBackParam & stKCallBackParams = KCallBackParam()) = 0;
};

#endif		// #ifndef _I_K_UPLIVE_CALL_BACK_H_