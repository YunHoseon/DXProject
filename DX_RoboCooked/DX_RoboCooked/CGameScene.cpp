#include "stdafx.h"
#include "CGameScene.h"

#include "CField.h"


CGameScene::CGameScene()
	:m_pField(NULL)
{
}

CGameScene::~CGameScene()
{
	SafeDelete(m_pField);
}

void CGameScene::Init()
{
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

}

void CGameScene::Update()
{
	for (auto it : m_vecStaticActor)
	{
		it->Update();
	}
}
