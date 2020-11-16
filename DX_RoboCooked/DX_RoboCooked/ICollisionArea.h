#pragma once

class CSphereCollision;
class CBoxCollision;

class ICollisionArea
{
public:
	enum class EColideType { E_Box, E_Sphere };
protected:
	EColideType			m_eType;
	bool				isCollide;
	D3DCOLOR			stColor[2];

	D3DXVECTOR3			m_vOriginCenterPos;
	D3DXVECTOR3			m_vCenterPos;

	D3DXMATRIXA16*		m_pmatWorldTM;
		
public:
	ICollisionArea();
	virtual ~ICollisionArea() {}
	D3DXVECTOR3	GetCenter() { return m_vCenterPos; }
	//const EColideType& GetType() { return m_eType; }
	bool Collide(ICollisionArea* pTargetCollider);
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual bool CollideToBox(CBoxCollision* pTargetCollider) = 0;
	virtual bool CollideToSphere(CSphereCollision* pTargetCollider) = 0;
};
