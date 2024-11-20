// ����ģ��Ļص���
#ifndef		_I_K_UPDATE_CALL_BACK_H_ 
#define		_I_K_UPDATE_CALL_BACK_H_ 
#include "kcallbackdatadef.h"

enum K_UPDATE_EVT
{
	EVT_K_UPDATE_NEED_UPDATE_BEGIN,					// ��Ҫ���¿�ʼ��
	EVT_K_UPDATE_NEED_UPDATE_END,					// ��Ҫ���½�����
	EVT_K_UPDATE_NOT_UPDATE_FOR_DOWNLOAD_FAILED,	// ������ʧ�ܣ��ʲ����и��¡�
	EVT_K_UPDATE_NOT_UPDATE_FOR_NOT_NEED_UPDATE,	// �����ļ����£��ʲ����и��¡�
	EVT_K_UPDATE_ONE_FILE_UPDATE_BEGIN,				// ����һ���ļ���ʼ��
	EVT_K_UPDATE_ONE_FILE_UPDATE_END,				// ����һ���ļ�������
	EVT_K_UPDATE_NEED_REBOOOT,						// ��Ҫ������
	EVT_K_UPDATE_SUCCESSED,							// ���³ɹ���
	EVT_K_UPDATE_FAILED,							// ����ʧ�ܡ�
	EVT_K_UPDATE_NEED_UPDATE_SELF,					// ��Ҫ�Ը��¡�
	EVT_K_UPDATE_SHOW_TITLE_RESULT,
	EVT_K_UPDATE_SHOW_BOX_ITEM_RESULT,
	EVT_K_UPDATE_SHOW_BOX_ITEM_SUMMARY,
	EVT_K_UPDATE_SHOW_VIRUS_INFOS,					// ����������汾��������������
	EVT_K_UPDATE_SHOW_BOX_SUCCESSED,				// ShowBox���³ɹ�״̬��
	EVT_K_UPDATE_SHOW_BOX_FAILED,					// ShowBox����ʧ��״̬��
	EVT_K_UPDATE_SHOW_BOX_NOTIFY_FAILED,			// ShowBox����Windows/WinPe״̬��
	EVT_K_UPDATE_SHOW_BOX_END,						// ShowBox������
	EVT_K_UPDATE_REUPDATE_BEGIN	= 40,				// ReUpdate���¿�ʼ��
	EVT_K_UPDATE_REUPDATE_END,						// ReUpdate���½�����
	EVT_K_UPDATE_REUPDATE_SHOW_PROGRESS,			// ��ʾReUpdate���½�������
	EVT_K_UPDATE_REUPDATE_NOTIFY_UI,				// ��ʾReUpdate���½�������
	EVT_K_UPDATE_REUPDATE_FINISH,					// ��ʾReUpdate���½�������
};

class IKUpdateCallBack
{
public:
	virtual int	OnUpdateEvent(K_UPDATE_EVT enumEvent, const KCallBackParam & stKCallBackParams = KCallBackParam()) = 0;
};

#endif		// _I_K_UPDATE_CALL_BACK_H_
