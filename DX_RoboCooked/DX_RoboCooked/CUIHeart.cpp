#include "stdafx.h"
#include "CUIHeart.h"

CUIHeart::CUIHeart():
	CUITexture("data/UI/harpy_skill_1.png", nullptr, nullptr, D3DXVECTOR2(960, 540)),
	m_matRotate(g_matIdentity),
	m_matWorld(g_matIdentity),
	m_fRot(0),
	m_fElapsedTime(0),
	m_fDuration(4)
{
	D3DXMATRIXA16 ls, lt, wt;
	D3DXMatrixScaling(&ls, 0.5, 0.5, 1);
	D3DXMatrixTranslation(&lt, -(float)m_DisabledInfo.Width * 0.5f, -(float)m_DisabledInfo.Height * 0.5f, 0);
	m_matLocal = lt * ls;
	D3DXMatrixTranslation(&wt, 1920 * 0.5f, 1080 * 0.5f, 0);
	m_matWorld = wt;
}

CUIHeart::~CUIHeart()
{
}

void CUIHeart::Update()
{
	m_fElapsedTime += g_pTimeManager->GetElapsedTime();
	//if(m_fElapsedTime <= m_fDuration)
	{
		int i = round(m_fElapsedTime);
		m_fRot += D3DX_PI * 0.25f * g_pTimeManager->GetElapsedTime() * (i % 2 ? -1 : 1);
		D3DXMatrixRotationZ(&m_matRotate, m_fRot);
	}
}

void CUIHeart::Render()
{
	m_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	//이미지 출력
	RECT rc;

	m_Sprite->SetTransform(&(m_matLocal * m_matRotate * m_matWorld));
	
	//m_Sprite->SetTransform(&g_matIdentity);

	SetRect(&rc, 0, 0, m_DisabledInfo.Width, m_DisabledInfo.Height);
	m_Sprite->Draw(m_DisabledTexture,
		&rc,
		//&D3DXVECTOR3(m_DisabledInfo.Width * 0.5f, m_DisabledInfo.Height * 0.5f, 0),
		&g_vZero,
		//&D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 0),
		&g_vZero,
		D3DCOLOR_ARGB(255, 255, 255, 255));


	m_Sprite->End();
}
