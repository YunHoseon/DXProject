#include "stdafx.h"
#include "CParts.h"
#include "CSphereCollision.h"

CParts::CParts()
	:m_vPosition(3.0f, 0.0f, 2.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
	m_sphere.vCenter = m_vPosition;
	m_sphere.fRaidus = 0.3f;

	g_EventManager->Attach(EEvent::E_PartsHold, this);
	g_EventManager->Attach(EEvent::E_PartsSpin, this);
	g_EventManager->Attach(EEvent::E_PartsPut, this);
	g_EventManager->Attach(EEvent::E_PartsThrow, this);
	std::cout << "ID°¡ ¾ø´Â ÆÄÃ÷ÀÔ´Ï´Ù." << std::endl;
}

CParts::CParts(int nPartsID)
	:m_vPosition(3.0f, 0.0f, 2.0f)
{
	m_nPartsID = nPartsID;
	D3DXMatrixIdentity(&m_matWorld);
	m_sphere.vCenter = m_vPosition;
	m_sphere.fRaidus = 0.3f;

	g_EventManager->Attach(EEvent::E_PartsHold, this);
	g_EventManager->Attach(EEvent::E_PartsSpin, this);
	g_EventManager->Attach(EEvent::E_PartsPut, this);
	g_EventManager->Attach(EEvent::E_PartsThrow, this);
	std::cout << "ÆÄÃ÷ ID : " << m_nPartsID << std::endl;
}

CParts::~CParts()
{
}

void CParts::Setup()
{
	m_pCollision = new CSphereCollision(m_vPosition, 0.3f, &m_matWorld);
	D3DXCreateSphere(g_pD3DDevice, m_sphere.fRaidus, 10, 10, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlParts, sizeof(D3DMATERIAL9));
	m_stMtlParts.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_stMtlParts.Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	m_stMtlParts.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
}

void CParts::Update()
{
	m_matWorld = m_matS * m_matR * m_matT;
}

void CParts::Render()
{
	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlParts);
	m_pMeshSphere->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
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

void CParts::Interact()
{

}
