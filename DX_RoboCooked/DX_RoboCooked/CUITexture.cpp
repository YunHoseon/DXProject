#include "stdafx.h"
#include "CUITexture.h"


CUITexture::CUITexture( char* DisabledPath, char* ActivePath, char* HoverPath, D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup(DisabledPath, ActivePath, HoverPath);
}

CUITexture::CUITexture(char * DisabledPath, char * ActivePath, char * HoverPath,D3DXMATRIXA16* pWorld)
{
	m_vPosition.x = 0;
	m_vPosition.y = 0;
	m_pTargetWorldTM = pWorld;
	Setup(DisabledPath, ActivePath, HoverPath);
}

CUITexture::CUITexture(char* DisabledPath, char* ActivePath, char* HoverPath, D3DXVECTOR3* pPos)
{
	m_pTargetPosition = pPos;
	Setup(DisabledPath, ActivePath, HoverPath);
}


CUITexture::~CUITexture()
{
	SafeRelease(m_Sprite);
}

void CUITexture::Setup(char * DisabledPath, char * ActivePath, char * HoverPath)
{
	D3DXCreateSprite(g_pD3DDevice, &m_Sprite);

	if (DisabledPath == NULL)
		return;
	m_DisabledTexture = g_pUITextureManager->GetTexture(DisabledPath);
	m_DisabledInfo = g_pUITextureManager->GetTextureInfo(DisabledPath);

	if (ActivePath == NULL)
	{
		m_ActiveTexture = nullptr;
		return;
	}

	m_ActiveTexture = g_pUITextureManager->GetTexture(ActivePath);
	m_ActiveInfo = g_pUITextureManager->GetTextureInfo(ActivePath);

	if (HoverPath == NULL)
	{
		m_HoverTexture = nullptr;
		return;
	}

	m_HoverTexture = g_pUITextureManager->GetTexture(HoverPath);
	m_HoverInfo = g_pUITextureManager->GetTextureInfo(HoverPath);
}

void CUITexture::Update()
{

}

void CUITexture::Render()
{
	if (m_isActive)
		RenderTexture(m_eUIState);
}

void CUITexture::RenderTexture(eUIState state)
{
	if (m_pTargetWorldTM)
	{
		D3DVIEWPORT9 vp;

		D3DXMATRIXA16 matView, matProj, matWorld;
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetViewport(&vp);

		D3DXVECTOR3 pos;
		D3DXVec3Project(&pos,&g_vZero, &vp,&matProj,&matView,m_pTargetWorldTM);
		m_vPosition.x = pos.x;
		m_vPosition.y = pos.y;
	}

	m_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	
	RECT rc;
	m_Sprite->SetTransform(&g_matIdentity);

	if (state == eUIState::Up)
	{
		SetRect(&rc, 0, 0, m_DisabledInfo.Width, m_DisabledInfo.Height);
		m_Sprite->Draw(m_DisabledTexture,
			&rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if (state == eUIState::Down)
	{
		if (m_ActiveTexture == nullptr)
			return;
		SetRect(&rc, 0, 0, m_ActiveInfo.Width, m_ActiveInfo.Height);
		m_Sprite->Draw(m_ActiveTexture,
			&rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if (state == eUIState::Hover)
	{
		if (m_HoverTexture == nullptr)
			return;
		SetRect(&rc, 0, 0, m_HoverInfo.Width, m_HoverInfo.Height);
		m_Sprite->Draw(m_HoverTexture,
			&rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	m_Sprite->End();
}

