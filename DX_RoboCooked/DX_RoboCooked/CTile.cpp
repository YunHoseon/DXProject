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

}


void CTile::Render()
{
	D3DXMATRIXA16 matWorld;
	matWorld = m_matS * m_matR * m_matT;
	
	g_pD3DDevice->SetTexture(0, m_PlaneTexture);
	
	
	matWorld._41 = m_stCube.vCenter.x;
	matWorld._42 = m_stCube.vCenter.y;
	matWorld._43 = m_stCube.vCenter.z;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	
	m_pCubeTile->DrawSubset(0);

	
	
	g_pD3DDevice->SetTexture(0, 0);
}

void CTile::Update()
{
}

