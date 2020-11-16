#pragma once
#include "ICollisionArea.h"

class CBoxCollision;

class CSphereCollision : public ICollisionArea
{
protected:
	float			fRadius;
public:
	explicit CSphereCollision(D3DXVECTOR3 vOriginPos, float fRadius = 1.0f, D3DXMATRIXA16* pmatWorld = nullptr);
	~CSphereCollision() override;
	void Render() override;
	void Update() override;
	float GetRadius() { return fRadius; }
	bool CollideToBox(CBoxCollision* pTargetCollider) override;
	bool CollideToSphere(CSphereCollision* pTargetCollider) override;
};
