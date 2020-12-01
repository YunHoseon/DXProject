#include "stdafx.h"
#include "CMainGame.h"
#include "CGrid.h"
#include "CCamera.h"
#include "CGameScene.h"
#include "CParts.h"

CMainGame::CMainGame()
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	//, m_pScene(NULL)
{
}


CMainGame::~CMainGame()
{
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);

	g_pUITextureManager->Destroy();
	g_pTextureManager->Destroy();
	g_SceneManager->Destroy();
	g_SoundManager->Destroy();
	g_pFontManager->Destroy();
	g_pDeviceManager->Destroy(); 
}

void CMainGame::Setup()
{
	SetLight();
	InputManager;
	g_pPartsManager;
	m_pGrid = new CGrid;
	if (m_pGrid)
		m_pGrid->Setup();

	m_pCamera = new CCamera;
	if (m_pCamera)
		m_pCamera->Setup(NULL);

	//m_pScene = new CGameScene;
	//g_SceneManager->AddScene("GAMESCENE", new CGameScene);
	g_SceneManager->SetCurrentScene(new CGameScene);
	//g_pPartsManager->GetPartsData("data/js/PartsData.json");
}

void CMainGame::Update()
{
	g_pTimeManager->Update();
	
	InputManager->Update();
	
	if (m_pCamera)
		m_pCamera->Update();

	g_SceneManager->GetCurrentScene()->Update();
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

	//if (m_pScene)
	//	m_pScene->Render();
	g_SceneManager->GetCurrentScene()->Render();

	/*if (m_pDebugParts)
		m_pDebugParts->Render();
	*/
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	InputManager->WndProc(hWnd, message, wParam, lParam);
	
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void CMainGame::SetLight()
{
	D3DLIGHT9	stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3 vDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
}