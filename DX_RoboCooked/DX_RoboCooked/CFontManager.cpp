#include "stdafx.h"
#include "CFontManager.h"

CFontManager::CFontManager(): CSingleton<CFontManager>(), m_nFontCount(0)
{
	AddFontResourceA("./data/Fonts/a컴퓨터C.ttf");
	++m_nFontCount;
}

CFontManager::~CFontManager()
{
	for (auto && p : m_mapFont)
	{
		while(p.second)
			SafeRelease(p.second);
	}
	for (auto && p : m_map3dFont)
	{
		DeleteObject(p.second);
	}
	for (int i = 0; i < m_nFontCount; ++i)
	{
		RemoveFontResourceA("./data/Fonts/a컴퓨터C.ttf");
	}
	m_nFontCount = 0;
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
	else if(e == CLEARTIME)
	{
		fd.Height = 100;
		fd.Width = 100;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		
		AddFontResource(L"data/Fonts/a컴퓨터C.ttf");
		++m_nFontCount;
		wcscpy_s(fd.FaceName, L"a컴퓨터C");
	}
	else if (e == SELECT)
	{
		fd.Height = 46;
		fd.Width = 23;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		
		AddFontResource(L"data/Fonts/a컴퓨터C.ttf");
		++m_nFontCount;
		wcscpy_s(fd.FaceName, L"a컴퓨터C");
	}
	else if (e == UPDATE)
	{
		fd.Height = 80;
		fd.Width = 40;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;

		AddFontResource(L"data/Fonts/a컴퓨터C.ttf");
		++m_nFontCount;
		wcscpy_s(fd.FaceName, L"a컴퓨터C");
	}
	else if (e == TIP)
	{
		fd.Height = 35;
		fd.Width = 35;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		
		AddFontResource(L"data/Fonts/a컴퓨터C.ttf");
		++m_nFontCount;
		wcscpy_s(fd.FaceName, L"a컴퓨터C");
	}
	
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);
	return m_mapFont[e];
}

HFONT CFontManager::Get3dFont(eFontType e)
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
		AddFontResourceA("./data/Fonts/a컴퓨터C.ttf");
		++m_nFontCount;
	}

	
	m_map3dFont[e] = CreateFontIndirect(&lf);

	return m_map3dFont[e];
}

void CFontManager::Destroy()
{
	for (auto && p : m_mapFont)
	{
		while (p.second)
			SafeRelease(p.second);
	}
	for (auto && p : m_map3dFont)
	{
		DeleteObject(p.second);
	}
	for (int i = 0; i < m_nFontCount; ++i)
	{
		RemoveFontResourceA("./data/Fonts/a컴퓨터C.ttf");
	}
	m_nFontCount = 0;
}
