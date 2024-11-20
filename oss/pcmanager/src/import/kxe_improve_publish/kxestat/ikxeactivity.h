////////////////////////////////////////////////////////////////
//
//	Filename: 	ikxeactivity.h
//	Creator:	yangjun  <yangjun@kingsoft.com>
//	Date:		2009-5-19  9: 35
//	Comment:	
//
///////////////////////////////////////////////////////////////


#ifndef _ikxeactivity_h_
#define _ikxeactivity_h_

#include <Unknwn.h>

///////////////////////////////////////////////////////////////
//
// interface IKxeActivity ��Ծ��ͳ�ƽӿ�
//
///////////////////////////////////////////////////////////////

MIDL_INTERFACE("E19AA587-600D-499d-A091-F22691E9F4B2")
IKxeActivity : public IUnknown
{
	virtual int __stdcall Init() = 0;

	virtual int __stdcall Start() = 0;

	/**
	* @brief   ֪ͨ��Ծ��Ϣ
	* @param   [in] uProductId          ��Ʒ���
	* @param   [in] pwszProductVersion  ��Ʒ�汾��Ϣ(�ɴ���)
	* @remark
	*/
	virtual int __stdcall NoticeActivity( 
		/*[in]*/ unsigned int uProductId, 
		/*[in]*/ const wchar_t *pwszProductVersion
		) = 0;

	virtual int __stdcall Stop() = 0 ;

	virtual int __stdcall Uninit() = 0;

};

#define E_GETUUID_SUCCESSS			 0	///< ��ȡ�ɹ� 
#define E_GETUUID_ERROR_UNKNOWN		-1	///< ��ȡʧ�ܣ�ԭ��δ֪ 
#define E_GETUUID_ERROR_NONETWORK	-2	///< ��ȡʧ��,û������ 
#define E_GETUUID_ERROR_SMALLBUFFER	-3	///< ��ȡʧ��,����������̫С

/**
* @brief	��ȡUUID
* @param	[out]	 pszUUID ���ص��û�UUID
* @param	[in out] pnLen	 ����ʱΪ������pszUUIDָ��Ļ��������ַ���
���ʱΪʵ��copy���ֽ���

* @param	[int]	 bRefresh ����л����UUID,�Ƿ����¼���UUID
* @return	��E_GETUUID_XXX
* @remark	����ڲ���û�л���UUID��
*/
int __stdcall GetUUID(char* pszUUID,
					  int* pnLen,
					  bool bRefresh
					  );

#endif // _ikxeactivity_h_