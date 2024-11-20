#pragma once

#include <softmgr/ISoftInstall.h>
#include <softmgr/iksautoinstcallback.h>

namespace ksm
{

typedef struct PluginInfo
{
	CString		_key;
	CString		_name;
	BOOL		_state;
	BOOL		_curState;
} *PPluginInfo;

typedef CSimpleArray<PluginInfo>  PluginInfoList;

typedef struct InstInfo
{
	DWORD		_instTimeout;
	CString		_instPackPath;
	CString		_downUrl;
	CString		_downName;
	CString		_downMd5;
	CString		_instDir;
	ULONGLONG	_downSize;
	ULONGLONG	_instSize;
	BOOL		_bUseVirtualDesk;
	PluginInfoList _pluginInfoList;

	InstInfo()
	{
		_instTimeout = 0;
	}
} *PInstInfo;

typedef CAtlMap<DWORD, InstInfo> InstInfoMap;
	
class CSoftInstProxy
{
public:
	CSoftInstProxy();
	~CSoftInstProxy();

	void SetNotify(IKSAutoInstCallBack2 *pNotify) 
	{ _pNotify = pNotify; }
	BOOL Initialize(LPCWSTR pKSafePath);
	void Uninitialize();

	// ��ȡ��װ��Ϣ�б����ó�ʼ������Ч��
	const InstInfoMap& GetInstInfoMap() const 
	{ return _instInfoMap; }

	const InstInfo*	GetInstInfo(DWORD nId) const;
	// ���ð�װĿ¼
	void SetInstDir(LPCWSTR pInstDir) 
	{ _instDir = pInstDir; }
	// ���ð�װ��·��
	BOOL SetInstPackPath(DWORD id, LPCWSTR pInstPackPath);
	// ���ò����Ϣ
	BOOL SetPluginInfo(DWORD id, LPCWSTR pPluginKey, BOOL state);
	// ��ʼ/ֹͣ��װ���
	BOOL StartInstSoft(DWORD id);
	void StopInstSoft();

private:
	BOOL LoadInstLib(LPCWSTR pLibPath);

private:
	HMODULE _hModSoftMgr;

	CString _instDir;
	InstInfoMap _instInfoMap;
	ISoftInstall *_pISoftInst;
	IKSAutoInstCallBack2 *_pNotify;
};

}