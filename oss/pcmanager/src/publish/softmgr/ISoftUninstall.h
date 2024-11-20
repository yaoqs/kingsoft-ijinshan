#pragma once

namespace ksm
{

//
// ж���¼�
//
enum UninstEvent : LONG
{
	UE_Unknown = 0,
	UE_Update,					// ����
	UE_Add,						// ���
	UE_Delete,					// ɾ��
	UE_Modify,					// �޸�

	UE_Data_Loaded,				// �����Ѽ���
	UE_Data_Failed,				// ���ݼ���ʧ��
	UE_Data_Completed,			// ���ݼ������

	UE_Invoke_Uninst,			// ���ñ�׼ж�س���
	UE_Invoke_Failed,			// ���ñ�׼ж�س���ʧ��
	UE_Invoke_Succeeded,		// ���ñ�׼ж�س���ɹ�
	UE_Invoke_Canceled,			// �û�ȡ��ִ�б�׼ж�س���
	UE_Enum_Multi,				// ���ֶ������װ��ͬһĿ¼
	UE_Enum_End,				// ����ö�ٽ���
	UE_Sweeping,				// ��ɨ��...
	UE_Sweep_Failed,			// ж���г��ִ���

	UE_Sweep_Begin,				// ��ɨ��ʼ
	UE_Sweep_End,				// ��ɨ����
	UE_Refresh_Begin,			// ˢ�¿�ʼ
	UE_Refresh_End,				// ˢ�½���

	UE_Enum_Too_Much,			// ������̫��
};

//
// �����������
//
enum SoftDataMask : ULONG
{
	SDM_None			= (0<<0),
	SDM_Key				= (1<<0),
	SDM_Main_Path		= (1<<1),
	SDM_Description		= (1<<2),
	SDM_Info_Url		= (1<<3),
	SDM_PinYin			= (1<<4),
	SDM_Size			= (1<<5),
	SDM_LastUse			= (1<<6),
	SDM_Type			= (1<<7),
	SDM_Count			= (1<<8),
	SDM_All				= (0xFFFFFFFF),
};

//
// �������
//
typedef struct SoftData
{
	ULONG			_mask;

	LPCWSTR			_pcKey;			// keyword
	LPCWSTR			_pcDisplayName;
	LPCWSTR			_pcMainPath;	// ����Ϊ��
	LPCWSTR			_pcDescript;	// ����Ϊ��
	LPCWSTR			_pcInfoUrl;		// ����Ϊ��
	LPCWSTR			_pcSpellWhole;	// ����Ϊ��
	LPCWSTR			_pcSpellAcronym;// ����Ϊ��
	LPCWSTR			_pcIconLocation;// ����Ϊ��
	LPCWSTR			_pcLogoUrl;		// ����Ϊ��
	ULONGLONG		_size;			// ����Ϊ0
	LONG			_lastUse;		// ����Ϊ0
	LONG			_id;
	LONG			_type;
	LONG			_count;
} *PSoftData;
typedef const SoftData* PCSoftData;

//
// ��Ŀ����
//
enum SoftItemAttri : ULONG
{
	SIA_Unknown			= (0<<0),
	SIA_File			= (1<<0),
	SIA_Link			= (1<<1),
	SIA_Directory		= (1<<2),
	SIA_Registry		= (1<<3),
	SIA_Start			= (1<<4),
	SIA_Quick			= (1<<5),
	SIA_Desktop			= (1<<6),
	SIA_Process			= (1<<7),
	SIA_Tray			= (1<<8),
};

//
// ���������
//
typedef struct SoftRubbish
{
	SoftItemAttri	_type;	// ��ʼ�����١����桢ע���
	LPCWSTR			_pData;
} *PSoftRubbish;
typedef const SoftRubbish* PCSoftRubbish;

//
// �������ö�ٽӿ�
//
class ISoftDataEnum
{
public:
	virtual BOOL __stdcall EnumFirst(PSoftData pData) = 0;
	virtual BOOL __stdcall EnumNext(PSoftData pData) = 0;
};

//
// �������ö�ٽӿ�
//
class ISoftLinkEnum
{
public:
	virtual BOOL __stdcall EnumFirst(LPCWSTR *pKey) = 0;
	virtual BOOL __stdcall EnumNext(LPCWSTR *pKey) = 0;
};

//
// ���������ö�ٽӿ�
//
class ISoftRubbishEnum
{
public:
	virtual BOOL __stdcall EnumFirst(PSoftRubbish pData) = 0;
	virtual BOOL __stdcall EnumNext(PSoftRubbish pData) = 0;
};

//
// ���ж�ؽӿ�
//
class ISoftDataSweep
{
public:
	virtual void __stdcall Uninitialize() = 0;
	virtual LPCWSTR __stdcall GetKey() = 0;

	virtual ISoftRubbishEnum* __stdcall DataUninstEnum() = 0;
	virtual ISoftRubbishEnum* __stdcall DataSweepingEnum() = 0;

	virtual BOOL __stdcall DataSetSweep(PCSoftRubbish pcData) = 0;
	virtual BOOL __stdcall DataSweep(BOOL recycle) = 0;
	virtual BOOL __stdcall DataSoftExists() = 0;
	virtual BOOL __stdcall DataCancelUninst(LPCWSTR pKey) = 0;

	virtual LPCWSTR __stdcall GetMainDir() = 0;
};

class ISoftDataSweep2 : public ISoftDataSweep
{
public:
	virtual ULONGLONG __stdcall GetRubbishSize() = 0;
};

//
// ��������ɨ�ӿ�
//
class ISoftRubbishSweep
{
public:
	virtual void __stdcall Uninitialize() = 0;
	
	virtual ISoftRubbishEnum* __stdcall RubbishSweepingEnum() = 0;

	virtual BOOL __stdcall RubbishSetSweep(PCSoftRubbish pcData) = 0;
	virtual BOOL __stdcall RubbishSweep(BOOL recycle) = 0;
	virtual BOOL __stdcall RubbishCancelSweep() = 0;
};

//
// ���ж�ػص��ӿ�
//
class ISoftUnincallNotify
{
public:
	// ��������¼�
	virtual void __stdcall SoftDataEvent(UninstEvent event, ISoftDataEnum *pEnum) = 0;
	// ���ж���¼�
	virtual void __stdcall SoftDataSweepEvent(UninstEvent event, ISoftDataSweep *pSweep) = 0;

	// ��ݷ�ʽ�����¼�
	virtual void __stdcall SoftLinkEvent(UninstEvent event, SoftItemAttri type, ISoftLinkEnum *pData) = 0;

	// �������¼�
	virtual void __stdcall SoftRubbishEvent(UninstEvent event, ISoftRubbishEnum *pEnum) = 0;
	// ��������ɨ�¼�
	virtual void __stdcall SoftRubbishSweepEvent(UninstEvent event, ISoftRubbishSweep *pSweep) = 0;
};

//
// ���ж�ؽӿ�
//
class __declspec(uuid("F3E296D1-40AD-4ad1-B109-B8C993920D25")) ISoftUninstall
{
public:
	virtual void __stdcall SetNotify(ISoftUnincallNotify *pNotify) = 0;
	virtual BOOL __stdcall Initialize(LPCWSTR pKSafePath) = 0;
	virtual void __stdcall Uninitialize() = 0;

	//
	// ���ˢ�²���
	//
	//@Remark
	// 1.ǿ��ˢ�£���ͬ��
	// �첽�������ؽ�����
	// 2.��ǿ��ˢ�£���ͬ��
	// ͬ��������ֱ�Ӷ�ȡ��������
	//
	virtual BOOL __stdcall DataRefresh(BOOL force) = 0;
	virtual ISoftDataSweep* __stdcall DataSweep(LPCWSTR pKey) = 0;

	//
	// ��ݷ�ʽ����
	//
	// ɨ�����桢��������������ʼ�˵�������Լ�����
	virtual BOOL __stdcall LinkRefresh(SoftItemAttri type, BOOL force) = 0;

	//
	// ���������
	//
	virtual BOOL __stdcall RubbishRefresh() = 0;
	virtual ISoftRubbishSweep* __stdcall RubbishSweep() = 0;
};

class __declspec(uuid("0A7E1A75-3BC8-4872-BADA-21224D60020D")) ISoftUninstall2 : public ISoftUninstall
{
public:
	virtual ISoftDataSweep2* __stdcall DataSweep2(LPCWSTR pKey) = 0;
};

}