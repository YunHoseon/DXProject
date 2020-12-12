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
	int GetLightCount() { return m_vecLightPosition.size(); }
	D3DXVECTOR2 GetLightPosition(int i) { return m_vecLightPosition[i]; }
};

