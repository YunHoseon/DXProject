#pragma once
#include "CUIButton.h"
class IInteractCenter;
class CUIReady :
	public CUIButton
{
private:
	float				m_fElapsedTime;

public:
	CUIReady(D3DXVECTOR2 vPos, IInteractCenter* pIntractCenter);
	~CUIReady();

public:
	void Setup()override;
	bool OnEvent(eEvent eEvent, void* _value);
	bool TickUpdate(void* _value);
};

