#pragma once
#include "CActor.h"


class CDebugPlayer1 : public CActor
{
private:
	float				m_fSpeed;
	float				m_fRotY;
	D3DXVECTOR3			m_vDirection;
	D3DXVECTOR3			m_vPosition;
	D3DXMATRIXA16		m_matWorld;
	ICollisionArea*		m_pInteractCollision;
	
	ST_SPHERE			m_sphere;
	LPD3DXMESH			m_pMeshSphere;
	D3DMATERIAL9		m_stMtlSphere;
	ST_PLAYER_INPUTKEY	m_stInputKey;
public:
	CDebugPlayer1();
	~CDebugPlayer1();

	void Setup();
	void Update() override;
	void Render() override;

	void OnEvent(EEvent eEvent, void* _value);
	void PressKey(void* _value);
	void ReleaseKey(void* _value);
	void Move(D3DXVECTOR3 _vecMove);
	void Rotate();
	void SetKeyChange(void* _value);
};

