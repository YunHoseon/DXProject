#include "stdafx.h"
#include "CCombinatorButton.h"
#include "CBoxCollision.h"
#include "CPartCombinator.h"


CCombinatorButton::CCombinatorButton(CPartCombinator* pPartCombinator)
			:m_pPartCombinator(pPartCombinator)
{
	m_fMass = 9999.f;
}


CCombinatorButton::~CCombinatorButton()
{
	SafeRelease(m_CombinatorBtnTexture);
}

void CCombinatorButton::OnEvent(eEvent eEvent, void * _value)
{
}

void CCombinatorButton::Interact(CCharacter * pCharacter)
{
	m_pPartCombinator->ReadytoCarryParts();
}

void CCombinatorButton::Update()
{
	 if (m_pCollision)
		 m_pCollision->Update();
}

void CCombinatorButton::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSMesh->Render();

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
}

void CCombinatorButton::Setup(float fAngle, D3DXVECTOR3 vPosition)
{
	SetRotationY(D3DXToRadian(fAngle));
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Switch1");
	m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);

	SetScale(0.01f, 0.01f, 0.01f);
	SetPosition(vPosition);

	float y = vPosition.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPosition.y - m_pCollision->GetCenter().y);
	SetPosition(vPosition.x, y, vPosition.z);

	if (m_pCollision)
		m_pCollision->Update();
}
