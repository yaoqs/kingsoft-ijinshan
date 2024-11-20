/**
* @file    avploader.h
* @brief   ...
* @author  bbcallen
* @date    2010-04-09 14:28
*/

#ifndef AVPLOADER_H
#define AVPLOADER_H

#include "skylark2\skylarkbase.h"
#include "skylark2\bkeng.h"
#include "skylark2\bkatrun.h"
#include "skylark2\bkbak.h"
#include "skylark2\bkcache.h"

/**
* @brief    ��������ģ��
* @param    lpszEngineDir   ����ģ�����ڵ�Ŀ¼,���ΪNULL,��ȡ��ǰģ������Ŀ¼
*/
EXTERN_C HRESULT WINAPI BKEngLoad(LPCWSTR lpszEngineDir = NULL);

#endif//AVPLOADER_H