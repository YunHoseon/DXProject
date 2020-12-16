#pragma once
#include "CCrowdControl.h"
class CCCSpeedDown :
	public CCrowdControl
{
public:
	CCCSpeedDown();
	CCCSpeedDown(CCCSpeedDown* clone) : CCrowdControl(clone) {}
public:
	string GetID()
	{
		return "SPEEDDOWN";
	};

	virtual void Render(D3DXVECTOR3& vPos) {};
	virtual float MultiplySpeed() { return 0.3f; }
	virtual CCrowdControl* Clone() { return new CCCSpeedDown(this); };
};

