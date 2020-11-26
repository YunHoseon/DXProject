#include "stdafx.h"
#include "CUI.h"
#include "CPauseUI.h"
#include "CUISprite.h"


CPauseUI::CPauseUI()
{

}


CPauseUI::~CPauseUI()
{
	if(m_pRoot)
		m_pRoot->Destroy();

}

void CPauseUI::Setup()
{

	Sprite sp;
	
	D3DXVECTOR2 vecTemp(0,0);
	CUISprite* m_cBody = new CUISprite("UI","panel-info.png",NULL,NULL);
	m_cBody->Setup(vecTemp);
	
	m_cBody->SetParentWorldTM(&m_matWorld);
	m_pRoot = m_cBody;
	//sp.st_Position = D3DXVECTOR2(0, 0); sp.st_SpriteSize = g_pUITextureManager->GetTextureSize("UI/panel-info.png");
	//m_vecSprite.push_back(sp);
	m_vSize = g_pUITextureManager->GetTextureSize("UI/panel-info.png");
	m_vecBtn.push_back(m_cBody);

	
	vecTemp = D3DXVECTOR2(130, 330);
	CUISprite* m_cOk = new CUISprite("UI", "btn-med-over.png", "UI", "btn-med-down.png");
	m_cOk->Setup(vecTemp);
	m_pRoot->AddChild(m_cOk);
	sp.st_Position = D3DXVECTOR2(130, 330); sp.st_SpriteSize = g_pUITextureManager->GetTextureSize("UI/btn-med-over.png");
	m_vecSprite.push_back(sp);
	m_vecBtn.push_back(m_cOk);

	
	vecTemp = D3DXVECTOR2(130, 400);
	CUISprite* m_cCancel = new CUISprite("UI", "btn-med-over.png", "UI", "btn-med-down.png");
	m_cCancel->Setup(vecTemp);
	m_pRoot->AddChild(m_cCancel);
	sp.st_Position = D3DXVECTOR2(130, 400); sp.st_SpriteSize = g_pUITextureManager->GetTextureSize("UI/btn-med-over.png");
	m_vecSprite.push_back(sp);
	m_vecBtn.push_back(m_cCancel);


	vecTemp = D3DXVECTOR2(400, 80);
	CUISprite* m_cExit = new CUISprite("UI", "btn-main-menu.png",NULL,NULL);
	m_cExit->Setup(vecTemp);
	m_pRoot->AddChild(m_cExit);
	sp.st_Position = D3DXVECTOR2(400, 80); sp.st_SpriteSize = g_pUITextureManager->GetTextureSize("UI/btn-main-menu.png");
	m_vecSprite.push_back(sp);
	m_vecBtn.push_back(m_cExit);


}

void CPauseUI::Update()
{
	if (m_pRoot)
		m_pRoot->Update();
}

void CPauseUI::Render()
{
	if (m_pRoot)
		m_pRoot->Render();
}

void CPauseUI::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	}
		
}

void CPauseUI::ClickEvent(EVENT ev)
{
	switch (ev)
	{
	case EN_OK:
		m_vecBtn[ev]->BtnOnOff();
		break;
	case EN_CANCEL:
		m_vecBtn[ev]->BtnOnOff();
		break;
	case EN_EXIT:
		break;

	}
}

int CPauseUI::ChildBtnInCheck(POINT pt)
{
	for (int i = 0; i < m_vecSprite.size(); i++)
	{
		if(EN_BODY == i)continue;

		if (m_vPosition.x+ m_vecSprite[i].st_Position.x <= pt.x &&m_vPosition.x + m_vecSprite[i].st_Position.x + m_vecSprite[i].st_SpriteSize.x >= pt.x
			&& m_vPosition.y + m_vecSprite[i].st_Position.y <= pt.y &&m_vPosition.y + m_vecSprite[i].st_Position.y + m_vecSprite[i].st_SpriteSize.y >= pt.y)
			return i;
	}
	return 0;
}

