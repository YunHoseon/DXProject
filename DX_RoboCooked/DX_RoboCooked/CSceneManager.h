#pragma once

#define g_SceneManager CSceneManager::GetInstance()


class CScene;

class CSceneManager : public CSingleton<CSceneManager>
{
private:
	friend CSingleton<CSceneManager>;
	CSceneManager();
	~CSceneManager();

public:
	//void SceneChange(std::string sceneName);
	//void AddScene(std::string SceneName, CScene* scene);
	//void EraseScene(std::string SceneName);
	CScene* SetCurrentScene(CScene* Scene);
	CScene* GetCurrentScene();
	
	void Destroy();
private:
	//std::map<std::string,CScene*> m_SceneList;
	CScene* m_pCurrentScene;


};

