#pragma once
#include "CCrowdControl.h"
class CUICC;

class CCCReverseKey :
	public CCrowdControl
{
public:
	CCCReverseKey();
	CCCReverseKey(CCCReverseKey* clone);
	virtual ~CCCReverseKey();
private:
	CUICC* m_pImage;
public:
	string GetID()
	{
		return "REVERSEKEY";
	};

	virtual void Render();
	virtual float ReverseRotate() { return D3DX_PI; }
	virtual CCrowdControl* Clone() { return new CCCReverseKey(this); }
	void SetTarget(D3DXVECTOR3* target) override;;
	
};

