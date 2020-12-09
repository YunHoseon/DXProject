#include "stdafx.h"
#include "CTornado.h"
#include "CSphereCollision.h"

CTornado::CTornado(D3DXVECTOR3 pos)
{
	SetPosition(pos);
	m_pCollision = new CSphereCollision(D3DXVECTOR3(0, 0, 0), 2.0f, &m_matWorld);
	m_pCollision->Update();
}


CTornado::~CTornado()
{
}

void CTornado::Update()
{
}

void CTornado::Render()
{
	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
}
