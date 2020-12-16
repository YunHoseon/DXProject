#pragma once
#include "CCrowdControl.h"
class CCCNone :
	public CCrowdControl
{
public:
	string GetID()
	{ 
		return "NONE";
	};
	virtual void Render(D3DXVECTOR3& vPos) {};
	virtual CCrowdControl* Clone() { return new CCCNone; };
	virtual bool IsEnd() { return false; }
};

