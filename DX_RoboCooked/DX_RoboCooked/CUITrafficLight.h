#pragma once
#include "CUIButton.h"

class CUITrafficLight :
	public CUIButton
{
protected:
	vector<D3DXVECTOR2>		m_vecLightPosition;
public:
	CUITrafficLight();
	virtual ~CUITrafficLight();
	virtual void Setup() = 0;
	void SetPosition();
};

