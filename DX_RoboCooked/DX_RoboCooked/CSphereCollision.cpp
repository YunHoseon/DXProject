#include "stdafx.h"
#include "CSphereCollision.h"

#include "CBoxCollision.h"

static LPD3DXMESH pMesh = nullptr;
CSphereCollision::CSphereCollision(float fRadius): fRadius(fRadius)
{/// 부모 주소
	m_eType = EColideType::E_Sphere;

	_RELEASE_COMMENT return;
	
	if (pMesh == nullptr)
		D3DXCreateSphere(g_pD3DDevice, fRadius, 20, 20, &pMesh, nullptr);
	
}

CSphereCollision::~CSphereCollision()
{
}

void CSphereCollision::Render()
{
	_RELEASE_COMMENT return;

	if(pMesh)
	{
		//g_pD3DDevice->SetRenderState()
	}
	
}

void CSphereCollision::Update()
{
}

bool CSphereCollision::CollideToBox(ICollisionArea* pTargetCollider)
{
	CBoxCollision* box = dynamic_cast<CBoxCollision*>(pTargetCollider);
	isCollide = box->CollideToSphere(this);
	return isCollide;
}

bool CSphereCollision::CollideToSphere(ICollisionArea* pTargetCollider)
{
	CSphereCollision* target = dynamic_cast<CSphereCollision*>(pTargetCollider);
	D3DXVECTOR3 vDist = target->GetCenter() - m_vOriginCenterPos;
	isCollide = false;
	
	if (D3DXVec3LengthSq(&vDist) > (fRadius + target->fRadius) * (fRadius + target->fRadius))
		return false;

	isCollide = true;
	return true;
}
