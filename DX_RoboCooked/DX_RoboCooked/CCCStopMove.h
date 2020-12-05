#pragma once
#include "CCrowdControl.h"
class CCCStopMove :
	public CCrowdControl
{
public:
	CCCStopMove();
	~CCCStopMove();

public:
	string& GetID()
	{
		string name = "STOPMOVE";
		return name;
	};

	virtual void Render(D3DXVECTOR3& vPos) {};
	virtual bool IsMovable() { return false; }
	virtual CCrowdControl* Clone() { return new CCCStopMove; };

};

