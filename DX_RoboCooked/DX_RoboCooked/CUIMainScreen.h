#pragma once
#include "CUIButton.h"
class CUIMainScreen :
	public CUIButton
{
public:
	CUIMainScreen();
	~CUIMainScreen();

public:
	void Setup() override;
	bool OnEvent(eEvent eEvent, void * _value);
	void StartGame();
	void EndGame();
};

