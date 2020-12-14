#pragma once
#include "CCrowdControl.h"
class CCCReverseKey :
	public CCrowdControl
{
public:
	CCCReverseKey();

public:
	string GetID()
	{
		return "REVERSEKEY";
	};

	virtual void Render(D3DXVECTOR3& vPos) {};
	virtual float ReverseRotate() { return D3DX_PI; }
	virtual CCrowdControl* Clone() { return new CCCReverseKey; };
};

