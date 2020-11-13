#include "stdafx.h"
#include "CParts.h"
#include "CBoxCollision.h"

CParts::CParts()
	:m_vPosition(3.0f, 0.0f, 2.0f)
{
	D3DXMatrixIdentity(&m_matWorld);

	g_EventManager->Attach(EEvent::E_PartsHold, this);
	g_EventManager->Attach(EEvent::E_PartsSpin, this);
	g_EventManager->Attach(EEvent::E_PartsPut, this);
	g_EventManager->Attach(EEvent::E_PartsThrow, this);
}


CParts::~CParts()
{
}

void CParts::Setup()
{
	m_pCollision = new CBoxCollision(m_vPosition, D3DXVECTOR3(0.4f, 0.4f, 0.4f), &m_matWorld);
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlParts, sizeof(D3DMATERIAL9));
	m_stMtlParts.Ambient = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	m_stMtlParts.Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	m_stMtlParts.Specular = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
}

void CParts::Update()
{
}

void CParts::Render()
{
	m_matWorld = m_matS * m_matR * m_matT;

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlParts);
	m_pMeshSphere->DrawSubset(0);
}

void CParts::OnEvent(EEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case EEvent::E_PartsHold:
		break;
	case EEvent::E_PartsSpin:
		break;
	case EEvent::E_PartsPut:
		break;
	case EEvent::E_PartsThrow:
		break;
	}
}
