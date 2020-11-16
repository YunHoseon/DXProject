#pragma once
#include "CInteractiveActor.h"

class CParts :
	public CInteractiveActor
{
private:
	D3DXVECTOR3			m_vPosition;
	D3DXMATRIXA16		m_matWorld;
	
	ST_SPHERE			m_sphere;
	LPD3DXMESH			m_pMeshSphere;
	D3DMATERIAL9		m_stMtlParts;

	int					m_nPartsID;
	
public:
	CParts();
	CParts(int nPartsID);
	virtual ~CParts();

	void Setup();
	void Update() override;
	void Render() override;
	void OnEvent(EEvent eEvent, void* _value);
	void Interact() override;
};

