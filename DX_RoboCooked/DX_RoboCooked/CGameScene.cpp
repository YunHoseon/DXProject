#include "stdafx.h"
#include "CGameScene.h"
#include "CField.h"
#include "CInteractiveActor.h"
#include "CParts.h"
#include "CPartStorage.h"
#include "ICollisionArea.h"
#include "CActor.h"
#include "CCharacter.h"
#include "CPartCombinator.h"
#include "CCombinatorButton.h"
#include "CPartManualCombinator.h"
#include "CPartAutoCombinator.h"
#include "COutlet.h"
#include "CPartVending.h"
#include "CPhysicsApplyer.h"
#include "CWall.h"
#include "CUIButton.h"
#include "CBlueprint.h"
#include "CMonster.h"
#include "CPharaohCoffin.h"
#include "CTV.h"
#include "CWhiteboard.h"
#include "CTile.h"
#include "CCrowdControl.h"

#include "CTipBoard.h"
#include "CTornado.h"
#include "CSandpile.h"

#include "CUILoseButton.h"
#include "CUIClearButton.h"
#include "CUIPauseButton.h"
#include "CUITrafficLight.h"
#include "CUILoading.h"
#include "CUIReady.h"
#include "CUIWarning.h"
#include "CUIEsc.h"

/* ������ */
#include <filesystem>
#include <fstream>
#include <locale>
#include <codecvt>

#include "CBoundaryWall.h"

std::mutex CGameScene::m_cMutex;

#include "CCactus.h"
#include "CDebugPlayer1.h"
#include "CDebugPlayer2.h"

CGameScene::CGameScene() : 
						   m_pDebugLoseUI(nullptr),
						   m_pDebugClearUI(nullptr),
						   m_pDebugPauseUI(nullptr),
						   m_pDebugTrafficLight(nullptr),
						   m_pLoadingPopup(nullptr),
						   m_isTimeStop(false),
						   m_vWind(0, 0, 0),
						   m_fGameTime(300.0f),
						   m_pReady(nullptr),
						   m_pWarnning(nullptr),
						   m_pEscUI(nullptr)
{
	g_SoundManager->AddBGM("data/Sound/bgm/Tribal_Tensions.mp3");
	g_SoundManager->PlayBGM();

	g_EventManager->Attach(eEvent::Tick, this);
	// 로딩 UI
	CUILoading *pLoadingPopup = new CUILoading(this);
	m_pLoadingPopup = pLoadingPopup;
}

CGameScene::~CGameScene()
{
	m_cMutex.lock();
	for (CActor *it : m_vecStaticActor)
	{
		SafeDelete(it);
	}

	for (CInteractiveActor *it : m_vecObject)
	{
		SafeDelete(it);
	}

	for (CInteractiveActor *it : m_vecParts)
	{
		SafeDelete(it);
	}

	for (CCharacter *it : m_vecCharacters)
	{
		SafeDelete(it);
	}
	for (CMonster *it : m_vecMonster)
	{
		SafeDelete(it);
	}

	for (CTile *it : m_vecTile)
	{
		SafeDelete(it);
	}

	for (CBlueprint *it : m_vecBlueprints)
	{
		SafeDelete(it);
	}
	SafeDelete(m_pDebugPauseUI);
	SafeDelete(m_pDebugTrafficLight);
	SafeDelete(m_pDebugClearUI);
	SafeDelete(m_pLoadingPopup);
	SafeDelete(m_pDebugLoseUI);
	SafeDelete(m_pReady);
	SafeDelete(m_pWarnning);
	SafeDelete(m_pEscUI);
	m_cMutex.unlock();
}

void CGameScene::Init()
{
	CWall *wall = new CWall(this, true);
	//CBoundaryWall* pBwall = new CBoundaryWall;
	CUIButton *pClearButton = new CUIClearButton(D3DXVECTOR2(465, 10), this);
	CUIButton *pPauseButton = new CUIPauseButton(D3DXVECTOR2(465, 10), 27, this);
	CUIButton *pLoseButton = new CUILoseButton(D3DXVECTOR2(465, 10), this);
	CUITrafficLight *pTrafficLight = new CUITrafficLight(this, m_vecBlueprints.size());
	CUIButton *pReady = new CUIReady(D3DXVECTOR2(675, 450), this);
	CUIButton *pEsc = new CUIEsc;
	CUIWarning *pWarrning = new CUIWarning;


	m_cMutex.lock();
	m_fGameTime = 300.0f;
	m_vecStaticActor.push_back(wall);
	
	m_pEscUI = pEsc;
	m_pWarnning = pWarrning;
	m_pReady = pReady;
	m_pDebugPauseUI = pPauseButton;
	m_pDebugLoseUI = pLoseButton;
	m_pDebugClearUI = pClearButton;
	m_pDebugTrafficLight = pTrafficLight;
	
	m_cMutex.unlock();
}

void CGameScene::Render()
{
	D3DXMATRIXA16 matView, matProjection;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
	g_pRenderShadowManager->SetWorldLightPosition(D3DXVECTOR4(20.f, 40.0f, 20.0f, 1.0f));
	D3DXMATRIXA16 matViewProjection;
	D3DXMatrixMultiply(&matViewProjection, &matView, &matProjection);

	m_cMutex.lock();
	// CreateShadow
	{

		LPDIRECT3DSURFACE9 pHWBackBuffer = NULL;
		LPDIRECT3DSURFACE9 pHWDepthStencilBuffer = NULL;
		g_pD3DDevice->GetRenderTarget(0, &pHWBackBuffer);
		g_pD3DDevice->GetDepthStencilSurface(&pHWDepthStencilBuffer);

		LPDIRECT3DSURFACE9 pShadowSurface;
		pShadowSurface = NULL;

		if (SUCCEEDED(g_pRenderShadowManager->GetShadowRenderTarget()->GetSurfaceLevel(0, &pShadowSurface)))
		{
			g_pD3DDevice->SetRenderTarget(0, pShadowSurface);
			pShadowSurface->Release();
			pShadowSurface = NULL;
		}
		g_pD3DDevice->SetDepthStencilSurface(g_pRenderShadowManager->GetShadowDepthStencil());

		g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), 0xFFFFFFFF, 1.0f, 0);
		g_pRenderShadowManager->CalAndSetLightView();
		g_pRenderShadowManager->CalAndSetLightProjection();
		g_pRenderShadowManager->GetCreateShadowShader()->SetVector("gWorldLightPosition", &g_pRenderShadowManager->GetWorldLightPosition());
		for (CCharacter* it : m_vecCharacters)
		{
			it->CreateShadowMap();
		}
		for (CActor* it : m_vecStaticActor)
		{
			it->CreateShadowMap();
		}
		for (CTile* it : m_vecTile)
		{
			it->CreateShadowMap();
		}
		for (CInteractiveActor* it : m_vecObject)
		{
			it->CreateShadowMap();
		}
		for (CParts* it : m_vecParts)
		{
			it->CreateShadowMap();
		}

		g_pD3DDevice->SetRenderTarget(0, pHWBackBuffer);
		g_pD3DDevice->SetDepthStencilSurface(pHWDepthStencilBuffer);
		pHWBackBuffer->Release();
		pHWBackBuffer = NULL;
		pHWDepthStencilBuffer->Release();
		pHWDepthStencilBuffer = NULL;
	}

	// ApplyShadow
	{
		if (g_pRenderShadowManager->GetApplyShadowShader())
		{

			g_pRenderShadowManager->GetApplyShadowShader()->SetMatrix("gViewProjectionMatrix", &matViewProjection);
			g_pRenderShadowManager->GetApplyShadowShader()->SetVector("gWorldLightPosition", &g_pRenderShadowManager->GetWorldLightPosition());

			g_pRenderShadowManager->GetApplyShadowShader()->SetTexture(
				"ShadowMap_Tex", g_pRenderShadowManager->GetShadowRenderTarget());
		}
		
		for (CTile *it : m_vecTile)
		{
			it->Render();
		}
		
		for (CCharacter* it : m_vecCharacters)
		{
			it->Render();
		}

		for (CParts *it : m_vecParts)
		{
			it->Render();
		}
		
		for (CInteractiveActor *it : m_vecObject)
		{
			it->Render();
		}


		for (CBlueprint *it : m_vecBlueprints)
		{
			it->Render();
		}


		for (CActor* it : m_vecStaticActor)
		{
			it->Render();
		}
	
		for (CMonster *it : m_vecMonster)
		{
			it->Render();
		}
	}
	
	if (m_pDebugTrafficLight)
		m_pDebugTrafficLight->Render();

	if (m_pDebugLoseUI)
		m_pDebugLoseUI->Render();

	if (m_pDebugPauseUI)
		m_pDebugPauseUI->Render();

	if (m_pDebugClearUI)
		m_pDebugClearUI->Render();

	if (m_pEscUI)
		m_pEscUI->Render();

	if (m_pLoadingPopup)
		m_pLoadingPopup->Render();

	if (m_pReady)
		m_pReady->Render();

	if (m_pWarnning)
		m_pWarnning->Render();

	

	m_cMutex.unlock();
}

void CGameScene::Update()
{
	if (m_isTimeStop)
		return;

	{
		for (CCharacter *character : m_vecCharacters)
		{
			CPhysicsApplyer::ApplyGravity(character);
		}

		for (CParts *part : m_vecParts)
		{
			CPhysicsApplyer::ApplyGravity(part);
		}
	}

	{
		for (CCharacter *character : m_vecCharacters)
		{
			character->AddForce(m_vWind * TimeRevision);
		}

		for (CParts *part : m_vecParts)
		{
			part->AddForce(m_vWind * TimeRevision);
		}
	}

	{
		for (CMonster *monster : m_vecMonster)
		{
			for (CCharacter *character : m_vecCharacters)
			{
				monster->AddForce(character);
			}
		}
	}

	// collide -> update
	{ // collide
		if (m_vecCharacters.size() == 2)
		{
			if (CPhysicsApplyer::ApplyBound(m_vecCharacters[0], m_vecCharacters[1]))
			{
				if (ColideCheck(m_vecCharacters[0], m_vecCharacters[1]))
				{
					g_SoundManager->PlaySFX("character_impact");
				}
			}
			else
			{
				m_vecCharacters[0]->SetIsCollide(false);
				m_vecCharacters[1]->SetIsCollide(false);
			}
		}

		for (CParts *part : m_vecParts)
		{
			for (CCharacter *character : m_vecCharacters)
			{
				CPhysicsApplyer::ApplyBound(character, part);
			}
			for (CParts *part2 : m_vecParts)
			{
				if (part != part2)
				{
					if (CPhysicsApplyer::ApplyBound(part2, part))
					{
						if (ColideCheck(part2, part))
						{
							g_SoundManager->PlaySFX("part_impact");
						}
					}
					else
					{
						part->SetIsCollide(false);
						part2->SetIsCollide(false);
					}

				}
			}
		}

		for (CInteractiveActor *obj : m_vecObject)
		{
			for (CCharacter *character : m_vecCharacters)
			{
				CPhysicsApplyer::ApplyBound(obj, character);
			}
			for (CParts *part : m_vecParts)
			{
				CPhysicsApplyer::ApplyBound(obj, part);
			}
		}

		for (CActor *pStaticActor : m_vecStaticActor)
		{
			for (CCharacter *character : m_vecCharacters)
			{
				CPhysicsApplyer::ApplyBound(pStaticActor, character);
			}
			for (CParts *part : m_vecParts)
			{
				CPhysicsApplyer::ApplyBound(pStaticActor, part);
			}
		}
		
		for (CTile *tile : m_vecTile)
		{
			D3DXVECTOR3 min, max;
			float dist;
			tile->GetCollision()->GetMinMax(&min, &max);
			for (CCharacter *character : m_vecCharacters)
			{
				if (D3DXVec3LengthSq(&(character->GetPosition() - tile->GetPosition())) < 5.f)
				{
					if (
						D3DXBoxBoundProbe(&min, &max, &character->GetPosition(), &D3DXVECTOR3(1, 0, 0)) ||
						D3DXBoxBoundProbe(&min, &max, &character->GetPosition(), &D3DXVECTOR3(-1, 0, 0)) ||
						D3DXBoxBoundProbe(&min, &max, &character->GetPosition(), &D3DXVECTOR3(0, 1, 0)) ||
						D3DXBoxBoundProbe(&min, &max, &character->GetPosition(), &D3DXVECTOR3(0, -1, 0)) ||
						D3DXBoxBoundProbe(&min, &max, &character->GetPosition(), &D3DXVECTOR3(0, 0, 1)) ||
						D3DXBoxBoundProbe(&min, &max, &character->GetPosition(), &D3DXVECTOR3(0, 0, -1)))
					{
						CPhysicsApplyer::ApplyBound(tile, character);
					}
				}
			}

			for (CParts *part : m_vecParts)
			{
				if (D3DXVec3LengthSq(&(tile->GetPosition() - tile->GetPosition())) < 5.f)
				{
					if (
						D3DXBoxBoundProbe(&min, &max, &part->GetPosition(), &D3DXVECTOR3(1, 0, 0)) ||
						D3DXBoxBoundProbe(&min, &max, &part->GetPosition(), &D3DXVECTOR3(-1, 0, 0)) ||
						D3DXBoxBoundProbe(&min, &max, &part->GetPosition(), &D3DXVECTOR3(0, 1, 0)) ||
						D3DXBoxBoundProbe(&min, &max, &part->GetPosition(), &D3DXVECTOR3(0, -1, 0)) ||
						D3DXBoxBoundProbe(&min, &max, &part->GetPosition(), &D3DXVECTOR3(0, 0, 1)) ||
						D3DXBoxBoundProbe(&min, &max, &part->GetPosition(), &D3DXVECTOR3(0, 0, -1)))
					{
						CPhysicsApplyer::ApplyBound(tile, part);
					}
				}
			}
		}

		for (CBlueprint *blueprint : m_vecBlueprints)
		{
			for (CCharacter *character : m_vecCharacters)
			{
				CPhysicsApplyer::ApplyBound(character, blueprint);
			}
		}
	}
	{ // update
		for (CActor *it : m_vecStaticActor)
		{
			it->Update();
		}

		for (int i = 0; i < m_vecParts.size(); ++i)
		{
			m_vecParts[i]->Update();

			if (m_vecParts[i]->GetPosition().y < -150)
			{
				DeleteParts(m_vecParts[i]);
				--i;
			}
		}

		for (CInteractiveActor *it : m_vecObject)
		{
			it->Update();
		}

		for (CBlueprint *it : m_vecBlueprints)
		{
			it->Update();
		}

		for (CMonster *it : m_vecMonster)
		{
			it->Update();
		}

		for (CCharacter *character : m_vecCharacters)
		{
			character->Update();
		}
	}
}

bool CGameScene::OnEvent(eEvent eEvent, void *_value)
{
	switch (eEvent)
	{
	case eEvent::Tick:
		if (m_isTimeStop)
			break;
		return TickUpdate(_value);
	}
	return true;
}

bool CGameScene::TickUpdate(void *_value)
{
	ST_TickEvent *data = static_cast<ST_TickEvent *>(_value);
	m_fGameTime -= data->fElapsedTime;

	int check = IsGameClear();
	if (check == 1)
	{
		g_SoundManager->PlaySFX("win");
		ST_SetTimeEvent timeData;
		timeData.nTime = m_fGameTime;

		m_isTimeStop = true;
		SafeDelete(m_pDebugPauseUI);
		g_EventManager->CallEvent(eEvent::ClearSetTime, (void *)&timeData);
		//g_SaveLoadManager->Save(m_sStageKey, true, m_fGameTime);

		json& jData = g_SaveLoadManager->GetStageData(m_sStageKey);
		jData["isClear"] = true;
		jData["ClearTime"] = m_fGameTime;
		g_SaveLoadManager->Save();
		


		//세이브 체크중
		if (m_pDebugClearUI)
			m_pDebugClearUI->ActiveUI();

		return false;
	}
	else if (check == 2)
	{
		g_SoundManager->PlaySFX("game_over");

		m_isTimeStop = true;
		SafeDelete(m_pDebugPauseUI);

		if (m_pDebugLoseUI)
			m_pDebugLoseUI->ActiveUI();
		return false;
	}
	
	return true;
}

void CGameScene::Load(string sFolder, string sStageKey, void (CGameScene::*pCallback)(void))
{
	m_cMutex.lock();
	m_isTimeStop = true;
	m_cMutex.unlock();

	m_sStageKey = sStageKey;
	json jData = g_SaveLoadManager->GetStageData(sStageKey);
	string FileName = jData["FileName"];
	string sFullname = sFolder + "/" + FileName;
	
	std::ifstream is(sFullname);
	assert(is.is_open());
	json j;
	is >> j;
	is.close();
	vector<CBlueprint *> vecBP;
	vector<CActor *> vecStatic;
	vector<CInteractiveActor *> vecInter;
	vector<CParts *> vecParts;
	vector<CCharacter *> vecChara;
	vector<CTile *> vecTile;
	vector<CMonster *> vecMonster;

	while(!g_pStaticMeshManager->IsLoaded()){} // 메시 로딩이 끝날때까지 busylock
	if (g_pThreadManager->GetStopMessage()) return;
	{
		{
			// blueprint
			json jBP = j["Blueprint"];
			for (auto&& p : jBP)
			{
				string id = p["PartsID"];
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				float partsangle = p["PartsAngle"];
				CBlueprint* blueprint = new CBlueprint(id, m_vecParts, pos, scale, rotate, partsangle);
				blueprint->Setup();
				vecBP.push_back(blueprint);
			}
		}
		{
			json jCactus = j["Cactus"];
			for (auto&& p : jCactus)
			{
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				CCactus* cactus = new CCactus(pos);
				cactus->SetRotationY(rotate);
				cactus->SetScale(scale);
				vecStatic.push_back(cactus);
			}
		}
		{
			json jSandpile = j["Sandpile"];
			for (auto&& p : jSandpile)
			{
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				CSandpile* sandpile = new CSandpile(this, pos);
				sandpile->SetRotationY(rotate);
				sandpile->SetScale(scale);
				vecStatic.push_back(sandpile);
			}
		}
		{
			json jCoffin = j["PharaohCoffin"];
			for (auto&& p : jCoffin)
			{
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				CPharaohCoffin* Coffin = new CPharaohCoffin(this, pos);
				Coffin->SetRotationY(rotate);
				Coffin->SetScale(scale);
				vecInter.push_back(Coffin);
			}
		}
		{
			//outlet - vending
			json jOutlet = j["Outlet"];
			vector<COutlet*> vecOutlet;
			for (auto&& p : jOutlet)
			{
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				COutlet* pOutlet = new COutlet(this);
				pOutlet->SetScale(scale);
				pOutlet->Setup(rotate, pos);
				vecInter.push_back(pOutlet);
				vecOutlet.push_back(pOutlet);
			}
			json jvending = j["PartVending"];
			for (auto&& p : jvending)
			{
				string id = p["PartsId"];
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				CPartVending* vending = new CPartVending(vecOutlet[p["OutletIdx"]], this, id);
				vending->Setup(rotate, pos);
				vending->SetScale(scale);
				vecInter.push_back(vending);
			}
		}
		{
			// manual - switch
			json jManual = j["PartManualCombinator"];
			vector<CPartManualCombinator*> vecManual;
			for (auto&& p : jManual)
			{
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				CPartManualCombinator* manual = new CPartManualCombinator(this, (eCombinatorPartsLevel)p["eCombinatorPartsLevel"], rotate, pos);
				manual->SetScale(scale);
				vecInter.push_back(manual);
				vecManual.push_back(manual);
			}
			json jButton = j["CombinatorButton"];
			for (auto&& p : jButton)
			{
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				CCombinatorButton* button = new CCombinatorButton(vecManual[p["PartManualCombinatorIdx"]]);
				button->Setup(rotate, pos);
				button->SetScale(scale);
				vecInter.push_back(button);
			}
		}
		{
			// auto
			json jAuto = j["PartAutoCombinator"];
			for (auto&& p : jAuto)
			{
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				CPartAutoCombinator* autoCombinator = new CPartAutoCombinator(this, (eCombinatorPartsLevel)p["eCombinatorPartsLevel"], rotate, pos);
				autoCombinator->SetScale(scale);
				vecInter.push_back(autoCombinator);
			}
		}
		{
			// storage
			json jStorage = j["PartStorage"];
			for (auto&& p : jStorage)
			{
				string id = p["PartsId"];
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				CPartStorage* storage = new CPartStorage(this);
				storage->Setup(rotate, pos, id);
				storage->SetScale(scale);
				vecInter.push_back(storage);
			}
		}
		{
			json jField = j["Field"];
			for (int i = 0; i < jField.size(); ++i)
			{
				eTileType eFieldTileType = static_cast<eTileType>(jField[i]["TileType"]);
				CField* field = new CField(eFieldTileType);
				vecStatic.push_back(field);
			}
		}
		{
			json jBoundaryWall = j["BoundaryWall"];
			for (int i = 0; i < jBoundaryWall.size(); ++i)
			{
				CBoundaryWall* bwall = new CBoundaryWall;
				vecStatic.push_back(bwall);
			}
		}
		{
			json jTipboard = j["Tipboard"];
			for (auto&& p : jTipboard)
			{
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				string txt = p["Text"];
				std::wstring_convert < std::codecvt_utf8<wchar_t>, wchar_t> convertString;
				std::wstring wideString = convertString.from_bytes(txt);
				CTipBoard* Tipboard = new CTipBoard(pos, wideString);
				Tipboard->SetRotationY(rotate);
				Tipboard->SetScale(scale);
				vecInter.push_back(Tipboard);
			}
		}
		{
			while (!g_pPartsManager->IsLoaded()) {}
			if (g_pThreadManager->GetStopMessage()) return;
			// parts
			json jParts = j["Parts"];
			for (auto&& p : jParts)
			{
				string id = p["PartsId"];
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				CParts* parts = g_pPartsManager->CreateParts(id);
				parts->SetPosition(pos);
				parts->SetRotationY(rotate);
				parts->SetScale(scale);
				vecParts.push_back(parts);
			}
		}
		{
			// tile
			{
				json jWater = j["Water"];
				for (auto&& p : jWater)
				{
					D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
					float rotate = p["Rotate"];
					D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
					CWater* Tile = new CWater(pos);
					Tile->SetRotationY(rotate);
					Tile->SetScale(scale);
					vecTile.push_back(Tile);
				}
			}
			{
				json jSand = j["Sand"];
				for (auto&& p : jSand)
				{
					D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
					float rotate = p["Rotate"];
					D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
					CSand* Tile = new CSand(pos);
					Tile->SetRotationY(rotate);
					Tile->SetScale(scale);
					vecTile.push_back(Tile);
				}
			}
			{
				json jSoil = j["Soil"];
				for (auto&& p : jSoil)
				{
					D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
					float rotate = p["Rotate"];
					D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
					CSoil* Tile = new CSoil(pos);
					Tile->SetRotationY(rotate);
					Tile->SetScale(scale);
					vecTile.push_back(Tile);
				}
			}
			{
				json jStair = j["Stair"];
				for (auto&& p : jStair)
				{
					D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
					float rotate = p["Rotate"];
					D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
					CStair* Tile = new CStair(pos);
					Tile->SetRotationY(rotate);
					Tile->SetScale(scale);
					vecTile.push_back(Tile);
				}
			}
			{
				json jThickSand = j["ThickSand"];
				for (auto&& p : jThickSand)
				{
					D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
					float rotate = p["Rotate"];
					D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
					CThickSand* Tile = new CThickSand(pos);
					Tile->SetRotationY(rotate);
					Tile->SetScale(scale);
					vecTile.push_back(Tile);
				}
			}
			{
				json jFlowSand = j["FlowSand"];
				for (auto&& p : jFlowSand)
				{
					D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
					float rotate = p["Rotate"];
					D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
					CFlowSand* Tile = new CFlowSand(pos);
					Tile->SetRotationY(rotate);
					Tile->SetScale(scale);
					vecTile.push_back(Tile);
				}
			}
			{
				json jBrick = j["Brick"];
				for (auto&& p : jBrick)
				{
					D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
					float rotate = p["Rotate"];
					D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
					CBrick* Tile = new CBrick(pos);
					Tile->SetRotationY(rotate);
					Tile->SetScale(scale);
					vecStatic.push_back(Tile);
				}
			}
		}
		{
			// player1
			if (!j["Player1"].empty())
			{
				auto&& p = j["Player1"][0];
				CDebugPlayer1* player = new CDebugPlayer1(this);
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				player->SetDefaultPosition(pos);
				player->SetPosition(pos);
				player->SetRotationY(rotate);
				player->SetScale(scale);
				vecChara.push_back(player);
			}
		}
		{
			// player2
			if (!j["Player2"].empty())
			{
				auto&& p = j["Player2"][0];
				CDebugPlayer2* player = new CDebugPlayer2(this);
				D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
				float rotate = p["Rotate"];
				D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
				player->SetDefaultPosition(pos);
				player->SetPosition(pos);
				player->SetRotationY(rotate);
				player->SetScale(scale);
				vecChara.push_back(player);
			}
		}
	}
	// 뮤텍스락
	this->m_cMutex.lock();
	this->m_vecBlueprints.insert(m_vecBlueprints.end(), vecBP.begin(), vecBP.end());
	this->m_vecStaticActor.insert(m_vecStaticActor.end(), vecStatic.begin(), vecStatic.end());
	this->m_vecObject.insert(m_vecObject.end(), vecInter.begin(), vecInter.end());
	this->m_vecParts.insert(m_vecParts.end(), vecParts.begin(), vecParts.end());
	this->m_vecCharacters.insert(m_vecCharacters.end(), vecChara.begin(), vecChara.end());
	this->m_vecTile.insert(m_vecTile.end(), vecTile.begin(), vecTile.end());
	this->m_sStageKey = m_sStageKey;
	this->m_cMutex.unlock();

	{
		json jMonster = j["Monster"];
		for (UINT i = 0; i < jMonster.size(); i++)
		{
			if (jMonster[i]["Type"] == "Medusa")
			{
				CMonsterMedusa* pTempMedusa = new CMonsterMedusa(this);
				vecMonster.push_back(pTempMedusa);
			}
			else if (jMonster[i]["Type"] == "Harpy")
			{
				CMonsterHarpy* pTempHarpy = new CMonsterHarpy(this);
				vecMonster.push_back(pTempHarpy);

				json jTempSkObj = jMonster[i]["SkillObject"];
				for (UINT j = 0; j < jTempSkObj.size(); j++)
				{
					D3DXVECTOR3 vTempPos = D3DXVECTOR3(jTempSkObj[j][0], jTempSkObj[j][1], jTempSkObj[j][2]);
					pTempHarpy->AddObjectPosition(vTempPos);
				}
			}
		}
	}
	vector<CInteractiveActor*> vecWhiteboard;
	{
		json jWhiteboard = j["Whiteboard"];
		for (auto&& p : jWhiteboard)
		{
			D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
			float rotate = p["Rotate"];
			D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
			CWhiteboard* Whiteboard = new CWhiteboard(pos);
			Whiteboard->SetRotationY(rotate);
			Whiteboard->SetScale(scale);
			Whiteboard->SetFormula(m_vecBlueprints);
			vecWhiteboard.push_back(Whiteboard);
		}
	}
	

	this->m_cMutex.lock();
	this->m_vecMonster.insert(m_vecMonster.end(), vecMonster.begin(), vecMonster.end());
	this->m_vecObject.insert(m_vecObject.end(), vecWhiteboard.begin(), vecWhiteboard.end());
	this->m_cMutex.unlock();
	
	if (pCallback)
		(this->*pCallback)();

	// 로딩ui 종료하고 게임 시작
	g_EventManager->CallEvent(eEvent::LoadingEnd, NULL);
}

void CGameScene::ToggleStop()
{
	m_isTimeStop = !m_isTimeStop;
}

void CGameScene::ApplyMonsterSkill(eSkill skill, float fDuration)
{
	switch (skill)
	{
	case eSkill::SandWind:
		SetWindDirection(fDuration);
		break;
	case eSkill::None:
	case eSkill::KeyLock:
	case eSkill::SlowMove:
	case eSkill::KeyReverse:
		SetCCToRandomCharacter(skill, fDuration);
		break;
	}
}

void CGameScene::FinishSkill(eSkill skill)
{
	switch (skill)
	{
	case eSkill::SandWind:
		DeleteWind();
		break;
	case eSkill::Tornado:
		DeleteTornado();
		break;
	}
}

bool CGameScene::CheckSpecificPartsID(string partsID)
{
	for (CParts *it : m_vecParts)
	{
		if (it->GetPartsID() == partsID)
			return true;
	}
	return false;
}

D3DXVECTOR3 CGameScene::SelectRandomObject()
{
	CRandomNumberGenerator rand;
	int index = rand.GenInt(0, m_vecObject.size() - 1);

	return m_vecObject[index]->GetPosition();
}

bool CGameScene::CheckDistanceToSelectedObject(D3DXVECTOR3 pos, float fSize)
{
	D3DXVECTOR3 size(fSize, 100.0f, fSize);
	CBoxCollision cCollsion(pos, size);

	for (auto it : m_vecCharacters)
	{
		if (cCollsion.Collide(it->GetCollision()))
			return true;
	}
	return false;
}

void CGameScene::CheckCollideCharacterToSandpile(ICollisionArea *collision)
{
	for (auto it : m_vecCharacters)
	{
		if (collision->Collide(it->GetCollision())) // 모래더미와 겹쳐있음
		{
			if (it->GetCC()->GetID() != "SLOWANDSTOP")
				it->SetCC(new CCCSlowAndStop);

			it->SetOverlappedSandpile(collision);
		}
		else if (collision == it->GetOverlappedSandpile()) // 모래더미와 겹쳐있지 않은데 이전에 겹친 적이 있음
		{
			if (it->GetCC()->GetID() == "SLOWANDSTOP")
				it->DeleteCC();
				
			it->SetOverlappedSandpile(nullptr);
		}
	}
}

D3DXVECTOR3 CGameScene::GetRandomPartsPosition()
{
	if (m_vecParts.empty())
		return D3DXVECTOR3(-999, -999, -999);

	CRandomNumberGenerator rand;
	int index = rand.GenInt(0, m_vecParts.size() - 1);

	return m_vecParts[index]->GetPosition();
}

CCrowdControl *CGameScene::ChooseCC(eSkill skill)
{
	switch (skill)
	{
	case eSkill::KeyLock:
		return new CCCStopMove;
	case eSkill::SlowMove:
		return new CCCSpeedDown;
	case eSkill::KeyReverse:
		return new CCCReverseKey;
	}
	return new CCCNone;
}

void CGameScene::SetCCToRandomCharacter(eSkill skill, float fDuration)
{
	CCrowdControl *pCC = ChooseCC(skill);
	pCC->SetDuration(fDuration);

	CRandomNumberGenerator r;
	m_vecCharacters[r.GenInt(0, 1)]->SetCC(pCC);
	g_EventManager->CallEvent(eEvent::CrowdControl, NULL);
}

void CGameScene::DestroyPartsOnPosition(D3DXVECTOR3 pos)
{
	CSphereCollision cCollsion(pos, 2.0f);

	for (int i = 0; i < m_vecParts.size(); ++i)
	{
		if (cCollsion.Collide(m_vecParts[i]->GetCollision()))
		{
			SafeDelete(m_vecParts[i]);
			m_vecParts.erase(m_vecParts.begin() + i);
			--i;
		}
	}
}

bool CGameScene::CheckWarning()
{
	if (m_pWarnning == nullptr)
		return true;

	if (m_pWarnning->GetCheckFirst())
	{
		return m_pWarnning->GetCheckEnd();
	}
	else
	{
		g_EventManager->CallEvent(eEvent::CallWarning, NULL);
	}
	return false;
}

void CGameScene::SetWindDirection(float nDir)
{
	m_vWind = D3DXVECTOR3(0.01f * nDir, 0, 0);
}

void CGameScene::DeleteWind()
{
	m_vWind = g_vZero;
}

void CGameScene::DeleteTornado()
{
	g_EventManager->CallEvent(eEvent::DeleteTornado, NULL);
}

void CGameScene::DeleteCC()
{
	for (CCharacter *it : m_vecCharacters)
	{
		it->DeleteCC();
	}
}

int CGameScene::IsGameClear()
{
	if (m_fGameTime <= 0)
	{
		return 2; //실패
	}

	for (CBlueprint *it : m_vecBlueprints)
	{
		if (it->GetIsCompleted() == false)
			return 0; // 완료되지 않음
	}
	if (!m_vecBlueprints.empty())
		return 1; // 클리어

	return 0;
}

bool CGameScene::ColideCheck(CActor* pActor1, CActor* pActor2)
{

	if (pActor1->GetIsCollide() == false || pActor2->GetIsCollide() == false)
	{
		pActor1->SetIsCollide(true);
		pActor2->SetIsCollide(true);
		return true;
	}
	return false;
}

void CGameScene::GetInteractObject(CCharacter *pCharacter)
{
	float fMaxDistance = 9999.f;
	CInteractiveActor* target = nullptr;
	map<float, CInteractiveActor *> veclength;

	for (CParts *it : m_vecParts)
	{
		if (pCharacter->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			float dist = D3DXVec3Length(&(pCharacter->GetPosition() - it->GetPosition()));
			if(dist < fMaxDistance)
			{
				fMaxDistance = dist;
				target = it;
			}
		}
	}

	for (CInteractiveActor *it : m_vecObject)
	{
		if (pCharacter->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			float dist = D3DXVec3Length(&(pCharacter->GetPosition() - it->GetPosition()));
			if (dist < fMaxDistance)
			{
				fMaxDistance = dist;
				target = it;
			}
		}
	}

	for (CBlueprint *it : m_vecBlueprints)
	{
		if (pCharacter->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			float dist = D3DXVec3Length(&(pCharacter->GetPosition() - it->GetPosition()));
			if (dist < fMaxDistance)
			{
				fMaxDistance = dist;
				target = it;
			}
		}
	}

	if (target)
		target->Interact(pCharacter);

}

void CGameScene::AddParts(CParts *parts)
{
	if (parts)
		m_vecParts.push_back(parts);
}

void CGameScene::DeleteParts(CParts *parts)
{
	if (parts)
	{
		int Cnt = 0;
		for (CInteractiveActor *it : m_vecParts)
		{
			if (it == parts)
			{
				SafeDelete(it);
				m_vecParts.erase(m_vecParts.begin() + Cnt);
				return;
			}
			Cnt++;
		}
	}
}

void CGameScene::CheckAroundCombinator(CPartCombinator *combinator)
{
	if (combinator->GetCombinatorLoadState() == eCombinatorLoadState::LoadImpossible)
		return;

	map<float, CParts *> veclength;
	for (CParts *it : m_vecParts)
	{
		if (it->GetGrabPosition() != NULL)
			continue;

		if (combinator->GetCombinPartsLevel() == it->GetCombinePartsLevel() &&
			combinator->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			D3DXVECTOR3 vDirection = combinator->GetPosition() - it->GetPosition();
			veclength[D3DXVec3Length(&vDirection)] = it;
		}
	}

	for (auto it : veclength)
	{
		combinator->PartsInteract(it.second);
		it.second->SetCPartCombinator(combinator);
	}
}
