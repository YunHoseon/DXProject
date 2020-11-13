#pragma once
class CKeyboard;
class CMouse;

#define InputManager CInputManager::GetInstance()

class CInputManager : public CSingleton<CInputManager>
{
	CKeyboard*	m_pKeyboard;
	CMouse*		m_pMouse;
public:
	CInputManager();
	~CInputManager();

public:
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

