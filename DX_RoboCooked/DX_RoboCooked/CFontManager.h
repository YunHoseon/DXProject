#pragma once

#define g_pFontManager CFontManager::GetInstance()

class CFontManager : public CSingleton<CFontManager>
{
public:
	enum eFontType
	{
		E_DEFAULT,
		E_QUEST
	};
	//Singletone(CFontManager);
private:
	map<eFontType, LPD3DXFONT> m_mapFont;
	CFontManager();
	~CFontManager();
	
public:
	LPD3DXFONT GetFont(eFontType e);
	void Destroy();
};
