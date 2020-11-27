#include "stdafx.h"
#include "CUICloseButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"


CUICloseButton::CUICloseButton(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUICloseButton::~CUICloseButton()
{
}

void CUICloseButton::Setup()
{
	CUI* Texture = new CUITexture("data/UI/btn-main-menu.png", NULL, NULL, m_vPosition);
	Add(Texture);
}

void CUICloseButton::Update()
{
	for (const auto c : m_listUIchildren)
	{
		c->Update();
	}
}

void CUICloseButton::Render()
{
	for (const auto c : m_listUIchildren)
	{
		c->Render();
	}
}

