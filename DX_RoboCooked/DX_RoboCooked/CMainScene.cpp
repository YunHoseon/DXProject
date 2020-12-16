#include "stdafx.h"
#include "CMainScene.h"
#include "CUIMainScreen.h"
#include "CUIMaker.h"


CMainScene::CMainScene():m_pScreen(nullptr), m_pMaker(nullptr)
{
	Init();
}


CMainScene::~CMainScene()
{
	SafeDelete(m_pScreen);
	SafeDelete(m_pMaker);
}

void CMainScene::Init()
{
	m_pScreen = new CUIMainScreen;
	m_pMaker = new CUIMaker(D3DXVECTOR2(465, 10));
	m_pMaker->InvertActive();
}

void CMainScene::Render()
{

	if (m_pScreen)
		m_pScreen->Render();

	if (m_pMaker)
		m_pMaker->Render();



}

void CMainScene::Update()
{
}
