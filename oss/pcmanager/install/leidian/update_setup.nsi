

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

!define PRODUCT_PARTNER  "h_update"                      ;��������
!define PRODUCT_OUT_FILE "..\..\product\package\setup_update.exe"       ;���ɰ�װ��������
!define PRODUCT_UPDATE   "1"                           ;������
!define PRODUCT_WITH_KENG "1"
!define WRITE_TRAY_REG_RUN      1      ;�Ƿ�дtray��������
!include "leidian_install.nsh"

