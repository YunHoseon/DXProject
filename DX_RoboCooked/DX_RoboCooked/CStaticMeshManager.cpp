#include "stdafx.h"
#include "CStaticMeshManager.h"
#include "CMeshLoader.h"

CStaticMeshManager::CStaticMeshManager()
{
	Load();
}


CStaticMeshManager::~CStaticMeshManager()
{
}

CStaticMesh* CStaticMeshManager::GetStaticMesh(string name)
{
	return m_mapStaticMesh[name];
}

void CStaticMeshManager::Load()
{
	CStaticMesh* StaticMesh = new CStaticMesh;
	CStaticMesh* StaticMesh2 = new CStaticMesh;
	
	string name = "AutoCombinator";
	CMeshLoader::LoadMesh("MixMch1.X", "data/model/object", StaticMesh);
	m_mapStaticMesh.emplace(name, StaticMesh);

	name = "ManualCombinator";
	CMeshLoader::LoadMesh("MixMch2.X", "data/model/object", StaticMesh2);
	m_mapStaticMesh.emplace(name, StaticMesh2);
}
