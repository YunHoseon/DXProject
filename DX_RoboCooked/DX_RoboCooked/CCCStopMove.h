#pragma once
#include "CCrowdControl.h"
class CUICC;

class CCCStopMove :
	public CCrowdControl
{
public:
	CCCStopMove();
	CCCStopMove(CCCStopMove* clone);
	virtual ~CCCStopMove();
private:
	CUICC* m_pImage;
public:
	string GetID()
	{
		return "STOPMOVE";
	};

	virtual void Render() override;
	virtual void SetTarget(D3DXVECTOR3* target) override;
	virtual bool IsMovable() { return false; }
	virtual CCrowdControl* Clone() { return new CCCStopMove(this); };
};

