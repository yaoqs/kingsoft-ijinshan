//////////////////////////////////////////////////////////////////////
///		@file		kxeconfig.h
///		@author		luopeng
///		@date		2008-9-25 09:07:58
///	
///		@brief		kxeconfig��ض���
//////////////////////////////////////////////////////////////////////

#pragma once
#include "../kxebase/kxebase_config.h"
#include "../kxeerror/kxeerror.h"
#include <list>
#include <map>

/**
  @page kxeconfig_example KXEngine Config Example

  @code 
struct target
{
	std::wstring strName;
	int nType;
	int nId;	
	std::wstring strPath;
	std::wstring strComment;
};

KXE_CFG_DDX_BEGIN(target, strName)
	KXE_CFG_DDX_MEMBER_DEFAULT("Type", nType, 0)
	KXE_CFG_DDX_MEMBER_DEFAULT("Id", nId, 0)
	KXE_CFG_DDX_MEMBER_DEFAULT("Path", strPath, L"")
	KXE_CFG_DDX_MEMBER_DEFAULT("Comment", strComment, L"")
KXE_CFG_DDX_END()

struct target_tree
{
	std::wstring strName;
	std::map<std::wstring, target_tree> mapTargetTree;
};

KXE_CFG_DDX_BEGIN(target_tree, strName)
	KXE_CFG_DDX_MEMBER("target", mapTargetTree)
KXE_CFG_DDX_END()

struct aliases
{
	std::wstring strName;
	std::map<std::wstring, target> mapTarget;
};

KXE_CFG_DDX_BEGIN(aliases, strName)
	KXE_CFG_DDX_MEMBER("target", mapTarget)
KXE_CFG_DDX_END()


struct solution
{
	std::wstring strName;
	std::map<std::wstring, target_tree> mapTargetTree;
};

KXE_CFG_DDX_BEGIN(solution, strName)
	KXE_CFG_DDX_MEMBER("target", mapTargetTree)
KXE_CFG_DDX_END()

void TestFunction()
{
	kxe_base_init();
	kxe_base_start();

	target_tree parent;
	parent.strName = L"�ؼ�����";

	target_tree child1;
	child1.strName = L"�������";

	target_tree child2;
	child2.strName = L"SystemĿ¼";

	target_tree child3;
	child3.strName = L"WindowsĿ¼";

	parent.mapTargetTree[child1.strName] = child1;
	parent.mapTargetTree[child2.strName] = child2;
	parent.mapTargetTree[child3.strName] = child3;

	solution sln;
	sln.strName = L"solution";
	sln.mapTargetTree[parent.strName] = parent;

	kxe_config_write_config(KXE_CURRENT_USER_CONFIG, L"ScanSystem", sln);

	sln.mapTargetTree.clear();


	target t1 = {L"�ؼ�����", 0x20005, 0, L"", L""};
	target t2 = {L"SystemĿ¼", 0x10003, 0, L"c:\\windows\\system32", L"������Ŀ¼"}; 
	target t3 = {L"WindowsĿ¼", 0x10003, 0, L"c:\\windows", L"��������Ŀ¼"}; 
	target t4 = {L"�������", 0x10200, 0, L"", L"�������"}; 

	aliases ali;
	ali.strName = L"aliases";
	ali.mapTarget[t1.strName] = t1;
	ali.mapTarget[t2.strName] = t2;
	ali.mapTarget[t3.strName] = t3;
	ali.mapTarget[t4.strName] = t4;

	kxe_config_write_config(KXE_CURRENT_USER_CONFIG, L"ScanSystem", ali);
	ali.mapTarget.clear();

	kxe_config_read_config(KXE_CURRENT_USER_CONFIG, L"ScanSystem", sln);
	kxe_config_read_config(KXE_CURRENT_USER_CONFIG, L"ScanSystem", ali);

	kxe_base_stop();
	kxe_base_fini();
}
	@endcode
*/


/**
 * @defgroup kxeconfig_group KXEngine Architecture Config Interface
 * @{
 */

/**
* @brief ����·��,�������һ��ָ�������ü�
* @param[in] key ����Ҫ�򿪵ľ��Լ�ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_base_create_config_key��kxe_base_open_config_key���������ļ�
* @param[in] pwszPath ���·��,���򿪵�·��Ϊkey��path+pwszPath
* @param[out] pNewKey �ɹ��򿪺󴫳������ü�
* @remark ���ָ���ļ�����,�����,���򴴽���
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
int kxe_config_create_key(
	kxe_config_key_t key,
	const wchar_t* pwszPath, 
	kxe_config_key_t* pNewKey
	);

/**
* @brief ����·��,��һ��ָ�������ü�
* @param[in] key ����Ҫ�򿪵ľ��Լ�ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_base_create_config_key��kxe_base_open_config_key���������ļ�
* @param[in] pwszPath ���·��,���򿪵�·��Ϊkey��path+pwszPath
* @param[out] pNewKey �ɹ��򿪺󴫳������ü�
* @remark ���ָ���ļ�����,�����,����ʧ��
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
int kxe_config_open_key(
	kxe_config_key_t key,
	const wchar_t* pwszPath, 
	kxe_config_key_t* pNewKey
	);

/**
* @brief �ر�ָ�������ü�
* @param[in] key ͨ��kxe_config_create_key��kxe_config_open_key��õļ�ֵ
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
int kxe_config_close_key(
    kxe_config_key_t key
	);

/**
* @brief ɾ��ָ���ļ�ֵ
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,���·��Ϊkey��path+pwszPath
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
int kxe_config_delete_key(
	kxe_config_key_t key,
	const wchar_t* pwszPath
	);


/**
* @brief ͨ��ָ���ļ��������·��,��ȡ��Ӧ�����ݽṹ
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in, out] value ������Ҫ��ȡ���ݵ����ݽṹ����
* @remark 
*      �����ģ������T,��Ҫ�Ѿ������KXE_CFG_DDX_BEGIN����غ�,���򽫻�ȡ������
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
template
<
	typename T
>
int kxe_config_read_config(
	kxe_config_key_t key,
	const wchar_t* pwszPath, 
	T& value
	);

/**
* @brief ͨ��ָ���ļ��������·��,д���Ӧ�����ݽṹ
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in] value ������Ҫд������ݽṹ����
* @remark 
*      �����ģ������T,��Ҫ�Ѿ������KXE_CFG_DDX_BEGIN����غ�,����д�������
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
template
<
	typename T
>
int kxe_config_write_config(
	kxe_config_key_t key,
	const wchar_t* pwszPath,
	const T& value
	);

#if _MSC_VER > 1200
/**
* @brief ͨ��ָ���ļ��������·��,��ȡһ�����ݽṹ
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in, out] listValue ������Ҫ��ȡ���ݵ����ݽṹ�б�����
* @remark 
*    ��ģ������T����ΪKXE_CFG_DDX_BEGIN�����������,Ҳ�����Ƕ����ostream��istream��
*    �������������
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
template
<
	typename T
>
int kxe_config_read_config(
	kxe_config_key_t key,
	const wchar_t* pwszPath, 
	std::list<T>& listValue
	);

/**
* @brief ͨ��ָ���ļ��������·��,д��һ�����ݽṹ
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in] listValue ������Ҫд�����ݵ����ݽṹ�б�����
* @remark 
*    ��ģ������T����ΪKXE_CFG_DDX_BEGIN�����������,Ҳ�����Ƕ����ostream��istream��
*    �������������
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
template
<
	typename T
>
int kxe_config_write_config(
	kxe_config_key_t key,
	const wchar_t* pwszPath,
	const std::list<T>& listValue
	);
#endif

/**
* @brief ͨ��ָ���ļ��������·��,��ȡһ�����ݽṹ,����map���
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in, out] mapKeyToType ������Ҫ��ȡ���ݵ����ݽṹ�б�����
* @remark 
*    ��ģ������T����ΪKXE_CFG_DDX_BEGIN�����������,��map�е�keyΪ
*    KXE_CFG_DDX_BEGIN���������
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
template
<
	typename Key,
	typename T
>
int kxe_config_read_config(
	kxe_config_key_t key,
	const wchar_t* pwszPath,
	std::map<Key, T>& mapKeyToType
	);

/**
* @brief ͨ��ָ���ļ��������·��,д��һ�����ݽṹ,����map���
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in] mapKeyToValue ������Ҫд������ݽṹ�б�����
* @remark 
*    ��ģ������T����ΪKXE_CFG_DDX_BEGIN�����������,��map�е�keyΪ
*    KXE_CFG_DDX_BEGIN���������
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
template
<
	typename Key,
	typename T
>
int kxe_config_write_config(
	kxe_config_key_t key,
	const wchar_t* pwszPath,
	const std::map<Key, T>& mapKeyToValue
	);

/**
* @brief ͨ��ָ���ļ��������·��,��ȡ�ü��������Ӽ�
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in, out] listKey ����洢��ȡ���������Ӽ�
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
int kxe_config_read_key(
	kxe_config_key_t key,
	const wchar_t* pwszPath, 
	std::list<std::wstring>& listKey
	);

/**
* @brief ͨ��ָ���ļ��������·��,��ȡָ��valuename�����ݽṹ
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in] pwszValueName ָ��Ҫ��ȡ��valuename
* @param[in, out] value �洢��ȡ������������
* @remark 
*    ��ģ������T��Ҫ��������������
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
template
<
	typename T
>
int kxe_config_read_value(
	kxe_config_key_t key,
	const wchar_t* pwszPath,
	const wchar_t* pwszValueName,
	T& value
	);

/**
* @brief ͨ��ָ���ļ��������·��,��ָ��valuename��д������
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in] pwszValueName ָ��Ҫ��ȡ��valuename
* @param[in] value �洢������
* @remark 
*    ��ģ������T��Ҫ��������������
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
template
<
	typename T
>
int kxe_config_write_value(
	kxe_config_key_t key,
	const wchar_t* pwszPath,
	const wchar_t* pwszValueName,
	const T& value
	);

/**
* @brief ͨ��ָ���ļ��������·��pwszPath��pwsaValueName��ȡһ�����ݽṹ
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in] pwszValueName ��pwszPath������·��
* @param[in, out] listValue ������Ҫ��ȡ���ݵ����ݽṹ
* @see 	kxe_config_read_config(kxe_config_key_t key, const wchar_t* pwszPath, std::list<T>& listValue);
* @remark 
*     �˺������յ���kxe_config_read_config
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
template
<
	typename T
>
int kxe_config_read_value(
	kxe_config_key_t key,
	const wchar_t* pwszPath,
	const wchar_t* pwszValueName,
	std::list<T>& listValue
	);

/**
* @brief ͨ��ָ���ļ��������·��pwszPath��pwsaValueNameд��һ�����ݽṹ
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in] pwszValueName ��pwszPath������·��
* @param[in, out] listValue ������Ҫ�洢������
* @see kxe_config_write_config(kxe_config_key_t key,const wchar_t* pwszPath, const std::list<T>& listValue);
* @remark 
*     �˺������յ���kxe_config_write_config
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
template
<
	typename T
>
int kxe_config_write_value(
	kxe_config_key_t key,
	const wchar_t* pwszPath,
	const wchar_t* pwszValueName,
	const std::list<T>& listValue
	);

/**
* @brief ͨ��ָ���ļ��������·��pwszPath��pwszValueName,��ȡһ�����ݽṹ,����map���
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in] pwszValueName ��pwszPath������·��
* @param[in, out] keyToValue ������Ҫ��ȡ���ݵ����ݽṹ�б�����
* @see kxe_config_read_config(kxe_config_key_t key, const wchar_t* pwszPath, std::map<Key, T>& mapKeyToType);
* @remark 
*     ����ת������kxe_config_read_config
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
template
<
	typename Key,
	typename T
>
int kxe_config_read_value(
	kxe_config_key_t key,
	const wchar_t* pwszPath,
	const wchar_t* pwszValueName,
	std::map<Key, T>& keyToValue
	);

/**
* @brief ͨ��ָ���ļ��������·��pwszPath��pwszValueName,��ȡһ�����ݽṹ,����map���
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_config_create_key��kxe_config_open_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in] pwszValueName ��pwszPath������·��
* @param[in, out] keyToValue ������Ҫ�洢������
* @see kxe_config_write_config(kxe_config_key_t key,const wchar_t* pwszPath,const std::map<Key, T>& mapKeyToValue);
* @remark 
*     ����ת������kxe_config_write_config
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
template
<
	typename Key,
	typename T
>
int kxe_config_write_value(
	kxe_config_key_t key,
	const wchar_t* pwszPath,
	const wchar_t* pwszValueName,
	const std::map<Key, T>& keyToValue
	);

//template
//<
//	typename Class,
//	typename Left,
//	typename Right
//>
//bool KxEBaseIsSame(Left Class::* pLeft, Right Class::* pRight)
//{
//	return false;  // ���Ͳ�һ��,��Ȼfalse
//}
//
//template
//<
//	typename Class,
//	typename Left
//>
//bool KxEBaseIsSame(Left Class::* pLeft, Left Class::* pRight)
//{
//	return pLeft == pRight;
//}

template
<
	typename T,
	typename Key
>
inline int KxEConfigDataKey(kxe_config_key_t key, 
							bool bWrite, 
							const T& value, 
							Key T::* pMemberKey,
							kxe_config_key_t* pNewKey)
{
	std::wostringstream os;
	os << value.*pMemberKey;

	return kxe_config_create_key(
		key,
		os.str().c_str(),
		pNewKey
		);
}

template
<
	typename T
>
inline void KxEConfigSetKeyValue(T& object, const std::wstring& value)
{
	std::wistringstream is(value);
	is >> object;
}

template
<
	typename T
>
inline int KxEConfigDataExchange(kxe_config_key_t key, bool bWrite, T& value)
{
	return 0;
}

template
<
	typename T
>
struct KxEUserDefineConfigStruct
{
	enum {value = false};
};

/**
 * @brief ��ʼ���彫���ݽṹ������֮��������л��뷴���л����м�����
 * @param[in] _Class ��Ҫ�����м����ݵ����ݽṹ
 * @param[in] _Key _Class��������ΪKey�����ݳ�Ա������
 */
#define KXE_CFG_DDX_BEGIN(_Class, _Key) \
	template\
	<\
	>\
	struct KxEUserDefineConfigStruct<_Class>\
	{\
		enum {value = true};\
	};\
	template<>\
	inline void KxEConfigSetKeyValue(_Class& object, const std::wstring& value)\
	{\
		std::wistringstream is(value);\
		is >> object.*(&_Class::_Key);\
	}\
	template<>\
	inline int KxEConfigDataExchange(kxe_config_key_t key, bool bWrite, _Class& value)\
	{\
		kxe_config_key_t newKey = NULL;\
		int nRet = KxEConfigDataKey(key, bWrite, value, &_Class::_Key, &newKey);\
		if (nRet != 0) \
		{\
			return nRet;\
		}\
		key = newKey;\

/**
* @brief ���彫���ݽṹ������֮��������л��뷴���л����м������е����ݳ�Ա,
*        ֻ������ͨ��KXE_CFG_DDX_BEGIN���������
* @param[in] _Name �洢ʱ���õ�ValueName
* @param[in] _Member ���ݽṹ�ĳ�Ա������
*/
#define KXE_CFG_DDX_MEMBER(_Name, _Member)\
	if (bWrite) kxe_config_write_config(key, L##_Name, value._Member);\
	else kxe_config_read_config(key, L##_Name, value._Member);

/**
* @brief ���彫���ݽṹ������֮��������л��뷴���л����м������е����ݳ�Ա,
*        ���û���ҵ�ֵ,����_Default���
* @param[in] _Name �洢ʱ���õ�ValueName
* @param[in] _Member ���ݽṹ�ĳ�Ա������
* @param[in] _Default �ڶ�ȡ����ʱ,���û���ҵ���Ӧ��ValueName,����_Default���
*/
#define KXE_CFG_DDX_MEMBER_DEFAULT(_Name, _Member, _Default)\
	if (bWrite)\
	{\
		kxe_config_write_value(key, NULL, L##_Name, value._Member);\
	}\
	else \
	{\
		nRet = kxe_config_read_value(key, NULL, L##_Name, value._Member);\
		if (nRet == ERROR_FILE_NOT_FOUND || nRet == E_KXECFG_VALUE_NOT_CORRECT) \
		{\
			value._Member = _Default;\
		}\
	}

/**
* @brief �������彫���ݽṹ������֮��������л��뷴���л����м�����
*/
#define KXE_CFG_DDX_END() \
	if (newKey) \
	{\
		kxe_config_close_key(newKey); \
	}\
	return 0;\
	}

/**
* @brief ֱ�ӽ�һ��struct����Ϊһ����
*/
#define KXE_CFG_DDX_DEFINE(_Class) \
	template\
	<\
	>\
	struct KxEUserDefineConfigStruct<_Class>\
	{\
		enum {value = true};\
	};\
	template<>\
	inline int KxEConfigDataExchange(kxe_config_key_t key, bool bWrite, _Class& value)\
	{\
		std::wostringstream os;\
		os << value;\
		kxe_config_key_t newKey = NULL;\
		int nRet = kxe_config_create_key(key, os.str().c_str(), &newKey);\
		if (nRet != 0)\
		{\
			return nRet;\
		}\
		else\
		{\
			kxe_config_close_key(newKey);\
			return 0;\
		}\
	}
		
// ����ʵ��
#include "kxeconfig.inl"

/**
 * @}
 */
