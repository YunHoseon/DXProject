#pragma once
#include "CActor.h"
#include "CCharacter.h"

class CDebugPlayer1 
	: public CCharacter
{
private:

public:
	CDebugPlayer1(IInteractCenter* pInteractCenter = nullptr);
	virtual ~CDebugPlayer1();
};

