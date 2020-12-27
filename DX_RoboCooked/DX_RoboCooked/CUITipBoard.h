#pragma once
#include "CUIButton.h"
class CUIPopUpBoard;
class CUITipBoard :
	public CUIButton
{
private:
	CUIPopUpBoard*	m_pPopUpBoard;
public:
	CUITipBoard(D3DXVECTOR2 vPos);
	~CUITipBoard();
public:
	void Setup()override;
	void SetText(string sText,int nWidth,int nHeight);
};

