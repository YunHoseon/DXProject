#pragma once
#include "CCrowdControl.h"
class CCCSpeedDown :
	public CCrowdControl
{
public:
	virtual string& GetID() = 0;
	virtual void Render(D3DXVECTOR3& vPos) = 0;
	virtual CCrowdControl* Clone() = 0;
	virtual float MultiplySpeed() { return 0.8f; }
};

