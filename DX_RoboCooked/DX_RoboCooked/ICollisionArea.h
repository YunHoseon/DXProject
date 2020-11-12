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
	virtual void Render() = 0;
	virtual void Update() = 0;
protected:
	virtual bool CollideToBox(ICollisionArea* pTargetCollider) = 0;
	virtual bool CollideToSphere(ICollisionArea* pTargetCollider) = 0;
};
