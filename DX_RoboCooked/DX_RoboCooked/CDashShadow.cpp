#include "stdafx.h"
#include "CDashShadow.h"

CDashShadow::CDashShadow():
	m_fAnimScale(0.001f),
	m_fDuration(0.5f),
	m_fElapsedTime(m_fDuration + 0.1f),
	m_pShader(nullptr),
	m_pTexture(nullptr),
	m_pSMesh(nullptr)
{
	m_pShader = g_pShaderManager->GetShader("data/shader/nebula.fx");
	m_pTexture = g_pTextureManager->GetTexture("data/texture/NebX.dds");

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &m_matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);
	D3DXMatrixInverse(&m_matViewI, 0, &m_matView);
	D3DXMatrixTranspose(&m_matViewIT, &m_matViewI);
	m_matWorld = g_matIdentity;
	m_matWorldIT = g_matIdentity;
	D3DXMatrixMultiply(&m_matWV, &m_matWorld, &m_matView);
	D3DXMatrixMultiply(&m_matWVP, &m_matWV, &m_matProj);

	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Character");

	//m_NebXf = g_matIdentity;
	//m_NebXf._13 = 20.f;
}

CDashShadow::~CDashShadow()
{
}

void CDashShadow::Update()
{
	if (m_fElapsedTime > m_fDuration)
		return;

	m_fElapsedTime += g_pTimeManager->GetElapsedTime();
	m_fAnimScale += g_pTimeManager->GetElapsedTime() * 2;
}

void CDashShadow::SetAnimation(D3DXMATRIXA16* pmatWorld)
{
	m_matWorld = *pmatWorld;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &m_matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);
	D3DXMatrixInverse(&m_matViewI, 0, &m_matView);
	D3DXMatrixTranspose(&m_matViewIT, &m_matViewI);
	D3DXMatrixMultiply(&m_matWV, &m_matWorld, &m_matView);
	D3DXMatrixMultiply(&m_matWVP, &m_matWV, &m_matProj);
	D3DXMatrixInverse(&m_matWorldIT, 0,  &m_matWorld);
	D3DXMatrixTranspose(&m_matWorldIT, &m_matWorldIT);
	D3DXMatrixMultiply(&m_matWV, &m_matWorld, &m_matView);
	D3DXMatrixMultiply(&m_matWVP, &m_matWV, &m_matProj);

	m_fAnimScale = 0.001f;
	m_fElapsedTime = 0.f;
}

void CDashShadow::Render()
{
	if (m_fElapsedTime > m_fDuration)
		return;
	m_pShader->SetTexture("nebTexture_Tex", m_pTexture);
	m_pShader->SetMatrix("WorldITXf", &m_matWorldIT);
	m_pShader->SetMatrix("WvpXf", &m_matWVP);
	m_pShader->SetMatrix("WorldXf", &m_matWorld);
	m_pShader->SetMatrix("ViewITXf", &m_matViewIT);
	m_pShader->SetMatrix("ViewIXf", &m_matViewI);
	m_pShader->SetMatrix("WorldViewXf", &m_matWV);
	m_pShader->SetFloat("Scale", m_fAnimScale);
	
	UINT	numPasses = 0;
	int nSubsetSize = 0;
	nSubsetSize = m_pSMesh->GetVecMaterial().size();
	m_pShader->Begin(&numPasses, NULL);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			m_pShader->BeginPass(0);
			//for (int j = 0; j < nSubsetSize; ++j)
			{
				m_pSMesh->Render();
			}
			m_pShader->EndPass();
		}
	}
	m_pShader->End();
}
