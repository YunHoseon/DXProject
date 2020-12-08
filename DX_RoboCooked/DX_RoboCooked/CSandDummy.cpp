#include "stdafx.h"
#include "CSandDummy.h"


CSandDummy::CSandDummy(D3DXVECTOR3 vPosition)
{
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Sandpile");

}


CSandDummy::~CSandDummy()
{
}

void CSandDummy::Render()
{
	if (m_pSMesh)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		m_pSMesh->Render();
	}
}

void CSandDummy::Update()
{
}
