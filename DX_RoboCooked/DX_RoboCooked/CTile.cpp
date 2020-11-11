#include "stdafx.h"
#include "CTile.h"



CTile::CTile()
{
}


CTile::~CTile()
{
}

void CTile::AddEvent(EEvent eEvent)
{

}


void CTile::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	
	g_pD3DDevice->SetTexture(0, m_PlaneTexture);
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0],
	//	sizeof(ST_PNT_VERTEX));
	
	g_pD3DDevice->SetTexture(0, 0);
}

