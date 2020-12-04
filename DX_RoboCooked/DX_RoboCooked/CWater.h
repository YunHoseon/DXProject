#pragma once
#include "CTile.h"
class CWater :
	public CTile
{
public:
	CWater(D3DXVECTOR3 vPosition);
	~CWater();

	void Update() override;
};

