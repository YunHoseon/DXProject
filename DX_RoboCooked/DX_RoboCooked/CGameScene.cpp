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
		m_pField->Setup(WIDTH,HEIGHT);
}

void CGameScene::Render()
{
	if (m_pField)
		m_pField->Render();
}

void CGameScene::Update()
{
	
}
