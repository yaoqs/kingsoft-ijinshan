/**
* @file     KModule.h
* @brief    �ṩϵͳ������صĺ���
* @details  
*/

#pragma once

#include <shlobj.h>

using namespace std;

namespace Kingsoft
{
	namespace Test
	{
		namespace CCF
		{
			namespace System
			{
				class KModule
				{
				public:

					/**
					* @brief ��ȡ��ǰģ���Ŀ¼·��
					* @return std::wstring ·��
					* @note 
					*/
					static wstring GetCurrentModuleDirectory();

					/**
					* @brief ��ȡ��ǰģ����ļ���
					* @return std::wstring �ļ���
					* @note 
					*/
					static wstring GetCurrentModuleFileName();

					static wstring GetCurrentModuleFilePath();
				};
			}
		}
	}
}