#pragma once
#include "CTile.h"
class CStair :
	public CTile
{
public:
	CStair(D3DXVECTOR3 vPosition);
	~CStair();

	void Render() override;
};

