/**
* @file    slfeedcode.h
* @brief   ...
* @author  zhangrui
* @date    2009-03-02  15:21
*/

#ifndef SLFEEDCODE_H
#define SLFEEDCODE_H

//////////////////////////////////////////////////////////////////////////
#define SLK_FEEDCODE_MAX            65535   ///< code �����ֵ

//////////////////////////////////////////////////////////////////////////
// SLK_SCHEMA_ENV_INF = 32
#define SLK_FEEDCODE_AV_DETECT          1       ///< ɱ����
#define SLK_FEEDCODE_FW_DETECT          2       ///< ����ǽ���
#define SLK_FEEDCODE_OS_DETECT          3       ///< ����ϵͳ���
#define SLK_FEEDCODE_FS_DETECT          4       ///< �ļ�ϵͳ���
#define SLK_FEEDCODE_SOFTWARE_DETECT    5       ///< �����װ�ռ�

//////////////////////////////////////////////////////////////////////////
// SLK_SCHEMA_PROTO = 33
#define SLK_FEEDCODE_SLPROTO_QUERY_SYS_1ST              1001    ///< ��һ�β�ѯϵͳ��Ϣ
#define SLK_FEEDCODE_SLPROTO_QUERY_SYS_2ND              1002    ///< �ڶ��β�ѯϵͳ��Ϣ
#define SLK_FEEDCODE_SLPROTO_QUERY_SYS_3RD              1003    ///< �����β�ѯϵͳ��Ϣ
#define SLK_FEEDCODE_SLPROTO_UPLOAD_SYS                 1004    ///< �ϴ�ϵͳ��Ϣ
#define SLK_FEEDCODE_SLPROTO_QUERY_PROCESS              1005    ///< ��ѯ������Ϣ
#define SLK_FEEDCODE_SLPROTO_UPLOAD_PROCESS             1006    ///< �ϴ�������Ϣ
#define SLK_FEEDCODE_SLPROTO_UPLOAD_FILE                1007    ///< �ϴ��ļ�
#define SLK_FEEDCODE_SLPROTO_LOST_UPLOADED_SYS          1008    ///< �޷���ѯ���ϴ�������Ϣ
#define SLK_FEEDCODE_SLPROTO_QUERY_SYSTEM32             1009    ///< ��ѯsystem32Ŀ¼�µ��ļ�ʱ��������
#define SLK_FEEDCODE_SLPROTO_UPLOAD_SYSTEM32            1010    ///< �ϴ�system32Ŀ¼�µ��ļ�ʱ��������

#define SLK_FEEDCODE_SLPROTO_SYS_SCAN_ACCOMPLISH        1100    ///< ���ϵͳɨ��

#define SLK_FEEDCODE_SLPROTO_MEH_FAILED_TO_QUERY_FILE   2001    ///< mehɨ���޷����ļ�

#define SLK_FEEDCODE_SLPROTO_ENCRYPT_ERROR              3001    ///< ���ܴ���
#define SLK_FEEDCODE_SLPROTO_DECRYPT_ERROR              3002    ///< ���ܴ���

#define SLK_FEEDCODE_SLPROTO_FAILED_TO_UPLOAD_FILE      4001    ///< �ϴ��ļ�ʧ��
#define SLK_FEEDCODE_SLPROTO_FAILED_TO_UPLOAD_FILE_SIZE 4002    ///< �ϴ��ļ�ʧ��,�����ļ���С

#define SLK_FEEDCODE_SLPROTO_STANDALONE_FAILED_TO_UPLOAD_FILE   5001    ///< �����ϴ��ļ�ʧ��
#define SLK_FEEDCODE_SLPROTO_STANDALONE_SUCCEED_TO_UPLOAD_FILE  5002    ///< �����ϴ��ļ��ɹ�
#define SLK_FEEDCODE_SLPROTO_STANDALONE_INTERRUPT_UPLOAD_FILE   5003    ///< �����ϴ��ļ��ж�
#define SLK_FEEDCODE_SLPROTO_STANDALONE_AUTO_FAILED_TO_INIT     5004    ///< �Զ��ϴ�������ʼ��ʧ��
#define SLK_FEEDCODE_SLPROTO_STANDALONE_MANUAL_FAILED_TO_INIT   5005    ///< �ֶ��ϴ�������ʼ��ʧ��
#define SLK_FEEDCODE_SLPROTO_STANDALONE_AUTO_FAILED_TO_APPEND   5006    ///< �Զ��ϴ���������ʧ��
#define SLK_FEEDCODE_SLPROTO_STANDALONE_MANUAL_FAILED_TO_APPEND 5007    ///< �ֶ��ϴ���������ʧ��
#define SLK_FEEDCODE_SLPROTO_STANDALONE_AUTO_FAILED_TO_TOTAL    5008    ///< �Զ��ϴ�������ѯ����ʧ��
#define SLK_FEEDCODE_SLPROTO_STANDALONE_MANUAL_FAILED_TO_TOTAL  5009    ///< �ֶ��ϴ�������ѯ����ʧ��

#define SLK_FEEDCODE_SLPROTO_STANDALONE_BACKUP_FAILED_TO_INIT   5010    ///< �����ļ��ϴ�������ʼ��ʧ��
#define SLK_FEEDCODE_SLPROTO_STANDALONE_BACKUP_FAILED_TO_APPEND 5011    ///< �����ļ��ϴ���������ʧ��
#define SLK_FEEDCODE_SLPROTO_STANDALONE_BACKUP_FAILED_TO_TOTAL  5012    ///< �����ļ��ϴ�������ѯ����ʧ��
#define SLK_FEEDCODE_SLPROTO_STANDALONE_BACKUP_FAILED_TO_CALL   5013    ///< �����ļ��ϴ���������ĳ���ļ�ʧ�ܵ���ʣ��û���ϴ�

//////////////////////////////////////////////////////////////////////////
// SLK_SCHEMA_PROTO_AUTORUN = 34
#define SLK_FEEDCODE_SLPROTOATR_INIT_AUTORUN            1       ///< ��ʼ��autorun
#define SLK_FEEDCODE_SLPROTOATR_NO_ENTRY_FOUND          2       ///< autorunû��ɨ�赽�κ��ļ�
#define SLK_FEEDCODE_SLPROTOATR_FAILED_TO_QUERY_FILE    3       ///< autorunɨ��ʱ,��ѯ�ļ�ʧ��
#define SLK_FEEDCODE_SLPROTOATR_FAILED_TO_REPORT_FILE   4       ///< autorunɨ��ʱ,�����ļ���Ϣʧ��
#define SLK_FEEDCODE_SLPROTOATR_FAILED_TO_UPLOAD_FILE   5       ///< autorunɨ��ʱ,�ϴ��ļ�ʧ��

#define SLK_FEEDCODE_SLPROTOATR_MISSING_FILE            1001    ///< autorunɨ��ʱ,�޷����ļ�

//////////////////////////////////////////////////////////////////////////
// SLK_SCHEMA_AUTORUN = 35
#define SLK_FEEDCODE_SLAUTORUN__APPEND_MIN                      1000    ///< ...
#define SLK_FEEDCODE_SLAUTORUN__APPEND_REGVALUE_AS_STARTUP      1101    ///< Append_RegValue_As_Startupʱ, ����ʧ�ܵ��ַ���
#define SLK_FEEDCODE_SLAUTORUN__APPEND_REGVALUE_AS_STARTUP_LIST 1201    ///< Append_RegValue_As_Startup_Listʱ, ����ʧ�ܵ��ַ���
#define SLK_FEEDCODE_SLAUTORUN__APPEND_SERVICE__IMAGE_PATH      1301    ///< Append_Serviceʱ,���� ImagePath ʧ��
#define SLK_FEEDCODE_SLAUTORUN__APPEND_SERVICE__SERVICE_DLL     1302    ///< Append_Serviceʱ,���� ServiceDll ʧ��
#define SLK_FEEDCODE_SLAUTORUN__APPEND_SCHEDULED_TASK_APP       1303    ///< Append_Scheduled_Taskʱ,����ִ���ļ�·��ʧ��
#define SLK_FEEDCODE_SLAUTORUN__APPEND_STARTUP_FOLDER_FILE      1304    ///< Append_Scheduled_Taskʱ,����ִ���ļ�·��ʧ��
#define SLK_FEEDCODE_SLAUTORUN__APPEND_MAX                      9999    ///< ...

#define SLK_FEEDCODE_SLAUTORUN__FAILED_TO_PARSE_EXISTING_FILE  10000    ///< �ļ�����,������ʧ��(ͨ����bug)
#define SLK_FEEDCODE_SLAUTORUN__MISSING_FILE_IN_COMMAND_LINE   10001    ///< û���ҵ���Ӧ�����������е��ļ�,����rundll32.exe�Ĳ���

//////////////////////////////////////////////////////////////////////////
// SLK_SCHEMA_CACHE_DB = 36
#define SLK_FEEDCODE_SLCACHEDB__FAILED_TO_OPEN_DATABASE         1       ///< �����ݿ�ʧ��
#define SLK_FEEDCODE_SLCACHEDB__FAILED_TO_INIT_DATABASE         2       ///< ��ʼ�����ݿ�ʧ��
#define SLK_FEEDCODE_SLCACHEDB__REBUILD_DB_AFTER_FAILURE_OPEN   3       ///< �����ݿ�ʧ�ܺ��ؽ����ݿ�
#define SLK_FEEDCODE_SLCACHEDB__REBUILD_DB_AFTER_FAILURE_INIT   4       ///< ��ʼ�����ݿ�ʧ�ܺ��ؽ����ݿ�
#define SLK_FEEDCODE_SLCACHEDB__FAILED_TO_REOPEN_AFTER_REBUILD  5       ///< �ؽ����ݿ���ʧ��

//////////////////////////////////////////////////////////////////////////
// SLK_SCHEMA_TRJSCAN = 37
#define SLK_FEEDCODE_SLTRJSCAN__SUCCEEDED_TO_DELETE_FILE                1       ///< ֱ��ɾ���ļ��ɹ�
#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_CREATE_RECYCLE                2       ///< ��������Ŀ¼ʧ��

#define SLK_FEEDCODE_SLTRKSCAN__FAILED_TO_MOVE_FILE                     3       ///< �ƶ��ļ�ʧ��

#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_REBOOT_MOVE_RECYCLE_FILE      4       ///< MoveFileEx�����ļ�ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__REMOVE_RECYCLE_FILE_NEED_REBOOT         5       ///< ɾ�������ļ�����Ҫ����

#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_REBOOT_MOVE_ORIGINAL_FILE     7       ///< MoveFileExԭʼ�ļ�ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__REMOVE_ORIGINAL_FILE_NEED_REBOOT        8       ///< ɾ��ԭʼ�ļ�����Ҫ����



#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_DENY_EXECUTE                  11      ///< �����ļ�ִ��Ȩ��ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_GET_FILE_ATTRIBUTES           12      ///< ��ȡ�ļ�����ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_SET_FILE_ATTRIBUTES           13      ///< �޸��ļ�����ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_ALLOW_DELETE                  14      ///< �����ļ�ɾ��Ȩ��ʧ��

#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_BOOT_CLEAN_RECYCLE_FILE       21      ///< ����Bootcleanɾ�������ļ�ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_BOOT_CLEAN_ORIGINAL_FILE      22      ///< ����Bootcleanɾ��ԭʼ�ļ�ʧ��

#define SLK_FEEDCODE_SLTRJSCAN__BOOT_CLEAN_RECYCLE_FILE_NEED_REBOOT     23      ///< ����Bootcleanɾ�������ļ�����Ҫ����
#define SLK_FEEDCODE_SLTRJSCAN__BOOT_CLEAN_ORIGINAL_FILE_NEED_REBOOT    24      ///< ����Bootcleanɾ��ԭʼ�ļ�����Ҫ����


#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_OCCUPY_FILE                   25      ///< ռ���ļ�ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_TERMINATE_PROCESS             26      ///< ��������ʧ��

#define SLK_FEEDCODE_SLTRJSCAN__TERMINATE_PROCESS_FOR_2ND_CHANCE        27      ///< �ڵڶ��ν������̹����н����Ľ���




#define SLK_FEEDCODE_SLTRJSCAN__SUCCEEDED_TO_REPLACE_FILE                   1001    ///< ֱ�Ӹ����ļ��ɹ�
#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_COPY_FOR_REPLACE                  1002    ///< �����������ǵ��ļ�ʱʧ��
#define SLK_FEEDCODE_SLTRJSCAN__FAILED_TO_REBOOT_REPLACE_FILE               1003    ///< ����MoveFileEx
#define SLK_FEEDCODE_SLTRJSCAN__REPLACE_FILE_NEED_REBOOT                    1004    ///< MoveFileEx�滻�ļ�����Ҫ����
#define SLK_FEEDCODE_SLTRJSCAN__REPLACE_FILE_BUT_FAILED_TO_DELETE_RECYCLE   1005    ///< �滻�ļ��ɹ�,���Ǳ��滻���ļ�ɾ��ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__REPLACE_FILE_NEED_REBOOT_DELETE_RECYCLE     1006    ///< �滻�ļ��ɹ�,��Ҫ����ɾ�����յ��ļ�
#define SLK_FEEDCODE_SLTRJSCAN__REPLACE_FILE_DELETE_DEST_BUT_FAILED_TO_COPY 1007    ///< �滻�ļ�,�����ļ��ɹ�,���ǿ����ļ���ԭλ��ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__REPLACE_FILE_FAILED_TO_MOVE_FILE            1008    ///< �滻�ļ�ʱ,����ԭ���ļ�ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__REPLACE_FILE_FAILED_TO_CREATE_RECYCLE_DIR   1009    ///< �滻�ļ�ʱ,��������Ŀ¼ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__FAILED_BOOT_REPLACE                         1010    ///< bootreplaceʧ��


#define SLK_FEEDCODE_SLTRJSCAN__SFM_FAILED_TO_SEARCH_INDEX                  2001    ///< ��������ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__SFM_INVALID_INDEX                           2002    ///< ��Ч������
#define SLK_FEEDCODE_SLTRJSCAN__SFM_FAILED_TO_LOCAL_MAKE_DOWNLOAD_PATH      2003    ///< ���챾������·��ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__SFM_FAILED_TO_DOWNLOAD_FILE                 2004    ///< �����ļ�ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__SFM_DOWNLOAD_FILE_MISMATCH                  2005    ///< ���ص��ļ���ƥ��
#define SLK_FEEDCODE_SLTRJSCAN__SFM_FAILED_TO_LOAD_SFC_OS_DLL               2006    ///< ����sfc_os.dllʧ��
#define SLK_FEEDCODE_SLTRJSCAN__SFM_FAILED_TO_DISABLE_SFC_OF_DLL_CACHE_FILE 2007    ///< ����dllcache�ļ���sfcʧ��
#define SLK_FEEDCODE_SLTRJSCAN__SFM_FAILED_TO_DISABLE_SFC_OF_SYSTEM_FILE    2008    ///< ����system�ļ���sfcʧ��
#define SLK_FEEDCODE_SLTRJSCAN__SFM_FAILED_TO_REPLACE_SFC_OF_DLL_CACHE_FILE 2009    ///< �滻dllcache�ļ�ʧ��
#define SLK_FEEDCODE_SLTRJSCAN__SFM_FAILED_TO_REPLACE_SFC_OF_SYSTEM_FILE    2010    ///< ����system�ļ�ʧ��

//////////////////////////////////////////////////////////////////////////
// SLK_SCHEMA_BEIKE_ANTIARP = 38
//service error
#define SLK_FEEDCODE_ANTIARP__SERVICE_DUMP_FILE_NUM                                         1      ///< ����dump�ļ�ͳ��  
#define SLK_FEEDCODE_ANTIARP__SERVICE_LOAD_BEIKECMM_DLL                                     2      ///< ����dll�ļ�beikecmm.dllʧ��
#define SLK_FEEDCODE_ANTIARP__SERVICE_OPEN_DEVICE										    3      ///< �������豸����ʧ��
#define SLK_FEEDCODE_ANTIARP__SERVICE_CREATE_NAME_PIPE									    4      ///< �������ܵ�ʧ��
#define SLK_FEEDCODE_ANTIARP__SERVICE_CONNECT_NAMED_PIPE 								    5      ///< �ȴ������ܵ�����ʧ��
#define SLK_FEEDCODE_ANTIARP__SERVICE_LOAD_BEIKENETCFG_DLL								    6      ///< ����dll�ļ�beikenetcfg.dllʧ��
#define SLK_FEEDCODE_ANTIARP__SERVICE_ARP_ATTAC                                             7      ///< ����ARP����
#define SLK_FEEDCODE_ANTIARP__SERVICE_GET_GATEWAY                                           9      ///< ������ʧ��
//update error
#define SLK_FEEDCODE_ANTIARP__UPDATE_CALLBACK_ON_ERROR									  51      ///< OnError�ص�
#define SLK_FEEDCODE_ANTIARP__UPDATE_GET_MODULE_NAME                                      52      ///< ��ģ����ʧ��
#define SLK_FEEDCODE_ANTIARP__UPDATE_CREATE_UPDATE_INTERFACE                              53      ///< �������½ӿ�ʧ��
#define SLK_FEEDCODE_ANTIARP__UPDATE_COPY_SYS_FILE                                        54      ///< ��������ʧ��

//////////////////////////////////////////////////////////////////////////
// SLK_SCHEMA_ELIVESAFE = 39
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_CALL_UPDATE                                   1       ///< ��������ʧ��
#define SLK_FEEDCODE_ELIVESAFE__MISSING_ELIVEBEIKE_DLL                                  2       ///< û���ҵ�elivebeike.dll
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_OBTAIN_CALLER_TOKEN                           3       ///< ��ȡ������ tokenʧ��
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_OBTAIN_ELIVE_TOKEN                            4       ///< ��ȡelive tokenʧ��
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_OBTAIN_EXPLORER_TOKEN                         5       ///< ��ȡexplorer tokenʧ��
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_OBTAIN_ANY_DESKTOP_TOKEN                      6       ///< û�ܻ�ȡ�κ�����token

#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_OPEN_SERVICE_MANAGER_FOR_INSTALL              101     ///< �򿪷��������ʧ��(��װ)
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_CREATE_SERVICE                                102     ///< ��������ʧ��

#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_OPEN_SERVICE_MANAGER_FOR_UNINSTALL            201     ///< �򿪷��������ʧ��(ж��)
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_OPEN_SERVICE_FOR_UNINSTALL                    202     ///< �򿪷���ʧ��(ж��)
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_STOP_SERVICE_FOR_UNINSTALL                    203     ///< ֹͣ����ʧ��(ж��)
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_DELETE_SERVICE                                204     ///< ɾ������ʧ��(ж��)

#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_OPEN_SERVICE_MANAGER_FOR_START                301     ///< �򿪷��������ʧ��(����)
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_OPEN_SERVICE_FOR_START                        302     ///< �򿪷���ʧ��(����)
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_QUERY_SERVICE_STATUS_FOR_START                303     ///< ��ѯ����״̬ʧ��(����)
#define SLK_FEEDCODE_ELIVESAFE__TIMEOUT_WAITING_SERVICE_TO_STOP_FOR_START               304     ///< �ȴ�����ֹͣ��ʱ(����)
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_START_SERVICE_FOR_START                       305     ///< ��������ʧ��(����)
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_QUERY_SERVICE_STATUS_AFTER_START_FOR_START    306     ///< �ٴβ�ѯ����״̬ʧ��(����)
#define SLK_FEEDCODE_ELIVESAFE__SERVICE_NOT_STARTED_FOR_START                           307     ///< ��������ʧ��(����)

#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_OPEN_SERVICE_MANAGER_FOR_STOP                 401     ///< �򿪷��������ʧ��(ֹͣ)
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_OPEN_SERVICE_FOR_STOP                         402     ///< �򿪷���ʧ��(ֹͣ)
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_QUERY_SERVICE_STATUS_FOR_STOP                 403     ///< ��ѯ����״̬ʧ��(ֹͣ)
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_STOP_SERVICE_FOR_STOP                         404     ///< ֹͣ����ʧ��(ֹͣ)
#define SLK_FEEDCODE_ELIVESAFE__FAILED_TO_STOP_SERVICE_AFTER_STOP_FOR_STOP              405     ///< �ٴβ�ѯ����״̬ʧ��(ֹͣ)

//////////////////////////////////////////////////////////////////////////
// SLK_SCHEMA_UPDATE = 17

//////////////////////////////////////////////////////////////////////////
// SLK_SCHEMA_VKILLER = 64
#define SLK_FEEDCODE_VKILLER_SCAN_REPORT                            1   ///< ɨ�����ϱ�
#define SLK_FEEDCODE_VKILLER_ECHO_RESULT                            2   ///< ���ֽ���ϱ�
#define SLK_FEEDCODE_VKILLER_POPUP_SHOW                             3   ///< ���ݵ����ϱ�
#define SLK_FEEDCODE_VKILLER_APP_PATH                               4   ///< ��������Ŀ¼�ϱ�

#define SLK_FEEDCODE_VKILLER_WRONG_VIRUS_STATUS                     5   ///< ͳ�Ʋ���ʾ����ʽ�������ʽ�Ĵ���

//////////////////////////////////////////////////////////////////////////
// SLK_SHEMA_OLSCAN = 65
#define SLK_FEEDCODE_OLSCAN_INSTALL_ERROR                           1   ///< ��װʧ��

//////////////////////////////////////////////////////////////////////////
// SLK_SCHEMA_BACKUP = 40
#define SLK_FEEDCODE_BACKUP_FAILED_TO_DELETE_NONNIL_DIRECTORY       1   ///< ɾ���ǿ�Ŀ¼ʧ��
#define SLK_FEEDCODE_BACKUP_FAILED_TO_ALL_DELETE                    2   ///< ����ɾ������ʧ��
#define SLK_FEEDCODE_BACKUP_FAILED_TO_NORMAL_RETRIEVE               3   ///< һ��Ļָ������ļ�ʧ��

#endif//SLFEEDCODE_H
