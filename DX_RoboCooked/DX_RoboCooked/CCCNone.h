#pragma once
#include "CCrowdControl.h"
class CUITexture;

class CCCNone :
	public CCrowdControl
{
private:
public:
	CCCNone();
	virtual ~CCCNone();
	string GetID()
	{ 
		return "NONE";
	};
	virtual void Render();
	virtual CCrowdControl* Clone() { return new CCCNone; };
	virtual bool IsEnd() { return false; }
};

