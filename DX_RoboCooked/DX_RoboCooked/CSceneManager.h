#pragma once

#define g_SceneManager CSceneManager::GetInstance()


class CScene;

class CSceneManager : public CSingleton<CSceneManager>
{
public:
	CSceneManager();
	~CSceneManager();

public:
	void SceneChange(std::string sceneName);
	void AddScene(std::string SceneName, CScene* scene);
	void EraseScene(std::string SceneName);
	void SetCurrentScene(CScene* Scene);
	CScene* GetCurrentScene();
	
private:
	std::map<std::string,CScene*> m_SceneList;
	CScene* m_pCurrentScene;


};

