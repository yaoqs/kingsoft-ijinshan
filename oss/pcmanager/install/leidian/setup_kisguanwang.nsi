

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

!define PRODUCT_PARTNER "O_KISGUANWANG"                      				;��������
!define PRODUCT_OUT_FILE "..\..\product\package\setup_kisguanwang.exe"        ;���ɰ�װ��������
!define MACRO_CFG_PATH  "cfg"							;����Ŀ¼������
!define PRODUCT_WITH_KENG                           1
!define WRITE_TRAY_REG_RUN      1      ;�Ƿ�дtray��������
;!define FORCE_SILENT_INST       1      ;�Ƿ�ǿ�ƾ�Ĭ��װ

!include "leidian_install.nsh"

