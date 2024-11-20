#pragma once

using namespace std;

struct IInfocDataDecoder// : public IUnknown
{
	// ���ܣ������һ�� Infoc ���ܹ���Ķ�
	// ������
	// pcbAttrNameSize  ��pszAttrName �Ĵ�С��BYTE ��Ŀ��
	// pszAttrName	    �����ܳ���������
	// pcbAttrValueSize ��pbyAttrValue �Ĵ�С��BYTE ��Ŀ��
	// pbyAttrValue		�����ܳ�����Ӧ���ֵ�ֵ�ַ���
	virtual long GetNextData(
		IN OUT      DWORD       *pcbAttrNameSize, 
		OUT         BYTE        *pszAttrName, 
		IN OUT      DWORD       *pcbAttrValueSize, 
		OUT         BYTE        *pbyAttrValue) = 0;

	// �ͷ���Դ
	virtual void Release() = 0;
};

// ��ý��ܽӿ� IInfocDataDecoder
long GetDataDecoder(
					IN      DWORD       cbUrlLength,		// pbyUrlBuffer �Ĵ�С��BYTE��Ŀ��
					IN      BYTE*       pbyUrlBuffer,		// ��Ҫ���ܵ��ַ���
					OUT IInfocDataDecoder** ppiDecoder);	// ���ܽӿ�ָ��

class IInfocDataEncoder//: IUnknown
{
public:
	// ���ܣ���ü��ܽӿڵİ汾�ţ�Ŀǰδʵ�֣���������1��
    // ������
	// pdwVersion��IInfocDataEncoder �� pdwVersion �汾��
	virtual long __stdcall GetEncoderVersion(
        OUT     DWORD       *pdwVersion) = 0;

	// ���ܣ���� Infoc ������ֶζ�
	// ������
	// dwNameSize��		�����ַ����Ĵ�С���ַ�����
	// pszName��		���ֳ��ַ���
	// dwAttrSize��		��Ӧ���ֵĽ���Ĵ�С���ַ�����
	// pszAttrValue��	��Ӧ���ֵĽ���ַ���
	virtual long __stdcall AddStringAttr(
		IN			DWORD       dwNameSize,
		IN const	TCHAR       *pszName, 
		IN			DWORD       dwAttrSize,
		IN const	TCHAR       *pszAttrValue) = 0;

	// ���ܣ���ý���ַ���
	// ������
	// pcbUrlLength������ pbyUrlBuffer �Ĵ�С��BYTE ��Ŀ��
	// pbyUrlBuffer���������
    virtual long __stdcall FormatInfocDataToUrl(
        IN OUT  DWORD       *pcbUrlLength, 
        OUT     BYTE*       pbyUrlBuffer) = 0;

	// ���ܣ��ͷŴ˽ӿڵ���Դ��ÿ�μ������֮�󶼱�����ã�
    virtual void __stdcall Release() = 0;

	// ��ü��ܽӿ�ָ��
};

long GetDataEncoder(OUT IInfocDataEncoder **ppiEncoder);


