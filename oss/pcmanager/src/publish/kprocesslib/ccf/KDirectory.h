/**
* @file     KDirectory.h
* @brief    �ṩ�ļ��п�������
* @details  
* @author   �ֽ�(Linjie@kingsoft.com)
* @date     2009-6-17
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
                // ����ѡ��
                enum SearchOption
                {
                    // Includes only the current directory in a search.
                    TopDirectoryOnly,

                    // Includes the current directory and all the subdirectories in a search operation.
                    AllDirectories
                };

                class KDirectory
                {
                public:
                    /**
                    * @brief   ʵ��Ŀ¼������Ŀ¼����������
                    * @param   srcDirName      ԴĿ¼,����������\��Ҳ����û��
                    * @param   destDirName  Ŀ��Ŀ¼,����������\��Ҳ����û��
                    * @return  bool
                    * @note ���Ŀ��Ŀ¼�Ѵ��ڻḲ�ǣ�ԴĿ¼�����ڷ���false��
                    *       ���ƹ��������ļ�ʧ�ܷ���false.
                            ��ԴĿ¼ ��Ŀ��Ŀ¼Ϊ�գ��򷵻�false
                    */
                    static bool Copy(const wstring& srcDirName, const wstring& destDirName);

                    
					
					/**
					 * @brief ʵ��ɾ��Ŀ¼������Ŀ¼������
					 * @param wstring dirPath Ҫɾ����Ŀ¼·��
					 * @param bool deleteRoot �Ƿ�ɾ������Ŀ¼��
					 *		  ���Ϊtrue����ɾ������Ŀ¼��(Ĭ��)
					 *		  ���Ϊfalse����ɾ����Ŀ¼�µ������ļ������ļ��С�
					 * @return bool
					 * @note ��dirPathΪ�գ��򷵻�false
					 */
					static bool Delete(const wstring& dirPath, bool deleteRoot = true);

					
					/**
					 * @brief �ж�Ŀ¼�Ƿ����
					 * @param wstring dirPath
					 * @return bool
					 * @note ��dirPathΪ�գ��򷵻�false
					 */
					static bool Exists(const wstring& dirPath);


					/**
					 * @brief ��ȡ��ǰ·��
					 * @return std::wstring
					 * @note 
					 */
					static wstring GetCurrentDirectory();

					
					/**
					 * @brief ���õ�ǰ·��
					 * @param const wstring & path
					 * @return bool
					 * @note ��pathΪ�գ��򷵻�false
					 */
					static bool SetCurrentDirectory(const wstring& path);

                    /**
                    * @brief   ��ȡָ��Ŀ¼�������ļ�
                    * @param   path Ŀ¼·��
                    * @param   option  ����ѡ��, Ĭ��ΪTopDirectoryOnly
                    * @return  vector<wstring>  �����ļ�·��
                    * @note    ��pathΪ�գ��򷵻�false
                    */
                    static vector<wstring> GetFiles(const wstring& path, SearchOption option = TopDirectoryOnly, wstring fileNamePattern = L"*.*");

                    /**
                    * @brief   ��ȡָ��Ŀ¼������Ŀ¼
                    * @param   path   Ŀ¼·��
                    * @param   option ����ѡ��, Ĭ��ΪTopDirectoryOnly
                    * @return  vector<wstring> ����Ŀ¼·��
                    * @note    ��pathΪ�գ��򷵻�false
                    */
                    static vector<wstring> GetDirectories(const wstring& path, SearchOption option = TopDirectoryOnly);


                    /**
                    * @brief   Creates all directories and subdirectories as specified by path.
                    * @param   path The directory path to create. 
                    * @return  bool
                    * @note    ��pathΪ�գ��򷵻�false
                    */
                    static bool CreateDirectory(const wstring& path);

                    /**
                    * @brief   ������Ŀ¼
                    * @param   oldPath ��Ŀ¼·��
                    * @param   newPath ��Ŀ¼·��
                    * @param   bool deleteWhenNewPathExist  ����Ŀ¼����ʱ���Ƿ�ɾ��
                    * @return  bool
                    * @note    �������Ŀ¼���Ŀ¼����һ����Ŀ¼�£��ͻ�ִ���ƶ�����·���¡�
                    *          ��pathΪ�գ��򷵻�false
                    * @example
                               Rename(L"c:\\test", L"c:\\test2");
                               Rename(L"c:\\test", L"d:\\test2", false);
                    */
                    static bool Rename(const wstring& oldPath, const wstring& newPath, bool deleteWhenNewPathExist = false);
                };
            }
		}
	}
}
