#pragma once

#define g_pFontManager CFontManager::GetInstance()

class CFontManager : public CSingleton<CFontManager>
{
public:
	enum eFontType
	{
		DEFAULT,
		QUEST
	};
private:
	map<eFontType, LPD3DXFONT> m_mapFont;
	friend CSingleton<CFontManager>;
	CFontManager();
	~CFontManager();
public:
	
	LPD3DXFONT GetFont(eFontType e);
	void Destroy();
};
