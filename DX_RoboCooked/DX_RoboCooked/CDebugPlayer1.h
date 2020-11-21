#pragma once
#include "CActor.h"
#include "CCharacter.h"



class CDebugPlayer1 : public CCharacter
{
private:
	ST_SPHERE			m_sphere;
	LPD3DXMESH			m_pMeshSphere;
	D3DMATERIAL9		m_stMtlSphere;
	ST_PLAYER_INPUTKEY	m_stInputKey;
	DWORD				m_ElapsTimeF;
	DWORD				m_ElapsTimeG;
	DWORD				m_ElapsTimeH;

public:
	CDebugPlayer1(IInteractCenter* pInteractCenter = nullptr);
	~CDebugPlayer1();

	void Setup();
	void Update() override;
	void Render() override;

	void OnEvent(EEvent eEvent, void* _value) override;
	void PressKey(void* _value);
	//void PressMoveKey();
	void ReleaseKey(void* _value);
	void SetKeyChange(void* _value);
	
	void Move();
	void Rotate(float fTargetRot);
};

