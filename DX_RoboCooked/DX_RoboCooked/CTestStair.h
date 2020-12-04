#pragma once
#include "CActor.h"

class CTestStair : public CActor
{
public:
	CTestStair();
	virtual ~CTestStair();
	void Update() override;
	void Render() override;
};
