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
	
}

void CTestPhysics::ApplyBound(CActor* pA, CActor* pB)
{
	D3DXVECTOR3 vNormal(0, 0, 0);
	if (pA->Collide(pB, &vNormal))
	{
		// 마찰력 = -1 * 마찰계수 * 수직항력 * Normalization(velocity)
		// 수직항력 = vNormal * dot(vNormal, -velocity)
		//D3DXVECTOR3 vNormalForce = vNormal * -D3DXVec3Dot(&vNormal, &pA->GetVelocity());
		D3DXVECTOR3 vNormalForce = vNormal * -D3DXVec3Dot(&vNormal, &pA->GetAcceleration()); // 임시. 나중에 가속도를 속도로 바꿔야함.
		D3DXVECTOR3 vMinusVelocity;
		D3DXVec3Normalize(&vMinusVelocity, &pA->GetAcceleration());
		vMinusVelocity *= -1 * 0.02f;
		pA->AddForce(vNormalForce);
		pA->AddForce(vMinusVelocity);
	}
}
