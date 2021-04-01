﻿#include "stdafx.h"
#include "CCactus.h"
#include "ICollisionArea.h"

CCactus::CCactus(): m_pSMesh(nullptr)
{
	m_fFriction = 0.1;
	m_fRepulsivePower = 0.5f;
	m_fMass = 9999.f;

	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Cactus");
	m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);
	SetScale(0.01f, 0.01f, 0.01f);
}

CCactus::CCactus(D3DXVECTOR3 vPos) : CCactus()
{
	SetPosition(vPos);
}

CCactus::~CCactus()
{
}

void CCactus::Update()
{
}

void CCactus::Render()
{
	//g_pRenderShadowManager->GetApplyShadowShader()->SetMatrix("gWorldMatrix", &m_matWorld);
	//g_pRenderShadowManager->GetApplyShadowShader()->SetBool("gIsSkinned", false);
	//UINT numPasses = 0;
	//g_pRenderShadowManager->GetApplyShadowShader()->Begin(&numPasses, NULL);

	//for (UINT i = 0; i < numPasses; ++i)
	//{
	//	g_pRenderShadowManager->GetApplyShadowShader()->BeginPass(i);
	//	{
	//		if (m_pSMesh)
	//		{
	//			m_pSMesh->RenderWidthShadow();
	//		}
	//	}
	//	g_pRenderShadowManager->GetApplyShadowShader()->EndPass();
	//}

	//g_pRenderShadowManager->GetApplyShadowShader()->End();
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSMesh->Render();

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT	m_pCollision->Render();
}

void CCactus::SetScale(float x, float y, float z)
{
	m_vScale = D3DXVECTOR3(x, y, z);
	D3DXMatrixScaling(&m_matS, x, y, z);
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->SetScale(x * 0.5, y * 0.5, z * 0.5);
}

void CCactus::SetScale(const D3DXVECTOR3& vScale)
{
	m_vScale = vScale;
	D3DXMatrixScaling(&m_matS, vScale.x, vScale.y, vScale.z);
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->SetScale(vScale.x * 0.5, vScale.y * 0.5, vScale.z * 0.5);
}

void CCactus::CreateShadowMap()
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
