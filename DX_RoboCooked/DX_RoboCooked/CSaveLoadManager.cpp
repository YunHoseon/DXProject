#include "stdafx.h"
#include "CSaveLoadManager.h"
#include <fstream>

CSaveLoadManager::CSaveLoadManager()
{
	std::ifstream is("data/js/SaveData.json");
	is >> m_jSaveData;
	is.close();
}

CSaveLoadManager::~CSaveLoadManager()
{
	
}

void CSaveLoadManager::Save()
{
	g_pThreadManager->AddThread(thread([this]() 
	{ 
		std::ofstream o("data/js/SaveData.json");o << m_jSaveData; o.close(); 
	}
	));
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

string CSaveLoadManager::GetStageIDByIndex(int nIndex)
{
	json jData = GetStageData(nIndex);
	string sStageID = jData["StageID"];
	return sStageID;
}

int CSaveLoadManager::GetMaxIndex()
{
	return m_jSaveData["StageIndex"].size() - 1;
}

int CSaveLoadManager::GetDataSize()
{
	return m_jSaveData["StageIndex"].size();
}
