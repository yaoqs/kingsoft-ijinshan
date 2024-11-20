// Copyright (c) 2010 Kingsoft Corporation. All rights reserved.
// Copyright (c) 2010 The KSafe Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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