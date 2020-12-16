#pragma once
#include "CUIButton.h"
class CUIClearBoard :
	public CUIButton
{
private:
	string m_sTimeText;

public:
	CUIClearBoard(string sText, eBtnEvent btnEvent);
	~CUIClearBoard();
public:
	virtual void Setup() override;
};

