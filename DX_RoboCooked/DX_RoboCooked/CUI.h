#pragma once
#include "CEventListener.h"

enum class eUIState
{
	up,
	down,
	Hover
};

enum class eBtnEvent
{
	None,
	MakerClose,
	MainStart,
	MainControll,
	MainMaker,
	MainEnd,
	PauseMain,
	PauseClose,
	PauseReset,
	PauseEnd,
	ClearMain,
	ClearNextStage,
	LoseMain,
	LoseReset,
	ControllClose

};
class CUI : public CEventListener
{
private:
	eUIState			m_eUIPastState;
public:
	CUI();
	virtual ~CUI();

protected:
	eBtnEvent			m_eBtnEvent;
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
	virtual void AddChild(CUI *component) {}
	virtual void Remove(CUI *component) {}
	virtual void Setup() {}
	virtual void CheckPressIn(POINT pt);
	virtual void CheckReleaseIn(POINT pt);
	virtual void CheckInHover(POINT pt);
	virtual void InvertActive();
	virtual void ActiveUI();
	virtual void CheckActiveEvent();
	virtual bool GetActive() { return m_isActive; }
	D3DXVECTOR2 GetPosition() { return m_vPosition; }
	void ButtonEvent(eBtnEvent btnEvent);

	INT GetlistUIchildrenSize() { return m_listUIchildren.size(); }

	eUIState GetUIState() { return m_eUIState; }
	void SetUIState(eUIState st) { m_eUIState = st; }

	eUIState GetUIPastState() { return m_eUIPastState; }
	void SetUIPastState(eUIState st) 
	{ 
		if(st != eUIState::Hover)
			m_eUIPastState = st;
	}

	void InitUIState();
	void SetActiveUIState(int n);

	void AddPosition(float x, float y);
};

