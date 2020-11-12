#include "stdafx.h"
#include "CTile.h"



CTile::CTile()
{
}


CTile::~CTile()
{
	SafeRelease(m_PlaneTexture);
}

void CTile::AddEvent(EEvent eEvent)
{

}


void CTile::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	
	g_pD3DDevice->SetTexture(0, m_PlaneTexture);
	
	
	//g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0],
	//	sizeof(ST_PNT_VERTEX));
	matWorld._41 = m_stCube.vCenter.x;
	matWorld._42 = m_stCube.vCenter.y;
	matWorld._43 = m_stCube.vCenter.z;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	
	m_pCubeTile->DrawSubset(0);

	
	
	g_pD3DDevice->SetTexture(0, 0);
}

