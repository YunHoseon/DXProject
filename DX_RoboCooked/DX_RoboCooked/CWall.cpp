#include "stdafx.h"
#include "CWall.h"
#include "CBoxCollision.h"
#include "CTV.h"
CWall::CWall(IInteractCenter* pIntaract, bool hasTV, float fWidth, float fHeight)
	:m_nRotAngleX(0)
	, m_pTV(nullptr)
	, m_pSMesh(nullptr)
{
	m_pInteractCenter = pIntaract;
	if (hasTV)
	{
		m_pTV = new CTV(m_pInteractCenter, &m_matWorld);
		g_EventManager->Attach(eEvent::KeyRelease, this);
	}
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Brick");
	Setup(fWidth, fHeight);
	m_fMass = 9999.f;
}


CWall::~CWall()
{
	SafeDelete(m_pTV);
}

void CWall::Setup(float fWidth, float fHeight)
{
	D3DXMATRIXA16 matS, matT;

	float fStartX = fWidth * -0.5f * BLOCK_SIZE + BLOCK_SIZE * 0.5f;
	float fStartY = BLOCK_SIZE * 0.5f;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	{
		for (int i = 0; i < fWidth; ++i)
		{
			for (int j = 0; j < fHeight; ++j)
			{
				D3DXMatrixTranslation(&matT, fStartX + i * BLOCK_SIZE, fStartY + j * BLOCK_SIZE, 0);
				m_vecMeshLocalMatrix.push_back(matS * matT);
			}
		}
	}
	D3DXVECTOR3 vMin(fWidth * -0.5f * BLOCK_SIZE, 0, -0.5f);
	D3DXVECTOR3 vMax(fWidth * 0.5f * BLOCK_SIZE, fHeight * BLOCK_SIZE, 0.5f);
	m_pCollision = new CBoxCollision((vMax + vMin) * 0.5f, (vMax - vMin)*1.1f, &m_matWorld);
	m_nRotAngleX = 12;
	D3DXMatrixRotationX(&m_matR, D3DXToRadian(m_nRotAngleX));
	SetPosition(0, -1.5f, 6);
	m_pCollision->Update();
}

void CWall::Update()
{


	if (m_pTV)
		m_pTV->Update();


}

void CWall::Render()
{
	_DEBUG_COMMENT string sWallRotationX = string("�� ȸ��(O/PŰ) :") + std::to_string(m_nRotAngleX);
	_DEBUG_COMMENT RECT rc;
	_DEBUG_COMMENT SetRect(&rc, 0, 100, 0, 0);
	_DEBUG_COMMENT LPD3DXFONT pFont = g_pFontManager->GetFont(CFontManager::eFontType::DEFAULT);

	_DEBUG_COMMENT pFont->DrawTextA(NULL,
	_DEBUG_COMMENT	sWallRotationX.c_str(),
	_DEBUG_COMMENT	sWallRotationX.length(),
	_DEBUG_COMMENT	&rc,
	_DEBUG_COMMENT	DT_LEFT | DT_TOP | DT_NOCLIP,
	_DEBUG_COMMENT	D3DCOLOR_XRGB(255, 255, 255));

	
	for (int i = 0; i < m_vecMeshLocalMatrix.size(); ++i)
	{		
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_vecMeshLocalMatrix[i] * m_matWorld));
		m_pSMesh->Render();
	}
	g_pD3DDevice->SetTexture(0, 0);

	if (m_pTV)
		m_pTV->Render();
	_DEBUG_COMMENT if (m_pCollision)
	_DEBUG_COMMENT 	m_pCollision->Render();
}

bool CWall::OnEvent(eEvent eEvent, void * _value)
{
	switch (eEvent)
	{
	case eEvent::KeyRelease:
		ReleaseKey(_value);
		break;
	default:
		break;
	}
	return true;
}

void CWall::ReleaseKey(void* _value)
{
	ST_KeyInputEvent* data = static_cast<ST_KeyInputEvent*>(_value);
	_DEBUG_COMMENT if (data->wKey == 'O')
	_DEBUG_COMMENT {
	_DEBUG_COMMENT 	m_nRotAngleX -= 2;
	_DEBUG_COMMENT 	if (m_nRotAngleX <= 0)
	_DEBUG_COMMENT 		m_nRotAngleX = 0;
	_DEBUG_COMMENT 	D3DXMatrixRotationX(&m_matR, D3DXToRadian(m_nRotAngleX));
	_DEBUG_COMMENT }
	_DEBUG_COMMENT else if (data->wKey == 'P')
	_DEBUG_COMMENT {
	_DEBUG_COMMENT 	m_nRotAngleX += 2;
	_DEBUG_COMMENT 	if (m_nRotAngleX >= 90)
	_DEBUG_COMMENT 		m_nRotAngleX = 90;
	_DEBUG_COMMENT 	D3DXMatrixRotationX(&m_matR, D3DXToRadian(m_nRotAngleX));
	_DEBUG_COMMENT }

	
	m_matWorld = m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->Update();
}

bool CWall::Collide(CActor* target, D3DXVECTOR3* pNormal)
{
	bool b = target->Collide(this, pNormal);
	if (pNormal)
		*pNormal *= -1;

	if (b)
		target->GetCollision()->SetIsCollide(false);
	
	return b;
}
