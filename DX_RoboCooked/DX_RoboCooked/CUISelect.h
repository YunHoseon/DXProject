#pragma once
#include "CUIButton.h"
class CUIStar;

class CUISelect :
	public CUIButton
{
protected:
	string		m_sStageID;
	float		m_fGameTime;
public:
	CUISelect(D3DXVECTOR2 vPos ,string chStageID,float fTime);
	~CUISelect();

public:
	void Setup() = 0;
};

