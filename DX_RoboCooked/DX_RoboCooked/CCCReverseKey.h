#pragma once
#include "CCrowdControl.h"
class CCCReverseKey :
	public CCrowdControl
{
public:
	CCCReverseKey();
	CCCReverseKey(CCCReverseKey* clone) : CCrowdControl(clone) {}
private:
	
public:
	string GetID()
	{
		return "REVERSEKEY";
	};

	virtual void Render() {};
	virtual float ReverseRotate() { return D3DX_PI; }
	virtual CCrowdControl* Clone() { return new CCCReverseKey(this); };
};

