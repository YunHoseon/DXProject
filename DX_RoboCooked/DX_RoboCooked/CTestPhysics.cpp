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
	pA->AddForce(gravity);
}

void CTestPhysics::ApplyBound(CActor* pA, CActor* pB)
{
	D3DXVECTOR3 vNormal(0, 0, 0);
	if (pA->Collide(pB, &vNormal))
	{
		// 마찰력 = -1 * 마찰계수 * 수직항력 * Normalization(velocity)
		// 수직항력 = vNormal * dot(vNormal, -velocity)
		//D3DXVECTOR3 vNormalForce = vNormal * 0.02;
		// 노멀과 방향의 각도가 같으면 생략
		
		D3DXVECTOR3 vTempVelocity = pA->GetVelocity() + pA->GetAcceleration();
		float power = -D3DXVec3Dot(&vNormal, &vTempVelocity);
		D3DXVECTOR3 vNormalForce;
		if (power > 0)
		{
			vNormalForce = vNormal * power;
			pA->AddForce(vNormalForce); // 수직항력
			vTempVelocity = pA->GetVelocity() + pA->GetAcceleration();
		}
		
		vTempVelocity *= -0.25f; // -1 * 마찰계수
		pA->AddForce(vTempVelocity); // 마찰력
	}
}
