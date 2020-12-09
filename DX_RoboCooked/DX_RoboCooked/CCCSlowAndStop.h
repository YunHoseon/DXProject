#pragma once
#include "CCrowdControl.h"

class CCCSlowAndStop : public CCrowdControl
{
public:
	CCCSlowAndStop() : CCrowdControl() {}
public:
	string& GetID()
	{
		string name = "SLOWANDSTOP";
		return name;
	};
	virtual void Render(D3DXVECTOR3& vPos) {};
	virtual float MultiplySpeed() { return 0.3f; }
	virtual bool StopWithParts() { return true; }
	virtual CCrowdControl* Clone() { return new CCCSlowAndStop; };
};
