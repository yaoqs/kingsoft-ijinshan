#ifndef KCLEAR_TRASHONEKEY_H_
#define KCLEAR_TRASHONEKEY_H_

//////////////////////////////////////////////////////////////////////////

#include "kclear/ionekeyclean.h"
#include "configdata.h"
#include "filelistdata.h"

//////////////////////////////////////////////////////////////////////////
// һ������֧��
class KTrashOnekeyTask : public ICleanTask
{
public:
    KTrashOnekeyTask();
    ~KTrashOnekeyTask();

    //��ʼ��
    HRESULT __stdcall Initialize();

    //����ʼ��
    HRESULT __stdcall Uninitialize();

    //���ûص�
    void __stdcall SetCallback(ICleanCallback* pCallBack);

   //ֹͣ���
    bool __stdcall StopClean();

    //��ʼ���
    bool __stdcall StartClean(int nTask,const char* szTask);

    void __stdcall Release()
    {
        delete this;
    }

private:
    BOOL IsCleaning() const;
    void RunCleanFile();
    static DWORD WINAPI CleanFileThread(LPVOID lpVoid);

    bool SplitStrTask( 
        /*[in]*/  std::wstring str, 
        /*[out]*/ std::vector <std::wstring>& vcResult,
        /*[in]*/  char delim = ','
        );
 
    ICleanCallback* m_pCallBack;       //�ص�
    CConfigData m_config;
    CFileListData  m_FileListData;
    HANDLE m_hThread;
    DWORD  m_dwThreadID;
    CConfigData::DirWorkArray m_DirWorks;
    DWORD m_ulTotalJunkFileSize;
    int m_nCurrentIndex;
    CFileDelete DelFile;
    std::map<std::wstring,bool> TaskMap;
    std::vector<std::wstring> TaskVector;
    std::vector<std::wstring> TaskDesc;
    std::wstring strDesc;  
};

//////////////////////////////////////////////////////////////////////////
// �ṩ��һ������
bool __cdecl GetTrashCleanerForOnekey(const GUID& riid, void** ppv);

//////////////////////////////////////////////////////////////////////////

#endif // KCLEAR_TRASHONEKEY_H_
