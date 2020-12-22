#pragma once
#include "CUIButton.h"
class CUIStageSelect :
	public CUIButton
{
public:
	CUIStageSelect(D3DXVECTOR2 vPos);
	~CUIStageSelect();

public:
	void Setup() override;
	bool OnEvent(eEvent eEvent, void * _value);
};

