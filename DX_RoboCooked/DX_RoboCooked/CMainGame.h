#pragma once
class CGrid;
class CCamera;
class CScene;

class CMainGame
{
private:
	CGrid*					m_pGrid;
	CCamera*				m_pCamera;
	CScene*					m_pScene;

public:
	CMainGame();
	~CMainGame();

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	void SetLight();
};

