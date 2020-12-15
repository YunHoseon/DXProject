#pragma once

#define g_pFontManager CFontManager::GetInstance()

class CFontManager : public CSingleton<CFontManager>
{
public:
	enum eFontType
	{
		DEFAULT,
		CLEARTIME,
		TVTIME
	};
private:
	map<eFontType, LPD3DXFONT> m_mapFont;
	map<eFontType, HFONT> m_map3dFont;

	friend CSingleton<CFontManager>;
	CFontManager();
	~CFontManager();
public:
	
	LPD3DXFONT GetFont(eFontType e);
	HFONT Get3dFont(eFontType e);
	void Destroy();
};
