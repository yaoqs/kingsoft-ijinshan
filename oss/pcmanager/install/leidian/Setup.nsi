

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

!define PRODUCT_PARTNER "h_home"                      				;��������
!define PRODUCT_OUT_FILE "..\..\product\package\setup_${AUTO_FILE_VERSION}.exe"        ;���ɰ�װ��������
!define MACRO_CFG_PATH  "cfg"							;����Ŀ¼������
!define PRODUCT_WITH_KENG                           1
!define WRITE_TRAY_REG_RUN      1      ;�Ƿ�дtray��������
;!define FORCE_SILENT_INST       1      ;�Ƿ�ǿ�ƾ�Ĭ��װ

!include "leidian_install.nsh"

