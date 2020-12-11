#pragma once
#include "CUIButton.h"

class IInteractCenter;


class CUIPauseButton :
	public CUIButton
{

private:
	IInteractCenter*	m_pInteractCenter;

public:
	CUIPauseButton(D3DXVECTOR2 vPos,WPARAM wParam, IInteractCenter* pInteractCenter);
	~CUIPauseButton();

public:
	virtual void Setup() override;
	void OnEvent(eEvent eEvent, void * _value);
	void ClickEvent(void* _value);
	void HoverEvent(void* _value);
	void KeyPressEvent(void* _value);
	void KeyReleaseEvent(void* _value);
	void MouseReleaseEvent(void* _value);
	void ActiveButton();
};

