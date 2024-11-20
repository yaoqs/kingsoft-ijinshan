//////////////////////////////////////////////////////////////////////
///		@file		ikxesystemservice.h
///		@author		luopeng
///		@date		2008-10-06 09:07:58
///
///		@brief		ϵͳ�����ServiceProvider
//////////////////////////////////////////////////////////////////////

#pragma once
#include "kxesystemservice_def.h"
#include "../include/idl.h"

/**
* @defgroup kxebase_system_service_provider KXEngine Architecture System Service Provider
* @{
*/

/**
* @brief ��ƽ̨�ṩ��ϵͳ��ط���
*/
class IKxESystemService
{
public:
    /**
    * @brief ֪ͨ���������
    * @return 0 �ɹ�,����Ϊʧ�ܴ�����
    */
    virtual int __stdcall Reboot(
        const KXE_NULL_PARAEMETER&, 
        KXE_NULL_PARAEMETER&
        ) = 0;

    /**
    * @brief ͨ��nFolder��ֵ��ȡ��Ӧ��·��
    * @param[in] nFolder ָ����Folderѡ��,�μ�MSDN��CSLIDL
    * @param[out] strFolderPath ��ȡ��ָ����FolderPath
    * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
    */
    virtual int __stdcall GetFolderPath(
        const int& nFolder,
        std::wstring& strFolderPath
        ) = 0;

    /**
    * @brief ��ȡ��������������
    * @param[out] listDriverInfo �õ����������Ƽ�������
    * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
    */
    virtual int __stdcall GetLogicalDrives(
        const KXE_NULL_PARAEMETER&, 
        std::vector<KXE_LOGIC_DRIVER_INFO>& listDriverInfo
        ) = 0;

    /**
    * @brief ����ָ����Ŀ¼��ȡ����Ŀ¼
    * @param[in] strParentPath ��Ҫ��ȡ��Ŀ¼��·��
    * @param[out] vecChildPath �õ�����Ŀ¼����,��ȫ·��
    * @return 0 �ɹ�,����Ϊʧ�ܴ�����
    */
    virtual int __stdcall GetChildPath(
        const std::wstring& strParentPath,
        std::vector<std::wstring>& vecChildPath
        ) = 0;

    /**
    * @brief ���������û�Ȩ�޴�������
    * @param[in] strCommandLine ��Ҫ�����Ľ���ȫ·������������
    * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
    */
    virtual int __stdcall CreateProcess(
        const std::wstring& strCommandLine,
        KXE_NULL_PARAEMETER&
        ) = 0;

    /**
    * @brief �رռ����
    * @return 0 �ɹ�,����Ϊʧ�ܴ�����
    */
    virtual int __stdcall ShutDown(
        const KXE_NULL_PARAEMETER&, 
        KXE_NULL_PARAEMETER&
        ) = 0;
};

KXE_RCF_BEGIN(IKxESystemService, "KxESystemService")
    KXE_RCF_METHOD(Reboot, KXE_NULL_PARAEMETER, KXE_NULL_PARAEMETER)
    KXE_RCF_METHOD(GetFolderPath, int, std::wstring)
    KXE_RCF_METHOD(GetLogicalDrives, KXE_NULL_PARAEMETER, std::vector<KXE_LOGIC_DRIVER_INFO> )
	KXE_RCF_METHOD(GetChildPath, std::wstring, std::vector<std::wstring>)
	KXE_RCF_METHOD(CreateProcess, std::wstring, KXE_NULL_PARAEMETER)
    KXE_RCF_METHOD(ShutDown, KXE_NULL_PARAEMETER, KXE_NULL_PARAEMETER)
KXE_RCF_END()

/**
 * @}
 */