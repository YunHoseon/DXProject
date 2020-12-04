#pragma once
#include "CTile.h"
class CSand3 :
	public CTile
{
public:
	CSand3(D3DXVECTOR3 vPosition);
	~CSand3();

	void Render() override;
	void Update() override;
};

