#include "stdafx.h"
#include "CMainScene.h"
#include "CUIMainScreen.h"
#include "CUIMaker.h"
#include "CUIControll.h"
#include "CUIStageSelect.h"


CMainScene::CMainScene()
	:m_pScreen(nullptr),
	m_pUIMaker(nullptr),
	m_pUIControll(nullptr),
	m_pUIStageSelect(nullptr)
{
	g_SoundManager->AddBGM("data/Sound/bgm/911.mp3");
	g_SoundManager->PlayBGM();
	Init();
}


CMainScene::~CMainScene()
{
	SafeDelete(m_pScreen);
	SafeDelete(m_pUIMaker);
	SafeDelete(m_pUIStageSelect)
}

void CMainScene::Init()
{
	m_pUIMaker = new CUIMaker(D3DXVECTOR2(465, 10));
	m_pUIControll = new CUIControll(D3DXVECTOR2(465, 10));
	m_pUIStageSelect = new CUIStageSelect(D3DXVECTOR2(165, 10));
	//m_pUIStageSelect->SetActive(true);
	m_pScreen = new CUIMainScreen(m_pUIStageSelect,m_pUIMaker, m_pUIControll);
}

void CMainScene::Render()
{
	if (m_pScreen)
		m_pScreen->Render();

	if (m_pUIMaker)
		m_pUIMaker->Render();

	if (m_pUIControll)
		m_pUIControll->Render();

	if (m_pUIStageSelect)
		m_pUIStageSelect->Render();
}

void CMainScene::Update()
{
}
