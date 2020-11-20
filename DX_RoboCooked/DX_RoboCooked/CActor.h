#pragma once
#include "CEventListener.h"

class IInteractCenter;
class ICollisionArea;

class CActor : public CEventListener
{
public:
	CActor();
	virtual  ~CActor();

protected:
	IInteractCenter*	m_pInteractCenter;
	D3DXMATRIXA16		m_matS;
	D3DXMATRIXA16		m_matR;
	D3DXMATRIXA16		m_matT;
	D3DXMATRIXA16		m_matWorld;
	float				m_fRotY;
	D3DXVECTOR3			m_vDirection;
	D3DXVECTOR3			m_vPosition;

	float				m_fBaseSpeed;
	float				m_fSpeed;
	
	ICollisionArea*		m_pCollision;
public:

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual bool Collide(CActor* target, D3DXVECTOR3* pNormal = nullptr);

	ICollisionArea* GetCollision() { return m_pCollision; }
	
	D3DXVECTOR3& GetDirection()	{ return m_vDirection; }
	void SetDirection(const D3DXVECTOR3& vDirection) { m_vDirection = vDirection; }
	__declspec(property(get = GetDirection, put = SetDirection)) D3DXVECTOR3 Direction;

	float GetSpeed() { return m_fSpeed; }
};

