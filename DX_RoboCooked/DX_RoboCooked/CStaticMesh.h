#pragma once

class CStaticMesh
{
public:
	CStaticMesh(const CStaticMesh& other);

	CStaticMesh(CStaticMesh&& other) noexcept;

	CStaticMesh& operator=(const CStaticMesh& other);

	CStaticMesh& operator=(CStaticMesh&& other) noexcept;

protected:
	LPD3DXMESH m_pMesh;
	vector<D3DMATERIAL9> m_vecMaterial;
	vector<LPDIRECT3DTEXTURE9> m_vecTexture;
public:
	CStaticMesh();
	virtual ~CStaticMesh();

	LPD3DXMESH& GetMesh() { return m_pMesh; }
	vector<D3DMATERIAL9>& GetVecMaterial() { return m_vecMaterial; }
	vector<LPDIRECT3DTEXTURE9>& GetVecTexture() { return m_vecTexture; }

	virtual void Render(LPDIRECT3DTEXTURE9 pBlendTexture = nullptr);
	virtual void RenderWidthShadow();
	virtual void CreateShadowMap();
};
