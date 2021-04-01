#pragma once
#include "CUIButton.h"
class CBlueprint;
class CUIWhiteboard :
	public CUIButton
{
public:
	CUIWhiteboard(D3DXVECTOR2 vPos );
	~CUIWhiteboard();

	virtual void Setup() override;
	void SetFormula(vector<CBlueprint *>& vBp);

};

