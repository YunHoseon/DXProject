#pragma once
#include "CUIButton.h"

class CUITrafficLightBoard :
	public CUIButton
{
protected:
	vector<D3DXVECTOR2>		m_vecLightPosition;
public:
	CUITrafficLightBoard();
	virtual ~CUITrafficLightBoard();
	virtual void Setup() = 0;
	void SetPosition();
};

