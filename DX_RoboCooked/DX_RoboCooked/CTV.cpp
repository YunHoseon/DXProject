#include "stdafx.h"
#include "CTV.h"
#include "CBoxCollision.h"


CTV::CTV()
	: m_p3DText(nullptr)
	, m_pSMesh(nullptr)
	, m_nMin(0)
	, m_nSec(0)
	, m_fTime(0.0f)
{
	//m_pSMesh = g_pStaticMeshManager->GetStaticMesh("TV");
	//m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);
	Create_Font();
}


CTV::~CTV()
{
}

void CTV::Update()
{
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
	wcscpy_s(lf.lfFaceName, L"±¼¸²Ã¼");

	HFONT hFont;
	HFONT hFontOld;

	hFont = CreateFontIndirect(&lf);
	hFontOld = (HFONT)SelectObject(hdc, hFont);
	D3DXCreateText(g_pD3DDevice, hdc, L"TV TEXT", 0.001f, 0.01f, &m_p3DText, 0, 0);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);

}

