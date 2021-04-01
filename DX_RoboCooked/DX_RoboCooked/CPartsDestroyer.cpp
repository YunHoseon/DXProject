﻿#include "stdafx.h"
#include "CPartsDestroyer.h"

CPartsDestroyer::CPartsDestroyer():
	//m_pMesh(nullptr),
	//m_stMtl({}),
	m_pTexture(nullptr),
	m_fDuration(0),
	m_fElapseTime(0),
	m_isRenderable(false),
	m_pSMesh(nullptr)
{
	//D3DXCreateSphere(g_pD3DDevice, 1, 30, 30, &m_pMesh, nullptr);
	//m_pTexture = g_pTextureManager->GetTexture("data/texture/medusa_poison.png");
	//m_stMtl.Ambient = D3DXCOLOR(0.43f, 0.67f, 0.27f, 1.0f);
	//m_stMtl.Diffuse = D3DXCOLOR(0.43f, 0.67f, 0.27f, 1.0f);
	//m_stMtl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Medusa_MagicCircle");
}

CPartsDestroyer::~CPartsDestroyer()
{
	//SafeRelease(m_pMesh);
}

bool CPartsDestroyer::OnEvent(eEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case eEvent::Tick:
	{
		ST_TickEvent* data = (ST_TickEvent*)_value;
		m_fElapseTime  = m_fElapseTime + data->fElapsedTime;
		//_DEBUG_COMMENT cout << m_fElapseTime << endl;
		if(m_fElapseTime >= m_fDuration)
		{
			m_isRenderable = false;
			m_fElapseTime = 0;
			if (m_cRain.GetActive())
				m_cRain.InvertActive();
			return false;
		}
	}
		break;
	default: ;
	}
	return true;
}

void CPartsDestroyer::Render()
{
	if(m_isRenderable)
	{
		/*if(m_pMesh)
		{
			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
			g_pD3DDevice->SetTexture(0, m_pTexture);
			g_pD3DDevice->SetMaterial(&m_stMtl);
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
			m_pMesh->DrawSubset(0);
		}*/
		if (m_pSMesh)
		{
			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
			m_pSMesh->Render();
		}
		m_cRain.Render();
	}
}

void CPartsDestroyer::SetActive(D3DXVECTOR3& vPos, float fDuration)
{
	D3DXMATRIXA16 matS, matR, matT;

	D3DXMatrixRotationX(&matR, 0);
	D3DXMatrixTranslation(&matT, vPos.x, vPos.y, vPos.z);
	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	m_matWorld = matS * matR * matT;

	g_EventManager->Attach(eEvent::Tick, this);
	m_fDuration = fDuration;
	m_isRenderable = true;

	if (!m_cRain.GetActive())
		m_cRain.InvertActive();
}
