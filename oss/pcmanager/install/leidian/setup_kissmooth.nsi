

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

!define PRODUCT_PARTNER  "O_kissmooth"                      ;��������
!define PRODUCT_OUT_FILE "..\..\product\package\setup_kissmooth.exe"          ;���ɰ�װ��������
!define MACRO_CFG_PATH  "cfg_enable_mon_skylark"
!define WRITE_TRAY_REG_RUN 1
;!define SLIENT_INST_NO_REINSTALL        1
!define PRODUCT_WITH_KENG                           1

!define FORCE_SILENT_INST       1      ;�Ƿ�ǿ�ƾ�Ĭ��װ


!define WRITE_PID_SPECAIL_VALUE   1     ;�Ƿ���coop��ֵ��д�������PID���
!define SPECAIL_KEY_VALUE         "smark"   ; PID �����ǵ�����
!define SPECAIL_KEY_VALUE_DATA    1001  		; PID �����Ǽ���ֵ


!include "leidian_install.nsh"

