#pragma once
#include "CUI.h"

class CUI;
class CUITexture;
class CUIText;


class CUIButton :
	public CUI
{
protected:
	WPARAM					  m_wActiveButton;
	CUITexture*				  m_pTexture;
	CUIText*				  m_pText;
	std::array<ST_PLAYER_INPUTKEY*, 2>	m_pInputKey;
	bool					  m_isKeyDown;
	bool					  m_isMouseDown;

public:
	CUIButton();
	virtual ~CUIButton();
	
	virtual void Setup() = 0;
	virtual void Render();

public:
	virtual void Add(CUI *component) override;
	virtual void Remove(CUI *component) override;

};