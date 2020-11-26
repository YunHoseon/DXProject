#include "stdafx.h"
#include "cSprite.h"


cSprite::cSprite()
	:m_btnCheck(false)
{
	D3DXMatrixIdentity(&matTranslation);
	D3DXMatrixIdentity(&m_matWorldTM);
	Setup();
}


cSprite::~cSprite()
{
	SafeRelease(m_pSprite);
	SafeRelease(m_pDisabledTextureUI);
	SafeRelease(m_pActiveTextureUI);
}

void cSprite::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}

void cSprite::Update()
{

}

void cSprite::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	//이미지 출력
	RECT rc;

	//>>: UI도 회전같은걸 시킬수있어
	D3DXMATRIXA16 matS, matR,mat;
	//사진 위치  matTranslation;

	mat = m_matWorldTM;

	m_pSprite->SetTransform(&mat);

	if(!m_btnCheck)
	{
		SetRect(&rc, 0, 0, m_DisabledInfo.Width, m_DisabledInfo.Height);
		m_pSprite->Draw(m_pDisabledTextureUI,
			&rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(150, 255, 255, 255)); // A가 알파블랜딩값
	}
	else
	{
		SetRect(&rc, 0, 0, m_ActiveInfo.Width, m_ActiveInfo.Height);
		m_pSprite->Draw(m_pActiveTextureUI,
			&rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(150, 255, 255, 255)); // A가 알파블랜딩값
	}



	m_pSprite->End();
}

void cSprite::BtnOnOff()
{
	m_btnCheck = !m_btnCheck;
}

