#pragma once
#include "CUITexture.h"

class CUICC : public CUITexture
{
public:
	CUICC(char* DisabledPath, char* ActivePath, char* HoverPath, D3DXVECTOR3* pPosition = nullptr);
	void Render() override;
};
