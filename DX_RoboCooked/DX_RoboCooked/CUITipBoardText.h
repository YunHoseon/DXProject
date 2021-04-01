#pragma once
#include "CUIButton.h"
class CUITipBoardText :
	public CUIButton
{
private:
	string		m_sTipText;
	std::wstring m_wsTipText;
	int			m_nWidth;
	int			m_nHeight;
public:
	CUITipBoardText(D3DXVECTOR2 vPos,string sText,int nWidth, int nHeight);
	CUITipBoardText(D3DXVECTOR2 vPos, std::wstring wsText, int nWidth, int nHeight);
	~CUITipBoardText();

public:
	void Setup()override;
};

