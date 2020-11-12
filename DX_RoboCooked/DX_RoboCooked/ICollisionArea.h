#pragma once

class ICollisionArea
{
public:
	enum class EColideType { E_Box, E_Sphere };
protected:
	EColideType m_eType;
public:
	virtual ~ICollisionArea() {}
	//const EColideType& GetType() { return m_eType; }
	bool Collide(ICollisionArea* pTargetCollider);
	virtual bool Render() = 0;
protected:
	virtual bool CollideToBox(ICollisionArea* pTargetCollider) = 0;
	virtual bool CollideToSphere(ICollisionArea* pTargetCollider) = 0;
};
