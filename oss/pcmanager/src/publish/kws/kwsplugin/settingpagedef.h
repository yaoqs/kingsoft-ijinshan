/* -------------------------------------------------------------------------
//	FileName	��	settingpagedef.h
//	Creator		��	zhoufeng
//	Date		��	2010/5/11 10:28:28
//	Brief		��	���öԻ����һЩͨ�ö���
//
//	$Id: $
// -----------------------------------------------------------------------*/
#ifndef __SETTINGPAGEDEF_H__
#define __SETTINGPAGEDEF_H__

// -------------------------------------------------------------------------
enum EM_INIT_PAGE
{
	em_trustlist_page		= 0,		// ����������
	em_adblack_page			= 1,		// �����˹�������
	em_adfilter_page		= 2,		// �������
	em_download_safe_page   = 3,		// ���ذ�ȫ����
	em_setbrower_page       = 4         // ���������
};

class ISettingUI
{
public:

	/**
	* @brief        ��ѯĳ����ҳ�Ƿ��Ѿ��޸�������
	* @return		TRUE �Ѿ��޸ģ�����Ϊ�޸�
	*/
	virtual BOOL __stdcall IsApplyEnable() = 0;

	/**
	* @brief        ��ĳ����ҳ��������
	* @return		TRUE ����ɹ������򱣴�ʧ��
	*/
	virtual BOOL __stdcall DoSettingApply() = 0;

};

// -------------------------------------------------------------------------
// $Log: $

#endif /* __SETTINGPAGEDEF_H__ */
