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

//////////////////////////////////////////////////////////////////////////

#include <wtlhelper/whwindow.h>
#include "kscmain.h"
#include "ksctoolvector.h"
#include "msgdefine.h"
#include "kuires.h"
#include "uihandler_opt.h"
#include "uihandler_onekey.h"
#include "uihandler_bigfile.h"
#include "filtermenu.h"

//////////////////////////////////////////////////////////////////////////

// ����
#define IDC_LBL_MSGBOX_TITLE                60004
#define IDC_ICON_MSGBOX_ICON                60005
#define IDC_LBL_MSGBOX_TEXT                 60006
#define IDC_CHK_MSGBOX_NONOTIFYLATER        60007
#define IDC_DIV_MSGBOX_BUTTONS              60008
#define IDC_DIV_MSGBOX_CONTENT              60009
#define IDC_TAB_MAIN                        136

//////////////////////////////////////////////////////////////////////////

class CKscMainDlg
    : public CKuiDialogImpl<CKscMainDlg>
    , public CFilterMenu<CKscMainDlg>
{
public:
    DECLARE_WND_CLASS(L"{C9A5B730-1E5F-49A2-AAD5-025BBD1F43F0}")

	CKscMainDlg();
	~CKscMainDlg();

    BOOL OnNavigate(const CString& strNavigate);

	BOOL OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/);
	BOOL OnTabMainSelChange(int nTabItemIDOld, int nTabItemIDNew);
	void OnSize(UINT nType, CSize size);
    void OnDestroy();
	BOOL CanQuitNow()
	{
		return m_handlerOpt.CloseCheck();
	}

    ICleanTask* GetCleanProvider()
    {
        return &m_handlerOpt;
    }

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		KUI_NOTIFY_TAB_SELCHANGE(IDC_TAB_MAIN, OnTabMainSelChange)
	KUI_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CKscMainDlg)
        CHAIN_MSG_MAP(CKuiDialogImpl<CKscMainDlg>)
        CHAIN_MSG_MAP_MEMBER(m_handlerOpt)
        CHAIN_MSG_MAP_MEMBER(m_handlerOnekey)
        CHAIN_MSG_MAP_MEMBER(m_handlerBigFile)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_SIZE(OnSize)
        MSG_WM_DESTROY(OnDestroy)
        MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
        CHAIN_MSG_MAP(CFilterMenu<CKscMainDlg>)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	BOOL UpdateToolSize();

	KscToolVector		m_wndToolVector;
    CUIHandlerOpt		m_handlerOpt;
    CUIHandlerOnekey	m_handlerOnekey;
    CUIHandlerBigFile	m_handlerBigFile;
};

//////////////////////////////////////////////////////////////////////////
