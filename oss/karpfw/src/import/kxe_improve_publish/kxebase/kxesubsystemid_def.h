//////////////////////////////////////////////////////////////////////
///		@file		kxesubsystemid_def.h
///		@author		luopeng
///		@date		2008-9-10 09:07:58
///
///		@brief		������ϵͳID����
//////////////////////////////////////////////////////////////////////

#pragma once

/// ������ϵͳ����ö����,��ֵ���Ϊ0xffff
typedef enum _KXE_SUB_SYSTEM_ID
{
	enum_SubSystem_Base = 0,  ///< ������ϵͳ
	enum_SubSystem_Scan,      ///< ɨ����ϵͳ
	enum_SubSystem_FileMon,   ///< �ļ������ϵͳ
	enum_SubSystem_Popo,      ///< ������ϵͳ
	enum_SubSystem_White,     ///< ��������ϵͳ
	enum_SubSystem_Update,    ///< ������ϵͳ
    enum_SubSystem_Defend     ///< ����������ϵͳ
} KXE_SUB_SYSTEM_ID;
