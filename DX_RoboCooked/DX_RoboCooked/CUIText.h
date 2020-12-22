#pragma once
#include "CUI.h"

enum class eTextType
{
	ClearText,
	SelectText,
	UpdateText
};


class CUIText :
	public CUI
{
private:
	string		m_sText;
	RECT		m_rcText;
	eTextType	m_eType;
public:
	CUIText(string ptext , D3DXVECTOR2 vPos, eTextType type);
	~CUIText();

	void Update() override;
	void Render() override;
};

