#include "stdafx.h"
#include "Keyboard.h"


CKeyboard::CKeyboard()
	:m_elapsedTime(0)
	,m_dwPrevKey(0)
{
	m_eKeyState = E_NONE;

	m_arrBaseInputKey[0].moveFowardKey = 'W';
	m_arrBaseInputKey[0].moveLeftKey = 'A';
	m_arrBaseInputKey[0].moveBackKey = 'S';
	m_arrBaseInputKey[0].moveRightKey = 'D';
	m_arrBaseInputKey[0].interactableKey1 = 'F';
	m_arrBaseInputKey[0].interactableKey2 = 'G';
	m_arrBaseInputKey[0].interactableKey3 = 'H';

	m_arrBaseInputKey[1].moveFowardKey = VK_UP;
	m_arrBaseInputKey[1].moveLeftKey = VK_LEFT;
	m_arrBaseInputKey[1].moveBackKey = VK_DOWN;
	m_arrBaseInputKey[1].moveRightKey = VK_RIGHT;
	m_arrBaseInputKey[1].interactableKey1 = VK_OEM_COMMA;
	m_arrBaseInputKey[1].interactableKey2 = VK_OEM_PERIOD;
	m_arrBaseInputKey[1].interactableKey3 = VK_OEM_2;

	m_arrInputKey = m_arrBaseInputKey;
	g_EventManager->CallEvent(eEvent::Player1KeyChange, (void*)&m_arrInputKey[0]);
	g_EventManager->CallEvent(eEvent::Player2KeyChange, (void*)&m_arrInputKey[1]);
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
		//std::cout << *it << std::endl;
		g_EventManager->CallEvent(eEvent::KeyPress, (void*)&data);
	}
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

	/*while (m_eKeyState == E_BTNDOWN)
	{
		DWORD currentTime = GetTickCount();

		if (currentTime - m_elapsedTime < 500 && keyID == m_dwPrevKey && m_eKeyState == E_BTNUP)
		{
			std::cout << "È¦µå" << std::endl;
			m_eKeyState = E_HOLD;
		}
		m_elapsedTime = GetTickCount();
	}*/
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
	ST_KeyInputEvent data{ new_vk };
	g_EventManager->CallEvent(eEvent::KeyRelease, (void*)&data);
}

void CKeyboard::OnEvent(eEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case eEvent::Player1KeyChange:
		SetKeyChange(1, _value);
		break;
	case eEvent::Player2KeyChange:
		SetKeyChange(2, _value);
		break;
	}
}

void CKeyboard::SetKeyChange(int n, void* _value)
{
	ST_PLAYER_INPUTKEY *data = static_cast<ST_PLAYER_INPUTKEY*>(_value);
	m_arrInputKey[n - 1] = *data;
}

void CKeyboard::Reset()
{
	m_arrInputKey = m_arrBaseInputKey;
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