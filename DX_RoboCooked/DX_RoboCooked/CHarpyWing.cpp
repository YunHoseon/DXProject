#include "stdafx.h"
#include "CHarpyWing.h"

CHarpyWing::CHarpyWing() :
	m_matWorld(g_matIdentity),
	m_matLocal(g_matIdentity),
	m_fRotY(0),
	m_fElapseTime(0)
{
}

CHarpyWing::~CHarpyWing()
{
}

void CHarpyWing::Render(LPDIRECT3DTEXTURE9 pBlendTexture)
{
	if(m_fElapseTime < 4.0f)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
		CStaticMesh::Render(pBlendTexture);
	}
}
