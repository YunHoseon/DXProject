#include "stdafx.h"
#include "CMainGame.h"
#include "CGrid.h"
#include "CCamera.h"
#include "CGameScene.h"
#include "CMainScene.h"

CMainGame::CMainGame()
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	//, m_pScene(NULL)
{
	//Sound Add
	//g_SoundManager->AddBGM("data/sound/bgm.mp3");
	g_SoundManager->AddSFX("data/sound/effBBam.mp3", "BBam");
	g_SoundManager->AddSFX("data/sound/effMelem.mp3", "Melem");

	g_SoundManager->AddSFX("data/sound/sfx/click.mp3", "click");
	g_SoundManager->AddSFX("data/sound/sfx/win.mp3", "win");
	g_SoundManager->AddSFX("data/sound/sfx/game_over.mp3", "game_over");
	g_SoundManager->AddSFX("data/sound/sfx/siren.mp3", "siren");

	g_SoundManager->AddSFX("data/sound/player/run_1.mp3", "run_1");
	g_SoundManager->AddSFX("data/sound/player/dash.mp3", "dash");
	g_SoundManager->AddSFX("data/sound/player/charge_up.mp3", "charge_up");
	g_SoundManager->AddSFX("data/sound/player/charge_complete.mp3", "charge_complete");
	g_SoundManager->AddSFX("data/sound/player/throw.mp3", "throw");

	g_SoundManager->AddSFX("data/sound/object/character_impact.mp3", "character_impact");
	g_SoundManager->AddSFX("data/sound/object/part_f.mp3", "part_f");
	g_SoundManager->AddSFX("data/sound/object/part_impact.mp3", "part_impact");
	g_SoundManager->AddSFX("data/sound/object/machine_run.mp3", "machine_run");
	g_SoundManager->AddSFX("data/sound/object/machine_complete.mp3", "machine_complete");
	g_SoundManager->AddSFX("data/sound/object/box.mp3", "box");
	g_SoundManager->AddSFX("data/sound/object/button.mp3", "button");

	g_SoundManager->AddSFX("data/sound/monster/medusa_snake_01.mp3", "medusa_snake_01");
	g_SoundManager->AddSFX("data/sound/monster/medusa_snake_02.mp3", "medusa_snake_02");
	g_SoundManager->AddSFX("data/sound/monster/medusa_ult.mp3", "medusa_ult");

	g_SoundManager->AddSFX("data/sound/monster/heartbeat.mp3", "heartbeat");
	g_SoundManager->AddSFX("data/sound/monster/wind.mp3", "wind");
	g_SoundManager->AddSFX("data/sound/monster/tornado.mp3", "tornado");
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
	
	_DEBUG_COMMENT m_pGrid = new CGrid;
	if (m_pGrid)
		m_pGrid->Setup();

	m_pCamera = new CCamera;
	if (m_pCamera)
		m_pCamera->Setup(NULL);

	/*CGameScene* scene = new CGameScene;
	thread _t1(&CGameScene::Load, scene, "data/js", "AllTest.json", &CGameScene::Init);
	_t1.detach();
	
	CScene* pBeforeScene = g_SceneManager->SetCurrentScene(scene);
	if (pBeforeScene)
	{
		thread _t2([pBeforeScene]() { delete pBeforeScene; });
		_t2.detach();
	}*/

	CMainScene* scene = new CMainScene;

	CScene* pBeforeScene = g_SceneManager->SetCurrentScene(scene);
	if (pBeforeScene)
	{
		thread _t2([pBeforeScene]() { delete pBeforeScene; });
		_t2.detach();
	}
}

void CMainGame::Update()
{
	g_pTimeManager->Update();
	InputManager->Update();
	
	if (m_pCamera)
		m_pCamera->Update();

	g_SceneManager->Update();
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
	g_SceneManager->Render();

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