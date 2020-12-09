#pragma once
#include "CTile.h"
class CBrick :
	public CTile
{
public:
	CBrick(D3DXVECTOR3 vPosition);
	~CBrick();

	void Update() override;
};

