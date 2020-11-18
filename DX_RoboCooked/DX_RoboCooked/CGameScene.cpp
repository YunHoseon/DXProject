#include "stdafx.h"
#include "CGameScene.h"
#include "CField.h"
#include "CInteractiveActor.h"
#include "CParts.h" //생성할때 사용하기위해
#include "CPartStorage.h"
#include "ICollisionArea.h"
#include "CActor.h"
#include "CCharacter.h"

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
	for (auto it : m_vecParts)
	{
		SafeDelete(it);
	}
	SafeDelete(m_pDebugSphere);
	SafeDelete(m_pDebugCube);
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
	partStorage->Setup(0, D3DXVECTOR3(5, 0, 2) , 1);

	m_vecObject.push_back(partStorage);

	m_pDebugSphere = new CDebugPlayer1(this);
	if (m_pDebugSphere)
		m_pDebugSphere->Setup();

	m_pDebugCube = new CDebugPlayer2(this);
	if (m_pDebugCube)
		m_pDebugCube->Setup();

	m_vecCharacters.push_back(m_pDebugCube);
	m_vecCharacters.push_back(m_pDebugSphere);

	//m_pDebugParts = new CParts(999);
	//if (m_pDebugParts)
	//	m_pDebugParts->Setup();
	//m_vecParts.push_back(m_pDebugParts);
}

void CGameScene::Render()
{
	for (auto it : m_vecStaticActor)
	{
		it->Render();
	}

	for (auto it : m_vecParts)
	{
		it->Render();
	}

	for (auto it : m_vecObject)
	{
		it->Render();
	}

	for (auto it : m_vecCharacters)
	{
		it->Render();
	}
	
	//if (m_pDebugSphere)
	//	m_pDebugSphere->Render();

	//if (m_pDebugCube)
	//	m_pDebugCube->Render();
}

void CGameScene::Update()
{
	for (auto it : m_vecStaticActor)
	{
		it->Update();
	}

	for (auto it : m_vecParts)
	{
		it->Update();
	}

	for (auto it : m_vecObject)
	{
		it->Update();
	}

	if (m_pDebugCube)
		m_pDebugCube->Update();


	if (m_pDebugSphere)
	{
		m_pDebugSphere->Update();
		m_pDebugSphere->Collide(m_pDebugCube);
	}

	for (auto && value : m_vecObject)
	{
		m_pDebugSphere->Collide(value);
		m_pDebugCube->Collide(value);
	}
}


void CGameScene::GetInteractObject(CCharacter* pCharacter)
{
	for (auto it : m_vecObject)
	{
		if (pCharacter->GetInteractCollsion()->Collide(it->GetCollision()))
		{
			it->Interact(pCharacter);
			break;
		}
	}
}

void CGameScene::AddParts(CParts * parts)
{
	if(parts != NULL)
		m_vecParts.push_back(parts);
}
