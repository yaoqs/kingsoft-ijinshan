

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

!define PRODUCT_PARTNER  "O_KNSD"                      ;��������
!define PRODUCT_OUT_FILE "..\..\product\package\setup_knsd.exe"          ;���ɰ�װ��������
!define MACRO_CFG_PATH  "cfg_enable_mon_skylark"
!define WRITE_TRAY_REG_RUN 1
;!define SLIENT_INST_NO_REINSTALL        1
!define PRODUCT_WITH_KENG                           1
!include "leidian_install.nsh"

