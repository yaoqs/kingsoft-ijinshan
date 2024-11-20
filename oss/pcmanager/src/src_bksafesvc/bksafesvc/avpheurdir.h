/**
* @file    avpheurdir.h
* @brief   ...
* @author  bbcallen
* @date    2010-07-13 19:40
*/

#ifndef AVPHEURDIR_H
#define AVPHEURDIR_H

#include <atlstr.h>
#include <atlcoll.h>

NS_SKYLARK_BEGIN

class CAvpHeurDir
{
public:
    // ���عؼ�Ŀ¼,��������ʽ����
    HRESULT LoadHeuristDir();
    BOOL    IsFileUnderHeuristDir(LPCWSTR lpszFile);

    HRESULT AddHeurDir(LPCWSTR lpszDirectory, BOOL bNormailized);

protected:
    CAtlMap<CString, DWORD> m_HeurDirMap;
};

NS_SKYLARK_END

#endif//AVPHEURDIR_H