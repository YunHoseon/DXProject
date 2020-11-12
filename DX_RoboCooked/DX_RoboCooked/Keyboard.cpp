#include "stdafx.h"
#include "Keyboard.h"


CKeyboard::CKeyboard()
	:m_elapsedTime(0)
	,m_dwPrevKey(0)
{
	m_eKeyState = E_NONE;
}

CKeyboard::~CKeyboard()
{
}

void CKeyboard::Update()
 {
	
	//ST_BitrhDayEvent data{ name, age };
	//NotifyEvent(EEvent::E_BIRTHDAY, (void*)&data);
	
	if (InputManager->IsKeyPressed('W'))
	{
		ST_MoveEvent data;
		data.wKey = 'W';
		g_EventManager->CallEvent(EEvent::E_EventMovePlayer1, (void*)&data);
		std::cout << "W" << std::endl;
	}
	if (InputManager->IsKeyPressed('A'))
	{
		ST_MoveEvent data;
		data.wKey = 'A';
		g_EventManager->CallEvent(EEvent::E_EventMovePlayer1, (void*)&data);
		std::cout << "A" << std::endl;
	}
	if (InputManager->IsKeyPressed('S'))
	{
		ST_MoveEvent data;
		data.wKey = 'S';
		g_EventManager->CallEvent(EEvent::E_EventMovePlayer1, (void*)&data);
		std::cout << "S" << std::endl;
	}
	if (InputManager->IsKeyPressed('D'))
	{
		ST_MoveEvent data;
		data.wKey = 'D';
		g_EventManager->CallEvent(EEvent::E_EventMovePlayer1, (void*)&data);
		std::cout << "D" << std::endl;
	}
	if(InputManager->IsKeyPressed(VK_CONTROL))
	{
		std::cout << "lCtrl" << std::endl;
	}

	if(InputManager->IsKeyPressed(VK_UP))
	{
		g_EventManager->CallEvent(EEvent::E_EventMovePlayer2, NULL);
		std::cout << "up" << std::endl;
	}
	if (InputManager->IsKeyPressed(VK_LEFT))
	{
		g_EventManager->CallEvent(EEvent::E_EventMovePlayer2, NULL);
		std::cout << "left" << std::endl;
	}
	if (InputManager->IsKeyPressed(VK_DOWN))
	{
		g_EventManager->CallEvent(EEvent::E_EventMovePlayer2, NULL);

		std::cout << "down" << std::endl;
	}
	if (InputManager->IsKeyPressed(VK_RIGHT))
	{
		g_EventManager->CallEvent(EEvent::E_EventMovePlayer2, NULL);

		std::cout << "right" << std::endl;
	}
	if (InputManager->IsKeyPressed(VK_RCONTROL))
	{
		std::cout << "rCtrl" << std::endl;
	}

	/*if(GetAsyncKeyState(VK_RCONTROL) & 0x8000)
	{
		std::cout << "right control" << std::endl;
	}*/

}

void CKeyboard::PressKey(WPARAM keyID, LPARAM lParam)
{
	WPARAM new_vk = keyID;
	UINT scancode = (lParam & 0x00ff0000) >> 16;
	int extended = (lParam & 0x01000000) != 0;

	switch (keyID)
	{
	case VK_SHIFT:
		new_vk = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
		break;
		
	case VK_PROCESSKEY:
	case VK_HANJA:
		new_vk = extended ? VK_RCONTROL : VK_LCONTROL;
		break;
		
	case VK_MENU:
		new_vk = extended ? VK_RMENU : VK_LMENU;
		break;
	default:
		new_vk = keyID;
		break;
	}

	m_dwPrevKey = new_vk;
	m_eKeyState = E_BTNDOWN;
	m_mapKey[new_vk] = true;
}

void CKeyboard::ReleaseKey(WPARAM keyID, LPARAM lParam)
{
	WPARAM new_vk = keyID;
	UINT scancode = (lParam & 0x00ff0000) >> 16;
	int extended = (lParam & 0x01000000) != 0;

	switch (keyID)
	{
	case VK_SHIFT:
		new_vk = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
		break;
		
	case VK_PROCESSKEY:
	case VK_HANJA:
		new_vk = extended ? VK_RCONTROL : VK_LCONTROL;
		break;
		
	case VK_MENU:
		new_vk = extended ? VK_RMENU : VK_LMENU;
		break;
	default:
		new_vk = keyID;
		break;
	}
	
	m_eKeyState = E_BTNUP;
	m_mapKey[new_vk] = false;
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