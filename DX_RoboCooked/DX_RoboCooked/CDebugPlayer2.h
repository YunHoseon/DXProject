#pragma once
#include "CActor.h"
#include "CCharacter.h"


class CDebugPlayer2 : public CActor,public CCharacter
{
private:
	ST_CUBE				m_cube;
	LPD3DXMESH			m_pMeshCube;
	D3DMATERIAL9		m_stMtlCube;
	ST_PLAYER_INPUTKEY	m_stInputKey;
	
public:
	CDebugPlayer2(CGameScene* gameCenter);
	~CDebugPlayer2();

	void Setup();
	void Update();
	void Render() override;
	
	void OnEvent(EEvent eEvent, void* _value);
	void PressKey(void* _value);
	void ReleaseKey(void* _value);
	void Move(D3DXVECTOR3 _vecMove);
	void Rotate();
	void SetKeyChange(void* _value);
};

