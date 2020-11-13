#pragma once


class CGrid;
class CCamera;
class CScene;

/* µð¹ö±ë¿ë */
class CDebugPlayer1;
class CDebugPlayer2;

class CMainGame
{
private:
	CGrid*					m_pGrid;
	CCamera*				m_pCamera;
	CScene*					m_pScene;

	

	/* µð¹ö±ë¿ë */
	CDebugPlayer1*			m_pDebugSphere;
	CDebugPlayer2*				m_pDebugCube;
public:
	CMainGame();
	~CMainGame();

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	

};

