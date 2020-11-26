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

	
	// for physics
	ICollisionArea*		m_pCollision;
	D3DXVECTOR3			m_vPosition;
	D3DXVECTOR3			m_vVelocity;
	D3DXVECTOR3			m_vAcceleration;
	D3DXVECTOR3			m_vDirection;
	float				m_fBaseSpeed;
	float				m_fSpeed;
	float				m_fMass;
	
public:

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual bool Collide(CActor* target, D3DXVECTOR3* pNormal = nullptr);

	ICollisionArea* GetCollision() { return m_pCollision; }
	
	D3DXVECTOR3& GetDirection()	{ return m_vDirection; }
	void SetDirection(const D3DXVECTOR3& vDirection) { m_vDirection = vDirection; }
	__declspec(property(get = GetDirection, put = SetDirection)) D3DXVECTOR3 Direction;

	const D3DXVECTOR3& GetVelocity() { return m_vVelocity; }
	const D3DXVECTOR3& GetAcceleration() { return m_vAcceleration; }

	/// test now-Àç¿í
	virtual void AddForce(const D3DXVECTOR3& vForce);
	virtual void SetForce(const D3DXVECTOR3& vForce = D3DXVECTOR3(0, 0, 0));
};

