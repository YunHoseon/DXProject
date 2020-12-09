#pragma once
#include "CEventListener.h"
class CEventListener;

class CCrowdControl
{
public:
	CCrowdControl();
	~CCrowdControl();
	virtual string& GetID() = 0;

	virtual CCrowdControl* Clone() = 0;
	virtual float ReverseRotate() { return 0; }
	virtual float MultiplySpeed() { return 1.0f; }
	virtual void Render(D3DXVECTOR3& vPos) = 0;
	virtual bool IsOverlapable() { return false; }
	virtual bool IsMovable() { return true; }
	virtual bool IsProtected() { return false; }
	// 타겟을 지정하는 함수
};

#include "CCCSpeedDown.h"
#include "CCCReverseKey.h"
#include "CCCStopMove.h"
#include "CCCNone.h"
#include "CCCSlowAndStop.h"