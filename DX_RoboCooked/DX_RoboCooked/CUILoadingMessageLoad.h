#pragma once
#include "CUIButton.h"
class CUILoadingMessageLoad :
	public CUIButton
{
public:
	CUILoadingMessageLoad(D3DXVECTOR2 vPos);
	~CUILoadingMessageLoad();

	virtual void Setup() override;
};

