#include "stdafx.h"
#include "CPartsManager.h"
#include <fstream>

CPartsManager::CPartsManager()
{
	Load();
}

CPartsManager::~CPartsManager()
{
}

void CPartsManager::Load()
{
	std::ifstream is("data/js/PartsData.json");
	json j;
	is >> j;

	// 1. 조합식으로만 검색
	// 2. ID로만 검색
	// 3. 두 가지 접근점을 모두 제공

	for (int i = 0; i < j.size(); ++i)
	{
		ST_Parts_Attr st;
		st.sID = j[i]["ID"];
		st.fMass = j[i]["Mass"];
		st.sFormula = j[i]["Formula"];
		_DEBUG_COMMENT cout << "ID : " << st.sID << endl;
		_DEBUG_COMMENT cout << "Formula : " << st.sFormula << endl;
		_DEBUG_COMMENT cout << "Mass : " << st.fMass << endl << endl;

		m_mapPartsAttr.emplace(st.sID, st);
		m_mapFormula.emplace(st.sFormula, st.sID);
	}
}

CParts* CPartsManager::CreateParts(string sID)
{
	return nullptr;
}

string CPartsManager::GetIDFromFormula(string sFormula)
{
	return "";
}
