#include "stdafx.h"
#include "CMainGame.h"
#include "CGrid.h"
#include "CCamera.h"
#include "CGameScene.h"
#include "CParts.h"

/* µð¹ö±ë¿ë */
#include "CDebugPlayer1.h"
#include "CDebugPlayer2.h"

CMainGame::CMainGame()
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pScene(NULL)
	, m_pDebugSphere(NULL)
	, m_pDebugCube(NULL)
	, m_pDebugParts(NULL)
{
}


CMainGame::~CMainGame()
{
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);

	g_pFontManager->Destroy();
	g_pDeviceManager->Destroy(); 
}

void CMainGame::Setup()
{
	m_pGrid = new CGrid;
	if (m_pGrid)
		m_pGrid->Setup();

	m_pCamera = new CCamera;
	if (m_pCamera)
		m_pCamera->Setup(NULL);

	m_pDebugSphere = new CDebugPlayer1;
	if (m_pDebugSphere)
		m_pDebugSphere->Setup();

	m_pDebugCube = new CDebugPlayer2;
	if (m_pDebugCube)
		m_pDebugCube->Setup();

	m_pDebugParts = new CParts;
	if (m_pDebugParts)
		m_pDebugParts->Setup();

	m_pScene = new CGameScene;
	g_SceneManager->AddScene("GAMESCENE",m_pScene);
	g_SceneManager->SetCurrentScene(m_pScene);

	//g_EventManager->CallEvent(EEvent::E_EventTile, NULL);
}

void CMainGame::Update()
{
	InputManager->Update();
	
	if (m_pCamera)
		m_pCamera->Update();

	if (m_pScene)
		m_pScene->Update();

	if (m_pDebugCube)
		m_pDebugCube->Update();

	if (m_pDebugSphere)
		m_pDebugSphere->Update();
}

void CMainGame::Render()
{
	if (g_pD3DDevice)
		g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(45, 45, 48), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	if (m_pCamera)
		m_pCamera->Render();
	
	if (m_pGrid)
		m_pGrid->Render();

	if (m_pScene)
		m_pScene->Render();

	if (m_pDebugSphere)
		m_pDebugSphere->Render();

	if (m_pDebugCube)
		m_pDebugCube->Render();

	if (m_pDebugParts)
		m_pDebugParts->Render();
	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	InputManager->WndProc(hWnd, message, wParam, lParam);
	
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
