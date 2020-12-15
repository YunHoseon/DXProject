#include "stdafx.h"
#include "CUILoading.h"
#include "CUITexture.h"

CUILoading::CUILoading(D3DXVECTOR2 vPos)
	: m_isLoading(false)
{
	m_vPosition = vPos;
	g_EventManager->Attach(eEvent::KeyPress, this);
}


CUILoading::~CUILoading()
{
}

void CUILoading::Setup()
{
	m_pTexture = new CUITexture("data/UI/roadingScreen.png", "data/UI/roadingScreen.png", "data/UI/roadingScreen.png", m_vPosition);
}

void CUILoading::Render()
{
}
