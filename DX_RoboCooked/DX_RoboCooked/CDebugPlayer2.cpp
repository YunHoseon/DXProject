#include "stdafx.h"
#include "CDebugPlayer2.h"

#include "CBoxCollision.h"
#include "CSphereCollision.h"

CDebugPlayer2::CDebugPlayer2(IInteractCenter* pInteractCenter): CCharacter(1)
{
	m_pInteractCenter = pInteractCenter;
	//m_vPosition = m_cube.vCenter;
	m_vPosition = D3DXVECTOR3(-2, 0, 0);
	m_matWorld = m_matS * m_matR * m_matT;
	D3DXMatrixIdentity(&m_matWorld);

	g_EventManager->Attach(eEvent::KeyPress, this);
	g_EventManager->Attach(eEvent::KeyRelease, this);
	g_EventManager->Attach(eEvent::Player2KeyChange, this);
}

CDebugPlayer2::~CDebugPlayer2()
{
	SafeDelete(m_pInteractCollision);
}

void CDebugPlayer2::Setup()
{
	m_pCollision = new CSphereCollision(g_vZero, 0.5f, &m_matWorld);
	m_pInteractCollision = new CBoxCollision(D3DXVECTOR3(0, 0, 0.5f), D3DXVECTOR3(1.f, 1.f, 1.f), &m_matWorld);
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMesh, NULL);
}
