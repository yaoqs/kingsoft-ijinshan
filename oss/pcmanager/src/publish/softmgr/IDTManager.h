/**
* @file    IDtManager.h
* @brief   ���ع���
* @author  liveck
* @date    2010/04/09 20:11
*/

#pragma once

enum DTManager_Stat{TASK_DONE=0,TASK_DOWNING,TASK_PAUSED,TASK_CONECTING,TASK_ERROR,TASK_ERROR_MD5};


typedef void (*GetTaskCallback)(void* tk,void* para);
static void GetTaskCallbackByArr(void* tk,void* para)
{
	CAtlArray<void*>* tasks=(CAtlArray<void*>*)para;
	tasks->Add(tk);
}

//��ȡ������Ϣ�Ļص�
typedef void (*InfoCallBack)(__int64 cur,__int64 all,__int64 speed,DWORD time,void* para);

//������ȷ����仯�Ļص�
/**
* tk������������ 
* para���Զ���ص��Ĳ���
*
*/
typedef void (*DtStateChangeNotifyCallBack)(DTManager_Stat st,void* tk,void* para);

class __declspec(uuid("43D2ACDB-2D19-4637-8BE9-4B5FF020A2E3")) IDTManager
{
public:
	virtual void Init(CAtlMap<DtStateChangeNotifyCallBack,void*>* calls)=0;

	/**
	* �½��������ش�cur��ʼ
	* @return   void*
	* @param CAtlArray<CString> * urls ���һ��url�ᱻ���̴߳���
	* @param CString localfile
	* @param int64 cur
	*/
	virtual void* NewTask(CAtlArray<CString>* urls,CString md5,CString localfile)=0;

	/**
	* �ָ���ֹͣ������ 
	* @return   void
	* @param void * context
	* @remark ���resume������Ŷ��
	*/
	virtual void ResumeTask(void* context)=0;

	/**
	* ֹͣ����
	* @return   void
	* @param void * context
	*/
	virtual void PauseTask(void* context)=0;

	/**
	* ֹͣ����
	* @return   void
	* @param void * context
	*/
	virtual void StopTask(void* context)=0;

	/**
	* ȡ�����񣬻���context
	* @return   void
	* @param void * context
	*/
	virtual void CancelTask(void* context)=0;

	/**
	* ��ѯ��������
	* @return   size_t
	*/
	virtual size_t GetTaskCount()=0;

	virtual int GetTasks(GetTaskCallback func,void* para )=0;

	/**
	* ��ѯ������Ϣ
	* @return   void
	* @param void * tk
	* @param InfoCallBack func
	* @param void * para
	*/
	virtual void QueryTask(void* tk,InfoCallBack func,void* para)=0;
};