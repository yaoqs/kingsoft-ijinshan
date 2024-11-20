/** 
* @file     ikrescanspmanager.h
* @author   jiaoyafei
* @date     2010-11-11
* @brief    the interface for service provider manager
*/

#ifndef _I_KRESCAN_SP_MANAGER_H__
#define _I_KRESCAN_SP_MANAGER_H__


__declspec(selectany) GUID CLSID_CKRescanSP = 
{ 0xc21140f0, 0x3a5b, 0x4c1f, { 0xae, 0x69, 0x4d, 0x86, 0x2b, 0xf7, 0xbd, 0xe8 } };


struct IReScanCallback;

MIDL_INTERFACE("A4D908A6-9AD9-4557-97B4-76BCD7652FE5")
IKRescanSPManager
{
    /**
    * @brief    ��ʼ��Service Provider,�ɷ������������
    * @return   0 Ϊ�ɹ�, ����Ϊʧ��
    */
    virtual int __stdcall InitializeService(IReScanCallback* iRescanCallback) = 0;

    /**
    * @brief ����ʼ��Service Provider,�ɷ������������
    * @return 0 Ϊ�ɹ�, ����Ϊʧ��
    */
    virtual int __stdcall UninitializeService() = 0;

    /**
    * @brief ����Service Provider,�ɷ������������
    * @return 0 Ϊ�ɹ�, ����Ϊʧ��
    */
    virtual int __stdcall StartService() = 0;

    /**
    * @brief �ر�Service Provider,�ɷ������������
    * @return 0 Ϊ�ɹ�, ����Ϊʧ��
    */
    virtual int __stdcall StopService() = 0;
};

#endif //> _I_KRESCAN_SP_MANAGER_H__