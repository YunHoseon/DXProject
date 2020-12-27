#include "stdafx.h"
#include "CTipBoard.h"
#include "ICollisionArea.h"
#include "CCharacter.h"
#include "CUITipBoard.h"


CTipBoard::CTipBoard(D3DXVECTOR3 vPos, string sText)
	: m_pSMesh(nullptr)
	, m_pCharacter(nullptr)
	, m_pTipBoard(nullptr)
{
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Whiteboard");
	m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);

	m_pTipBoard = new CUITipBoard(D3DXVECTOR2(530, 160));
	m_pTipBoard->SetText(sText, 700, 450);

	SetScale(0.025f, 0.025f, 0.025f);
	SetRotationY(D3DXToRadian(0));
	SetPosition(vPos);

	float y = vPos.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPos.y - m_pCollision->GetCenter().y);
	SetPosition(vPos.x, y, vPos.z);

	if (m_pCollision)
		m_pCollision->Update();
}


CTipBoard::~CTipBoard()
{
}

void CTipBoard::Update()
{
}

void CTipBoard::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSMesh->Render();
	m_pTipBoard->Render();

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT	m_pCollision->Render();
}

void CTipBoard::Interact(CCharacter * pCharacter)
{
	g_EventManager->Attach(eEvent::KeyRelease, this);
	m_pTipBoard->SetActive(true);

	if (m_pCharacter == nullptr)
	{
		m_pCharacter = pCharacter;
		g_EventManager->Detach(eEvent::KeyRelease, m_pCharacter);
	}
}

bool CTipBoard::OnEvent(eEvent eEvent, void * _value)
{
	switch (eEvent)
	{
	case eEvent::KeyRelease:
		return ClosePopup(_value);
	}
	return true;
}

bool CTipBoard::ClosePopup(void * _value)
{
	WPARAM* data = static_cast<WPARAM*>(_value);

	if (m_pCharacter && *data == m_pCharacter->GetInputKey().interactableKey1)
	{
		m_pTipBoard->SetActive(false);
		g_EventManager->Attach(eEvent::KeyRelease, m_pCharacter);
		m_pCharacter->ReleaseKey(data);
		m_pCharacter = nullptr;
		return false;
	}
	return true;
}
