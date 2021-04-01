#include "stdafx.h"
#include "CTornado.h"
#include "CSphereCollision.h"

CTornado::CTornado(D3DXVECTOR3 pos): m_pSMesh(nullptr)
{
	SetPosition(pos);
	SetScale(0.1, 0.1, 0.1);
	m_pCollision = new CSphereCollision(D3DXVECTOR3(0, 0, 0), 2.0f, &m_matWorld);
	m_pCollision->Update();
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Tornado");
}


CTornado::~CTornado()
{
}

void CTornado::Update()
{
	SetRotationY(m_fRotY += g_pTimeManager->GetElapsedTime() * D3DX_PI * 2);
}

void CTornado::Render()
{
	if(m_pSMesh)
	{
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pSMesh->Render();
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		
	}
	
	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
}
