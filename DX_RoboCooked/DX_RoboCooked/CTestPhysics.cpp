#include "stdafx.h"
#include "CTestPhysics.h"
#include "CActor.h"

//void CTestPhysics::ApplyPhysics(CActor* pA, CActor* pB)
//{
//	ApplyGravity(pA);
//	ApplyBound(pA, pB);
//}

void CTestPhysics::ApplyGravity(CActor* pA)
{
	//return;
	D3DXVECTOR3 gravity(0, -0.01f, 0);
	pA->AddAcceleration(gravity);
}

void CTestPhysics::ApplyBound(CActor* pA, CActor* pB)
{
	D3DXVECTOR3 vNormal(0, 0, 0);
	if (pA->Collide(pB, &vNormal))
	{
		// 마찰력 = -1 * 마찰계수 * 수직항력 * Normalization(velocity)
		// 수직항력 = vNormal * dot(vNormal, -velocity)
		// 노멀과 방향의 각도가 같으면 생략
		
		D3DXVECTOR3 vTempVelocity = (pA->GetVelocity() + pA->GetAcceleration()) + (pB->GetVelocity() + pB->GetAcceleration());
		float power = -D3DXVec3Dot(&vNormal, &vTempVelocity);
		D3DXVECTOR3 vNormalForce(g_vZero);
		if (power > 0)
			vNormalForce = vNormal * power * 1.0f; // 탄성계수

		else if (power < 0)
			vNormalForce = -vNormal * power * 1.0f; // 탄성계수

		if (pA->GetMass() < pB->GetMass())
			pA->AddAcceleration(vNormalForce); // 수직항력
		else if (pA->GetMass() > pB->GetMass())
			pB->AddAcceleration(-vNormalForce);
		else
		{
			pA->AddAcceleration(vNormalForce * 0.5f);
			pB->AddAcceleration(-vNormalForce * 0.5f);
		}
		
		vTempVelocity = (pA->GetVelocity() + pA->GetAcceleration()) * -1 * pB->GetFriction(); // -1 * 마찰계수
		pA->AddAcceleration(vTempVelocity); // 마찰력

		vTempVelocity = (pB->GetVelocity() + pB->GetAcceleration()) * -1 * pA->GetFriction(); // -1 * 마찰계수
		pB->AddAcceleration(vTempVelocity); // 마찰력
	}
}
