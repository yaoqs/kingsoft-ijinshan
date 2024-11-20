; �ýű�ʹ�� HM VNISEdit �ű��༭���򵼲���

!include "LogicLib.nsh"
!include "FileFunc.nsh"

; ��װ�����ʼ���峣��
!define PRODUCT_NAME "��ɽ��ʿV10����"
!define PRODUCT_PUBLISHER "��ɽ��ʿV10����"
!define PRODUCT_WEB_SITE "http://www.ijinshan.com"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_VERSION "1.1��"
!define PRODUCT_ENG_MARK  "SOFTWARE\KSafe\KEng"
!define PRODUCT_ENG_MARK_VALUE  "Install"       ; ��װ������� Enable ���޸�Ϊ Install

!define FILE_VER     		${AUTO_FILE_VERSION}

SetCompressor /SOLID lzma

; ------ MUI �ִ����涨�� (1.67 �汾���ϼ���) ------
!include "MUI.nsh"


!define REGKEY_PRODUCT         "Software\KSafe"
!define REGVAL_INSTALL         "Install Path"         ; �ǵ��޸�InstallDirRegKey, by bbcallen

;//Our nsh
!addincludedir "..\common\"
!addplugindir "..\common\"

!include "defines.nsh"
!include "MyFileEx.nsh"
!include "MyUpgradeDLL.nsh"
!include "Http.nsh"
!include "commfunc.nsh"
!include "StrFunc.nsh"
!include "cmdLine.nsh"

; MUI Ԥ���峣��
!define MUI_ABORTWARNING
!define MUI_ICON "res\Install.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "res\InstallWelCome.bmp"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "res\InstallWelCome.bmp"
!define MUI_UNICON "res\uninstall.ico"

; ��װ������������
InstallDirRegKey HKLM "SOFTWARE\KSafe" "Install Path"
; ��ӭҳ��
!insertmacro MUI_PAGE_WELCOME

; ��װ����ҳ��
!insertmacro MUI_PAGE_INSTFILES

; ��װ���ҳ��
!insertmacro MUI_PAGE_FINISH

; ж�ع���ҳ��
!insertmacro MUI_UNPAGE_INSTFILES
; ж�����ҳ��
!insertmacro MUI_UNPAGE_FINISH

; ��װ�����������������
!insertmacro MUI_LANGUAGE "SimpChinese"

; ��װԤ�ͷ��ļ�
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI �ִ����涨����� ------

RequestExecutionLevel admin

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "${PRODUCT_OUT_FILE}"
InstallDir "$PROGRAMFILES\KSafe\KEng"
XPStyle on
ShowInstDetails nevershow
ShowUninstDetails nevershow
BrandingText "ijinshan.com"
Caption " ${PRODUCT_NAME} ${PRODUCT_VERSION} ��װ"

!include "keng_install_mainsection.nsh"

Section -Post
  WriteUninstaller "$INSTDIR\uninstkeng.exe"   ; ж�س���ת��KEng��Ŀ¼��, by bbcallen
  ; ��дж����
  ; WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  ; WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\KEng\uninstkeng.exe"  ; ͬ��
  ; WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  ; WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  ; WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

/******************************
 *  �����ǰ�װ�����ж�ز���  *
 ******************************/

Section Uninstall
  ;ж��ͳ��
  ;push $0
  ;ReadRegStr $0 HKEY_LOCAL_MACHINE "${REGKEY_PRODUCT}\Coop" "PreOEM"
  ;!insertmacro InternetGetCookie "stat.ijinshan.com" "/uninstallkeng.htm?pid=$0&ver=${FILE_VER}"
  ;pop $0

  !insertmacro DeleteFileEx "$INSTDIR\ksgmerge.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\ksignup.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\ksafeave.dll" "$INSTDIR"

  Delete /REBOOTOK "$INSTDIR\uninstkeng.exe"

  SetOutPath "$TEMP"
  RMDir /r "$INSTDIR"
  DeleteRegKey HKLM "${PRODUCT_ENG_MARK}"
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"

  SetAutoClose true
SectionEnd

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

Function GetKSafePathByCMD

  Strcpy $0 ""
  !insertmacro GETPARAMETERVALUE "/D2="
  pop $0
  
  ;MessageBox MB_OK $0
  ${if} $0 != ""
      Strcpy $1 "$0ksafever.dll"
      IfFileExists $1 0 label_out
      Strcpy $0 $0
      goto label_out_x
  label_out:
      Strcpy $0 "0"
  ${else}
      Strcpy $0 "0"
  ${endif}

  label_out_x:

FunctionEnd

Function GetInstalledLeidianPath
  push $1

  Strcpy $0 ""
  ReadRegStr $0 HKLM "${REGKEY_PRODUCT}" "${REGVAL_INSTALL}"
  ${if} $0 != ""
      Strcpy $1 "$0\ksafever.dll"
      IfFileExists $1 0 label_out
      Strcpy $0 $0
      goto label_out_x
  label_out:
      Strcpy $0 "0"
  ${else}
      Strcpy $0 "0"
  ${endif}
  
  label_out_x:
  pop $1
FunctionEnd

Function .onInit
  push $0
  
  Call GetKSafePathByCMD
  ${if} $0 == "0"
      Call GetInstalledLeidianPath
      ${if} $0 == "0"
          MessageBox MB_OK "��������û�а�װ��ɽ��ʿ�����Ȱ�װ��ɽ��ʿ!"
          quit
      ${endif}
  ${endif}
  StrCpy $INSTDIR "$0\KEng"
  pop $0
FunctionEnd

Function .onInstSuccess
FunctionEnd

Function un.onInit
FunctionEnd

Function un.onUninstSuccess
FunctionEnd

VIAddVersionKey  "ProductName" "��ɽ��ʿV10����"
VIAddVersionKey  "Comments" "��ɽ��ʿV10����"
VIAddVersionKey  "CompanyName" "��ɽ��ʿ"
VIAddVersionKey  "LegalTrademarks" "��ɽ��ʿ"
VIAddVersionKey  "LegalCopyright" "��Ȩ����(C) 2010 ��ɽ��ʿ"
VIAddVersionKey  "FileDescription" "��ɽ��ʿV10����"
VIAddVersionKey  "FileVersion" "${FILE_VER}"
VIAddVersionKey  "ProductVersion" "${FILE_VER}"
VIProductVersion "${FILE_VER}"
