#include "stdafx.h"
#include "CTornado.h"
#include "CSphereCollision.h"

CTornado::CTornado()
{
	m_pCollision = new CSphereCollision(D3DXVECTOR3(0, 0, 0), 2.0f, &m_matWorld);
	m_pCollision->Update();
}


CTornado::~CTornado()
{
}

void CTornado::Update()
{
	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = m_matT;
}

void CTornado::Render()
{
	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
}
