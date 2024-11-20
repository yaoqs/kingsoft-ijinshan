#pragma once

#include "scom/scom/scombase.h"

//�ڲ��ӿ�

struct IUpdMgr
{
	//LockCreate֪ͨ������������Ĵ���������������ʱ������UpdCtrl��������ܱ�����
	//Return:
	//	S_OK �ɹ�
	virtual HRESULT STDMETHODCALLTYPE LockCreate(
		) = 0;

	//UnlockCreate֪ͨ�����������������ٵ���ÿ�������CompleteUpdate֪ͨ����������Ѿ����
	//Return:
	//	S_OK �ɹ�
	virtual HRESULT STDMETHODCALLTYPE UnlockCreate(
		) = 0;


	//GetRelatedProcess���ݷ����ڱ���ĵ��ù�ϵ������������clsids�Ľ�����̵��б�������ʾ�û�������¼
	//Return:
	//	S_OK �ɹ�ȡ�������б�
	//	E_OUTOFMEMORY ����ķ���ID���ڴ治����
	//  E_FAIL ʧ��
	virtual HRESULT STDMETHODCALLTYPE GetRelatedProcess(IN KSCLSID* pCLSIDs, IN int nCLSIDNum, IN OUT DWORD* pdwPIDs, IN OUT int* pnPIDNum
		) = 0;

	//NotifyComponentUpdateָ֪ͨ��������˳�
	//Return:
	//	S_OK ָ��������˳���ռ�õ��ļ�
	//  S_FALSE ��Ҫ�˳�ָ����������˳���ռ�õ��ļ�
	//	E_PENDING ������Ա�δ֪ģ�������ã������Ŀǰ�޷�ж��
	//	E_FAIL ʧ��
	//Param:
	//	clsid�Ǳ������ļ�������(�������)
	//	pwsFileNameList�Ǳ������ļ����б�����ļ�������'|'�ָ�
	virtual HRESULT STDMETHODCALLTYPE NotifyComponentUpdate(IN KSCLSID clsid, IN DWORD dwDataType, IN const wchar_t* pwsFileNameList
		) = 0;

	//NotifyProcessQuitָ֪ͨ��PID�Ľ����˳�
	//Return:
	//	S_OK ��ָ֪ͨ������ID�Ľ����˳���ͨ���㲥��ʽ��
	//	E_PENDING ���֪ͨ���Ƿ������˳����ò�������ִ�У���Ҫ��������NotifyServiceQuit��������֪ͨ�����˳�
	//	E_FAIL ʧ��
	//Param:
	//	pdwPIDs�Ǳ�֪ͨ�˳��Ľ���ID�б��ӵ�֪ͨ�Ľ��̿��Բ���ѯ���û��������˳�
	//	nPIDNum���б������
	virtual HRESULT STDMETHODCALLTYPE NotifyProcessQuit(IN DWORD* pdwPIDs, IN int nPIDNum
		) = 0;
};