// ����ģ��Ļص���
#ifndef		_I_K_DOWNLOAD_CALL_BACK_H_ 
#define		_I_K_DOWNLOAD_CALL_BACK_H_ 
#include "kcallbackdatadef.h"



typedef enum
{
	EVT_K_DOWNLOAD_INIT_UI = 0,					//��ʼ��UI��
	EVT_K_DOWNLOAD_INIT_ONE_FILE,				//��ʼ��һ�������ļ���
	EVT_K_DOWNLOAD_BEGIN,		
	EVT_K_DOWNLOAD_ONE_FILE_BEGIN,				// ����һ�ļ���ʼ��
	EVT_K_DOWNLOAD_ONE_FILE_END,				// ����һ�ļ�������
	EVT_K_DOWNLOAD_SUCCESSED,					//���سɹ�
	EVT_K_DOWNLOAD_FAILED,						//����ʧ��
	EVT_K_DOWNLOAD_START_DOWNLOADING,			//��ʼ����
	EVT_K_DOWNLOAD_GET_SIZEOF_FILE,				
	EVT_K_DOWNLOAD_PROCESS,						//���ؽ���
	EVT_K_DOWNLOAD_USER_BREAK,					//�û��ж�
	EVT_K_DOWNLOAD_CALLBACK_ALREADY_EXIST,		//���ػص��Ѵ���
	EVT_K_DOWNLOAD_USING_DEFAULT_BUFFER_SIZE,	//����ʹ��Ĭ��Buffer��С
	EVT_K_DOWNLOAD_PARAMETER_ERROR,				//���ز���������
	EVT_K_DOWNLOAD_PROXY_PARAMETER_ERROR,		//���ش�������������
	EVT_K_DOWNLOAD_COMM_INIT_ERROR,				//���س�ʼ��������
	EVT_K_DOWNLOAD_CONNECTING,					//����������
	EVT_K_DOWNLOAD_CONNECT_SUCCESSED,			//�������ӳɹ�
	EVT_K_DOWNLOAD_CONNECT_ERROR,				//��������ʧ��
	EVT_K_DOWNLOAD_GET_IP_FROM_DNS,				//���ش�DNS��ȡIP
	EVT_K_DOWNLOAD_SEND_REQUEST_ERROR,			//��������ʧ��
	EVT_K_DOWNLOAD_PARSE_HTTP_HEADER_ERROR,		//����Httpͷʧ��
	EVT_K_DOWNLOAD_HTTP_QUERY_INFO_ERROR,		//Http������Ϣ������
	EVT_K_DOWNLOAD_INTERNET_SET_OPTION_ERROR,	//��������������
	EVT_K_DOWNLOAD_AUTHENTICATION_DENIED,		//������֤ʧ��
	EVT_K_DOWNLOAD_PROXY_AUTHENTICATION_DENIED,	//������֤ʧ��
	EVT_K_DOWNLOAD_NEW_EVENT_PARAMS_ERROR,		
	EVT_K_DOWNLOAD_GET_SIZEOF_FILE_ERROR,		//��ȡ�ļ���Сʧ��
	EVT_K_DOWNLOAD_LOST_CONNECTION,				//����ʧȥ����
	EVT_K_DOWNLOAD_CREATE_FILE_ERROR,			//���ش�����ʱ�ļ�ʧ��
	EVT_K_DOWNLOAD_DISK_FULL,					//���ش��̿ռ���  �ύ�û��Ƿ���Ҫ����������1 ������0 ������ 
	EVT_K_DOWNLOAD_WRITE_FILE_ERROR,			//����д�ļ�����
	EVT_K_DOWNLOAD_WRITE_PROTECTED,				//����д�ļ�����
	EVT_K_DOWNLOAD_RETRY,						//��������

	EVT_K_DOWNLOAD_REMAIN_TIME						//����ʣ��ʱ��
} K_DOWNLOAD_EVT;



class IKDownloadCallBack
{
public:
	virtual int	OnDownloadEvent(K_DOWNLOAD_EVT nEvent, const KCallBackParam & stKCallBackParams = KCallBackParam()) = 0;
};

#endif		// #ifndef _I_K_DOWNLOAD_CALL_BACK_H_