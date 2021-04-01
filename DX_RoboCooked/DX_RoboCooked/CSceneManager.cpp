#include "stdafx.h"
#include "CScene.h"



CSceneManager::CSceneManager():CSingleton<CSceneManager>()
	 ,m_pCurrentScene(nullptr)
{

}


CSceneManager::~CSceneManager()
{
	SafeDelete(m_pCurrentScene);
}

CScene* CSceneManager::SetCurrentScene(CScene* Scene)
{
	CScene* pBeforeScene = m_pCurrentScene;
	m_pCurrentScene = Scene;
	return pBeforeScene;
}


CScene* CSceneManager::GetCurrentScene()
{
	return m_pCurrentScene;
}

void CSceneManager::Update()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Update();
}

void CSceneManager::Render()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Render();
}

void CSceneManager::Destroy()
{
	SafeDelete(m_pCurrentScene);
}

