﻿#include "stdafx.h"
#include "CPartsManager.h"
#include <fstream>

#include "CMeshLoader.h"
#include "CParts.h"

static std::mutex cMutex;

CPartsManager::CPartsManager() : m_isLoaded(false)
{
	Load();
	m_isLoaded = true;
}

CPartsManager::~CPartsManager()
{
	for (auto && p : m_mapParts)
	{
		SafeDelete(p.second);
	}
}

void CPartsManager::Load()
{
	std::ifstream is("data/js/PartsData.json");
	json j;
	is >> j;
	is.close();

	// 1. 조합식으로만 검색
	// 2. ID로만 검색
	// 3. 두 가지 접근점을 모두 제공
	{
		for (int i = 0; i < j.size(); ++i)
		{
			if (g_pThreadManager->GetStopMessage()) return;
			string id = j[i]["ID"];
			string filename = j[i]["Filename"];
			float fMass = j[i]["Mass"];
			fMass *= 0.1f;
			CParts* part = new CParts(id, j[i]["Formula"], fMass);
			CMeshLoader::LoadMesh(filename, "data/model/parts", part->GetStaticMesh());
			part->Setup(D3DXVECTOR3(j[i]["Size"][0], j[i]["Size"][1], j[i]["Size"][2]));
			//part->Setup(D3DXVECTOR3(0.5, 0.5, 0.5));
			cMutex.lock();
			m_mapParts.emplace(id, part);
			m_mapFormula.emplace(j[i]["Formula"], j[i]["ID"]);
			cMutex.unlock();
		}
	}
}

CParts* CPartsManager::CreateParts(string sID)
{
	if(m_mapParts.find(sID) != m_mapParts.end())
		return m_mapParts[sID]->Clone();
	return m_mapParts["D00"]->Clone();
}

string CPartsManager::GetIDFromFormula(string sFormula)
{
	if (m_mapFormula.find(sFormula) != m_mapFormula.end())
		return m_mapFormula[sFormula];
	return m_mapFormula[""];
}
