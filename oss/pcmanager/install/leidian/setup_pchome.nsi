

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

!define PRODUCT_PARTNER  "O_PCHOME"                      ;��������
!define PRODUCT_OUT_FILE "..\..\product\package\setup_pchome.exe"          ;���ɰ�װ��������

!include "leidian_install.nsh"

