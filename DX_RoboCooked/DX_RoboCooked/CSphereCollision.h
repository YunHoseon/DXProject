#pragma once
#include "ICollisionArea.h"

class CSphereCollision : public ICollisionArea
{
protected:
	float fRadius;
public:
	void Render() override;
	void Update() override;
	bool CollideToBox(ICollisionArea* pTargetCollider) override;
	bool CollideToSphere(ICollisionArea* pTargetCollider) override;

	float GetRadius() { return fRadius; }
};
