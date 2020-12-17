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

	data.fileName = "combinator1.X"; data.objectName = "CombinatorLevel1"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "combinator2.X"; data.objectName = "CombinatorLevel2"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Vending.X"; data.objectName = "Vending"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Switch1.X"; data.objectName = "SwitchLevel1"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Switch2.X"; data.objectName = "SwitchLevel2"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "sandpile.X"; data.objectName = "Sandpile"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Cactus.X"; data.objectName = "Cactus"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Coffin.X"; data.objectName = "Coffin"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "TV.X"; data.objectName = "TV"; data.filePath = "data/model/object";
	vecData.push_back(data);
	data.fileName = "Whiteboard.X"; data.objectName = "Whiteboard"; data.filePath = "data/model/object";
	vecData.push_back(data);

	data.fileName = "sand.X"; data.objectName = "Sand"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	data.fileName = "thicksand.X"; data.objectName = "ThickSand"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	data.fileName = "flowsand.X"; data.objectName = "FlowSand"; data.filePath = "data/model/tile";
	vecData.push_back(data);		
	data.fileName = "flowsand_upper.X"; data.objectName = "FlowSand_Upper"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	data.fileName = "water.X"; data.objectName = "Water"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	data.fileName = "soil.X"; data.objectName = "Soil"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	data.fileName = "brick.X"; data.objectName = "Brick"; data.filePath = "data/model/tile";
	vecData.push_back(data);
	data.fileName = "stair.X"; data.objectName = "Stair"; data.filePath = "data/model/tile";
	vecData.push_back(data);

	data.fileName = "harpy_skill_2_1.X"; data.objectName = "Harpy_Wing_L"; data.filePath = "data/model/monster";
	vecData.push_back(data);
	data.fileName = "harpy_skill_2_2.X"; data.objectName = "Harpy_Wing_R"; data.filePath = "data/model/monster";
	vecData.push_back(data);
	
	for (ST_StaticMesh_Data datas : vecData)
	{
		CStaticMesh* staticMesh = new CStaticMesh;
		CMeshLoader::LoadMesh(datas.fileName, datas.filePath, staticMesh);
		m_mapStaticMesh.emplace(datas.objectName, staticMesh);
	}
}
