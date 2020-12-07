#pragma once
#include "CActor.h"
class CTornado :
	public CActor
{
public:
	CTornado();
	~CTornado();

public:
	void Update() override;
	void Render() override;

	FLOAT GetPower() { return 0.01f; }

};

