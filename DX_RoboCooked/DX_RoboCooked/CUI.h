#pragma once

class CUI
{
public:
	CUI();
	virtual ~CUI();

protected:
	CUI*				m_pParent;
	D3DXMATRIXA16		m_matWorld;
	Synthesize(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	
public:
	virtual void Update() {}
	virtual void Render() {}
	void SetParent(CUI *parent);
	CUI *GetParent() const 
	{
		return this->m_pParent;
	}
	virtual void Add(CUI *component) {}
	virtual void Remove(CUI *component) {}
	virtual void Setup() {}
};

