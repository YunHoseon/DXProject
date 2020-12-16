#include "stdafx.h"
#include "CMainScene.h"
#include "CUIMainScreen.h"


CMainScene::CMainScene():m_pScreen(nullptr)
{
	Init();
}


CMainScene::~CMainScene()
{
	SafeDelete(m_pScreen);
}

void CMainScene::Init()
{
	m_pScreen = new CUIMainScreen;
}

void CMainScene::Render()
{
	if (m_pScreen)
		m_pScreen->Render();
}

void CMainScene::Update()
{
	if (m_pScreen)
		m_pScreen->Update();
}
