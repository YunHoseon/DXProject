#include "stdafx.h"
#include "CMainScene.h"
#include "CUIMainScreen.h"
#include "CUIMaker.h"
#include "CUIControll.h"


CMainScene::CMainScene():m_pScreen(nullptr), m_pMaker(nullptr), m_pControll(nullptr)
{
	g_SoundManager->AddBGM("data/Sound/bgm/911.mp3");
	g_SoundManager->PlayBGM();
	Init();
}


CMainScene::~CMainScene()
{
	SafeDelete(m_pScreen);
	SafeDelete(m_pMaker);
}

void CMainScene::Init()
{
	
	
	m_pMaker = new CUIMaker();
	m_pControll = new CUIControll();

	m_pScreen = new CUIMainScreen(m_pMaker, m_pControll);
}

void CMainScene::Render()
{

	if (m_pScreen)
		m_pScreen->Render();

	if (m_pMaker)
		m_pMaker->Render();

	if (m_pControll)
		m_pControll->Render();



}

void CMainScene::Update()
{
}
