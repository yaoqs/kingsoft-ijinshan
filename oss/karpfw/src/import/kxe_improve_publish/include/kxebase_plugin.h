//////////////////////////////////////////////////////////////////////
///		@file		kxebase_plugin.h
///		@author		luopeng
///		@date		2008-9-17 09:07:58
///	
///		@brief		��չSDK�Ķ��巽ʽ,��չ��SDK���붨�������������
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../kxebase/kxebase_plugin_marco.h"

/**
* @page kxebase_plugin_sdk KXEngine SDK Plugin
* @section kxebase_plugin_sdk_face ������ʽ
* - ͨ��DLLʹ��C�����ķ�ʽ�����º�������,�������pluginĿ¼
* @section kxebase_plugin_sdk_function ��������
* - @ref type_kxe_sdk_plugin_initialize
* - @ref type_kxe_sdk_plugin_uninitialize
* - @ref type_kxe_sdk_plugin_start
* - @ref type_kxe_sdk_plugin_stop
* - @ref type_kxe_sdk_plugin_get_name
* @section kxebase_plugin_sdk_function_name �������ĺ�
* - @ref KXE_SDK_PLUGIN_INIT
* - @ref KXE_SDK_PLUGIN_FINI
* - @ref KXE_SDK_PLUGIN_START
* - @ref KXE_SDK_PLUGIN_STOP
* - @ref KXE_SDK_PLUGIN_GET_NAME
* 
*/

/**
 * @brief ��չSDK��Ҫ����ĺ�����,kxebase����ô˺�������plugin��ʼ��
 */
#define KXE_SDK_PLUGIN_INIT "kxe_sdk_plugin_initialize"

/**
* @brief ��չSDK��Ҫ����ĺ�������,kxebase����ô˺�������plugin��ʼ��
*/
typedef int __stdcall type_kxe_sdk_plugin_initialize();

/**
* @brief ��չSDK��Ҫ����ĺ�����,kxebase����ô˺�������plugin����ʼ��
*/
#define KXE_SDK_PLUGIN_FINI "kxe_sdk_plugin_uninitialize"

/**
* @brief ��չSDK��Ҫ����ĺ�������,kxebase����ô˺�������plugin����ʼ��
*/
typedef int __stdcall type_kxe_sdk_plugin_uninitialize();

/**
* @brief ��չSDK��Ҫ����ĺ�����,kxebase����ô˺�������plugin
*/
#define KXE_SDK_PLUGIN_START "kxe_sdk_plugin_start"

/**
* @brief ��չSDK��Ҫ����ĺ�������,kxebase����ô˺�������plugin
*/
typedef int __stdcall type_kxe_sdk_plugin_start();

/**
* @brief ��չSDK��Ҫ����ĺ�����,kxebase����ô˺���ֹͣplugin
*/
#define KXE_SDK_PLUGIN_STOP "kxe_sdk_plugin_stop"

/**
* @brief ��չSDK��Ҫ����ĺ�������,kxebase����ô˺�������plugin
*/
typedef int __stdcall type_kxe_sdk_plugin_stop();

/**
* @brief ��չSDK��Ҫ����ĺ�����,kxebase����ô˺�����ȡ��plugin������
*/
#define KXE_SDK_PLUGIN_GET_NAME "kxe_sdk_plugin_get_name"

/**
* @brief ��չSDK��Ҫ����ĺ�������,kxebase����ô˺�����ȡ��plugin������
*/
typedef const char* __stdcall type_kxe_sdk_plugin_get_name();

