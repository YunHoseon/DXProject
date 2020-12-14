#include "stdafx.h"
#include "CTV.h"
#include "CBoxCollision.h"
#include "IInteractCenter.h"



CTV::CTV(IInteractCenter* pIntaract)
	: m_p3DText(nullptr)
	, m_pSMesh(nullptr)
	, m_fTime(0.0f)
	, m_sTime()
{
	m_pInteractCenter = pIntaract;
	//m_pSMesh = g_pStaticMeshManager->GetStaticMesh("TV");
	//m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);
}


CTV::~CTV()
{
	SafeRelease(m_p3DText);
	SafeDelete(m_pSMesh);
}

void CTV::Update()
{
	m_fTime = m_pInteractCenter->GetTime();
	string sTime = CalMin(m_fTime) +":" + CalSec(m_fTime);
	m_sTime.assign(sTime.begin(), sTime.end());
	wprintf(m_sTime.c_str());
	Create_Font();

}

void CTV::Render()
{
	//m_pSMesh->Render();

	/*_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT	m_pCollision->Render();*/
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

string CTV::CalMin(int sec)
{
	int a = sec / 60;
	if (a >= 10)
	{
		return std::to_string(a);
	}
	else
	{
		return "0" + std::to_string(a);
	}
}

string CTV::CalSec(int sec)
{
	int a = sec % 60;
	if (a >= 10)
	{
		return std::to_string(a);
	}
	else
	{
		return "0" + std::to_string(a);
	}
}

//{return std::to_string(sec / 60); }
//{return std::to_string(sec % 60); }