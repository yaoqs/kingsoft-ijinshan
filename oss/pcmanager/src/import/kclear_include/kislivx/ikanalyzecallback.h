// ����ģ��Ļص���
#ifndef		_I_K_ANALYZE_CALL_BACK_H_ 
#define		_I_K_ANALYZE_CALL_BACK_H_ 
#include "kcallbackdatadef.h"


typedef enum
{
	EVT_K_ANALYS_FILE_DAT_IS_NOT_EXIST = -1,			//Index.dat������
	EVT_K_ANALYS_FILE_IS_NOT_EXIST,						//Index.txt������
	EVT_K_ANALYS_ERROR_ACCESS_DENIED,					//Index����ʧ��
	EVT_K_ANALYS_PROCSS,								//����������
	EVT_K_ANALYS_LAN_UPDATE_NOT_WHOLE_DATA,				//�������ݲ�����
	EVT_K_ANALYS_WIN_SYNC_ITEM,							//Winͬ��һ�������
	EVT_K_ANALYS_WIN_SYNC_ITEM_ERR_TIP					//Winͬ��һ�������������ʾ��
} K_ANALYZE_EVT;


class IKAnalyzeCallBack
{
public:
	virtual int		OnAnalyzeEvent(K_ANALYZE_EVT nEvent, const KCallBackParam & stKCallBackParams = KCallBackParam()) = 0;
};


#endif		// #ifndef _I_K_ANALYZE_CALL_BACK_H_