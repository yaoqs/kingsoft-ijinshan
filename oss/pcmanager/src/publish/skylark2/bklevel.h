/**
* @file    bklevel.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-16 21:29
*/

#ifndef BKLEVEL_H
#define BKLEVEL_H

#include "skylarkbase.h"

NS_SKYLARK_BEGIN

//////////////////////////////////////////////////////////////////////////
// Level �ļ���

#define SLPTL_LEVEL_GROUP__MIN                                  0       ///< ...
#define SLPTL_LEVEL_GROUP__SERVER_MIN                           0       ///< ...

// �ϱ�(������)
#define SLPTL_LEVEL_GROUP__UPLOAD_MIN                           0       ///< ...
#define SLPTL_LEVEL_MARK___RESERVED                             0       ///< ����
#define SLPTL_LEVEL_MARK___UNRECOGNISED_SYSTEM                  1       ///< δ�ϴ�����ϵͳǩ��
#define SLPTL_LEVEL_MARK___UNRECOGNISED_PROCESS                 2       ///< δ�ϴ����Ľ���ǩ��
#define SLPTL_LEVEL_MARK___UNRECOGNISED_FILE                    3       ///< δ�ϴ������ļ�ǩ��
#define SLPTL_LEVEL_GROUP__UPLOAD_MAX                           49      ///< ...

// ������
#define SLPTL_LEVEL_GROUP__BLACK_MIN                            50      ///< ...

#define SLPTL_LEVEL_GROUP__BLACK_AUTO_MIN                       50      ///< �Զ��кڵķ���
#define SLPTL_LEVEL_MARK___BLACK_AUTO                           50      ///< ����(δ�жϸ�Ⱦ��)
#define SLPTL_LEVEL_MARK___BLACK_AUTO_NON_INFECTED              51      ///< �Ǹ�Ⱦ��
#define SLPTL_LEVEL_MARK___BLACK_AUTO_INFECTED                  52      ///< ��Ⱦ��
#define SLPTL_LEVEL_GROUP__BLACK_AUTO_MAX                       59      

#define SLPTL_LEVEL_GROUP__BLACK_MANUAL_MIN                     60      ///< �ֶ��кڵķ���
#define SLPTL_LEVEL_MARK___BLACK_MANUAL_NON_INFECTED            61      ///< �Ǹ�Ⱦ��
#define SLPTL_LEVEL_MARK___BLACK_MANUAL_INFECTED                62      ///< ��Ⱦ��
#define SLPTL_LEVEL_GROUP__BLACK_MANUAL_MAX                     69

#define SLPTL_LEVEL_GROUP__BLACK_ABSOLUTELY_MIN                 70      ///< ���Ժڵķ���(����Ҫ��������ǩ��)
#define SLPTL_LEVEL_MARK___BLACK_ABSOLUTELY_NON_INFECTED        71      ///< �Ǹ�Ⱦ��
#define SLPTL_LEVEL_MARK___BLACK_ABSOLUTELY_INFECTED            72      ///< ��Ⱦ��
#define SLPTL_LEVEL_GROUP__BLACK_ABSOLUTELY_MAX                 79

#define SLPTL_LEVEL_GROUP__BLACK_HEURIST_MIN                    80      ///< �ƶ�����ʽ
#define SLPTL_LEVEL_MARK___BLACK_HEURIST_HIGH_RISK              80      ///< �߷���
#define SLPTL_LEVEL_MARK___BLACK_HEURIST_LOW_RISK               81      ///< �ͷ���
#define SLPTL_LEVEL_GROUP__BLACK_HEURIST_MAX                    89      ///<

#define SLPTL_LEVEL_GROUP__BLACK_MAX                            99      ///< ...

// ������
#define SLPTL_LEVEL_GROUP__GRAY_MIN                             100     ///< ...
#define SLPTL_LEVEL_GROUP__GRAY_UNTRUST_MIN                     100     ///< ...
#define SLPTL_LEVEL_MARK___NEVER_BEEN_SCANNED                   100     ///< δɨ����ļ�
#define SLPTL_LEVEL_MARK___SCANNED_ONCE_SUSPICIOUS              101     ///< ɨ���һ��,�����ɵ���ļ�
#define SLPTL_LEVEL_MARK___SCANNED_ONCE                         102     ///< ɨ���һ�ε��ļ�
#define SLPTL_LEVEL_MARK___SCANNED_MORE_THAN_ONCE               103     ///< ����ɨ������ε��ļ�
#define SLPTL_LEVEL_GROUP__GRAY_UNTRUST_MAX                     119     ///< ...

#define SLPTL_LEVEL_GROUP__GRAY_TRUST_MIN                       120     ///< ...
#define SLPTL_LEVEL_MARK___TEMP_FALSE_POSITIVE                  130     ///< ��ʱ��Ϊ���󱨵��ļ�
#define SLPTL_LEVEL_MARK___SCANNED_ENOUGH                       150     ///< ɨ�����㹻��ʱ����ļ�
#define SLPTL_LEVEL_MARK___WIN_TRUST__DEPRECATE                 160     ///< (����ʹ��)(����)����΢�����ε�����ǩ�����ļ�
#define SLPTL_LEVEL_MARK___WHITE_COEXIST                        168     ///< ��������ļ�������ͳ���ж�Ϊ����в���ļ�
#define SLPTL_LEVEL_GROUP__GRAY_TRUST_MAX                       169     ///< ...
#define SLPTL_LEVEL_GROUP__GRAY_MAX                             169     ///< ...

// ������
#define SLPTL_LEVEL_GROUP__TRUST_MIN                            170     ///< ...
#define SLPTL_LEVEL_MARK___MANUALLY_WHITE                       170     ///< �˹�����ȷ���������ļ�
#define SLPTL_LEVEL_MARK___MANUALLY_FALSE_POSITIVE              171     ///< �˹�����ȷ�����󱨵��ļ�
#define SLPTL_LEVEL_MARK___WHITE_SCANNED_ENOUGH                 172     ///< ɨ���㹻����,��Ϊ�����а�
#define SLPTL_LEVEL_MARK___DOWNLOADED_FROM_TRUSTED_WEBSITES     180     ///< �ӿ��ŵ�վ�����ص����
#define SLPTL_LEVEL_MARK___DOWNLOADED_FROM_OFFICIAL_WEBSITES    181     ///< �ӹٷ���վ���ص����
#define SLPTL_LEVEL_MARK___DISTRIBUTED_BY_MICROSOFT             182     ///< ΢�������ļ�
#define SLPTL_LEVEL_MARK___DISTRIBUTED_BY_COPARTNER             183     ///< ��������ύ���ļ�
#define SLPTL_LEVEL_MARK___DISTRIBUTED_BY_BEIKE_CORP            184     ///< ���Ƿ������ļ�
#define SLPTL_LEVEL_MARK___MANUALLY_TRUST                       185     ///< �˹�ȷ��Ϊ�������ļ�

// add by yangjun 2010.11.12 Ϊ������԰׻���ʱ���������
#define SLPTL_LEVEL_MARK___DUBA_TRUST_3DAY                      186     ///< ������Ϊ����Ҫ����3��
#define SLPTL_LEVEL_MARK___DUBA_TRUST_5DAY                      187     ///< ������Ϊ����Ҫ����5��
#define SLPTL_LEVEL_MARK___DUBA_TRUST_7DAY                      188     ///< ������Ϊ����Ҫ����7��
#define SLPTL_LEVEL_MARK___DUBA_TRUST_10DAY                     189     ///< ������Ϊ����Ҫ����10��
// add end

#define SLPTL_LEVEL_GROUP__TRUST_MAX                            199     ///< ...
#define SLPTL_LEVEL_GROUP                                               ///< ...

#define SLPTL_LEVEL_GROUP__SERVER_MAX                           199     ///< ...



// ����ʹ�õ�level
#define SLPTL_LEVEL_GROUP__LOCAL_MIN                            800     ///< ...

#define SLPTL_LEVEL_GROUP__LOCAL_WHITE_MIN                      800     ///< ...
#define SLPTL_LEVEL_MARK___LOCAL_WHITE_FILE_NAME                801     ///< ���ذ������ļ���
#define SLPTL_LEVEL_MARK___LOCAL_WIN_TRUST                      802     ///< ���ؿ��ŵ�����ǩ��
#define SLPTL_LEVEL_MARK___LOCAL_WIN_TRUST_FAKE_SYS             803     ///< ���ؿ��ŵ�����ǩ��,���ǰ׼��ڵ��кڲ���
#define SLPTL_LEVEL_MARK___LOCAL_WIN_TRUST_HEURIST              804     ///< ���ؿ��ŵ�����ǩ��,������ʽ�к�
#define SLPTL_LEVEL_MARK___LOCAL_WIN_TRUST_CLOUD_HIGH_RISK      805     ///< ���ؿ��ŵ�����ǩ��,���ƶ˱��߷���
#define SLPTL_LEVEL_MARK___LOCAL_WIN_TRUST_CLOUD_LOW_RISK       806     ///< ���ؿ��ŵ�����ǩ��,���ƶ˱��ͷ���
#define SLPTL_LEVEL_MARK___LOCAL_WIN_TRUST_BOTH_HEURIST         807     ///< ���ؿ��ŵ�����ǩ��,���ƶ������ͱ�������������
#define SLPTL_LEVEL_MARK___LOCAL_KSCLOUD_TRUST                  808     ///< �����ƿ���
#define SLPTL_LEVEL_GROUP__LOCAL_WHITE_MAX                      849     ///< ...


#define SLPTL_LEVEL_GROUP__LOCAL_BLACK_MIN                      850     ///< ...
#define SLPTL_LEVEL_MARK___LOCAL_INFECTED_DELPHI                860     ///< ����Ⱦ��delphi
#define SLPTL_LEVEL_MARK___LOCAL_HEURIST                        861     ///< ��������ʽ
#define SLPTL_LEVEL_MARK___LOCAL_AVENGINE                       862     ///< ����ɱ�����淢�ֵĲ���
#define SLPTL_LEVEL_MARK___LOCAL_AVP                            863     ///< ���ؿ������淢�ֵĲ���
#define SLPTL_LEVEL_MARK___LOCAL_FAKE_SYS_FILE                  864     ///< ���طǰ׼��ڵ��кڲ���
#define SLPTL_LEVEL_MARK___LOCAL_HEURIST_WITH_CLOUD_LOW_RISK    865     ///< �����������ƶ������ͷ���ͬʱ����
#define SLPTL_LEVEL_MARK___LOCAL_KSCLOUD_BLACK                  868     ///< ��������Ϊ�ǲ���
#define SLPTL_LEVEL_GROUP__LOCAL_BLACK_MAX                      899     ///< ...


// ���ش���
#define SLPTL_LEVEL_GROUP__LOCAL_ERROR_MIN                      900     ///< ...
#define SLPTL_LEVEL_MARK___LOCAL_RESERVED                       900     ///< ����
#define SLPTL_LEVEL_MARK___LOCAL_FAILED_TO_HASH_FILE            901     ///< �����ļ�hash��ʱ��������
#define SLPTL_LEVEL_MARK___LOCAL_FAILED_TO_QUERY_FILE           902     ///< ��ѯ�ļ�level��ʱ��������
#define SLPTL_LEVEL_MARK___LOCAL_FAILED_TO_HASH_PROCESS         903     ///< �������hash��ʱ��������
#define SLPTL_LEVEL_MARK___LOCAL_FAILED_TO_QUERY_PROCESS        904     ///< ��ѯ����hash��ʱ��������
#define SLPTL_LEVEL_MARK___LOCAL_FAILED_TO_HASH_SYSTEM          905     ///< ����ϵͳhash��ʱ��������
#define SLPTL_LEVEL_MARK___LOCAL_FAILED_TO_QUERY_SYSTEM         906     ///< ��ѯϵͳhash��ʱ��������
#define SLPTL_LEVEL_MARK___LOCAL_NON_PE_FILE                    910     ///< ��PE�ļ�
#define SLPTL_LEVEL_MARK___LOCAL_TOO_SMALL_FILE                 911     ///< �ļ�̫С
#define SLPTL_LEVEL_MARK___LOCAL_TOO_LARGE_FILE                 912     ///< �ļ�̫��
#define SLTPL_LEVEL_MARK___LOCAL_NON_EXE_FILE                   931     ///< ���ز���ִ�е��ļ�
#define SLPTL_LEVEL_GROUP__LOCAL_ERROR_MAX                      949     ///< ...

#define SLPTL_LEVEL_GROUP__LOCAL_GRAY_MIN                       950     ///< ...
#define SLPTL_LEVEL_MARK___LOCAL_FAKE_SYS_GRAY_TRUST            950     ///< ����sfmkb�Ŀ��Ż��ļ�
#define SLPTL_LEVEL_MARK___LOCAL_FAKE_SYS_GRAY_UNTRUST          975     ///< ����sfmkb�Ĳ����Ż��ļ�
#define SLPTL_LEVEL_MARK___LOCAL_NO_NEED_SRV_HEURIST_HIGH_RISK  976     ///< ���ز���Ҫ���ƶ��������(�߷���)
#define SLPTL_LEVEL_MARK___LOCAL_NO_NEED_SRV_HEURIST_LOW_RISK   977     ///< ���ز���Ҫ���ƶ��������(�ͷ���)
#define SLPTL_LEVEL_GROUP__LOCAL_GRAY_MAX                       999     ///< ...

#define SLPTL_LEVEL_GROUP__LOCAL_MAX                            999     ///< ...



#define SLPTL_LEVEL_GROUP__MAX                                  999     ///< ...



/// ������,����1Сʱ
inline BOOL SLLevelIsGray(DWORD dwLevel)
{
    return dwLevel >= SLPTL_LEVEL_GROUP__GRAY_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__GRAY_MAX;
}

///// �����ŵĻ���������Ҫ�ύ����������
//inline BOOL SLLevelIsGrayUnTrust(DWORD dwLevel)
//{
//    if (dwLevel >= SLPTL_LEVEL_GROUP__GRAY_UNTRUST_MIN &&
//        dwLevel <= SLPTL_LEVEL_GROUP__GRAY_UNTRUST_MAX)
//        return TRUE;
//
//    if (dwLevel == SLPTL_LEVEL_MARK___LOCAL_FAKE_SYS_GRAY_UNTRUST)
//        return TRUE;
//
//    return FALSE;
//}

/// ���ŵĻ����������ύ����������
inline BOOL SLLevelIsGrayTrust(DWORD dwLevel)
{
    if (dwLevel >= SLPTL_LEVEL_GROUP__GRAY_TRUST_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__GRAY_TRUST_MAX)
        return TRUE;

    if (dwLevel == SLPTL_LEVEL_MARK___LOCAL_FAKE_SYS_GRAY_TRUST)
        return TRUE;

    return FALSE;
}

/// �Զ������ĺ�����,��Ҫ��֤����ǩ��
inline BOOL SLLevelIsBlackAuto(DWORD dwLevel)
{
    if (dwLevel >= SLPTL_LEVEL_GROUP__BLACK_AUTO_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__BLACK_AUTO_MAX)
        return TRUE;

    if (dwLevel >= SLPTL_LEVEL_GROUP__BLACK_HEURIST_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__BLACK_HEURIST_MAX)
        return TRUE;

    if (dwLevel >= SLPTL_LEVEL_GROUP__LOCAL_BLACK_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__LOCAL_BLACK_MAX)
        return TRUE;

    return FALSE;
}

/// �ֶ������ĺ�����,��Ҫ��֤����ǩ��
inline BOOL SLLevelIsBlackManual(DWORD dwLevel)
{
    if (dwLevel >= SLPTL_LEVEL_GROUP__BLACK_MANUAL_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__BLACK_MANUAL_MAX)
        return TRUE;

    return FALSE;
}

/// ���Եĺ�����,����Ҫ��֤����ǩ��
inline BOOL SLLevelIsBlackAbsolutely(DWORD dwLevel)
{
    if (dwLevel >= SLPTL_LEVEL_GROUP__BLACK_ABSOLUTELY_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__BLACK_ABSOLUTELY_MAX)
        return TRUE;

    return FALSE;
}

/// ...
//inline BOOL SLLevelIsBlack(DWORD dwLevel)
//{
//    if (SLLevelIsBlackAuto(dwLevel))
//        return TRUE;
//
//    if (SLLevelIsBlackManual(dwLevel))
//        return TRUE;
//
//    return FALSE;
//}

/// ��֪Ҫ�����ĺ��ļ�
inline BOOL SLLevelIsBlackKnown(DWORD dwLevel)
{
    if (SLLevelIsBlackAuto(dwLevel))
        return TRUE;

    if (SLLevelIsBlackManual(dwLevel))
        return TRUE;

    if (SLLevelIsBlackAbsolutely(dwLevel))
        return TRUE;

    return FALSE;
}

/// ��֪�ĸ�Ⱦ��
inline BOOL SLLevelIsInfected(DWORD dwLevel)
{
    if (SLPTL_LEVEL_MARK___BLACK_AUTO_INFECTED == dwLevel)
        return TRUE;

    if (SLPTL_LEVEL_MARK___BLACK_MANUAL_INFECTED == dwLevel)
        return TRUE;

    if (SLPTL_LEVEL_MARK___BLACK_ABSOLUTELY_INFECTED == dwLevel)
        return TRUE;

    return FALSE;
}

/// �����εİ��ļ�
inline BOOL SLLevelIsTrusted(DWORD dwLevel)
{
    if (dwLevel >= SLPTL_LEVEL_GROUP__TRUST_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__TRUST_MAX)
        return TRUE;

    if (dwLevel >= SLPTL_LEVEL_GROUP__LOCAL_WHITE_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__LOCAL_WHITE_MAX)
        return TRUE;

    return FALSE;
}

/// ...
inline BOOL SLLevelIsServer(DWORD dwLevel)
{
    return dwLevel >= SLPTL_LEVEL_GROUP__SERVER_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__SERVER_MAX;
}

/// ...
inline BOOL SLLevelIsLocalError(DWORD dwLevel)
{
    return dwLevel >= SLPTL_LEVEL_GROUP__LOCAL_ERROR_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__LOCAL_ERROR_MAX;
}

/// ...
inline BOOL SLLevelIsLocalWhite(DWORD dwLevel)
{
    return dwLevel >= SLPTL_LEVEL_GROUP__LOCAL_WHITE_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__LOCAL_WHITE_MAX;
}

/// ...
inline BOOL SLLevelIsLocalBlack(DWORD dwLevel)
{
    return dwLevel >= SLPTL_LEVEL_GROUP__LOCAL_BLACK_MIN &&
        dwLevel <= SLPTL_LEVEL_GROUP__LOCAL_BLACK_MAX;
}

NS_SKYLARK_END

#endif//BKLEVEL_H