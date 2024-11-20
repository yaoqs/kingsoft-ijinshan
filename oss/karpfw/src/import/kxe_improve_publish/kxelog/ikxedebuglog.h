#ifndef _IKXEDEBUGLOG_H_
#define _IKXEDEBUGLOG_H_

class IKxEDebugLog
{
public:
	/**
	* @brief ������־�ĵ�����Ϣ
	* @remark
	* @param[in ] pszMessage ������Ϣ�ַ���
	* @return
	*/
	virtual void __stdcall debug(const char* pszMessage) = 0;
	virtual void __stdcall info(const char* pszMessage) = 0;
	virtual void __stdcall notice(const char* pszMessage) = 0;
	virtual void __stdcall warn(const char* pszMessage) = 0;
	virtual void __stdcall error(const char* pszMessage) = 0;
	virtual void __stdcall crit(const char* pszMessage) = 0;
	virtual void __stdcall alert(const char* pszMessage) = 0;
	virtual void __stdcall emerg(const char* pszMessage) = 0;
	virtual void __stdcall fatal(const char* pszMessage) = 0;
	virtual void __stdcall release() = 0;
};

#endif