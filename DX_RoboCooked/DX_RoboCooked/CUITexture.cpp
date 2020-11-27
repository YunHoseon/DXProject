#include "stdafx.h"
#include "CUITexture.h"


CUITexture::CUITexture(char* ActivePath, char* DisabledPath, char* HoverPath, D3DXVECTOR2 vPos)
{
	D3DXCreateSprite(g_pD3DDevice, &m_Sprite);
	m_vPosition = vPos;

	if (ActivePath == NULL)
		return;

	m_ActiveTexture		= g_pUITextureManager->GetTexture(ActivePath);
	m_ActiveInfo		= g_pUITextureManager->GetTextureInfo(ActivePath);

	if (DisabledPath == NULL)
		return;
	m_DisabledTexture	= g_pUITextureManager->GetTexture(DisabledPath);
	m_DisabledInfo		= g_pUITextureManager->GetTextureInfo(DisabledPath);

	if (HoverPath == NULL)
		return;
	m_HoverTexture		= g_pUITextureManager->GetTexture(HoverPath);
	m_HoverInfo			= g_pUITextureManager->GetTextureInfo(HoverPath);

}


CUITexture::~CUITexture()
{
	SafeRelease(m_Sprite);
}

void CUITexture::Update()
{
	D3DXMATRIXA16 matS,matT,matR;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y,0);
	m_matWorld = matS * matR * matT;

	if (m_pParentWorldTM)
		m_matWorld *= *m_pParentWorldTM;
}

void CUITexture::Render()
{
	m_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	//이미지 출력
	RECT rc;

	////>>: UI도 회전같은걸 시킬수있어
	//D3DXMATRIXA16 matS, matR, mat;
	////사진 위치  matTranslation;

	//mat = m_matWorldTM;

	m_Sprite->SetTransform(&m_matWorld);


	SetRect(&rc, 0, 0, m_ActiveInfo.Width, m_ActiveInfo.Height);
	m_Sprite->Draw(m_ActiveTexture,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(150, 255, 255, 255)); // A가 알파블랜딩값




	m_Sprite->End();
}

