////////////////////////////////////////////////////////////////////////////////
//      
//      File for url cache manager
//      
//      File      : systool.h
//      Version   : 1.0
//      Comment   : �ṩһ�����ʹ����ڴ����
//      
//      Create at : 2010-2-3
//      Create by : liupeng
//		Motify by : 
//      
///////////////////////////////////////////////////////////////////////////////

#pragma once

// �ṩһ�����Թ��κ��˷��ʵİ�ȫ������
class KSecurityDesAcessByAnyone
{
public:
	KSecurityDesAcessByAnyone()
	{
		m_psa  = new SECURITY_ATTRIBUTES;
		m_psd = new SECURITY_DESCRIPTOR;
		::InitializeSecurityDescriptor( m_psd, SECURITY_DESCRIPTOR_REVISION);
		::SetSecurityDescriptorDacl( m_psd, 
			TRUE, 
			NULL,     // Allowing all access to the object 
			FALSE );
		m_psa->nLength = sizeof(SECURITY_ATTRIBUTES);
		m_psa->bInheritHandle = TRUE;
		m_psa->lpSecurityDescriptor = m_psd;
	}
	operator PSECURITY_ATTRIBUTES()
	{
		return m_psa;
	}

	~KSecurityDesAcessByAnyone()
	{
		if (m_psa)
		{
			delete m_psa->lpSecurityDescriptor;
			delete m_psa;
		}
	}
private:
	PSECURITY_ATTRIBUTES m_psa;
	PSECURITY_DESCRIPTOR m_psd;
};
