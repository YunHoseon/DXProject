#include "stdafx.h"
#include "CUIPause.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"

CUIPause::CUIPause()
{
	Setup();
}


CUIPause::~CUIPause()
{
}


void CUIPause::Setup()
{
	CUI* BackBoard = new CUITexture("data/UI/panel-info.png", NULL, NULL);
	CUI* BackBoardText = new CUIText;

	Add(BackBoard);
	Add(BackBoardText);
}

void CUIPause::Update()
{
	for (const auto c : m_listUIchildren)
	{
		c->Update();
	}
}

void CUIPause::Render()
{
	for (const auto c : m_listUIchildren)
	{
		c->Render();
	}
}

void CUIPause::Add(CUI * component)
{
	this->m_listUIchildren.push_back(component);
	component->SetParent(this);
}

void CUIPause::Remove(CUI * component)
{
	m_listUIchildren.remove(component);
	component->SetParent(nullptr);
}
