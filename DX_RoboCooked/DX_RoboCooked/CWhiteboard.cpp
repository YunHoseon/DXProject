#include "stdafx.h"
#include "CWhiteboard.h"
#include "ICollisionArea.h"
#include "CUIWhiteboard.h"

CWhiteboard::CWhiteboard(D3DXVECTOR3 vPos)
	:m_pSMesh(nullptr)
{
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Whiteboard");
	m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);
	m_pUIWhiteboard = new CUIWhiteboard();

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

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT	m_pCollision->Render();
}

void CWhiteboard::Interact(CCharacter * pCharacter)
{

}
