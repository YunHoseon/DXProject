#include "stdafx.h"
#include "CHarpyWing_L.h"

CHarpyWing_L::CHarpyWing_L()
{
	CStaticMesh* p = g_pStaticMeshManager->GetStaticMesh("Harpy_Wing_L");
	*dynamic_cast<CStaticMesh*> (this) = *p;
	D3DXMATRIXA16 matT, matR, matS, matlR;
	D3DXVECTOR3 vProj(-1, 0, 0.5), vTrans;
	D3DXMatrixScaling(&matS, 0.05, 0.05, 0.05);


	D3DXMATRIXA16 matView, matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXVec3Unproject(&vTrans, &vProj, nullptr, &matProj, &matView, nullptr);

	D3DXVECTOR3 vLookAt(matView._21, matView._22, matView._23);

	float rot = -D3DXVec3Dot(&vLookAt, &D3DXVECTOR3(0, 0, 1));

	D3DXVECTOR3 dir = vTrans + vLookAt, axis;
	D3DXVec3Normalize(&dir, &dir);

	D3DXVec3Cross(&axis, &vLookAt, &dir);
	D3DXMatrixRotationAxis(&matR, &axis, rot);
	D3DXMatrixTranslation(&matT, vTrans.x, vTrans.y, vTrans.z);
	D3DXMatrixRotationZ(&matlR, D3DXToRadian(-10));
	m_matWorld = matlR * matS * matR * matT;
}

CHarpyWing_L::~CHarpyWing_L()
{
}

void CHarpyWing_L::Update()
{
	m_fElapseTime += g_pTimeManager->GetElapsedTime();
	m_fRotY += D3DX_PI * 0.25f * g_pTimeManager->GetElapsedTime() * ((int)m_fElapseTime % 2 ? 1 : -1);
	D3DXMatrixRotationY(&m_matLocal, m_fRotY);
}
