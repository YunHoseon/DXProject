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
#include "CTile.h"
#include "CCrowdControl.h"

#include "CTornado.h"
#include "CSandpile.h"

#include "CUICloseButton.h"
#include "CUIBoardButton.h"
#include "CUIBarButton.h"
#include "CUIPauseButton.h"

/* ������ */
#include <fstream>

#include "CDebugPlayer1.h"
#include "CDebugPlayer2.h"
#include "CTestStair.h"

CGameScene::CGameScene() : m_pField(NULL),
						   m_pDebugSphere(NULL),
						   m_pDebugCube(NULL),
						   m_pDebugParts(NULL),
						   m_pDebugPauseUI(nullptr),
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

	SafeDelete(m_pDebugPauseUI);
}

void CGameScene::Init()
{
	//g_SoundManager->PlayBGM();
	//g_SoundManager->SetBGMSound(0.5f);
	m_fGameTime = 300.0f;

	m_pField = new CField;
	if (m_pField)
	{
		m_pField->Setup(WIDTH, HEIGHT);
		m_vecStaticActor.push_back(m_pField);
	}

	CWall *wall = new CWall;
	wall->Setup();
	m_vecStaticActor.push_back(wall);

	CPartStorage *partStorage = new CPartStorage(this);
	partStorage->Setup(0, D3DXVECTOR3(5, 0, 2), "A00");
	m_vecObject.push_back(partStorage);

	partStorage = new CPartStorage(this);
	partStorage->Setup(0, D3DXVECTOR3(5, 0, 3), "A02");
	m_vecObject.push_back(partStorage);

	CPartCombinator *partManualCombinator = new CPartManualCombinator(this, eCombinatorPartsLevel::TWO, 0, D3DXVECTOR3(-2, 0, 2));
	m_vecObject.push_back(partManualCombinator);

	CCombinatorButton *combinatorButton = new CCombinatorButton(partManualCombinator);
	combinatorButton->Setup(0, D3DXVECTOR3(1, 0, -1));
	m_vecObject.push_back(combinatorButton);

	CPartCombinator *partAutoCombinator = new CPartAutoCombinator(this, eCombinatorPartsLevel::ONE, 0, D3DXVECTOR3(-4, 0, -3));
	m_vecObject.push_back(partAutoCombinator);

	COutlet *outlet = new COutlet(this);
	outlet->Setup(0, D3DXVECTOR3(1, 0, 3));
	m_vecObject.push_back(outlet);

	CPartVending *partVending = new CPartVending(outlet, this, "A01");
	partVending->Setup(0, D3DXVECTOR3(1, 0, -3));
	m_vecObject.push_back(partVending);

	CBlueprint *blueprint = new CBlueprint("A00", m_vecParts,
										   D3DXVECTOR3(5.0f, -0.5f, -3.0f), D3DXVECTOR3(2.0f, 0.1f, 2.8f), 0, 0);
	blueprint->Setup();
	m_vecBlueprints.push_back(blueprint);

	CBlueprint *blueprint2 = new CBlueprint("A01", m_vecParts,
											D3DXVECTOR3(5.0f, -0.5f, 0), D3DXVECTOR3(2.0f, 0.1f, 2.8f), D3DX_PI * 0.5f, D3DX_PI * 0.5f);
	blueprint2->Setup();
	blueprint2->SetPosition(-3.0f, -0.5f, 0);
	m_vecBlueprints.push_back(blueprint2);

	m_pDebugSphere = new CDebugPlayer1(this);
	if (m_pDebugSphere)
		m_pDebugSphere->Setup();

	m_pDebugCube = new CDebugPlayer2(this);
	if (m_pDebugCube)
		m_pDebugCube->Setup();

	m_vecCharacters.push_back(m_pDebugSphere);
	m_vecCharacters.push_back(m_pDebugCube);

	m_pDebugPauseUI = new CUIPauseButton(D3DXVECTOR2(100, 100), 27, this);
	m_pDebugPauseUI->Setup();

	CMonster *Medusa = new CMonsterMedusa(this);
	m_vecMonster.push_back(Medusa);

	CMonster *Harpy = new CMonsterHarpy(this);
	m_vecMonster.push_back(Harpy);
	Harpy->AddObjectPosition(D3DXVECTOR3(0, 0, 0));
	Harpy->AddObjectPosition(D3DXVECTOR3(3, 0, 0));
	Harpy->AddObjectPosition(D3DXVECTOR3(0, 0, 3));
	Harpy->AddObjectPosition(D3DXVECTOR3(-3, 0, 0));
	Harpy->AddObjectPosition(D3DXVECTOR3(0, 0, -3));


	m_vecStaticActor.push_back(new CStair(D3DXVECTOR3(1, 0, -4)));
	m_vecStaticActor.push_back(new CSandpile(this,D3DXVECTOR3(4, 0, 0)));
	m_vecStaticActor.push_back(new CWater(D3DXVECTOR3(0, -1, -6.5)));
	m_vecStaticActor.push_back(new CSand(D3DXVECTOR3(0, -1, -7.5)));

}

void CGameScene::Render()
{
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

	if (m_pDebugPauseUI)
		m_pDebugPauseUI->Render();

}

void CGameScene::Update()
{
	if (m_isTimeStop)
		return;

	if (IsGameClear())
	{
		_DEBUG_COMMENT cout << "���� Ŭ����" << endl;
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
			character->AddForce(m_vWind);
		}

		for (CParts *part : m_vecParts)
		{
			part->AddForce(m_vWind);
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

		if (m_pDebugPauseUI)
			m_pDebugPauseUI->Update();
	}
}

void CGameScene::Load(string sFolder, string sFilename)
{
	string sFullname = sFolder + "/" + sFilename;
	std::ifstream is(sFullname);
	assert(is.is_open());
	json j;
	is >> j;

	// blueprint
	{
		json jBP = j["Blueprint"];
		for (auto &&p : jBP)
		{
			string id = p["PartsID"];
			D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
			float rotate = p["Rotate"];
			D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
			CBlueprint *blueprint = new CBlueprint(id, m_vecParts, pos, scale, rotate, rotate);
			blueprint->Setup();
			m_vecBlueprints.push_back(blueprint);
		}
	}
	{
		//outlet - vending
		json jOutlet = j["Outlet"];
		vector<COutlet *> vecOutlet;
		for (auto &&p : jOutlet)
		{
			D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
			float rotate = p["Rotate"];
			D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
			COutlet *pOutlet = new COutlet(this);
			pOutlet->SetScale(scale);
			pOutlet->Setup(rotate, pos);
			m_vecObject.push_back(pOutlet);
			vecOutlet.push_back(pOutlet);
		}
		json jvending = j["PartVending"];
		for (auto &&p : jvending)
		{
			string id = p["PartsId"];
			D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
			float rotate = p["Rotate"];
			D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
			CPartVending *vending = new CPartVending(vecOutlet[p["OutletIdx"]], this, id);
			vending->Setup(rotate, pos);
			vending->SetScale(scale);
			m_vecObject.push_back(vending);
		}
	}
	{
		// manual - switch
		json jManual = j["PartManualCombinator"];
		vector<CPartManualCombinator *> vecManual;
		for (auto &&p : jManual)
		{
			D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
			float rotate = p["Rotate"];
			D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
			CPartManualCombinator *manual = new CPartManualCombinator(this, (eCombinatorPartsLevel)0, rotate, pos);
			//manual->SetScale(scale);
			m_vecObject.push_back(manual);
			vecManual.push_back(manual);
		}
		json jButton = j["CombinatorButton"];
		for (auto &&p : jButton)
		{
			D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
			float rotate = p["Rotate"];
			D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
			CCombinatorButton *button = new CCombinatorButton(vecManual[p["PartManualCombinatorIdx"]]);
			button->Setup(rotate, pos);
			//button->SetScale(scale);
			m_vecObject.push_back(button);
		}
	}
	{
		// auto
		json jAuto = j["PartAutoCombinator"];
		for (auto &&p : jAuto)
		{
			D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
			float rotate = p["Rotate"];
			D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
			CPartAutoCombinator *autoCombinator = new CPartAutoCombinator(this, (eCombinatorPartsLevel)0, rotate, pos);
			//autoCombinator->SetScale(scale);
			m_vecObject.push_back(autoCombinator);
		}
	}
	{
		// storage
		json jStorage = j["PartStorage"];
		for (auto &&p : jStorage)
		{
			string id = p["PartsId"];
			D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
			float rotate = p["Rotate"];
			D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
			CPartStorage *storage = new CPartStorage(this);
			storage->Setup(rotate, pos, id);
			//storage->SetScale(scale);
			m_vecObject.push_back(storage);
		}
	}
	{
		// parts
		json jParts = j["Parts"];
		for (auto &&p : jParts)
		{
			string id = p["PartsId"];
			D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
			float rotate = p["Rotate"];
			D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
			CParts *parts = g_pPartsManager->CreateParts(id);
			parts->SetPosition(pos);
			parts->SetRotationY(rotate);
			parts->SetScale(scale);
			m_vecParts.push_back(parts);
		}
	}
	{
		// player1
		if (!j["Player1"].empty())
		{
			auto &&p = j["Player1"][0];
			CDebugPlayer1 *player = new CDebugPlayer1(this);
			D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
			float rotate = p["Rotate"];
			D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
			player->SetDefaultPosition(pos);
			player->SetPosition(pos);
			player->SetRotationY(rotate);
			player->SetScale(scale);
			m_vecCharacters.push_back(player);
		}
	}
	{
		// player2
		if (!j["Player2"].empty())
		{
			auto &&p = j["Player2"][0];
			CDebugPlayer2 *player = new CDebugPlayer2(this);
			D3DXVECTOR3 pos(p["Position"][0], p["Position"][1], p["Position"][2]);
			float rotate = p["Rotate"];
			D3DXVECTOR3 scale(p["Scale"][0], p["Scale"][1], p["Scale"][2]);
			player->SetDefaultPosition(pos);
			player->SetPosition(pos);
			player->SetRotationY(rotate);
			player->SetScale(scale);
			m_vecCharacters.push_back(player);
		}
	}
}

void CGameScene::ToggleStop()
{
	m_isTimeStop = !m_isTimeStop;
}

void CGameScene::MonsterSkill(eSkill skill)
{
	switch (skill)
	{
	case eSkill::DestroyParts:
		MedusaUlt();
		break;
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
	for (CParts* it : m_vecParts)
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

void CGameScene::CheckSandDummyArea(ICollisionArea* collison)
{
	for (auto it : m_vecCharacters)
	{
		//if (it->GetDummy() == false &&  it->GetParts() && collison->Collide(it->GetCollision())) // 더미안인데 파츠가있으면 들어오는곳 
		//{
		//	it->SetDummy(true);
		//	it->SetCC(new CCCStopMove);
		//}

		//if (it->GetDummy() && it->GetParts() == nullptr) //더미안에서 파츠를 던지면 들어오는곳
		//{
		//	it->SetDummy(false);
		//	it->DeleteCC();
		//}


		//if (it->GetParts() && collison->Collide(it->GetCollision())) // 더미안인데 파츠가있으면 들어오는곳 
		//{
		//	it->SetCC(new CCCStopMove);
		//}

		//if (it->GetDummy() && it->GetParts() == nullptr) //더미안에서 파츠를 던지면 들어오는곳
		//{
		//	it->SetCC(new CCCSpeedDown);
		//}

		if (it->GetDummy() == false && collison->Collide(it->GetCollision())) //더미 밖에서 안으로 들어올때 들어오는곳
		{
			it->SetDummy(true);

			it->SetCC(new CCCSlowAndStop);
			
		}
		else if(it->GetDummy() && collison->Collide(it->GetCollision()) == false) // 더미밖에서 들어오는곳 
		{
			it->SetDummy(false);
			it->DeleteCC();
		}
	}
}

void CGameScene::UpdateTornado(CTornado * tornado)
{
	for (CCharacter *character : m_vecCharacters)
	{
		D3DXVECTOR3 dir(0, 0, 0);
		if (tornado->Collide(character, &dir))
		{
			character->AddForce(dir * tornado->GetPower());
		}
	}
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

void CGameScene::MedusaUlt()
{
	if (m_vecParts.empty())
		return;

	CRandomNumberGenerator rand;
	int index = rand.GenInt(0, m_vecParts.size() - 1);

	D3DXVECTOR3 vec = m_vecParts[index]->GetPosition();

	CSphereCollision cCollsion(vec, 2.0f);

	for (int i = 0; i < m_vecParts.size(); i++)
	{
		if (cCollsion.Collide(m_vecParts[i]->GetCollision()))
		{
			SafeDelete(m_vecParts[i]);
			m_vecParts.erase(m_vecParts.begin() + i);
			--i;
		}
	}
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

//void CGameScene::ThrowParts(CCharacter* pCharacter,CParts* parts, D3DXVECTOR3 vDir)
//{
//	if (parts != nullptr)
//	{
//		pCharacter->SetPlayerState(ePlayerState::None);
//		parts->ThrowParts(vDir);
//	}
//}

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

//void CGameScene::SendPartsToOutlet(CParts * parts, COutlet * outlet)
//{
//	outlet->AcceptPartsFromVending(parts);
//}
