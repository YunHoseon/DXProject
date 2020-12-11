#pragma once
#include "CEventListener.h"

enum class eUIState
{
	Disabled,
	Active,
	Hover

};

enum class eBtnEvent
{
	None,
	PauseExit

};
class CUI : public CEventListener
{
private:
	eUIState			m_eUIPastState;
public:
	CUI();
	virtual ~CUI();

protected:
	eUIState			m_eUIState;
	CUI*				m_pParent;
	D3DXVECTOR2			m_vPosition;
	D3DXVECTOR2			m_vSize;
	std::list<CUI*>		m_listUIchildren;
	bool				m_isActive;
	bool				m_isPress;
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
	virtual void CheckPressIn(POINT pt);
	virtual void CheckReleaseIn(POINT pt);
	virtual void CheckInHover(POINT pt);
	void InvertActive();
	virtual void ButtonEvent() {};

	INT GetlistUIchildrenSize() { return m_listUIchildren.size(); }

	eUIState GetUIState() { return m_eUIState; }
	void SetUIState(eUIState st) { m_eUIState = st; }

	eUIState GetUIPastState() { return m_eUIPastState; }
	void SetUIPastState(eUIState st) 
	{ 
		if(st != eUIState::Hover)
			m_eUIPastState = st;
	}

};

