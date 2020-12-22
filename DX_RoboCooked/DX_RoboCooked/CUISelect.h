#pragma once
#include "CUIButton.h"
class CUIStar;

class CUISelect :
	public CUIButton
{
protected:
	ST_GameData		m_stData;
public:
	CUISelect(D3DXVECTOR2 vPos ,ST_GameData data);
	~CUISelect();

public:
	void Setup() = 0;
};

