#pragma once
#include "CStaticMesh.h"
#define g_pStaticMeshManager CStaticMeshManager::GetInstance()

class CStaticMeshManager : public CSingleton<CStaticMeshManager>
{
private:
	struct ST_StaticMesh_Data
	{
		string fileName;
		string objectName;
		string filePath;
	};
	map<string, CStaticMesh*> m_mapStaticMesh;
	bool m_isLoaded;
public:
	CStaticMeshManager();
	~CStaticMeshManager();

	CStaticMesh* GetStaticMesh(string name);
	void Load();

	bool IsLoaded() { return m_isLoaded; }
};

