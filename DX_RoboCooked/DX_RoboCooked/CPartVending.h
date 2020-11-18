#pragma once
#include "CInteractiveActor.h"

class CPartVending : public CInteractiveActor
{
public:
	CPartVending();
	~CPartVending();

	void Interact(CCharacter* pCharacter) override;
};

