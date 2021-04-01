#pragma once

class CActor;

class CPhysicsApplyer
{
	static D3DXVECTOR3 vGravity;
public:
	//static void ApplyPhysics(CActor* pA, CActor* pB);
	static void ApplyGravity(CActor* pA);
	static bool ApplyBound(CActor* pA, CActor* pB); // 
	//static void ApplyFriction(CActor* pA, CActor* pB);
	static const D3DXVECTOR3& GetGravity() { return vGravity; }
};
