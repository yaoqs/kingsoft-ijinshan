

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

!define PRODUCT_PARTNER "o_test"                      				;��������
!define PRODUCT_OUT_FILE "..\..\product\package\setup_${AUTO_FILE_VERSION}.exe"        ;���ɰ�װ��������
!define MACRO_CFG_PATH  "cfg"							;����Ŀ¼������
;!define WRITE_TRAY_REG_RUN      1      ;�Ƿ�дtray��������
;!define FORCE_SILENT_INST       1      ;�Ƿ�ǿ�ƾ�Ĭ��װ
!define BIND_WITH_OTHER_SOFTMGR  1
!define PATH_OTHER_SOFTMGR              "pattern\softmgr.exe"

!include "leidian_install.nsh"

