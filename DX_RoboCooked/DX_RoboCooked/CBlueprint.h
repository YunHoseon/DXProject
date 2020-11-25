#pragma once
#include "CActor.h"

enum class eBluePrintState
{
	Usable,
	Unusable
};

class CBlueprint :
	public CActor
{
private:
	D3DXVECTOR3		m_vScale;
	bool			m_isRightPartsID;
	bool			m_isRightPartsAngle;
	float			m_fProcessivity;

public:
	CBlueprint();
	~CBlueprint();
};

