#pragma once
#include "CUIButton.h"
class CUIloadingMessageComplete :
	public CUIButton
{
public:
	CUIloadingMessageComplete(D3DXVECTOR2 vPos);
	~CUIloadingMessageComplete();

	virtual void Setup() override;
};

