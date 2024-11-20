/********************************************************************
	created:	2010/05/26
	created:	26:5:2010   10:14
	filename: 	libkschelper.h
	author:		Jiang Fengbing
	
	purpose:	����ר���������ƽӿ�
*********************************************************************/

#ifndef LIBKSCHELPER_INC_
#define LIBKSCHELPER_INC_

//////////////////////////////////////////////////////////////////////////

/**
 * ��װ/ж������
 */
bool __stdcall InstallKscHelper(HINSTANCE hInstance);
bool __stdcall UnInstallKscHelper();

/**
 * ����/ֹͣ����
 */
bool __stdcall StartKscHelper();
bool __stdcall StopKscHelper();

/**
 * ׼������
 * ��KscOpenVolumeǰ���ã��������û�а�װ�����������Զ���װ������
 */
bool __stdcall PrepareKscHelper(HINSTANCE hInstance);


/**
 * ��/�رվ��豸
 * ����ʹ��ReadFile����WriteFile���ж�����д
 */
HANDLE __stdcall KscOpenVolume(const wchar_t szVolume[]);
BOOL __stdcall KscCloseVolume(HANDLE hVolume);

//////////////////////////////////////////////////////////////////////////

#endif	// LIBKSCHELPER_INC_
