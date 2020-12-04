#pragma once
#include "CStaticMesh.h"
#define g_pStaticMeshManager CStaticMeshManager::GetInstance()

class CStaticMeshManager : public CSingleton<CStaticMeshManager>
{
private:
	map<string, CStaticMesh*> m_mapStaticMesh;
public:
	CStaticMeshManager();
	~CStaticMeshManager();

	CStaticMesh* GetStaticMesh(string name);
	void Load();
};

