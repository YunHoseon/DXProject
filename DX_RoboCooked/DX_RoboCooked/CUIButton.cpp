#include "stdafx.h"
#include "CUIButton.h"
#include "CUITexture.h"
#include "CUIText.h"



CUIButton::CUIButton()
	: m_pTexture(nullptr)
	, m_pText(nullptr)
	, m_isKeyDown(false)
	, m_isMouseDown(false)
{
	m_pInputKey[0] = InputManager->GetInputKey(0);
	m_pInputKey[1] = InputManager->GetInputKey(1);
}


CUIButton::~CUIButton()
{
	//for (CUI * p : m_listUIchildren)
	//{
	//	SafeDelete(p);
	//}
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



