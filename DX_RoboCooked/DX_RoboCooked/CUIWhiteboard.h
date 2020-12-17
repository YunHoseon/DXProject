#pragma once
#include "CUIButton.h"
class CUIWhiteboard :
	public CUIButton
{
public:
	CUIWhiteboard();
	~CUIWhiteboard();

	virtual void Setup() override;
};

