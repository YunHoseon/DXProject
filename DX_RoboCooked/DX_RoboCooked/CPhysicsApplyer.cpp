﻿#include "stdafx.h"
#include "CPhysicsApplyer.h"
#include "CActor.h"

D3DXVECTOR3 CPhysicsApplyer::vGravity(0, -0.01f, 0);
void CPhysicsApplyer::ApplyGravity(CActor* pA)
{
	pA->AddAcceleration(vGravity * TimeRevision);
}

bool CPhysicsApplyer::ApplyBound(CActor* pA, CActor* pB)
{
	D3DXVECTOR3 vNormal(0, 0, 0);
	if (pA->Collide(pB, &vNormal))
	{
		// 마찰력 = -1 * 마찰계수 * 수직항력 * Normalization(velocity)
		// 수직항력 = vNormal * dot(vNormal, -velocity)
		// 노멀과 방향의 각도가 같으면 생략
		D3DXVECTOR3 vTempVelo[2];
		vTempVelo[0] = (pA->GetVelocity() + pA->GetAcceleration());
		vTempVelo[1] = (pB->GetVelocity() + pB->GetAcceleration());

		float power[2];
		power[0] = -D3DXVec3Dot(&vNormal, &vTempVelo[0]);
		power[1] = -D3DXVec3Dot(&-vNormal, &vTempVelo[1]);

		D3DXVECTOR3 vNormalForce[2]{g_vZero, g_vZero};
		

		if (power[0] > 0)
		{
			vNormalForce[0] = vNormal * power[0] * pB->GetFlexibiltiy() + vNormal * pB->GetRepulsivePower();  // 1.0 = 탄성계수. 1.0이면 튕기지 않음, RepulsivePower = 반발력. 속도와 무관하게 밀어내는 값
			vNormalForce[1] = -vNormal * power[0] * pA->GetFlexibiltiy() + -vNormal * pA->GetRepulsivePower();
		}

		else if (power[1] > 0)
		{
			vNormalForce[0] = vNormal * power[1] * pB->GetFlexibiltiy() + vNormal * pB->GetRepulsivePower();
			vNormalForce[1] = -vNormal * power[1] * pA->GetFlexibiltiy() + -vNormal * pA->GetRepulsivePower();
		}

		if (pA->GetMass() < pB->GetMass())
			pA->AddAcceleration(vNormalForce[0]); // 수직항력 적용
		else if (pA->GetMass() > pB->GetMass())
			pB->AddAcceleration(vNormalForce[1]);
		else
		{
			pA->AddAcceleration( vNormalForce[0] * 0.5f - vNormalForce[1] * 0.5f);
			pB->AddAcceleration(-vNormalForce[0] * 0.5f + vNormalForce[1] * 0.5f);
		}
		
		D3DXVECTOR3 vTempVelocity;
		vTempVelocity = (pA->GetVelocity() + pA->GetAcceleration()) * -1 * pB->GetFriction(); // -1 * 속도 * 마찰계수
		pA->AddAcceleration(vTempVelocity); // 마찰력

		vTempVelocity = (pB->GetVelocity() + pB->GetAcceleration()) * -1 * pA->GetFriction(); // -1 * 마찰계수
		pB->AddAcceleration(vTempVelocity); // 마찰력

		return true;
	}
	return false;
}
