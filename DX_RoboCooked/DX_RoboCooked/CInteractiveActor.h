#pragma once
#include "CActor.h"

class CCharacter;


class CInteractiveActor :
	public CActor
{
public:
	CInteractiveActor();
	virtual ~CInteractiveActor();

	virtual void Interact(CCharacter* pCharacter) = 0;
};

