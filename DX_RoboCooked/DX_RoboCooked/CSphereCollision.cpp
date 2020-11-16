#include "stdafx.h"
#include "CSphereCollision.h"

#include "CBoxCollision.h"

static LPD3DXMESH pMesh = nullptr;
CSphereCollision::CSphereCollision(D3DXVECTOR3 vOriginPos, float fRadius, D3DXMATRIXA16* pmatWorld): fRadius(fRadius)
{
	m_eType = EColideType::E_Sphere;
	m_vOriginCenterPos = vOriginPos;
	_RELEASE_COMMENT return;
	m_pmatWorldTM = pmatWorld;
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
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, m_pmatWorldTM);
		g_pD3DDevice->SetTexture(0, NULL);
		D3DMATERIAL9 stMtl{};
		float a = isCollide ? 0 : 1;
		stMtl.Ambient = D3DXCOLOR(1, a, a, 1.0f);
		stMtl.Diffuse = D3DXCOLOR(1, a, a, 1.0f);
		stMtl.Specular = D3DXCOLOR(1, a, a, 1.0f);
		g_pD3DDevice->SetMaterial(&stMtl);
		pMesh->DrawSubset(0);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	
}

void CSphereCollision::Update()
{
	D3DXVec3TransformCoord(&m_vCenterPos, &m_vOriginCenterPos, m_pmatWorldTM);
}

bool CSphereCollision::CollideToBox(CBoxCollision* pTargetCollider)
{
	isCollide = pTargetCollider->CollideToSphere(this);
	return isCollide;
}

bool CSphereCollision::CollideToSphere(CSphereCollision* pTargetCollider)
{
	D3DXVECTOR3 vDist = pTargetCollider->GetCenter() - m_vCenterPos;
	isCollide = false;
	
	if (D3DXVec3LengthSq(&vDist) > (fRadius + pTargetCollider->fRadius) * (fRadius + pTargetCollider->fRadius))
		return false;

	isCollide = true;
	return true;
}
