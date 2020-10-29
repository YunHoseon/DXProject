#pragma once

#define g_pSkinnedMeshManager	CSkinnedMeshManager::GetInstance()
class CSkinnedMesh;

class CSkinnedMeshManager : public CSingleton<CSkinnedMeshManager>
{
public:
	//Singletone(CSkinnedMeshManager);
private:
	map<string, CSkinnedMesh*> m_mapSkinnedMesh;

	CSkinnedMeshManager();
	~CSkinnedMeshManager();
public:
	CSkinnedMesh*		GetSkinnedMesh(char* szFolder, char* szFileName);
	void				Destroy();
	
};
