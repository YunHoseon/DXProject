#pragma once
#include "CUIButton.h"

class IInteractCenter;

class CUILoading :
	public CUIButton
{
private:
	//IInteractCenter*	m_pInteractCenter;
	bool				m_isLoading;

	CUI*				m_pBoard;
	CUI*				m_pLoadingMessage;
	CUI*				m_pCompleteMessage;

public:
	CUILoading(IInteractCenter*	pInteractCenter);
	~CUILoading();

	void Setup() override;
	bool OnEvent(eEvent eEvent, void* _value);

	bool KeyReleaseEvent(void* _value);
	bool LoadingEndEvent();
};

