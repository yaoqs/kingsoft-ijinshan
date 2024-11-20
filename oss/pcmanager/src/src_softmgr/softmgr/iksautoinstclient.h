//=================================================================
/**
* @file iksautoinstclient.h 
* @brief
* @author zhengyousheng <zhengyousheng@kingsoft.com>
* @data 2010-11-06 11:22
*/
//=================================================================

#pragma once
#include <Unknwn.h>
#include <softmgr/iksautoinstcallback.h>

// {F908EA8A-745E-4322-9E1F-088381A1D3C0}
// IMPLEMENT_OLECREATE(<<class>>, <<external_name>>, 
// 					0xf908ea8a, 0x745e, 0x4322, 0x9e, 0x1f, 0x8, 0x83, 0x81, 0xa1, 0xd3, 0xc0);
[
	uuid("F908EA8A-745E-4322-9E1F-088381A1D3C0")
]
interface IKSAutoInstClient
{
	/**
	* @brief ��ʼ��
	* @param[in] lpwszXmlCfg ��������ļ�·��
	* @param[in] lpReserved ��������, Ŀǰ��ʱδ��,ֱ�Ӵ�NULL
	* @return 0 �ɹ�������Ϊʧ�ܴ�����
	*/
	virtual HRESULT STDMETHODCALLTYPE Init(LPCWSTR lpwszXmlCfg, LPVOID lpReserved) = 0;

	/**
	* @brief ���ûص�
	* @param[in] piInstallCallBack �ص��ӿ�
	* @return 0 �ɹ�������Ϊʧ�ܴ�����
	*/
	virtual HRESULT STDMETHODCALLTYPE SetCallBack(IKSAutoInstCallBack* piInstallCallBack) = 0;

	/**
	* @brief ��װ�����е����
	* @param[in] lpszGBKXmlBuffer �����xml���ã���bufferΪgbk���룬���а������ID����װ��·�����û��Զ�����Ϣ
	* @parma[in] nBufferSize buffer��С,��byteΪ��λ
	* @return 0 �ɹ�������Ϊʧ�ܴ�����
	*/
	/*
	lpwszXmlConfig��ʽ��
	<soft ver="1.0">
	   <softinfo softid="1" inst_pack="d:\qq.exe" >
//	   <download url="" md5="" save_name="" file_size="" inst_size="" />
		 <inst_dir>C:\xxxxx</inst_dir>
	     <user_define count="3" >
			 <item name="$ctrl_name_1" value="0" info="����QQ����2.9" />
			 <item name="$ctrl_name_2" value="1" info="��ʾ������" />
	     </user_define>
	   </softinfo>
	</soft>
	*/
	virtual HRESULT STDMETHODCALLTYPE StartInstSoft(LPCSTR lpszGBKXmlBuffer, int nBufferSize) = 0;

	/**
	* @brief ֹ֪ͨͣ
	* @return 0 �ɹ�������Ϊʧ�ܴ�����
	*/
	virtual HRESULT STDMETHODCALLTYPE NotifyStop() = 0;

	/**
	* @brief ����ʼ
	* @return 0 �ɹ�������Ϊʧ�ܴ�����
	*/
	virtual HRESULT STDMETHODCALLTYPE UnInit() = 0;

	/**
	* @brief ���ü�������
	*/
	virtual HRESULT STDMETHODCALLTYPE AddRef() = 0;
	virtual HRESULT STDMETHODCALLTYPE Release() = 0;
};