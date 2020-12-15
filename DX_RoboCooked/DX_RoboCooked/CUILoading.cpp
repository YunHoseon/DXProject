#include "stdafx.h"
#include "CUILoading.h"
#include "CUITexture.h"

CUILoading::CUILoading()
	: m_isLoading(false)
{
	m_isActive = true;
	g_EventManager->Attach(eEvent::KeyPress, this);
	g_EventManager->Attach(eEvent::KeyRelease, this);
	g_EventManager->Attach(eEvent::MouseClick, this);
	g_EventManager->Attach(eEvent::MouseRelease, this);
}


CUILoading::~CUILoading()
{
}

void CUILoading::Setup()
{
	m_pTexture = new CUITexture("data/UI/roadingScreen.png", "data/UI/roadingScreen.png", "data/UI/roadingScreen.png", m_vPosition);

	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);
	m_vPosition = D3DXVECTOR2(vp.Width / 2 - m_pTexture->GetActiveTextureWidth()
							, vp.Height / 2 - m_pTexture->GetActiveTextureHeight());
}

void CUILoading::OnEvent(eEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case eEvent::MouseClick:
		ClickEvent(_value);
		break;
	case eEvent::KeyPress:
		KeyPressEvent(_value);
		break;
	case eEvent::KeyRelease:
		KeyReleaseEvent(_value);
		break;
	case eEvent::MouseRelease:
		MouseReleaseEvent(_value);
		break;
	}
}

void CUILoading::ClickEvent(void* _value)
{
	ST_KeyInputEvent* data = static_cast<ST_KeyInputEvent*>(_value);
}

void CUILoading::MouseReleaseEvent(void* _value)
{
	ST_KeyInputEvent* data = static_cast<ST_KeyInputEvent*>(_value);

	if (!m_isLoading)
	{

	}
}

void CUILoading::KeyPressEvent(void* _value)
{
	ST_KeyInputEvent* data = static_cast<ST_KeyInputEvent*>(_value);
}

void CUILoading::KeyReleaseEvent(void* _value)
{
	ST_KeyInputEvent* data = static_cast<ST_KeyInputEvent*>(_value);

	if (!m_isLoading)
	{

	}
}
