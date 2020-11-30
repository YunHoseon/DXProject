#pragma once
#include "CUIButton.h"
class CUIPauseButton :
	public CUIButton
{

public:
	CUIPauseButton(D3DXVECTOR2 vPos,WPARAM wParam);
	~CUIPauseButton();

public:
	virtual void Setup() override;
	void OnEvent(eEvent eEvent, void * _value);
	void ClickEvent(void* _value);
	void HoverEvent(void* _value);
	void KeyPressEvent(void* _value);
	void MouseReleaseEvent(void* _value);
};

