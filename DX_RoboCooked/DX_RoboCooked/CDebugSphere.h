#pragma once
class CDebugSphere
{
private:
	float			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matWorld;
	
	ST_SPHERE		m_sphere;
	LPD3DXMESH		m_pMeshSphere;
	D3DMATERIAL9	m_stMtlSphere;
public:
	CDebugSphere();
	~CDebugSphere();

	void Setup();
	void Update();
	void Render();
};

