#pragma once

#include <atlstr.h>
#include <atlrx.h>
#include <atlcoll.h>
#include "kclear/ICleanMgr.h"
#include "kclear/ICleanProc.h"
#include "3rdparty/tinyxml/tinyxml.h"

class CCleanManager :public ICleanMgr
{
public:
	CCleanManager(void);
	virtual ~CCleanManager(void);

	//���������
	//Return	int;
	//param	CString lib_file
	//param	void* pType;	CAtlMap<CString, TreeType>& pType
	//param void* pInfo;	CSimpleArray<TreeInfo>& m_arrScanReg
	virtual int LoadTreetruct(CString lib_file);

	//Ӧ�ó�������
	virtual void SetSoftInfoCallBack(SoftInfoCallBack pSoftInfoCallBack,void* pThis);
	//���ṹ��Ϣ
	virtual void SetTreeCallBack(SoftTreeCallBack pSoftTreeCallBack,void* pThis);

private:
	CString _libfile;

	//�����ص�ָ��
	SoftInfoCallBack m_pInfo;
	SoftTreeCallBack  m_pTree;
	void* m_pInfoThis;
	void* m_pTreeThis;
};