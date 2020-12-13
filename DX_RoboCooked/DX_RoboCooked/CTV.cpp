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
	AddFontResourceA("./data/Fonts/a컴퓨터C.ttf");
	m_pInteractCenter = pIntaract;
	//m_pSMesh = g_pStaticMeshManager->GetStaticMesh("TV");
	//m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);
}


CTV::~CTV()
{
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

	m_p3DText->DrawSubset(0);
}

void CTV::Create_Font()
{
	HDC hdc = CreateCompatibleDC(0);
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 25;
	lf.lfWidth = 12;
	lf.lfWeight = 500;
	lf.lfItalic = false;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	lf.lfCharSet = DEFAULT_CHARSET;
	wcscpy_s(lf.lfFaceName, L"a컴퓨터C");

	HFONT hFont;
	HFONT hFontOld;

	hFont = CreateFontIndirect(&lf);
	hFontOld = (HFONT)SelectObject(hdc, hFont);
	D3DXCreateText(g_pD3DDevice, hdc, m_sTime.c_str(), 0.001f, 0.01f, &m_p3DText, 0, 0);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
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