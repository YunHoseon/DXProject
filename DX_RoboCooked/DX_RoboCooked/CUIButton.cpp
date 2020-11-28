#include "stdafx.h"
#include "CUIButton.h"
#include "CUITexture.h"
#include "CUIText.h"



CUIButton::CUIButton():m_pTexture(nullptr),m_pText(nullptr)
{

}


CUIButton::~CUIButton()
{
}


//void CUIButton::Setup()
//{
//	/*g_EventManager->Attach(eEvent::MouseClick, this);
//
//	D3DXVECTOR2 vec2;
//
//	vec2 = D3DXVECTOR2(500,100);
//	CUI* Texture = new CUITexture("data/UI/panel-info.png", NULL, NULL, vec2);
//	vec2 = D3DXVECTOR2 (700, 250);
//	CUI* Text = new CUIText("UI_TEST",vec2);
//	
//	Add(Texture);
//	Add(Text);
//
//
//	CUI* OKButton = new CUIButton;
//	Add(OKButton);
//
//	vec2 = D3DXVECTOR2(630, 400);
//	Texture = new CUITexture("data/UI/btn-med-over.png", NULL, NULL, vec2);
//	vec2 = D3DXVECTOR2(750, 420);
//	Text = new CUIText("OK", vec2);
//
//	OKButton->Add(Texture);
//	OKButton->Add(Text);
//
//	CUI* NoButton = new CUIButton;
//	Add(NoButton);
//
//	vec2 = D3DXVECTOR2(630, 500);
//	Texture = new CUITexture("data/UI/btn-med-over.png", NULL, NULL, vec2);
//	vec2 = D3DXVECTOR2(750, 520);
//	Text = new CUIText("NO", vec2);
//
//	NoButton->Add(Texture);
//	NoButton->Add(Text);
//*/
//
//}
//
//void CUIButton::Update()
//{
//	/*for (const auto c : m_listUIchildren)
//	{
//		c->Update();
//	}*/
//}
//
//void CUIButton::Render()
//{
//	/*for (const auto c : m_listUIchildren)
//	{
//		c->Render();
//	}*/
//}

void CUIButton::Update()
{
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

//void CUIButton::OnEvent(eEvent eEvent, void * _value)
//{
//	/*ST_MouseEvent *data = static_cast<ST_MouseEvent*>(_value);
//
//	for (auto it : m_listUIchildren)
//	{
//		cout << it->CheckIn(data->pt) << endl;
//	}*/
//}

//bool CUIButton::CheckIn(POINT pt)
//{
//	for (auto it : m_listUIchildren)
//	{
//		cout << it->CheckIn(pt) << endl;
//	}
//	return false;
//}

