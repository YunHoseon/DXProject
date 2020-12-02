#include "stdafx.h"
#include "CPartAutoCombinator.h"
#include "CBoxCollision.h"
#include "CSphereCollision.h"
#include "CParts.h"
#include "IInteractCenter.h"
#include "CCharacter.h"

CPartAutoCombinator::CPartAutoCombinator(IInteractCenter* pInteractCenter, eCombinatorPartsLevel eType, float fAngle, D3DXVECTOR3 vPosition):
	CPartCombinator(pInteractCenter, eType, fAngle, vPosition)
{
	switch (m_eLevel)
	{
	case eCombinatorPartsLevel::ONE:
		m_nMaxPartsCount = 2;
		break;
	case eCombinatorPartsLevel::TWO:
		m_nMaxPartsCount = 3;
		break;
	}
	Setup(fAngle, vPosition);
}


CPartAutoCombinator::~CPartAutoCombinator()
{
}

void CPartAutoCombinator::Update()
{
	if (m_eCombinatorLoadState == eCombinatorLoadState::LoadImpossible &&
		m_eCombinatorActionState == eCombinatorActionState::Usable)
		CombineParts();
	
	if(m_isCombine && m_pParts == nullptr)
		DischargeParts();

	if (m_eCombinatorLoadState == eCombinatorLoadState::LoadPossible && m_pParts == nullptr)
		m_pInteractCenter->CheckAroundCombinator(this);
}

void CPartAutoCombinator::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_CombinatorTexture);

	D3DMATERIAL9 mtlStorage;
	ZeroMemory(&mtlStorage, sizeof(D3DMATERIAL9));
	mtlStorage.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	mtlStorage.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	mtlStorage.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	g_pD3DDevice->SetMaterial(&mtlStorage);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->SetTexture(0, 0);

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();

	_DEBUG_COMMENT if (m_pPartsInteractCollision)
		_DEBUG_COMMENT m_pPartsInteractCollision->Render();
}

void CPartAutoCombinator::Interact(CCharacter* pCharacter)
{
	if (m_pParts == nullptr || pCharacter->GetPlayerState() != ePlayerState::None)
		return;
	pCharacter->SetParts(m_pParts);
	m_pParts->SetGrabPosition(&pCharacter->GetGrabPartsPosition());
	m_pParts->GetCollision()->SetActive(true);
	m_pParts = nullptr;
}

void CPartAutoCombinator::PartsInteract(CParts* pParts)
{
	m_nPartsCount++;
	
	if (m_nPartsCount > m_nMaxPartsCount)
	{
		return;
	}

	if(m_nPartsCount == m_nMaxPartsCount)
		m_eCombinatorLoadState = eCombinatorLoadState::LoadImpossible;


	pParts->GetCollision()->SetActive(false);
	pParts->SetCombinatorPosition(m_vPosition);
	pParts->SetMoveParts(true);
}

void CPartAutoCombinator::OnEvent(eEvent eEvent, void* _value)
{
}

void CPartAutoCombinator::CombineParts()
{
	m_fElapsedTime += g_pTimeManager->GetElapsedTime();

	if (m_fElapsedTime >= m_fCombineTime)
	{
		m_fElapsedTime = 0;
		ReadytoCarryParts();
	}
}

void CPartAutoCombinator::DischargeParts()
{
	//if (m_vecDischargeParts.empty())
	//{
	//	m_nPartsCount = 0;
	//	m_eCombinatorActionState = eCombinatorActionState::Unusable;
	//	m_eCombinatorLoadState = eCombinatorLoadState::LoadPossible;
	//	m_isCombine = false;
	//	return;
	//}

	m_nPartsCount = 0;
	m_eCombinatorActionState = eCombinatorActionState::Unusable;
	m_eCombinatorLoadState = eCombinatorLoadState::LoadPossible;
	m_isCombine = false;

	m_pParts = *m_vecDischargeParts.begin();
	//m_pParts->SetPosition(m_vOnCombinatorPosition);
	m_pParts->SetGrabPosition(&m_vOnCombinatorPosition);
	m_vecDischargeParts.clear();
}

void CPartAutoCombinator::InsertParts(CParts* p)
{
	m_multimapParts.insert(std::make_pair(p->GetPartsID(), p));
}

void CPartAutoCombinator::ReadytoCarryParts()
{
	m_isCombine = true;
	CParts* parts = Make();

	m_vecDischargeParts.push_back(parts);
	m_pInteractCenter->AddParts(parts);
}

CParts* CPartAutoCombinator::Make()
{
	string strResult;
	for (auto it : m_multimapParts)
	{
		strResult += it.first;
		m_pInteractCenter->DeleteParts(it.second);
	}
	m_multimapParts.clear();

	CParts* Parts = g_pPartsManager->CreateParts(g_pPartsManager->GetIDFromFormula(strResult));
	
	return Parts;
}

void CPartAutoCombinator::Setup(float fAngle, D3DXVECTOR3 vPosition)
{
	vector<ST_PNT_VERTEX> vecVertex;
	ST_PNT_VERTEX v;
	v.n = D3DXVECTOR3(0, 1, 0);

	{
		//front
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 1);
		vecVertex.push_back(v);

		//back
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 0);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);

		//left
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	v.t = D3DXVECTOR2(1, 1);
		vecVertex.push_back(v);

		//right
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 1);
		vecVertex.push_back(v);

		//top
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 1);
		vecVertex.push_back(v);

		//bottom
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	v.t = D3DXVECTOR2(0, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 1);
		vecVertex.push_back(v);
	}

	m_vecVertex = vecVertex;

	m_CombinatorTexture = g_pTextureManager->GetTexture(("data/Texture/city_auto.png"));

	D3DXMatrixRotationY(&m_matR, D3DXToRadian(fAngle));
	D3DXMatrixTranslation(&m_matT, vPosition.x, 0, vPosition.z);

	m_pCollision = new CBoxCollision(g_vZero, D3DXVECTOR3(1.0f, 1.0f, 1.0f), &m_matWorld);

	m_pPartsInteractCollision = new CSphereCollision(g_vZero, 2.0f, &m_matWorld);

	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->Update();
	if (m_pPartsInteractCollision)
		m_pPartsInteractCollision->Update();
}
