#pragma once
#include "CUI.h"

class CUIText :
	public CUI
{
protected:
	string		m_sText;
	RECT		m_rcText;
public:
	CUIText(string ptext , D3DXVECTOR2 vPos);
	~CUIText();

	void Update() override;
	void Render() override;
};

