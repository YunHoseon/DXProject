#include "stdafx.h"
#include "CWhiteboard.h"
#include "ICollisionArea.h"
#include "CUIWhiteboard.h"
#include "CCharacter.h"



CWhiteboard::CWhiteboard(D3DXVECTOR3 vPos)
	: m_pSMesh(nullptr)
	, m_pCharacter(nullptr)
	, m_pUIWhiteboard(nullptr)
{
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Whiteboard");
	m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);

	m_pUIWhiteboard = new CUIWhiteboard(D3DXVECTOR2(530,160));

	SetScale(0.025f, 0.025f, 0.025f);
	SetRotationY(D3DXToRadian(0));
	SetPosition(vPos);

	float y = vPos.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPos.y - m_pCollision->GetCenter().y);
	SetPosition(vPos.x, y, vPos.z);

	if (m_pCollision)
		m_pCollision->Update();
}


CWhiteboard::~CWhiteboard()
{
}

void CWhiteboard::Update()
{
}

void CWhiteboard::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSMesh->Render();
	m_pUIWhiteboard->Render();

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT	m_pCollision->Render();
}

void CWhiteboard::Interact(CCharacter* pCharacter)
{	
	g_EventManager->Attach(eEvent::KeyRelease, this);
	m_pUIWhiteboard->SetActive(true);

	if (m_pCharacter == nullptr)
	{
		m_pCharacter = pCharacter;
		g_EventManager->Detach(eEvent::KeyRelease, m_pCharacter);
	}
}

bool CWhiteboard::OnEvent(eEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case eEvent::KeyRelease:
		return ClosePopup(_value);
	}
	return true;
}

bool CWhiteboard::ClosePopup(void* _value)
{
	WPARAM* data = static_cast<WPARAM*>(_value);

	if (m_pCharacter && *data == m_pCharacter->GetInputKey().interactableKey1)
	{
		m_pUIWhiteboard->SetActive(false);
		g_EventManager->Attach(eEvent::KeyRelease, m_pCharacter);
		m_pCharacter->ReleaseKey(data);
		m_pCharacter = nullptr;
		return false;
	}
	return true;
}

void CWhiteboard::SetFormula(vector<CBlueprint*>& vBp)
{
	int a = vBp.size();
	 m_pUIWhiteboard->SetFormula(vBp); 
}

