#pragma once

#define g_SaveLoadManager CSaveLoadManager::GetInstance()

class CSaveLoadManager : public CSingleton<CSaveLoadManager>
{
private:
	friend class CSingleton<CSaveLoadManager>;
	CSaveLoadManager();
	~CSaveLoadManager();

	json m_jSaveData;
public:
	void Save();
	string GetKeyByIndex(int nIndex);
	int GetIndexByKey(string sKey);
	json& GetStageData(int nIndex);
	json& GetStageData(string sKey);
	json& GetSaveData();

	int GetMaxIndex();
	int GetDataSize();
};
