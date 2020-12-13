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
#include "CTile.h"
#include "CCrowdControl.h"

#include "CTornado.h"
#include "CSandpile.h"

#include "CUIPauseButton.h"
#include "CUITrafficLight.h"

/* ������ */
#include <filesystem>
#include <fstream>

std::mutex CGameScene::m_cMutex;

#include "CCactus.h"
#include "CDebugPlayer1.h"
#include "CDebugPlayer2.h"

CGameScene::CGameScene() : m_pField(NULL),
						   m_pDebugPauseUI(nullptr),
						   m_pDebugTrafficLight(nullptr),
						   m_isTimeStop(false),
						   m_vWind(0, 0, 0),
						   m_fGameTime(300.0f),
						   m_nLotIndex(0)
{
	//Sound Add
	g_SoundManager->AddBGM("data/sound/bgm.mp3");
	g_SoundManager->AddSFX("data/sound/effBBam.mp3", "BBam");
	g_SoundManager->AddSFX("data/sound/effMelem.mp3", "Melem");
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
	for (CMonster* it : m_vecMonster)
	{
		SafeDelete(it);
	}

	for (CTile* it : m_vecTile)
	{
		SafeDelete(it);
	}

	for (CBlueprint* it : m_vecBlueprints)
	{
		SafeDelete(it);
	}
	SafeDelete(m_pDebugPauseUI);
	SafeDelete(m_pDebugTrafficLight);
	m_cMutex.unlock();
}

void CGameScene::Init()
{
	CWall *wall = new CWall(this);
	CMonster *Medusa = new CMonsterMedusa(this);
	CMonster *Harpy = new CMonsterHarpy(this);
	Harpy->AddObjectPosition(D3DXVECTOR3(0, 0, 0));
	Harpy->AddObjectPosition(D3DXVECTOR3(3, 0, 0));
	Harpy->AddObjectPosition(D3DXVECTOR3(0, 0, 3));
	Harpy->AddObjectPosition(D3DXVECTOR3(-3, 0, 0));
	Harpy->AddObjectPosition(D3DXVECTOR3(0, 0, -3));

	CUIButton* pPauseButton = new CUIPauseButton(D3DXVECTOR2(465, 10), 27, this);
	CUITrafficLight* pTrafficLight = new CUITrafficLight(this,m_vecBlueprints.size());
	
	//CPharaohCoffin* coffin = new CPharaohCoffin(this, D3DXVECTOR3(0,0,0));

	m_cMutex.lock();

	m_fGameTime = 300.0f;
	m_vecStaticActor.push_back(wall);
	m_vecMonster.push_back(Medusa);
	m_vecMonster.push_back(Harpy);

	m_pDebugTrafficLight = pTrafficLight;
	m_pDebugPauseUI = pPauseButton;
	//m_vecObject.push_back(coffin);

	m_cMutex.unlock();
}

void CGameScene::Render()
{
	m_cMutex.lock();
	for (CActor *it : m_vecStaticActor)
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

	for (CCharacter *it : m_vecCharacters)
	{
		it->Render();
	}

	for (CBlueprint *it : m_vecBlueprints)
	{
		it->Render();
	}

	for (CMonster *it : m_vecMonster)
	{
		it->Render();
	}

	for (CTile *it : m_vecTile)
	{
		it->Render();
	}

	if (m_pDebugPauseUI)
		m_pDebugPauseUI->Render();

	if (m_pDebugTrafficLight)
		m_pDebugTrafficLight->Render();
	m_cMutex.unlock();
}

void CGameScene::Update()
{
	if (m_isTimeStop)
		return;

	if (IsGameClear())
	{
		_DEBUG_COMMENT cout << "game clear!" << endl;
	}

	if (IsGameLose())
	{
		_DEBUG_COMMENT cout << "game lose!" << endl;
	}

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
			CPhysicsApplyer::ApplyBound(m_vecCharacters[0], m_vecCharacters[1]);
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
					CPhysicsApplyer::ApplyBound(part2, part);
			}
		}

		
		
		for (CInteractiveActor *obj : m_vecObject)
		{
			for (CCharacter *character : m_vecCharacters)
			{
				CPhysicsApplyer::ApplyBound(character, obj);
			}
			for (CParts *part : m_vecParts)
			{
				CPhysicsApplyer::ApplyBound(part, obj);
			}
		}

		for (CActor *pStaticActor : m_vecStaticActor)
		{
			for (CCharacter *character : m_vecCharacters)
			{
				CPhysicsApplyer::ApplyBound(character, pStaticActor);
			}
			for (CParts *part : m_vecParts)
			{
				CPhysicsApplyer::ApplyBound(part, pStaticActor);
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
						CPhysicsApplyer::ApplyBound(character, tile);
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
						CPhysicsApplyer::ApplyBound(part, tile);
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

		for (CParts *it : m_vecParts)
		{
			it->Update();
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

void CGameScene::Load(string sFolder, string sFilename, void (CGameScene::* pCallback)(void))
{
	m_cMutex.lock();
	m_isTimeStop = true;
	m_cMutex.unlock();

	string sFullname = sFolder + "/" + sFilename;
	std::ifstream is(sFullname);
	assert(is.is_open());
	json j;
	is >> j;
	is.close();
	vector<CBlueprint*> vecBP;
	vector<CActor*> vecStatic;
	vector<CInteractiveActor*> vecInter;
	vector<CParts*> vecParts;
	vector<CCharacter*> vecChara;
	vector<CTile*> vecTile;
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
				CSandpile* sandpile = new CSandpile(this,pos);
				sandpile->SetRotationY(rotate);
				sandpile->SetScale(scale);
				vecStatic.push_back(sandpile);
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
	this->m_sID = sFilename;
	this->m_cMutex.unlock();

	if (pCallback)
		(this->*pCallback)();

	// 로딩ui 종료하고 게임 시작
	m_cMutex.lock();
	m_isTimeStop = false;
	m_cMutex.unlock();
}

void CGameScene::ToggleStop()
{
	m_isTimeStop = !m_isTimeStop;
}

void CGameScene::MonsterSkill(eSkill skill)
{
	switch (skill)
	{
	case eSkill::SandWind:
		SetWindDirection();
		break;
	}

	CC(ChooseCC(skill));
}

void CGameScene::FinishSkill(eSkill skill)
{
	switch (skill)
	{
	case eSkill::KeyLock:
		DeleteCC();
		break;
	case eSkill::SlowMove:
		DeleteCC();
		break;
	case eSkill::KeyRevers:
		DeleteCC();
		break;
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

void CGameScene::ElectIndexLot()
{
	CRandomNumberGenerator rand;
	m_nLotIndex = rand.GenInt(0, m_vecObject.size() - 1);
}

bool CGameScene::CheckSpecificArea()
{
	D3DXVECTOR3 pos = m_vecObject[m_nLotIndex]->GetPosition();
	D3DXVECTOR3 size(1.5f, 100.0f, 1.5f);
	CBoxCollision cCollsion(pos, size);

	cCollsion.Render();

	for (auto it : m_vecCharacters)
	{
		if (cCollsion.Collide(it->GetCollision()))
			return true;
	}

	return false;
}

void CGameScene::CheckSandDummyArea(ICollisionArea *collison)
{
	for (auto it : m_vecCharacters)
	{
		if (it->GetDummy() == false && collison->Collide(it->GetCollision())) //더미 밖에서 안으로 들어올때 들어오는곳
		{
			it->SetDummy(true);

			it->SetCC(new CCCSlowAndStop);
		}
		else if (it->GetDummy() && collison->Collide(it->GetCollision()) == false) // 더미밖에서 들어오는곳
		{
			it->SetDummy(false);
			it->DeleteCC();
		}
	}
}

D3DXVECTOR3 CGameScene::GetRandomPartsPosition()
{
	if (m_vecParts.empty())
		return D3DXVECTOR3(-999, -999, -999);

	CRandomNumberGenerator rand;
	int index = rand.GenInt(0, m_vecParts.size() - 1);

	D3DXVECTOR3 vec = m_vecParts[index]->GetPosition();

	return vec;
}

CCrowdControl *CGameScene::ChooseCC(eSkill skill)
{
	switch (skill)
	{
	case eSkill::KeyLock:
		return new CCCStopMove;
	case eSkill::SlowMove:
		return new CCCSpeedDown;
	case eSkill::KeyRevers:
		return new CCCReverseKey;
	}

	return new CCCNone;
}

void CGameScene::CC(CCrowdControl *pCC)
{
	g_EventManager->CallEvent(eEvent::CrowdControl, NULL);

	for (CCharacter *it : m_vecCharacters)
	{
		it->SetCC(pCC->Clone());
	}

	SafeDelete(pCC);
}

void CGameScene::MedusaUlt(D3DXVECTOR3 pos)
{
	CSphereCollision cCollsion(pos, 2.0f);

	for (int i = 0; i < m_vecParts.size(); i++)
	{
		if (cCollsion.Collide(m_vecParts[i]->GetCollision()))
		{
			SafeDelete(m_vecParts[i]);
			m_vecParts.erase(m_vecParts.begin() + i);
			--i;
		}
	}
	cCollsion.Render();
}

void CGameScene::SetWindDirection()
{
	int windDirection = rand() % 2;

	if (windDirection == 1)
	{
		m_vWind = D3DXVECTOR3(0.01f, 0, 0);
	}
	else
	{
		m_vWind = D3DXVECTOR3(-0.01f, 0, 0);
	}
}

void CGameScene::DeleteWind()
{
	m_vWind = D3DXVECTOR3(0, 0, 0);
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

bool CGameScene::IsGameClear()
{
	for (CBlueprint *it : m_vecBlueprints)
	{
		if (it->GetIsCompleted() == false)
			return false;
	}
	return true;
}

bool CGameScene::IsGameLose()
{
	m_fGameTime -= g_pTimeManager->GetElapsedTime();

	if (m_fGameTime <= 0)
	{
		return true;
	}

	return false;
}

void CGameScene::GetInteractObject(CCharacter *pCharacter)
{
	for (CParts *it : m_vecParts)
	{
		if (pCharacter->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			it->Interact(pCharacter);
			return;
		}
	}

	for (CInteractiveActor *it : m_vecObject)
	{
		if (pCharacter->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			it->Interact(pCharacter);
			return;
		}
	}

	for (CBlueprint *it : m_vecBlueprints)
	{
		if (pCharacter->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			it->Interact(pCharacter);
			return;
		}
	}
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
