#include "stdafx.h"
#include "CUIMainScreen.h"
#include "CUIMainScreenBoard.h"
#include "CUIMainStartButton.h"
#include "CUIMainControllButton.h"
#include "CUIMainMakerButton.h"
#include "CUIMainEndButton.h"
#include "CGameScene.h"


CUIMainScreen::CUIMainScreen(CUIButton* pMaker, CUIButton* pControll):m_pMaker(pMaker),m_pControll(pControll)
{
	g_EventManager->Attach(eEvent::MainStart, this);
	g_EventManager->Attach(eEvent::MainControll, this);
	g_EventManager->Attach(eEvent::MainEnd, this);
	g_EventManager->Attach(eEvent::MainMaker, this);

	Setup();
}


CUIMainScreen::~CUIMainScreen()
{
}

void CUIMainScreen::Setup()
{
	CUI* board = new CUIMainScreenBoard();
	AddChild(board);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_vPosition = D3DXVECTOR2(rc.right / 2, 450);

	CUI* starUI = new CUIMainStartButton(D3DXVECTOR2(m_vPosition.x, m_vPosition.y), eBtnEvent::MainStart);
	board->AddChild(starUI);

	CUI* controllUI = new CUIMainControllButton(D3DXVECTOR2(m_vPosition.x, m_vPosition.y+130), eBtnEvent::MainControll);
	board->AddChild(controllUI);

	CUI* makerUI = new CUIMainMakerButton(D3DXVECTOR2(m_vPosition.x, m_vPosition.y+260), eBtnEvent::MainMaker);
	board->AddChild(makerUI);

	CUI* endUI = new CUIMainEndButton(D3DXVECTOR2(m_vPosition.x, m_vPosition.y+390), eBtnEvent::MainEnd);
	board->AddChild(endUI);
	ActiveUI();
}

bool CUIMainScreen::OnEvent(eEvent eEvent, void * _value)
{
	if (m_pMaker->GetActive() || m_pControll->GetActive())
		return true;

	switch (eEvent)
	{
	case eEvent::MouseClick:
		MouseClickEvent(_value);
		break;
	case eEvent::MouseHover:
		MouseHoverEvent(_value);
		break;
	case eEvent::MouseRelease:
		MouseReleaseEvent(_value);
		break;
	case eEvent::MainStart:
		StartGame();
		break;
	case eEvent::MainControll:
		m_pControll->ActiveUI();
		break;
	case eEvent::MainMaker:
		m_pMaker->ActiveUI();
		break;
	case eEvent::MainEnd:
		EndGame();
		break;
	}
	return true;
}

void CUIMainScreen::StartGame()
{
	CGameScene* scene = new CGameScene;
	thread _t1(&CGameScene::Load, scene, "data/js", "AllTest.json", &CGameScene::Init);
	_t1.detach();

	CScene* pBeforeScene = g_SceneManager->SetCurrentScene(scene);
	if (pBeforeScene)
	{
		thread _t2([pBeforeScene]() { delete pBeforeScene; });
		_t2.detach();
	}
}

void CUIMainScreen::EndGame()
{
	exit(-1);
}
