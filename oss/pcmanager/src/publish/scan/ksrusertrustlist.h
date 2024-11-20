//////////////////////////////////////////////////////////////////////
//  @ File		KSRTrustList.h
//  @ version	1.0
//  @ Author	�����<liangguangcai@kingsoft.com>
//  @ Date		[2010-3-16, 14:43:44]
//  @ Brief		ϵͳ�޸��û����õ������б�
//					
//  @ Last changed
//    *Who		
//    *When		
//    *What		
//////////////////////////////////////////////////////////////////////

#pragma once

//	�û������б������ļ���
#define USER_TRUST_LIST_INI_FILE_NAME_W			L"tl.dat"
//	Url �����б�
#define USER_TRUST_LIST_URL_SECTION_NAME_W		L"UrlList"
//	�ļ������б�
#define USER_TRUST_LIST_FILE_SECTION_NAME_W		L"FileList"
//	ע���·�������б�
#define USER_TRUST_LIST_REG_SECTION_NAME_W		L"RegList"
//	ϵͳ�޸��ű� UUID �����б�
#define USER_TRUST_LIST_SCRIPT_SECTION_NAME_W	L"ScriptList"

typedef enum _EM_TRUST_ITEM_TYPE
{
	enum_TRUST_ITEM_TYPE_INVALID	= 0,	///< ��Ч����
	enum_TRUST_ITEM_TYPE_URL		= 1,	///< ���� Url
	enum_TRUST_ITEM_TYPE_FILE		= 2,	///< �����ļ�
	enum_TRUST_ITEM_TYPE_REG		= 3,	///< ����ע���·��
	enum_TRUST_ITEM_TYPE_SCRIPT		= 4		///< ���νű� UUID
} EM_TRUST_ITEM_TYPE;

typedef enum _EM_SPECIAL_ACTION_TYPE
{
	enum_SPECIAL_ACTION_TYPE_REFRESH_DESKTOP	= 1,	///< ˢ������
	enum_SPECIAL_ACTION_TYPE_REBOOT				= 2		///< ��������
} EM_SPECIAL_ACTION_TYPE;

