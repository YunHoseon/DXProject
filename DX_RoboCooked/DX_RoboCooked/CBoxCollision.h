#pragma once
#include "ICollisionArea.h"

class CBoxCollision : public ICollisionArea
{
public:
	CBoxCollision(D3DXVECTOR3 vHalfSize);
	~CBoxCollision() override;
	bool Render() override;
protected:
	bool CollideToBox(ICollisionArea* pTargetCollider) override;
	bool CollideToSphere(ICollisionArea* pTargetCollider) override;
public:
	
};
