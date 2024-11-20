
#pragma once

interface IKpfwFrame
{
	/**
	*@param void
	*@return TRUE: msn�Ѿ�����  FLASE msn �Ѿ��ر�
	*/
	virtual STDMETHODIMP_(BOOL) GetMsnEnable() = 0;


	/**
	*@param TRUE ����msn  FLASE �ر�msn
	*@return TRUE: ���óɹ�  FLASE ����ʧ��
	*/
	virtual STDMETHODIMP_(BOOL) SetMsnEnable( BOOL bEnable ) = 0;

	/**
	*@param void 
	*@return TRUE: �򿪳ɹ� FLASE ��ʧ��
	��@ ��Ӧ�ó������༭��
	*/
	virtual STDMETHODIMP_(BOOL) OpenAppRule( ) = 0;

	/**
	*@param void 
	*@return TRUE: �򿪳ɹ� FLASE ��ʧ��
	��@ ���������Ӳ鿴��
	*/
	virtual STDMETHODIMP_(BOOL) OpenNetAct( ) = 0;

	/**
	*@param void 
	*@return TRUE: �򿪳ɹ� FLASE ��ʧ��
	��@ ����־�鿴��
	*/
	virtual STDMETHODIMP_(BOOL) OpenLog( ) = 0;


	/**
	*@param void 
	*@return TRUE: �򿪳ɹ� FLASE ��ʧ��
	��@ �ر�����������
	*/
	virtual STDMETHODIMP_(BOOL) CloseKpfwMain( LPCTSTR pszHtml ) = 0;

	/**
	*@param [out]����ip�ַ�����[in]����ip
	*@return ת���ɹ� FLASE ת��ʧ��
	��@ ULOG תip�ַ���
	*/
	virtual STDMETHODIMP_(BOOL) IpToString( ULONG uIp, LPTSTR pszIp ) = 0;

	/**
	*@param [out]pszMac �����ַ��� [in] n0, n1, n2, n3, n4, n5
	*@return TRUE: ת���ɹ� FLASE ת��ʧ��
	��@ macת�ַ���
	*/
	virtual STDMETHODIMP_(BOOL) MacToString( int n0, int n1, int n2, int n3, int n4, int n5, LPTSTR pszMac ) = 0;

	/**
	*@param [in]bOpen TRUE Ϊ���ļ� FALSE Ϊ�����ļ�
	*       [out] pszFullPath �Ż��û�ѡ�е��ļ�, ���Ϊ���ַ�����ʾ�û�û��ѡ��·��
	*@return TRUE: �򿪳ɹ� FLASE ��ʧ��
	��@ �û����ļ�·��ѡ����
	*/
	virtual STDMETHODIMP_(BOOL) OpenFileDlg( BOOL bOpen, LPTSTR pszFullPath ) = 0;
		
};