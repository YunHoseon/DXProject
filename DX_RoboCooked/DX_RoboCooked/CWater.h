#pragma once
#include "CTile.h"
class CWater :
	public CTile
{
public:
	CWater(D3DXVECTOR3 vPosition);
	~CWater();

	void Render() override;
	void Update() override;
	bool Collide(CActor* target, D3DXVECTOR3* pNormal) override;

	void CreateShadowMap() override {}
};

