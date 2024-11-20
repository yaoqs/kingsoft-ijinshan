/**
* @file    ksafesdk_def.h
* @brief   ...
* @author  bbcallen
* @date    2010-08-06 11:34
*/

#ifndef KSAFESDK_DEF_H
#define KSAFESDK_DEF_H

#pragma pack(push,1)


#define KSAFE_S_M_ASYNC         0x00000001      ///< �첽ɨ��


// ɨ����
enum KSAFE_RESULT
{
    KSAFE_S_R_UNKNOWN           = 0,        ///< δ֪�ļ�(�޷��ж�Ϊ��ȫ���ļ�)
    KSAFE_S_R_PENDING           = 1,        ///< �����첽ģʽ(��δ����)
    KSAFE_S_R_ERROR             = 2,        ///< ��������

    KSAFE_S_R_SAFE              = 100,      ///< ��ȫ���ļ�
    KSAFE_S_R_TRUST             = 101,      ///< ���ε��ļ�

    KSAFE_S_R_DETECTED          = 1000,     ///< �����ǲ���

    // �������ʱ,�п��ܷ�������Ľ��
    KSAFE_S_R_DISINFECTED       = 2001,     ///< ���޸�
    KSAFE_S_R_DELETED           = 2002,     ///< ��ɾ��
    KSAFE_S_R_FAILED_TO_CLEAN   = 2003,     ///< ���ʧ��
};



// �ص�����ֵ
enum KSAFE_CALLBACK_RET
{
    KSAFE_CLBK_OK = 0,                  ///< �ݲ�֧�������Ļص�����ֵ
};



// �ص��¼�
enum KSAFE_EVENT
{
    KSAFE_EVT_OK            = 0,        ///<    ��ȫ�ļ�

    KSAFE_EVT_INPROGRESS    = 1,        ///<    ɨ�������
                                        ///<    dwParam1        ������
                                        ///<    dwParam2        ������
                                        ///<    pObjectName     �ļ���
                                        ///<    pVirusName      ������

    KSAFE_EVT_RESULT        = 101,      ///<    ɨ�����,���ؽ��
                                        ///<    dwParam1        ����Ϊ KSAFE_RESULT
                                        ///<    dwParam2        ������
                                        ///<    pObjectName     �ļ���
                                        ///<    pVirusName      ������

    KSAFE_EVT_ERROR         = 65536,    ///<    ɨ�跢������
};



// �ص�����
typedef KSAFE_CALLBACK_RET (__cdecl *PFN_ksafeCallbackW) (
    KSAFE_EVENT     Event,
    unsigned long   dwParam1,
    unsigned long   dwParam2,
    const wchar_t*  pObjectName,
    const wchar_t*  pVirusName,
    void*           pUserContext);

#pragma pack(pop)

#endif//KSAFESDK_DEF_H