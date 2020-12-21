#include "stdafx.h"
#include "CUICC.h"

CUICC::CUICC(char* DisabledPath, char* ActivePath, char* HoverPath, D3DXVECTOR3* pPosition):
	CUITexture(DisabledPath, ActivePath, HoverPath, pPosition)
{
}

void CUICC::Render()
{
	//return;
	if (m_pTargetPosition)
	{
		m_matWorld = g_matIdentity;
		D3DVIEWPORT9 vp;
		D3DXMATRIXA16 matView, matProj;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		g_pD3DDevice->GetViewport(&vp);

		D3DXVECTOR3 pos;
		D3DXVec3Project(&pos, m_pTargetPosition, &vp, &matProj, &matView, nullptr);
		m_vPosition.x = pos.x;
		m_vPosition.y = pos.y;
	}

	m_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc;
	m_Sprite->SetTransform(&g_matIdentity);

	{
		SetRect(&rc, 0, 0, m_DisabledInfo.Width, m_DisabledInfo.Height);
		m_Sprite->Draw(m_DisabledTexture,
			&rc,
			&g_vZero,
			&D3DXVECTOR3(m_vPosition.x - m_DisabledInfo.Width * 0.5f, m_vPosition.y - m_DisabledInfo.Height, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	m_Sprite->End();

}
