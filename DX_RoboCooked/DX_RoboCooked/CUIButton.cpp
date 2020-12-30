#include "stdafx.h"
#include "CUIButton.h"
#include "CUITexture.h"
#include "CUIText.h"
#include "CMainScene.h"
#include "CGameScene.h"



CUIButton::CUIButton(IInteractCenter* pInteractCenter)
	: m_pTexture(nullptr)
	, m_pText(nullptr)
	, m_isKeyDown(false)
	, m_pInteractCenter(pInteractCenter)
	//, m_isMouseDown(false)
{
	m_pInputKey[0] = InputManager->GetInputKey(0);
	m_pInputKey[1] = InputManager->GetInputKey(1);
}


CUIButton::~CUIButton()
{
	for (CUI * p : m_listUIchildren)
	{
		SafeDelete(p);
	}
}

void CUIButton::Render()
{
	if (!m_isActive)
		return;

	if (m_pTexture)
		m_pTexture->RenderTexture(m_eUIState);

	if (m_pText)
		m_pText->Render();

	for (const auto c : m_listUIchildren)
	{
		c->Render();
	}
}

void CUIButton::SetPosition(float x, float y)
{
	D3DXVECTOR2 dir = D3DXVECTOR2(x, y) - m_vPosition;
	m_vPosition += dir;
	for (list<CUI*>::value_type p : m_listUIchildren)
	{
		AddPosition(dir.x, dir.y);
	}
}

void CUIButton::ResetGame()
{

	if (m_pInteractCenter == nullptr)
		return;

	//return;
	CGameScene* scene = new CGameScene;

	g_pThreadManager->AddThread(thread(&CGameScene::Load, scene, "data/js", m_pInteractCenter->GetSceneID(), &CGameScene::Init));

	CScene* pBeforeScene = g_SceneManager->SetCurrentScene(scene);
	if (pBeforeScene)
	{
		g_pThreadManager->AddThread(thread([pBeforeScene]() { delete pBeforeScene; }));
	}
}

void CUIButton::GoToMain()
{
	CMainScene* scene = new CMainScene;

	CScene* pBeforeScene = g_SceneManager->SetCurrentScene(scene);
	if (pBeforeScene)
	{
		g_pThreadManager->AddThread(thread([pBeforeScene]() { delete pBeforeScene; }));
	}
}

void CUIButton::NextStage()
{
	if (m_pInteractCenter == nullptr)
		return;

	int iTemp = g_SaveLoadManager->GetIndexByKey(m_pInteractCenter->GetSceneID()) + 1;
	if (iTemp > g_SaveLoadManager->GetMaxIndex())
	{
		GoToMain();
		return;
	}

	CGameScene* scene = new CGameScene;

	g_pThreadManager->AddThread(thread(&CGameScene::Load, scene, "data/js", g_SaveLoadManager->GetStageIDByIndex(iTemp), &CGameScene::Init));

	CScene* pBeforeScene = g_SceneManager->SetCurrentScene(scene);
	if (pBeforeScene)
	{
		g_pThreadManager->AddThread(thread([pBeforeScene]() { delete pBeforeScene; }));
	}

}

void CUIButton::AddChild(CUI * component)
{
	this->m_listUIchildren.push_back(component);
	component->SetParent(this);
}

void CUIButton::Remove(CUI * component)
{
	m_listUIchildren.remove(component);
	component->SetParent(nullptr);
}

void CUIButton::MouseClickEvent(void * _value)
{
	ST_MouseEvent *data = static_cast<ST_MouseEvent*>(_value);


	for (auto it : m_listUIchildren)
	{
		it->CheckPressIn(data->pt);
	}
	m_isMouseDown = true;
}

void CUIButton::MouseHoverEvent(void * _value)
{
	ST_MouseEvent *data = static_cast<ST_MouseEvent*>(_value);

	for (auto it : m_listUIchildren)
	{
		it->CheckInHover(data->pt);
	}
}

void CUIButton::MouseReleaseEvent(void * _value)
{
	ST_MouseEvent *data = static_cast<ST_MouseEvent*>(_value);

	for (auto it : m_listUIchildren)
	{
		it->CheckReleaseIn(data->pt);
	}
	m_isMouseDown = false;
}



