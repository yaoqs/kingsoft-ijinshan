

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

!define PRODUCT_PARTNER  "O_WD_WEB"                                      ;��������
!define PRODUCT_OUT_FILE "..\..\product\package\setup_wd_web.exe"          ;���ɰ�װ��������
!define MACRO_CFG_PATH  "cfg"							;����Ŀ¼������
!define PRODUCT_WITH_KENG                           1
!define WRITE_TRAY_REG_RUN 1
!include "leidian_install.nsh"

