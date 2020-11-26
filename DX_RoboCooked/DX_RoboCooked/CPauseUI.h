#pragma once
#include "CUI.h"

class CUI;

class CPauseUI :
	public CUI
{
	enum EVENT
	{
		EN_BODY = 0 ,EN_OK,EN_CANCEL,EN_EXIT
	};

	
public:
	CPauseUI();
	~CPauseUI();

	

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

