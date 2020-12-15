#pragma once
#include "CUIButton.h"
#include "IInteractCenter.h"

class IInteractCenter;
class CUIStar;
class CUIClearButton :
	public CUIButton
{
private:
	IInteractCenter*	m_pInteractCenter;
	CUIStar*			m_pUIStar;

public:
	CUIClearButton(D3DXVECTOR2 vPos,FLOAT fTime, IInteractCenter* pInteractCenter);
	~CUIClearButton();

public:
	virtual void Setup() override;
	void OnEvent(eEvent eEvent, void * _value);
	void ClickEvent(void* _value);
	void HoverEvent(void* _value);
	void KeyPressEvent(void* _value);
	void KeyReleaseEvent(void* _value);
	void MouseReleaseEvent(void* _value);
};

