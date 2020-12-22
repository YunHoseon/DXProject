#pragma once
#include "CUIButton.h"
#include "CUIText.h"

class CUIClearTime :
	public CUIButton
{
private:
	eTextType m_eType;
public:
	CUIClearTime(D3DXVECTOR2 vPos, D3DXVECTOR2 vTextPos, string sTimeText, eTextType eType);
	~CUIClearTime();

public:
	virtual void Setup();
};

