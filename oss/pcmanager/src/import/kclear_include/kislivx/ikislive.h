// ikislive �ӿڡ�

#pragma once
#ifndef __UPLIVE_COM_IKISLIVE_H__
#define __UPLIVE_COM_IKISLIVE_H__
#include "uplive_common.h"

#include "kisco.h"
#include "ikuplivecallback.h"

//{A2B79F67-A177-458f-9015-C2B8C0E654BC}
#if _MSC_VER <= 1200 // vc6.0
interface __declspec(uuid("A2B79F67-A177-458f-9015-C2B8C0E654BC"))
#else
[
    uuid("A2B79F67-A177-458f-9015-C2B8C0E654BC")
]
interface
#endif
IKislive 
	: public KISUP::Kis::IKisCoObjectT<IKislive>
{
	/*
	@ FuncName	: CheckKislive
	@ Param		: lpszCheck ������ݿ顣
	@ Param		: pExVerInfo ����kislivx.dll�汾��չ��Ϣ��
	@ Brief		: ���Kislive�Ƿ���á�
	*/
	virtual STDMETHODIMP CheckKislive(IN LPCWSTR lpszCheck, OUT KExVerInfo* pExVerInfo, OUT KExReserve* pReserve = NULL) = 0;
	/*
	@ FuncName	: InitKislive
	@ Param		: lpStrAppCmdlive ���������в�����
	@ Brief		: ��ʼ��Kislive��
	*/
	virtual STDMETHODIMP InitKislive(IN LPCWSTR lpStrAppCmdlive) = 0;
	/*
	@ FuncName	: UnInitKislive
	@ Brief		: ����ʼ��Kislive��
	*/
	virtual STDMETHODIMP UnInitKislive(void) = 0;
	/*
	@ FuncName	: CfgCallBack
	@ Param		: pIKUpliveCallBack �ص��ӿڡ�
	@ Brief		: ����IKUpliveCallBack�ص���
	*/
	virtual STDMETHODIMP CfgCallBack(IN IKUpliveCallBack * pIKUpliveCallBack) = 0;
	/*
	@ FuncName	: CfgKisliveParam
	@ Param		: lpStrDataParam ���ݲ�����
	@ Brief		: ����Kislive�ڲ�����������ExeҪ�ı�kislive.dll������ӿڡ�
	*/
	virtual STDMETHODIMP CfgKisliveParam(IN LPCWSTR lpStrDataParam) = 0;
	/*
	@ FuncName	: LoadKisliveDataToUI
	@ Brief		: ��Kislive�м������ݵ�UI���棬����ͨ�����ݻص��ӿ�OnKisDataEvent���ء�
	*/
	virtual STDMETHODIMP LoadKisliveDataToUI(void) = 0;
	/*
	@ FuncName	: AnalyzeIndex
	@ Brief		: ����Index�ļ�������������������������������������
	*/
	virtual STDMETHODIMP AnalyzeIndex(void) = 0;
	/*
	@ FuncName	: DownloadFiles
	@ Brief		: �����ļ������������������������ļ������Ǿ�������������ͬ��������ȣ���
	*/
	virtual STDMETHODIMP DownloadFiles(void) = 0;
	/*
	@ FuncName	: UpdateFiles
	@ Brief		: �����ļ���XXX����
	*/
	virtual STDMETHODIMP UpdateFiles(void) = 0;
	/*
	@ FuncName	: ReUpdateFiles
	@ Param		: bShowWnd ��ʾUI�Ƿ�����ʾ����
	@ Brief		: ���¸����ļ���
	*/
	virtual STDMETHODIMP ReUpdateFiles(IN BOOL bShowWnd) = 0;
	/*
	@ FuncName	: ReUpdateActiveUIWnds
	@ Brief		: ���¸���ʱ������ռ���ļ���UI���̡�
	*/
	virtual STDMETHODIMP ReUpdateActiveUIWnds(void) = 0;
	/*
	@ FuncName	: CheckLanUpdateDir
	@ Param		: lpStrLanUpdateDir �����������������ڵ�Ŀ¼��
	@ Brief		: ������������Ŀ¼��������������S_OK��
	*/
	virtual STDMETHODIMP CheckLanUpdateDir(IN LPCWSTR lpStrLanUpdateDir) = 0;
	/*
	@ FuncName	: MakeOfflinePackage
	@ Param		: lpStrPackageDir ��Ҫ�������������������Ŀ¼��
	@ Brief		: �����������������ɹ�����S_OK��
	*/
	virtual STDMETHODIMP MakeOfflinePackage(IN LPCWSTR lpStrPackageDir) = 0;
	/*
	@ FuncName	: CfgOemInfo
	@ Param		: uOemInfoId Oem��Ϣid�š�
	@ Brief		: ����oem��Ϣ��
	*/
	virtual STDMETHODIMP CfgOemInfo(IN u_int uOemInfoId, IN int nOemInfo) = 0;
	/*
	@ FuncName	: CfgOemInfo
	@ Param		: uOemInfoId Oem��Ϣid�š�
	@ Brief		: ����oem��Ϣ��
	*/
	virtual STDMETHODIMP CfgOemInfo(IN u_int uOemInfoId, IN LPCWSTR lpszOemInfo) = 0;
};

#endif //__UPLIVE_COM_IKISLIVE_H__

