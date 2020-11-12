#pragma once


class CGrid;
class CCamera;
class CScene;

/* µð¹ö±ë¿ë */
class CDebugSphere;
class CDebugCube;

class CMainGame
{
private:
	CGrid*					m_pGrid;
	CCamera*				m_pCamera;
	CScene*					m_pScene;

	

	/* µð¹ö±ë¿ë */
	CDebugSphere*			m_pDebugSphere;
	CDebugCube*				m_pDebugCube;
public:
	CMainGame();
	~CMainGame();

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	

};

