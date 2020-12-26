#include "stdafx.h"
#include "CUIWhiteboard.h"
#include "CUI1LevelCombination.h"
#include "CUI2LevelCombination.h"
#include "CUI1LevelCombinatorImage.h"
#include "CUI2LevelCombinatorImage.h"
#include "CBlueprint.h"
#include "CUITexture.h"

CUIWhiteboard::CUIWhiteboard(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIWhiteboard::~CUIWhiteboard()
{
}

void CUIWhiteboard::Setup()
{
	//D3DVIEWPORT9 vp;
	//g_pD3DDevice->GetViewport(&vp);
	//CUI* board = new CUISubWhiteboard(D3DXVECTOR2(vp.Width / 2 - 584,vp.Height / 2 - 475));
	//AddChild(board);

	m_pTexture = new CUITexture("data/UI/popUp_Board_new.png", NULL, NULL, m_vPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/popUp_Board_new.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);


	CUI* combinator1Lv = new CUI1LevelCombinatorImage(D3DXVECTOR2(m_vPosition.x + 220, m_vPosition.y + 80));
	AddChild(combinator1Lv);
	CUI* combinator2Lv = new CUI2LevelCombinatorImage(D3DXVECTOR2(m_vPosition.x + 570, m_vPosition.y + 80));
	AddChild(combinator2Lv);
	CUI* combination1lv = new CUI1LevelCombination(D3DXVECTOR2(m_vPosition.x + 110, m_vPosition.y + 200));
	AddChild(combination1lv);

}

void CUIWhiteboard::SetFormula(vector<CBlueprint*>& vBp)
{
	
	int iTemp = 0;
	for (CBlueprint* it : vBp)
	{
		CUI* combination2lv = new CUI2LevelCombination(D3DXVECTOR2(m_vPosition.x + 470, m_vPosition.y + 200 + iTemp * 80), it->GetRightPartsID());
		AddChild(combination2lv);
		iTemp++;
	}
	
}
