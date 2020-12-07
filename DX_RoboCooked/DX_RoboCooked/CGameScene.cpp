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
#include "CStair.h"
#include "CWater.h"
#include "CSand3.h"
#include "CSphereCollision.h"
#include "CCrowdControl.h"
#include "CCCSpeedDown.h"
#include "CCCReverseKey.h"
#include "CCCStopMove.h"
#include "CCCNone.h"


#include "CUICloseButton.h"
#include "CUIBoardButton.h"
#include "CUIBarButton.h"
#include "CUIPauseButton.h"

#include "CMonsterMedusa.h"
#include "CMonsterHarpy.h"
#include "CRandomNumberGenerator.h"


/* 디버깅용 */
#include "CDebugPlayer1.h"
#include "CDebugPlayer2.h"
#include "CTestStair.h"

CGameScene::CGameScene() :
	m_pField(NULL),
	m_pDebugSphere(NULL),
	m_pDebugCube(NULL),
	m_pDebugParts(NULL),
	m_pDebugPauseUI(nullptr),
	m_isTimeStop(false)
{
	//Sound Add
	g_SoundManager->AddBGM("data/sound/bgm.mp3");
	g_SoundManager->AddSFX("data/sound/effBBam.mp3", "BBam");
	g_SoundManager->AddSFX("data/sound/effMelem.mp3", "Melem");
}

CGameScene::~CGameScene()
{
	for (CActor* it : m_vecStaticActor)
	{
		SafeDelete(it);
	}

	for (CInteractiveActor* it : m_vecObject)
	{
		SafeDelete(it);
	}

	for (CInteractiveActor* it : m_vecParts)
	{
		SafeDelete(it);
	}
	
	for (CCharacter* it : m_vecCharacters)
	{
		SafeDelete(it);
	}

	SafeDelete(m_pDebugPauseUI);
}

void CGameScene::Init()
{
	//g_SoundManager->PlayBGM();
	//g_SoundManager->SetBGMSound(0.5f);

	m_pField = new CField;
	if (m_pField)
	{
		m_pField->Setup(WIDTH, HEIGHT);
		m_vecStaticActor.push_back(m_pField);
	}

	CWall* wall = new CWall;
	wall->Setup();
	m_vecStaticActor.push_back(wall);

	CPartStorage* partStorage = new CPartStorage(this);
	partStorage->Setup(0, D3DXVECTOR3(5, 0, 2) , "A00");
	m_vecObject.push_back(partStorage);

	CPartCombinator* partManualCombinator = new CPartManualCombinator(this, eCombinatorPartsLevel::ONE , 45.0f , D3DXVECTOR3(-2, 0, 2));
	m_vecObject.push_back(partManualCombinator);

	CCombinatorButton* combinatorButton = new CCombinatorButton(partManualCombinator);
	combinatorButton->Setup(0,D3DXVECTOR3(1,0,-1));
	m_vecObject.push_back(combinatorButton);

	CPartCombinator* partAutoCombinator = new CPartAutoCombinator(this, eCombinatorPartsLevel::ONE, 0, D3DXVECTOR3(-4, 0, -3));
	m_vecObject.push_back(partAutoCombinator);

	COutlet* outlet = new COutlet(this);
	outlet->Setup(0, D3DXVECTOR3(1, 0, 3));
	m_vecObject.push_back(outlet);
	
	CPartVending* partVending = new CPartVending(outlet, this, "A01");
	partVending->Setup(0, D3DXVECTOR3(1, 0, -3));
	m_vecObject.push_back(partVending);

	CBlueprint* blueprint = new CBlueprint("A00", m_vecParts, 
		D3DXVECTOR3(5.0f, -0.5f, -3.0f), D3DXVECTOR3(2.0f, 0.1f, 2.8f), 0, 0);
	blueprint->Setup();
	//m_vecObject.push_back(blueprint);
	m_vecBlueprints.push_back(blueprint);

	CBlueprint* blueprint2 = new CBlueprint("A01", m_vecParts,
		D3DXVECTOR3(5.0f, -0.5f, 0), D3DXVECTOR3(2.0f, 0.1f, 2.8f), 90, 90);
	blueprint2->Setup();
	//m_vecObject.push_back(blueprint2);
	m_vecBlueprints.push_back(blueprint2);

	m_pDebugSphere = new CDebugPlayer1(this);
	if (m_pDebugSphere)
		m_pDebugSphere->Setup();

	m_pDebugCube = new CDebugPlayer2(this);
	if (m_pDebugCube)
		m_pDebugCube->Setup();

	m_vecCharacters.push_back(m_pDebugSphere);
	m_vecCharacters.push_back(m_pDebugCube);

	//m_pDebugParts = new CParts("999");
	//if (m_pDebugParts)
	//	m_pDebugParts->Setup();
	//m_vecParts.push_back(m_pDebugParts);
	//
	//CParts* m_pDebugParts2 = new CParts("999");
	//if (m_pDebugParts2)
	//	m_pDebugParts2->Setup();
	//m_vecParts.push_back(m_pDebugParts2);

	m_pDebugPauseUI = new CUIPauseButton(D3DXVECTOR2(100,100),27,this);
	m_pDebugPauseUI->Setup();

	CMonster* monster = new CMonsterMedusa(this);
	m_vecMonster.push_back(monster);

	m_vecStaticActor.push_back(new CStair(D3DXVECTOR3(1,0,-4)));
}

void CGameScene::Render()
{
	for (CActor* it : m_vecStaticActor)
	{
		it->Render();
	}

	for (CInteractiveActor* it : m_vecParts)
	{
		it->Render();
	}

	for (CInteractiveActor* it : m_vecObject)
	{
		it->Render();
	}

	for (CCharacter* it : m_vecCharacters)
	{
		it->Render();
	}

	for (CBlueprint* it : m_vecBlueprints)
	{
		it->Render();
	}
	
	for (CMonster* it : m_vecMonster)
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

	if(IsGameClear())
	{
		_DEBUG_COMMENT cout << "게임 클리어" << endl;
	}

	{
		for (CCharacter * character : m_vecCharacters)
		{
			CPhysicsApplyer::ApplyGravity(character);
		}

		for (CInteractiveActor* part : m_vecParts)
		{
			CPhysicsApplyer::ApplyGravity(part);
		}
	}
	
	// collide -> update
	{// collide
		if (m_vecCharacters.size() == 2)
		{
			CPhysicsApplyer::ApplyBound(m_vecCharacters[0], m_vecCharacters[1]);
		}

		for (CInteractiveActor* part : m_vecParts)
		{
			for (CCharacter* character : m_vecCharacters)
			{
				CPhysicsApplyer::ApplyBound(character, part);
			}
			for (CInteractiveActor* part2 : m_vecParts)
			{
				if(part != part2)
					CPhysicsApplyer::ApplyBound(part2, part);
			}
		}
		
		for (CInteractiveActor* obj : m_vecObject)
		{
			for (CCharacter* character : m_vecCharacters)
			{
				CPhysicsApplyer::ApplyBound(character, obj);
			}
			for (CInteractiveActor* part : m_vecParts)
			{
				CPhysicsApplyer::ApplyBound(part, obj);
			}
		}

		for (CActor* pStaticActor : m_vecStaticActor)
		{
			for (CCharacter* character : m_vecCharacters)
			{
				CPhysicsApplyer::ApplyBound(character, pStaticActor);
			}
			for (CInteractiveActor* part : m_vecParts)
			{
				CPhysicsApplyer::ApplyBound(part, pStaticActor);
			}
		}

		for (CBlueprint* blueprint : m_vecBlueprints)
		{
			for (CCharacter* character : m_vecCharacters)
			{
				CPhysicsApplyer::ApplyBound(character, blueprint);
			}
		}
	}
	{// update
		for (CActor* it : m_vecStaticActor)
		{
			it->Update();
		}

		for (CInteractiveActor* it : m_vecParts)
		{
			it->Update();
		}

		for (CInteractiveActor* it : m_vecObject)
		{
			it->Update();
		}
		
		for (CBlueprint* it : m_vecBlueprints)
		{
			it->Update();
		}

		for (CMonster* it : m_vecMonster)
		{
			it->Update();
		}

		for (CCharacter* character : m_vecCharacters)
		{
			character->Update();
		}

		if (m_pDebugPauseUI)
			m_pDebugPauseUI->Update();
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
	/*case eSkill::KeyLock:
		break;
	case eSkill::SlowMove:
		break;*/
	case eSkill::DestroyParts:
		MedusaUlt();
		break;
	/*case eSkill::KeyRevers:
		break;
	case eSkill::SandWind:
		break;
	case eSkill::Flurry:
		break;*/
	}

	CC(ChooseCC(skill));
}

bool CGameScene::CheckSpecificPartsID(string partsID)
{
	for (CInteractiveActor* it : m_vecParts)
	{
		CParts* data = static_cast<CParts*>(it);
		if (data->GetPartsID() == partsID)
		{
			return true;
		}
	}

	return false;
}

CCrowdControl* CGameScene::ChooseCC(eSkill skill)
{

	switch (skill)
	{
	case eSkill::KeyLock:
		return new CCCStopMove;
	case eSkill::SlowMove:
		return new CCCSpeedDown;
	case eSkill::KeyRevers:
		return new CCCReverseKey;
	/*case eSkill::SandWind:
		return new CCCSpeedDown;
	case eSkill::Flurry:
		return new CCCSpeedDown;*/
	}

	return new CCCNone;
}

void CGameScene::CC(CCrowdControl * pCC)
{
	g_EventManager->CallEvent(eEvent::CrowdControl, NULL);

	for (CCharacter* it : m_vecCharacters)
	{
		it->SetCC(pCC->Clone());
	}

	SafeDelete(pCC);
}

void CGameScene::MedusaUlt()
{
	CRandomNumberGenerator rand;
	int index = rand.GenInt(0, m_vecParts.size() - 1);

	//CParts* data = static_cast<CParts*>(m_vecParts[index]);

	D3DXVECTOR3 vec = m_vecParts[index]->GetPosition();

	CSphereCollision Collsion(vec, 2.0f);

	Collsion.Update();

	for (int i = 0; i < m_vecParts.size(); i++)
	{
		if (Collsion.Collide(m_vecParts[i]->GetCollision()))
		{
			SafeDelete(m_vecParts[i]);
			m_vecParts.erase(m_vecParts.begin() + i);
			i = 0;
		}
	}




}

bool CGameScene::IsGameClear()
{
	for (CBlueprint* it : m_vecBlueprints)
	{
		if (it->GetIsCompleted() == false)
			return false;
	}
	return true;
}

void CGameScene::GetInteractObject(CCharacter* pCharacter)
{
	for (CInteractiveActor * it : m_vecParts)
	{
		if (pCharacter->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			it->Interact(pCharacter);
			return;
		}
	}

	for (CInteractiveActor * it : m_vecObject)
	{
		if (pCharacter->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			it->Interact(pCharacter);
			return;
		}
	}

	for (CBlueprint *  it : m_vecBlueprints)
	{
		if (pCharacter->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			it->Interact(pCharacter);
			return;
		}
	}
}

void CGameScene::AddParts(CParts * parts)
{
	if (parts)
		m_vecParts.push_back(parts);
}

void CGameScene::DeleteParts(CParts * parts)
{
	if (parts)
	{
		int Cnt = 0;
		for (CInteractiveActor* it : m_vecParts)
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

void CGameScene::CheckAroundCombinator(CPartCombinator* combinator)
{
	if (combinator->GetCombinatorLoadState() == eCombinatorLoadState::LoadImpossible)
		return;

	map<CParts*,float> veclength;
	for (CInteractiveActor * it : m_vecParts)
	{
		CParts* data = static_cast<CParts*>(it);
		if (data->GetGrabPosition() != NULL)
			continue;

		if (combinator->GetCombinPartsLevel() == data->GetCombinePartsLevel() &&
			combinator->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			D3DXVECTOR3 vDirection = combinator->GetPosition() - data->GetPosition();
			veclength[data] = D3DXVec3Length(&vDirection);	
		}
	}

	for(auto it : veclength)
	{
		combinator->PartsInteract(it.first);
		it.first->SetCPartCombinator(combinator);
	}
}

//void CGameScene::SendPartsToOutlet(CParts * parts, COutlet * outlet)
//{
//	outlet->AcceptPartsFromVending(parts);
//}
