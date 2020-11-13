#pragma once
#include "ICollisionArea.h"

class CBoxCollision;

class CSphereCollision : public ICollisionArea
{
protected:
	float			fRadius;
public:
	explicit CSphereCollision(float fRadius = 0.0f);
	~CSphereCollision() override;
	void Render() override;
	void Update() override;
	bool CollideToBox(ICollisionArea* pTargetCollider) override;
	bool CollideToSphere(ICollisionArea* pTargetCollider) override;
	float GetRadius() { return fRadius; }
};
