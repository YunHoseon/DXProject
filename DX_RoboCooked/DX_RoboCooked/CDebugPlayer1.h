#pragma once
#include "CActor.h"
#include "CCharacter.h"



class CGameScene;

class CDebugPlayer1 : public CActor, public CCharacter
{
private:
	ST_SPHERE			m_sphere;
	LPD3DXMESH			m_pMeshSphere;
	D3DMATERIAL9		m_stMtlSphere;
	ST_PLAYER_INPUTKEY	m_stInputKey;



public:
	CDebugPlayer1(CGameScene* gameCenter);
	~CDebugPlayer1();

	void Setup();
	void Update() override;
	void Render() override;

	void OnEvent(EEvent eEvent, void* _value);
	void PressKey(void* _value);
	void ReleaseKey(void* _value);
	void SetKeyChange(void* _value);
	
	void Move();
	void Rotate(float fTargetRot);
	void Pick();
	void Place();
	
};

