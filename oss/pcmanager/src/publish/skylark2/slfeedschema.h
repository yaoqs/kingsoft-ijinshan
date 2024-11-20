/**
* @file    slfeedschema.h
* @brief   ...
* @author  zhangrui
* @date    2009-03-03  11:43
*/

#ifndef SLFEEDSCHEMA_H
#define SLFEEDSCHEMA_H

//////////////////////////////////////////////////////////////////////////
// 16���µ�idΪLSE����,��ص� feedcode ��ѯ lse�� bugcode.h �� infocode.h
//////////////////////////////////////////////////////////////////////////
//    bugfeed       ->  feeddbg
//        id        ->
//        mid       ->  mid
//                  ->  ver
//        time      ->  time
//        ip        ->  ip
//        ptype     ->  schema
//        code      ->  code
//                  ->  par
//        content   ->  msg
//
//////////////////////////////////////////////////////////////////////////
//    infourl       ->  feedsta
//        id        ->
//        mid       ->  mid
//                  ->  ver
//        time      ->  time
//        ip        ->  ip
//        ptype     ->  schema
//        code      ->  code
//                  ->  par
//        content   ->
//
//////////////////////////////////////////////////////////////////////////
//    activeinfo    ->  feedadt
//        mid       ->  mid
//                  ->  ver
//        ip        ->  ip
//        type      ->  pid
//        tid1      ->  chid
//                  ->  act
//  
#define SLK_SCHEMA_LSE_PT_UPDATE               1       ///< ��������
#define SLK_SCHEMA_LSE_PT_LSE                  2       ///< LSE
#define SLK_SCHEMA_LSE_PT_OGSLDR               3       ///< ����Ƕ��ģ��
#define SLK_SCHEMA_LSE_PT_SKYLARK              4       ///< Skylark����ģ��
#define SLK_SCHEMA_LSE_PT_OGSVR                5       ///< ���α�������
#define SLK_SCHEMA_LSE_PT_AV_DETECT            6       ///< ɱ����(�ѷ���)
#define SLK_SCHEMA_LSE_PT_FW_DETECT            8       ///< ����ǽ���(�ѷ���)
#define SLK_SCHEMA_LSE_PT_OS_DETECT            9       ///< ����ϵͳ�汾���(�ѷ���)
#define SLK_SCHEMA_LSE_PT_PP_SVR               7       ///< ����ʺű���
#define SLK_SCHEMA_LSE_PT_ANTIARP              10      ///< ARP ����ǽ
#define SLK_SCHEMA_LSE_PT_FILE_SYS_DETECT      11      ///< �ļ�ϵͳ̽��(�ѷ���)
#define SLK_SCHEMA_LSE_PT_UPDATE_VC_LOG        12      ///< �汾check��¼
#define SLK_SCHEMA_LSE_PT_BIGFOOT_DOWNLOADER   13      ///< ���������
#define SLK_SCHEMA_LSE_PT_BKSECPRT             14      ///< ���̱���ģ��
#define SLK_SCHEMA_LSE_PT_SKYLARK_PROTO        15      ///< skylark�ͻ���(v1)

//////////////////////////////////////////////////////////////////////////
// [16, 127] ��skylarkʹ��
#define SLK_SCHEMA_TEST             16      ///< ������
#define SLK_SCHEMA_UPDATE           17      ///< ����ģ��

#define SLK_SCHEMA_ENV_INF          32      ///< ������Ϣ�ռ�
#define SLK_SCHEMA_PROTO            33      ///< level��ѯ���ϱ�
#define SLK_SCHEMA_PROTO_AUTORUN    34      ///< autorun��ѯ���ϱ�
#define SLK_SCHEMA_AUTORUN          35      ///< autorunģ�鱾��Ĳ�ѯ���ϱ�
#define SLK_SCHEMA_CACHE_DB         36      ///< skylark�������ݿ�
#define SLK_SCHEMA_TRJSCAN          37      ///< skylarkɨ��ģ��

#define SLK_SCHEMA_BEIKE_ANTIARP    38      ///< ����arp����ǽ

#define SLK_SCHEMA_ELIVESAFE        39      ///< ����beikeserv

#define SLK_SCHEMA_BACKUP           40      ///< skylark����ģ��

//////////////////////////////////////////////////////////////////////////
// ����ģ��� 64 ��ʼ����
#define SLK_SHEMA_VKILLER           64      ///< ľ��רɱ
#define SLK_SHEMA_OLSCAN            65      ///< ����ɱ��

#define SLK_SCHMEA_MAX              256     ///< ���256


#endif//SLFEEDSCHEMA_H