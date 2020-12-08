#pragma once
#include "CTile.h"
class CFlowSand :
	public CTile
{
public:
	CFlowSand(D3DXVECTOR3 vPosition);
	~CFlowSand();

	void Update() override;
};

