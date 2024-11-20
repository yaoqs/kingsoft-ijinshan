#ifndef REGCLEANER_WOW64HELPER_H_
#define REGCLEANER_WOW64HELPER_H_

//////////////////////////////////////////////////////////////////////////

typedef enum tagWow64Type {
    WOW64_DEFAULT = 0,      // �����ļ���ע���ʹ��Ĭ��ģʽ
    FORCE_WOW64_64 = 1,     // ǿ�Ʒ���64λע����Ӽ�, �ر��ļ��ض���
    FORCE_WOW64_32 = 2,     // ǿ�Ʒ���32λע����Ӽ�
    WOW64_MISC = 3          // ����ģʽ, ����Ĭ�Ϸ�ʽ����ע���, 
                            //   ���ر��ļ��ض���͹رյ�����£�ֻҪ��һ���ļ����ڣ������ļ�����
} Wow64Type;

//////////////////////////////////////////////////////////////////////////

inline DWORD GetRegAccess(Wow64Type wow64type) 
{
    DWORD retval = 0;

    switch (wow64type)
    {
    case FORCE_WOW64_64:
        retval = KEY_WOW64_64KEY;
        break;

    case FORCE_WOW64_32:
        retval = KEY_WOW64_32KEY;
        break;

    case WOW64_DEFAULT:
    case WOW64_MISC:
    default:
        retval = 0;
    }

    return retval;
}

//////////////////////////////////////////////////////////////////////////

#endif // REGCLEANER_WOW64HELPER_H_
