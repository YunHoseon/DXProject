#pragma once
#include "CCrowdControl.h"
class CCCNone :
	public CCrowdControl
{
public:
	string& GetID()
	{ 
		string name = "NONE";
		return name;
	};
	virtual void Render(D3DXVECTOR3& vPos) {};
	virtual CCrowdControl* Clone() { return new CCCNone; };
};

