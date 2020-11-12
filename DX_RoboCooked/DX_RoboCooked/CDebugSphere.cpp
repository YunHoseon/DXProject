#include "stdafx.h"
#include "CDebugSphere.h"


CDebugSphere::CDebugSphere()
{
}


CDebugSphere::~CDebugSphere()
{
}

void CDebugSphere::Setup()
{
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}

void CDebugSphere::Update()
{
	if (GetKeyState('A') & 0X8000)
	{
		m_fRotY -= 0.1f;
	}
	if (GetKeyState('D') & 0X8000)
	{
		m_fRotY += 0.1f;
	}

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, -1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	D3DXVECTOR3 vPosition = m_vPosition;

	if (GetKeyState('W') & 0X8000)
	{
		vPosition = m_vPosition + (m_vDirection * 0.1f);
	}
	if (GetKeyState('S') & 0X8000)
	{
		vPosition = m_vPosition - (m_vDirection * 0.1f);
	}
}

void CDebugSphere::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	matWorld = matS * matR;

	D3DXMatrixIdentity(&matWorld);
	matWorld._41 = m_sphere.vCenter.x;
	matWorld._42 = m_sphere.vCenter.y;
	matWorld._43 = m_sphere.vCenter.z;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlSphere);
	m_pMeshSphere->DrawSubset(0);
}
