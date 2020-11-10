#pragma once
class CMouse
{
private:
	enum eMouseState { E_NONE = 0, E_CLICK, E_RELEASE, E_DBLCLK, E_DRAG };
	
	POINT		m_mousePoint;
	DWORD		m_dwPrevKey;
	DWORD		m_elapsedTime;
	eMouseState m_eMouseState;
	
public:
	CMouse();
	~CMouse();

	void PressLBtn(LPARAM lParam);
	void ReleaseLBtn(WPARAM keyID);
	void JudgeLDoubleClick(WPARAM keyID);

	POINT GetMousePoint(); 
};

