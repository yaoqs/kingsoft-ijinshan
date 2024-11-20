/**
* @file     KStringConvert.h
* @brief    ת���ַ�������
* @details  
* @author   �ֽ�(Linjie@kingsoft.com)
* @date     2009-6-28
*/

#pragma once
#include <atlbase.h>

using namespace std;
namespace Kingsoft
{
	namespace Test
	{
		namespace CCF
		{
            namespace Text
            {
                /**
                * �ַ���ת����
                */
                class KStringConvert
                {
                public:

                    /**
                    * @brief   ���ַ�תΪխ�ַ�
                    * @param   wstr ���ַ���
                    * @param   ansiString խ�ַ���
                    * @return  �ɹ�����true����������false
                    */
                    static bool WideToAnsi(const wstring& wstr, string& ansiString);

                    /**
                    * @brief   ���ַ�תΪխ�ַ�
                    * @param   const wstring & wstr ���ַ���
                    * @return  std::string խ�ַ����� ���ת��ʧ�ܣ��򷵻ؿմ���
                    */
                    static string WideToAnsi(const wstring& wstr);

                    /**
                    * @brief   խ�ַ���תΪ���ַ���
                    * @param   str խ�ַ���
                    * @param   wideString ���ַ���
                    * @return  �ɹ�����true����������false
                    */
                    static bool AnsiToWide(const string& str, wstring& wideString);

                    /**
                    * @brief   խ�ַ���תΪ���ַ���
                    * @param   const string & str խ�ַ���
                    * @return  std::wstring ���ַ����� ���ת��ʧ�ܣ��򷵻ؿմ���
                    */
                    static wstring AnsiToWide(const string& str);

                    /**
                    * @brief   Utf8ת���ַ���
                    * @param   utf8string Utf8�ַ���
                    * @param   wideString ���ַ���
                    * @return  �ɹ�����true����������false
                    */
                    static bool Utf8ToWide(const string& utf8string, wstring& wideString);

                    /**
                    * @brief   UTF8�ַ���תΪ���ַ�
                    * @param   const string & utf8string UTF8�ַ���
                    * @return  std::wstring ���ַ����� ���ת��ʧ�ܣ��򷵻ؿմ���
                    */
                    static wstring Utf8ToWide(const string& utf8string);

                    /**
                    * @brief   ���ַ���תUtf8
                    * @param   widestring ���ַ���
                    * @param   utf8String Utf8�ַ���
                    * @return  �ɹ�����true����������false
                    */
                    static bool WideToUtf8(const wstring& widestring, string& utf8String);

                    /**
                    * @brief   ���ַ���תUtf8
                    * @param   widestring ���ַ���
                    * @return  string utf8�ַ����� ���ת��ʧ�ܣ��򷵻ؿմ���
                    */
                    static string WideToUtf8(const wstring& widestring);

                    static string AnsiToUtf8(const string& ansiStr);
                    static string Utf8ToAnsi(const string& utf8Str);

                    /** 
                    * @brief   ʵ���ַ����滻 
                    * @param   originalStr Դ�� 
                    * @param   oldStr  ���ҵĴ� 
                    * @param   newStr  �滻���´� 
                    * @return  �����޸ĺ�Ĵ� 
                    * @example
                        wstring originalStr=L"a,b,c";
                        wstring replacedStr = Replace(originalStr, L",", L".");
                        // replacedStr = L"a.b.c"
                    */
                    static wstring Replace(const wstring& originalStr, const wstring& oldStr, const wstring& newStr);

                    /**
                    * @brief   ���ַ���תΪ��д
                    * @param   orignalStr Դ�ַ���
                    * @return  std::wstring ת������ַ���
                    */
                    static wstring ToUpper(const wstring& orignalStr);
                    static string ToUpper(const string& orignalStr);


                    /**
                    * @brief   ���ַ���תΪСд
                    * @param   const wstring & orignalStr
                    * @return  std::wstring ת������ַ���
                    */
                    static wstring ToLower(const wstring& orignalStr);

                    static string ToLower(const string& orignalStr);

                    /**
                    * @brief   �ַ���ת��Ϊ��������
                    * @param   wstr  �ַ������磺��True���������ִ�Сд
                    * @return  bool  ��true/True��ת��Ϊtrue������תΪfalse
                    * @note
                            boost ���е�ת��ֻ֧�֡�1��ת��Ϊtrue����֧�֡�True����ת����
                    */
                    static bool WStringToBool(const wstring& wstr);


                    /**
                    * @brief   ��������ת��Ϊ�ַ���
                    * @param   bool  ����ֵ
                    * @return  std::wstring ת������ַ�����true��ת��Ϊ��True����falseת��Ϊ��False��
                    * @note
                           boost ���е�ת��ֻ֧��trueת��Ϊ��1����falseת��Ϊ��0��
                    */
                    static wstring BoolToWString(bool value);


					/**
					 * @brief ��ʽ�ַ���
					 * @param wstring format
					 * @param ...
					 * @return std::wstring
					 * @note ע�⣡����...��������ֱ�Ӵ�wstring����Ϊԭ����...ֻ֧��wchar_t����֧��wstring��
					 *		 ���ʹ��ʱ������ǵ���wstring�����c_str()�������磺
					 *		 wstring fileName;
					 *		 KStringConvert.Format(L"%s", fileName.c_str());
					 */
					static wstring Format(wstring format, ...);

                    /**
					 * @brief ��ʽ�ַ���
					 * @param string format
					 * @param ...
					 * @return string
					 * @note ע�⣡����...��������ֱ�Ӵ�string����Ϊԭ����...ֻ֧��char����֧��string��
					 *		 ���ʹ��ʱ������ǵ���string�����c_str()�������磺
					 *		 string fileName;
					 *		 KStringConvert.Format("%s", fileName.c_str());
					 */
					static string Format(string format, ...);

					/**
					* @brief	��ͨC++�ַ���ת����BSTR
					* @param const wstring& text
					* @note ���ص�BSTR�ַ�����Ҫ��::SysFreeString���������ͷ�
					*/
					static BSTR WStringToBSTR(const wstring& text);

					/**
					* @brief	BSTR�ַ���ת������ͨC++�ַ���
					* @param	const BSTR bsText
					* @note
					*/
					static wstring BSTRToWString(const BSTR bsText);


					/**
					 * @brief �ָ��ַ���
					 * @param const wstring & str
					 * @param const wstring & delimiter �ָ���
					 * @param int maxSplit ���ָ�����
					 * @return vector<wstring>
					 * @note 
					 */
					static vector<wstring> Split(const wstring& str, const wstring& delimiter = L" ", int maxSplit = -1);

					/**
					 * @brief ȥ����λ�ո�
					 * @param const wstring & str
					 * @return std::wstring
					 * @note 
					 */
					static wstring Trim(const wstring& str);

					/**
					 * @brief ȥ��ǰ��Ŀո�
					 * @param const wstring & str
					 * @return std::wstring
					 * @note 
					 */
					static wstring TrimLeft(const wstring& str);

					/**
					 * @brief ȥ��β���Ŀո�
					 * @param const wstring & str
					 * @return std::wstring
					 * @note 
					 */
					static wstring TrimRight(const wstring& str);
                };
            }
		}
	}
}
