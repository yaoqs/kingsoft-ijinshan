#ifndef __BUILDCFG_BUILDCFG_H__
#define __BUILDCFG_BUILDCFG_H__

/*

1   �򿪱����̵�����Դ�ļ���ɾ��ԭ�еİ汾��Ϣ����version.rc��ӵ�����

2   �� trunk/builder/buildcfg Ŀ¼�¶�Ӧ��buildcfg.h�ļ�
	�ҵ��ù�������λ�ã�����Ӣ�ﶨ�����������꣬�磺	

#ifdef ETM_ETDBE // size : 20000
	#pragma comment(linker, "/base:0x4DA00000")   
	#pragma message("\t    ETM_ETDBE")
	#define VI_FILEDESCRIPTION	"Data Import"	//�ļ�����
	#define VI_INTERNALNAME		"dbe"			//�ڲ�����
	#define VI_ORIGINALFILENAME	"etdbe.dll"		//ԭʼDLL�ļ���
#endif

3.  �ڹ������õ� Resources ҳ��"Preprocessor definitions"����ӱ����̶�Ӧ�ĺ꣬�� ETM_ETDBE
	��ע����������(Debug/Release/...)��Ҫ����
	��"Additionalresource include directories"�м���Coding/includeĿ¼�����λ��
	�� "../../builder/buildcfg"
	
 */

// -------------------------------------------------------------------------

#ifdef _WINDOWS_
#error "include buildcfg.h before include all other files"
#endif

/////////////////////////////////
//exe
/**
here is a exe example:
#ifdef KISM_KAV32
	#pragma message("\t    KISM_KAV32")
	#define VI_FILEDESCRIPTION	"Kingsoft AntiVirus"
	#define VI_INTERNALNAME		"kav32"
	#define VI_ORIGINALFILENAME	"kav32.exe"
#endif
*/


#ifdef PLUG_EXTEND_DLL
#pragma message("\t    PLUG_EXTEND_DLL")
#define VI_FILEDESCRIPTION	"KSafe Plug Extend"
#define VI_INTERNALNAME		"kplugext"
#define VI_ORIGINALFILENAME	"kplugext.dll"
#endif

#endif /* __BUILDCFG_BUILDCFG_H__ */
