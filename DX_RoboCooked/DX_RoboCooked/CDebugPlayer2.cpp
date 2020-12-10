#include "stdafx.h"
#include "CDebugPlayer2.h"

#include "CBoxCollision.h"
#include "CSphereCollision.h"
#include "CSkinnedMesh.h"

CDebugPlayer2::CDebugPlayer2(IInteractCenter* pInteractCenter): CCharacter(1)
{
	m_pInteractCenter = pInteractCenter;
	m_vPosition = g_vZero;

	m_pSkinnedMesh = new CSkinnedMesh;
	m_pSkinnedMesh->Load("data/model/character", "로보토미_2P_달리기1.X");
	m_pSkinnedMesh->m_pmatWorldTM = new D3DXMATRIXA16;

	D3DXVECTOR3 max = m_pSkinnedMesh->GetMax();
	D3DXVECTOR3 min = m_pSkinnedMesh->GetMin();

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixScaling(&matS, 0.015f, 0.015f, 0.015f);
	D3DXMatrixRotationY(&matR, D3DXToRadian(180));
	D3DXMatrixTranslation(&matT, 0, -((max.y - min.y) /2 * 0.015f), 0);
	*(m_pSkinnedMesh->m_pmatWorldTM) = matS * matR * matT;

	m_pCollision = new CSphereCollision(g_vZero, 0.5f, &m_matWorld);
	m_pInteractCollision = new CBoxCollision(D3DXVECTOR3(0, 0, 0.5f), D3DXVECTOR3(.8f, .8f, .8f), &m_matWorld);

	g_EventManager->Attach(eEvent::KeyPress, this);
	g_EventManager->Attach(eEvent::KeyRelease, this);
	g_EventManager->Attach(eEvent::Player1KeyChange, this);

	//D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMesh, NULL);
}

CDebugPlayer2::~CDebugPlayer2()
{
	SafeDelete(m_pInteractCollision);
	SafeDelete(m_pSkinnedMesh->m_pmatWorldTM);
	SafeDelete(m_pCollision);
	//SafeRelease(m_pMesh);
}

void CDebugPlayer2::Setup()
{
}
