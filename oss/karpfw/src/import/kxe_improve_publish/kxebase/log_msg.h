#pragma once
#include <stdio.h>
#include <iostream>
#include <cassert>
#include <vector>
#include "kxebase_log.h"
#include "../kxelog/log_priority.h"
#include "../scom/scom/singleton.h"

/**
 * @defgroup kxengine_debug_log_interface KXEngine Architecture Debug Log Interface
 * @{
 */

class KxEDebugLogMsg
{
public:
	KxEDebugLogMsg()
	{
		m_hLog = NULL;
	}

	~KxEDebugLogMsg()
	{
		assert(m_hLog == NULL);
	}

	int Log(
		KXE_LOG_LEVEL level, 
		const char* pszFormat, 
		...
		)
	{
		va_list args;
		va_start(args, pszFormat);

		int nRet = LogV(
			level,
			pszFormat,
			args
			);

		va_end(args);
		return nRet;
	}

	int LogV(
		KXE_LOG_LEVEL level, 
		const char* pszFormat, 
		va_list args
		)
	{
		/*��ȡ��־��Ϣ��д����־��*/
		char szBuffer[1024] = {0};
#if _MSC_VER == 1400
		int nCount = vsnprintf_s(
			szBuffer,
			1024, 
			_TRUNCATE,
			pszFormat, 
			args
			);
#else
		int nCount = _vsnprintf(
			szBuffer,
			1024,
			pszFormat,
			args
			);
#endif

		int nRet = 0;
		if (nCount == -1 || nCount == 1024)  // buffer������
		{
#if _MSC_VER == 1400
			nCount = _vscprintf(
				pszFormat,
				args
				);
			std::vector<char> vecBuffer(nCount + 1);

			vsnprintf_s(
				&vecBuffer[0],
				vecBuffer.size(),
				_TRUNCATE,
				pszFormat,
				args
				);
#else
			nCount = vprintf(
				pszFormat,
				args
				);
			std::vector<char> vecBuffer(nCount + 1);

			_vsnprintf(
				&vecBuffer[0],
				vecBuffer.size(),
				pszFormat,
				args
				);
#endif
			nRet = kxe_base_debug_log(
				m_hLog, 
				level, 
				&vecBuffer[0]
			);
		}
		else
		{
			nRet = kxe_base_debug_log(
				m_hLog, 
				level, 
				szBuffer
				);
		}

		return nRet;
	}

public:
	int CreateLogInstance(const char* pszName)
	{
		return kxe_base_create_debug_log(
			pszName,
			&m_hLog
			);

	}

	int CloseLogInstance()
	{
		int nRet = kxe_base_close_debug_log(m_hLog);
		m_hLog = NULL;

		return nRet;
	}
private:
	kxe_log_t m_hLog;
};

typedef SingletonHolder<KxEDebugLogMsg> KxEDebugLogMsgSinglton;

#ifdef NO_DEBUG_LOG

#define KXE_INIT_DEBUG_LOG(name)

#define KXE_DEBUG_LOG(X)

#define KXE_DEBUG_LOG_V(X)

#define KXE_FINI_DEBUG_LOG()

#else

/**
 * @brief ��ʼ������name���ֵĵ�����־������
 * @param[in] name ����������־������,�������,һ��ʹ����ϵͳ����
 */
#define KXE_INIT_DEBUG_LOG(name) \
	do\
{\
	KxEDebugLogMsgSinglton::Instance().CreateLogInstance(name);\
	KxEDebugLogMsgSinglton::Instance().Log(LOG_INFO, "To start debugging.");\
} while (0)

/**
 * @brief ������־�����
 * @param[in] X �������־����,�ֱ�ΪKXE_LOG_LEVEL, format string, arg
 * @remark ���÷�ʽΪKXE_DEBUG_LOG((LOG_INFO, "just for test %s", "test"));
 */
#define KXE_DEBUG_LOG(X) \
	do\
{\
	KxEDebugLogMsgSinglton::Instance().Log X;\
} while (0)

/**
 * @brief ������־�����
 * @param[in] X �������־����,�ֱ�ΪKXE_LOG_LEVEL, format string, va_list
 * @remark ���÷�ʽΪKXE_DEBUG_LOG((LOG_INFO, "just for test %s", va_list));
 */
#define KXE_DEBUG_LOG_V(X) \
	do\
{\
	KxEDebugLogMsgSinglton::Instance().LogV X;\
} while (0)

/**
 * @brief �ر���־���
 */
#define KXE_FINI_DEBUG_LOG() \
	do\
{\
	KxEDebugLogMsgSinglton::Instance().Log(LOG_INFO, "To end debugging.");\
	KxEDebugLogMsgSinglton::Instance().CloseLogInstance();\
} while (0);


#endif

class KxEFunctionTraceDebugLog
{
public:
	KxEFunctionTraceDebugLog(
		const char* pszFunctionName,
		KXE_LOG_LEVEL logLevel,
		const char* pszFileName,
		int nLine
		) : m_pszFunctionName(pszFunctionName), m_level(logLevel)
	{
		KXE_DEBUG_LOG((
			logLevel,
			"Enter Function %s at file %s in line %d", 
			pszFunctionName,
			pszFileName,
			nLine
			));
	}

	~KxEFunctionTraceDebugLog()
	{
		KXE_DEBUG_LOG((
			m_level,
			"Leave Function %s", 
			m_pszFunctionName
			));
	}

private:
	const char* m_pszFunctionName;
	KXE_LOG_LEVEL m_level;
};

/// ��������׷�ٺ�
#define KXE_FUNCTION_TRACE() \
	KxEFunctionTraceDebugLog __dummyLog__(__FUNCTION__, LOG_INFO, __FILE__, __LINE__);

/**
 * @}
 */
