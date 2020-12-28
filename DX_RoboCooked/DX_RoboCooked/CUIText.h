#pragma once
#include "CUI.h"

enum class eTextType
{
	ClearText,
	SelectText,
	UpdateText,
	TipText
};


class CUIText :
	public CUI
{
private:
	string		m_sText;
	std::wstring m_wsText;
	RECT		m_rcText;
	eTextType	m_eType;
public:
	CUIText(string sText , D3DXVECTOR2 vPos, int nWidth = 500, int nHeight = 200, eTextType type = eTextType::UpdateText);
	CUIText(std::wstring wsText, D3DXVECTOR2 vPos, int nWidth = 500, int nHeight = 200, eTextType type = eTextType::UpdateText);
	~CUIText();

	void Update() override;
	void Render() override;
};

