#pragma once
#include "CEventListener.h"

class CGameScene;
class ICollisionArea;

class CActor : public CEventListener
{
public:
	CActor();
	virtual  ~CActor();

protected:
	CGameScene*	  m_GameCenter;
	D3DXMATRIXA16 m_matS;
	D3DXMATRIXA16 m_matR;
	D3DXMATRIXA16 m_matT;
	D3DXMATRIXA16 m_matWorld;

	//콜라이더 미추가
	ICollisionArea* m_pCollision;
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual bool Collide(CActor* target);

	ICollisionArea* GetCollision() { return m_pCollision; }
	
};

