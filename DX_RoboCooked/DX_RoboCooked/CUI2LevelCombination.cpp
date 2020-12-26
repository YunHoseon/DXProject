#include "stdafx.h"
#include "CUI2LevelCombination.h"
#include "CBlueprint.h"
#include "CUITexture.h"


CUI2LevelCombination::CUI2LevelCombination(D3DXVECTOR2 vPos, string sPartsID)
{
	m_vPosition = vPos;
	m_sPartsID = sPartsID;
	Setup();
}


CUI2LevelCombination::~CUI2LevelCombination()
{
}

void CUI2LevelCombination::Setup()
{
	string sFullPath("data/UI");
	sFullPath += string("/") + m_sPartsID + string(".png");
	//sFullPath += string("/") + string("C00") + string(".png"); 테스트용

	char temp[100];
	strcpy(temp, sFullPath.c_str());

	m_pTexture = new CUITexture(temp, temp, temp, m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo(temp);
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
