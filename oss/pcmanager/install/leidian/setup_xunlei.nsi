

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

!define PRODUCT_PARTNER  "O_XUNLEI"                                      ;��������
!define PRODUCT_OUT_FILE "..\..\product\package\setup_xunlei.exe"          ;���ɰ�װ��������
!define MACRO_CFG_PATH  "cfg_enable_mon_skylark"
!define WRITE_TRAY_REG_RUN 1


!include "leidian_install.nsh"

