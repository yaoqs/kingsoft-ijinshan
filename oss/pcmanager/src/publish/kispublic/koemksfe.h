#pragma once
#include "public.h"

NS_BEGIN(KIS)
NS_BEGIN(KOemKsfe)

/*
OEM��Ϣ����
Duba�кܶ��ض��İ汾����Щ�汾�����ڹ��ܶ��ٻ���һЩ��������ϴ���һЩ���죬
Ϊ���ܹ�ͳһ���а汾�����Ǳ��������������õ���ͬһ�ݣ�Ҳ�������й��ܼ��ϡ�
��װ����Ϊ�Ǵ��Եģ�����Ϊ�ض��汾���ǳ�����Ķ��ƣ������������������������
�������ļ��������⣬�ٷ����԰���Ҫ����ֻά��һ�ݡ�

һ���������
1��[oem file]��kis.dat��oem.dat�����ʽΪ���ܶ������ļ������Ծ���Duba��һЩ
��Ϊ�������ݲμ�oem_category��˵��
2��[oem dir]��λ�� <root/oem> �£�����������ΪһGUID������´��oem.dat������
�ļ�����kis�У������������Ը��ǳ���Ĭ����Ϊ

֮���Դ���[oem file]����Ϊ�˷�������ά�������Գ������һЩ��С�Ķ���ʱ��
������������ɡ�

��������ļ�Ŀ¼�ṹ��
<kis>
|	kis.dll
|	kis.dat
|	<oem>
			-----| <{7E2E5FCB-C0A9-43e3-994A-4954A529A686}>
			-----| oem.dat
			-----| kav32.xml
			-----| ...
			-----| Kav32_Logo.bmp

��������ʵ���߼�
	1��kis.dll��ʼ��ʱ����<oem>��Ŀ¼���ҵ���һ����Ч��[oem dir]
	2�����[oem dir]������oem.dat�����Ը�Ŀ¼��kis.dat��Ϊkis��[oem file]
	3��kslang��Loadʱ�������[oem dir]������ͬ�ļ������ļ�����ʹ��[oem dir]���ļ�
		�����Ե�ǰ����Ŀ¼Ϊ׼��������̣���һ���ļ�Ϊ��λ
	4��kslang�ڼ�����Ӧxml֮�����[oem file]�д���PatchCmds��������Ӧ����
		�����޸ģ�������ɾ�˵���޸��������ݡ���ͼƬ�ȵ�

*/
//ע�����
//1����Ϊ���ǵ�Ч�������������������Ϊ��ֵ������Ҳ������һ��������һ�����ܺ�
//	 ����Զ���ܸı�����ֵ��������Ҫ���ܻ������ܵ���ҡ�
//2������ÿ�����ܵ���밴���Ѿ��еĸ�ʽд������ܺ��壬����������
//	 ���һ������ID����ʹ���ˣ��뱣����λ
//3��Ŀǰֻ֧��32λ�������ͺ��ַ������ͣ�����Bool������0��1������FALSE��TRUE
//4��һ������������ֵ��������ں��
enum oem_category
{								// ����					����
	oemc_start = 0x0,			//int					����ʵ����
	oemc_VirusFreeShow,			//int					�Ƿ���ʿ��������������ģ��
	oemc_MoreOptimizeShow,		//int					�Ƿ���ʿ��������ʾ�������Ż���
	oemc_SearchEngineProtectShow,//int					�Ƿ���ʿ��������ʾ���������桱��	
	oemc_SoftwareMangerShow,	//int					�Ƿ���ʾ�������
	oemc_trayShow,				//int					�Ƿ���ʾ����
	oemc_netmonterShow,			//int					�Ƿ���ʾ�������
	oemc_OtherCheckName,		//LPCWSTR				�����µĻ�������������ַ���
	oemc_DownProtectedColor,	//int					���ر�����title��������ɫ
	oemc_SafeLinkURL,			//LPCWSTR				��ȫ���ӵ�URL·��
	oemc_IconBig,				//int					ָ���ļ��ص�ICON��ֵ
	oemc_IconSmall,				//int					ָ���ļ��ص�ICON��ֵ��small��
	oemc_SubKeyStr,				//LPCWSTR				ָ��SOFTWARE�µ������ƣ���SOFTWARE\\KSafeʱ��ΪKSafe
	oemc_IsOem,					//int					�Ƿ���oem�汾��1==�ٶ�OEM
	oemc_Appdata,				//LPCWSTR				APP��·��
	oemc_Reclye,				//LPCWSTR				RECYCLE��·��
	oemc_KwspluginName,			//LPCWSTR				������Ҫ��DLL���ļ���
	oemc_ServiceName,			//LPCWSTR				������
	oemc_KWSCShowName,			//LPCWSTR				��ɽ�������ع��ı���
	oemc_IsOpenNetM,			//int					�Ƿ���������
	oemc_SetCloudAddr,			//int					�ư�ȫ����˵����url
	oemc_BBSUrl,				//LPCWSTR				BBSָ����·��
	oemc_RunTrayName,			//LPCWSTR				ksafetray����������
	oemc_RunKSafeSvcName,		//LPCWSTR				ksafesvc����������
	oemc_FishBlockUrl,			//LPCWSTR				������վ������ʾ�ĵ�ַ
	oemc_UpdataUrlMsg,			//LPCWSTR				���ݵε�������Url
	oemc_UpdataUrlShow,			//LPCWSTR				������Url
	oemc_UpdataUrlQuick,		//LPCWSTR				������Url
	oemc_NetmonPriLevel,		//int					������صĵȼ�
	oemc_end					//int					����ʵ����
};

/*
* @brief								�趨OEM�ļ���ȫ·��
* @param lpFilePath					--- ָ����Ҫ���õ�OEM�ļ���ȫ·�������ʹ��Ĭ�ϣ�����oemĿ¼�в��ҵ��ĵ�һ���ļ���
*										���omeĿ¼�в������ļ������ԭ�����ļ���
* @remark							--- �ú��������Ҫ���ã������ڲ�ѯ����֮ǰ����
* @return 
*							   TRUE --- �ɹ�
*							   FALSE--- ʧ��
*/
STDAPIN_(int)  SetOEMFullPathA(IN LPCSTR lpFilePath = NULL);
STDAPIN_(int)  SetOEMFullPathW(IN LPCWSTR lpFilePath = NULL);


/*
* @brief								��ѯOem��ֵ��
* @param nKey						--- ��Ҫ��ѯ��key
* @param nValue						--- ��ѯ���Ľ��
* @param lpFilePath					--- ָ����Ҫ��ѯ���ļ���·���������ָ������ᵽoemĿ¼�в���
* @return 
*							   TRUE --- ���ҳɹ�
*							   FALSE--- ����ʧ��
*/
STDAPIN_(int)  QueryOEMInt(IN KOemKsfe::oem_category nKey, IN int& nValue); 

/*
* @brief								��ѯOem��ֵ��
* @param nKey						--- ��Ҫ��ѯ��key
* @param lpValue					--- ��ѯ���Ľ��,�����ֵΪNULL,��nSize������Ҫ�Ĵ�С
* @param nSize						--- ��ѯ���Ľ�����ַ������ȡ����lpValue����ʱ��ΪNULL���򷵻س��ȵ�ʵ�ʴ�С
* @param lpFilePath					--- ָ����Ҫ��ѯ���ļ���·���������ָ������ᵽoemĿ¼�в���
* @remark							--- ����ʹ�ã�
std::wstring strValue;
CallFunc<int, KIS::KOemKsfe::oem_category, LPWSTR, size_t&>(KIS::KOemKsfe::QueryOEMStrW, KIS::KOemKsfe::XXX, strValue);
* @return 
*							   TRUE --- ���ҳɹ�
*							   FALSE--- ����ʧ��
*/
STDAPIN_(int)  QueryOEMStrA(IN KOemKsfe::oem_category nKey, OUT LPSTR lpValue, IN OUT size_t& nSize);
STDAPIN_(int)  QueryOEMStrW(IN KOemKsfe::oem_category nKey, OUT LPWSTR lpValue, IN OUT size_t& nSize);


/*
* @brief								������OEM��������Ϣд��
* @return 
*							   TRUE --- ���ҳɹ�
*							   FALSE--- ����ʧ��
*/
STDAPIN_(int)  WriteAllOemData(void);


NS_END(KOemKsfe)
NS_END(KIS)




