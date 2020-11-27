#pragma once
#include "CUIButton.h"
class CUIPauseButton :
	public CUIButton
{
public:
	CUIPauseButton(D3DXVECTOR2 vPos);
	~CUIPauseButton();

public:
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

