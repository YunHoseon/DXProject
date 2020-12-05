#pragma once
#include "CCrowdControl.h"
class CCCSpeedDown :
	public CCrowdControl
{
public:
	string& GetID()
	{
		string name = "SPEEDDOWN";
		return name;
	};

	virtual void Render(D3DXVECTOR3& vPos) {};
	virtual float MultiplySpeed() { return 0.3f; }
	virtual CCrowdControl* Clone() { return new CCCSpeedDown; };
};

