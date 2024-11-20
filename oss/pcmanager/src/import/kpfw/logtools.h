////////////////////////////////////////////////////////////////////////////////
//      
//      Kingsoft File for netmon
//      
//      File      : logtools.h
//      Version   : 1.0
//      Comment   : ��־��¼protocol buffer ���л�����
//      
//      Create at : 2008-3-17
//      Create by : liupeng
//      
////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include <string>

 void AssignProtocalString(std::string& strTarget, std::wstring& strSource);

 std::string ToProtocolString(std::wstring& strSource);

 std::string ToProtocolString(wchar_t* str);

 std::string ToProtocolString( char* pData, int nSize);

template<class T>
 std::string ToProtocolString(T* pData);

template<class T>
 std::string ToProtocolString(T* pData, int nSize);


 std::string ToProtocolString(const wchar_t* str);

 void ExtractProtocolString(std::wstring& strTarget, std::string& strSource);

HRESULT TimeToString( __time64_t nTime, ATL::CString& strTime );

//__time64_t FileTimeToTime( FILETIME time );