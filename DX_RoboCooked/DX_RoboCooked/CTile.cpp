#include "stdafx.h"
#include "CTile.h"
#include "ICollisionArea.h"


CTile::CTile():
	m_pSMesh(nullptr)
{
	m_fMass = 9999.f;
	SetRotationY(0);
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