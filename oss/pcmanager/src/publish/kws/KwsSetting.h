///////////////////////////////////////////////////////////////
//
//	Filename: 	KwsSetting.h
//	Creator:	lichenglin  <lichenglin@kingsoft.com>
//	Date:		2009-3-18  19:06
//	Comment:	
//
///////////////////////////////////////////////////////////////


#ifndef _KwsSetting_h_
#define _KwsSetting_h_
#include <vector>
#include <string>
#include <atlstr.h>

using namespace std;

typedef int SHINELEVEL;
#define SHINELEVEL_NORMAL 2
#define SHINELEVEL_HIGH   5
#define SHINELEVEL_LOW    1


typedef struct AdGuidVersion
{
    AdGuidVersion()
    {
        strguid = "";
        dwversion = 0;
    }
    std::string strguid;
    DWORD dwversion;
}*pAdGuidVersion;


typedef struct AdGuidVerID
{
    AdGuidVerID()
    {
        nid = 1;
    }
    int nid;
    AdGuidVersion adguidver;
}*pAdGuidVerID;

class KwsSetting 
{
public:
	KwsSetting();
	~KwsSetting();

public:
	// �����رձ���
	BOOL IsKwsEnable();
	BOOL SetKwsEnable( BOOL bEnable );
	BOOL IsKwsEnableEx( BOOL& bEnable ); // ����ֵ�ж��Ƿ�����쳣


	// ����ͼ��
	BOOL IsTrayIconEnable();
	BOOL EnableTrayIcon( BOOL bEnable );


	// ��������
	BOOL OnlineUpdate();


	// ����Ч��
	int IsShineEnable();
	BOOL SetShineEnable( int bEnable );

	COLORREF GetSafeColor();
	BOOL SetSafeColor( COLORREF cr );

	COLORREF GetWarnColor();
	BOOL SetWarnColor( COLORREF cr );

	COLORREF GetDangerColor();
	BOOL SetDangerColor( COLORREF cr );


	
	SHINELEVEL GetShineLevel();
	BOOL SetShineLevel( SHINELEVEL nLevel ); 


	// ������
	//BOOL GetBlackUrlList( std::vector<std::string>& vecList ); 
	//BOOL SetBlackUrlList( const std::vector<std::string>& vecList );
	//BOOL IsUrlInBlackList( const char* pszUrl );

	// ����Ƿ�����Ҫ����(��������������������״̬)
	BOOL GetUpdStatus(DWORD& dwValue);
	BOOL SetUpdStatus(DWORD dwValue);

	//  �Զ��屣������
	void GetShieldProcess(std::vector<std::wstring> &vecProcesses);
	BOOL SetShieldProcess(const std::vector<std::wstring> vecProcesses);

	// ��ȡ���һ��������ʱ��
	BOOL GetLastUpdateTime(LPWSTR strTime, size_t nSize);
	BOOL SetLastUpdateTime(LPCWSTR strTime);

    BOOL KwsSetTime(INT64 nTime, LPCWSTR lpwname);
    BOOL KwsGetTime(INT64 *nTime, LPCWSTR lpwname);

	// �û����һ�η�����ʱ��
	BOOL GetLastFeedbackTime(INT64* nTime);
	BOOL SetLastFeedbackTime(INT64 nTime = 0);

	// ��ȡUuid
	BOOL GetUuid(std::wstring &strUuid);

	// ��ȡͨ����
	BOOL GetChannelCode(DWORD& dwMajCode, DWORD& dwSlvCode);

	// �Ƿ��һ������
	BOOL IsFirstRun();
	BOOL SetFirstRun();

	DWORD GetDangerCount();
	BOOL SetDangerCount(DWORD uCount);
	DWORD GetProtectedDay();
	BOOL SetSetupTime(INT64 time = 0);

	// ��������ʱ�����������Ƿ���ʾ���������Ѿ����ϣ�
	BOOL IsShowTrayBalloon();
	BOOL SetShowTrayBalloon(BOOL bShow);

	// ��������
	BOOL IsShowTrayShine();
	BOOL SetShowTrayShine(BOOL bShow);


	// �ܱ����
	BOOL IsScanedKPP();
	BOOL SetScanedKPP(BOOL bScaned);

	// ��������
	BOOL GetSearchEngine(DWORD &dwVal);
	BOOL SetSearchEngine(DWORD dwVal);

	// �Ƿ���Ҫ��������
	BOOL IsNeedBlockDialog();
	BOOL SetNeedBlockDialog(BOOL bNeed);

	// ���һ���ϱ���Ծ��ʱ��
	BOOL GetLastReportTime(INT64* nTime);
	BOOL SetLastReportTime(INT64 nTime = 0);

	// �Ƿ���Ҫ�Ƽ��ܱ�
	BOOL SetNeedRcmKpp(BOOL bVal);

	// �Ƿ����ΰ�
	BOOL IsForMaxthon();

	//�Ƿ��Ƕ��԰�
	BOOL IsForDuba();

	// ��ȡ���ܰ汾
	BOOL GetKwsVt(DWORD& dwVt);

	//������ҳ
    BOOL GetStartPage(std::wstring& strSP);
	BOOL SetStartPage(LPCWSTR strSP);

	// �����ر�������ҳ
	BOOL IsLockSPEnable();
	BOOL SetLockSPEnable( BOOL bEnable );
	BOOL SetLockSPFirstShow( BOOL bEnable );
	BOOL IsLockSPFirstTipShowed();

	// ���ر���	
	BOOL IsDPEnable();
	BOOL SetDPEnable( BOOL bEnable );
	BOOL GetDPSoft( DWORD &dwVal );
	BOOL SetDPSoft( DWORD dwVal );

	// ��ҳ����
	BOOL IsHtmFilterEnable();
	BOOL SetHtmFilterEnable( BOOL bEnable );

	// ר��
	BOOL GetSvt( DWORD &dwSvt );
	BOOL SetSvt( DWORD dwSvt );
	BOOL GetSvtName(std::wstring &strName);
	BOOL GetSvtUrl(std::wstring &strSvtUrl);
	BOOL GetUrlChn(std::wstring &strUrlChn);

	// ����
	BOOL IsMouseProEnable();
	BOOL SetMouseProEnable( BOOL bEnable );

	//�Ƿ��ǰٶȵ�һ��ִ��
	DWORD GetBaiduFirstShow();
	BOOL SetBaiduFirstShow( DWORD dwvalue );
	BOOL IsCloseBaiduShowed();
	BOOL SetCloseBaiduShowed();

	// �Ƿ���Ҫ�Ƽ�������
	BOOL SetNeedRcmKsm(BOOL bVal);

	// �������汣��
	BOOL IsBrowserProEnable();
	BOOL SetBrowserProEnable( BOOL bEnable );
	BOOL GetBrowserPath(std::wstring& strBsPath);
	BOOL SetBrowserPath(LPCWSTR strBsPath);
    BOOL SetLockDefBsWarpper(BOOL bEnable, const wchar_t* pwszBsPath);

	// ����������ܿ��أ�����ر��������������Ч��
	BOOL IsBrowserLockEnable();
	BOOL SetBrowserLockEnable( BOOL bEnable );

	// ���ɨ�������ҳ��ʱ��
	BOOL GetLastEnumEUTime(INT64* nTime);
	BOOL SetLastEnumEUTime(INT64 nTime = 0);

	// �����رյ��㱣��
	BOOL IsFishingEnable();
	BOOL SetFishingEnable( BOOL bEnable );

/* �����ر���ҳľ����� */
	BOOL IsAntiTrojanEnable();
	BOOL SetAntiTrojanEnable(BOOL bEnalbe);
    // �жϵ�ǰ�û���û�ж��Ĺ��
	BOOL IsAntiAdEnable();
	VOID SetAntiAdEnable(BOOL bEnable);
    BOOL IsAnyRuleSubscribed();
	// ����guid��version
    BOOL GetAdGuid_Version(std::vector<AdGuidVersion>& vecadguidversion);
    BOOL SetAdGuid_Version(LPCTSTR strguidversion);
    BOOL GetAdGuid_VersionAsString(std::string& strguid_version);
    //��ҳ���ĵĴ���
    BOOL GetSpModifyCount(DWORD& dwCount);
    BOOL IncSpModifyCount();
    BOOL ResetSpModifyCount();

	// 360�����������ʾ
	BOOL NeedShow360SEPopo();
	BOOL SetShow360SEPopo(BOOL bNeed);

	// �����رյ�ַ��ͼ��
	BOOL IsABIconEnable();
	BOOL SetABIconEnable( BOOL bEnable );

	// �����ر�upreport�ϱ�
	BOOL IsUpReportEnable();
	BOOL SetUpReportEnable( BOOL bEnable );

    // IE��ʾ�����˿���
    BOOL IsTipSpannerEnable();
    BOOL SetupTipSpannerEnable( BOOL bEnable );

    //ǿת����ҳ�Ĵ�����1
    BOOL IncReNavigateCount(BOOL bReset = 0);

    //��ȡǿת����ҳ�Ĵ���
    BOOL GetReNavigateCount(DWORD& dwReNvCount);


    //���MAXTHON������������ٵ��ݱ�־
    BOOL IsMaxBsptNotifyDisable();
    BOOL SetMaxBstrNotifyDisable();

    //��ҳ�Ƽ������Ƿ��ٵ�
    BOOL IsLockSpNotifyDisable();
    BOOL SetLockSpNotifyDisable();
    // �жϽ����Ѿ����û����ص����URL��
    BOOL IsAnyURLBeenBlockedToday();

    // ��ǽ����Ѿ����û����ص����URL��
    BOOL MarkURLBeenBlockedToday();

    //���û�ȡ��ȡ�ϴ�����ҳɨ�赯��ʱ��
    BOOL SetLastScanSpNotifyTime(INT64 time = 0);
    BOOL GetLastScanSpNotifyTime(INT64* time);

	// �ж���WIN7����ͼ����ʾ�����������Ƿ��Ѿ����й���
	BOOL IsTrayIconShowOutCfg();
	BOOL SetTrayIconShowOut();

	//�������Ƿ���Ҫ��pc120ͬ��
	BOOL IsWebRuleNeedCheck();
	//�����������Ƿ���pc123ͬ��
	void SetWebRuleCheck( BOOL bCheck );

    // �жϹ����˵���־�����Ƿ���. Ŀǰ�����˵���־���ܽ����ṩ��
    // �ڲ�ʹ��. ���Խ�����û���ṩ�ӿ������������.
    BOOL IsAntiAdvLogEnabled();
	BOOL SetAntiAdvLogEnable(BOOL bEnable);

    // ���һ��IE�Ƽ������˵�ʱ��
    BOOL GetLastTipsSbanRecommendTime(INT64& iDate);
    BOOL SetLastTipsSbanRecommendTime(INT64 iDate);
    BOOL SetLastTipsSbanRecommendTimeAsNow();

    BOOL GetLastRecommendDate(UINT &nDate);
    BOOL SetLastRecommendDate();

	// �Ƿ���Ҫ�޸Ŀ�ݷ�ʽ
	BOOL IsNeedChangeSc();
	BOOL SetNotNeedChangeSc();

	// �û��Զ�����ӵ������
	BOOL GetSelfDefBrowserPath(std::wstring& strBsPath);
	BOOL SetSelfDefBrowserPath(LPCWSTR strBsPath);

    //���������������ҳ����
    BOOL IsNeedLockMaxSp();
    BOOL SetLockMaxSp(BOOL bNeed);
    BOOL SetNeverPopLockMaxSp(BOOL bNever);
    BOOL IsNeedPopLockMaxSp();	
	BOOL SetNeedShowBlockSpPop(BOOL bVal);
	BOOL IsNeedShowBlockSpPop();

	//�Ƿ���Ҫ��ʾmini��
	BOOL IsMiniSiteShow();
	BOOL SetMiniSiteShow( BOOL bShow );

	// ���ΰ�mini��
	BOOL IsMxMiniSiteShow();
	BOOL SetMxMiniSiteShow(BOOL bShow);

	// ���ΰ�ڶ���miniҳ
	BOOL IsMxMiniSite2Show();
	BOOL SetMxMiniSite2Show(BOOL bShow);

	// �޸İ��ΰ����õĿ���
	BOOL IsNeedFixMxCfg();
	BOOL SetNeedFixMxCfg(BOOL bNeed);

	// һ���޸�
	BOOL SetOnekeyAlready();

	// �������ذ�ȫ
	BOOL IsAutoScanEnable();
	BOOL SetAutoScanEnable(BOOL b);

	BOOL IsAutoCleanVirus();
	BOOL SetAutoCleanVirus(BOOL b);

	BOOL IsShowSafePop();
	BOOL SetShowSafePop(BOOL b);

	BOOL IsShowGrayPop();
	BOOL SetShowGrayPop(BOOL b);

	BOOL IsFileHelperEnable();
	BOOL SetFileHelper(BOOL bValue);

	//3.6mini�����Ƽ�
	BOOL IsMini36Show();
	BOOL SetMini36Show( BOOL bShow );

	//���ذ�ȫdfimport.exe�Ƿ�����
	INT	 GetDownFileImportFlag();
	BOOL SetDownFileImportFlag(INT nFlag);

	//���ذ�ȫ�Ƿ���ʾtip����
	BOOL DSNeedShowTip();
	BOOL DSSetShowTip(BOOL bShow);

    //�ռ�Application Data\\Kingsoft\\KIS\\KCLT\\public_kws.inf��Ϣ
    BOOL GetCommonInfo(std::string& strvalue);

	/* �Ƿ���Ҫ��ʾ����������ʾ */
	BOOL IsNeedAutorunHit();
	void SetNeedAutorunHit(BOOL fShow);

private:
	LONG KwsSettingGetDWORDValue( LPCTSTR pszKey, DWORD& dwValue, DWORD dwDefault );
	LONG KwsSettingGetStringValue( LPCTSTR pszKey, ATL::CAtlString& strValue, LPCTSTR pszDefault );

	LONG KwsSettingSetDWORDValue( LPCTSTR pszKey, DWORD dwValue );
	LONG KwsSettingSetStringValue( LPCTSTR pszKey, LPCTSTR pszValue );

private:
	LONG KwsSettingGetRegDWORDValue( LPCTSTR pszKey, LPCTSTR pszSubKey, DWORD& dwValue, DWORD dwDefault );
	LONG KwsSettingGetRegStringValue( LPCTSTR pszKey, LPCTSTR pszSubKey, ATL::CAtlString& strValue, LPCTSTR pszDefault );

	LONG KwsSettingSetRegDWORDValue( LPCTSTR pszKey, LPCTSTR pszSubKey, DWORD dwValue );
	LONG KwsSettingSetRegStringValue( LPCTSTR pszKey, LPCTSTR pszSubKey, LPCTSTR pszValue );

	LONG KwsSettingDeleteRegValue( LPCTSTR pszKey, LPCTSTR pszSubKey );

	
};

#endif // _KwsSetting_h_
