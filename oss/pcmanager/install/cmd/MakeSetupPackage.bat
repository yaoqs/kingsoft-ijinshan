@rem           Down : �ٷ��氲װ��
@rem        curpath : ��Ŀ¼һ��
@rem        tooldir : ������װ������Ŀ¼,Ĭ��ʹ��2.30�汾,����������汾����ʱ���ϰ汾����ΪĿ¼�磺%tooldir%\2.37\makensis.exe
@rem     installdir : ������װ����Ϣ��Ŀ¼
@rem         script : ��װ���ű��ļ�
@rem   �� ���� file : ��������ļ��Ĵ��Ŀ¼
@rem        package : ��װ�����Ŀ¼

@set curpath=%1
@set tooldir=%2
@set installdir=%curpath%\install

if {%curpath%} == { } goto nopath
if {%tooldir%} == { } goto notool

%tooldir%\2.45\makensis.exe /V1 %installdir%\leidian\Setup.nsi
@if %ERRORLEVEL% EQU 0 (
   @goto dubaweb
   ) else   (
   @goto failed
   )
   
:dubaweb
%tooldir%\2.45\makensis.exe  /V1 %installdir%\leidian\Setup_dubaweb.nsi
@if %ERRORLEVEL% EQU 0 (
   @goto zhuansha
   ) else   (
   @goto failed
   )
   
:zhuansha
%tooldir%\2.45\makensis.exe  /V1 %installdir%\leidian\Setup_zhuansha.nsi
@if %ERRORLEVEL% EQU 0 (
   @goto update
   ) else   (
   @goto failed
   )
   
:update
%tooldir%\2.45\makensis.exe  /V1 %installdir%\leidian\update_setup.nsi
@if %ERRORLEVEL% EQU 0 (
   @goto exit
   ) else   (
   @goto failed
   )

:nopath
echo WorkCopy path no Set
if Failed

:notool
echo MakeNsis Tool no set
if Failed
  
:failed
echo MakeSetupPackage Exec Failed
if Failed

:exit