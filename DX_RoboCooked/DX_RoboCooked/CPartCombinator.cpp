#include "stdafx.h"
#include "CPartCombinator.h"
#include "CActor.h"
#include "IInteractCenter.h"


CPartCombinator::CPartCombinator(IInteractCenter* pInteractCenter, eCombinatorPartsLevel eType, float fAngle, D3DXVECTOR3 vPosition) :
	m_eLevel(eType),
	m_eCombinatorLoadState(eCombinatorLoadState::LoadPossible),
	m_CombinatorTexture(nullptr),
	m_pPartsInteractCollision(NULL),
	//m_vOnCombinatorPosition(vPosition.x, vPosition.y + 2.5f, vPosition.z),
	m_pParts(NULL),
	m_isCombine(false),
	m_fElapsedTime(0),
	m_fCombineTime(5.f),
	m_nPartsCount(0),
	m_eCombinatorActionState(eCombinatorActionState::Usable),
	m_nMaxPartsCount(0),
	m_pSMesh(nullptr),
	m_pUICombinatorGauge(nullptr),
	m_DestroyTrashCountTime(0)
{
	m_vecOnCombinatorPosition.push_back(D3DXVECTOR3(vPosition.x - 0.5f, vPosition.y + 2.5f, vPosition.z));
	m_vecOnCombinatorPosition.push_back(D3DXVECTOR3(vPosition.x, vPosition.y + 2.5f, vPosition.z));
	m_vecOnCombinatorPosition.push_back(D3DXVECTOR3(vPosition.x + 0.5f, vPosition.y + 2.5f, vPosition.z));

	m_pInteractCenter = pInteractCenter;
	m_vPosition = vPosition;
	m_fMass = 9999.f;
}


CPartCombinator::~CPartCombinator()
{
	
}

void CPartCombinator::CreateShadowMap()
{
	g_pRenderShadowManager->GetCreateShadowShader()->SetMatrix("gWorldMatrix", &m_matWorld);
	UINT numPasses = 0;
	g_pRenderShadowManager->GetCreateShadowShader()->Begin(&numPasses, NULL);

	for (UINT i = 0; i < numPasses; ++i)
	{
		g_pRenderShadowManager->GetCreateShadowShader()->BeginPass(i);
		{
			if (m_pSMesh)
				m_pSMesh->CreateShadowMap();
		}
		g_pRenderShadowManager->GetCreateShadowShader()->EndPass();
	}

	g_pRenderShadowManager->GetCreateShadowShader()->End();
}

