@rem      CurrAll : ������ǰ��Ҫ�İ�װ��
@rem           %1 : ��Ŀ¼һ��
@rem           %2 : ������װ������
set WorkDir=%1
set NsisTool=%2
set BatPath=%WorkDir%\install\cmd

call %BatPath%\MakeSetupPackage.bat %WorkDir% %NsisTool%
call %BatPath%\MakeSetupPackage_OEM.bat %WorkDir% %NsisTool%