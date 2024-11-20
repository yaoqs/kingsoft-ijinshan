/**
* @file    ISoftChecker.h
* @brief   ��������װж����Ϣ
* @author  liveck
* @date    2010/04/07 21:50
*/

#pragma once
#include "ISoftManager.h"
/**
return:
	0 continue, no acttion
	1 stop
*/
typedef int (*InsCheckCallBack)(CString id, CString name, CString ver, CString curver, CString published, CString filename, void* param);



/**
return:
	0 continue, no acttion
	1 stop
*/

// key  --  ע������
// disp_icon -- ���ͼ��
// loc  -- λ��  ������ǿ����ɨ��
// uni_cmd ж������
typedef int (*UniCheckCallBack)(CString key,CString name,CString disp_icon,CString loc,CString uni_cmd,CString parent,void* param);

typedef int (*UniCheckCallBackEx)(void* mp,void* param);

//�����ص�
typedef int  (__stdcall *pfnUpdateCheckCallBack)(void* mp, void* param);


/**
return:
	0 continue, no acttion
	1 stop
	2 delete to recycler
	3 really delete

*/
typedef int (*PowerSweepCallBack)(CString type,CString path,void* param);
typedef bool (*PowerSweepFilterCallBack)(const LPCTSTR lpszFolder, PVOID param);

class __declspec(uuid("C431B499-65C1-4bc3-A91C-1EA2927DB7E2"))  ISoftChecker
{
public:
	///���������Ѱ�װ���е����
	virtual int CheckAllInstalled(InsCheckCallBack func,void* para) = 0;

	///����ض�������Ƿ�װ
	virtual int CheckOneInstalled(CString id,InsCheckCallBack func,void* para)= 0;

	///���ж����  --- ���key�б�
	virtual int CheckAll2Uninstall(UniCheckCallBack func,void* para)= 0;

	///���ָ����ж�����Ƿ����   -1 -- ������  0 -- ��ж����
	virtual int CheckOne2Uninstall(CString key,UniCheckCallBack func,void* para)= 0;

	///����ж��  
	virtual int Uninstall(CString cmd)=0;

	///��key��ȡ�����id����ȡid֮�����ͨ��manager�õ��꾡����Ϣ
	virtual const wchar_t* FindUninstallId(CString key)=0;
	///��display_name��ȡ�����id����ȡid֮�����ͨ��manager�õ��꾡����Ϣ
	virtual const wchar_t* FindUninstallIdByName( CString name ) = 0;

	///��װ����ж����ȣ����ȴ��ӽ���
	virtual int Install(CString cmd)=0;

	///ǿ����ɨ -1 -- ������ɨ  0 -- ����ɨ��   1  -- ȡ��
	virtual int PowerSweep(CString key,CString loc,PowerSweepCallBack func, void* para, PowerSweepFilterCallBack fnFilter)=0;


	///���ڲ�������
	virtual int Combine(CString diff_file)=0;

	///���ؿ⣬�������޸�ʱ�䣬�����ͬ��˵���б仯�������¼��أ�����ֱ�ӷ���
	virtual int Load(CString lib_file="",bool reload=true)=0;

	virtual size_t GetSoftCount()=0;
};

class __declspec(uuid("917CB47F-8493-4186-B37D-5639E9E2C23B"))  ISoftCheckerEx:public ISoftChecker
{
public:
	//ȡ�����е�ж������Ϣ
	/*
	k �Ǽ�
	name ��ж��������
	ico ��display icon
	loc �ǰ�װ·��
	pr ��parent
	py_ ƴ��
	pq_ ƴ��
	si �Ǵ�С ��λ���ֽ�
	lastuse ���ʹ��ʱ��
	stat ��װ״̬ �� �Ѱ�װ
	������ͬ�����Ϣ
	
	*/
	virtual int CheckAll2Uninstall(UniCheckCallBackEx func,GetInfoCallback cbfun,void* mp,void* para) = 0;

	//���ĳ���Ƿ����
	virtual int CheckOne2Uninstall(CString key ,UniCheckCallBackEx func,GetInfoCallback cbfun,void* mp,void* para) = 0;

	//����
	virtual void* SearchUninstallItem(CString word) = 0;
	//��ȡ������������ص�������
	virtual wchar_t* GetNextItem(void* pos) = 0;
	//����֮�����������
	virtual void FinalizeGet(void* pos) = 0;
	//����ж����Ϣ��
	virtual int LoadUnInfo(CString lib_file) = 0;

	//�ͷ�ж����Ϣ��
	virtual int FreeUnInfo() = 0; 
	//����ж����Ϣ��ĺϲ�
	virtual int Combine_UniInfo( CString diff_file ) = 0;

	//��ʼ�˵����������������棬���̣�������ݲ�֧�֣���������ͼ������
	enum SoftType {STARTMENU=0,QUICKLAUNCH,DESKTOP,PS_MODULE,STARTUP,NOTIFY_ICON};

	//���ݲ�ͬ����ȡ��ж����Ϣ
	virtual int CheckAll2UninstallByType(SoftType tp,UniCheckCallBackEx func,GetInfoCallback cbfun,void* mp,void* para) = 0;

	//�����ݷ�ʽ �� loc : loc ��װ·��
	virtual int RemoveLnk(SoftType tp,CString loc,PowerSweepCallBack func,void* para) = 0;

	//��������� : loc -> path ����·��
	/*
	����ڻص���û��ɾ������¼��������
	*/
	virtual int RemoveRemainds(CString name,CString ins_loc,CString type,CString loc,PowerSweepCallBack func,void* para) = 0;

	//���������С
	virtual __int64 CountSize(CString loc) = 0;

	//������еĲ������
	/*
	type ���� ע��� �ļ� Ŀ¼
	path �����·��
	loc		�����İ�װĿ¼
	name 
	*/
	virtual int CheckAll2Remains(UniCheckCallBackEx func,GetInfoCallback cbfun,void* mp,void* para) = 0;

	//����ȡ�ò�����
	/*
	*/

	virtual int CheckAll2RemainsByGroup(UniCheckCallBackEx func,GetInfoCallback cbfun,void* mp,void* para) =0;

	virtual int CheckAll2RemainsByNameAndLoc(CString name,CString loc,UniCheckCallBackEx func,GetInfoCallback cbfun,void* mp,void* para) =0;



	//�ӻ�����ȡ����Ϣ
	virtual int CheckAll2UninstallCache(UniCheckCallBackEx func,GetInfoCallback cbfun,void* mp,void* para) = 0;
	//��������
	virtual int MakeAll2UninstallCache()	=	0;

	//����ƴ����
	virtual int LoadFonts(CString strFile) = 0;

	//��ȡ��������
	virtual int GetUpdateFromCache(pfnUpdateCheckCallBack pfnCallBack, GetInfoCallback cbfun, void* mp, void* para) = 0;

	//������������, ���������첽��⴦��, ����Ͳ������첽������, ���ṹ����
	virtual int MakeUpdateCache() = 0;

};