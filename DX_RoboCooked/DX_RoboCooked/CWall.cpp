#include "stdafx.h"
#include "CWall.h"
#include "CBoxCollision.h"
#include "CTV.h"
CWall::CWall(IInteractCenter* pIntaract)
	:m_nRotAngleX(0)
	, m_pTV(nullptr)
	, m_pMesh(nullptr)
{
	m_pInteractCenter = pIntaract;
	g_EventManager->Attach(eEvent::KeyRelease, this);
	Setup();
}


CWall::~CWall()
{
	SafeDelete(m_pTV);
	SafeRelease(m_pMesh);
}

void CWall::Setup()
{
	m_pTV = new CTV(m_pInteractCenter, &m_matWorld);
	vector<ST_PNT_VERTEX> vecVertex;
	ST_PNT_VERTEX v;
	

	{
		//front
		v.n = D3DXVECTOR3(0, 0, -1);
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
		v.n = D3DXVECTOR3(0, 0, 1);
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
		v.n = D3DXVECTOR3(-1, 0, 0);
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
		v.n = D3DXVECTOR3(1, 0, 0);
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
		v.n = D3DXVECTOR3(0, 1, 0);
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
		v.n = D3DXVECTOR3(0, -1, 0);
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

	m_wallTexture = g_pTextureManager->GetTexture(("data/Texture/box.jpg"));
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 30.0f, 12.0f, 1.0f);
	D3DXMatrixTranslation(&matT, 0.0f, 6.0f, 0.0f);
	mat = matS * matT;

	for (size_t i = 0; i < vecVertex.size(); ++i)
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &mat);

	D3DXCreateMeshFVF(12, 12 * 3, D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, g_pD3DDevice, &m_pMesh);
	{
		ST_PNT_VERTEX* pVertex = NULL;
		m_pMesh->LockVertexBuffer(0, (LPVOID*)&pVertex);
		memcpy(pVertex, &vecVertex[0], vecVertex.size() * sizeof ST_PNT_VERTEX);
		m_pMesh->UnlockVertexBuffer();

		WORD* pIndex = NULL;
		m_pMesh->LockIndexBuffer(0, (LPVOID*)&pIndex);
		for (int i = 0; i < vecVertex.size(); ++i)
		{
			pIndex[i] = i;
		}
		m_pMesh->UnlockIndexBuffer();
		vector<DWORD> vecAttrBuf(vecVertex.size() / 3, 0);
		DWORD* pAttr = NULL;
		m_pMesh->LockAttributeBuffer(0, &pAttr);
		memcpy(pAttr, &vecAttrBuf[0], vecAttrBuf.size() * sizeof DWORD);
		m_pMesh->UnlockAttributeBuffer();

		vector<DWORD> vecAdj(vecVertex.size());
		m_pMesh->GenerateAdjacency(0.00001f, &vecAdj[0]);

		m_pMesh->OptimizeInplace
        (
            D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
            &vecAdj[0],
            0, 0, 0
        );
	}
	
	//CreateFont();

	ZeroMemory(&m_stMtlWall, sizeof(D3DMATERIAL9));
	m_stMtlWall.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMtlWall.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMtlWall.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_wallTexture);
	g_pD3DDevice->SetMaterial(&m_stMtlWall);
	m_pMesh->DrawSubset(0);
	
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
