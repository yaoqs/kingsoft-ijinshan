#include "stdafx.h"
#include "kglobal.h"

BOOL g_bStop[TRASHCLASS] = {
    FALSE, //��ͨ����
    FALSE,  //һ������
    FALSE   //���
};

HWND g_hWndKClear = NULL;