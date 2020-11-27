#pragma once
#include"CUIButton.h"

class CUIButton;

class CUIBoardButton :
	public CUIButton

{
public:
	CUIBoardButton(D3DXVECTOR2 vPos);
	~CUIBoardButton();

public:
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

