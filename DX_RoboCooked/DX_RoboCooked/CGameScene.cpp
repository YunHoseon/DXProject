#include "stdafx.h"
#include "CGameScene.h"
#include "CField.h"
#include "CInteractiveActor.h"
#include "CParts.h" //생성할때 사용하기위해
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
#include "CTestPhysics.h"
#include "CWall.h"

/* 디버깅용 */
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
	partStorage->Setup(0, D3DXVECTOR3(5, 0, 2) , "1");
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
	
	CPartVending* partVending = new CPartVending(outlet, this, "2");
	partVending->Setup(0, D3DXVECTOR3(1, 0, -3));
	m_vecObject.push_back(partVending);

	m_pDebugSphere = new CDebugPlayer1(this);
	if (m_pDebugSphere)
		m_pDebugSphere->Setup();

	m_pDebugCube = new CDebugPlayer2(this);
	if (m_pDebugCube)
		m_pDebugCube->Setup();

	m_vecCharacters.push_back(m_pDebugCube);
	m_vecCharacters.push_back(m_pDebugSphere);

	m_pDebugParts = new CParts("999");
	if (m_pDebugParts)
		m_pDebugParts->Setup();
	m_vecParts.push_back(m_pDebugParts);
	
	CParts* m_pDebugParts2 = new CParts("999");
	if (m_pDebugParts2)
		m_pDebugParts2->Setup();
	m_vecParts.push_back(m_pDebugParts2);
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
}

void CGameScene::Update()
{
	if (m_isTimeStop)
		return;


	{
		// Gravity Update
		if (m_pDebugCube)
			CTestPhysics::ApplyGravity(m_pDebugCube);

		if (m_pDebugSphere)
			CTestPhysics::ApplyGravity(m_pDebugSphere);

		for (CInteractiveActor* part : m_vecParts)
		{
			CTestPhysics::ApplyGravity(part);
		}
	}
	
	// collide -> update
	{// collide
		//if (m_pDebugSphere)
		//	CTestPhysics::ApplyBound(m_pDebugSphere, m_vecObject[2]);
		if (m_pDebugSphere && m_pDebugCube)
			CTestPhysics::ApplyBound(m_pDebugSphere, m_pDebugCube);

		for (CInteractiveActor* part : m_vecParts)
		{
			CTestPhysics::ApplyBound(m_pDebugSphere, part);
			CTestPhysics::ApplyBound(m_pDebugCube, part);
			for (CInteractiveActor* part2 : m_vecParts)
			{
				if(part != part2)
					CTestPhysics::ApplyBound(part2, part);
			}
		}
		
		for (CInteractiveActor* obj : m_vecObject)
		{
			CTestPhysics::ApplyBound(m_pDebugSphere, obj);
			CTestPhysics::ApplyBound(m_pDebugCube, obj);

			for (CInteractiveActor* part : m_vecParts)
			{
				CTestPhysics::ApplyBound(part, obj);
			}
		}

		for (CActor* pStaticActor : m_vecStaticActor)
		{
			CTestPhysics::ApplyBound(m_pDebugCube, pStaticActor);
			CTestPhysics::ApplyBound(m_pDebugSphere, pStaticActor);
			for (CInteractiveActor* part : m_vecParts)
			{
				CTestPhysics::ApplyBound(part, pStaticActor);
			}
		}
		// part-part, part-obj 필요
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

		if (m_pDebugCube)
			m_pDebugCube->Update();

		if (m_pDebugSphere)
			m_pDebugSphere->Update();
	}
}

void CGameScene::PausePlayGame()
{
		m_isTimeStop = !m_isTimeStop;

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

//void CGameScene::DownParts(CCharacter* pCharacter,CParts* parts, D3DXVECTOR3 vDir)
//{
//	if (parts != nullptr)
//	{
//		pCharacter->SetPlayerState(ePlayerState::None);
//		parts->DownParts(vDir);
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

void CGameScene::SendPartsToOutlet(CParts * parts, COutlet * outlet)
{
	outlet->AcceptPartsFromVending(parts);
}
