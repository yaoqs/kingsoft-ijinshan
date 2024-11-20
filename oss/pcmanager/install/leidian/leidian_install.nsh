; �ýű�ʹ�� HM VNISEdit �ű��༭���򵼲���

!include "LogicLib.nsh"
!include "FileFunc.nsh"
!include "WordFunc.nsh"

; ��װ�����ʼ���峣��
!define PRODUCT_NAME "��ɽ��ʿ"
!define CAPTION_NAME		"��ɽ��ʿ"
!define PRODUCT_PUBLISHER "��ɽ��ʿ"
!define PRODUCT_WEB_SITE "http://www.ijinshan.com"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define LEIDIAN_TRAY_AUTORUN	"KSafeTray"
!define KSAFE_PLUG_RUNONCE  "KSafeRebootPlugClean"

!ifndef  PRODUCT_UPDATE
  !define PRODUCT_VERSION     "${AUTO_FILE_VERSION} ��ʽ��"
  !define PRODUCT_VERSION_REG "${AUTO_FILE_VERSION} ��ʽ��"
!else
  !define PRODUCT_VERSION     "${AUTO_FILE_VERSION} ��ʽ��������"
  !define PRODUCT_VERSION_REG "${AUTO_FILE_VERSION} ��ʽ��"
!endif

!define PRODUCT_ENG_MARK  "SOFTWARE\KSafe\KEng"
!define PRODUCT_ENG_MARK_VALUE  "Install"       ; ��װ������� Enable ���޸�Ϊ Install


!define FILE_VER     		${AUTO_FILE_VERSION}

!define BIN_DIR         "..\..\product\win32"
SetCompressor /SOLID lzma

; ------ MUI �ִ����涨�� (1.67 �汾���ϼ���) ------
!include "MUI.nsh"


;//OUR DEFINE
!define REGKEY_PRODUCT         "Software\KSafe"
!define REGVAL_INSTALL         "Install Path"         ; �ǵ��޸�InstallDirRegKey
!define REG_KEY_UPDATE         "Software\KSafe\update"
!define REGKEY_COOP            "${REGKEY_PRODUCT}\Coop"


;//Our nsh
!addincludedir "..\common\"
!addPluginDir "..\common\"
!include "defines.nsh"
!include "MyFileEx.nsh"
!include "MyUpgradeDLL.nsh"
!include "Http.nsh"
!include "commfunc.nsh"
!include "winver.nsh"

!insertmacro GetDrives
!insertmacro un.GetDrives
!insertmacro GetFileName
!insertmacro un.GetFileName
!insertmacro un.DirState

; MUI Ԥ���峣��
!define MUI_ABORTWARNING
!define MUI_ICON "res\Install.ico"

!ifdef RES_WELCOME_BMP
		!define MUI_WELCOMEFINISHPAGE_BITMAP 		${RES_WELCOME_BMP}
		!define MUI_UNWELCOMEFINISHPAGE_BITMAP 	${RES_WELCOME_BMP}
!else
		!define MUI_WELCOMEFINISHPAGE_BITMAP "res\InstallWelCome.bmp"
		!define MUI_UNWELCOMEFINISHPAGE_BITMAP "res\InstallWelCome.bmp"
!endif

!define MUI_UNICON "res\uninstall.ico"

; ��װ������������
InstallDirRegKey HKLM "SOFTWARE\KSafe" "Install Path"
; ��ӭҳ��
!insertmacro MUI_PAGE_WELCOME
	
;�����������������ʾ����
!ifndef PRODUCT_UPDATE
	; ���Э��ҳ��
	!insertmacro MUI_PAGE_LICENSE "res\license.txt"
!endif

; ��װĿ¼ѡ��ҳ�Ƿ�����ѡ��Ŀ¼
!define MUI_PAGE_CUSTOMFUNCTION_PRE SelectDirPagePre
; ��װĿ¼ѡ��ҳ��
!insertmacro MUI_PAGE_DIRECTORY

; ��װ����ҳ��
!insertmacro MUI_PAGE_INSTFILES

; ��װ���ҳ��

!define MUI_FINISHPAGE_RUN "$INSTDIR\KSafe.exe"

!define MUI_PAGE_CUSTOMFUNCTION_PRE   FinishPagePre
!define MUI_PAGE_CUSTOMFUNCTION_SHOW   FinishPageShow
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE FinishPageLeave
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

Name "${CAPTION_NAME}${PRODUCT_VERSION_REG}"
OutFile "${PRODUCT_OUT_FILE}"
InstallDir "$PROGRAMFILES\KSafe"
XPStyle on
ShowInstDetails nevershow
ShowUninstDetails nevershow
BrandingText "ijinshan.com"
Caption " ${CAPTION_NAME} ${PRODUCT_VERSION} ��װ"


; ���װ��־��¼������־�ļ�������Ϊж���ļ�������(ע�⣬�����α����������������֮ǰ)
Section "-LogSetOn"
  ;LogSet on
SectionEnd
 ;  File /r "bin\*.*"
 
!macro KillLeidianTray
  push $0
  FindWindow $0 "{5469F950-888A-4bc1-B0B4-72F0159D7ACD}" ""

  ${if} $0 != 0
    SendMessage $0 1131 0 0 /TIMEOUT=5000
  ${endif}
  pop $0
  ;KillProcDLL::KillProc "KSafeTray.exe"
!macroend

!macro KillLeidianMain
  ExecWait "$INSTDIR\KSafe.exe -do:{B2C96360-9354-4686-A04B-0F9870D892C9}"
!macroend

!macro FileVirusDat FileDst DirLocal FileLocal KeyData RepFile
  push $0
  push $1
  push $2
  push $3
  push $4

!define UPVIRUSDAT_UNIQUE ${__FILE__}${__LINE__}

  IfFileExists ${FileDst} 0 label_newer_${UPVIRUSDAT_UNIQUE}
  GetFileTimeLocal "${DirLocal}\${FileLocal}" $1 $2
  GetFileTime ${FileDst} $3 $4

  IntCmpU $3 $1 0 label_newer_${UPVIRUSDAT_UNIQUE} label_out_${UPVIRUSDAT_UNIQUE}
  IntCmpU $4 $2 label_out_${UPVIRUSDAT_UNIQUE} label_newer_${UPVIRUSDAT_UNIQUE} label_out_${UPVIRUSDAT_UNIQUE}

  label_newer_${UPVIRUSDAT_UNIQUE}:
  
		${if} ${RepFile} != "0"
			SetOverWrite ifnewer
			File /oname=${FileDst} "${DirLocal}\${FileLocal}"
    ${endif}
    WriteRegStr HKLM ${REG_KEY_UPDATE} ${FileLocal} ${KeyData}
    
  label_out_${UPVIRUSDAT_UNIQUE}:
  
!undef UPVIRUSDAT_UNIQUE

  pop $4
  pop $3
  pop $2
  pop $1
  pop $0
!macroend

!macro UpVirusDat FileName RegData RepFile
  !insertmacro FileVirusDat "$INSTDIR\data\sfm2\${FileName}" "${BIN_DIR}\data\sfm2" ${FileName} ${RegData} ${RepFile}
!macroend

!macro UpVirusDat2 FileName RegData RepFile
  !insertmacro FileVirusDat "$INSTDIR\data\${FileName}" "${BIN_DIR}\data" ${FileName} ${RegData} ${RepFile}
!macroend

!macro UpVirusDat3 FileName RegData RepFile
  !insertmacro FileVirusDat "$INSTDIR\data\sfm3kb\${FileName}" "${BIN_DIR}\data\sfm3kb" ${FileName} ${RegData} ${RepFile}
!macroend

!macro UpVirusDat4 FileName RegData RepFile
  !insertmacro FileVirusDat "$INSTDIR\${FileName}" "..\..\product\win32" ${FileName} ${RegData} ${RepFile}
!macroend


!include leidian_install_mainsection.nsh

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\ksafe.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION_REG}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

/******************************
 *  �����ǰ�װ�����ж�ز���  *
 ******************************/

; ���ݰ�װ��־ж���ļ��ĵ��ú�
!macro DelFileByLog LogFile
  ifFileExists `${LogFile}` 0 +4
    Push `${LogFile}`
    Call un.DelFileByLog
    Delete `${LogFile}`
!macroend

Section Uninstall

  ;ж��ͳ��
   push $0
   ReadRegStr $0 HKEY_LOCAL_MACHINE "${REGKEY_PRODUCT}\Coop" "PreOEM"
   !insertmacro InternetGetCookie "stat.ijinshan.com" "/uninstall.htm?pid=$0&ver=${FILE_VER}"
   pop $0

  ; ���ú�ֻ���ݰ�װ��־ж�ذ�װ�����Լ���װ�����ļ�
  ;!insertmacro DelFileByLog "$INSTDIR\install.log"

  ; �����װ���򴴽�������ж��ʱ����Ϊ�յ���Ŀ¼�����ڵݹ���ӵ��ļ�Ŀ¼���������ڲ����Ŀ¼��ʼ���(ע�⣬��Ҫ�� /r �����������ʧȥ DelFileByLog ������)
	;��˽��������������صĽ�����ɱ��
  KillProcDLL::KillProc "kprivacy.exe"
  KillProcDLL::KillProc "netmon.exe"
  KillProcDLL::KillProc "kmspeed.exe"

  !insertmacro KillLeidianMain
  !insertmacro KillLeidianTray
  ExecWait "$INSTDIR\KSafeSvc.exe /stop"
  ;�ָ�������Ŀ
	ExecWait "$INSTDIR\KSafe.exe -uninstall"
  ExecWait "$INSTDIR\KSafeSvc.exe /uninstall"
  ExecWait "$INSTDIR\KSafeSvc.exe /uninst_kpfw_driver"
  ExecWait "$INSTDIR\KSafeSvc.exe /uninst_karpfw_drive"
  
  KillProcDLL::KillProc "KSafe.exe"
  !insertmacro KillLeidianTray
  ExecWait "$INSTDIR\KSafeSvc.exe /stop"
  ExecWait "$INSTDIR\KSafeSvc.exe /stop"
  ExecWait "$INSTDIR\KSafeSvc.exe /stop"

  KillProcDLL::KillProc "KClear.exe"
  KillProcDLL::KillProc "kpcfileopen.exe"
  KillProcDLL::KillProc "kpcfileopen.exe"
  KillProcDLL::KillProc "kpcfileopen.exe"
  KillProcDLL::KillProc "perfopt.exe"
  ;�ȵ�������������ж��
  IfFileExists "$INSTDIR\KClear\uninstclear.exe" 0 +2
     ExecWait '"$INSTDIR\KClear\uninstclear.exe" /S _?=$INSTDIR\KClear'

  ;�ȵ��������ж��
  IfFileExists "$INSTDIR\KEng\uninstkeng.exe" 0 +2
     ExecWait '"$INSTDIR\KEng\uninstkeng.exe" /S _?=$INSTDIR\KEng'

  ;ɾ����ǰ�û����ļ�������Ĺ���Ŀ¼
  SetShellVarContext current
  RMDir /r  "$APPDATA\KSafe"
  
  SetShellVarContext all
  ;ɾ����cacheĿ¼
  IfFileExists "$APPDATA\KSafe\*.*" 0 lbl_cache_continue
  RMDir /r  "$APPDATA\KSafe"
lbl_cache_continue:

  ;ɾ������Ŀ¼
  push $0
  Strcpy $0 "$APPDATA\KSafeQuarantine"
  IfFileExists "$0\*.kbk" 0 lbl_del_quant
  MessageBox MB_YESNO "�Ƿ�Ҫɾ�������ļ���" IDYES lbl_del_quant IDNO lbl_no_del_quant
lbl_del_quant:
  RMDir /r "$0\*.*"
lbl_no_del_quant:
  pop  $0
  
  SetShellVarContext current
  ;  ɾ�����и�Ŀ¼�µ� KSafeRecycle Ŀ¼
  ${un.GetDrives} "ALL" "un.DeleteKSafeRecycleDir"

  ;ɾ�����ز���Ŀ¼
  StrCpy $0 "$INSTDIR\hotfix"
  ${DirState} "$0" $R1
  Strcmp $R1 "1" 0 lbl_del_hotfix
  MessageBox MB_YESNO "�Ƿ�Ҫɾ�����صĲ����ļ���" IDYES lbl_del_hotfix IDNO lbl_no_del_hotfix
lbl_del_hotfix:
  RMDir /r "$INSTDIR\hotfix"
lbl_no_del_hotfix:
  pop $0
!ifndef PRODUCT_UPDATE
	!insertmacro DeleteFileEx "$INSTDIR\KnInstAD.exe" "$INSTDIR"
!endif
  !insertmacro DeleteFileEx "$INSTDIR\KSafeTray.exe" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\KSafe.exe" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\ksafebak.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kcache.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\ksafedb.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\ksafeeng.dll" "$INSTDIR"
  ;!insertmacro DeleteFileEx "$INSTDIR\ksignup.dll"
  !insertmacro DeleteFileEx "$INSTDIR\KSafeSvc.exe" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\ksfmon.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\ksafeexam.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\ksafevul.dll" "$INSTDIR"
  ;!insertmacro DeleteFileEx "$INSTDIR\kfiled.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kplugext.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\ksafeup.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\ksafever.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\katrun.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kiefixeng.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\krunopt.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\zlib1.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kproclib.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\msvcm80.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\msvcp80.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\msvcr80.dll" "$INSTDIR"
  
  !insertmacro DeleteFileEx "$INSTDIR\KEng\ksgmerge.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\KEng\ksignup.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\KEng\ksafeave.dll" "$INSTDIR"
  
  !insertmacro DeleteFileEx "$INSTDIR\KSoft\softmgr.dll" "$INSTDIR\KSoft"

  !insertmacro DeleteFileEx "$INSTDIR\KAV100602_ONLINE_10_10.exe" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kwsctrl.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\sqlite.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kavmgr.dll" "$INSTDIR"

  # ɾ�����ܵ��ļ�
  !insertmacro DeleteFileEx "$INSTDIR\kswebshield.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kwsui.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\BC.sys" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kavquara.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kcldrep.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\khandler.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kscanner.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kscantyp.xml" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\ksreng3.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\ksscore.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kxebase.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kxecomm.dat" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kxestat.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\productidinfo.ini" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\scom.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\vf1.dat" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\WhiteList.dat" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kse\data.fsg" "$INSTDIR\kse"
  !insertmacro DeleteFileEx "$INSTDIR\kse\ksbwdet2.dll" "$INSTDIR\kse"
  !insertmacro DeleteFileEx "$INSTDIR\kse\ksbwdt.ini" "$INSTDIR\kse"
  !insertmacro DeleteFileEx "$INSTDIR\kse\ksecorex.dll" "$INSTDIR\kse"
  !insertmacro DeleteFileEx "$INSTDIR\kse\sqlite.dll" "$INSTDIR\kse"
  !insertmacro DeleteFileEx "$INSTDIR\kse\wfs.dll" "$INSTDIR\kse"
  !insertmacro DeleteFileEx "$INSTDIR\kse\kavquara.dll" "$INSTDIR\kse"
  !insertmacro DeleteFileEx "$INSTDIR\kse\ksecansp.dll" "$INSTDIR\kse"
  !insertmacro DeleteFileEx "$INSTDIR\kse\unknown.fsg" "$INSTDIR\kse"
  !insertmacro DeleteFileEx "$INSTDIR\kse\config\kse.stat_fac_cfg.xml" "$INSTDIR\kse\config"
  !insertmacro DeleteFileEx "$INSTDIR\kse\config\ksecore.addon.xml" "$INSTDIR\kse\config"
  !insertmacro DeleteFileEx "$INSTDIR\kse\config\ksecore.netdetcfg.xml" "$INSTDIR\kse\config"
  !insertmacro DeleteFileEx "$INSTDIR\kse\config\ksecore.sln.xml" "$INSTDIR\kse\config"
  !insertmacro DeleteFileEx "$INSTDIR\kse\config\kspfeng.filemonfilter.xml" "$INSTDIR\kse\config"
  !insertmacro DeleteFileEx "$INSTDIR\kse\config\kspfeng.polman.xml" "$INSTDIR\kse\config"
  !insertmacro DeleteFileEx "$INSTDIR\kse\config\kspfeng.pwlcfg.xml" "$INSTDIR\kse\config"
  !insertmacro DeleteFileEx "$INSTDIR\kxecore\kxecore.dll" "$INSTDIR\kxecore"
  !insertmacro DeleteFileEx "$INSTDIR\kdump.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kdumprep.exe" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kdumpfix.exe" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kswbc.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kwssp.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\pedownui.dll" "$INSTDIR"
  !insertmacro DeleteFileEx "$INSTDIR\kwsplugin.dll" "$INSTDIR"
  
  !insertmacro DeleteFileEx "$INSTDIR\KAV_ONLINE_95_11.exe" "$INSTDIR"

	;;; ��˽������ж��
  !insertmacro DeleteFileEx "$INSTDIR\kprivacy\kprivacy.exe" "$INSTDIR\kprivacy"
  !insertmacro DeleteFileEx "$INSTDIR\kprivacy\trackcleaner.dll" "$INSTDIR\kprivacy"
  !insertmacro DeleteFileEx "$INSTDIR\kprivacy\kclear.dll" "$INSTDIR\kprivacy"
	;;;;;;;;;;;;;;;;;;

  RMDir /r "$INSTDIR\data"
  Delete "$INSTDIR\*"
  RMDir /r "$INSTDIR\cfg"
  RMDir /r "$INSTDIR\avs"
  RMDir /r "$INSTDIR\AppData"
  RMDir /r "$INSTDIR\temp"
  RMDir /r "$INSTDIR\KEng"
  RMDir /r "$INSTDIR\KClear"
  RMDir /r "$INSTDIR\KSoft"
  RMDir /r "$INSTDIR\res"
  RMDir /r "$INSTDIR\cp1"
  RMDir /r "$INSTDIR\cp2"
  RMDir /r "$INSTDIR\cp3"
  RMDir /r "$INSTDIR\kxecore"
  RMDir /r "$INSTDIR\webui"
  RMDir /r "$INSTDIR\log"
  
  RMDir /r "$INSTDIR\ksrcfg"
  RMDir /r "$INSTDIR\kse"
  RMDir /r "$INSTDIR\kxecore"
  RMDir /r "$INSTDIR\kprivacy"

  ; ɾ����������ģ��Ļ����ļ�
  SetShellVarContext all
  RMDir /r "$APPDATA\kingsoft\kclear\fcache"
  SetFileAttributes "$INSTDIR\regbackup" NORMAL
  RMDir /r "$INSTDIR\regbackup"
  SetShellVarContext all
  Delete "$DESKTOP\��ɽ��ʿ.lnk"
  Delete "$DESKTOP\��ɽ��ʿ�������.lnk"
  RMDir /r "$SMPROGRAMS\��ɽ��ʿ"

  RMDir "$INSTDIR"
  
  DeleteRegValue HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\RunOnce" "${KSAFE_PLUG_RUNONCE}"
  DeleteRegValue HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Run" "${LEIDIAN_TRAY_AUTORUN}"
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${REGKEY_PRODUCT}"
  DeleteRegKey HKCU "${REGKEY_PRODUCT}"

  SetAutoClose true
SectionEnd

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

Function un.DeleteKSafeRecycleDir
  IfFileExists "$9KSafeRecycle\*.*" 0 label_out
  RMDir /r "$9KSafeRecycle"
label_out:
	Push $0
FunctionEnd


Function SelectDirPagePre
    push $0
    Call GetInstalledLeidianPath
    ${if} $0 != "0"
      StrCpy $INSTDIR $0
      Abort
    ${endif}
    pop $0
FunctionEnd


Function GetParternName
  push $0
  push $1
  !ifdef USE_NAME_AS_PARTER
       push $R0
       KillProcDLL::GetPidByFileName
       StrCpy $0 $R0
       pop $R0
  !else
       StrCpy $0 "${PRODUCT_PARTNER}"
  !endif
  pop $1
  Exch $0
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

;��ȡ��ɽ��ʿ�İ汾��
Function GetInstalledLeidianDLLPath
  push $1
  Call GetInstalledLeidianPath
  ${if} $0 != "0"
       Strcpy $1 "$0\ksafever.dll"
       Strcpy $0 $1
  ${endif}
  pop $1
FunctionEnd

; �ж��Ƿ����°汾�Ѿ���װ
Function IsNewerLeidianInstalled
  push $1
  push $2
  push $3
  push $4

  Strcpy $0 "0"
  Call GetInstalledLeidianDLLPath
  ${if} $0 != "0"
    GetDLLVersion $0  $1 $2
!ifdef PRODUCT_UPDATE
    GetDLLVersionLocal "${BIN_DIR}\ksafever.dll" $3 $4
!else
    GetDLLVersionLocal "${BIN_DIR}\ksafever.dll" $3 $4
!endif
    Strcpy $0 "0"
    IntCmpU $3 $1 0 label_newer label_out
    IntCmpU $4 $2 label_out label_newer label_out

  label_newer:
     Strcpy $0 "1"
  label_out:

  ${else}
    Strcpy $0 "0"
  ${endif}

  pop $4
  pop $3
  pop $2
  pop $1

FunctionEnd

!ifdef PRODUCT_JXSJ
;������Ե�İ�װ�߼�
Function GetJXSJSectionName
  push $0
  push $1
  
       ${GetFileName} $EXEPATH $1
       ${WordReplace} "$1" "${STR_JXSJ_FMARK_1}" "" "+" $0
       ${WordReplace} "$0" "${STR_JXSJ_FMARK_2}" "" "+" $1
       Strcpy $0 "${STR_JXSJ_INI_SECTION_PRE}$1"
       
  push $1
  Exch $0
FunctionEnd

Function IsJXSJInsted
  push $0
  push $1
  
  Call GetJXSJSectionName
  pop $0
  ReadINIStr $1 "$EXEDIR\${STR_JXSJ_INI_NAME}" $0 "${STR_JXSJ_INI_INST_KEY}"
  
  StrCpy $0 "0"
  ${if} $1 != ""
        ${if} $1 != "0"
              StrCpy $0 "1"
        ${endif}
  ${endif}
  pop $1
  Exch $0
FunctionEnd

Function WriteJXSJInstMark
  push $0
  push $1
  
  Call GetJXSJSectionName
  pop $0
  WriteINIStr "$EXEDIR\${STR_JXSJ_INI_NAME}" $0 "${STR_JXSJ_INI_INST_KEY}" "1"

  pop $1
  pop $0
FunctionEnd
!endif

Function .onInit

!ifdef FORCE_SILENT_INST
  SetSilent silent
!endif

!ifdef JXSJ_MSG_TIP_TXT
  Call GetInstalledLeidianPath
  ${if} $0 != "0"
      quit
  ${else}
	    MessageBox MB_YESNO|MB_ICONINFORMATION "${JXSJ_MSG_TIP_TXT}" IDYES label_jxsj_msg_contine  IDNO label_jxsj_msg_quit
	    label_jxsj_msg_quit:
			Quit
			label_jxsj_msg_contine:
  ${endif}
!endif

!ifdef SLIENT_INST_NO_REINSTALL
  ${if} ${silent}
        Call GetInstalledLeidianPath
        ${if} $0 != "0"
              quit
        ${endif}
  ${endif}
!endif

!ifdef PRODUCT_JXSJ
  push $0
  push $1
  
  Call IsJXSJInsted
  pop $0
  ${if} $0 == "1"
        quit
  ${endif}
  
  pop $1
  pop $0

!endif

  ${if} ${silent}
        
  ${else}
	   ${if} ${IsWin2000}
	     MessageBox MB_YESNO "��ɽ��ʿ��Windows 2000ϵͳ�п����޷��������У��Ƿ�Ҫ������װ��" IDYES label_2k_contine  IDNO label_2k_quit
	    label_2k_quit:
			 Quit
			label_2k_contine:
	   ${endIf}
  ${endif}

!ifdef PRODUCT_UPDATE
;  SetSilent silent
;    Call GetInstalledLeidianPath
;    ${if} $0 == "0"
;        quit
;    ${endif}
!else
    push $0

    ${if} ${silent}
    ${else}
    	    Call IsNewerLeidianInstalled
	    ${if} $0 != "0"
	        MessageBox MB_YESNO "��װ�����⵽���Ļ��������и��°汾�Ľ�ɽ��ʿ��$\r$\n����밲װ���а汾������ж�ػ��������еĽ�ɽ��ʿ��$\r$\n$\r$\n���Ƿ�Ҫ�������а�װ��" IDYES lbl_continue_x IDNO lbl_QuiteInstall
	    lbl_continue_x:
	    ${else}
	      Call GetInstalledLeidianPath
	      ${if} $0 != "0"
	        MessageBox MB_YESNO "��⵽�Ѱ�װ��ɽ��ʿ����ȷ��Ҫ�������ǰ�װ��" IDYES lbl_continue_y IDNO lbl_QuiteInstall
	        lbl_continue_y:
	      ${endif}
	    ${endif}
	    goto lbl_KillApp
	  lbl_QuiteInstall:
	    quit
	  lbl_KillApp:
    ${endif}
    pop $0
!endif

FunctionEnd

Function .onInstSuccess
  ${if} ${silent}
	  !ifdef WRITE_TRAY_REG_RUN
	  !ifdef PRODUCT_UPDATE
	  Exec '"$INSTDIR\KSafeTray.exe -traystart:1"'
	  !else
		Exec '"$INSTDIR\KSafeTray.exe"'
		!endif
	  !endif
  ${endif}
  
!ifdef PRODUCT_JXSJ
 ;д��������İ�װ���
 Call WriteJXSJInstMark
!endif

!ifdef BIND_WITH_OTHER_SOFTMGR
  push $1
  HideWindow
  SetOutPath $TEMP
  GetTempFileName $0
  Delete $0
  File /oname=$0 "pattern\softmgr.exe"
  StrCpy $1 '"$0" /S /D=$PROGRAMFILES\Kingsoft\softmanager'
  Exec $1
  pop $1
!endif
  
FunctionEnd


Function FinishPageShow

  push $0
  Push $1

  ${if} ${RebootFlag}
  ${else}
    ; ��������ӵ�checkbox�ı���ɫ
    Strcpy $0 ""
    !insertmacro MUI_INSTALLOPTIONS_READ $0 "ioSpecial.ini" "Field 5" "hwnd"
     ${if} $0 != ""
        SetCtlColors $0 "" 0xFFFFFF
    ${endif}

    ; ��������ӵ�Maxthon�ڶ��еı���ɫ
    !insertmacro MUI_INSTALLOPTIONS_READ $0 "ioSpecial.ini" "Field 6" "hwnd"
    ${if} $0 != ""
      SetCtlColors $0 "" 0xFFFFFF
    ${endif}
    
    
  !insertmacro MUI_INSTALLOPTIONS_READ $0 "ioSpecial.ini" "Field 7" "hwnd"
  ${if} $0 != ""
      SetCtlColors $0 "0x7F7F7F" 0xFFFFFF
  ${endif}
  
      ; �������ӵı���ɫ
  !insertmacro MUI_INSTALLOPTIONS_READ $0 "ioSpecial.ini" "Field 8" "hwnd"
  ${if} $0 != ""
      Linker::link /NOUNLOAD $0 "http://www.ijinshan.com/safe/yun_intro.html?fr=client"
  ${endif}
  
  !ifndef WRITE_SOFTMGR_ICO
		!insertmacro MUI_INSTALLOPTIONS_READ $0 "ioSpecial.ini" "Field 9" "hwnd"
	  ${if} $0 != ""
	      SetCtlColors $0 "0x7F7F7F" 0xFFFFFF
	  ${endif}
  !endif
  
	!ifdef LOCK_HOMEPAGE_TEXT
	  !insertmacro MUI_INSTALLOPTIONS_READ $0 "ioSpecial.ini" "Field 10" "hwnd"
	  ${if} $0 != ""
	      SetCtlColors $0 "0x7F7F7F" 0xFFFFFF
	  ${endif}
  !endif

  ${endif}

  Pop $1
  pop $0

FunctionEnd

Var TopCloud
Var TopDeskTop
Var TopHomePage

Function FinishPagePre

  push $0
  Push $1
  Push $2

  ${if} ${RebootFlag}
  ${else}

	; $2 Ϊ��һ�е�����
	StrCpy $2 "110"


  StrCpy $TopCloud		$2
  StrCpy $TopDeskTop 	$2
  StrCpy $TopHomePage $2

  !ifndef WRITE_SOFTMGR_ICO
	    !ifdef LOCK_HOMEPAGE_TEXT
					 StrCpy $TopCloud "150"
					 StrCpy $TopDeskTop "110"
					 StrCpy $TopHomePage "130"
			!else
					 StrCpy $TopCloud "150"
					 StrCpy $TopDeskTop "110"
					 StrCpy $TopHomePage "0"
	  	!endif
  !else
	    !ifdef LOCK_HOMEPAGE_TEXT
					 StrCpy $TopCloud "130"
					 StrCpy $TopDeskTop "0"
					 StrCpy $TopHomePage "110"
			!else
					 StrCpy $TopCloud "115"
					 StrCpy $TopDeskTop "0"
					 StrCpy $TopHomePage "0"
	  	!endif
  !endif


  
         StrCpy $0 $TopCloud
				 IntOp $1 $0 + 10
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Settings" "NumFields" "5"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Type" "Checkbox"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Left" "120"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Right" "325"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Top" "$0"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Bottom" "$1"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "State" "1"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Text" "�����ư�ȫ�ƻ����Զ��ϱ������ļ����ư�ȫ����"

         IntOp $0 $1 + 5
				 IntOp $1 $0 + 10
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Settings" "NumFields" "6"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "Type" "label"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "Left" "133"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "Right" "315"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "Top" "$0"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "Bottom" "$1"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "State" "1"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "Text" "�����п��ٷ�������ʱ���ֲ�����²���ľ��"

         IntOp $0 $1 + 4
				 IntOp $1 $0 + 10
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Settings" "NumFields" "7"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "Type" "label"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "Left" "120"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "Right" "273"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "Top" "$0"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "Bottom" "$1"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "Text" "����ƻ������ַ�������˽�������ʹ�á�"

         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Settings" "NumFields" "8"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 8" "Type" "label"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 8" "Left" "273"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 8" "Right" "290"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 8" "Top" "$0"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 8" "Bottom" "$1"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 8" "Text" "��˽��������"

					;  ��������ͼ��
  !ifndef WRITE_SOFTMGR_ICO
         StrCpy $0 $TopDeskTop
				 IntOp $1 $0 + 10
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Settings" "NumFields" "9"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 9" "Type" "Checkbox"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 9" "Left" "120"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 9" "Right" "325"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 9" "Top" "$0"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 9" "Bottom" "$1"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 9" "State" "1"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 9" "Text" "����������ʾ��������ݷ�ʽ"
	!endif
	
					;  ��������ͼ��
  !ifdef LOCK_HOMEPAGE_TEXT
         StrCpy $0 $TopHomePage
				 IntOp $1 $0 + 10
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Settings" "NumFields" "10"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 10" "Type" "Checkbox"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 10" "Left" "120"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 10" "Right" "325"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 10" "Top" "$0"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 10" "Bottom" "$1"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 10" "State" "1"
         !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 10" "Text" "${LOCK_HOMEPAGE_TEXT}"
	!endif

  ${endif}

	Pop $2
  Pop $1
  pop $0

FunctionEnd

Function FinishPageLeave

  ; ���ѡ���˰�װ�����г���������ָ������
  push $0
  Push $1

  ${if} ${RebootFlag}
  ${else}
	  !insertmacro MUI_INSTALLOPTIONS_READ $0 "ioSpecial.ini" "Field 5" "State"
          WriteINIStr "$INSTDIR\cfg\scansetting.ini" "Skylark" "JoinSkylark" "$0"
          
	  !ifndef WRITE_SOFTMGR_ICO
	  	!insertmacro MUI_INSTALLOPTIONS_READ $0 "ioSpecial.ini" "Field 9" "State"
			${if} $0 == 1
			    		CreateShortCut "$DESKTOP\��ɽ��ʿ�������.lnk" "$INSTDIR\KSafe.exe" "-do:ui_softmgr" "$INSTDIR\KSoft\softmgr.ico" 0
			${endif}
      WriteINIStr '$INSTDIR\cfg\bksoftmgr.ini' "update" "desktop_icon" "$0"
		!endif
		
		!ifdef LOCK_HOMEPAGE_TEXT
	  	!insertmacro MUI_INSTALLOPTIONS_READ $0 "ioSpecial.ini" "Field 10" "State"
			${if} $0 == 1
				WriteRegStr HKLM "SOFTWARE\Microsoft\Internet Explorer\Main" "Start Page" "${LOCK_HOMEPAGE_URL}"
                                WriteRegStr HKCU "SOFTWARE\Microsoft\Internet Explorer\Main" "Start Page" "${LOCK_HOMEPAGE_URL}"
			${endif}
		!endif
		
		
		
	  !insertmacro MUI_INSTALLOPTIONS_READ $0 "ioSpecial.ini" "Field 4" "State"
	  ${if} $0 == 1
	    Exec "$INSTDIR\KSafe.exe"
	  ${endif}
	  
  ${endif}

  Pop $1
  pop $0

FunctionEnd

Function un.onInit

  MessageBox MB_YESNO|MB_DEFBUTTON1 "�Ƿ�Ҫж�ؽ�ɽ��ʿ��" IDYES lbl_GoUnstall IDNO lbl_ExitUnstall
lbl_ExitUnstall:
  quit
lbl_GoUnstall:

FunctionEnd

Function un.onUninstSuccess
FunctionEnd

VIAddVersionKey  "ProductName" "��ɽ��ʿ"
VIAddVersionKey  "Comments" "��ɽ��ʿ"
VIAddVersionKey  "CompanyName" "��ɽ��ʿ"
VIAddVersionKey  "LegalTrademarks" "��ɽ��ʿ"
VIAddVersionKey  "LegalCopyright" "��Ȩ����(C) 2010 ��ɽ��ʿ"
VIAddVersionKey  "FileDescription" "��ɽ��ʿ"
VIAddVersionKey "FileVersion" "${FILE_VER}"
VIAddVersionKey "ProductVersion" "${FILE_VER}"
VIProductVersion "${FILE_VER}"
