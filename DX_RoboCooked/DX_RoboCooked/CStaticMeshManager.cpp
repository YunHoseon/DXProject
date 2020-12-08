#include "stdafx.h"
#include "CStaticMeshManager.h"
#include "CMeshLoader.h"

CStaticMeshManager::CStaticMeshManager()
{
	Load();
}


CStaticMeshManager::~CStaticMeshManager()
{
	for (auto it : m_mapStaticMesh)
	{
		SafeDelete(it.second);
	}
	m_mapStaticMesh.clear();
}

CStaticMesh* CStaticMeshManager::GetStaticMesh(string name)
{
	return m_mapStaticMesh[name];
}

void CStaticMeshManager::Load()
{
	vector<ST_StaticMesh_Data> vecData;
	ST_StaticMesh_Data data;

	data.fileName = "MixMch1.X"; data.objectName = "AutoCombinator"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "MixMch2.X"; data.objectName = "ManualCombinator"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "모래타일3.X"; data.objectName = "Sand3"; data.filePath = "data/model/tile";
	vecData.push_back(data);		
	data.fileName = "물타일.X"; data.objectName = "Water"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	data.fileName = "모래돌_타일_계단 일반.X"; data.objectName = "Stair"; data.filePath = "data/model/tile";
	vecData.push_back(data);

	data.fileName = "Vending.X"; data.objectName = "Vending"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Switch1.X"; data.objectName = "Switch1"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Switch2.X"; data.objectName = "Switch2"; data.filePath = "data/model/object";
	vecData.push_back(data);
	
	for (ST_StaticMesh_Data datas : vecData)
	{
		CStaticMesh* staticMesh = new CStaticMesh;
		CMeshLoader::LoadMesh(datas.fileName, datas.filePath, staticMesh);
		m_mapStaticMesh.emplace(datas.objectName, staticMesh);
	}
}
