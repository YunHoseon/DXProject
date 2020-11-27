#include "stdafx.h"
#include "CUIBarButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"

CUIBarButton::CUIBarButton(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIBarButton::~CUIBarButton()
{
}

void CUIBarButton::Setup()
{
	CUI* Texture = new CUITexture("data/UI/btn-med-over.png", NULL, NULL, m_vPosition);
	Add(Texture);
}

void CUIBarButton::Update()
{
	for (const auto c : m_listUIchildren)
	{
		c->Update();
	}
}

void CUIBarButton::Render()
{
	for (const auto c : m_listUIchildren)
	{
		c->Render();
	}
}
