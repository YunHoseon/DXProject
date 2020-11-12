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
	virtual void Update() override;
	virtual void  Render() override;
	//입력키 바꿀 수 있는 함수 추가
};

