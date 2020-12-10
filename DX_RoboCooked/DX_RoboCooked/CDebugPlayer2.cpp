#include "stdafx.h"
#include "CDebugPlayer2.h"

#include "CBoxCollision.h"
#include "CSphereCollision.h"

CDebugPlayer2::CDebugPlayer2(IInteractCenter* pInteractCenter): CCharacter(1)
{
	m_pInteractCenter = pInteractCenter;

	m_pCollision = new CSphereCollision(g_vZero, 0.5f, &m_matWorld);
	m_pInteractCollision = new CBoxCollision(D3DXVECTOR3(0, 0, 0.5f), D3DXVECTOR3(.8f, .8f, .8f), &m_matWorld);
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMesh, NULL);
	
	SetPosition(-2, 0, 0);
	
	g_EventManager->Attach(eEvent::KeyPress, this);
	g_EventManager->Attach(eEvent::KeyRelease, this);
	g_EventManager->Attach(eEvent::Player2KeyChange, this);

}

CDebugPlayer2::~CDebugPlayer2()
{
	SafeDelete(m_pInteractCollision);
	SafeDelete(m_pCollision);
	SafeRelease(m_pMesh);
}

void CDebugPlayer2::Setup()
{

}
