#pragma once
#include "libdownload/libDownload.h"

//�ص�����
class IStatusCallback
{
public:
	/*
	* @funcn							--- OnStatusCallback
	* @param				enumState	---	��ǰ״̬
	* @param				nSpeed		---	��ǰ���صļ�ʱ�ٶ�
	* @param				nAvgSpeed	---	�����ļ���ƽ���ٶ�
	* @param				nProcess	---	��ǰ���صĽ���
	*/
	virtual void OnStatusCallback(ProcessState enumState, int64 nSpeed, int64 nAvgSpeed, int nProcess) = 0;

};


class KDownFile : public IHttpAsyncObserver
{
public:
	KDownFile(){	m_pDownLoad = NULL;		}
	~KDownFile()
	{	
		DeleteFile(m_strDownFileSavePath);	
		DeleteFile(m_strDownFileSavePathT);	
	}

public:
	//��ȡ�ļ������ٶ�
	int GetDownSpeed(IStatusCallback* pCallBack);

	/*
	* @funcn							--- OnHttpAsyncEvent
	* @brief							--- http�Ļص�����
	* @param pDownload					--- ָ���Ķ���
	* @param state						--- ָ����״̬
	*/
	virtual BOOL OnHttpAsyncEvent( IDownload* pDownload, ProcessState state, LPARAM lParam );

public:
	void StopDown(void);
	void WaitDown(void);
private:
	ULONG		m_uSpeed;			//��ʱ�����ٶ�
	ULONG		m_uAvgSpeed;		//ƽ�������ٶ�
	IDownload*	m_pDownLoad;
	IStatusCallback* m_pCallBack;
	CString		m_strUrlAddr;
	CString		m_strDownFileSavePath;
	CString		m_strDownFileSavePathT;
	DWORD		m_dwBegin;
	DWORD		m_dwEnd;
	
};