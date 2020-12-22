#include "stdafx.h"
#include "CTile.h"
#include "ICollisionArea.h"


CTile::CTile():
	m_pSMesh(nullptr)
{
	m_fMass = 9999.f;
	SetRotationY(0);
	//m_pShader = LoadShader("data/Shader/SpecularMapping.fx");
	//m_pDiffuseMap = g_pTextureManager->GetTexture("data/model/tile/test.png");
	//m_pSpecularMap = g_pTextureManager->GetTexture("data/model/tile/test.png");
}


CTile::~CTile()
{
	//SafeRelease(m_PlaneTexture);
}

void CTile::AddEvent(eEvent eEvent)
{
	g_EventManager->Attach(eEvent, this);
}

bool CTile::OnEvent(eEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case eEvent::TileMove:
		//D3DXMatrixScaling(&m_matS, 1.0f, 2.0f, 1.0f);
		break;
	}
	return true;
}

void CTile::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	/*if (m_pSMesh && m_pShader)
	{
		D3DXMATRIXA16	matView, matProj;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

		m_pShader->SetMatrix("gWorldMatrix", &m_matWorld);
		m_pShader->SetMatrix("gViewMatrix", &matView);
		m_pShader->SetMatrix("gProjectionMatrix", &matProj);
		D3DXVECTOR4 camPos = D3DXVECTOR4(0, 0, -200, 1.0f);
		m_pShader->SetVector("gWorldCameraPosition", &camPos);

		D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);
		m_pShader->SetValue("gColor", &color, sizeof(D3DXCOLOR));

		m_pShader->SetVector("gLightColor", &D3DXVECTOR4(0.7f, 0.7f, 1.0f, 1.0f));
		m_pShader->SetTexture("DiffuseMap_Tex", m_pDiffuseMap);
		m_pShader->SetTexture("SpecularMap_Tex", m_pSpecularMap);

		UINT numPasses = 0;
		m_pShader->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; i++)
			{
				m_pShader->BeginPass(i);
				if (m_pSMesh)
					m_pSMesh->Render();
				m_pShader->EndPass();
			}
		}
		m_pShader->End();
	}
	else*/
	{
		if (m_pSMesh)
			m_pSMesh->Render();
	}
}

void CTile::Update()
{

}