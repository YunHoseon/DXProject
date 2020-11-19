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

	ICollisionArea*		m_pCollision;
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual bool Collide(CActor* target);

	ICollisionArea* GetCollision() { return m_pCollision; }
	
};

