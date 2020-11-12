#pragma once
#include "CActor.h"



class CDebugCube : public CActor
{
private:
	float				m_fRotY;
	D3DXVECTOR3			m_vDirection;
	D3DXVECTOR3			m_vPosition;
	D3DXMATRIXA16		m_matWorld;

	ST_CUBE				m_cube;
	LPD3DXMESH			m_pMeshCube;
	D3DMATERIAL9		m_stMtlCube;
	ST_PLAYER_INPUTKEY	m_stInputKey;
public:
	CDebugCube();
	~CDebugCube();

	void Setup();
	void Update() override;
	void Render() override;
	void OnEvent(EEvent eEvent, void* _value);
	void Move(void* _value);
};

