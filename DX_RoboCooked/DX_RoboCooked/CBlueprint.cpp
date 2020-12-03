#include "stdafx.h"
#include "CBlueprint.h"
#include "CBoxCollision.h"
#include "CSphereCollision.h"
#include "CCharacter.h"
#include "CParts.h"
#include "CInteractiveActor.h"

CBlueprint::CBlueprint(string partsID, vector<CInteractiveActor*>& vecParts, D3DXVECTOR3 position, D3DXVECTOR3 scale, float angle, float partsAngle)
	: m_isCompleted(false)
	, m_onBlueprintParts(NULL)
	, m_pPartsPosition(nullptr)
{
	m_sRightPartsID = partsID;
	m_pVecParts = &vecParts;
	m_vPosition = position;
	m_vScale = scale;
	m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/Blueprint.jpg");
	m_completeBlueprintTexture = g_pTextureManager->GetTexture("data/Texture/CompleteBlueprint.jpg");
	//파츠 아이디에 따라 m_matS,텍스쳐 다르게
	m_fFriction = 0.2f;
	m_nRightPartsAngleY = partsAngle;
	m_nRotAngleY = angle;

	D3DXMatrixIdentity(&m_matInteractCollision);
}


CBlueprint::~CBlueprint()
{
	SafeDelete(m_pPartsPosition);
}

void CBlueprint::Setup()
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

	m_vecVertex_Multi = vecVertex;
	
	D3DXMatrixRotationY(&m_matR, D3DXToRadian(m_nRotAngleY));
	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = m_matS * m_matR * m_matT;

	m_matInteractCollision = m_matT;
	m_pCollision = new CBoxCollision(D3DXVECTOR3(0, -2.f, 0), D3DXVECTOR3(1, 1, 1), &m_matWorld);
	SetScale(m_vScale);
	m_pPartsPosition = new CSphereCollision(D3DXVECTOR3(0, 0.5f, 0), 1.f, &m_matInteractCollision);
	
	if(m_pCollision)
		m_pCollision->Update();
	if (m_pPartsPosition)
		m_pPartsPosition->Update();
}

void CBlueprint::Update()
{
	StoreOnBlueprintParts(); // --> 설계도에 부품을 붙인 상황
}

void CBlueprint::Render()
{
	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
	_DEBUG_COMMENT if (m_pPartsPosition)
		_DEBUG_COMMENT m_pPartsPosition->Render();

	if (CheckBluePrintComplete() == true && m_onBlueprintParts)
	{
		MultiTexture_Render();
	}
	else
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetTexture(0, m_blueprintTexture);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex_Multi.size() / 3, 
			&m_vecVertex_Multi[0], sizeof(ST_PNT_VERTEX));
		g_pD3DDevice->SetTexture(0, 0);
	}
}

void CBlueprint::OnEvent(eEvent eEvent, void * _value)
{
}

void CBlueprint::StoreOnBlueprintParts()
{
	if (m_onBlueprintParts)
		return;
	
	if (m_onBlueprintParts == nullptr)
	{
		for (CInteractiveActor* it : *m_pVecParts)
		{
			if (it->Collide(this))
			{
				m_onBlueprintParts = (CParts*)it;
				m_onBlueprintParts->SetGrabPosition(&m_pPartsPosition->GetCenter());
				m_onBlueprintParts->GetCollision()->SetActive(false);
				break;
			}
		}
	}
}

bool CBlueprint::CheckBluePrintComplete()
{
	if (m_onBlueprintParts && m_sRightPartsID == m_onBlueprintParts->GetPartsID()
		&& m_nRightPartsAngleY == m_onBlueprintParts->GetPartsAngle())
	{
		m_isCompleted = true;
	}
	return m_isCompleted;
}

void CBlueprint::Interact(CCharacter* pCharacter)
{
	if(m_onBlueprintParts)
	{
		// 캐릭터 손에 들려두는 작업
		if (pCharacter->GetPlayerState() == ePlayerState::None)
		{
			m_onBlueprintParts->SetGrabPosition(&pCharacter->GetGrabPartsPosition());
			m_onBlueprintParts->GetCollision()->SetActive(true);
			pCharacter->SetParts(m_onBlueprintParts);									
			m_onBlueprintParts = nullptr;
			m_isCompleted = false;
		}
	}
}

void CBlueprint::MultiTexture_Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	for (int i = 0; i < 2; i++)
	{
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, 0);
	g_pD3DDevice->SetTextureStageState(3, D3DTSS_TEXCOORDINDEX, 0);

	g_pD3DDevice->SetTexture(0, m_blueprintTexture);
	g_pD3DDevice->SetTexture(1, m_completeBlueprintTexture);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSMOOTH);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex_Multi.size() / 3,
		&m_vecVertex_Multi[0],
		sizeof(ST_PNT_VERTEX));

	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTexture(1, NULL);
	g_pD3DDevice->SetTexture(2, NULL);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_RESULTARG, D3DTA_CURRENT);

	for (int i = 0; i < 2; ++i)
	{
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_NONE);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	}
}