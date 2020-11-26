#include "stdafx.h"
#include "CUISprite.h"

CUISprite::CUISprite(char* OffBtnPath, char* OnBtnPath, char* HoverBtnPath, D3DXVECTOR2 vPosition)
{
	Setup(vPosition);


	string Path(OffBtnPath);

	m_pDisabledTextureUI = g_pUITextureManager->GetTexture(Path);
	m_DisabledInfo = g_pUITextureManager->GetTextureInfo(Path);

	if (OnBtnPath == NULL)
		return;

	Path = OnBtnPath;

	m_pActiveTextureUI = g_pUITextureManager->GetTexture(Path);
	m_ActiveInfo = g_pUITextureManager->GetTextureInfo(Path);
	

	
}

CUISprite::~CUISprite()
{
}

void CUISprite::Setup(D3DXVECTOR2 vecTranslation)
{
	D3DXMatrixTranslation(&matTranslation, vecTranslation.x, vecTranslation.y, 0);
}
