

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

!define PRODUCT_PARTNER "h_homefull"                      ;��������
!define PRODUCT_OUT_FILE "..\..\product\package\setup_full.exe"          ;���ɰ�װ��������
!define PRODUCT_WITH_KENG                           1

!include "leidian_install.nsh"

