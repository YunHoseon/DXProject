#include "stdafx.h"
#include "CGameScene.h"
#include "CField.h"
#include "CInteractiveActor.h"
#include "CParts.h" //생성할때 사용하기위해


CGameScene::CGameScene()
	:m_pField(NULL)
{
	//Sound Add
	g_SoundManager->AddBGM("data/sound/bgm.mp3");
	g_SoundManager->AddSFX("data/sound/effBBam.mp3", "BBam");
	g_SoundManager->AddSFX("data/sound/effMelem.mp3", "Melem");
	g_EventManager->Attach(EEvent::E_PartsMake, this);

}

CGameScene::~CGameScene()
{
	SafeDelete(m_pField);
	for (auto it : m_vecParts)
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
}

void CGameScene::OnEvent(EEvent eEvent, void * _value)
{
	if (eEvent == EEvent::E_PartsMake)
	{
		CParts* parts = new CParts;
		parts->Setup();
		m_vecParts.push_back(parts);
	}
}
