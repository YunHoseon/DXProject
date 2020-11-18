#pragma once
#include "CGameScene.h"
class CGameScene;


enum class ePlayerState
{
	E_None, //기본상태
	E_Grab  //잡기상태
};

class CCharacter
{
protected:
	CGameScene*			m_GameCenter;
	ePlayerState		m_ePlayerState;
	ICollisionArea*		m_pInteractCollision;
	float				m_fSpeed;
	float				m_fRotY;
	D3DXVECTOR3			m_vDirection;
	D3DXVECTOR3			m_vPosition;
	
public:
	CCharacter();
	virtual ~CCharacter() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	
	//D3DXVECTOR3& GetPosition() { return m_vPosition; }
	ICollisionArea* GetInteractCollsion() { return m_pInteractCollision; }
};

