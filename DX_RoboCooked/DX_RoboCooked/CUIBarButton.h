#pragma once
#include "CUIButton.h"
class CUIBarButton :
	public CUIButton
{
public:
	CUIBarButton(D3DXVECTOR2 vPos);
	~CUIBarButton();

public:
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

