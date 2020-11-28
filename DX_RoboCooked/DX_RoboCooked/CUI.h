#pragma once
#include "CEventListener.h"

enum class eUIState
{
	Disabled,
	Active,
	Hover

};

class CUI : public CEventListener
{
public:
	CUI();
	virtual ~CUI();

protected:
	eUIState			m_eUIState;
	CUI*				m_pParent;
	D3DXVECTOR2			m_vPosition;
	D3DXVECTOR2			m_vSize;
	std::list<CUI*>		m_listUIchildren;
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
	virtual void CheckIn(POINT pt);
	INT GetlistUIchildrenSize() { return m_listUIchildren.size(); }
	eUIState GetUIState() { return m_eUIState; }
	void SetUIState(eUIState st) { m_eUIState = st; }
};

