//////////////////////////////////////////////////////////////////////
///		@file		mainpage.h
///		@author		luopeng
///		@date		2008-9-25 09:07:58
///	
///		@brief		doxygen�����ļ�
//////////////////////////////////////////////////////////////////////

#pragma once

/**
  @mainpage KXEngine Architecture

  @section kxengine_architecture_interface 1. �ܹ��ӿ�����
  - @subpage kxe_ipc_interface "IPC������ؽӿ�"
   - @ref kxeipc_service_provider_interface_group
   - @ref kxeipc_idl_interface_group
   - @ref kxepipe_idl_interface_group
   - @ref kxehttp_idl_interface_group

  - @subpage architecture_product_manage_interface "�����ܲ�Ʒ����ӿ�"
   - @ref kxeservice_manager_service_provider_interface_group "��Ʒ�����HTTP-RPC�ӿ�"
   - @ref kxeserv_command_line "��Ʒ����������нӿ�"

  - @subpage architecture_interface "�ܹ��ӿ�"
   - @ref kxebase "�ܹ������ӿ�SDK"
   - @ref kxebase_plugin_sdk "��ϵͳSDK��չ�ӿ�"
   - @ref data_struct "���ݽṹ����"
   - @ref json_data_struct "Json������ݽṹ����"
   - @ref kxe_file_register_interface "�ܹ��������������ṩ�߰�װ�ӿ�"

  - @subpage architecture_core_component_interface "�ܹ���������ӿ�"
   - @ref kxethread_component_interface  "�̹߳�������ӿ�"
   - @ref kxeconfig_component_interface  "���ù�������ӿ�"
   - @ref kxeevent_component_interface   "�¼���������ӿ�"
   - @ref kxe_pipe_interface_define "���̷���ͨѶ�ӿ�"

  - @subpage architecture_wow64_interface "�ܹ����64λ�ļ��ݴ���"
   - @ref kxereg_wow64_interface "ע�����ʲ���"
   - @ref kxefile_wow64_interface "�ļ����ʲ���"

  - @subpage architecture_src_interface "�ܹ��������ܽӿ�"
   - @ref kxebase_src_thread_group "�߳���ظ����������ӿ�"
   - @ref kxearchitecture_md5_group "MD5����ӿ�"

  - @subpage example "�ܹ��ӿ�ʹ��ʾ��"
   - @ref kxeevent_example "�¼�ʹ��ʾ��"
   - @ref kxeconfig_example "����ʹ��ʾ��"
   - @ref kxehttp_example "HTTP-RPCʹ��ʾ��"
   - @ref kxeservice_provider_example "�����ṩ�ߴ���ʾ��"
   - @ref kxeplugin_sdk_example "��ϵͳSDK��չ����ʾ��"

  - @subpage architecture_service_provider_interface "�ܹ������ṩ�߻����ӿ�"
   - @ref kxe_service_provider_interface_group
   - @ref kxe_service_provider_clsid_group
   - @ref kxe_service_provider_export_group

 @section kxengine_starfish_plan_application 2. ���Ǽƻ�
  - @subpage kxengine_starfish_product_application

 @section kxengine_product_application 3. ��ƷӦ��
  - @subpage kxengine_highperf_product_application "���ٰ�Ӧ��"
*/

/**
 * @page kxengine_starfish_product_application KXEngine in Starfish Product
  @section kxengine_starfish_architecture 1. �ܹ��ṹͼ
   @image html starfish_arch.png

  @section kxengine_common_component 1. ��������ӿڶ���
   - @subpage kxeservice_manager_define "����������ӿڶ���"
    - @ref kxeservice_manager_service_provider_interface_group
    - @ref kxeservice_manager_event_define_group
    - @ref kxeservice_manager_data_struct_group
    - @ref kxeservice_manager_config_data_struct_group
    - @ref kxeserv_command_line
  
  @section kxengine_security_center_component 2. ��ȫ���Ľӿڶ���
   - @ref kxengine_starfish_security_center_architecture
   - @ref kxe_security_center_service_provider_interface_group
   - @ref kxe_security_center_data_struct
   - @ref kxe_sc_tray_interface_group
   - @ref kxepassport_service_provider_interface_star_fish_group
   - @ref kxe_security_center_downloader_service_provider_interface_group
   - @ref kxe_security_center_installer_service_provider_interface_group

  @section kxengine_security_core_component 2. ��ȫ��������ӿڶ���
   - @subpage kxescan_subsystem_define "��ɱ��ϵͳ����ӿڼ�SDK����"
    - @ref kxescan_subsystem_interface_group
    - @ref kxescan_subsystem_data_struct
    - @ref kxescan_service_provider_interface_group
    - @ref kxescan_event_define_group

   - @subpage kxewhite_subsystem_define "��������ϵͳ����ӿڼ�SDK����"
    - @ref kxewhite_subsystem_interface_group
    - @ref kxewhite_subsystem_data_struct_group
    - @ref kxewhite_service_provider_interface_group
    - @ref kxewhite_event_define_group

   - @subpage kxefilemon_subsystem_define "�ļ������ϵͳ����ӿڼ�SDK����"
    - @ref kxefilemon_subsystem_interface_group
    - @ref kxefilemon_subsystem_data_struct_group
    - @ref kxefilemon_service_provider_interface_group
    - @ref kxefilemon_event_define_group
    - @ref kxefilemon_subsystem_config_group

   - @subpage kxedefendengine_subsystem_define "�����������ӿڼ�SDK����"
    - @ref kxedefendengine_service_provider_interface_group
  
  @section kxengine_security_application_component 3. ��ȫӦ������ӿڶ���
   - @subpage kxe_popo_subsytem_define_2 "���ݷ���ӿڶ���"
    - @ref kxe_pop_server_service_provider_interface_group
    - @ref kxe_pop_server_data_define_group

  @section kxengine_security_product_component 4. ��ȫ��������ӿڶ���
   - @subpage kxenameinfo_subsystem_define "��������ѯ����ӿڶ���"
    - @ref kxe_virus_name_info_service_provider_interface_group
	- @ref kxe_virus_name_info_plugin_sdk_interface_group
    - @ref kxe_virus_name_info_data_group

   - @subpage kxe_leakscan_subsystem_define "©��ɨ�����ӿڶ���"
    - @ref kxe_leak_scan_service_provider_interface_group
    - @ref kxe_leak_scan_data_define_group

   - @subpage kxe_2010_product_define "2010��Ʒ��ؽӿڶ���"
    - @ref kxe_2010_product_sercice_provider_interface
	- @ref kxe_2010_product_data_define_interface


 */

/**
 * @page kxengine_starfish_security_center_architecture KXEngine Security Center Architecture in Startfish
 *  @image html kxe_sc_architecture.png
 */

/**
 * @page kxengine_highperf_product_application KXEngine in High Perfoncmance Product
    @image html highperf_arch.png

   - @ref kxegnine_architecture_file_list_table "�ļ��б�����"

  - @subpage kxeservice_manager_define "����������ӿڶ���"
   - @ref kxeservice_manager_service_provider_interface_group
   - @ref kxeservice_manager_event_define_group
   - @ref kxeservice_manager_data_struct_group
   - @ref kxeservice_manager_config_data_struct_group
   - @ref kxeserv_command_line

  - @subpage kxepassport_subsystem_define "Passport��ϵͳ����ӿڼ�SDK����"
   - @ref kxepassport_subsystem_interface_group
   - @ref kxepassport_subsystem_data_struct_group
   - @ref kxepassport_service_provider_interface_group
   - @ref kxepassport_event_define_group

  - @subpage kxescan_subsystem_define "��ɱ��ϵͳ����ӿڼ�SDK����"
   - @ref kxescan_subsystem_interface_group
   - @ref kxescan_subsystem_data_struct
   - @ref kxescan_service_provider_interface_group
   - @ref kxescan_event_define_group

  - @subpage kxewhite_subsystem_define "��������ϵͳ����ӿڼ�SDK����"
   - @ref kxewhite_subsystem_interface_group
   - @ref kxewhite_subsystem_data_struct_group
   - @ref kxewhite_service_provider_interface_group
   - @ref kxewhite_event_define_group

  - @subpage kxefilemon_subsystem_define "�ļ������ϵͳ����ӿڼ�SDK����"
   - @ref kxefilemon_subsystem_interface_group
   - @ref kxefilemon_subsystem_data_struct_group
   - @ref kxefilemon_service_provider_interface_group
   - @ref kxefilemon_event_define_group
   - @ref kxefilemon_subsystem_config_group

  - @subpage kxepopo_subsystem_define "������ϵͳ����ӿڼ�SDK����"
   - @ref kxepopo_subsystem_interface_group
   - @ref kxepopo_subsystem_data_struct_group
   - @ref kxepopo_service_provider_interface_group
   - @ref kxepopo_event_define_group

  - @subpage kxeupdate_subsystem_define "������ϵͳ����ӿڼ�SDK����"
   - @ref kxeupdate_subsystem_interface_group
   - @ref kxeupdate_subsystem_data_struct_group
   - @ref kxeupdate_service_provider_interface_group
   - @ref kxeupdate_event_define_group
   - @ref kxeupdate_subsystem_config_data_struct_group

  - @subpage kxebase_system_define "ϵͳ�����ṩ�߽ӿ�"
   - @ref kxebase_system_service_provider
   - @ref kxebase_system_service_provider_data_struct 
  
  - @subpage kxeexp_system_define "��Ʒ�м��ӿڶ���"
   - @ref kxeexp_interface_group

  - @subpage kxedefendengine_subsystem_define "�����������ӿڼ�SDK����"
   - @ref kxedefendengine_service_provider_interface_group
*/

/**
 * @page example KXEngine Architecture Example
 * - @subpage kxeevent_example "�¼�ʹ��ʾ��
 * - @subpage kxeconfig_example "����ʹ��ʾ��"
 * - @subpage kxehttp_example "HTTP-RPCʹ��ʾ��"
 * - @subpage kxeservice_provider_example "�����ṩ�ߴ���ʾ��"
 * - @subpage kxeplugin_sdk_example "��ϵͳSDK����ʾ��"
 * - @subpage kxebase_thread_example "�߳�SDKʹ��ʾ��"
 * - @subpage kxearchitecture_md5_example_page "MD5����ʹ��ʾ��"
 */

/**
* @page json_data_struct KXEngine Architecture Json Data Struct
* - @subpage kxehttp_json_data_struct "HTTP-RPC�����Json���ݽṹ"
* - @subpage kxeevent_json_data_struct "�¼��������Json���ݽṹ"
*/

/**
 * @page data_struct KXEngine Architecture Data Struct
 * - @subpage json_data_struct
 */

/**
 * @page architecture_interface KXEngine Architecture Interface
 *  - @subpage kxebase "�ܹ������ӿ�SDK"
 *  - @subpage kxebase_plugin_sdk "��ϵͳSDK��չ�ӿ�"
 *  - @subpage architecture_service_provider_interface "�ܹ������ṩ�߻����ӿ�"
 *  - @subpage data_struct "���ݽṹ����"
 */

/**
 * @page kxebase_system_define KXEngine Architecture System Service Provider Define
 * - @ref kxebase_system_service_provider
 * - @ref kxebase_system_service_provider_data_struct 
 */

/**
 * @page kxeservice_manager_define KXEngine Service Manager Define
 * - @ref kxeservice_manager_service_provider_interface_group
 * - @ref kxeservice_manager_event_define_group
 * - @ref kxeservice_manager_data_struct_group
 * - @ref kxeservice_manager_config_data_struct_group
 * - @ref kxeserv_command_line
 */

/**
 * @page kxescan_subsystem_define KXEngine Scan Subsystem Define
 *  - @ref kxescan_subsystem_interface_group
 *  - @ref kxescan_subsystem_data_struct
 *  - @ref kxescan_service_provider_interface_group
 *  - @ref kxescan_event_define_group
 */

/**
 * @page kxewhite_subsystem_define KXEngine WhiteFile SubSystem Define
 *  - @ref kxewhite_subsystem_interface_group
 *  - @ref kxewhite_subsystem_data_struct_group
 *  - @ref kxewhite_service_provider_interface_group
 *  - @ref kxewhite_event_define_group
 */

/**
 * @page kxefilemon_subsystem_define KXEngine Filemon SubSystem Define
 *  - @ref kxefilemon_subsystem_interface_group
 *  - @ref kxefilemon_subsystem_data_struct_group
 *  - @ref kxefilemon_service_provider_interface_group
 *  - @ref kxefilemon_event_define_group
 *  - @ref kxefilemon_subsystem_config_group
 */

/**
 * @page kxepopo_subsystem_define KXEngine Popo SubSystem Define
 *  - @ref kxepopo_subsystem_interface_group
 *  - @ref kxepopo_subsystem_data_struct_group
 *  - @ref kxepopo_service_provider_interface_group
 *  - @ref kxepopo_event_define_group
 */

/**
 * @page kxeupdate_subsystem_define KXEngine Update SubSystem Define
 *  - @ref kxeupdate_subsystem_interface_group
 *  - @ref kxeupdate_subsystem_data_struct_group
 *  - @ref kxeupdate_service_provider_interface_group
 *  - @ref kxeupdate_event_define_group
 *  - @ref kxeupdate_subsystem_config_data_struct_group
 */

/**
 * @page architecture_src_interface KXEngine Architecture Assistant Interface
 *  - @ref kxebase_src_thread_group "�߳���ظ����������ӿ�"
 *  - @ref kxearchitecture_md5_group "MD5����ӿ�"
 */

/**
 * @page architecture_core_component_interface KXEngine Architecture Core Component Interface 
 *  - @ref kxethread_component_interface  "�̹߳�������ӿ�"
 *  - @ref kxeconfig_component_interface  "���ù�������ӿ�"
 *  - @ref kxeevent_component_interface   "�¼���������ӿ�"
 */

/**
 * @page architecture_wow64_interface KXEngine Architecture WOW64 Mode
 *  - @ref kxereg_wow64_interface "ע�����ʲ���"
 *  - @ref kxefile_wow64_interface "�ļ����ʲ���"
 */

/**
 * @page kxeexp_system_define KXEngine Architecture Express Layer Define
 *  - @ref kxeexp_interface_group
 */

/**
 * @page kxepassport_subsystem_define KXEngine Passport SubSystem Define
 *  - @ref kxepassport_subsystem_interface_group
 *  - @ref kxepassport_subsystem_data_struct_group
 *  - @ref kxepassport_service_provider_interface_group
 *  - @ref kxepassport_event_define_group
 */

/**
 * @page kxedefendengine_subsystem_define KXEngine DefendEngine Define
 *  - @ref kxedefendengine_service_provider_interface_group
 */

/**
 * @page architecture_product_manage_interface KXEngine Product Manage interface
 *  - @ref kxeservice_manager_service_provider_interface_group "��Ʒ�����HTTP-RPC�ӿ�"
 *  - @ref kxeserv_command_line "��Ʒ����������нӿ�
 */

/**
 * @page kxegnine_architecture_file_list_table KXEngine File List Table
 @code
+-KXEngine
    |
    +-driver
        |
        +-kwatch64.sys  64λ�ļ��������
	+-kxeweb
	    |
        +-kavweb.dat  ������ʹ�õ���ҳ�ļ�ѹ������ʹ��zipѹ��
        +-kpopweb.dat ����ʹ�õ���ҳ�ļ�ѹ������ʹ��zipѹ��
	+-ksg     �������ļ�,�뵥���ļ��γ�ͳһ
    +-kxecore ��ܺ����ļ�
        |
        +-kxecfg.dll   ���ù���
        +-kxeevent.dll �¼�����
        +-kxehttp.dll  HTTP����
        +-kxelog.dll   Debug��־����
		+-kxesvc.dll   Service Callģ�飬Ϊkissvc.dll�ĸ���Ʒ
        +-kxethr.dll   �̹߳���
    +-lang �����ļ�(���ڵ�����kavlog2.exe, krecycle.exeʹ��)
		|
		+-chs
		   |
		   +-kavlog2.xml kavlog2.exeʹ�õ���Դ�ļ�
		   +-kavppwiz.xml kavppwiz.dllʹ�õ���Դ�ļ�
		   +-kis.dat ����ʹ�õ������ļ�
		   +-kolhtml.xml kolhtml.dllʹ�õ���Դ�ļ�
		   +-krecycle.xml krecycle.exeʹ�õ���Դ�ļ�
		   +-license.txt
		   +-uplive.svr ���������������ļ�
		   +-uplive.xml ����ʹ�õ���Դ�ļ�
    +-plugin �����չSDK�ļ�
        |
        +-ksesdk.dll   ��ɱ��SDK
        +-kxeexp.dll   ��Ʒ�м��,�ṩ���ܵ���Ʒ֮���ת��
        +-kxefm.dll    �ļ���ص�SDK
        +-kxepop.dll   ���ݵ�SDK
        +-kxewhite.dll ��������SDK
    +-serviceprovider �����ṩ��Ŀ¼
        |
        +-kxefmsp.dll  �ļ���ص�sp
        +-kxepopsp.dll ���ݵ�sp
        +-kxeppsp.dll  passport��sp
        +-kxesansp.dll ��ɱ��sp
        +-kxesyssp.dll ϵͳ�����sp
        +-kxeupdsp.dll ���������sp
        +-kxewfssp.dll �����������sp
    +-subsystem ��ϵͳĿ¼
        |
        +-kxefilemon �ļ������ϵͳĿ¼
             |
             +- kxefmsys.dll �ļ������ϵͳ�ļ�
        +-kxepopo    ������ϵͳĿ¼
             |
             +-kxeposys.dll   ������ϵͳ�ļ�
        +-kxescan    ��ɱ��ϵͳĿ¼
             |
             +-config  ��ɱ��ϵͳ�����ļ�
                |
                +-ksecore.addon.xml            ��ɱ��ϵͳ����б�
                +-ksecore.config.filemon.xml   ��ɱ��ϵͳ�ļ����ɨ������������Ϣ
                +-ksecore.config.normal.xml    ��ɱ��ϵͳһ��ɨ������������Ϣ
                +-ksecore.config.top.xml       ��ɱ��ϵͳ����������Ϣ
                +-ksecore.sln.xml              ��ɱ��ϵͳ��ɱ������ֽ��б�
                +-kspfeng.polman.xml           ��ɱ��ϵͳ�ļ����没������ز����ļ�������������Ϣ
             +-kae     �ļ������ļ�
                |
                +-7z.dll        ֧�ֶ���ѹ����ʽ��ѹ���㷨ʵ��ģ��, ����ѹ�ӿڷ�װģ�����
                +-kaecore.dat   �ļ�ʶ��, �ж��ʹ���ķ�װ�ӿ�ģ��, �ṩ�ӿ�IKSGetFileType, IKSBWManager��IKSSPManager
                +-kaecore.ini   �ڰ׻������ļ�
                +-kaecorea.dat  ͨ�úڰ׻�(Ҳ�ƽű�����), ������ӿڷ�װģ�����
				+-kaeolea.dat   ����ole��ģ��
                +-kaeunpack.dat ��������ѿ�ģ��, ���ѿǽӿڷ�װģ�����
                +-kaeunpak.dat  �����ļ��ĵĻ�ԭ����ģ��, �ṩ�ӿ�IKSUnpack
                +-kaext2.dat
                +-kaextend.dat
                +-karchive.dat  ѹ����, �Խ�ѹ�ļ�, ��װ���ļ��Ļ�ԭ����, �ṩ�ӿ�IKSArchive
             +-kas     ����ר�������ļ�
                +-kasengine.dll
             +-kavquara.dll ���������ļ�
             +-kis.dll      ����������
             +-ksecore.dll  ��ɱ��ϵͳ���Ŀ��
             +-ksejob.dll   ��ɱ��ϵͳ�̵߳���ģ��
             +-kspfeng.dll  ��ɱ��ϵͳ�ļ�ɨ����
             +-kspkas.dll   ��ɱ��ϵͳ�������ɨ����
             +-kssingle.dll ��ɱ��ϵͳ�����߰�
        +-kxewhite ��������ϵͳĿ¼
             |
             +-kavrep.dll ��������������֤�ļ�
             +-kxewfsys.dll ��������ϵͳ�ļ�
		+-kxeupdate ������ϵͳĿ¼
		     |
			 +-kxeupchk.dll ʵʱ��������ģ��
		+-userlog   �û���־Ŀ¼
		     |
			 +-kxeurlog.dll ����д�û���־��dll��Ϊkavevent.dll�ĸ���Ʒ(Ŀǰ�Ѿ�����ʹ�ã�2009-6-25,liusheng)
    +-driver64.exe 64λ������װж�س���(Ψһ��64λ����)
	+-kaearcha.dat �ļ�����(�ϰ汾)
	+-kaeboot.dat  �ļ�����(�ϰ汾)
	+-kaecall2.dll �ļ�����(�ϰ汾)
	+-kaecentr.dat �ļ�����(�ϰ汾)
	+-kaecore.dat  �ļ�����(�ϰ汾)
	+-kaecorea.dat �ļ�����(�ϰ汾)
	+-kaemaldt.dll �ļ�����(�ϰ汾)
	+-kaememex.dll �ļ�����(�ϰ汾)
	+-kaengcfg.dat �ļ�����(�ϰ汾)
	+-kaengine.dat �ļ�����(�ϰ汾)
	+-kaentrya.dat �ļ�����(�ϰ汾)
	+-kaeolea.dat  �ļ�����(�ϰ汾)
	+-kaeplat.dll  �ļ�����(�ϰ汾)
	+-kaeplata.dll �ļ�����(�ϰ汾)
	+-kaeprev.dll  �ļ�����(�ϰ汾)
	+-kaeproxy.dat �ļ�����(�ϰ汾)
	+-kaesgnld.dll �ļ�����(�ϰ汾)
	+-kaeunpack.dat�ļ�����(�ϰ汾)
	+-kaext2.dat   �ļ�����(�ϰ汾)
	+-kaextend.dat �ļ�����(�ϰ汾)
	+-karchive.dat �ļ�����(�ϰ汾)
	+-karescfg.dat �ļ�����(�ϰ汾)
    +-kav64.exe    ������
    +-kavevent.dll �����û���־����ļ�
    +-kavipc2.dll  ģ�ⵥ����ipc�ӿ�ʵ�ֵ��м�ת���ļ�
    +-kavlog2.exe  �û���־�鿴��
    +-kavpass2.dll passport��֤ģ��
    +-kavpassp.dll passport��֤ģ��
	+-kavpid.kid   ���������ж�ģ����ļ�,���ݲ�����
	+-kapolicy.exe ��signs.iniת��Ϊkaesign.pol�Ĺ���
    +-kavppwiz.dll passport��wizģ��
	+-kdevmgr.dll  ������װж��ģ��(��uplive.exe����)
	+-kiscall.exe  ģ����ó������ڽ�Ȩ�޵���
    +-kis.dll      �����Ļ���ģ��
    +-kissvc.dll   ������Service Callģ��
	+-kolhtml.dll  ��ֵ��֤Ƕ�����ҳģ��
    +-krecycle.exe ����ģ��ģ��
    +-kstart64.exe ����ģ��
    +-kxebase.dll  ��ܻ���ģ��
	+-kxecolct.exe ��������Ϣ�ռ�ģ��
	+-kxedump.dll  ��������ģ��
    +-kxeerror.dll ������鿴ģ��
    +-kxeserv.exe  ��ܷ������
	+-kxeupsrv.exe �����������Ŀǰ����������Service Call
    +-scom.dll     COM�������ģ��
    +-scomregsvr.exe COM���ע��ж��ģ��
	+-signs.ini    �����������ļ�
    +-updateex.dll ����������չģ��
    +-uplive.exe   ��������ģ��
    +-microsoft.vc80.crt ΢���crt��manifest
    +-msvcm80.dll  ΢��crtģ��
    +-msvcp80.dll  ΢��crtģ��
    +-msvcr80.dll  ΢��crtģ��
 @endcode

  @page kxe_ipc_interface "IPC������ؽӿ�"
   - @ref kxeipc_service_provider_interface_group
   - @ref kxeipc_idl_interface_group
   - @ref kxepipe_idl_interface_group
   - @ref kxehttp_idl_interface_group

 */

/**
  @page kxenameinfo_subsystem_define KXEngine virus name info service
   - @ref kxe_virus_name_info_service_provider_interface_group
   - @ref kxe_virus_name_info_data_group
 */

/**
  @page kxe_leakscan_subsystem_define KXEngine leakscan service
   - @ref kxe_leak_scan_service_provider_interface_group
   - @ref kxe_leak_scan_data_define_group
 */

/**
  @page kxe_popo_subsytem_define_2 KXEngine popo system service
   - @ref kxe_pop_server_service_provider_interface_group
   - @ref kxe_pop_server_data_define_group
 */
