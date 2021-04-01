#include "stdafx.h"
#include "CBlueprint.h"
#include "CBoxCollision.h"
#include "CSphereCollision.h"
#include "CCharacter.h"
#include "CParts.h"
#include "CInteractiveActor.h"

CBlueprint::CBlueprint(string partsID, vector<CParts*>& vecParts, D3DXVECTOR3 position, D3DXVECTOR3 scale, float angle, float partsAngle)
	: m_isCompleted(false)
	, m_onBlueprintParts(NULL)
	, m_pInteractCollision(nullptr)
	, m_blueprintTexture(nullptr)
	, m_completeBlueprintTexture(nullptr)
{
	m_sRightPartsID = partsID;
	m_pVecParts = &vecParts;
	m_fFriction = 0.2f;
	SetPosition(position.x, position.y - 0.5f, position.z);
	SetScale(scale);
	SetRotationY(angle);
	m_fRightPartsAngleY = partsAngle;
	m_fMass = 9999.f;

	SetupTexture(partsID);
	m_completeBlueprintTexture = g_pTextureManager->GetTexture("data/Texture/blueprint/blueprint_base.png");
}


CBlueprint::~CBlueprint()
{
	SafeDelete(m_pInteractCollision);
}

void CBlueprint::Setup()
{
	vector<ST_PNT_VERTEX> vecVertex;
	ST_PNT_VERTEX v;
	v.n = D3DXVECTOR3(0, 1, 0);
	
	{
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

		//uv 회전
		D3DXMATRIXA16 mat2dRot;
		D3DXMatrixTransformation2D(&mat2dRot, 0, 0, 0, &D3DXVECTOR2(0.5, 0.5), -m_fRightPartsAngleY, 0);
		for (auto && vertex : vecVertex)
		{
			D3DXVec2TransformCoord(&vertex.t, &vertex.t, &mat2dRot);
		}
	}

	m_vecVertex_Multi = vecVertex;
	
	m_pCollision = new CSphereCollision(D3DXVECTOR3(0, 0.5f, 0), 1.0f, &m_matWorld);
	m_pCollision->SetActive(false);
	m_pInteractCollision = new CSphereCollision(D3DXVECTOR3(0, 0.5f, 0), 1.0f, &m_matWorld);
	
	if(m_pCollision)
		m_pCollision->Update();
	if (m_pInteractCollision)
		m_pInteractCollision->Update();
}

void CBlueprint::Update()
{
	StoreOnBlueprintParts(); // --> 설계도에 부품을 붙인 상황
}

void CBlueprint::Render()
{
	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
	_DEBUG_COMMENT if (m_pInteractCollision)
		_DEBUG_COMMENT m_pInteractCollision->Render();

	if (m_isCompleted)
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

bool CBlueprint::OnEvent(eEvent eEvent, void * _value)
{
	return true;
}

void CBlueprint::StoreOnBlueprintParts()
{
	if (m_onBlueprintParts)
		return;
	
	for (CParts* it : *m_pVecParts)
	{
		if (it->GetCollision()->Collide(m_pInteractCollision))
		{
			m_onBlueprintParts = it;
			m_onBlueprintParts->SetGrabPosition(&m_pInteractCollision->GetCenter());
			m_onBlueprintParts->GetCollision()->SetActive(false);
			m_pCollision->SetActive(true);
			m_pInteractCollision->SetActive(false);

			CheckBluePrintComplete();
			break;
		}
	}
	
}

void CBlueprint::CheckBluePrintComplete()
{
	if (m_onBlueprintParts && m_sRightPartsID == m_onBlueprintParts->GetPartsID()
		&& abs(m_fRightPartsAngleY - m_onBlueprintParts->GetRotY()) < EPSILON)
	{
		m_isCompleted = true;
		g_EventManager->CallEvent(eEvent::CompleteBluePrint, this);
	}
	else
	{
		m_isCompleted = false;
	}
}

void CBlueprint::Interact(CCharacter* pCharacter)
{
	if(m_onBlueprintParts)
	{
		// 캐릭터 손에 들려두는 작업
		if (pCharacter->GetPlayerState() == ePlayerState::None)
		{
			m_onBlueprintParts->GetCollision()->SetActive(true);
			m_onBlueprintParts->SetGrabPosition(&pCharacter->GetGrabPartsPosition());
			pCharacter->SetParts(m_onBlueprintParts);
			m_onBlueprintParts = nullptr;
			m_pCollision->SetActive(false);
			m_pInteractCollision->SetActive(true);
			if(m_isCompleted)
			{
				m_isCompleted = false;
				g_EventManager->CallEvent(eEvent::UnCompleteBluePrint, this);
			}
		}
	}
}

void CBlueprint::SetupTexture(string partsID)
{
	if (partsID == "C00")
		m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/blueprint/blueprint_body_hyper.png");
	else if (partsID == "C01")
		m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/blueprint/blueprint_body_boost.png");
	else if (partsID == "C02")
		m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/blueprint/blueprint_arm.png");
	else if (partsID == "C03")
		m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/blueprint/blueprint_hand_gravity.png");
	else if (partsID == "C04")
		m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/blueprint/blueprint_hand_rolling.png");
	else if (partsID == "C05")
		m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/blueprint/blueprint_leg.png");
	else if (partsID == "C06")
		m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/blueprint/blueprint_foot_trust.png");
	else if (partsID == "C07")
		m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/blueprint/blueprint_foot_infinity.png");
	else if (partsID == "C08")
		m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/blueprint/blueprint_head_hero.png");
	else if (partsID == "C09")
		m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/blueprint/blueprint_head_final.png");
	else if (partsID == "B01")
		m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/blueprint/B01_RC.png");
	else
		m_blueprintTexture = g_pTextureManager->GetTexture("data/Texture/Blueprint.jpg");
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

void CBlueprint::SetPosition(D3DXVECTOR3 vPosition)
{
	CActor::SetPosition(vPosition);
	if (m_pInteractCollision)
		m_pInteractCollision->Update();
}

void CBlueprint::SetPosition(float x, float y, float z)
{
	CActor::SetPosition(x, y, z);
	if (m_pInteractCollision)
		m_pInteractCollision->Update();
}
