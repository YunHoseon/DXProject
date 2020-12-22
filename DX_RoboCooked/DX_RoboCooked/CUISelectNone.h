#pragma once
#include "CUISelect.h"
class CUISelectNone :
	public CUISelect
{
public:
	CUISelectNone(D3DXVECTOR2 vPos , ST_GameData data);
	~CUISelectNone();

public: 
	void Setup();
};

