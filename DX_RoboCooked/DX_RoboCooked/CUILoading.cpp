#include "stdafx.h"
#include "CUILoading.h"
#include "CUITexture.h"
#include "CUILoadingScreen.h"
#include "CUILoadingMessageLoad.h"
#include "CUIloadingMessageComplete.h"
#include "IInteractCenter.h"

CUILoading::CUILoading(IInteractCenter*	pInteractCenter)
	: m_isLoading(true)
{
	m_vPosition = D3DXVECTOR2(0,0);
	m_isActive = true;
	m_pInteractCenter = pInteractCenter;
	Setup();

	//g_EventManager->Attach(eEvent::KeyPress, this);
	g_EventManager->Attach(eEvent::KeyRelease, this);
	g_EventManager->Attach(eEvent::LoadingEnd, this);
}


CUILoading::~CUILoading()
{

}

void CUILoading::Setup()
{
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);
	
	m_pBoard = new CUILoadingScreen();
	AddChild(m_pBoard);

	m_pLoadingMessage = new CUILoadingMessageLoad(D3DXVECTOR2(vp.Width / 2 - 200, vp.Height / 2 + 300));
	m_pBoard->AddChild(m_pLoadingMessage);

	m_pCompleteMessage = new CUIloadingMessageComplete(D3DXVECTOR2(vp.Width / 2 - 375, vp.Height / 2 + 300));
	m_pBoard->AddChild(m_pCompleteMessage);
	m_pCompleteMessage->SetIsActive(false);
}

bool CUILoading::OnEvent(eEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case eEvent::KeyRelease:
		return KeyReleaseEvent(_value);
	case eEvent::LoadingEnd:
		return LoadingEndEvent();
	}
	return true;
}

bool CUILoading::KeyReleaseEvent(void* _value)
{
	if (m_isLoading)
		return true;
	SetIsActive(false);
	if (m_pInteractCenter->GetStop())
		m_pInteractCenter->ToggleStop();
	return false;
}

bool CUILoading::LoadingEndEvent()
{
	m_isLoading = false;
	m_pCompleteMessage->SetIsActive(true);
	m_pLoadingMessage->SetIsActive(false);
	return false;
}
