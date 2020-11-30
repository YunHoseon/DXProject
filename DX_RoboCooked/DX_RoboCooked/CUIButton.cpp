#include "stdafx.h"
#include "CUIButton.h"
#include "CUITexture.h"
#include "CUIText.h"



CUIButton::CUIButton()
	: m_pTexture(nullptr)
	, m_pText(nullptr)
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

void CUIButton::Update()
{
	if (!m_isActive)
		return;

	switch (m_eUIState)
	{
	case eUIState::Disabled:
	{
		if(m_pTexture)
			m_pTexture->SetUIState(eUIState::Disabled);
		if(m_pText)
			m_pText->SetUIState(eUIState::Disabled);
	}
	break;
	case eUIState::Active:
	{
		if (m_pTexture)
			m_pTexture->SetUIState(eUIState::Active);
		if (m_pText)
			m_pText->SetUIState(eUIState::Active);
	}
	break;
	case eUIState::Hover:
	{
		if (m_pTexture)
			m_pTexture->SetUIState(eUIState::Hover);
		if (m_pText)
			m_pText->SetUIState(eUIState::Hover);
	}
	break;
	}

	for (const auto c : m_listUIchildren)
	{
		c->Update();
	}
}

void CUIButton::Render()
{
	if (!m_isActive)
		return;

	for (const auto c : m_listUIchildren)
	{
		c->Render();
	}
	if (m_pTexture)
		m_pTexture->Render();
	if (m_pText)
		m_pText->Render();
}

void CUIButton::Add(CUI * component)
{
	this->m_listUIchildren.push_back(component);
	component->SetParent(this);
}

void CUIButton::Remove(CUI * component)
{
	m_listUIchildren.remove(component);
	component->SetParent(nullptr);
}


