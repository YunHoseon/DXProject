#pragma once
#include "CCrowdControl.h"
class CUICC;

class CCCSlowAndStop : public CCrowdControl
{
public:
	CCCSlowAndStop();
	CCCSlowAndStop(CCCSlowAndStop* clone);
	virtual ~CCCSlowAndStop();
private:
	CUICC* m_pImage;
public:
	string GetID()
	{
		return "SLOWANDSTOP";
	};
	virtual void Render();
	virtual float MultiplySpeed() { return 0.3f; }
	virtual bool StopWithParts() { return true; }
	virtual CCrowdControl* Clone() { return new CCCSlowAndStop(this); };
	void SetTarget(D3DXVECTOR3* target) override;
};
