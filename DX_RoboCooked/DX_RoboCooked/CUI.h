#pragma once
#include "CEventListener.h"

class CUI : public CEventListener
{
public:
	CUI();
	virtual ~CUI();

protected:
	CUI*				m_pParent;
	D3DXVECTOR2			m_vPosition;
	D3DXVECTOR2			m_vSize;
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
	virtual bool CheckIn(POINT pt);
};

