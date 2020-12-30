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

void CTile::CreateShadowMap()
{
	g_pRenderShadowManager->GetCreateShadowShader()->SetMatrix("gWorldMatrix", &m_matWorld);
	UINT numPasses = 0;
	g_pRenderShadowManager->GetCreateShadowShader()->Begin(&numPasses, NULL);

	for (UINT i = 0; i < numPasses; ++i)
	{
		g_pRenderShadowManager->GetCreateShadowShader()->BeginPass(i);
		{
			m_pSMesh->CreateShadowMap();
		}
		g_pRenderShadowManager->GetCreateShadowShader()->EndPass();
	}

	g_pRenderShadowManager->GetCreateShadowShader()->End();
}

void CTile::Render()
{
	g_pRenderShadowManager->GetApplyShadowShader()->SetMatrix("gWorldMatrix", &m_matWorld);
	g_pRenderShadowManager->GetApplyShadowShader()->SetBool("gIsSkinned", false);
	UINT numPasses = 0;
	g_pRenderShadowManager->GetApplyShadowShader()->Begin(&numPasses, NULL);
	
	for (UINT i = 0; i < numPasses; ++i)
	{
		g_pRenderShadowManager->GetApplyShadowShader()->BeginPass(i);
		{
			if (m_pSMesh)
			{
				m_pSMesh->RenderWidthShadow();
			}
		}
		g_pRenderShadowManager->GetApplyShadowShader()->EndPass();
	}
	
	g_pRenderShadowManager->GetApplyShadowShader()->End();
}

void CTile::Update()
{

}