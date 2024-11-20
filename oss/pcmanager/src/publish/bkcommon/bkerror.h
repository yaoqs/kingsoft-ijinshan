/**
* @file    bkerror.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-11 15:28
*/

#ifndef BKERROR_H
#define BKERROR_H

#include <winerror.h>


//////////////////////////////////////////////////////////////////////////
// �ж��Ƿ���windows������
//////////////////////////////////////////////////////////////////////////

/// �ж��Ƿ���windows����
#define IS_WIN32_ERROR(x)                           ((0xFFFF0000 & x) == 0x80070000)



//////////////////////////////////////////////////////////////////////////
// skylark
//////////////////////////////////////////////////////////////////////////
#define MAKE_SKYLARK_SUCCESS(x)                     HRESULT(0x60010000 | (0xFFFF & x))
#define MAKE_SKYLARK_ERROR(x)                       HRESULT(0xA0010000 | (0xFFFF & x))
#define IS_SKYLARK_MOD_HRESULT(x)                   ((0x3FFF0000 & x) == 0x20010000)


//////////////////////////////////////////////////////////////////////////
// http
//////////////////////////////////////////////////////////////////////////
#define MAKE_SKYLARK_HTTP_SUCCESS(x)                HRESULT(0x60020000 | (0xFFFF & x))
#define MAKE_SKYLARK_HTTP_ERROR(x)                  HRESULT(0xA0020000 | (0xFFFF & x))
#define IS_SKYLARK_HTTP_HRESULT(x)                  ((0x3FFF0000 & x) == 0x20020000)


//////////////////////////////////////////////////////////////////////////
// sqlite
//////////////////////////////////////////////////////////////////////////
#define MAKE_SKYLARK_SQLITE_SUCCESS(x)              HRESULT(0x60030000 | (0xFFFF & x))
#define MAKE_SKYLARK_SQLITE_ERROR(x)                HRESULT(0xA0030000 | (0xFFFF & x))
#define IS_SKYLARK_SQLITE_HRESULT(x)                ((0x3FFF0000 & x) == 0x20030000)


//////////////////////////////////////////////////////////////////////////
// skylark server
//////////////////////////////////////////////////////////////////////////
#define MAKE_SKYLARK_SERVER_SUCCESS(x)              HRESULT(0x60040000 | (0xFFFF & x))
#define MAKE_SKYLARK_SERVER_ERROR(x)                HRESULT(0xA0040000 | (0xFFFF & x))
#define IS_SKYLARK_SERVER_HRESULT(x)                ((0x3FFF0000 & x) == 0x20040000)

//////////////////////////////////////////////////////////////////////////
// ����
//////////////////////////////////////////////////////////////////////////
#define MAKE_BKENG_SUCCESS(x)                       HRESULT(0x60050000 | (0xFFFF & x))
#define MAKE_BKENG_ERROR(x)                         HRESULT(0xA0050000 | (0xFFFF & x))
#define IS_BKENG_HRESULT(x)                         ((0x3FFF0000 & x) == 0x20050000)





//////////////////////////////////////////////////////////////////////////
// skylark
//////////////////////////////////////////////////////////////////////////
#define ERROR_SKYLARK_CACHED_HASH                           0x0001  ///< �����hash
#define ERROR_SKYLARK_CACHED_LEVEL                          0x0002  ///< �����level
#define ERROR_SKYLARK_CACHED_WINTRUST                       0x0003  ///< �����WinTrust���
#define ERROR_SKYLARK_BWLIB_LEVEL                           0x0004  ///< �Ӻڰ׿��ȡ��level

#define ERROR_SKYLARK_RSP_NO_FILE_LEVEL                     0x0005  ///< �ظ���û�п��õ��ļ�level
#define ERROR_SKYLARK_RSP_NO_PROCESS_LEVEL                  0x0006  ///< �ظ���û�п��õĽ���level

#define ERROR_SKYLARK_QUERY_FILE_RSP_ERROR                  0x0010  ///< �����ļ�hash��ѯ�Ľ��ʱ��������
#define ERROR_SKYLARK_UPLOAD_FILE_RSP_ERROR                 0x0011  ///< �����ļ�    �ϴ��Ľ��ʱ��������
#define ERROR_SKYLARK_QUERY_PROCESS_RSP_ERROR               0x0012  ///< ��������hash��ѯ�Ľ��ʱ��������
#define ERROR_SKYLARK_UPLOAD_PROCESS_RSP_ERROR              0x0013  ///< ��������hash�ϴ��Ľ��ʱ��������
#define ERROR_SKYLARK_QUERY_SYSTEM_RSP_ERROR                0x0014  ///< ����ϵͳhash��ѯ�Ľ��ʱ��������
#define ERROR_SKYLARK_UPLOAD_SYSTEM_RSP_ERROR               0x0015  ///< ����ϵͳhash�ϴ��Ľ��ʱ��������
#define ERROR_SKYLARK_CMD_ENCRYPT_ERROR                     0x0030  ///< Э��������ܴ���
#define ERROR_SKYLARK_RSP_DECRYPT_ERROR                     0x0031  ///< Э��ظ����ܴ���
#define ERROR_SKYLARK_RSP_CORRUPT_ERROR                     0x0032  ///< Э��ظ���hashֵ��ƥ��

#define ERROR_SKYLARK_WIN_TRUST_FILE                        0x0040  ///< �ļ���������ǩ��
#define ERROR_SKYLARK_NON_PE_FILE                           0x0041  ///< ��PE�ļ�
#define ERROR_SKYLARK_IS_SFC_PROTECTED                      0x0042  ///< ��sfc�ļ�����
#define ERROR_SKYLARK_TRUSTED_INSTALLER                     0x0043  ///< �����ε�owner
#define ERROR_SKYLARK_NON_EXE_FILE                          0x0044  ///< �ǿ�ִ���ļ�

#define ERROR_SKYLARK_NO_FILES_BE_HASHED                    0x0050  ///< û���ļ���hash
#define ERROR_SKYLARK_NO_PROCESSES_BE_HASHED                0x0051  ///< û�н��̱�hash

#define ERROR_SKYLARK_TOO_LARGE_FILE                        0x0060  ///< �ļ�̫��
#define ERROR_SKYLARK_TOO_SMALL_FILE                        0x0061  ///< �ļ�̫С
#define ERROR_SKYLARK_EMPTY_FILE                            0x0062  ///< ���ļ� 

#define ERROR_SKYLARK_PENDING_SCAN                          0x0071  ///< �ӳٲ�ѯ
#define ERROR_SKYLARK_NO_NEED_TO_UPLOAD                     0x0072  ///< �ļ�����Ҫ�ϴ�

#define ERROR_SKYLARK_B3A_SCAN                              0x0080  ///< Ӧ��B3Aɨ��
#define ERROR_SKYLARK_B3A_NO_NEED_TO_FIX                    0x0081  ///< ����Ҫʹ��B3A�����޸�
#define ERROR_SKYLARK_B3A_FAILED_TO_FIX                     0x0082  ///< B3A�޸�ʧ��

#define ERROR_SKYLARK_LEVEL_CAN_NOT_CLEAN                   0x0090  ///< level����Ҫclean

#define ERROR_SKYLARK_REQUIRED_SKIP                         0x1001  ///< Ҫ������Ŀ��



#define ERROR_SKYLARK_OVERWRITE_INFECTED_SYS_FILE           0x2001  ///< ���Ǳ���Ⱦ��ϵͳ�ļ�
#define ERROR_SKYLARK_REMOVE_RECYCLE_FILE_NEED_REBOOT       0x2002  ///< ɾ����������ļ���Ҫ����
#define ERROR_SKYLARK_REMOVE_ORIGINAL_FILE_NEED_REBOOT      0x2003  ///< ɾ��ԭʼ�ļ�����Ҫ����
#define ERROR_SKYLARK_CAN_NOT_REMOVE_DIRECTORY              0x2004  ///< �޷�ɾ��Ŀ¼
#define ERROR_SKYLARK_BOOTCLEAN_RECYCLE_FILE_NEED_REBOOT    0x2005  ///< bootclean��������ļ���Ҫ����
#define ERROR_SKYLARK_BOOTCLEAN_ORIGINAL_FILE_NEED_REBOOT   0x2006  ///< bootcleanԭʼ�ļ�����Ҫ����


#define ERROR_SKYLARK_CAN_NOT_REPLACE_DIRECTORY                     0x2101  ///< ����Ĳ�����Ŀ¼,�޷��滻
#define ERROR_SKYLARK_REPLACE_FILE_NEED_REBOOT                      0x2102  ///< �滻�ļ�����Ҫ����
#define ERROR_SKYLARK_COPY_FOR_REPLACE                              0x2103  ///< ���������滻���ļ�
#define ERROR_SKYLARK_FAILED_TO_REBOOT_REPLACE_FILE                 0x2104  ///< ����MoveFileEx�滻�ļ�ʧ��
#define ERROR_SKYLARK_REPLACE_FILE_BUT_FAILED_TO_DELETE_RECYCLE     0x2105  ///< �滻�ļ��ɹ�,����ɾ�������ļ�ʧ��
#define ERROR_SKYLARK_REPLACE_FILE_NEED_REBOOT_DELETE_RECYCLE       0x2106  ///< �滻�ļ��ɹ�,��Ҫ����ɾ�������ļ�

#define ERROR_SKYLARK_BACKUP_FAILED_TO_REPLACE_NONNULL_DIRECTORY    0x21B1  ///< �޷��滻�ǿ�Ŀ¼
#define ERROR_SKYLARK_BACKUP_FAILED_TO_ALL_DELETE                   0x21B2  ///< ����ɾ��������ʧ��
#define ERROR_SKYLARK_BACKUP_FAILED_TO_FIND_SPECI_FILE              0x21B3  ///< �Ҳ���ָ���ļ�
#define ERROR_SKYLARK_BACKUP_NO_MORE_DISK_SPACE                     0x21B4  ///< ���̿ռ䲻��

#define ERROR_SKYLARK_RETRIEVE_FAILED_TO_OVERWRITE_DIRECTORY        0x21D1  ///< �޷���ԭ�ļ�(ָ���Ļָ�λ����һ��Ŀ¼)
#define ERROR_SKYLARK_RETRIEVE_FAILED_TO_OVERWRITE_FILE             0x21D2  ///< �޷���ԭ�ļ�(ָ���Ļָ�λ�ô���һ���ļ�)
#define ERROR_SKYLARK_RETRIEVE_MISSING_BACKUP_FILE                  0x21D3  ///< �������ݲ�����
#define ERROR_SKYLARK_RETRIEVE_FAILED_TO_EXTRACT_FILE               0x21D4  ///< ��ѹ�ļ���ʱ��������
#define ERROR_SKYLARK_RETRIEVE_FAILED_TO_EXTRACT_BACKUP_INFO        0x21D5  ///< ��ȡ�����ļ���Ϣ��ʱ��������
#define ERROR_SKYLARK_RETRIEVE_FAILED_TO_REPLACE_FILE               0x21D6  ///< �滻�ļ���ʱ��������


#define ERROR_SKYLARK_SFM_LOCAL_DOWNLOAD_NOT_MATCH          0x2201  ///< SFM(ϵͳ�ļ��޸�ģ��) �������ص��ļ��������еĲ�ƥ��
#define ERROR_SKYLARK_SFM_MISSING_URL_DATA                  0x2202  ///< SFM û���ҵ�url����
#define ERROR_SKYLARK_SFM_MISSING_INDEX_DATA                0x2203  ///< SFM û���ҵ�index����
#define ERROR_SKYLARK_SFM_MISSING_MODULE_IN_INDEX           0x2204  ///< SFM û����index�ҵ�ģ����Ϣ
#define ERROR_SKYLARK_SFM_MISSING_ENTRY                     0x2205  ///< SFM û����Ӳ�������ҵ�ϵͳ�ļ�entry
#define ERROR_SKYLARK_SFM_INVALID_URL_DATA                  0x2206  ///< SFM �ҵ���url������Ч
#define ERROR_SKYLARK_SFM_INVALID_INDEX_DATA                0x2207  ///< SFM �ҵ���index������Ч
#define ERROR_SKYLARK_SFM_DOWNLOAD_FILE_MISMATCH            0x2208  ///< SFM ���ص��ļ���ƥ��
#define ERROR_SKYLARK_SFM_NEED_REBOOT                       0x2209  ///< SFM �޸��ļ�����Ҫ����
#define ERROR_SKYLARK_SFM_FILE_NOT_IN_THIS_OS               0x220A  ///< SFC ָ����ϵͳ�ļ������ڲ���ϵͳ

#define ERROR_SKYLARK_SCSAPI_FAILED_TO_CALL_COPY_FILE       0x2301  ///< scs_copy_file   ����ʧ��
#define ERROR_SKYLARK_SCSAPI_FAILED_TO_CALL_DELETE_FILE     0x2302  ///< scs_delete_file ����ʧ��
#define ERROR_SKYLARK_SCSAPI_FAILED_TO_CALL_FILE_EXIST      0x2303  ///< scs_file_exists ����ʧ��


#define ERROR_SKYLARK_ONLY_SUPPORTED_ON_X86                 0x3001  ///< ��֧��x86
#define ERROR_SKYLARK_ONLY_SUPPORTED_ON_WINXP_OR_LATER      0x3002  ///< ��֧��xp���Ժ�ϵͳ




//////////////////////////////////////////////////////////////////////////
// Information
#define S_SKYLARK_CACHED_HASHED                         MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_CACHED_HASH)             ///< ...
#define S_SKYLARK_CACHED_LEVEL                          MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_CACHED_LEVEL)            ///< ...
#define S_SKYLARK_CACHED_WINTRUST                       MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_CACHED_WINTRUST)         ///< ...
#define S_SKYLARK_BWLIB_LEVEL                           MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_BWLIB_LEVEL)             ///< ...

#define S_SKYLARK_WIN_TRUST_FILE                        MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_WIN_TRUST_FILE)          ///< ...
#define S_SKYLARK_NON_PE_FILE                           MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_NON_PE_FILE)             ///< ...
#define S_SKYLARK_IS_SFC_PROTECTED                      MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_IS_SFC_PROTECTED)        ///< ...
#define S_SKYLARK_TRUSTED_INSTALLER                     MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_TRUSTED_INSTALLER)       ///< ...
#define S_SKYLARK_NON_EXE_FILE                          MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_NON_EXE_FILE)            ///< ...

#define S_SKYLARK_TOO_LARGE_FILE                        MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_TOO_LARGE_FILE)          ///< ...
#define S_SKYLARK_TOO_SMALL_FILE                        MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_TOO_SMALL_FILE)          ///< ...
#define S_SKYLARK_EMPTY_FILE                            MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_EMPTY_FILE)              ///< ...

#define S_SKYLARK_PENDING_SCAN                          MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_PENDING_SCAN)            ///< ...
#define S_SKYLARK_NO_NEED_TO_UPLOAD                     MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_NO_NEED_TO_UPLOAD)       ///< ...

#define S_SKYLARK_B3A_SCAN                              MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_B3A_SCAN)                ///< ...

#define S_SKYLARK_REQUIRED_SKIP                         MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_REQUIRED_SKIP)             ///< ...

#define S_SKYLARK_OVERWRITE_INFECTED_SYS_FILE           MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_OVERWRITE_INFECTED_SYS_FILE) ///< ...

#define S_SKYLARK_REMOVE_RECYCLE_FILE_NEED_REBOOT       MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_REMOVE_RECYCLE_FILE_NEED_REBOOT)     ///< ...
#define S_SKYLARK_REMOVE_ORIGINAL_FILE_NEED_REBOOT      MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_REMOVE_ORIGINAL_FILE_NEED_REBOOT)    ///< ...
#define S_SKYLARK_BOOTCLEAN_RECYCLE_FILE_NEED_REBOOT    MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_BOOTCLEAN_RECYCLE_FILE_NEED_REBOOT)              ///< ...
#define S_SKYLARK_BOOTCLEAN_ORIGINAL_FILE_NEED_REBOOT   MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_BOOTCLEAN_ORIGINAL_FILE_NEED_REBOOT)             ///< ...

#define S_SKYLARK_CAN_NOT_REPLACE_DIRECTORY                     MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_CAN_NOT_REPLACE_DIRECTORY)                   ///< ...
#define S_SKYLARK_REPLACE_FILE_NEED_REBOOT                      MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_REPLACE_FILE_NEED_REBOOT)                    ///< ...
#define S_SKYLARK_COPY_FOR_REPLACE                              MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_COPY_FOR_REPLACE)                            ///< ...
//#define S_SKYLARK_FAILED_TO_REBOOT_REPLACE_FILE                 MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_FAILED_TO_REBOOT_REPLACE_FILE)               ///< ...
#define S_SKYLARK_REPLACE_FILE_BUT_FAILED_TO_DELETE_RECYCLE     MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_REPLACE_FILE_BUT_FAILED_TO_DELETE_RECYCLE)   ///< ...
#define S_SKYLARK_REPLACE_FILE_NEED_REBOOT_DELETE_RECYCLE       MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_REPLACE_FILE_NEED_REBOOT_DELETE_RECYCLE)     ///< ...


#define S_SKYLARK_SFM_NEED_REBOOT                               MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_SFM_NEED_REBOOT)                             ///< ...


#define S_SKYLARK_ONLY_SUPPORTED_ON_X86                 MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_ONLY_SUPPORTED_ON_X86)               ///< ...
#define S_SKYLARK_ONLY_SUPPORTED_ON_WINXP_OR_LATER      MAKE_SKYLARK_SUCCESS(ERROR_SKYLARK_ONLY_SUPPORTED_ON_WINXP_OR_LATER)    ///< ...








//////////////////////////////////////////////////////////////////////////
// Error
#define E_SKYLARK_RSP_NO_FILE_LEVEL                     MAKE_SKYLARK_ERROR(ERROR_SKYLARK_RSP_NO_FILE_LEVEL)          ///< ...
#define E_SKYLARK_RSP_NO_PROCESS_LEVEL                  MAKE_SKYLARK_ERROR(ERROR_SKYLARK_RSP_NO_PROCESS_LEVEL)       ///< ...
#define E_SKYLARK_NO_FILES_BE_HASHED                    MAKE_SKYLARK_ERROR(ERROR_SKYLARK_NO_FILES_BE_HASHED)        ///< ...
#define E_SKYLARK_NO_PROCESSES_BE_HASHED                MAKE_SKYLARK_ERROR(ERROR_SKYLARK_NO_PROCESSES_BE_HASHED)    ///< ...


/// Э��Ļظ���������
#define E_SKYLARK_QUERY_FILE_RSP_ERROR                  MAKE_SKYLARK_ERROR(ERROR_SKYLARK_QUERY_FILE_RSP_ERROR)      ///< ...
#define E_SKYLARK_UPLOAD_FILE_RSP_ERROR                 MAKE_SKYLARK_ERROR(ERROR_SKYLARK_UPLOAD_FILE_RSP_ERROR)     ///< ...
#define E_SKYLARK_QUERY_PROCESS_RSP_ERROR               MAKE_SKYLARK_ERROR(ERROR_SKYLARK_QUERY_PROCESS_RSP_ERROR)   ///< ...
#define E_SKYLARK_UPLOAD_PROCESS_RSP_ERROR              MAKE_SKYLARK_ERROR(ERROR_SKYLARK_UPLOAD_PROCESS_RSP_ERROR)  ///< ...
#define E_SKYLARK_QUERY_SYSTEM_RSP_ERROR                MAKE_SKYLARK_ERROR(ERROR_SKYLARK_QUERY_SYSTEM_RSP_ERROR)    ///< ...
#define E_SKYLARK_UPLOAD_SYSTEM_RSP_ERROR               MAKE_SKYLARK_ERROR(ERROR_SKYLARK_UPLOAD_SYSTEM_RSP_ERROR)   ///< ...

/// Э��ļӽ��ܴ���
#define E_SKYLARK_CMD_ENCRYPT_ERROR                     MAKE_SKYLARK_ERROR(ERROR_SKYLARK_CMD_ENCRYPT_ERROR)         ///< ...
#define E_SKYLARK_RSP_DECRYPT_ERROR                     MAKE_SKYLARK_ERROR(ERROR_SKYLARK_RSP_DECRYPT_ERROR)         ///< ...
#define E_SKYLARK_RSP_CORRUPT_ERROR                     MAKE_SKYLARK_ERROR(ERROR_SKYLARK_RSP_CORRUPT_ERROR)         ///< ...

#define E_SKYLARK_CACHED_WINTRUST                       MAKE_SKYLARK_ERROR(ERROR_SKYLARK_CACHED_WINTRUST)           ///< ...

#define E_SKYLARK_WIN_TRUST_FILE                        MAKE_SKYLARK_ERROR(ERROR_SKYLARK_WIN_TRUST_FILE)            ///< ...
#define E_SKYLARK_NON_PE_FILE                           MAKE_SKYLARK_ERROR(ERROR_SKYLARK_NON_PE_FILE)               ///< ...
#define E_SKYLARK_IS_SFC_PROTECTED                      MAKE_SKYLARK_ERROR(ERROR_SKYLARK_IS_SFC_PROTECTED)          ///< ...
#define E_SKYLARK_TRUSTED_INSTALLER                     MAKE_SKYLARK_ERROR(ERROR_SKYLARK_TRUSTED_INSTALLER)         ///< ...
#define E_SKYLARK_NON_EXE_FILE                          MAKE_SKYLARK_ERROR(ERROR_SKYLARK_NON_EXE_FILE)              ///< ...

#define E_SKYLARK_PENDING_SCAN                          MAKE_SKYLARK_ERROR(ERROR_SKYLARK_PENDING_SCAN)              ///< ...


#define E_SKYLARK_TOO_LARGE_FILE                        MAKE_SKYLARK_ERROR(ERROR_SKYLARK_TOO_LARGE_FILE)            ///< ...
#define E_SKYLARK_TOO_SMALL_FILE                        MAKE_SKYLARK_ERROR(ERROR_SKYLARK_TOO_SMALL_FILE)            ///< ...
#define E_SKYLARK_EMPTY_FILE                            MAKE_SKYLARK_ERROR(ERROR_SKYLARK_EMPTY_FILE)                ///< ...

#define E_SKYLARK_B3A_NO_NEED_TO_FIX                    MAKE_SKYLARK_ERROR(ERROR_SKYLARK_B3A_NO_NEED_TO_FIX)        ///< ...
#define E_SKYLARK_B3A_FAILED_TO_FIX                     MAKE_SKYLARK_ERROR(ERROR_SKYLARK_B3A_FAILED_TO_FIX)         ///< ...

#define E_SKYLARK_LEVEL_CAN_NOT_CLEAN                   MAKE_SKYLARK_ERROR(ERROR_SKYLARK_LEVEL_CAN_NOT_CLEAN)       ///< ...

#define E_SKYLARK_CAN_NOT_REMOVE_DIRECTORY              MAKE_SKYLARK_ERROR(ERROR_SKYLARK_CAN_NOT_REMOVE_DIRECTORY)              ///< ...
#define E_SKYLARK_REMOVE_RECYCLE_FILE_NEED_REBOOT       MAKE_SKYLARK_ERROR(ERROR_SKYLARK_REMOVE_RECYCLE_FILE_NEED_REBOOT)       ///< ...
#define E_SKYLARK_REMOVE_ORIGINAL_FILE_NEED_REBOOT      MAKE_SKYLARK_ERROR(ERROR_SKYLARK_REMOVE_ORIGINAL_FILE_NEED_REBOOT)      ///< ...
#define E_SKYLARK_BOOTCLEAN_RECYCLE_FILE_NEED_REBOOT    MAKE_SKYLARK_ERROR(ERROR_SKYLARK_BOOTCLEAN_RECYCLE_FILE_NEED_REBOOT)    ///< ...
#define E_SKYLARK_BOOTCLEAN_ORIGINAL_FILE_NEED_REBOOT   MAKE_SKYLARK_ERROR(ERROR_SKYLARK_BOOTCLEAN_ORIGINAL_FILE_NEED_REBOOT)   ///< ...

#define E_SKYLARK_CAN_NOT_REPLACE_DIRECTORY                     MAKE_SKYLARK_ERROR(ERROR_SKYLARK_CAN_NOT_REPLACE_DIRECTORY)                     ///< ...
#define E_SKYLARK_REPLACE_FILE_NEED_REBOOT                      MAKE_SKYLARK_ERROR(ERROR_SKYLARK_REPLACE_FILE_NEED_REBOOT)                      ///< ...
#define E_SKYLARK_COPY_FOR_REPLACE                              MAKE_SKYLARK_ERROR(ERROR_SKYLARK_COPY_FOR_REPLACE)                              ///< ...
#define E_SKYLARK_FAILED_TO_REBOOT_REPLACE_FILE                 MAKE_SKYLARK_ERROR(ERROR_SKYLARK_FAILED_TO_REBOOT_REPLACE_FILE)                 ///< ...
#define E_SKYLARK_FAILED_TO_REBOOT_REPLACE_FILE                 MAKE_SKYLARK_ERROR(ERROR_SKYLARK_FAILED_TO_REBOOT_REPLACE_FILE)                 ///< ...
#define E_SKYLARK_REPLACE_FILE_BUT_FAILED_TO_DELETE_RECYCLE     MAKE_SKYLARK_ERROR(ERROR_SKYLARK_REPLACE_FILE_BUT_FAILED_TO_DELETE_RECYCLE)     ///< ...
#define E_SKYLARK_REPLACE_FILE_NEED_REBOOT_DELETE_RECYCLE       MAKE_SKYLARK_ERROR(ERROR_SKYLARK_REPLACE_FILE_NEED_REBOOT_DELETE_RECYCLE)       ///< ...




#define E_SKYLARK_SFM_LOCAL_DOWNLOAD_NOT_MATCH                  MAKE_SKYLARK_ERROR(ERROR_SKYLARK_SFM_LOCAL_DOWNLOAD_NOT_MATCH)          ///< ...
#define E_SKYLARK_SFM_MISSING_URL_DATA                          MAKE_SKYLARK_ERROR(ERROR_SKYLARK_SFM_MISSING_URL_DATA)                  ///< ...
#define E_SKYLARK_SFM_MISSING_INDEX_DATA                        MAKE_SKYLARK_ERROR(ERROR_SKYLARK_SFM_MISSING_INDEX_DATA)                ///< ...
#define E_SKYLARK_SFM_MISSING_MODULE_IN_INDEX                   MAKE_SKYLARK_ERROR(ERROR_SKYLARK_SFM_MISSING_MODULE_IN_INDEX)           ///< ...
#define E_SKYLARK_SFM_MISSING_ENTRY                             MAKE_SKYLARK_ERROR(ERROR_SKYLARK_SFM_MISSING_ENTRY)                     ///< ...
#define E_SKYLARK_SFM_INVALID_URL_DATA                          MAKE_SKYLARK_ERROR(ERROR_SKYLARK_SFM_INVALID_URL_DATA)                  ///< ...
#define E_SKYLARK_SFM_INVALID_INDEX_DATA                        MAKE_SKYLARK_ERROR(ERROR_SKYLARK_SFM_INVALID_INDEX_DATA)                ///< ...
#define E_SKYLARK_SFM_DOWNLOAD_FILE_MISMATCH                    MAKE_SKYLARK_ERROR(ERROR_SKYLARK_SFM_DOWNLOAD_FILE_MISMATCH)            ///< ...
#define E_SKYLARK_SFM_FILE_NOT_IN_THIS_OS                       MAKE_SKYLARK_ERROR(ERROR_SKYLARK_SFM_FILE_NOT_IN_THIS_OS)               ///< ...

#define E_SKYLARK_SCSAPI_FAILED_TO_CALL_COPY_FILE               MAKE_SKYLARK_ERROR(ERROR_SKYLARK_SCSAPI_FAILED_TO_CALL_COPY_FILE)       ///< ...
#define E_SKYLARK_SCSAPI_FAILED_TO_CALL_DELETE_FILE             MAKE_SKYLARK_ERROR(ERROR_SKYLARK_SCSAPI_FAILED_TO_CALL_DELETE_FILE)     ///< ...
#define E_SKYLARK_SCSAPI_FAILED_TO_CALL_FILE_EXIST              MAKE_SKYLARK_ERROR(ERROR_SKYLARK_SCSAPI_FAILED_TO_CALL_FILE_EXIST)      ///< ...


#define E_SKYLARK_ONLY_SUPPORTED_ON_X86                         MAKE_SKYLARK_ERROR(ERROR_SKYLARK_ONLY_SUPPORTED_ON_X86)                 ///< ...
#define E_SKYLARK_ONLY_SUPPORTED_ON_WINXP_OR_LATER              MAKE_SKYLARK_ERROR(ERROR_SKYLARK_ONLY_SUPPORTED_ON_WINXP_OR_LATER)      ///< ...


#define E_SKYLARK_BACKUP_FAILED_TO_DELETE_NONNULL_DIRECTORY     MAKE_SKYLARK_ERROR(ERROR_SKYLARK_BACKUP_FAILED_TO_REPLACE_NONNULL_DIRECTORY)    ///< ...
#define E_SKYLARK_BACKUP_FAILED_TO_ALL_DELETE                   MAKE_SKYLARK_ERROR(ERROR_SKYLARK_BACKUP_FAILED_TO_ALL_DELETE)                   ///< ...
#define E_SKYLARK_BACKUP_FAILED_TO_FIND_SPECI_FILE              MAKE_SKYLARK_ERROR(ERROR_SKYLARK_BACKUP_FAILED_TO_FIND_SPECI_FILE)              ///< ...
#define E_SKYLARK_BACKUP_NO_MORE_DISK_SPACE                     MAKE_SKYLARK_ERROR(ERROR_SKYLARK_BACKUP_NO_MORE_DISK_SPACE)                     ///< ...

#define E_SKYLARK_RETRIEVE_FAILED_TO_OVERWRITE_DIRECTORY        MAKE_SKYLARK_ERROR(ERROR_SKYLARK_RETRIEVE_FAILED_TO_OVERWRITE_DIRECTORY)        ///< ...
#define E_SKYLARK_RETRIEVE_FAILED_TO_OVERWRITE_FILE             MAKE_SKYLARK_ERROR(ERROR_SKYLARK_RETRIEVE_FAILED_TO_OVERWRITE_FILE)             ///< ...
#define E_SKYLARK_RETRIEVE_MISSING_BACKUP_FILE                  MAKE_SKYLARK_ERROR(ERROR_SKYLARK_RETRIEVE_MISSING_BACKUP_FILE)                  ///< ...
#define E_SKYLARK_RETRIEVE_FAILED_TO_EXTRACT_FILE               MAKE_SKYLARK_ERROR(ERROR_SKYLARK_RETRIEVE_FAILED_TO_EXTRACT_FILE)               ///< ...
#define E_SKYLARK_RETRIEVE_FAILED_TO_EXTRACT_BACKUP_INFO        MAKE_SKYLARK_ERROR(ERROR_SKYLARK_RETRIEVE_FAILED_TO_EXTRACT_BACKUP_INFO)        ///< ...
#define E_SKYLARK_RETRIEVE_FAILED_TO_REPLACE_FILE               MAKE_SKYLARK_ERROR(ERROR_SKYLARK_RETRIEVE_FAILED_TO_REPLACE_FILE)               ///< ...


//////////////////////////////////////////////////////////////////////////
// end of skylark
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
// skylark server
//////////////////////////////////////////////////////////////////////////

#define ERROR_SLPTL_G_RET_SUCCESS                   0       ///< �ɹ�
#define ERROR_SLPTL_G_RET_ERR_OUT_OF_SERVICE        1       ///< ��������ͣ����(��·����)
#define ERROR_SLPTL_G_RET_ERR_PARAM                 2       ///< ��������

// >=100:�������ڲ�����(���ö��û���������)
#define ERROR_SLPTL_G_RET_ERR_SVR_GENERAL           100    ///< һ���Է���������
#define ERROR_SLPTL_G_RET_ERR_SVR_COMMUNICATION     101    ///< ���������������
#define ERROR_SLPTL_G_RET_ERR_SVR_DB                102    ///< ���ݿ����
#define ERROR_SLPTL_G_RET_ERR_SVR_CACHE             103    ///< �������
#define ERROR_SLPTL_G_RET_ERR_SVR_HTTP_SERVER       104    ///< IIS����
#define ERROR_SLPTL_G_RET_ERR_SVR_LOGIC             105    ///< �߼�����

//////////////////////////////////////////////////////////////////////////
// endof skylark server
//////////////////////////////////////////////////////////////////////////







//////////////////////////////////////////////////////////////////////////
// BKEng
//////////////////////////////////////////////////////////////////////////
// �����������
#define ERROR_BKE_MODULE_IS_TOO_NEW                         0x0001  ///< ����汾̫�� (����İ汾��̫��)
#define ERROR_BKE_MODULE_IS_TOO_OLD                         0x0002  ///< ����汾̫�� (����İ汾��̫��)
#define ERROR_BKE_AVENGINE_IS_NOT_VALID                     0x0003  ///< �ļ����治����(����ʹ��������)

// �ļ���������
#define ERROR_KSE_COPY_INTERRUPTED                          0x0101
#define ERROR_KSE_FAILED_TO_OBTAIN_WRITABLE_KS_FILE         0x0102
#define ERROR_KSE_TOO_DEEP_EXTRACT                          0x0103  ///< ѹ�����̫��
#define ERROR_KSE_TOO_DEEP_UNPACK                           0x0104  ///< �ѿǲ��̫��

// �ڰ׻�
#define ERROR_KSE_BWM_CLEAN_FAILED_TO_CREATE_TEMP_FILE      0x0201
#define ERROR_KSE_BWM_NEED_DELETE_FILE                      0x0202
#define ERROR_KSE_BWM_FAILED_TO_SCAN_WHILE_RECLEAN          0x0203
#define ERROR_KSE_BWM_TOO_MANY_RECLEAN_ATTEMPT              0x0204
#define ERROR_KSE_BWM_FAILED_TO_CLEAN_WHILE_RECLEAN         0x0205
#define ERROR_KSE_BWM_CLEAN_RETURN_NO_VIRUS                 0x0206
#define ERROR_KSE_BWM_SKIP_TYPE_BY_SETTINGS                 0x0207
#define ERROR_KSE_BWM_CACHED_RESULT                         0x0208

// ��ѹ��
#define ERROR_KSE_ARC_FAILED_TO_CLEAN_VIRUS_IN_ARCHIVE      0x0301

// �ѿ�

// �Ʋ�ɱ����

// ��������
#define ERROR_BKE_DELETE_FILE_NEED_REBOOT                   0x0601  ///< ɾ���ļ�����Ҫ����
#define ERROR_BKE_REPLACE_FILE_NEED_REBOOT                  0x0602  ///< �滻�ļ�����Ҫ����
#define ERROR_BKE_CLEAN_NON_VIRUS                           0x0603  ///< �����������ǲ����ļ�
#define ERROR_BKE_CLEAN_SFM_MISSING_INDEX                   0x0604  ///< ���������Ҳ���ϵͳ�ļ����޸���Ϣ
#define ERROR_BKE_FAILED_TO_FIX_CRITICAL_FILE               0x0605  ///< �޸�ϵͳ�ؼ��ļ���ʱ��ʧ��

// ����������
#define ERROR_BKE_SIGN_FILE_CRC_MISMATCH                    0x0701  ///< �ļ�CRCУ��ʧ��
#define ERROR_BKE_SIGN_FILE_TOO_LARGE                       0x0702  ///< �����ļ�����
#define ERROR_BKE_SIGN_FILE_MISSING_IN_INDEX                0x0703  ///< ������û���ҵ������ļ�����Ϣ

#define ERROR_BKE_SIGN_FILE_FAILED_TO_CALL_KSMERGE_INIT     0x0710  ///< ksmerge.dll::init ʧ��
#define ERROR_BKE_SIGN_FILE_FAILED_TO_CALL_KSMERGE_CHECK    0x0711  ///< ksmerge.dll::check ʧ��
#define ERROR_BKE_SIGN_FILE_FAILED_TO_CALL_KSMERGE_MERGE    0x0712  ///< ksmerge.dll::merge ʧ��
#define ERROR_BKE_SIGN_FILE_FAILED_TO_CALL_KSMERGE_CREATE   0x0713  ///< ksmerge.dll::create ʧ��

#define ERROR_BKE_SIGN_FILE_FAILED_TO_UNCOMPRESS_FILE       0x0720  ///< ��ѹ�ļ�ʧ��


//////////////////////////////////////////////////////////////////////////
// error
#define E_BKE_MODULE_IS_TOO_NEW                             MAKE_BKENG_ERROR(ERROR_BKE_MODULE_IS_TOO_NEW)
#define E_BKE_MODULE_IS_TOO_OLD                             MAKE_BKENG_ERROR(ERROR_BKE_MODULE_IS_TOO_OLD)

#define E_KSE_COPY_INTERRUPTED_X                            MAKE_BKENG_ERROR(ERROR_KSE_COPY_INTERRUPTED)
#define E_KSE_FAILED_TO_OBTAIN_WRITABLE_KS_FILE             MAKE_BKENG_ERROR(ERROR_KSE_FAILED_TO_OBTAIN_WRITABLE_KS_FILE)

#define E_KSE_BWM_CLEAN_FAILED_TO_CREATE_TEMP_FILE          MAKE_BKENG_ERROR(ERROR_KSE_BWM_CLEAN_FAILED_TO_CREATE_TEMP_FILE)
#define E_KSE_BWM_NEED_DELETE_FILE                          MAKE_BKENG_ERROR(ERROR_KSE_BWM_NEED_DELETE_FILE)
#define E_KSE_BWM_FAILED_TO_SCAN_WHILE_RECLEAN              MAKE_BKENG_ERROR(ERROR_KSE_BWM_FAILED_TO_SCAN_WHILE_RECLEAN)
#define E_KSE_BWM_TOO_MANY_RECLEAN_ATTEMPT                  MAKE_BKENG_ERROR(ERROR_KSE_BWM_TOO_MANY_RECLEAN_ATTEMPT)
#define E_KSE_BWM_FAILED_TO_CLEAN_WHILE_RECLEAN             MAKE_BKENG_ERROR(ERROR_KSE_BWM_FAILED_TO_CLEAN_WHILE_RECLEAN)
#define E_KSE_BWM_CLEAN_RETURN_NO_VIRUS                     MAKE_BKENG_ERROR(ERROR_KSE_BWM_CLEAN_RETURN_NO_VIRUS)

#define E_KSE_ARC_FAILED_TO_CLEAN_VIRUS_IN_ARCHIVE          MAKE_BKENG_ERROR(ERROR_KSE_ARC_FAILED_TO_CLEAN_VIRUS_IN_ARCHIVE)
#define E_BKE_CLEAN_NON_VIRUS                               MAKE_BKENG_ERROR(ERROR_BKE_CLEAN_NON_VIRUS)
#define E_BKE_CLEAN_SFM_MISSING_INDEX                       MAKE_BKENG_ERROR(ERROR_BKE_CLEAN_SFM_MISSING_INDEX)
#define E_BKE_FAILED_TO_FIX_CRITICAL_FILE                   MAKE_BKENG_ERROR(ERROR_BKE_FAILED_TO_FIX_CRITICAL_FILE)

#define E_BKE_SIGN_FILE_CRC_MISMATCH                        MAKE_BKENG_ERROR(ERROR_BKE_SIGN_FILE_CRC_MISMATCH)
#define E_BKE_SIGN_FILE_TOO_LARGE                           MAKE_BKENG_ERROR(ERROR_BKE_SIGN_FILE_TOO_LARGE)
#define E_BKE_SIGN_FILE_MISSING_IN_INDEX                    MAKE_BKENG_ERROR(ERROR_BKE_SIGN_FILE_MISSING_IN_INDEX)

#define E_BKE_SIGN_FILE_FAILED_TO_CALL_KSMERGE_INIT         MAKE_BKENG_ERROR(ERROR_BKE_SIGN_FILE_FAILED_TO_CALL_KSMERGE_INIT)
#define E_BKE_SIGN_FILE_FAILED_TO_CALL_KSMERGE_CHECK        MAKE_BKENG_ERROR(ERROR_BKE_SIGN_FILE_FAILED_TO_CALL_KSMERGE_CHECK)
#define E_BKE_SIGN_FILE_FAILED_TO_CALL_KSMERGE_MERGE        MAKE_BKENG_ERROR(ERROR_BKE_SIGN_FILE_FAILED_TO_CALL_KSMERGE_MERGE)
#define E_BKE_SIGN_FILE_FAILED_TO_CALL_KSMERGE_CREATE       MAKE_BKENG_ERROR(ERROR_BKE_SIGN_FILE_FAILED_TO_CALL_KSMERGE_CREATE)

#define E_BKE_SIGN_FILE_FAILED_TO_UNCOMPRESS_FILE           MAKE_BKENG_ERROR(ERROR_BKE_SIGN_FILE_FAILED_TO_UNCOMPRESS_FILE)



//////////////////////////////////////////////////////////////////////////
// info
#define S_BKE_AVENGINE_IS_NOT_VALID                         MAKE_BKENG_SUCCESS(ERROR_BKE_AVENGINE_IS_NOT_VALID)

#define S_KSE_BWM_SKIP_TYPE_BY_SETTINGS                     MAKE_BKENG_SUCCESS(ERROR_KSE_BWM_SKIP_TYPE_BY_SETTINGS)
#define S_KSE_TOO_DEEP_EXTRACT                              MAKE_BKENG_SUCCESS(ERROR_KSE_TOO_DEEP_EXTRACT)                          
#define S_KSE_TOO_DEEP_UNPACK                               MAKE_BKENG_SUCCESS(ERROR_KSE_TOO_DEEP_UNPACK)

#define S_KSE_BWM_CACHED_RESULT                             MAKE_BKENG_SUCCESS(ERROR_KSE_BWM_CACHED_RESULT)

#define S_BKE_DELETE_FILE_NEED_REBOOT                       MAKE_BKENG_SUCCESS(ERROR_BKE_DELETE_FILE_NEED_REBOOT)
#define S_BKE_REPLACE_FILE_NEED_REBOOT                      MAKE_BKENG_SUCCESS(ERROR_BKE_REPLACE_FILE_NEED_REBOOT)

//////////////////////////////////////////////////////////////////////////
// end of kse
//////////////////////////////////////////////////////////////////////////




#endif//BKERROR_H