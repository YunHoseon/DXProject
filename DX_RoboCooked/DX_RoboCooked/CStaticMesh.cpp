#include "stdafx.h"
#include "CStaticMesh.h"

CStaticMesh::CStaticMesh(const CStaticMesh& other):
	m_pMesh(other.m_pMesh),
	m_vecMaterial(other.m_vecMaterial),
	m_vecTexture(other.m_vecTexture)
{
	SafeAddRef(m_pMesh);
	for (LPDIRECT3DTEXTURE9 p : other.m_vecTexture)
	{
		SafeAddRef(p);
	}
}

CStaticMesh::CStaticMesh(CStaticMesh&& other) noexcept:
	m_pMesh(other.m_pMesh),
	m_vecMaterial(std::move(other.m_vecMaterial)),
	m_vecTexture(std::move(other.m_vecTexture))
{
}

CStaticMesh& CStaticMesh::operator=(const CStaticMesh& other)
{
	if (this == &other)
		return *this;
	m_pMesh = other.m_pMesh;
	SafeAddRef(m_pMesh);
	m_vecMaterial = other.m_vecMaterial;
	m_vecTexture = other.m_vecTexture;
	for (LPDIRECT3DTEXTURE9	p : other.m_vecTexture)
	{
		SafeAddRef(p);
	}
	return *this;
}

CStaticMesh& CStaticMesh::operator=(CStaticMesh&& other) noexcept
{
	if (this == &other)
		return *this;
	m_pMesh = other.m_pMesh;
	m_vecMaterial = std::move(other.m_vecMaterial);
	m_vecTexture = std::move(other.m_vecTexture);
	return *this;
}

CStaticMesh::CStaticMesh():
	m_pMesh(nullptr)
{
}

CStaticMesh::~CStaticMesh()
{
	SafeRelease(m_pMesh);
	for (LPDIRECT3DTEXTURE9 p : m_vecTexture)
	{
		SafeRelease(p);
	}
}

// 머티리얼, 텍스처 세팅하고 렌더. 기타 옵션은 밖에서 해줘야 함
void CStaticMesh::Render()
{
	if(m_pMesh)
	{
		for (int i = 0; i < m_vecMaterial.size(); ++i)
		{
			g_pD3DDevice->SetMaterial(&m_vecMaterial[i]);
			g_pD3DDevice->SetTexture(0, m_vecTexture[i]);
			m_pMesh->DrawSubset(i);
		}
		g_pD3DDevice->SetTexture(0, 0);
	}
}
