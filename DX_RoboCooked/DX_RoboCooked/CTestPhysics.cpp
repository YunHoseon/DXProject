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
		pA->Direction += vNormal * pA->GetSpeed();
}
