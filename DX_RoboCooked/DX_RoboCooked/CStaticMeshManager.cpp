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

	data.fileName = "MixMch1.X"; data.objectName = "CombinatorLevel1"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "MixMch2.X"; data.objectName = "CombinatorLevel2"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Vending.X"; data.objectName = "Vending"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Switch1.X"; data.objectName = "SwitchLevel1"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Switch2.X"; data.objectName = "SwitchLevel2"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "모래더미.X"; data.objectName = "Sandpile"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Cactus.X"; data.objectName = "Cactus"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Coffin.X"; data.objectName = "Coffin"; data.filePath = "data/model/object";
	vecData.push_back(data);

	data.fileName = "모래타일1.X"; data.objectName = "Sand"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	data.fileName = "모래타일2.X"; data.objectName = "ThickSand"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	data.fileName = "모래타일3.X"; data.objectName = "FlowSand"; data.filePath = "data/model/tile";
	vecData.push_back(data);		
	data.fileName = "물타일.X"; data.objectName = "Water"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	data.fileName = "모래돌타일1.X"; data.objectName = "Soil"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	data.fileName = "모래돌_벽_타일.X"; data.objectName = "Brick"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	data.fileName = "모래돌_타일_계단 일반.X"; data.objectName = "Stair"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	
	
	for (ST_StaticMesh_Data datas : vecData)
	{
		CStaticMesh* staticMesh = new CStaticMesh;
		CMeshLoader::LoadMesh(datas.fileName, datas.filePath, staticMesh);
		m_mapStaticMesh.emplace(datas.objectName, staticMesh);
	}
}
