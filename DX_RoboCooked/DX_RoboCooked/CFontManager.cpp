#include "stdafx.h"
#include "CFontManager.h"

CFontManager::CFontManager(): CSingleton<CFontManager>()
{
}

CFontManager::~CFontManager()
{

}

LPD3DXFONT CFontManager::GetFont(eFontType e)
{
	if (m_mapFont.find(e) != m_mapFont.end())
	{
		return m_mapFont[e];
	}

	D3DXFONT_DESC fd{};
	
	if(e == DEFAULT)
	{
		fd.Height = 30;
		fd.Width = 15;
		fd.Weight = FW_BOLD;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		wcscpy_s(fd.FaceName, L"굴림체");
	}
	else if(e == QUEST)
	{
		fd.Height = 50;
		fd.Width = 25;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;

		AddFontResource(L"data/font/umberto.ttf");
		wcscpy_s(fd.FaceName, L"Umberto");
	}
	
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);
	return m_mapFont[e];
}

LOGFONT CFontManager::Get3dFont(eFontType e)
{
	if (m_map3dFont.find(e) != m_map3dFont.end())
	{
		return m_map3dFont[e];
	}

	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	if (e == TVTIME)
	{
		lf.lfHeight = 25;
		lf.lfWidth = 12;
		lf.lfWeight = 500;
		lf.lfItalic = false;
		lf.lfUnderline = false;
		lf.lfStrikeOut = false;
		lf.lfCharSet = DEFAULT_CHARSET;
		wcscpy_s(lf.lfFaceName, L"a컴퓨터C");
	}

	m_map3dFont[e] = lf;

	return m_map3dFont[e];
}

void CFontManager::Destroy()
{
	for (auto && it : m_mapFont)
	{
		SafeRelease(it.second);
	}
}
