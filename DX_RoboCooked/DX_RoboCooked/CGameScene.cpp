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
#include "COutlet.h"
#include "CPartVending.h"
#include "CTestPhysics.h"

/* 디버깅용 */
#include "CDebugPlayer1.h"
#include "CDebugPlayer2.h"

CGameScene::CGameScene()
	:m_pField(NULL)
	, m_pDebugSphere(NULL)
	, m_pDebugCube(NULL)
	, m_pDebugParts(NULL)
{
	//Sound Add
	g_SoundManager->AddBGM("data/sound/bgm.mp3");
	g_SoundManager->AddSFX("data/sound/effBBam.mp3", "BBam");
	g_SoundManager->AddSFX("data/sound/effMelem.mp3", "Melem");
}

CGameScene::~CGameScene()
{
	SafeDelete(m_pField);
	for (CInteractiveActor* it : m_vecParts)
	{
		SafeDelete(it);
	}
	
	for (CCharacter* it : m_vecCharacters)
	{
		SafeDelete(it);
	}
	SafeDelete(m_pDebugParts);
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
	
	CPartStorage* partStorage = new CPartStorage(this);
	partStorage->Setup(0, D3DXVECTOR3(5, 0, 2) , "1");
	m_vecObject.push_back(partStorage);

	CPartCombinator* partCombinator = new CPartCombinator(this, ECombinatorType::E_2stManual);
	partCombinator->Setup(45.0f, D3DXVECTOR3(-2, 0, 2));
	m_vecObject.push_back(partCombinator);

	CCombinatorButton* combinatorButton = new CCombinatorButton(partCombinator);
	combinatorButton->Setup(0,D3DXVECTOR3(1,0,-1));
	m_vecObject.push_back(combinatorButton);

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
	//{
	//	// Gravity Update
	//	if (m_pDebugCube)
	//		CTestPhysics::ApplyGravity(m_pDebugCube);

	//	if (m_pDebugSphere)
	//		CTestPhysics::ApplyGravity(m_pDebugSphere);

	//	for (CInteractiveActor* part : m_vecParts)
	//	{
	//		CTestPhysics::ApplyGravity(part);
	//	}
	//}
	
	// collide -> update
	{// collide
		if (m_pDebugSphere && m_pDebugCube)
			CTestPhysics::ApplyBound(m_pDebugSphere, m_pDebugCube);

		for (CInteractiveActor* obj : m_vecObject)
		{
			CTestPhysics::ApplyBound(m_pDebugSphere, obj);
			CTestPhysics::ApplyBound(m_pDebugCube, obj);
		}

		for (CInteractiveActor* part : m_vecParts)
		{
			CTestPhysics::ApplyBound(m_pDebugSphere, part);
			CTestPhysics::ApplyBound(m_pDebugCube, part);
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
	if(parts != nullptr)
		m_vecParts.push_back(parts);
}

void CGameScene::DownParts(CCharacter* pCharacter,CParts* parts, D3DXVECTOR3 vDir)
{
	if (parts != nullptr)
	{
		pCharacter->SetPlayerState(EPlayerState::E_None);
		parts->DownParts(vDir);
	}
}

void CGameScene::CheckAroundCombinator(CPartCombinator* combinator)
{
	map<CParts*,float> veclength;
	for (CInteractiveActor * it : m_vecParts)
	{
		CParts* data = static_cast<CParts*>(it);
		if (combinator->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			D3DXVECTOR3 vDirection = combinator->GetPosition() - data->GetPosition();
			veclength[data] = D3DXVec3Length(&vDirection);	
			//combinator->PartsInteract(static_cast<CParts*>(it)); //형변환해서 값을 넣어준다.
			//return;
		}
	}


	for(auto it : veclength)
	{
		combinator->PartsInteract(it.first);
	}
}

void CGameScene::SendPartsToOutlet(CParts * parts, COutlet * outlet)
{
	outlet->AcceptPartsFromVending(parts);
}
