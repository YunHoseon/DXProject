#include "stdafx.h"
#include "COutlet.h"
#include "ICollisionArea.h"
#include "CBoxCollision.h"
#include "CParts.h"
#include "CGameScene.h"

COutlet::COutlet(IInteractCenter* pInteractCenter)
	:m_nPartsID(0)
	, m_pGeneratorSwitch(NULL)
{
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	m_pInteractCenter = pInteractCenter;
	D3DXMatrixIdentity(&m_matWorld);
}


COutlet::~COutlet()
{
}

void COutlet::Setup(float fAngle, D3DXVECTOR3 vPosition, int nPartsID)
{
	m_nPartsID = nPartsID;
	m_vPosition = vPosition;
	D3DXCreateBox(g_pD3DDevice, 0.8f, 0.8f, 0.8f, &m_pMeshCube, NULL);

	ZeroMemory(&m_stMtlCube, sizeof(D3DMATERIAL9));
	m_stMtlCube.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlCube.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlCube.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	D3DXMatrixRotationY(&m_matR, D3DXToRadian(fAngle));
	D3DXMatrixTranslation(&m_matT, vPosition.x, 0, vPosition.z);

	m_pCollision = new CBoxCollision(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f), &m_matWorld);
}

void COutlet::Update()
{
	if (m_pCollision)
		m_pCollision->Update();
}

void COutlet::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlCube);
	m_pMeshCube->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
}

void COutlet::OnEvent(EEvent eEvent, void* _value)
{
}

CParts* COutlet::Make()
{
	CParts* parts = new CParts(m_nID);
	parts->Setup();
	parts->SetPosition(m_vPosition + m_vDirection);
	m_pInteractCenter->AddParts(parts);
	return 0;
}
