#ifndef _HELPER_2_H_
#define _HELPER_2_H_
//-----------------------------------------------------------------------------//
//
//  �õ�����HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services�µķ���
//
LONG
RegistryHelperGetServiceImagePath (
								   IN PWCHAR pwstrServiceName,
								   OUT PWCHAR pwstrImagePath,
								   IN OUT PLONG plSizeInBytes
								   );
//-----------------------------------------------------------------------------//
#endif