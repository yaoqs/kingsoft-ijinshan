

!system "if exist version.inc.nsi del version.inc.nsi"
!system "getver.exe ..\..\product\win32\ksafever.dll"
!include "version.inc.nsi"

;������Ե��ÿ�ܵ������Ѱ�

!define PRODUCT_PARTNER "O_JXSJMSG"                      				;��������
!define PRODUCT_OUT_FILE "..\..\product\package\setup_JXSJMSG.exe"        ;���ɰ�װ��������
!define MACRO_CFG_PATH  "cfg"							;����Ŀ¼������
!define PRODUCT_WITH_KENG                           1
!define WRITE_TRAY_REG_RUN      1      ;�Ƿ�дtray��������
!define JXSJ_MSG_TIP_TXT        "������Ե��  �Ƽ�����װ��ɽ��ʿ$\r$\n$\r$\n��Ϸ�����ѡ��ȫ�����ɱľ�������š���������    $\r$\n��Ϸ�˺źͲƲ���ȫ��������ѡ�ȷ����װ��"

!include "leidian_install.nsh"

