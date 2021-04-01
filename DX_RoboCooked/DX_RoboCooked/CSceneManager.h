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
	CScene* SetCurrentScene(CScene* Scene);
	CScene* GetCurrentScene();
	void Update();
	void Render();
	
	void Destroy();
private:
	CScene* m_pCurrentScene;


};


