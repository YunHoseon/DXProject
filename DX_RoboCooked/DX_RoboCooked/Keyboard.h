#pragma once

class CKeyboard
{
	enum eKeyBoardState { E_NONE, E_BTNDOWN, E_BTNUP, E_DBLDOWN, E_HOLD };
	eKeyBoardState	m_eKeyState;
	DWORD			m_dwPrevKey;
	DWORD			m_elapsedTime;
public:
	CKeyboard();
	~CKeyboard();

	std::unordered_map<WPARAM, bool> m_mapKey;

	void Update();
	void PressKey(WPARAM keyID, LPARAM lParam);
	void ReleaseKey(WPARAM keyID, LPARAM lParam);
	void JudgeDash(WPARAM keyID);

	bool IsKeyPressed(WPARAM keyID);
};
