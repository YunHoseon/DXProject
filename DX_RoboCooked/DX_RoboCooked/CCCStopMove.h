#pragma once
#include "CCrowdControl.h"
class CCCStopMove :
	public CCrowdControl
{
public:
	CCCStopMove();
	CCCStopMove(CCCStopMove* clone) : CCrowdControl(clone) {}

public:
	string GetID()
	{
		return "STOPMOVE";
	};

	virtual void Render() {};
	virtual bool IsMovable() { return false; }
	virtual CCrowdControl* Clone() { return new CCCStopMove(this); };
};

