#pragma once
#include "CTile.h"
class CSand :
	public CTile
{
public:
	CSand(D3DXVECTOR3 vPosition);
	~CSand();

	void Update() override;
};

