#include "stdafx.h"
#include "CPartVending.h"
#include "CBoxCollision.h"
#include "CCharacter.h"
#include "CParts.h"
#include "CGameScene.h"

CPartVending::CPartVending(COutlet *outlet, IInteractCenter *pInteractCenter, string sPartsID) : m_pOutlet(outlet),
																								 m_ePartVendingState(ePartVendingState::Usable),
																								 m_PartVendingTexture(nullptr)
{
	m_pInteractCenter = pInteractCenter;
	m_sID = sPartsID;
	m_fMass = 9999.f;
	m_fFriction = 0.2f;
}

CPartVending::~CPartVending()
{
	SafeRelease(m_PartVendingTexture);
}

void CPartVending::Setup(float fAngle, D3DXVECTOR3 vPosition)
{
	SetRotationY(fAngle);
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Vending");
	m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);

	SetScale(0.01f, 0.01f, 0.01f);
	SetPosition(vPosition);

	float y = vPosition.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPosition.y - m_pCollision->GetCenter().y);
	SetPosition(vPosition.x, y, vPosition.z);

	if (m_pCollision)
		m_pCollision->Update();
}

void CPartVending::Update()
{
	if (m_pOutlet->GetState() == eOutletState::None)
		m_ePartVendingState = ePartVendingState::Usable;
}

void CPartVending::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSMesh->Render();

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
}

void CPartVending::OnEvent(eEvent eEvent, void *_value)
{
}

CParts *CPartVending::Make()
{
	CParts *parts = g_pPartsManager->CreateParts(m_sID);
	return parts;
}

void CPartVending::Interact(CCharacter *pCharacter)
{
	if (m_ePartVendingState == ePartVendingState::Usable && m_pOutlet->GetState() == eOutletState::None && pCharacter->GetPlayerState() == ePlayerState::None)
	{
		CParts *parts = Make();
		parts->SetPosition(m_pOutlet->GetPosition() + D3DXVECTOR3(0, 1.0f, 0));
		m_pInteractCenter->AddParts(parts);

		m_ePartVendingState = ePartVendingState::Unusable;
		m_pOutlet->AcceptPartsFromVending(parts);
		//m_pInteractCenter->SendPartsToOutlet(parts, m_pOutlet);
		g_EventManager->CallEvent(eEvent::VendingUse, NULL);
	}
}
