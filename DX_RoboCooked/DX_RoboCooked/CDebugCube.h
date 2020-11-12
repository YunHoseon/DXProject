#pragma once
class CDebugCube
{
private:
	float			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matWorld;

	ST_CUBE			m_cube;
	LPD3DXMESH		m_pMeshCube;
	D3DMATERIAL9	m_stMtlCube;
public:
	CDebugCube();
	~CDebugCube();

	void Setup();
	void Update();
	void Render();
};

