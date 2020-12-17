#include "stdafx.h"
#include "CTV.h"
#include "CBoxCollision.h"
#include "IInteractCenter.h"

CTV::CTV(IInteractCenter *pIntaract)
	: m_p3DText(nullptr)
	, m_pSMesh(nullptr)
	, m_fTime(0.0f), m_sTime()
{
	m_pInteractCenter = pIntaract;

	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("TV");
	SetScale(0.01f, 0.01f, 0.01f);
	SetRotationY(D3DXToRadian(0));
	m_vPosition = D3DXVECTOR3(0.0f, 5.0f, 3.0f);
}

CTV::~CTV()
{
	SafeRelease(m_p3DText);
	SafeDelete(m_pSMesh);
}

void CTV::Update()
{
	m_fTime = m_pInteractCenter->GetTime();
	string sTime = m_pInteractCenter->CalMin(m_fTime) + ":" + m_pInteractCenter->CalSec(m_fTime);
	m_sTime.assign(sTime.begin(), sTime.end());
	Create_Font();
}

void CTV::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSMesh->Render();

	if (m_p3DText)
		m_p3DText->DrawSubset(0);
}

void CTV::Create_Font()
{
	HDC hdc = CreateCompatibleDC(0);

	HFONT hFontOld = (HFONT)SelectObject(hdc, g_pFontManager->Get3dFont(CFontManager::TVTIME));

	SafeRelease(m_p3DText);
	D3DXCreateText(g_pD3DDevice, hdc, m_sTime.c_str(), 0.001f, 0.01f, &m_p3DText, 0, 0);

	SelectObject(hdc, hFontOld);
	DeleteDC(hdc);
}
