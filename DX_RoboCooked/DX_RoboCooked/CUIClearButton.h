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
	INT					m_nTime;

public:
	CUIClearButton(D3DXVECTOR2 vPos, IInteractCenter* pInteractCenter);
	~CUIClearButton();

public:
	virtual void Setup() override;

	bool OnEvent(eEvent eEvent, void * _value);
	void SetTimeEvent(void * _value);
};

