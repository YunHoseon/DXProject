#pragma once

class CKeyboard
{
	enum eKeyBoardState { E_NONE, E_BTNDOWN, E_BTNUP, E_DBLDOWN, E_HOLD };
	eKeyBoardState	m_eKeyState;
	DWORD			m_dwPrevKey;
	DWORD			m_elapsedTime;

	ST_PLAYER_INPUTKEY	m_stInputKey[2];
public:
	CKeyboard();
	~CKeyboard();

	std::unordered_set<WPARAM> m_setKey;

	void Update();
	void PressKey(WPARAM keyID, LPARAM lParam);
	void ReleaseKey(WPARAM keyID, LPARAM lParam);
	//void JudgeDash(WPARAM keyID);
	void OnEvent(eEvent eEvent, void* _value);
	void SetKeyChange(int n, void* _value);		//어떤 플레이어의 키를 바꿀것인지, 어떤 값으로 바꿀것인지
};
