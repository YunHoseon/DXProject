#pragma once
#include "CActor.h"


class CDebugPlayer2 : public CActor
{
private:
	float				m_fSpeed;
	float				m_fRotY;
	D3DXVECTOR3			m_vDirection;
	D3DXVECTOR3			m_vPosition;
	D3DXMATRIXA16		m_matWorld;

	ST_CUBE				m_cube;
	LPD3DXMESH			m_pMeshCube;
	D3DMATERIAL9		m_stMtlCube;
	ST_PLAYER_INPUTKEY	m_stInputKey;
public:
	CDebugPlayer2();
	~CDebugPlayer2();

	void Setup();
	void Update() override;
	void Render() override;
	
	void OnEvent(EEvent eEvent, void* _value);
	void PressKey(void* _value);
	void ReleaseKey(void* _value);
	void Move(D3DXVECTOR3 _vecMove);
	void SetKeyChange(void* _value);
};

