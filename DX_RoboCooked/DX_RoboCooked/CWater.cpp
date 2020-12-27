#include "stdafx.h"
#include "CWater.h"
#include "CBoxCollision.h"

CWater::CWater(D3DXVECTOR3 vPosition)
{
	m_eTileType = eTileType::Water;

	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Water");
	m_pCollision = new CBoxCollision(g_vZero, D3DXVECTOR3(100, 100, 100), &m_matWorld);

	SetScale(0.01f, 0.01f, 0.01f);
	SetPosition(vPosition);

	float y = vPosition.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPosition.y - m_pCollision->GetCenter().y);
	SetPosition(vPosition.x, y, vPosition.z);
	m_fFriction = 0.0;
	m_fRepulsivePower = 0.f;
	m_fFlexibility = .5f;
	m_fMass = 0.01f;
	if (m_pCollision)
		m_pCollision->Update();
}


CWater::~CWater()
{
}

void CWater::Render()
{
	LPD3DXEFFECT pAnimationShader = g_pShaderManager->GetShader("data/shader/Water.fx");

	if (pAnimationShader)
	{
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		D3DXMATRIXA16 matView, matProjection, matWVP;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

		matWVP = m_matWorld * matView * matProjection;
		pAnimationShader->SetMatrix("gWorldViewProjectionMatrix", &matWVP);

		ULONGLONG tick = GetTickCount64();
		pAnimationShader->SetFloat("gTime", g_pTimeManager->GetLastUpdateTime());
		pAnimationShader->SetFloat("gWaveHeight", 3);
		pAnimationShader->SetFloat("Speed", 2);
		pAnimationShader->SetFloat("gWaveFrequency", 10);
		pAnimationShader->SetFloat("gUVSpeed", 0.25f);

		//float fBlend = m_isCreatedNow ? 0.4f : 1.0f;
		pAnimationShader->SetFloat("albedoAlpha", 1);

		UINT numPasses = 0;
		pAnimationShader->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; ++i)
			{
				pAnimationShader->BeginPass(i);
				{
					g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
					g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
					m_pSMesh->Render();
				}
				pAnimationShader->EndPass();
			}
			pAnimationShader->End();
		}
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
	// << :
	else if (m_pSMesh)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		m_pSMesh->Render();
	}
}

void CWater::Update()
{
}

bool CWater::Collide(CActor* target, D3DXVECTOR3* pNormal)
{
	bool b = CActor::Collide(target, pNormal);
	if(b)
		target->GetCollision()->SetIsCollide(false);
	return b;
}
