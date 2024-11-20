#pragma once
/*
	���̿������
	�����������̿�xml�ļ�

	˼·: ��XML�ļ���ȡ����tinyxml��������ת�����ڴ����ݡ�
	��˾		��     CompanyMap
	·��		��     PathMap
	����ǩ��   ��     SignMap
	������Ϣ   ��     ProcessInfoMap
						�ڲ���ProcessItemMap

	Ϊ�˼��ٲ�ѯ����������ProcessItem��MultiMap���Ż���ѯ��
*/

using namespace std;

class KProcessInfo;
class KProcessItem;
class TiXmlDocument;
class TiXmlElement;
struct ProcessLibOverwriteRule;
enum KProcessType;

class ProcessLib
{
public:
	ProcessLib(void);
	~ProcessLib(void);

	// ��ȡ���������ַ���
	static wstring GetProcessTypeString(KProcessType enumProcessType);

	// ��ȡ����ǩ����ǩ����
	static wstring GetDigitalSignaturerName(LPCTSTR szFilePath);

	// ��·���л�ȡ�ļ���
	static wstring GetFileName(LPCTSTR szFilePath);
	
	// ��ȡ�ļ��а�����������Ϣ
	static wstring GetFileDesc(LPCTSTR szFilePath);

	// ��ȡ2��Ŀ¼
	static wstring GetTwoLevelPath(LPCTSTR szFilePath, int& nPathLevel);
	
	// ��ȡ1��Ŀ¼
	static wstring GetOneLevelPath(LPCTSTR szFilePath);
	
	// ��ȡ��˾����
	static wstring GetCompanyName(LPCTSTR szFilePath);

	// ��xml�ļ�����
	BOOL Load(LPCTSTR filePath);

	// ���ڴ�������
	BOOL Load(char* buffer, long nLen);

	// ����
	BOOL Save(LPCTSTR filePath);

	// ��ʱ�õĴ���
	void TempFun();

	// �ϲ�
	BOOL Merge(ProcessLib* secondLib, ProcessLibOverwriteRule overWriteRule);
	BOOL MergeCompanyNameNode( map<int, wstring>& secondMap);
	BOOL MergeSignNameMap(map<int, wstring>& secondMap);
	BOOL MergePathMap(map<int,wstring>& secondMap);
	BOOL MergeProcessesMap(ProcessLib* secondLib,map<wstring, KProcessInfo>& secondMap, ProcessLibOverwriteRule& overWriteRule);

	BOOL FindInfo(LPCTSTR szFileName, KProcessItem& pInfo);

	// ͨ��id��·����
	wstring GetPath(int id);
	// ͨ��·����id
	int FindPathId(wstring path);

	// ͨ��id�鹫˾��
	wstring GetCompanyName(int id);
	// ������˾����id
	int FindCompanyId(wstring company);

	// ͨ��id��ǩ����
	wstring GetSignName(int id);
	// ͨ��ǩ���˲�id
	int FindSignNameId(wstring signName);

	// ͨ��id��ȡ��Ϣ
	KProcessItem GetProcessItem(int id);

	BOOL GetProcessInfo(wstring fileName, KProcessInfo& processInfo);

	// ���
	int  AddPathNode(const wstring&  strPath);
	int  AddCompanyNameNode(const wstring&  strCompanyName);
	int  AddSignNameNode(const wstring& strSignName);
	BOOL AddPathNode(int id, const wstring&  strPath);
	BOOL AddCompanyNameNode(int id, const wstring&  strCompanyName);
	BOOL AddSignNameNode(int id, const wstring& strSignName);
	BOOL AddProcessInfo(wstring fileName, KProcessInfo& processInfo);
	BOOL AddProcessItem(wstring processName, KProcessItem& processItem);
	BOOL AddProcessItem(wstring processName, KProcessItem& processItem, ProcessLibOverwriteRule& overwriteRule);
	
	// ɾ��
	BOOL RemovePathNode(int id);
	BOOL RemoveCompanyNameNode(int id);
	BOOL RemoveSignNameNode(int id);
	BOOL RemoveProcessItem(int processItemId);

	// �޸�
	BOOL ModifyPathNode(int id,  const wstring& strNewPath);
	BOOL ModifyCompanyNameNode(int id, const wstring& strNewCompanyName);
	BOOL ModifySignNameNode(int id, const wstring& newName);
	BOOL ModifyProcessItem(int id, KProcessItem& newProcessItem);
	
	// ���
	BOOL ClearAll();
	BOOL ClearCompnayMap();
	BOOL ClearSignNameMap();
	BOOL ClearPathMap();
	BOOL ClearProcessMap();

	// ��ȡmap
    BOOL GetCompanyNameMap(map<int, wstring>& mapCompanyName);
	BOOL GetPathMap(map<int, wstring>& mapPath);
	BOOL GetProcessMap(map<wstring, KProcessInfo>& mapProcesses);
	BOOL GetSignNameMap(map<int, wstring>& mapSignName);

	BOOL IsProcessNameExist(wstring strProcessName);

	int GetMaxProcessItemId();
	int GetProcessItemCount();

private:
	// ����
	BOOL ParseXml();
	BOOL ParsePathsNode();
	BOOL ParseCompanyNamesNode();
	BOOL ParseSignNamesNode();
	BOOL ParseProcessesNode();
	BOOL ParseMaxProcessItemIdNode();
	BOOL ParseProcessItemNode(TiXmlElement* nodes, KProcessInfo& processItem);

	// �����ڴ���������xml�ڵ�
	BOOL GenPathNodes(TiXmlElement* pRootNode);
	BOOL GenCompanyNameNodes(TiXmlElement* pRootNode);
	BOOL GenSignNameNodes(TiXmlElement* pRootNode);
	BOOL GenMaxProcessItemIdNode(TiXmlElement* pRootNode);
	BOOL GenProcessNodes(TiXmlElement* pRootNode);
	BOOL GenProcessItemNodes(TiXmlElement* pRootNode, KProcessInfo& processInfo);
	
	
	BOOL MergeIndexMap(map<int,wstring>* firstMap, map<int, wstring>* secondMap);
	BOOL IsMapValueExist(map<int, wstring>* mapToSearch, wstring& value);

private:
	map<int, wstring>   				m_mapPath;              // ·��
	map<int, wstring>   				m_mapCompanyNames;      // ��˾��
	map<int, wstring>   				m_mapSignNames;         // ����ǩ����
	map<wstring, KProcessInfo>			m_mapProcesses;         // ����
	multimap<wstring, KProcessItem>     m_mapProcessItems;      // �������б�Ϊ���Ż���ѯ
	
	int 								m_nMaxPathMapId;        // ·��Map�����ID
	int 								m_nMaxCompanyNamesMapId;// ��˾Map�����ID
	int 								m_nMaxSignNamesMapId;   // ����ǩ�������ID
	int 								m_nMaxProcessItemMapId; // ����Map�����ID
	
	TiXmlDocument*						m_pXmlDoc;             
};
