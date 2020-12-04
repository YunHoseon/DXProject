#pragma once
#include "CCrowdControl.h"

class CCCSpeedUp : public CCrowdControl
{
public:
	virtual string& GetID() = 0;
	virtual void Render(D3DXVECTOR3& vPos) = 0;
	virtual CCrowdControl* Clone() = 0;
	virtual float MultiplySpeed() override { return 1.3f; }
};
