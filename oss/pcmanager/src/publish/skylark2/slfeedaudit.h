/**
* @file    slfeedaudit.h
* @brief   ...
* @author  zhangrui
* @date    2009-03-18  16:56
*/

#ifndef SLFEEDAUDIT_H
#define SLFEEDAUDIT_H

//////////////////////////////////////////////////////////////////////////
// ��� pid ��ƷID
#define SLK_PID_UNKNOWN                     0       ///< δ֪�Ĳ�Ʒid
#define SLK_PID_UPDATE                      1       ///< ��������
#define SLK_PID_LSE                         2       ///< LSE
#define SLK_PID_OGSLDR                      3       ///< ����Ƕ��ģ��
#define SLK_PID_SKYLARK                     4       ///< Skylark����ģ��
#define SLK_PID_OGSVR                       5       ///< ���α�������
#define SLK_PID_AV_DETECT                   6       ///< ɱ����
#define SLK_PID_FW_DETECT                   8       ///< ����ǽ���
#define SLK_PID_OS_DETECT                   9       ///< ����ϵͳ�汾���
#define SLK_PID_PP_SVR                      7       ///< ����ʺű���
#define SLK_PID_ANTIARP                     10      ///< ARP ����ǽ
#define SLK_PID_FILE_SYS_DETECT             11      ///< �ļ�ϵͳ̽��
#define SLK_PID_UPDATE_VC_LOG               12      ///< �汾check��¼
#define SLK_PID_BIGFOOT_DOWNLOADER          13      ///< ���������
#define SLK_PID_BKSECPRT                    14      ///< ���̱���ģ��
#define SLK_PID_SKYLARK_PROTO               15      ///< skylark�ͻ���
// ����ΪLSE v1����ز�Ʒʹ�õ�pid

#define SLK_PID_VKILLER                     16      ///< ľ��רɱ�ͻ���
#define SLK_PID_BIGFOOT_EMBEDDED            17      ///< ��ŵ�Ƕ��ģ��
#define SLK_PID_SKYLARKSCAN_TOOL            18      ///< ������ɨ�蹤��

#define SLK_PID_SKYLARK_FOR_SOGOU           19      ///< �ѹ�

#define SLK_PID_ELIVE_SAFE                  20      ///< ��������live����
#define SLK_PID_BEIKE_ANTIARP               21      ///< ���ǵ�arp����ǽ
#define SLK_PID_BEIKE_ONLINESCAN            22      ///< ��������ɱ��
#define SLK_PID_KSAFE                       23      ///< ��ɽ��ʿ��pid

#define SLK_PID_MAX                         256     ///< pid �����ֵ


//////////////////////////////////////////////////////////////////////////
// ��� chid ͨ��ID
#define SLK_CHID_DEFAULT            0       ///< Ĭ�ϵ�ͨ��

// LSE�õ���CHID
#define SLK_CHID_LSE_SKYLARK2       2       ///< ʹ��skylark2��lse����

// SLK_PID_VKILLER �õ���CHID
#define SLK_CHID_BIGFOOT            1       ///< vkiller ͨ����ŷ����ĵ�ͨ��
#define SLK_CHID_BBS                2       ///< vkiller ͨ����̳�����ĵ�ͨ��
#define SLK_CHID_BAOFENG            3       ///< vkiller ͨ�����緢���ĵ�ͨ��
#define SLK_CHID_KINGSOFT           4       ///< vkiller ͨ����ɽ�����ĵ�ͨ��
#define SLK_CHID_ELIVE              5       ///< vkiller ͨ������ELive�����ĵ�ͨ��
#define SLK_CHID_9DUAN              6       ///< vkiller ͨ��9�����鷢���ĵ�ͨ��
#define SLK_CHID_JIANDANYOU         7       ///< vkiller ͨ�����η����ĵ�ͨ��
#define SLK_CHID_LANGANG            8       ///< vkiller ͨ�����۷����ĵ�ͨ��
#define SLK_CHID_CHENGJISIHAN       9       ///< vkiller ͨ������ɼ�˼�������ĵ�ͨ��
#define SLK_CHID_KINGSOFTGAME       11      ///< vkiller ͨ����ɽ��Ϸ�����ĵ�ͨ��
#define SLK_CHID_798                12      ///< vkiller ͨ��798�����ĵ�ͨ��
#define SLK_CHID_OEM                13      ///< vkiller �޶���������Ҫ����ͳ�Ƶİ汾ͨ��
#define SLK_CHID_BIGFOOT_WOW        14      ///< vkiller ͨ��ħ�޴�ŷ����ĵ�ͨ��
#define SLK_CHID_BIGFOOT_JX3        15      ///< vkiller ͨ��������ŷ����ĵ�ͨ��
#define SLK_CHID_OEM_CIBA           16      ///< vkiller ͨ���ʰԷ�����ͨ��
#define SLK_CHID_BAOYI              17      ///< vkiller ͨ��������������ͨ��
#define SLK_CHID_W2K                18      ///< vkiller win2kר�ð汾��ͨ��
#define SLK_CHID_ANTIARP            19      ///< vkiller ͨ��arp����ǽ�����ͨ��
#define SLK_CHID_YY                 20      ///< vkiller ͨ��YY������ͨ��
#define SLK_CHID_SUBANG             21      ///< vkiller �ٰ�İ汾ͨ��
#define SLK_CHID_KSG_FS2            22      ///< vkiller �����2ͨ��
#define SLK_CHID_KSG_JXW2           23      ///< vkiller ����2�⴫ͨ��

#define SLK_CHID_VIRSCAN_ORG        10      ///< ��virscan.org�ṩ��ɨ�蹤��

#define SLK_CHID_MAX                65536   ///< chid �����ֵ


//////////////////////////////////////////////////////////////////////////
// ��� action ��ΪID
#define SLK_FEEDAUDIT_ACT_UNKNOWN                       0       ///< ������
#define SLK_FEEDAUDIT_ACT_PRODUCT_INSTALL               1       ///< ��װ: ����װ������ɰ�װʱ
#define SLK_FEEDAUDIT_ACT_PRODUCT_UNINSTALL             2       ///< ж��: ��ж�س������ж��ʱ
#define SLK_FEEDAUDIT_ACT_PRODUCT_ACTIVE                3       ///< ��Ծ: ��Ʒ���κ�ģ��ִ��ʱ
#define SLK_FEEDAUDIT_ACT_PRODUCT_FIRST_ACTIVE          4       ///< �״λ�Ծ: ��һ��"��Ծ"����ʱ
#define SLK_FEEDAUDIT_ACT_PRODUCT_INTERACTIVE           5       ///< ������Ծ: ��Ʒ���û����ʹ��ʱ
#define SLK_FEEDAUDIT_ACT_PRODUCT_FIRST_INTERACTIVE     6       ///< �״ν�����Ծ: ��һ��"������Ծ����ʱ"

#define SLK_FEEDAUDIT_ACT_PRODUCT_ACTIVE_FOR_UPDATE     51      ///< ��Ծ����������ѭ��ġ�

// SLK_PID_VKILLER �õ���ACT
#define SLK_FEEDAUDIT_ACT_PRODUCT_SCHEDULE_ACTIVE       7       ///< �ƻ������Ծ
#define SLK_FEEDAUDIT_ACT_PRODUCT_FASTCHECK_ACTIVE      8       ///< ����ɨ���Ծ
#define SLK_FEEDAUDIT_ACT_PRODUCT_SINGLESCAN_ACTIVE     9       ///< �����ļ�ɨ���Ծ
#define SLK_FEEDAUDIT_ACT_PRODUCT_TAKE_SCORE            10      ///< ��ֻ�Ծ
#define SLK_FEEDAUDIT_ACT_PRODUCT_YYCHECK_ACTIVE        11       ///< ����ɨ���Ծ

#define SLK_FEEDAUDIT_ACT_MAX                           256     ///< ����audit action id

#endif//SLFEEDAUDIT_H