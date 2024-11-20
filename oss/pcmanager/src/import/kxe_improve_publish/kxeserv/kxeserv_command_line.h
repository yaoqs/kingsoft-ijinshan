//////////////////////////////////////////////////////////////////////
///		@file		kxeserv_command_line.h
///		@author		luopeng
///		@date		2009-3-11 09:07:58
///
///		@brief		�����ж���
//////////////////////////////////////////////////////////////////////

#pragma once
/**
 * @defgroup kxeserv_command_line KXEngine Commandline Define
 * @section kxeserv_command_line_install_service ����װ
 * kxeserv /debug     ����״̬������ \n
 * kxeserv /install   ��װ����\n
 * kxeserv /uninstall ж�ط���\n
 * kxeserv /start     ��������\n
 * kxeserv /stop      ֹͣ����\n
 * kxeserv /start_until_running ֱ��������ȫ������ŷ���\n
 * kxeserv /stop_until_stopped ֱ�ӷ�����ȫֹͣ��ŷ���\n
 * @section kxeserv_command_line_install_product  ��Ʒ��װ
 * kxeserv /install_product_by_file [config_file_name]   ��װ��Ʒ������װ���˻�ʧ��\n
 * kxeserv /reinstall_product_by_file [config_file_name] �ٴΰ�װ������װ����Ҳ���ٴΰ�װ\n
 * kxeserv /uninstall_product_by_file [config_file_name] ж�ز�Ʒ\n
 * @section kxeserv_command_line_install_product_config_file �����ļ���ʽ
 * �������д�·���Ĳ��֣�����Path����ֶ��⣬�����ֶζ����������·������Ե���Path����
 * �������µ�File0=test.dll��������·������d:\\kingsoft\\test.dll
 * @code 
 *

[Product]
ID=0x10000000
Parent=0x20000000
Recommend=
Path=d:\kingsoft
PluginPath=plugin // ����·����ʹ��Path��Ϊ��·����plugin�����·�����������d:\kingsoft\plugin
WebPath=web       // ����·����ʹ��Path��Ϊ��·����web�����·�����������d:\kingsoft\web

[ChildProduct]
Count=1
Product0=0x30000000

[Component]
Count=1
File0=test.dll  // ����·����ʹ��Path��Ϊ��·����test.dll�����·�����������d:\kingsoft\test.dll

[ServiceProvider]
Count=1
File0=test.dll  // ����·����ʹ��Path��Ϊ��·����test.dll�����·�����������d:\kingsoft\test.dll

 *
 * @endcode
 */
