��Ŀ¼Build:
1��Ŀ¼ɾ���ļ��б�
	����: deldir.list
	��;��������ָ��Ҫɾ��Ŀ¼���ļ��б�ӿ�
   ��ʽ��filename
�� ������filename����Կ�Ŀ¼Ҫɾ����Ŀ¼
�� ��ע�������������룬������ɾ����Թ���Ŀ¼�µ�releaseĿ¼
   ����:
{{{
Build
Src
Product/win
 }}}
2��ָ��Ҫ���빤�̵��б�solutionfile.list
�� ��ʽ��filename[,argname[,toolname]]
�� ˵����
     filename����Կ�Ŀ¼�Ĺ����ļ�/��������ļ���
���� argname�����������Ĭ��/t:build /p:Configuration=Release����
���� toolname�����빤�ߣ�Ĭ��msbuild.exe����
   ��ע����ͬ������������в���ʡ��argname����
�������� ��ͬ���빤�ߵ����в���ʡ��toolname����
   �ο���Build\solutionfile.list
3���ļ�ǩ���ļ��б�
	����: signfile.list
	��;: ������ָ��Ϊ�ļ�ǩ�����ļ��б�ӿ�
�� ��ʽ��filename[,filetype][,filenote]
�� ������
����filename: ��Կ�Ŀ¼Ҫ������ǩ�����ļ�
     filetype: ֧������ǩ����ʽ:PE(������,����Ϊ�ļ�����չ��)/SYS(����visat�����������ļ�sys������Ϊ�ļ�����չ��)/VSA(����visat�������ϵİ�ȫ�����ļ�,������vistaϵͳ��������Ч������ΪVSA)
    filenote: ǩ����������Ϣ,�����������ı��ļ����Ϊutf-8��ʽ
	��ע����ͬ��չ�����ļ����в���ʡ��filetype����ֵ
	����:
{{{
aaa.dll,dll
a\bbb.dll
a\ccc.exe,exe
}}}
4���ⲿ�����ļ��б�
	����: getdata.list
	��;��������ָ��Ҫcopy���ļ��б�ӿ� 
   ��ʽ��srcpath,dstpath
   ������srcpath�����dubabin��Ŀ¼�����·��
	dstpath�����svn�ֿ��Ŀ¼�����·��
   ��ע�� 
   ����:
{{{
DubaTest\KIS\SelfData\makesetup_installfile,product\win32\
DubaTest\KIS\SelfData\miniksg2010,product\win32\miniksg\
 }}}
5. ָ��Ҫ�޸�rc�ļ����б�verfilelist.list
   ��ʽ��filename,type,mmr,comp,same
   ˵����
       filename����Կ�Ŀ¼��rc2�ļ�
       type���ļ�����,0:vc����;1:c#����
       mmr������rc2�ļ���ProductVersion�ֶ�ֵ��ǰ��λ��ǰ��λ,��ʽ��1.0,1.0.1.���ݰ汾�ŵĸ�ʽ����.
       comp:����rc�ļ���VALUE "CompanyName"��ֵ,����Ҫ������
       same:����rc�ļ���FileVersion��ProductVersion�Ƿ�ȡֵͬ.0ֵͬ,��0��ֵͬ.
   ��ע��������������Ϊ��,���Ÿ���
   ����:
{{{
include\buildcfg\aaa\VersionNo.rc2,0,1.0
include\buildcfg\bbb\VersionNo.rc2,0,3.0
include\buildcfg\bbb\VersionNo.cs,1,1.0
include\buildcfg\VersionNo.rc2,0,2.0.1,Kingsoft Corporation,0
include\buildcfg\VersionNo.rc2,0,3.7,Kingsoft Corporation,1
 }}}