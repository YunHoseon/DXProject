#pragma once
#include "CUIButton.h"
class CUIMainScreen :
	public CUIButton
{
private:
	CUIButton* m_pMaker;
	CUIButton* m_pControll;
public:
	CUIMainScreen(CUIButton* pMaker,CUIButton* pControll);
	~CUIMainScreen();

public:
	void Setup() override;
	bool OnEvent(eEvent eEvent, void * _value);
	void StartGame();
	void EndGame();
};

