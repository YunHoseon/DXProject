#pragma once
#include "CUIButton.h"
class CUIPauseButton :
	public CUIButton
{
public:
	CUIPauseButton(D3DXVECTOR2 vPos);
	~CUIPauseButton();

public:
	virtual void Setup() override;
	void OnEvent(eEvent eEvent, void * _value);
	void ClickEvent(void* _value);
	void HoverEvent(void* _value);
};

