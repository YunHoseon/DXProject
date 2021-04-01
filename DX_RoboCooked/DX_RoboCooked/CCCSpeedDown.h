#pragma once
#include "CCrowdControl.h"
class CUICC;

class CCCSpeedDown :
	public CCrowdControl
{
public:
	CCCSpeedDown();
	CCCSpeedDown(CCCSpeedDown* clone);
	virtual ~CCCSpeedDown();
private:
	CUICC* m_pImage;
public:
	string GetID()
	{
		return "SPEEDDOWN";
	};

	virtual void Render();
	virtual float MultiplySpeed() { return 0.3f; }
	virtual CCrowdControl* Clone() { return new CCCSpeedDown(this); };
	void SetTarget(D3DXVECTOR3* target) override;
};

