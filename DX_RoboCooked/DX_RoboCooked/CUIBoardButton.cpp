#include "stdafx.h"
#include "CUIBoardButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"


CUIBoardButton::CUIBoardButton(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIBoardButton::~CUIBoardButton()
{
}

void CUIBoardButton::Setup()
{
	CUI* Texture = new CUITexture("data/UI/panel-info.png", NULL, NULL, m_vPosition);
	CUI* Text = new CUIText("UI_TEST");

	Add(Texture);
	Add(Text);

}

void CUIBoardButton::Update()
{
	for (const auto c : m_listUIchildren)
	{
		c->Update();
	}
}

void CUIBoardButton::Render()
{
	for (const auto c : m_listUIchildren)
	{
		c->Render();
	}
}
