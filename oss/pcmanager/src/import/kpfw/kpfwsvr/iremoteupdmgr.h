#pragma once

#include "SCOM/SCOM/SCOMBase.h"
#include "KisRpc/Rfcdef.h"
#include "wtypes.h"
#include <vector>
using namespace std;

//IRemote��ͷ�Ľӿڱ�ʾ��RPC�ӿ�
interface IRemoteUpdMgr
{
	//StartUpdCtrl֪ͨ�����������
	//Return:
	//	S_OK 
	//	E_FAIL 
	//Param:
	//	clsid�����������ID
	virtual HRESULT STDMETHODCALLTYPE StartUpdProcess(DWORD dwType
		) = 0;

	//QuitServiceProcess֪ͨ�����˳�
	virtual void STDMETHODCALLTYPE QuitServiceProcess(
		) = 0;

	//GetServiceProcessId�õ��������ID����������Wait����ȷ�Ϸ����Ƿ��Ѿ��˳�
	//Return:
	//	S_OK �ɹ�ȡ�÷�����̵�PID
	virtual HRESULT STDMETHODCALLTYPE GetServiceProcessId(IN OUT DWORD* pdwPID
		) = 0;

	//LockCreate֪ͨ������������Ĵ���������������ʱ�������ṩ�ߵ�������ܱ������������ڵģӣãϣͿ��ԣ�
	//Return:
	//	S_OK �ɹ�
	virtual HRESULT STDMETHODCALLTYPE LockCreate(
		) = 0;

	//UnlockCreate֪ͨ����������������UnlockCreate���Զ��ٵ���ÿ�������CompleteUpdate֪ͨ����������Ѿ����
	//Return:
	//	S_OK �ɹ�
	virtual HRESULT STDMETHODCALLTYPE UnlockCreate(
		) = 0;


	//GetRelatedProcess���ݷ����ڱ���ĵ��ù�ϵ������������clsids�Ľ�����̵��б�������ʾ�û�������¼
	//Return:
	//	S_OK �ɹ�ȡ�������б�
	//  E_FAIL ʧ��
	virtual HRESULT STDMETHODCALLTYPE GetRelatedProcess(IN vector<KSCLSID> clsids, IN OUT vector<DWORD>* pdwPIDs
		) = 0;

	//NotifyComponentUpdateָ֪ͨ��������˳�
	//Return:
	//	S_OK ָ��������˳���ռ�õ��ļ�
	//  S_FALSE ��Ҫ�˳�ָ����������˳���ռ�õ��ļ�
	//	E_PENDING ������Ա�δ֪ģ�������ã������Ŀǰ�޷�ж��
	//	E_FAIL ʧ��
	//Param:
	//	clsid�Ǳ������ļ�������(�������)
	//	fileNameList�Ǳ������ļ����б�
	virtual HRESULT STDMETHODCALLTYPE NotifyComponentUpdate(IN KSCLSID clsid, IN DWORD dwDataType, IN vector<wstring> fileNameList
		) = 0;

	//NotifyProcessQuitָ֪ͨ��PID�Ľ����˳�
	//Return:
	//	S_OK ��ָ֪ͨ������ID�Ľ����˳���ͨ���㲥��ʽ��
	//	E_PENDING ���֪ͨ���Ƿ������˳����ò�������ִ�У���Ҫ��������NotifyServiceQuit��������֪ͨ�����˳�
	//	E_FAIL ʧ��
	//Param:
	//	pdwPIDs�Ǳ�֪ͨ�˳��Ľ���ID�б��ӵ�֪ͨ�Ľ��̿��Բ���ѯ���û��������˳�
	//	nPIDNum���б������
	virtual HRESULT STDMETHODCALLTYPE NotifyProcessQuit(IN vector<DWORD> pids
		) = 0;

};

//RPC�ӿڶ���
RCF_CLASS_BEGIN_WITH_COM(IRemoteUpdMgr)
RCF_METHOD_R_1(HRESULT, StartUpdProcess, DWORD)
RCF_METHOD_V_0(QuitServiceProcess)
RCF_METHOD_R_1(HRESULT, GetServiceProcessId, DWORD*)
RCF_METHOD_R_0(HRESULT, LockCreate)
RCF_METHOD_R_0(HRESULT, UnlockCreate)
RCF_METHOD_R_2(HRESULT, GetRelatedProcess, vector<KSCLSID>, vector<DWORD>*)
RCF_METHOD_R_3(HRESULT, NotifyComponentUpdate, KSCLSID, DWORD, vector<wstring>)
RCF_METHOD_R_1(HRESULT, NotifyProcessQuit, vector<DWORD>)
RCF_CLASS_END
