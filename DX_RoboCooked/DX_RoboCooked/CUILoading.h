#pragma once
#include "CUIButton.h"
class CUILoading :
	public CUIButton
{
private:
	bool	m_isLoading;
public:
	CUILoading();
	~CUILoading();

	void Setup() override;
	void OnEvent(eEvent eEvent, void* _value);

	void ClickEvent(void* _value);
	void MouseReleaseEvent(void* _value);
	void KeyPressEvent(void* _value);
	void KeyReleaseEvent(void* _value);
};

