#include "stdafx.h"
#include "CMainGame.h"
#include "CGrid.h"
#include "CCamera.h"
#include "CGameScene.h"

/* µð¹ö±ë¿ë */
#include "CDebugSphere.h"
#include "CDebugCube.h"

CMainGame::CMainGame()
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pScene(NULL)
	, m_pDebugSphere(NULL)
	, m_pDebugCube(NULL)
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

	m_pDebugSphere = new CDebugSphere;
	if (m_pDebugSphere)
		m_pDebugSphere->Setup();

	m_pDebugCube = new CDebugCube;
	if (m_pDebugCube)
		m_pDebugCube->Setup();

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
	
}

void CMainGame::Render()
{
	if (g_pD3DDevice)
		g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(45, 45, 48), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();

	if (m_pScene)
		m_pScene->Render();

	if (m_pDebugSphere)
		m_pDebugSphere->Render();

	if (m_pDebugCube)
		m_pDebugCube->Render();
	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	InputManager->WndProc(hWnd, message, wParam, lParam);
	
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
