#pragma once
#include "CActor.h"
class CInteractiveActor :
	public CActor
{
public:
	CInteractiveActor();
	~CInteractiveActor();

	virtual void Interact() = 0;
};

