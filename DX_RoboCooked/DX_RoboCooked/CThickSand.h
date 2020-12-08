#pragma once
#include "CTile.h"
class CThickSand :
	public CTile
{
public:
	CThickSand(D3DXVECTOR3 vPosition);
	~CThickSand();

	void Update() override;
};

