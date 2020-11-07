#pragma once

class CGrid;
class CCamera;

class CMainGame
{
private:
	CGrid*					m_pGrid;
	CCamera*				m_pCamera;

public:
	CMainGame();
	~CMainGame();

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	

};

