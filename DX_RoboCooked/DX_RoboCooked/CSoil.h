#pragma once
#include "CTile.h"
class CSoil :
	public CTile
{
public:
	CSoil(D3DXVECTOR3 vPosition);
	~CSoil();

	void Update() override;
};

