#include "stdafx.h"
#include "CUIClearTime.h"
#include "CUITexture.h"
#include "CUIText.h"


CUIClearTime::CUIClearTime(D3DXVECTOR2 vPos, D3DXVECTOR2 vTextPos, string sTimeText, eTextType eType) : m_eType(eType)
{
	m_vPosition = vPos;
	m_vTextPosition = vTextPos;
	m_sText = sTimeText;
	Setup();
}


CUIClearTime::~CUIClearTime()
{
}

void CUIClearTime::Setup()
{
	m_pTexture = new CUITexture("data/UI/clearTime.png", "data/UI/clearTime.png", "data/UI/clearTime.png", m_vPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/popUp_clear.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);

	if (m_sText.empty())
		return;
	m_pText = new CUIText(m_sText, m_vTextPosition, 500, 200, m_eType);


}
