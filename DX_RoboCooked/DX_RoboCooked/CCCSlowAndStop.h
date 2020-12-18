#pragma once
#include "CCrowdControl.h"

class CCCSlowAndStop : public CCrowdControl
{
public:
	CCCSlowAndStop() : CCrowdControl() {}
	CCCSlowAndStop(CCCSlowAndStop* clone) : CCrowdControl(clone) {}
public:
	string GetID()
	{
		return "SLOWANDSTOP";
	};
	virtual void Render() {};
	virtual float MultiplySpeed() { return 0.3f; }
	virtual bool StopWithParts() { return true; }
	virtual CCrowdControl* Clone() { return new CCCSlowAndStop(this); };
};
