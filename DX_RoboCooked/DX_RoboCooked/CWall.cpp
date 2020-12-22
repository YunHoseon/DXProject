#include "stdafx.h"
#include "CWall.h"
#include "CBoxCollision.h"
#include "CTV.h"
CWall::CWall(IInteractCenter* pIntaract, bool b)
	:m_nRotAngleX(0)
	, m_pTV(nullptr)
	, m_pSMesh(nullptr)
{
	m_pInteractCenter = pIntaract;
	g_EventManager->Attach(eEvent::KeyRelease, this);
	if (b)
		m_pTV = new CTV(m_pInteractCenter, &m_matWorld);
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Brick");
	Setup();
	
}


CWall::~CWall()
{
	SafeDelete(m_pTV);
}

void CWall::Setup()
{
	

	D3DXMATRIXA16 matS, matT;

	float fWidth = 30;
	float fHeight = 6;
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

	m_nRotAngleX = 12;
	D3DXMatrixRotationX(&m_matR, D3DXToRadian(m_nRotAngleX));
	D3DXMatrixTranslation(&m_matT, 0, -1.5f, 6);
	m_matWorld = m_matR * m_matT;
}

void CWall::Update()
{


	if (m_pTV)
		m_pTV->Update();

}

void CWall::Render()
{
	_DEBUG_COMMENT string sWallRotationX = string("벽 회전(O/P키) :") + std::to_string(m_nRotAngleX);
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
}

bool CWall::OnEvent(eEvent eEvent, void * _value)
{
	switch (eEvent)
	{
	case eEvent::KeyRelease:
		ReleaseKey();
		break;
	default:
		break;
	}
	return true;
}

void CWall::ReleaseKey()
{
	if (GetAsyncKeyState('O') & 0x0001)
	{
		m_nRotAngleX -= 2;
		if (m_nRotAngleX <= 0)
			m_nRotAngleX = 0;
	}
	else if (GetAsyncKeyState('P') & 0x0001)
	{
		m_nRotAngleX += 2;
		if (m_nRotAngleX >= 90)
			m_nRotAngleX = 90;
	}

	D3DXMatrixRotationX(&m_matR, D3DXToRadian(m_nRotAngleX));
	D3DXMatrixTranslation(&m_matT, 0, -1.5f, 6);
	m_matWorld = m_matR * m_matT;
}
