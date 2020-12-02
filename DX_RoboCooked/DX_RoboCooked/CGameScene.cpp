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

#include "CUICloseButton.h"
#include "CUIBoardButton.h"
#include "CUIBarButton.h"
#include "CUIPauseButton.h"


/* µð¹ö±ë¿ë */
#include "CDebugPlayer1.h"
#include "CDebugPlayer2.h"

CGameScene::CGameScene()
	:m_pField(NULL)
	, m_pDebugSphere(NULL)
	, m_pDebugCube(NULL)
	, m_pDebugParts(NULL)
	, m_isTimeStop(false)
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

	CBlueprint* blueprint = new CBlueprint("A00", m_vecParts, D3DXVECTOR3(0,0,0), D3DXVECTOR3(0, 0, 0));
	blueprint->Setup();
	m_vecObject.push_back(blueprint);

	m_pDebugSphere = new CDebugPlayer1(this);
	if (m_pDebugSphere)
		m_pDebugSphere->Setup();

	m_pDebugCube = new CDebugPlayer2(this);
	if (m_pDebugCube)
		m_pDebugCube->Setup();

	m_vecCharacters.push_back(m_pDebugCube);
	m_vecCharacters.push_back(m_pDebugSphere);

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

	CMonster* monster = new CMonster(this);
	m_vecMonster.push_back(monster);
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

	{
		// Gravity Update
		if (m_pDebugCube)
			CPhysicsApplyer::ApplyGravity(m_pDebugCube);

		if (m_pDebugSphere)
			CPhysicsApplyer::ApplyGravity(m_pDebugSphere);

		for (CInteractiveActor* part : m_vecParts)
		{
			CPhysicsApplyer::ApplyGravity(part);
		}
	}
	
	// collide -> update
	{// collide
		//if (m_pDebugSphere)
		//	CPhysicsApplyer::ApplyBound(m_pDebugSphere, m_vecObject[2]);
		if (m_pDebugSphere && m_pDebugCube)
			CPhysicsApplyer::ApplyBound(m_pDebugSphere, m_pDebugCube);

		for (CInteractiveActor* part : m_vecParts)
		{
			CPhysicsApplyer::ApplyBound(m_pDebugSphere, part);
			CPhysicsApplyer::ApplyBound(m_pDebugCube, part);
			for (CInteractiveActor* part2 : m_vecParts)
			{
				if(part != part2)
					CPhysicsApplyer::ApplyBound(part2, part);
			}
		}
		
		for (CInteractiveActor* obj : m_vecObject)
		{
			CPhysicsApplyer::ApplyBound(m_pDebugSphere, obj);
			CPhysicsApplyer::ApplyBound(m_pDebugCube, obj);

			for (CInteractiveActor* part : m_vecParts)
			{
				CPhysicsApplyer::ApplyBound(part, obj);
			}
		}

		for (CActor* pStaticActor : m_vecStaticActor)
		{
			CPhysicsApplyer::ApplyBound(m_pDebugCube, pStaticActor);
			CPhysicsApplyer::ApplyBound(m_pDebugSphere, pStaticActor);
			for (CInteractiveActor* part : m_vecParts)
			{
				CPhysicsApplyer::ApplyBound(part, pStaticActor);
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

		for (CMonster* it : m_vecMonster)
		{
			it->Update();
		}

		if (m_pDebugCube)
			m_pDebugCube->Update();

		if (m_pDebugSphere)
			m_pDebugSphere->Update();

		if (m_pDebugPauseUI)
			m_pDebugPauseUI->Update();
	}
}

void CGameScene::ToggleStop()
{
	m_isTimeStop = !m_isTimeStop;
}

void CGameScene::CC(CCrowdControl * pCC)
{
	cout << "µ¹¸®±â È½¼ö·ÎÀÎÇÑ ±«¼ö ½ºÅ³" << endl;
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
		for (auto it : m_vecParts)
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

		if (combinator->GetCombinPartsLevel() == data->GetCombinPartsLevel() &&
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
