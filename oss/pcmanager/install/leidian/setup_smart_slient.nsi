

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

!define PRODUCT_PARTNER  "O_SMART_ERROR"                                      ;��������
!define PRODUCT_OUT_FILE "...\..\product\package\setup_pid_ssssssss.exe"          ;���ɰ�װ��������
!define MACRO_CFG_PATH  "cfg_enable_mon_skylark"
!define WRITE_TRAY_REG_RUN 1
!define PRODUCT_WITH_KENG                           1

!define USE_NAME_AS_PARTER 1
!define FORCE_SILENT_INST       1      ;�Ƿ�ǿ�ƾ�Ĭ��װ

!include "leidian_install.nsh"

