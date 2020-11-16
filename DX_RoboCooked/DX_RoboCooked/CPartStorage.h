#pragma once
#include "CInteractiveActor.h"
#include "IPartGenerator.h"
class CPartStorage :
	public CInteractiveActor ,IPartGenerator 
{
public:
	CPartStorage();
	~CPartStorage();


public:
	void Make() override;
	void Interact() override;
};

