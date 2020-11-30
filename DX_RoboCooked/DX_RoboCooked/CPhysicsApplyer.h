#pragma once

class CActor;

class CPhysicsApplyer
{
public:
	//static void ApplyPhysics(CActor* pA, CActor* pB);
	static void ApplyGravity(CActor* pA);
	static void ApplyBound(CActor* pA, CActor* pB); // 
	//static void ApplyFriction(CActor* pA, CActor* pB);
};
