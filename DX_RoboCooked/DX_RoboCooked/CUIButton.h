#pragma once
#include "CUI.h"

class CUI;
class CUITexture;
class CUIText;


class CUIButton :
	public CUI
{
protected:
	CUITexture*		m_pTexture;
	CUIText*		m_pText;

public:
	CUIButton();
	virtual ~CUIButton();
	
	virtual void Setup() = 0;
	virtual void Update();
	virtual void Render();


public:
	virtual void Add(CUI *component) override;
	virtual void Remove(CUI *component) override;
	//virtual bool CheckIn(POINT pt);
};