#include "stdafx.h"
#include "CActor.h"
#include "ICollisionArea.h"


CActor::CActor(): m_pCollision(nullptr)
{
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);
}


CActor::~CActor()
{
}

bool CActor::Collide(CActor* target)
{
	return m_pCollision->Collide(target->m_pCollision);
}
