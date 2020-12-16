#include "stdafx.h"
#include "CUIPauseButton.h"
#include "CGameScene.h"
#include "CMainScene.h"
#include "CUIText.h"
#include "CUITexture.h"
#include "CUIPauseBoard.h"
#include "CUIResetButton.h"
#include "CUIEndButton.h"
#include "CUIMainButton.h"
#include "CUICloseButton.h"
#include "IInteractCenter.h"



CUIPauseButton::CUIPauseButton(D3DXVECTOR2 vPos, WPARAM wParam, IInteractCenter* pInteractCenter)
			: m_pInteractCenter(pInteractCenter)
{
	m_vPosition = vPos;
	m_wActiveButton = wParam;
	Setup();

	g_EventManager->Attach(eEvent::KeyPress, this);
	g_EventManager->Attach(eEvent::KeyRelease, this);
	g_EventManager->Attach(eEvent::MouseRelease, this);

	g_EventManager->Attach(eEvent::PauseMain, this);
	g_EventManager->Attach(eEvent::PauseClose, this);
	g_EventManager->Attach(eEvent::PauseReset, this);
	g_EventManager->Attach(eEvent::PauseEnd, this);
}


CUIPauseButton::~CUIPauseButton()
{
}

void CUIPauseButton::Setup()
{
	CUI* board = new CUIPauseBoard(m_vPosition, eBtnEvent::None);
	AddChild(board);
	//m_vPosition = board->GetPosition();

	CUI* mainBtn = new CUIMainButton(D3DXVECTOR2(m_vPosition.x + 250, m_vPosition.y + 200), eBtnEvent::PauseMain);
	board->AddChild(mainBtn);

	CUI* closeBtn = new CUICloseButton(D3DXVECTOR2(m_vPosition.x + 550, m_vPosition.y + 200), eBtnEvent::PauseClose);
	board->AddChild(closeBtn);

	CUI* ResetBtn = new CUIResetButton(D3DXVECTOR2(m_vPosition.x + 250, m_vPosition.y + 500), eBtnEvent::PauseReset);
	board->AddChild(ResetBtn);

	CUI* EndBtn = new CUIEndButton(D3DXVECTOR2(m_vPosition.x + 550, m_vPosition.y + 500), eBtnEvent::PauseEnd);
	board->AddChild(EndBtn);
}

bool CUIPauseButton::OnEvent(eEvent eEvent, void * _value)
{
	switch (eEvent)
	{
	case eEvent::MouseClick:
		MouseClickEvent(_value);
		break;
	case eEvent::MouseHover:
		MouseHoverEvent(_value);
		break;
	case eEvent::KeyPress:
		KeyPressEvent(_value);
		break;
	case eEvent::KeyRelease:
		KeyReleaseEvent(_value);
		break;
	case eEvent::MouseRelease:
		MouseReleaseEvent(_value);
		break;
	case eEvent::PauseMain:
		GoToMain();
		break; 
	case eEvent::PauseClose:
		ActiveButton();
		break;
	case eEvent::PauseReset:
		ResetGame();
		break;
	case eEvent::PauseEnd:
		SendMessage(g_hWnd, WM_CLOSE, 0, 0);
		break;
	}
	return true;
}

void CUIPauseButton::KeyPressEvent(void * _value)
{
	ST_KeyInputEvent *data = static_cast<ST_KeyInputEvent*>(_value);

	if (data->wKey == m_wActiveButton)
	{
		m_isKeyDown = true;
	}
}

void CUIPauseButton::KeyReleaseEvent(void * _value)
{
	ST_KeyInputEvent* data = static_cast<ST_KeyInputEvent*>(_value);
	
	if (data->wKey == m_wActiveButton)
	{
		ActiveButton();
	}
}

void CUIPauseButton::ActiveButton()
{
	if (m_isKeyDown == true || m_isMouseDown == true)
	{
		m_isKeyDown = false;
		m_isMouseDown = false;
		for (auto it : m_listUIchildren)
		{
			it->InvertActive();
		}
		m_isActive = !m_isActive;

		if (m_isActive)
		{
			g_EventManager->Attach(eEvent::MouseClick, this);
			g_EventManager->Attach(eEvent::MouseHover, this);
			//g_EventManager->Attach(eEvent::MouseRelease, this);
		}
		else
		{
			g_EventManager->Detach(eEvent::MouseClick, this);
			g_EventManager->Detach(eEvent::MouseHover, this);
			//g_EventManager->Detach(eEvent::MouseRelease, this);
		}
		m_pInteractCenter->ToggleStop();
	}
}

void CUIPauseButton::ResetGame()
{
	//return;
	CGameScene* scene = new CGameScene;
	
	thread _t1(&CGameScene::Load, scene, "data/js", m_pInteractCenter->GetSceneID(), &CGameScene::Init);
	_t1.detach();

	CScene* pBeforeScene = g_SceneManager->SetCurrentScene(scene);
	if (pBeforeScene)
	{
		thread _t2([pBeforeScene]() { delete pBeforeScene; });
		_t2.detach();
	}
}

void CUIPauseButton::GoToMain()
{
	CMainScene* scene = new CMainScene;

	CScene* pBeforeScene = g_SceneManager->SetCurrentScene(scene);
	if (pBeforeScene)
	{
		thread _t2([pBeforeScene]() { delete pBeforeScene; });
		_t2.detach();
	}
}
