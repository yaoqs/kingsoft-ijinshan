/**
* @file     KPath.h
* @brief    ·����غ���
* @details  
* @author   �ֽ�(Linjie@kingsoft.com)
* @date     2009-4-3
*/

#pragma once

using namespace std;

namespace Kingsoft
{
	namespace Test
	{
		namespace CCF
		{
            namespace IO
            {
                /**
                * ����Windows·��
                */
                class KPath
                {
                public:					
					/**
					* @brief   ��ȡ��ǰExe���ڵ�Ŀ¼·��
					* @return  Ŀ¼·�������û��б��
					* @note	   ��������ʹ��KModule::GetCurrentModuleDirectory()��
					*		   ֮���Ҹ�ʱ����ɾ������������������޸��õ���������Ĺ���
					*/
					static wstring GetCurrentModuleFileDir();



					/**
					 * @brief ��ȡȫ·��
					 * @param const wstring & path
					 * @return std::wstring
					 * @note 
					 */
					static wstring GetFullPath(const wstring& path);

                    /**
                    * @brief   �ж�·���Ƿ����
                    */
                    static bool  Exists(const wstring& path);

                    /**
                    * @brief   �ϲ�·����
                    * @param   pathDir  ����·��
                    * @param   pathFile ���·��
                    * @return  std::wstring  �ϲ����·��
                    * @note
                    *      �ú���Ҳ����ִ��׷��·���Ĺ��ܣ���c:\\abc , abc.txt ִ�к���c:\\abc\\abc.txt
                    * @example
                    *       wstring path = L"c:\\abc\\uuu";
                    *       wstring pathMore = L"..\\g.txt";
                    *       path = KPath::Combine(path, pathMore);
                    *       // path ="c:\\abc\\g.txt"
                    */
                    static wstring Combine(const wstring& pathDir, const wstring& pathFile);

                    /**
                    * @brief   �Ƴ�·�����ķ�б��
                    * @param   path ·��
                    * @return  ���·������з�б�ܣ��Ǿͷ����Ƴ���б�ܵ�·�������û�У��򷵻�·����
                    * @example
                    *      wstring path = L"c:\\abc\\";
                    *      wstring actual = L"";
                    *      actual = KPath::RemoveLastBackslash(path);
                    *      // actual = L"c:\\abc"
                    */
                    static wstring RemoveLastBackslash(const wstring& path);

					/**
					 * @brief ��ȡĿ¼·��
					 * @param const wstring & path
					 * @return std::wstring
					 * @note 
					 */
					static wstring GetDirectoryName(const wstring& path);

					/**
					 * @brief ��ȡ�ļ���
					 * @param path
					 * @return std::wstring
					 * @note 
					 */
					static wstring GetFileName(const wstring& path);


					/*
					* @brief ��ȡ�ļ�����չ��
					* @param  path
					* @return 
					* @note 
					*/
					static wstring GetExtension(const wstring& path);


                    /**
                    * @brief   ��ȡ�ļ�����û����չ��
                    * @param   path ·���� �磺c:\example.txt
                    * @return  �����ļ�����û����չ���� �磺example
                    */
                    static wstring GetFileNameWithoutExtension(const wstring& path);

                };
            }
		}
	}
}