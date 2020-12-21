#include "stdafx.h"
#include "CTV.h"
#include "CBoxCollision.h"
#include "IInteractCenter.h"

CTV::CTV(IInteractCenter *pIntaract, D3DXMATRIXA16* pParentWorld)
	: m_p3DText(nullptr), m_pSMesh(nullptr), m_fTime(0.0f), m_sTime(), m_pParentWorld(pParentWorld)
{
	m_pInteractCenter = pIntaract;

	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("TV");
	SetScale(0.15f, 0.15f, 0.15f);
	SetRotationY(D3DXToRadian(0));
	SetPosition(0.0f, 3.25f, -.9f);


	D3DXMATRIXA16  matS, matT;
	D3DXMatrixScaling(&matS, 5.5f, 5.5f, 5.5f);
	D3DXMatrixTranslation(&matT, -6.5f, 5.5f, 0);
	m_matTextLocal = matS * matT;
}

CTV::~CTV()
{
	SafeRelease(m_p3DText);
}

void CTV::Update()
{
	m_fTime = m_pInteractCenter->GetTime();
	string sTime = m_pInteractCenter->CalMin(m_fTime) + ":" + m_pInteractCenter->CalSec(m_fTime);
	m_sTime.assign(sTime.begin(), sTime.end());
	CreateFont();
}

void CTV::Render()
{
	D3DXMATRIXA16 matWorld = m_matWorld * *m_pParentWorld;
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pSMesh->Render();

	if (m_p3DText)
	{
		matWorld = m_matTextLocal * matWorld;
		
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_p3DText->DrawSubset(0);
	}
}

void CTV::CreateFont()
{
	HDC hdc = CreateCompatibleDC(0);
	HFONT hFontOld = (HFONT)SelectObject(hdc, g_pFontManager->Get3dFont(CFontManager::TVTIME));

	SafeRelease(m_p3DText);
	D3DXCreateText(g_pD3DDevice, hdc, m_sTime.c_str(), 0.001f, 0.01f, &m_p3DText, 0, 0);

	SelectObject(hdc, hFontOld);
	DeleteDC(hdc);
}
