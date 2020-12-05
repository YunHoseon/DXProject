#pragma once
#include "CCrowdControl.h"
class CCCReverseKey :
	public CCrowdControl
{
public:
	CCCReverseKey();
	~CCCReverseKey();

public:
	string& GetID()
	{
		string name = "REVERSEKEY";
		return name;
	};

	virtual void Render(D3DXVECTOR3& vPos) {};
	virtual float ReverseRotate() { return D3DX_PI; }
	virtual CCrowdControl* Clone() { return new CCCReverseKey; };
};

