

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

!define PRODUCT_PARTNER  "O_THUNDER_WEB"                                      ;��������
!define PRODUCT_OUT_FILE "..\..\product\package\setup_thunder_web.exe"          ;���ɰ�װ��������
!define MACRO_CFG_PATH  "cfg_enable_mon_skylark_set_homepage"
!define WRITE_TRAY_REG_RUN 1


!include "leidian_install.nsh"

