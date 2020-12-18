#pragma once
#include "CEventListener.h"

enum class eUIState
{
	Up,
	Down,
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
	D3DXMATRIXA16		m_matWorld;
	D3DXVECTOR3*		m_pTargetPosition;
	D3DXMATRIXA16*		m_pTargetWorldTM;
	eBtnEvent			m_eBtnEvent;
	eUIState			m_eUIState;
	CUI*				m_pParent;
	D3DXVECTOR2			m_vPosition;
	D3DXVECTOR2			m_vSize;
	std::list<CUI*>		m_listUIchildren;
	bool				m_isActive;
	bool				m_isPress;

	static float		m_fWidthRevision;
	static float		m_fHeightRevision;

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
	virtual void SetPosition(float x, float y) { m_vPosition.x = x, m_vPosition.y = y; }
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

	static float GetWidthRevision() { return m_fWidthRevision; }
	static void SetWidthRevision(float x) { m_fWidthRevision = x; }
	static float GetHeightRevision() { return m_fHeightRevision; }
	static void SetHeightRevision(float x) { m_fHeightRevision = x; }

	bool GetIsActive() { return m_isActive; }
	void SetIsActive(bool isActive) { m_isActive = isActive; }

	D3DXVECTOR2 GetSize() { return m_vSize; }
	virtual void SetTargetPosition(D3DXVECTOR3* pPos) { m_pTargetPosition = pPos; }
	virtual void SetTargetWorldTM(D3DXMATRIXA16* pWorld) { m_pTargetWorldTM = pWorld; }
};

