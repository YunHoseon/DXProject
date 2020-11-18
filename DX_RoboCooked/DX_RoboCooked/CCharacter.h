#pragma once
#include "CParts.h"

class ICollisionArea;
class CGameScene;


enum class EPlayerState
{
	E_None, //�⺻����
	E_Grab  //������
};

class CCharacter
{
protected:
	//CGameScene*			m_pInteractCenter;
	EPlayerState		m_ePlayerState;
	ICollisionArea*		m_pInteractCollision;
	float				m_fBaseSpeed;
	float				m_fSpeed;
	float				m_fRotY;
	D3DXVECTOR3			m_vDirection;
	D3DXVECTOR3			m_vPosition;
	D3DXVECTOR3			m_vGrabPartsPosition;
	CParts*				m_pParts;

	DWORD				m_elapsedTime;
	bool				m_isGrabCooltime;
	// �����̻� ���� ���� //
	

public:
	CCharacter();
	virtual ~CCharacter() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	
	D3DXVECTOR3& GetGrabPartsPosition() { return m_vGrabPartsPosition; }
	ICollisionArea* GetInteractCollsion() { return m_pInteractCollision; }
	EPlayerState GetPlayerState() { return m_ePlayerState; }
	void SetPlayerState(EPlayerState state) { m_ePlayerState = state; }
	void SetParts(CParts* pParts) { m_pParts = pParts; }
};

