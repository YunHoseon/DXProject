#pragma once
#include "CUI.h"

class CUI;
class CUITexture;
class CUIText;

class CUIButton :
	public CUI
{
private:
	std::list<CUI*> m_listUIchildren;

public:
	CUIButton();
	~CUIButton();
	
	void Setup();
	void Update();
	void Render();


public:
	void Add(CUI *component) override;
	void Remove(CUI *component) override;
	void OnEvent(eEvent eEvent, void* _value) override;
	virtual bool CheckIn(POINT pt);


};

