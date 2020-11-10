#include "stdafx.h"
#include "Keyboard.h"


CKeyboard::CKeyboard()
	:m_elapsedTime(0),
	 m_dwPrevKey(0)
{
	m_eKeyState = E_NONE;
}

CKeyboard::~CKeyboard()
{
}

void CKeyboard::Update()
{
	if (InputManager->IsKeyPressed('W'))
	{
		std::cout << "W" << std::endl;
	}
	else if (InputManager->IsKeyPressed('A'))
	{
		std::cout << "A" << std::endl;
	}
	else if (InputManager->IsKeyPressed('S'))
	{
		std::cout << "S" << std::endl;
	}
	else if (InputManager->IsKeyPressed('D'))
	{
		std::cout << "D" << std::endl;
	}
}

void CKeyboard::PressKey(WPARAM keyID)
{
	JudgeDash(keyID);
	m_dwPrevKey = keyID;
	m_eKeyState = E_BTNDOWN;
	m_mapKey[keyID] = true;
}

void CKeyboard::ReleaseKey(WPARAM keyID)
{
	m_eKeyState = E_BTNUP;
	m_mapKey[keyID] = false;
}

void CKeyboard::JudgeDash(WPARAM keyID)
{
	DWORD currentTime = GetTickCount();

	if (currentTime - m_elapsedTime < 500 && keyID == m_dwPrevKey && m_eKeyState == E_BTNUP)
	{
		std::cout << "´ë½¬" << std::endl;
		m_eKeyState = E_DBLDOWN;
	}
	m_elapsedTime = GetTickCount();
}

bool CKeyboard::IsKeyPressed(WPARAM keyID)
{
	/*if (m_mapKey[keyID])
	{
		m_mapKey[keyID] = false;
		return true;
	}
	else
		return false;*/

	if (m_mapKey[keyID])
		return m_mapKey[keyID];
	else
		return false;
}
