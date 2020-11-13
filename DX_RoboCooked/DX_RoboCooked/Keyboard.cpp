#include "stdafx.h"
#include "Keyboard.h"


CKeyboard::CKeyboard()
	:m_elapsedTime(0)
	,m_dwPrevKey(0)
{
	m_eKeyState = E_NONE;

	m_stInputKey[0].moveFowardKey = 'W';
	m_stInputKey[0].moveLeftKey = 'A';
	m_stInputKey[0].moveBackKey = 'S';
	m_stInputKey[0].moveRightKey = 'D';
	m_stInputKey[0].interactableKey1 = 'F';
	m_stInputKey[0].interactableKey2 = 'G';
	m_stInputKey[0].interactableKey3 = 'H';

	m_stInputKey[1].moveFowardKey = VK_UP;
	m_stInputKey[1].moveLeftKey = VK_LEFT;
	m_stInputKey[1].moveBackKey = VK_BACK;
	m_stInputKey[1].moveRightKey = VK_RIGHT;
	m_stInputKey[1].interactableKey1 = VK_OEM_COMMA;
	m_stInputKey[1].interactableKey2 = VK_OEM_PERIOD;
	m_stInputKey[1].interactableKey3 = VK_OEM_2;

	g_EventManager->CallEvent(EEvent::E_Player1KeyChange, (void*)&m_stInputKey[0]);
	g_EventManager->CallEvent(EEvent::E_Player2KeyChange, (void*)&m_stInputKey[1]);
}

CKeyboard::~CKeyboard()
{
}

void CKeyboard::Update()
 {
	ST_KeyInputEvent data;

	unordered_set<WPARAM>::iterator it;
	for(it = m_setKey.begin(); it != m_setKey.end(); it++)
	{
		data.wKey = *it;
		std::cout << *it << std::endl;
		g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
	}

	/*{
		if (InputManager->IsKeyPressed('W'))
		{
			data.wKey = 'W';
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << "W" << std::endl;
		}
		if (InputManager->IsKeyPressed('A'))
		{
			data.wKey = 'A';
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << "A" << std::endl;
		}
		if (InputManager->IsKeyPressed('S'))
		{
			data.wKey = 'S';
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << "S" << std::endl;
		}
		if (InputManager->IsKeyPressed('D'))
		{
			data.wKey = 'D';
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << "D" << std::endl;
		}
		if (InputManager->IsKeyPressed('F'))
		{
			data.wKey = 'F';
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << "F" << std::endl;
		}
		if (InputManager->IsKeyPressed('G'))
		{
			data.wKey = 'G';
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << "g" << std::endl;
		}
		if (InputManager->IsKeyPressed('H'))
		{
			data.wKey = 'H';
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << "H" << std::endl;
		}
	}

	{
		if (InputManager->IsKeyPressed(VK_UP))
		{
			data.wKey = VK_UP;
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << "up" << std::endl;
		}
		if (InputManager->IsKeyPressed(VK_LEFT))
		{
			data.wKey = VK_LEFT;
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << "left" << std::endl;
		}
		if (InputManager->IsKeyPressed(VK_DOWN))
		{
			data.wKey = VK_DOWN;
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << "down" << std::endl;
		}
		if (InputManager->IsKeyPressed(VK_RIGHT))
		{
			data.wKey = VK_RIGHT;
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << "right" << std::endl;
		}
		if (InputManager->IsKeyPressed('<'))
		{
			data.wKey = '<';
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);\
			std::cout << "<" << std::endl;
		}
		if (InputManager->IsKeyPressed('>'))
		{
			data.wKey = '>';
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << ">" << std::endl;
		}
		if (InputManager->IsKeyPressed('?'))
		{
			data.wKey = '?';
			g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
			std::cout << "?" << std::endl;
		}
	}
	
	if (InputManager->IsKeyPressed(VK_CONTROL))
	{
		data.wKey = VK_RCONTROL;
		g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
		std::cout << "lCtrl" << std::endl;
	}
	
	if (InputManager->IsKeyPressed(VK_RCONTROL))
	{
		data.wKey = VK_RCONTROL;
		g_EventManager->CallEvent(EEvent::E_KeyPress, (void*)&data);
		std::cout << "rCtrl" << std::endl;
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

	m_setKey.insert(new_vk);
	m_dwPrevKey = new_vk;
	m_eKeyState = E_BTNDOWN;
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

	m_setKey.erase(new_vk);
	m_eKeyState = E_BTNUP;
	g_EventManager->CallEvent(EEvent::E_KeyRelease, NULL);
}

void CKeyboard::OnEvent(EEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case EEvent::E_Player1KeyChange:
		SetKeyChange(1, _value);
		break;
	case EEvent::E_Player2KeyChange:
		SetKeyChange(2, _value);
		break;
	}
}

void CKeyboard::SetKeyChange(int n, void* _value)
{
	memcpy(&m_stInputKey[n-1], &_value, sizeof(ST_PLAYER_INPUTKEY));
}

//void CKeyboard::JudgeDash(WPARAM keyID)
//{
//	DWORD currentTime = GetTickCount();
//
//	if (currentTime - m_elapsedTime < 500 && keyID == m_dwPrevKey && m_eKeyState == E_BTNUP)
//	{
//		std::cout << "´ë½¬" << std::endl;
//		m_eKeyState = E_DBLDOWN;
//	}
//	m_elapsedTime = GetTickCount();
//}