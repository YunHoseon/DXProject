#pragma once
#include "CUI.h"

class CUI;
class CUITexture;
class CUIText;
class IInteractCenter;

class CUIButton :
	public CUI
{
protected:
	WPARAM					  m_wActiveButton;
	CUITexture*				  m_pTexture;
	CUIText*				  m_pText;
	std::array<ST_PLAYER_INPUTKEY*, 2>	m_pInputKey;
	bool					  m_isKeyDown;
	//bool					  m_isMouseDown;
	IInteractCenter*		  m_pInteractCenter;
public:
	CUIButton(IInteractCenter* pInteractCenter = nullptr);
	virtual ~CUIButton();
	
	virtual void Setup() = 0;
	virtual void Render();
	virtual void SetPosition(float x, float y) override;
	virtual void ResetGame();
	virtual void GoToMain();

public:
	virtual void AddChild(CUI *component) override;
	virtual void Remove(CUI *component) override;
	virtual void MouseHoverEvent(void* _value);
	virtual void MouseClickEvent(void* _value);
	virtual void MouseReleaseEvent(void* _value);



};