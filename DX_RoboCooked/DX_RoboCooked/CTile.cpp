#include "stdafx.h"
#include "CTile.h"
#include "ICollisionArea.h"


CTile::CTile():
	m_pSMesh(nullptr)
{
	m_fMass = 9999.f;
}


CTile::~CTile()
{
	//SafeRelease(m_PlaneTexture);
}

void CTile::AddEvent(eEvent eEvent)
{
	g_EventManager->Attach(eEvent, this);
}

void CTile::OnEvent(eEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case eEvent::TileMove:
		//D3DXMatrixScaling(&m_matS, 1.0f, 2.0f, 1.0f);
		break;
	}
}

void CTile::Render()
{
	//D3DXMATRIXA16 matWorld;
	//D3DXMatrixIdentity(&matWorld);
	//
	//matWorld = m_matS * m_matR * m_matT;
	//
	//g_pD3DDevice->SetTexture(0, m_PlaneTexture);
	//
	//
	//matWorld._41 += m_stCube.vCenter.x;
	//matWorld._42 += m_stCube.vCenter.y;
	//matWorld._43 += m_stCube.vCenter.z;
	//
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//m_pCubeTile->DrawSubset(0);

	//g_pD3DDevice->SetTexture(0, 0);

	if(m_pSMesh)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		m_pSMesh->Render();
	}
}

void CTile::Update()
{

}