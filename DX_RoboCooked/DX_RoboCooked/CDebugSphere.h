#pragma once
#include "CActor.h"


class CDebugSphere : public CActor
{
private:
	float				m_fRotY;
	D3DXVECTOR3			m_vDirection;
	D3DXVECTOR3			m_vPosition;
	D3DXMATRIXA16		m_matWorld;
	
	ST_SPHERE			m_sphere;
	LPD3DXMESH			m_pMeshSphere;
	D3DMATERIAL9		m_stMtlSphere;
	ST_PLAYER_INPUTKEY	m_stInputKey;
public:
	CDebugSphere();
	~CDebugSphere();

	void Setup();
	void Update() override;
	void Render() override;
	
	//입력키 바꿀 수 있는 함수 추가

	void OnEvent(EEvent eEvent, void* _value);
	void PressKey(void* _value);
	void ReleaseKey(void* _value);
	void Move(D3DXVECTOR3 _vecMove);
};

