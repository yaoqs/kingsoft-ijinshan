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
				class KFile
				{
				private:
					WCHAR szFileName[MAX_PATH];

					/**
					* @brief ��ȡ�ļ��ľ��
					* @[in] param const wstring& filename	Ҫ��ȡ������ļ���
					* @return HANDLE	�ļ������ʧ�ܷ���INVALID_HANDLE_VALUE
					* @note:	���صľ������CloseHandle�ͷš�
					*/
					static HANDLE GetFileHandle(const wstring& filename);
				public:
					KFile(LPCWSTR szFileName);
					WCHAR* DigitalSignature() const;

					
					/**
					 * @brief ��ȡ�ļ������汾�źʹΰ汾��
					 * @param fileName �ļ�·��
					 * @param DWORD * pdwFileVersionMS ���汾��
					 * @param DWORD * pdwFileVersionLS �ΰ汾��
					 * @return bool
					 * @note 
					 */
					static bool GetFileVersion(const wstring& fileName, DWORD *pdwFileVersionMS, DWORD *pdwFileVersionLS);

					
					/**
					 * @brief ��ȡ�ļ��İ汾���ַ�������ʽΪ��2009.06.20.02
					 * @param fileName �ļ�·��
					 * @param fileVersion �汾���ַ���
					 * @return bool
					 * @note �����ʽ����xxxx.xx.xx.xx�������
					 *       GetFileVersion(const wstring& fileName, 
					 *                      DWORD *pdwFileVersionMS, 
					 *                      DWORD *pdwFileVersionLS);
					 *       Ȼ��������ƴ�ӡ�
					 */
					static bool GetFileVersion(const wstring& fileName, wstring& fileVersion);
					
					/**
					 * @brief �ļ��Ƿ����
					 * @param const wstring & path
					 * @return bool
					 * @note 
					 */
					static bool Exists(const wstring& path);

					/**
					 * @brief �����ļ�
					 * @param const wstring & sourceFileName
					 * @param const wstring & destFileName
					 * @param bool overwrite
					 * @return bool
					 * @note 
					 */
					static bool Copy(const wstring& sourceFileName, const wstring& destFileName, bool overwrite = true);

					
					/**
					 * @brief ɾ���ļ�
					 * @param const wstring & path
					 * @return bool
					 * @note ��������ļ�������ʱ��Ҳ����true
					 */
					static bool Delete(const wstring& path);

                    /**
                    * @brief �������ļ�
                    * @param oldPath  ���ļ�·��
                    * @param newPath  ���ļ�·��
                    * @param replaceWhenExist  �����ļ�·�������ǣ��Ƿ�ɾ����Ĭ�Ϸ񣬷���false
                    * @return bool
                    * @note ��������ļ�������ʱ������false
                    * @example
                             Rename(L"c:\\test.txt", L"c:\\test2.txt");
                    */
                    static bool Rename(const wstring& oldPath, const wstring& newPath, bool replaceWhenExist = false);

                    /**
                    * @brief   ����һ���ı��ļ�
                    * @param   filePath �ļ�·��
                    * @param   fileContent �ļ�����
                    * @param   bool isUTF8 �Ƿ���UTF8���룬 Ĭ��true
                    * @param   bool isUseBom �Ƿ����UTF8 Bom��Ĭ��true
                    * @example
                              CreateTextFile(L"c:\\test.txt", L"Kingsoft");
                    */
                    static bool CreateTextFile(const wstring& filePath, const wstring& fileContent, bool isUTF8 = true, bool isUseBom = true);

					/**
					 * @brief ��һ���ı��ļ�����������
					 * @param const wstring & path �ļ�·��
					 * @param bool isUTF8 �Ƿ���UTF8���룬 Ĭ��true
					 * @return std::wstring �ļ�������
					 * @note 
					 */
					static wstring ReadAllText(const wstring& path, bool isUTF8 = true);

					static wstring ReadAllTextUTF16(const wstring& path);

					/**
					* @brief �õ��ļ��Ĵ���ʱ��
					* @[in] param const wstring& path �ļ�·��
					* @[out] param LPFILETIME lpCreateTime ����ļ��Ĵ���ʱ��
					* @return �ɹ�����true, ʧ�ܷ���false
					*/
					static bool GetCreateTime(const wstring& path, LPFILETIME lpCreateTime);

					/**
					* @brief �õ��ļ���������ʱ��
					* @[in] param const wstring& path �ļ�·��
					* @[out] param LPFILETIME lpCreateTime ����ļ���������ʱ��
					* @return �ɹ�����true, ʧ�ܷ���false
					*/
					static bool GetLastAccessTime(const wstring& path, LPFILETIME lpLastAccessTime);

					/**
					* @brief �õ��ļ�������޸�ʱ��
					* @[in] param const wstring& path �ļ�·��
					* @[out] param LPFILETIME lpCreateTime ����ļ�������޸�ʱ��
					* @return �ɹ�����true, ʧ�ܷ���false
					*/
					static bool GetLastWriteTime(const wstring& path, LPFILETIME lpLastWriteTime);

                    /**
                    * @brief   ��ȡ�ļ���С
                    * @param   const wstring & path �ļ�4g·��
                    * @param   LARGE_INTEGER & fizeSize �ļ���С
                    * @return  bool
                    * @note    ֧��4G�����ļ�
                    */
                    static bool GetFileSize(const wstring& path, LARGE_INTEGER& fileSize);
				};
			}
		}
	}
}
