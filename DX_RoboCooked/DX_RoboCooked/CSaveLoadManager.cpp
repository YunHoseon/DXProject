#include "stdafx.h"
#include "CSaveLoadManager.h"

CSaveLoadManager::CSaveLoadManager()
{
	// SaveData의 로드
}

CSaveLoadManager::~CSaveLoadManager()
{
	
}

void CSaveLoadManager::Save()
{
	// SaveData를 스레드매니저를 이용해 저장
	
}

string CSaveLoadManager::GetKeyByIndex(int nIndex)
{
	return string(m_jSaveData["StageIndex"][nIndex]);
}

int CSaveLoadManager::GetIndexByKey(string sKey)
{
	string s;
	for (int i = 0; i < m_jSaveData["StageIndex"].size(); ++i)
	{
		s = m_jSaveData["StageIndex"][i];
		if (sKey == s)
			return i;
	}
	return -1;
}

json& CSaveLoadManager::GetStageData(int nIndex)
{
	string sKey = m_jSaveData["StageIndex"][nIndex];
	return m_jSaveData[sKey];
}

json& CSaveLoadManager::GetStageData(string sKey)
{
	return m_jSaveData[sKey];
}

json& CSaveLoadManager::GetSaveData()
{
	return m_jSaveData;
}

int CSaveLoadManager::GetMaxIndex()
{
	return m_jSaveData["StageIndex"].size() - 1;
}
