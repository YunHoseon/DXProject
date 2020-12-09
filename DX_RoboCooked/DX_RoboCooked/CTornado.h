#pragma once
#include "CActor.h"
class CTornado :
	public CActor
{
public:
	CTornado(D3DXVECTOR3 pos);
	~CTornado();

public:
	void Update() override;
	void Render() override;

	FLOAT GetPower() { return 0.01f; }

};

