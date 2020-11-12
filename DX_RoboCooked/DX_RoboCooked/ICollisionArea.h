#pragma once

class ICollisionArea
{
public:
	enum class EColideType { E_Box, E_Sphere };
protected:
	EColideType			m_eType;
	bool				isCollide;
	D3DXVECTOR3			m_vOriginCenterPos;
	D3DCOLOR			stColor[2];
public:
	D3DXVECTOR3	GetCenter() { return m_vOriginCenterPos; }
	ICollisionArea();
	virtual ~ICollisionArea() {}
	//const EColideType& GetType() { return m_eType; }
	bool Collide(ICollisionArea* pTargetCollider);
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual bool CollideToBox(ICollisionArea* pTargetCollider) = 0;
	virtual bool CollideToSphere(ICollisionArea* pTargetCollider) = 0;
};
