#pragma once
#include "CUIButton.h"
class CUIClearBoard :
	public CUIButton
{
private:
	string m_sTimeText;

public:
	CUIClearBoard(D3DXVECTOR2 vPos, string sText, eBtnEvent btnEvent);
	~CUIClearBoard();
public:
	virtual void Setup() override;
};

