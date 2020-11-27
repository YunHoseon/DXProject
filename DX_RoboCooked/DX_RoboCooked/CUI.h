#pragma once
class CButton;

class CUI
{

public:
	CUI();
	virtual ~CUI();

public:
	CButton*			m_pParent;
	D3DXMATRIXA16		m_matWorld;
	Synthesize(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
};

