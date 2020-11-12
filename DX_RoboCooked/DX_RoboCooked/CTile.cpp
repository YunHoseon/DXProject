#include "stdafx.h"
#include "CTile.h"



CTile::CTile()
{
}


CTile::~CTile()
{
	SafeRelease(m_PlaneTexture);
	SafeRelease(m_pCubeTile);
}

void CTile::AddEvent(EEvent eEvent)
{
	g_EventManager->Attach(eEvent, this);
}


void CTile::OnEvent(EEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case EEvent::E_EventNONE:
		break;
	case EEvent::E_EventTile:
		//D3DXMatrixScaling(&m_matS, 1.0f, 2.0f, 1.0f);
		//D3DXMatrixTranslation(&m_matT, 1.0f, 2.0f, 1.0f);
	/*	D3DXQUATERNION q;
		D3DXVECTOR3 a(0, 1, 0);
		D3DXQuaternionRotationAxis(&q, &a, D3DX_PI/4.0f);
		D3DXMatrixRotationQuaternion(&m_matR, &q);*/
		break;
	}
}

void CTile::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	
	matWorld = m_matS * m_matR * m_matT;
	
	g_pD3DDevice->SetTexture(0, m_PlaneTexture);
	
	
	matWorld._41 += m_stCube.vCenter.x;
	matWorld._42 += m_stCube.vCenter.y;
	matWorld._43 += m_stCube.vCenter.z;
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	
	m_pCubeTile->DrawSubset(0);

	
	
	g_pD3DDevice->SetTexture(0, 0);
}

void CTile::Update()
{
}

