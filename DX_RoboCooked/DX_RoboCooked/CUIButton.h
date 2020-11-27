#pragma once
#include "CUI.h"

class CUI;
class CUITexture;
class CUIText;

class CUIButton :
	public CUI
{
protected:
	std::list<CUI*> m_listUIchildren;

public:
	CUIButton();
	virtual ~CUIButton();
	
	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

public:
	virtual void Add(CUI *component) override;
	virtual void Remove(CUI *component) override;
	//virtual bool CheckIn(POINT pt);
};