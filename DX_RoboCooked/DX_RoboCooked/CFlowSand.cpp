#include "stdafx.h"
#include "CFlowSand.h"
#include "CBoxCollision.h"

CFlowSand::CFlowSand(D3DXVECTOR3 vPosition):
	m_pUpperMesh(nullptr)
{
	m_eTileType = eTileType::FlowSand;
	
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("FlowSand");
	//m_pUpperMesh = g_pStaticMeshManager->GetStaticMesh("FlowSand_Upper");
	m_pCollision = new CBoxCollision(g_vZero, D3DXVECTOR3(0.1, 0.1, 0.1), &m_matWorld);
	
	SetScale(10.f, 10.f, 10.f);
	SetPosition(vPosition);

	float y = vPosition.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPosition.y - m_pCollision->GetCenter().y);
	SetPosition(vPosition.x, y, vPosition.z);

	if (m_pCollision)
		m_pCollision->Update();

	m_fFriction = 0.7f;
}


CFlowSand::~CFlowSand()
{
}

void CFlowSand::Render()
{
	CTile::Render();
	if(m_pUpperMesh)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld_Upper);
		m_pUpperMesh->Render();
	}
}

void CFlowSand::SetPosition(D3DXVECTOR3 vPosition)
{
	CActor::SetPosition(vPosition);
	D3DXMATRIXA16 tempT = m_matT;
	tempT._42 += .5f;
	m_matWorld_Upper = m_matS * m_matR * tempT;
}

void CFlowSand::SetPosition(float x, float y, float z)
{
	CActor::SetPosition(x, y, z);
	D3DXMATRIXA16 tempT = m_matT;
	tempT._42 += .5f;
	m_matWorld_Upper = m_matS * m_matR * tempT;
}
