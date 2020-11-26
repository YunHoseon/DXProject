#include "stdafx.h"
#include "CUI.h"
#include "CPauseUI.h"
#include "CUISprite.h"


CPauseUI::CPauseUI()
{
	Setup();
}


CPauseUI::~CPauseUI()
{
	if(m_pRoot)
		m_pRoot->Destroy();

}

void CPauseUI::Setup()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_vSize = g_pUITextureManager->GetTextureSize("data/UI/panel-info.png");

	D3DXVECTOR2 vecTemp(rc.right/2.0f - m_vSize.x,rc.bottom/2.0f - m_vSize.y);
	CUISprite* m_cBody = new CUISprite("data/UI/panel-info.png",NULL,NULL , vecTemp);
	
	m_cBody->SetParentWorldTM(&m_matWorld);
	m_pRoot = m_cBody;


	
	vecTemp = D3DXVECTOR2(130, 330);
	CUISprite* m_cOk = new CUISprite("data/UI/btn-med-over.png", "data/UI/btn-med-down.png", "data/UI/btn-med-up.png" , vecTemp);
	m_pRoot->AddChild(m_cOk);
	
	vecTemp = D3DXVECTOR2(130, 400);
	CUISprite* m_cCancel = new CUISprite("data/UI/btn-med-over.png","data/UI/btn-med-down.png", "data/UI/btn-med-up.png" , vecTemp);
	m_pRoot->AddChild(m_cCancel);


	vecTemp = D3DXVECTOR2(400, 80);
	CUISprite* m_cExit = new CUISprite("data/UI/btn-main-menu.png",NULL,NULL , vecTemp);
	m_pRoot->AddChild(m_cExit);



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

