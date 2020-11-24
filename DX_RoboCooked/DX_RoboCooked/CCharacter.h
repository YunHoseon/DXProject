#pragma once
#include "CParts.h"

class ICollisionArea;
class CGameScene;


enum class ePlayerState
{
	None, 
	Grab 
};

class CCharacter :public CActor
{
protected:

	ePlayerState		m_ePlayerState;
	ICollisionArea*		m_pInteractCollision;

	D3DXVECTOR3			m_vGrabPartsPosition;
	CParts*				m_pParts;

	DWORD				m_elapsedTime;
	bool				m_isGrabCooltime;

public:
	CCharacter();
	virtual ~CCharacter() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	
	D3DXVECTOR3& GetGrabPartsPosition() { return m_vGrabPartsPosition; }
	ICollisionArea* GetInteractCollsion() { return m_pInteractCollision; }
	ePlayerState GetPlayerState() { return m_ePlayerState; }
	void SetPlayerState(ePlayerState state) { m_ePlayerState = state; }
	void SetParts(CParts* pParts) { m_pParts = pParts; }
	CParts* GetParts() { return m_pParts; }
};

