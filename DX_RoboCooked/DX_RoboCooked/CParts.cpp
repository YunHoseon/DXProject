#include "stdafx.h"
#include "CParts.h"

#include "CBoxCollision.h"
#include "CSphereCollision.h"
#include "CCharacter.h"

CParts::CParts(string sPartsID, string sFormula, float fMass)
	: m_vGrabPosition(nullptr), m_isMoveParts(false),
	  m_eLevel(eCombinatorPartsLevel::ONE), m_vCombinatorPosition(0, 0, 0) , m_pPartsCombinator(NULL),
	m_sPartsID(sPartsID), m_sFormula(sFormula)
{
	m_fMass = fMass;
	switch (m_sPartsID[0])
	{
	case 'A': m_eLevel = eCombinatorPartsLevel::ONE; break;
	case 'B': m_eLevel = eCombinatorPartsLevel::TWO; break;
	case 'C': m_eLevel = eCombinatorPartsLevel::THREE; break;
	case 'D': m_eLevel = eCombinatorPartsLevel::FOUR; break;
	default: break;
	}
	SetRotationY(0);
}

CParts::CParts(CParts* pParts) :
	CParts(pParts->m_sPartsID, pParts->m_sFormula, pParts->m_fMass)
{
	m_cMesh = pParts->m_cMesh;
	// 콜리전 만드는 함수
	
	m_pCollision = new CBoxCollision(m_cMesh.GetMesh(), &m_matWorld);
	SetScale(pParts->m_vScale);
	if (m_pCollision)
		m_pCollision->Update();
}

CParts* CParts::Clone()
{
	return new CParts(this);
}

CParts::~CParts()
{
}

void CParts::Setup(D3DXVECTOR3& vScale)
{
	assert(m_cMesh.GetMesh());
	m_pCollision = new CBoxCollision(m_cMesh.GetMesh(), &m_matWorld);
	SetScale(vScale);
	if (m_pCollision)
		m_pCollision->Update();
}

void CParts::Update()
{
	if (m_isMoveParts)
		MoveParts();
	
	else if (m_vGrabPosition)
	{
		m_vPosition = *m_vGrabPosition;
		m_pCollision->SetActive(false);
	}
	else
	{
		if (m_pCollision->GetActive())
		{
			m_vVelocity += m_vAcceleration;
			m_vPosition += m_vVelocity;
		}
		SetForce();
	}
	
	D3DXMatrixTranslation(&m_matT, m_vPosition.x , m_vPosition.y, m_vPosition.z);
	m_matWorld = m_matS * m_matR * m_matT;

	if (m_pCollision)
		m_pCollision->Update();
}

void CParts::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_cMesh.Render();
	

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
}


void CParts::Interact(CCharacter* pCharacter)
{
	SetGrabPosition(&pCharacter->GetGrabPartsPosition());
	pCharacter->SetParts(this);
	//pCharacter->SetPlayerState(ePlayerState::Grab);
}

void CParts::ThrowParts(D3DXVECTOR3 vForce)
{
	m_vGrabPosition = nullptr;
	m_pCollision->SetActive(true);
	AddForce(vForce);

	g_EventManager->CallEvent(eEvent::ThrowParts, NULL);
}

void CParts::PartsRotate()
{
	m_fRotY += D3DX_PI * 0.5f;
	if (m_fRotY >= D3DX_PI * 2)
		m_fRotY = 0;
	
	SetRotationY(m_fRotY);

	g_EventManager->CallEvent(eEvent::SpinParts, NULL);
}

void CParts::MoveParts()
{
	m_vVelocity = g_vZero;
	SetForce();
	D3DXVECTOR3 vDirection = m_vCombinatorPosition - m_vPosition;
	float fLength = D3DXVec3Length(&vDirection);
	
	if(fLength < 0.1f && fLength > -0.1f)
	{
		m_pPartsCombinator->InsertParts(this);
		m_pPartsCombinator = NULL;
		m_vPosition = D3DXVECTOR3(0, -100, 0);
		m_isMoveParts = false;
		return;
	}
	D3DXVec3Normalize(&vDirection, &vDirection);
	m_vPosition += vDirection * 0.05f * TimeRevision;
}

void CParts::SetGrabPosition(D3DXVECTOR3* vPosition)
{
	m_vGrabPosition = vPosition;
	if (vPosition)
		m_vVelocity = g_vZero;
}

void CParts::AddForce(const D3DXVECTOR3& vForce)
{
	if (m_isMoveParts || m_vGrabPosition)
		return;
	CActor::AddForce(vForce);

}

void CParts::AddAcceleration(const D3DXVECTOR3& vAccel)
{
	if (m_isMoveParts || m_vGrabPosition)
		return;
	CActor::AddAcceleration(vAccel);
}


