#include "stdafx.h"
#include "InputManager.h"
#include "Keyboard.h"
#include "Mouse.h"


CInputManager::CInputManager():CSingleton<CInputManager>()
{
	m_pKeyboard = new CKeyboard;
	m_pMouse = new CMouse;
}

CInputManager::~CInputManager()
{
	SafeDelete(m_pKeyboard);
	SafeDelete(m_pMouse);
}

void CInputManager::Update()
{
	m_pKeyboard->Update();
}

void CInputManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		m_pKeyboard->PressKey(wParam);
		break;

	case WM_KEYUP:
		m_pKeyboard->ReleaseKey(wParam);
		break;

	case WM_LBUTTONDOWN:
		m_pMouse->PressLBtn(lParam);
		break;

	case WM_LBUTTONUP:
		m_pMouse->ReleaseLBtn(wParam);
		break;

	case WM_RBUTTONDOWN:
		break;

	case WM_RBUTTONUP:
		break;
	}
}

bool CInputManager::IsKeyPressed(WPARAM wParam)
{
	return m_pKeyboard->IsKeyPressed(wParam);
}
